/*
 * File:   newmain.c
 * Author: Miguel-Notebook
 *
 * Created on June 7, 2023, 7:43 PM
 */

#include "configuracion.h"
#include <xc.h>
#include "pic18f45k50.h"
#define _XTAL_FREQ 12000000

long velocidad = 1;
char juego = 1;
void luces_uno(void);
void luces_dos(void);
void luces_tres(void);
void luces_cuatro(void);


void luces_uno(void){
    LATA = 0xAA;
    if(velocidad ==1){__delay_ms(1000);LATA = 0x00;__delay_ms(1000);}
    else if(velocidad ==2){__delay_ms(500);LATA = 0x00;__delay_ms(500);}
    else if(velocidad ==3){__delay_ms(250);LATA = 0x00;__delay_ms(250);}
    else if(velocidad ==4){__delay_ms(100);LATA = 0x00;__delay_ms(100);}
    if(PORTCbits.RC1 == 1){
        __delay_ms(20);
        velocidad = velocidad + 1;
        if(velocidad == 5)
        {velocidad =1;}
    }
}
void luces_dos(void){
    LATA = 0xFF;
    if(velocidad ==1){__delay_ms(1000);LATA = 0x00;__delay_ms(1000);}
    else if(velocidad ==2){__delay_ms(500);LATA = 0x00;__delay_ms(500);}
    else if(velocidad ==3){__delay_ms(250);LATA = 0x00;__delay_ms(250);}
    else if(velocidad ==4){__delay_ms(100);LATA = 0x00;__delay_ms(100);}
    if(PORTCbits.RC0 == 1){
        __delay_ms(20);
        velocidad = velocidad + 1;
        if(velocidad == 5)
        {velocidad =1;}
    }
}
void luces_tres(void){
    LATA = 0x66;
    if(velocidad ==1){__delay_ms(1000);LATA = 0x00;__delay_ms(1000);}
    else if(velocidad ==2){__delay_ms(500);LATA = 0x00;__delay_ms(500);}
    else if(velocidad ==3){__delay_ms(250);LATA = 0x00;__delay_ms(250);}
    else if(velocidad ==4){__delay_ms(100);LATA = 0x00;__delay_ms(100);}
    if(PORTCbits.RC0 == 1){
        __delay_ms(20);
        velocidad = velocidad + 1;
        if(velocidad == 5)
        {velocidad =1;}
    }
}

void luces_cuatro(void){
    LATA = 0x99;
    if(velocidad ==1){__delay_ms(1000);LATA = 0x00;__delay_ms(1000);}
    else if(velocidad ==2){__delay_ms(500);LATA = 0x00;__delay_ms(500);}
    else if(velocidad ==3){__delay_ms(250);LATA = 0x00;__delay_ms(250);}
    else if(velocidad ==4){__delay_ms(100);LATA = 0x00;__delay_ms(100);}
    if(PORTCbits.RC0 == 1){
        __delay_ms(20);
        velocidad = velocidad + 1;
        if(velocidad == 5)
        {velocidad =1;}
    }
}


void initPort(void){
    INTCON2bits.RBPU = 0; //Las resistencias PULL UP estan activadas 
    LATB = 0x00; //comienza en 0
    LATA = 0x00; //comienza en 0
    LATC = 0x00;
    ANSELB = 0x00; //se configuran los pines como digitales
    ANSELA = 0x00; //se configuran los pines como digitales
    ANSELC = 0x00; 
    TRISBbits.RB0 = 1; //es entrada
    TRISCbits.RC0 = 1; //es entrada
    TRISA = 0x00; //todos los pines como salidas
}

void main(void) {
    initPort();
    while(1){
        if(PORTBbits.RB0 == 0){ // =! diferente de , en esta caso de 1 //C0 esta conectado a pulldown
            __delay_ms(20);
            juego = juego + 1;
            if(juego == 5){
                juego = 1;}           
            //LATA = 0xFF; //Todo puerto B en alto
            //__delay_ms(500);           
        }
        switch(juego){
            case 1:
                luces_uno();
                break;
            case 2:
                luces_dos();
                break;   
            case 3:
                luces_tres();
                break;
            case 4:
                luces_cuatro();
                break;
        }      
    }   
    return;
}
