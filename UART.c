#include <p33FJ128GP804.h>
#include "UART.h"
#include "Clock.h"
#include "libpic30.h"
#include "RingBuffer.h"
#include "stdint.h"

/*==================== [Macros y definiciones] ===========================*/
#define RING_BUFFER_SIZE 16   // Tama�o del Ring Buffer
/*========================================================================*/

/*======================= [Variables Internas] ===========================*/
void* pRingBufferTx_U1;     
void* pRingBufferRx_U1;  
void* pRingBufferTx_U2;  
void* pRingBufferRx_U2;
uint8_t Char_Recup[4];
/*========================================================================*/

void Config_UART(void){

    /*******************        Configuraci�n UART 1        *******************/
    
    //Register U1MODE
    U1MODEbits.UEN = 0b00;          // Solamente utilizamos los pines U1TX U1RX  
    U1MODEbits.BRGH = 0b0;          // Baud Rate Generator genera 16 clock por bit
    U1MODEbits.STSEL = 0b0;         // 1-stop bit
    U1MODEbits.PDSEL = 0b0;         // No Parity, 8-data bits
    
    //Register U1STA
    U1STAbits.UTXISEL0 = 0b0;       // Interrupci�n cuando se transmita al registro TSR un caracter y el buffer de transmisi�n este vac�o
    U1STAbits.UTXISEL1 = 0b1;      
    U1STAbits.URXISEL = 0b10;       // Interrupciones cuando hay 3 (o 4) datos en el buffer de recepci�n
      
    // Con este valor de BRG obtengo un Baud Rate de 9615 y un error del 0.125% respecto al buscado de 9600 */
    U1BRG = 259;                    //Valor del Baud Rate Generator Register de la UART1

    /*******************        Configuraci�n UART 2        *******************/
      
    //Register U2MODE
    U2MODEbits.UEN = 0b00;          // Solamente utilizamos los pines U1TX U1RX
    U2MODEbits.BRGH = 0b0;          // Baud Rate Generator genera 16 clock por bit
    U2MODEbits.STSEL = 0b0;         // 1-stop bit
    U2MODEbits.PDSEL = 0b0;         // No Parity, 8-data bits
    
    //Register U2STA
    U2STAbits.UTXISEL0 = 0b0;       // Interrupci�n cuando se transmita al registro TSR un caracter y el buffer de transmisi�n
    U2STAbits.UTXISEL1 = 0b1;       
    U2STAbits.URXISEL = 0b10;       // Interrupciones cuando hay 3 (o 4) datos en el buffer de recepci�n
    
    U2BRG = U1BRG;                  // Valor del Baud Rate Generator de la UART2
}

void Create_RingBuffer(void){
    /* Inicializaci�n de buffer de recepci�n y transmisi�n*/
    pRingBufferTx_U1 = ringBuffer_init(RING_BUFFER_SIZE);
    pRingBufferRx_U1 = ringBuffer_init(RING_BUFFER_SIZE);     
    pRingBufferTx_U2 = ringBuffer_init(RING_BUFFER_SIZE);
    pRingBufferRx_U2 = ringBuffer_init(RING_BUFFER_SIZE);
}

/*******************        UART1        *******************/

void Enable_UART1(void){
    U1MODEbits.UARTEN = 0b1;        // Habilito la UART1
    __delay_us(60);
    U1STAbits.UTXEN = 0b1;          // Habilito el transmisor de la UART1
    __delay_us(150);                // Se recomienda este delay luego de habilitar el transmisor UART
}

void Disable_UART1(void){
    // Antes de deshabilitar la UART debemos retirar todos los datos de la FIFO RX y TX
    // sino se pierden todos los caracteres almacenados en ella
    U1STAbits.UTXEN = 0b0;          // Deshabilito el transmisor de la UART1
    __delay_us(200);                // Delay por seguridad
    U1MODEbits.UARTEN = 0b0;        // Deshabilito la UART1
}

