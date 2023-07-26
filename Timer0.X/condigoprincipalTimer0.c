/*
 * File:   condigoprincipal.c
 * Author: Miguel-Notebook
 *
 * Created on June 21, 2023, 11:56 PM
 */

#include "configuracion.h"
#include <xc.h>
#include <stdio.h>
#include "lcd.h"
#define _XTAL_FREQ 12000000

unsigned long carga = 35156;


void InitPort(void){
    ANSELC = 0x00; //Se declara como digital el puerto B
    ANSELA = 0x00; //Se declara como digital el Puerto B
    LATA = 0; //Se incializa en 1 el puerto A
    LATC = 0; //Se inicializa en 0 el puerto B
    TRISC = 1; //El puerto B va a ser entrada 
    TRISA = 0; //El puerto A va a a ser salida 
    //INTCON2bits.RBPU = 0; //puerto B activado el pull up
}

void Timer0(void){
    INTCONbits.GIE = 0; //se deshabilitan las interrupciones globales
    INTCONbits.TMR0IF = 0; //bandera de desbordamiento del Timer0, deshabilitada
    INTCONbits.TMR0IE = 1; //permite el desbordamiento del Timer0
    INTCONbits.PEIE = 1; //Habilita las interrupciones Externas
    INTCONbits.GIE = 1; //Habilita las Interrupciones Globales
    T0CONbits.T0CS = 0; //se habilida el reloj interno 
    T0CONbits.PSA = 0; //se habilita el preescaler
    T0CONbits.T0PS = 0b111; //se configura el valor del preescaler  de 1:256
    T0CONbits.T08BIT = 0; //Timer0 is configured as a 16-bit timer/counter
    T0CONbits.TMR0ON = 1; //se habilita el Timer 0
    
}



void main(void) {
    Lcd_Init();
    InitPort();
    Timer0();
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("TIEMPO");
    while(1){
        if(PORTCbits.RC0 == 1){
            __delay_ms(50);
            TMR0L = carga;
            TMR0H = (carga) >> 8;
            Lcd_Set_Cursor(2,5);
            Lcd_Write_String("3 segundo");
            LATAbits.LA0 = 1;   
        } 
    }
}

void __interrupt () ISR_timer0(void){
            if(INTCONbits.TMR0IF){
            Lcd_Set_Cursor(2,5);
            Lcd_Write_String("Terminado");
            INTCONbits.INT0IF = 0;
            LATAbits.LA0 = 0; 
        }  
      }


//La formula para generar el retardo en segundos con el timer es la siguiente
//Tiempo(s)*F.Oscilador / 4* El valor del preescaler )
// 3 * 12000000 / 4 * 256 = 35156 Asi quedaria en nuestro caso  