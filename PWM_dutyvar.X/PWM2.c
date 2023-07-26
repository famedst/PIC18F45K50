/*
 * File:   PWM2.c
 * Author: Miguel-Notebook
 *
 * Created on July 2, 2023, 10:00 PM
 */
#include "configuracion.h"
#include <xc.h>
#include <stdio.h>
#include <pic18f45k50.h>
#define _XTAL_FREQ 12000000

int duty_cicle;

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

void main(void){
    LATD = 0x00;// se inicializa en 0
    ANSELD = 0x00; //se declara como puerto digital
    PORTDbits.RD0 = 1;
    PORTDbits.RD1 = 1; //Ambos puertos como entrada
    LATC = 0x00;//se inicializa en 0
    ANSELC = 0x00;// se declara como puerto digital
    TRISCbits.RC2 = 1; //paso 1 
    //T2CON = 0b00000011 //se activa el timer 2 con un prescaler de 16
    PR2 = 0x24; //paso 2 PWM Periodo
    CCP1CON = 0b00001100; //paso 3 Pone el CCP como PWM 
    CCPR1L = 1; //paso 4 almancear el Duty cicle
    PIR1bits.TMR2IF = 0; //Desactivar la Interrupcion del registro PIR1   
    T2CONbits.T2CKPS = 1; //preescaler de 16 bits
    T2CONbits.TMR2ON = 1;//encender el Timer 2
    TRISCbits.RC2 = 0; //se pone como salida RC2 que es el pin del PWM
    while(1) {
        for (duty_cicle = 1; duty_cicle < PR2; duty_cicle++) {
            CCPR1L = duty_cicle;
            __delay_ms(20);
        }
        __delay_ms(500);

        for (duty_cicle = PR2; duty_cicle > 1; duty_cicle--) {
            CCPR1L = duty_cicle;
            __delay_ms(20);
        }
        __delay_ms(500);
//        if(PORTDbits.RD0 == 0){
//            duty_cicle = duty_cicle + 1;
//            if(duty_cicle = PR2){
//                duty_cicle = PR2 - 1;
//                }
//            CCPR1L = duty_cicle;
//            }
//        if(PORTDbits.RD1 == 0){
//            duty_cicle = duty_cicle - 1;
//            if(duty_cicle <= 1){
//                duty_cicle = 1;
//            }
//            CCPR1L = duty_cicle;
//        }
//        __delay_ms(50);
    }
    return;
}