unsigned int Tx_Reg_U1_State(void){
    if(U1STAbits.UTXBF == 1){
        // Buffer de transmisi�n lleno
        return(1);
    }
    else    
        // Al menos una palabra puede escribirse en la pila
    return(0);
}

unsigned int Tx_Shift_Reg_U1_State(void){
    if(U1STAbits.TRMT == 0){
        // Transmitiendo datos y/o tambi�n existe datos en cola.
        return(1);
    }
    else    
        // Registro vacio y no hay m�s datos a enviar
    return(0);
}

unsigned int Rx_Reg_U1_State(void){
    if(U1STAbits.URXDA == 1){
        // Al menos un caracter disponible en el buffer de recepci�n.
        return(1);
    }
    else
        return(0);
}

unsigned int Rx_Shift_Reg_U1_State(void){
    if(U1STAbits.RIDLE == 1){
        // Registro de recepci�n vac�o (Esperando recepci�n)
        return(1);
    }
    else
        // Recibiendo datos.
        return(0);
}

void Get_Char_Rx_Reg_U1(uint8_t *data){
     *data = U1RXREG;
}

void Send_Char_Tx_Reg_U1(uint8_t *data){
    U1TXREG = *data;
}

/*******************        UART2        *******************/

void Enable_UART2(void){
    U2MODEbits.UARTEN = 0b1;        // Habilito la UART2
    __delay_us(60);
    U2STAbits.UTXEN = 0b1;          // Habilito el transmisor de la UART2
    __delay_us(150);                // Se recomienda este delay luego de habilitar el transmisor UART
}

void Disable_UART2(void){
    // Antes de deshabilitar la UART se debe retirar todos los datos de las FIFO's RX y TX
    // sino se pierden todos los caracteres almacenados en ella
    U2STAbits.UTXEN = 0b0;          // Deshabilito el transmisor de la UART1
    __delay_us(200);                // Delay por seguridad
    U2MODEbits.UARTEN = 0b0;        // Deshabilito la UART1
};

unsigned int Tx_Reg_U2_State(void){
    if(U2STAbits.UTXBF == 1){
        //Buffer de transmisi�n lleno
        return(1);
    }
    else    
    //Al menos un caracter puede escribirse en la pila
    return(0);
}

unsigned int Tx_Shift_Reg_U2_State(void){
    if(U2STAbits.TRMT == 0){
        // Transmitiendo datos y/o tambi�n existe datos en cola.
        return(1);
    }
    else    
        // Registro vacio y no hay m�s datos a enviar
    return(0);
}

unsigned int Rx_Reg_U2_State(void){
    if(U2STAbits.URXDA == 1){
        //Al menos un caracter disponible en el buffer de recepci�n.
        return(1);
    }
    else
        //Buffer de recepci�n de la UART vac�o
        return(0);
}

unsigned int Rx_Shift_Reg_U2_State(void){
    if(U2STAbits.RIDLE == 1){
        // Registro de recepci�n vac�o (Esperando recepci�n)
        return(1);
    }
    else
        // Recibiendo datos.
        return(0);
}

void Get_Char_Rx_Reg_U2(uint8_t *data){
     *data = U2RXREG;
}

void Send_Char_Tx_Reg_U2(uint8_t *data){
    U2TXREG = *data;
}

