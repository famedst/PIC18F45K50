/*
 * File:   newmain.c
 * Author: Miguel-Notebook
 *
 * Created on June 5, 2023, 6:41 PM
 */


#include <xc.h>
#include "configuracion.h"
#include "pic18f45k50.h"
#define _XTAL_FREQ 4000000

void InitPort(){
    LATB = 0;
    LATA = 0;
    LATC = 0; 
    ANSELB = 0;
    ANSELA = 0;
    ANSELC = 0;
    TRISBbits.RB1 = 0; //PORTB = salida 0, 1 entrada
    TRISAbits.RA1 = 0; //PORTA = salida 0, 1 entrada
    TRISCbits.RC1 = 0; //PORTC = salida 0, 1 entrada
    //PORTCbits.RC0 = 1 //
}


void main(void) {
    InitPort();
    while(1){
        PORTBbits.RB1 = 1;
        PORTAbits.RA1 = 1;
        PORTCbits.RC1 = 1;
        __delay_ms(500);
        PORTBbits.RB1 = 0;
        PORTAbits.RA1 = 0;
        PORTCbits.RC1 = 0;
        __delay_ms(500); 
    }
    
    return;
}
