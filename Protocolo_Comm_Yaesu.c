#include "UART.h"
#include "RingBuffer.h"
#include "Protocolo_Comm_Yaesu.h"
#include "Entradas.h"
#include "Salidas_Motores.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <p33FJ128GP804.h>
/*
 * (CR)0xD -> Retorno de carro
 * (LF)0xA -> Avance de l�nea 
  
 * Se debe devolver un 'CR' desde el micro a la pc despu�s de cada comando y tambi�n un 
  0Ah se envian datos desde el micro

 * Comando no valido causa el retorno de "?>" y se debe borrar el comando recibido.
 
 * �ngulos en grados
 
 * Acimut: Incrementos positivos en sentido antihorario
 
 * Elevaci�n: Incrementos positivos respecto al plano horizontal
 
 * Para finalizar los comandos debemos enviar, despu�s del mismo,  'CR'
 * 
 * Si se envia una mayuscula o minuscula el comando debe ser ejecutado, si es valido.

 * Los �ngulos enviados a la interfaz de control deben tener 3 d�gitos (relleno a la izquierda con ceros), 
   y los �ngulos devueltos, en algunos casos, tener 4 d�gitos con un "+0" al principio.
 */

/*======================= [Lista de comandos validos] =======================*/
/*
  Trama (PC -> Interface):  Envio: XXX'CR'             (XXX comando valido)
  Trama (intercafe -> PC):  Respuesta: 'CR'            (Sin pedidos de datos)
                                       'CR''LF'XXX     (XXX datos)
                                       ?>              (Comando no valido)
 * 
 Nota: Los comandos basicos del Yaesu solo soportan 3 digitos por �ngulo, en el caso de los
 comando extendidos se enviaran/recibiran m�s caracteres.
 */

/* =======================   Comandos manuales   =======================
 * Acimut:
 *  R               // Clockwise Rotation
 *  L               // Counter Clockwise Rotation
 *  A               // CW/CCW Rotation Stop
 * Elevacion:
 *  U               // UP Direction Rotation
 *  D               // DOWN Direction Rotation
 *  E               // UP/DOWN Direction Rotation Stop
 * 
 * =======================   Comandos lectura   =========================
 *  C               // Retornar el valor actual del �ngulo de acimut
 *  B               // Retornar el valor de actual del �ngulo de elevaci�n
 * 
 * =======================   Comandos tracking   ========================
 *  S               // Parar todo moviento asociado a cualquier �ngulo
 *  Paaa.a eee.e    // Establecer objetivo de tracking
 
   ====================================================================== */

/*===================== [Variables Internas (Globales)] =====================*/
uint8_t Mensaje_Env[MAX_SIZE_DATA_SEND];
uint8_t Mensaje_Error[] = "?>";
uint8_t Mensaje_Recibido_Correcto[] = "\r";

uint8_t Caracter_Rec;
uint32_t FlagRec;
uint32_t Indice_Rec = 0;
char Buffer_Recepcion[MAX_SIZE_COMMAND_AVALIBLE];

Info_Comandos_Procesados Comando_Procesado;

uint8_t Flag_Parada_Emergencia = 0;     
Comando_Almacenado Char_Comando;
/*===========================================================================*/

/*===================== [Variables Externas (Globales)] =====================*/
extern volatile int Error_UART_U2;

extern Struct_Data_Control Data_Control;
extern _Contador Contador;
/*===========================================================================*/

/*
    Esta funci�n segmenta un string de acuerdo a los delimitadores definidos y 
separa la cadena ingresada en segmentos que se encuentren entre ellos. Se debe
corroborar el formato de la misma antes de el llamado de esta funci�n, dado que 
esta solo divide la cadema ingresada.

Para el uso se debe pasar la direcci�n de memoria del string a partir de la cual se 
comenzara a filtra los datos, una vez detectado un espacio o un 'CR' se copiara dicha cadena
y se devolveran los datos a traves de Out_Data_Ac y Out_Data_El, si no se detecto el final del string.
En caso de querer un �nico segmento de salida, repetir el dato de salida en los dos campos anteriores.
  
    char *Dato_No_Filtrada   (IN)        ->  Puntero al string a filtrar
    char* Out_Data_Ac        (IN/OUT)    ->  Primer dato de salida
    char* Out_Data_El        (IN/OUT)    ->  Segundo dato de salida
*/
void Segmentar_Datos(char *Raw_Data, char* Out_Data_Ac, char* Out_Data_El){
    
    while(!isdigit(*Raw_Data)){
        Raw_Data++;     // Sacamos los datos que no son digitos
    }
    
    char * token;
    char *Delimitador = " \r";  //Caracteres de a delimitar el string: ' ' (space) y 'CHAR_CR' o '\r' (carriage return))
    token = strtok(Raw_Data, Delimitador);
    strcpy(Out_Data_Ac,token);
    token = strtok(NULL, Delimitador);
    if( token != NULL){
        strcpy(Out_Data_El,token);
    }
}