// Posible testeo de las UARTS conectando transmisor y receptor.
void Loopback_Mode(void){
    
    /*******************        Configuraci�n UART 1        *******************/
    
    //Register U1MODE
    U1MODEbits.UEN = 0b00;          // Solamente utilizamos el pin U1TX (U1RX esta sin utilizaci�n).
    U1MODEbits.UARTEN = 0b1;        // Habilito la UART1     
    U1MODEbits.BRGH = 0b0;          // Baud Rate Generator genera 16 clock por bit
    U1MODEbits.STSEL = 0b0;         // 1-stop bit
    U1MODEbits.PDSEL = 0b0;         // No Parity, 8-data bits
    
    //Register U1STA
    //U1STAbits.URXISEL = 0b00;     // Configuraci�n de interrupci�n del transmisor
    //U1STAbits.URXISEL = 0b00;     // Modo de interrupci�n por Buffer de recepci�n
        
    // Con este valor de BRG obtengo un Baud Rate de 9615 y un error del 0.125% respecto al buscado de 9600 */
    U1BRG = 259;    //Valor del Baud Rate Generator Register de la UART1
    
    //Era recomendado ponerlo luego de haber configurado todo
    U1MODEbits.LPBACK = 0b01;       //Loopback Mode habilitado U1TX conectado internamente a U1RX
    
    /*******************        Configuraci�n UART 2        *******************/
      
    //Register U2MODE
    U2MODEbits.UEN = 0b00;          // Solamente utilizamos el pin U1TX (U1RX esta sin utilizaci�n).
    U2MODEbits.UARTEN = 0b1;        // Habilito la UART2
    U2MODEbits.BRGH = 0b0;          // Baud Rate Generator genera 16 clock por bit
    U2MODEbits.STSEL = 0b0;         // 1-stop bit
    U2MODEbits.PDSEL = 0b0;         // No Parity, 8-data bits
    
    //Register U2STA
    //U2STAbits.URXISEL = 0b00;     // Configuraci�n de interrupci�n del transmisor
    //U2STAbits.URXISEL = 0b00;     // Modo de interrupci�n por Buffer de recepci�n
    
    U2BRG = U1BRG;    //Valor del Baud Rate Generator de la UART2. Ponemos el mismo en las dos UART.
    
    //Era recomendado ponerlo luego de haber configurado todo
    U2MODEbits.LPBACK = 0b01;       //Loopback Mode habilitado U2TX conectado internamente a U2RX
}

int32_t uart_ringBuffer_recDatos_U1(uint8_t *pBuf, int32_t size){
    int32_t ret = 0;
    
    /* Es necesario deshabilitar las dem�s interrupci�nes para garantizar que no perdamos alg�n dato
    
     Para desactivar las interrupciones de prioridad entre 1 y 6 es necesario setear el bit
     INTCON2bits.DISI en 1 para que se ejecute la instrucci�n DISI. Luego es necesario setear el n�mero de
     ciclos de clock que vamos tener deshabilitadas estas en el registro DISICNT. Si este registro llega
     a 0 se vuelven a habilitar las interrupciones. 
    
    */
    
    INTCON2bits.DISI = 0b1;     // Deshabilito todas las interrupciones 
    DISICNT = 16384;            // M�ximo valor posible de ciclos de deshabilitaci�n de interrupciones 
       
    /*================== Secci�n critica de c�digo ==================*/
    
    while (!ringBuffer_isEmpty(pRingBufferRx_U1) && ret < size)
    {
    	uint8_t dato;

        ringBuffer_getData(pRingBufferRx_U1, &dato);
        pBuf[ret] = dato;
        ret++;
        DISICNT = 16384;        // Recarga del contador
    }
    DISICNT = 0;                // Habilitamos nuevamente las interrupciones
    
    /*================== Fin de secci�n critica de c�digo ==================*/
return ret;
}

int32_t uart_ringBuffer_envDatos_U1(uint8_t *pBuf, int32_t size){
    int32_t ret = 0;
    
    /* Es necesario deshabilitar las dem�s interrupci�nes para garantizar que no perdamos alg�n dato
    
     Para desactivar las interrupciones de prioridad entre 1 y 6 es necesario setear el bit
     INTCON2bits.DISI en 1 para que se ejecute la instrucci�n DISI. Luego es necesario setear el n�mero de
     ciclos de clock que vamos tener deshabilitadas estas en el registro DISICNT. Si este registro llega
     a 0 se vuelven a habilitar las interrupciones. 
    
    */ 
    
    INTCON2bits.DISI = 0b1;     // Deshabilito todas las interrupciones 
    DISICNT = 16384;            // M�ximo valor posible de ciclos de deshabilitaci�n de interrupciones 
       
    /*================== Secci�n critica de c�digo ==================*/
    
    /* si el buffer estaba vac�o hay que habilitar la int TX */
    if (ringBuffer_isEmpty(pRingBufferTx_U1))

    while (!ringBuffer_isFull(pRingBufferTx_U1) && ret < size)
    {
        ringBuffer_putData(pRingBufferTx_U1, pBuf[ret]);
        ret++;
        DISICNT = 16384;        // Recarga del contador
    }
    DISICNT = 0;                // Habilitamos nuevamente las interrupciones
    
    /*============== Fin de secci�n critica de c�digo ===============*/
return ret;
}

