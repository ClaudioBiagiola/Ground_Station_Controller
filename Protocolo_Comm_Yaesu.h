/* 
 * File:   Protocol_Comm_Yaesu.h
 * Author: Jere
 *
 * Created on 24 de mayo de 2021, 10:35
 */
#include "stdint.h"

#ifndef PROTOCOL_COMM_YAESU_H
#define	PROTOCOL_COMM_YAESU_H

#ifdef	__cplusplus
extern "C" {
#endif
    
/*==================== [Macros de Comunicaciones] ========================*/
#define START_OF_HEADING 1      // Comienzo de encabezado
#define START_OF_TEXT 2         // Comienzo de transmisi�n de un texto
#define END_OF_TEXT 3           // Fin de transmisi�n de un texto
#define END_OF_TRANSMISION 4    // Fin de la transmisi�n
#define ACKNOWLEDGE  6          // Dato recibido correctamente
#define BELL 7                  // Campana de llamado de atenci�n 
#define CHAR_LF  10             // Fin de linea  
#define CHAR_CR  13             // Retorno del carro
#define NEGATIVE_ACKNOWLEDGE 21 // Dato recibido incorrectamente

#define MAX_SIZE_COMMAND_AVALIBLE 14    // M�ximo dado por PC344.1 133.1'CR'
#define MAX_SIZE_DATA_SEND  16          // 'LF'+0344.1+0133.1'CR'
#define MAX_LONG_DATA_ANGLE 6           // M�xima longitud de datos asociada al �ngulo
/*========================================================================*/
    
/*===================== [Macros y Definiciones] ==========================*/
typedef struct{
    char Comando_Recibido[MAX_SIZE_COMMAND_AVALIBLE];
    char Char_Acimut[MAX_LONG_DATA_ANGLE];     //123.4\0
    char Char_Elevacion[MAX_LONG_DATA_ANGLE];  //160.8\0
} Comando_Almacenado;

typedef enum {
    Esperando_Datos = 0,
    Recopilando_Datos,
    Validando_Comando,
    Limpiando_Buffer,
    Comando_No_Reconocido
}Estado_Comunicacion;

typedef enum{
    Comando_No_Valido = 0,
        
    // Comandos manuales
    //Acimut
    Giro_Horario,                   // Clockwise Rotation
    Giro_Antihorario,               // Counter Clockwise Rotation
    Stop_Acimut,                    // CW/CCW Rotation Stop
    // Elevacion
    Arriba,                         // UP Direction Rotation
    Abajo,                          // DOWN Direction Rotation
    Stop_Elevacion,                 // UP/DOWN Direction Rotation Stop

    // Comandos de lectura
    Devolver_Valor_Acimut,          // Retornar el valor de actual del �ngulo de de acimut 
    Devolver_Valor_Elevacion,       // Retornar el valor de actual del �ngulo de elevaci�n

    // Comandos de tracking
    Parar_Todo,                     // Stop Global
    Mayor_Presicion_a_e_grados,     // Formato de mayor precisi�n para combinaci�n
}ID_Comandos;
/*===========================================================================*/

/*============================ [Funciones] ==================================*/
void Comm_PC_Interface(void);
uint8_t Verificando_Comando(void);
/*===========================================================================*/
 
#ifdef	__cplusplus
}
#endif

#endif	/* PROTOCOL_COMM_YAESU_H */