/* =========================================================================================================== */
/* 
    Esta funci�n an�liza el formato del dato enviado por la PC a la interface. Es la encargada de 
determinar si un dato esta correcto de acuerdo a la forma de definici�n del comando seg�n lo comentado
en la parte superior del archivo.
Retorna un 1 si el comando esta correcto. En caso contrario se devolvera un 0
 
    char* Segmento      (IN)    ->  Puntero a cadena a analizar.
 */
int Analizando_Datos(char* Segmento){
    
    // P123.1 123.1\r
    int j = 1, Angulo_Num = 0, Cant_Dig_Antes = 0;
    
    while(Segmento[j] != '\r'){
        
        Angulo_Num++;
        if(Angulo_Num > 2){
            // M�s de dos angulos se detectaron.
            return 0;
        }
        
        for( ; Segmento[j] != '.' && !isspace(Segmento[j]); j++){
            if(!isdigit(Segmento[j])){
                //Error detectando digitos
                return 0;
            }
            Cant_Dig_Antes++;
            if(Cant_Dig_Antes > 3){
                // + de 3 digitos en el �ngulo antes del '.' o ' '
                return 0;
            }
        }
        
        if(Segmento[j] == '.'){
            j++;
            for( ; !isspace(Segmento[j]); j++){
                if(!isdigit(Segmento[j])){
                    //Error detectando digitos
                    return 0;
                }
            }
        } else {
            // Punto decimal no detectado
            return 0;
        }
        
        j++;
        Cant_Dig_Antes = 0;
    }
    
    // Dato valido
    return 1; 
}


/* =========================================================================================================== */

uint8_t Verificando_Comando(){
    
    /* --------------------   Comandos manuales   -------------------- */
    
    // Acimut:
    
    if(Buffer_Recepcion[0] == 'R' || Buffer_Recepcion[0] == 'r') {
        putrsUART2("[Verificando_Comando] Comando GIRO_HORARIO detectado\r\n");
        return Giro_Horario;
    }
    
    if(Buffer_Recepcion[0] == 'L' || Buffer_Recepcion[0] == 'l') {
        putrsUART2("[Verificando_Comando] Comando GIRO_ANTIHORARIO detectado\r\n");
        return Giro_Antihorario;
    }
    
    if(Buffer_Recepcion[0] == 'A' || Buffer_Recepcion[0] == 'a') {
        putrsUART2("[Verificando_Comando] Comando STOP_ACIMUT detectado\r\n");
        return Stop_Acimut;
    }
    
    // Elevacion:
    
    if(Buffer_Recepcion[0] == 'U' || Buffer_Recepcion[0] == 'u') {
        putrsUART2("[Verificando_Comando] Comando ARRIBA detectado\r\n");
        return Arriba;
    }
    
    if(Buffer_Recepcion[0] == 'D' || Buffer_Recepcion[0] == 'd') {
        putrsUART2("[Verificando_Comando] Comando ABAJO detectado\r\n");
        return Abajo;
    }
    
    if(Buffer_Recepcion[0] == 'E' || Buffer_Recepcion[0] == 'e') {
        putrsUART2("[Verificando_Comando] Comando STOP_ELEVACION detectado\r\n");
        return Stop_Elevacion;
    }
    
    /* --------------------   Comandos tracking   -------------------- */
    
    // Parar todo
    if(Buffer_Recepcion[0] == 'S' || Buffer_Recepcion[0] == 's'){
        putrsUART2("[Verificando_Comando] Comando PARAR_TODO detectado\r\n");
        return Parar_Todo;
    }
    
    // Comando objetivo tracking
    if(Buffer_Recepcion[0] == 'P' || Buffer_Recepcion[0] == 'p'){
        putrsUART2("[Verificando_Comando] Comando OBJ_TRACKING detectado\r\n");
        if(Analizando_Datos(Buffer_Recepcion)){
            Segmentar_Datos(Buffer_Recepcion,Char_Comando.Char_Acimut,Char_Comando.Char_Elevacion);
            
            putrsUART2("\n\r [Verificando_Comando] azimut --> ");
            putrsUART2(Char_Comando.Char_Acimut);
            putrsUART2("\n\r [Verificando_Comando] elevacion --> ");
            putrsUART2(Char_Comando.Char_Elevacion);
            putrsUART2("\n\r");
            return Mayor_Presicion_a_e_grados;
        }
        else{
            putrsUART2("[Verificando_Comando] Comando tracking no valido\n\r");
            return Comando_No_Valido;
        }
    }
       
    /* --------------------   Comandos lectura   -------------------- */

    // Elevacion
    if(Buffer_Recepcion[0] == 'B' || Buffer_Recepcion[0] == 'b'){
        putrsUART2("[Verificando_Comando] Comando DEVOLVER_VALOR_ELEVACION detectado\n\r");
        return Devolver_Valor_Elevacion;
    }
    
    // Acimut
    if(Buffer_Recepcion[0] == 'C' || Buffer_Recepcion[0] == 'c'){
        putrsUART2("[Verificando_Comando] Comando DEVOLVER_VALOR_ACIMUT detectado\n\r");
        return Devolver_Valor_Acimut;
    }

    putrsUART2("[Verificando_Comando] Comando no valido\n\r");
    return Comando_No_Valido;
}


