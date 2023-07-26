/*
 * File:   7segmain.c
 * Author: Miguel-Notebook
 *
 * Created on June 10, 2023, 10:45 PM
 */

#include "configuracion.h"
#include <xc.h>
#define _XTAL_FREQ 12000000
int i; //variable que ocuparemos como contador
unsigned char display[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67}; //datos para display catodo comun
//unsigned char display[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x83,0xB8,0x80,0x98}; //datos para Anodo comun

//La conexion es de RB0 = A RB1 = B  RB3 = C y asi consecutivamente

void InitPort(){
    
    LATA = 0x00; //Se inicializan en 0
    LATB = 0x00; //Se inicializan en 0
    LATC = 0x00; //Se inicializan en 0
    ANSELA = 0x00; //se declaran como puerto digital
    ANSELB = 0x00; //se declara como puerto digital
    ANSELC = 0x00; //se declara como puerto digital
    TRISA = 0x00; //se declaran como salidas
    TRISB = 0x00; //se declaran como salidas
    INTCON2bits.RBPU = 1; //puerto B desactivado el pull up
    TRISCbits.RC0 = 1; //se declara como entrada //UP
    TRISCbits.RC1 = 1; //se declara como entrada //DOWN
    
    
}

void main(void) {
    InitPort();
    while(1){
        if(PORTCbits.RC0 == 1){
            LATAbits.LA0 = 1;
            LATAbits.LA1 = 0;
            for(i=0;i<10;i++){  //para i es igual a 0 y menor que 10 va aumentar su valor en 1
                PORTB = display[i];
                __delay_ms(500);
            }
            PORTB = 0;
            LATAbits.LA0 = 0;
            LATAbits.LA1 = 0;
        }
        else if(PORTCbits.RC1 == 0){ //hay que poner la resistencia a PULL UP //Mi tarjeta me esta mandando un 1 en c1 perma por lo que cambio a que se active con 0 y pongo el bottom en PULL UP
            LATAbits.LA0 = 0;
            LATAbits.LA1 = 1;
            for(i=9;i>=0;i--){ // para i es igual a 9 y mayor o igual que 0 , va a disminuir su valor en 1
                PORTB = display[i];
                __delay_ms(500);
            }
            PORTB = 0;
            LATAbits.LA0 = 0;
            LATAbits.LA1 = 0;
        }
    }
    return;
}