int32_t uart_ringBuffer_recDatos_U2(uint8_t *pBuf, int32_t size){
    int32_t ret = 0;
    
    /* Es necesario deshabilitar las dem�s interrupci�nes para garantizar que no perdamos alg�n dato
    
     Para desactivar las interrupciones de prioridad entre 1 y 6 es necesario setear el bit
     INTCON2bits.DISI en 1 para que se ejecute la instrucci�n DISI. Luego es necesario setear el n�mero de
     ciclos de clock que vamos tener deshabilitadas estas en el registro DISICNT. Si este registro llega
     a 0 se vuelven a habilitar las interrupciones. 
    
     */
    
    INTCON2bits.DISI = 0b1;     // Deshabilito todas las interrupciones 
    DISICNT = 16384;            // M�ximo valor posible de ciclos de deshabilitaci�n de interrupciones 
       
    /*================== Secci�n critica de c�digo ==================*/
    
    while (!ringBuffer_isEmpty(pRingBufferRx_U2) && ret < size)
    {
    	uint8_t dato;

        ringBuffer_getData(pRingBufferRx_U2, &dato);
        pBuf[ret] = dato;
        ret++;
        DISICNT = 16384;        // Recarga del contador
    }
    DISICNT = 0;                // Habilitamos nuevamente las interrupciones
    
    /*============== Fin de secci�n critica de c�digo ===============*/
return ret;
}

int32_t uart_ringBuffer_envDatos_U2(uint8_t *pBuf, int32_t size){
    int32_t ret = 0;
    
    /* Es necesario deshabilitar las dem�s interrupci�nes para garantizar que no perdamos alg�n dato
    
     Para desactivar las interrupciones de prioridad entre 1 y 6 es necesario setear el bit
     INTCON2bits.DISI en 1 para que se ejecute la instrucci�n DISI. Luego es necesario setear el n�mero de
     ciclos de clock que vamos tener deshabilitadas estas en el registro DISICNT. Si este registro llega
     a 0 se vuelven a habilitar las interrupciones. 
    
     */
    
    INTCON2bits.DISI = 0b1;     // Deshabilito todas las interrupciones 
    DISICNT = 16384;            // M�ximo valor posible de ciclos de deshabilitaci�n de interrupciones 
    
    /*================== Secci�n critica de c�digo ==================*/
    
    /* si el buffer estaba vac�o hay que habilitar la int TX */
    if (ringBuffer_isEmpty(pRingBufferTx_U2))

    while (!ringBuffer_isFull(pRingBufferTx_U2) && ret < size)
    {
        ringBuffer_putData(pRingBufferTx_U2, pBuf[ret]);
        ret++;
        DISICNT = 16384;        // Recarga del contador
    }
    
    DISICNT = 0;                // Habilitamos nuevamente las interrupciones
    
    /*============== Fin de secci�n critica de c�digo ===============*/
return ret;
}

/* Dado que no utilizamos el registro PSV ni tenemos mapeados en dicha memoria ninguna variable
 que nos sea de interes guardar y no perder, no tenemos que utilizar ciclos de clocks de seguridad 
 en escrituras/lecturas asociadas a dicho registro.
 */

void __attribute__((interrupt,no_auto_psv)) _U1TXInterrupt(void){
    uint8_t data;           //Variable temporal - Almacena 1 dato del RB

    if(!Tx_Reg_U1_State() && ringBuffer_getData(pRingBufferTx_U1, &data)){      //Hay al menos un lugar en el buffer de transmisi�n y tenemos datos en el RB
        while( !Tx_Reg_U1_State() && ringBuffer_getData(pRingBufferTx_U1, &data) ){     //Hasta que no se llene el registro de transmisi�n
            Send_Char_Tx_Reg_U1(&data);
        }
    }
    else
        // No hay datos en RB, se limpia solo la bandera seteada por que se vac�o el TXREG 
    IFS0bits.U1TXIF = 0;    // Clear TX Interrupt flag
}

