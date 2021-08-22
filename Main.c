/*
 * File:   main.c
 * Author: Jere
 *
 * Created on 18 de marzo de 2021, 14:50
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "DAC.h"
#include "Clock.h"
#include "libpic30.h"   
#include "IO_Config.h"
#include "UART.h"
#include "ADC.h"
#include "RingBuffer.h"
#include "Protocolo_Comm_Yaesu.h"
#include "interrupts.h"
#include "Entradas.h"
#include "Salidas_Motores.h"
#include "timer1.h"

static uint8_t Bandera_Home_Stop_1 = 1;

extern Last_Value Valor_Anterior;


void Chequear_Home_Stop_1(void){
    if(Home_Stop_1 != Valor_Anterior.Home_St0p_1){
        if(Home_Stop_1 == HIGH && Bandera_Home_Stop_1 == 1){
            //Seteo de posicion de reposo de alguna manera
            Bandera_Home_Stop_1 = 0;
        }
        if(Home_Stop_1 == HIGH && Bandera_Home_Stop_1 == 0){
            //Definir acciones
        }
        Home_Stop_1 = Valor_Anterior.Home_St0p_1;
    }
}

int main(){
        
//    Create_RingBuffer();    // Ponerlo antes de habilitar el uso de UART
    
    /* ============   Configuraci�n interna del microcontrolador   ============ */
    Config_Clock();
    Config_IO();
    Config_UART();
    Config_ADC();
    
    init_timer1();

    initInterrupts();
    /* ======================================================================== */

    // Change_Config_UART1();       // Recordar de remapear los pines de la UART 1

    LATAbits.LATA4 = 1;
    SetTimer(TEMP_1, 100);
    
    while(1) {

        if(GetTimer(TEMP_1) == 1)
        {
            LATAbits.LATA4 = !PORTAbits.RA4;
            SetTimer(TEMP_1, 100);
        }
        
        
        Comm_PC_Interface();
        //MEF_Accionamiento();
        //MEF_Principal();
        //Chequear_Home_Stop_1();
    }
    return (EXIT_SUCCESS);
}