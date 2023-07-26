/*
 * File:   newmain_PWM.c
 * Author: Miguel-Notebook
 *
 * Created on June 23, 2023, 9:19 PM
 */
#include "configuracion.h"
#include <xc.h>
#include <stdio.h>
#include <pic18f45k50.h>
#define _XTAL_FREQ 12000000

//PASO 2
//PWM periodo = (PR2 + 1)*4*Tosc*Prescaler //La frecuencia la escojemos nosotros
// 1/5KHz = (PR2 + 1)*4*(1/12MHZ)*16
//PR2 =(1/5KHz) /(4*(1/12MHZ)*16)
// PR2 + 1 = 37.5 
// PR2 - 1 = 36.5 = 36 -> 24 hex

//PASO4
//PWM duty cycle = (CCPRxL)x TOSC X (TMR2 Prescaler)
//CCPxL = PWM DC/Tosc x TMR2 prescaler 
//CCPXL = (1/5KHZ )/(1/12MHZ)x16) = 150 que representa el 100 % del ciclo de trabajo 
// vamos a dejar un duty cicle de 80%  = 120 en binario es 01111000 se corren 2 bits y queda  00011110

void main(void) {
    LATC = 0x00;
    ANSELC = 0x00;
    TRISCbits.RC2 = 1; //paso 1 
    //T2CON = 0b00000011 //se activa el timer 2 con un prescaler de 16
    PR2 = 0x24; //paso 2 PWM Periodo
    CCP1CON = 0b00001100; //paso 3 Pone el CCP como PWM 
    CCPR1L = 0b00011110; //paso 4 almancear el Duty cicle
    PIR1bits.TMR2IF = 0; //Desactivar la Interrupcion del registro PIR1   
    T2CONbits.T2CKPS = 1; //preescaler de 16 bits
    T2CONbits.TMR2ON = 1;//encender el Timer 2
    TRISCbits.RC2 = 0; //se pone como salida RC2 que es el pin del PWM
    while(1){
    }
    return;
}