void __attribute__((interrupt,no_auto_psv)) _U1RXInterrupt(void){
    uint8_t data;           //Variable temporal - Almacena 1 dato del RB
   
    while( !Rx_Reg_U1_State() ){        // Hay al menos 1 dato en la FIFO de RXREG, vaciamos el registro
        Get_Char_Rx_Reg_U1(&data);      // Saco un dato x iteraci�n
        ringBuffer_putData(pRingBufferRx_U2, data);
    }
    
    IFS0bits.U1RXIF = 0;    // Clear RX Interrupt flag
}

void __attribute__((interrupt,no_auto_psv)) _U1ErrInterrupt(void){
    uint8_t data;
    int i = 0,j = 0;
   
    if(U1STAbits.OERR && !U1STAbits.FERR){ // Overflow
        
            while( !Rx_Reg_U1_State() ){
                Get_Char_Rx_Reg_U1(&data);   // Saco un dato x iteraci�n, lo guardo dentro de data
                ringBuffer_putData(pRingBufferRx_U1, data);     // Envio el dato recuperado de la FIFO al RB
            }
            
        // Podr�amos usar una l�gica de ACK para hacerle sabera la PC que esta todo joya y puede mandar 
        // cuando recibimos un dato y que puede mandar el pr�ximo dato. Sino que vuelva a mandar dicho dato.
            
        U1STAbits.OERR &= ~(1UL << 0b1); // Clear del overrun para permitir recepci�n de m�s datos
    }
    if(U1STAbits.FERR && !U1STAbits.OERR){ // Falla en la detecci�n del bit de STOP
        
        while(!Rx_Reg_U1_State()){
           Get_Char_Rx_Reg_U1(&data);  // Saco un dato x iteraci�n, lo guardo dentro de data
           Char_Recup[i] = data;       // Uso i para saber cuantos datos recupero de la FIFO (Valor m�x = dato con error)
           i++;
        }
        
        while( i != (j+1) ){         // Uso j para escribir los datos sin error. En i = j esta el dato que esta roto
            ringBuffer_putData(pRingBufferRx_U1, Char_Recup[j]);     // Envio el dato recuperado de la FIFO al RB
            j++;
        }
        
        // Char_Recup[j] tiene el dato erroneo.
        
        // Podriamos enviar un mensaje para hacerle saber a la PC que hubo un problema y que mande de nuevo el mensaje
        // Si se utiliza la l�gica de ACK, si no se le envia nada a la PC esta volver�a a retransmitir el �ltimo dato.
        i=0; j=0;
    }
        
    if(U1STAbits.FERR && U1STAbits.OERR){
        
        while(!Rx_Reg_U1_State() && i < 4){     // Vacio solamente RXREG, el dato erroneo esta en RSR
            Get_Char_Rx_Reg_U1(&data);          // Saco un dato x iteraci�n, lo guardo dentro de data    
            ringBuffer_putData(pRingBufferRx_U1, data);     // Envio el dato recuperado al RB
            i++;
        }
        // Podriamos enviar un mensaje para hacerle saber a la PC que hubo un problema y que mande de nuevo el mensaje
        // Si se utiliza la l�gica de ACK, si no se le envia nada a la PC esta podr�a volver a retransmitir el �ltimo dato.
        i = 0;
        U1STAbits.OERR &= ~(1UL << 0b1); // Clear del overrun para permitir recepci�n de m�s datos
    }
    IFS4bits.U1EIF = 0;     // Clear Error Interrupt flag
}