/* =========================================================================================================== */

void Comm_PC_Interface(){
    static Estado_Comunicacion Estado_Comm = Esperando_Datos;      
    FlagRec = uart_ringBuffer_recDatos_U2(&Caracter_Rec, sizeof(Caracter_Rec));

        switch (Estado_Comm){
            
            case Esperando_Datos:
                
                if( FlagRec != 0 ){
                    putrsUART2("[Comm_PC_Interface] Comando recibido\n\r");
                    Buffer_Recepcion[Indice_Rec] = Caracter_Rec;
                    Indice_Rec++;
                    
                    Estado_Comm = Recopilando_Datos;
                }      
                
                break;
            
            case Recopilando_Datos:
                
                if(Error_UART_U2 == 1) { 
                    Indice_Rec = 0;
                    Clean_RingBufferRx_U2();
                    Mensaje_Env[0] = ACKNOWLEDGE;
                    uart_ringBuffer_envDatos_U2(Mensaje_Env,sizeof(char));
                    Estado_Comm = Esperando_Datos;
                    break;
                }
                
                if((FlagRec != 0) && (Caracter_Rec != CHAR_CR)) {
                    if(Indice_Rec <= MAX_SIZE_COMMAND_AVALIBLE){
                        Buffer_Recepcion[Indice_Rec] = Caracter_Rec;
                        Indice_Rec++;
                    }
                    else{
                        Indice_Rec = 0;
                        Clean_RingBufferRx_U2();                        
                        Estado_Comm = Comando_No_Reconocido;
                        break;
                    }
                }
            
                if( (FlagRec != 0) && (Caracter_Rec == CHAR_CR) ){
                    Buffer_Recepcion[Indice_Rec] = Caracter_Rec;    
                    Estado_Comm = Validando_Comando;
                    break;
                }
            break;
            
            case Validando_Comando:
                
                putrsUART2("[Comm_PC_Interface] Comando recibido: ");
                putrsUART2(Buffer_Recepcion);
                putrsUART2("/n/r");
                putrsUART2("[Comm_PC_Interface] Validando comando...\n\r");
                
                    
            /* Se podr�a poner que cada cierto tiempo los comandos "manuales se borren, como para que no queden
                girando, o moviendose indefinidamente seg�n ese comando recibido. Creo que un polling de 10 ms
                nos ayudaria aca. No debe afectar a los comandos de posicionamiento. 
            */
                Comando_Procesado.Proximo = Verificando_Comando();

                if(Comando_Procesado.Proximo == Comando_No_Valido){
                    Estado_Comm = Comando_No_Reconocido;
                    break;
                }
                
//                uart_ringBuffer_envDatos_U2(Mensaje_Recibido_Correcto,sizeof(Mensaje_Recibido_Correcto));
//                strcpy(Char_Comando.Comando_Recibido,Buffer_Recepcion);
                    
                putrsUART2("[Comm_PC_Interface] Comando valido!\n\r");
                Comando_Procesado.Ultimo = Comando_Procesado.Actual;
                Comando_Procesado.Actual = Comando_Procesado.Proximo;
                    
//                if(!Flag_Parada_Emergencia){ 
//                    Comando_Procesado.Ultimo = Comando_Procesado.Actual;
//                    Comando_Procesado.Actual = Comando_Procesado.Proximo;
//                }
                
                Estado_Comm = Limpiando_Buffer;
                break;
                
            
            case Limpiando_Buffer:
                
                putrsUART2("[Comm_PC_Interface] Limpiando buffer...\n\r");
                
                int i = 0;
                while(i < MAX_SIZE_COMMAND_AVALIBLE) { // [TO DO] Fijarse si se puede usar size del Buffer_Recepcion 
                    Buffer_Recepcion[i] = '\0';
                    i++;
                }
                Indice_Rec = 0;
                Estado_Comm = Esperando_Datos;
                
                break;
                
                
            case Comando_No_Reconocido:
//                uart_ringBuffer_envDatos_U2(Mensaje_Error,sizeof(Mensaje_Error));
                putrsUART2("[Comm_PC_Interface] Comando NO RECONOCIDO\n\r");
                
                Estado_Comm = Limpiando_Buffer;
                break;
            
            default: Estado_Comm = Limpiando_Buffer;
        }
}