void __attribute__((interrupt,no_auto_psv)) _U2TXInterrupt(void){
    uint8_t data;           //Variable temporal - Almacena 1 dato del RB
    
    if(!Tx_Reg_U1_State() && ringBuffer_getData(pRingBufferTx_U1, &data)){
        //Hay al menos un lugar en el buffer de transmisi�n y tenemos datos en el RB
        while( !Tx_Reg_U2_State() && ringBuffer_getData(pRingBufferTx_U2, &data) ){
            Send_Char_Tx_Reg_U2(&data);
        }
    }
    else
        // No hay datos en RB, se limpia solo la bandera seteada.
        
    IFS1bits.U2TXIF = 0;    // Clear TX Interrupt flag
}
void __attribute__((interrupt,no_auto_psv)) _U2RXInterrupt(void){
    uint8_t data;           //Variable temporal - Almacena 1 dato del RB
  
    while( !Rx_Reg_U2_State() ){
        Get_Char_Rx_Reg_U2(&data);      // Saco un dato x iteraci�n, lo guardo dentro de data
        ringBuffer_putData(pRingBufferRx_U2, data);     // Envio el dato recuperado al RB
    }
    
    IFS1bits.U2RXIF = 0;    // Clear RX Interrupt flag 
}

void __attribute__((interrupt,no_auto_psv)) _U2ErrInterrupt(void){
    uint8_t data;
    int i = 0,j = 0;
   
    if(U2STAbits.OERR && !U2STAbits.FERR){ // Overflow
        
            while( !Rx_Reg_U2_State() ){
                Get_Char_Rx_Reg_U2(&data);   // Saco un dato x iteraci�n, lo guardo dentro de data
                ringBuffer_putData(pRingBufferRx_U2, data);     // Envio el dato recuperado de la FIFO al RB
            }
            
        // Podr�amos usar una l�gica de ACK para hacerle sabera la PC que esta todo joya y puede mandar 
        // cuando recibimos un dato y que puede mandar el pr�ximo dato. Sino que vuelva a mandar dicho dato.
            
        U2STAbits.OERR &= ~(1UL << 0b1); // Clear del overrun para permitir recepci�n de m�s datos
    }
    if(U2STAbits.FERR && !U2STAbits.OERR){ // Falla en la detecci�n del bit de STOP
        
        while(!Rx_Reg_U2_State()){
           Get_Char_Rx_Reg_U2(&data);  // Saco un dato x iteraci�n, lo guardo dentro de data
           Char_Recup[i] = data;       // Uso i para saber cuantos datos recupero de la FIFO (Valor m�x = dato con error)
           i++;
        }
        
        while( i != (j+1) ){         // Uso j para escribir los datos sin error. En i = j esta el dato que esta roto
            ringBuffer_putData(pRingBufferRx_U2, Char_Recup[j]);     // Envio el dato recuperado de la FIFO al RB
            j++;
        }
        
        // Char_Recup[j] tiene el dato erroneo.
        
        // Podriamos enviar un mensaje para hacerle saber a la PC que hubo un problema y que mande de nuevo el mensaje
        // Si se utiliza la l�gica de ACK, si no se le envia nada a la PC esta volver�a a retransmitir el �ltimo dato.
        i=0; j=0;
    }
        
    if(U2STAbits.FERR && U2STAbits.OERR){
        
        while(!Rx_Reg_U2_State() && i < 4){     // Vacio solamente RXREG, el dato erroneo esta en RSR
            Get_Char_Rx_Reg_U2(&data);          // Saco un dato x iteraci�n, lo guardo dentro de data    
            ringBuffer_putData(pRingBufferRx_U2, data);     // Envio el dato recuperado al RB
            i++;
        }
        // Podriamos enviar un mensaje para hacerle saber a la PC que hubo un problema y que mande de nuevo el mensaje
        // Si se utiliza la l�gica de ACK, si no se le envia nada a la PC esta podr�a volver a retransmitir el �ltimo dato.
        i = 0;
        U2STAbits.OERR &= ~(1UL << 0b1); // Clear del overrun para permitir recepci�n de m�s datos
    }
    IFS4bits.U2EIF = 0;     // Clear Error Interrupt flag 
}

