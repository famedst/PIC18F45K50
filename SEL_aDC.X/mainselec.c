/*
 * File:   mainselec.c
 * Author: Miguel-Notebook
 *
 * Created on July 8, 2023, 2:45 PM
 */

// PIC18F45K50 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLSEL = PLL4X   // PLL Selection (4x clock multiplier)
#pragma config CFGPLLEN = OFF   // PLL Enable Configuration bit (PLL Disabled (firmware controlled))
#pragma config CPUDIV = NOCLKDIV// CPU System Clock Postscaler (CPU uses system clock (no divide))
#pragma config LS48MHZ = SYS24X4// Low Speed USB mode with 48 MHz system clock (System clock at 24 MHz, USB clock divider is set to 4)

// CONFIG1H
#pragma config FOSC = HSM       // Oscillator Selection (HS oscillator, medium power 4MHz to 16MHz)
#pragma config PCLKEN = OFF     // Primary Oscillator Shutdown (Primary oscillator shutdown firmware controlled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config nPWRTEN = ON     // Power-up Timer Enable (Power up timer enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (BOR disabled in hardware (SBOREN is ignored))
#pragma config BORV = 190       // Brown-out Reset Voltage (BOR set to 1.9V nominal)
#pragma config nLPBOR = OFF     // Low-Power Brown-out Reset (Low-Power Brown-out Reset disabled)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (WDT disabled in hardware (SWDTEN ignored))
#pragma config WDTPS = 32768    // Watchdog Timer Postscaler (1:32768)

// CONFIG3H
#pragma config CCP2MX = RC1     // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)
#pragma config T3CMX = RC0      // Timer3 Clock Input MUX bit (T3CKI function is on RC0)
#pragma config SDOMX = RB3      // SDO Output MUX bit (SDO function is on RB3)
#pragma config MCLRE = ON       // Master Clear Reset Pin Enable (MCLR pin enabled; RE3 input disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port Enable (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Block 0 Code Protect (Block 0 is not code-protected)
#pragma config CP1 = OFF        // Block 1 Code Protect (Block 1 is not code-protected)
#pragma config CP2 = OFF        // Block 2 Code Protect (Block 2 is not code-protected)
#pragma config CP3 = OFF        // Block 3 Code Protect (Block 3 is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protect (Boot block is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protect (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Block 0 Write Protect (Block 0 (0800-1FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Block 1 Write Protect (Block 1 (2000-3FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Block 2 Write Protect (Block 2 (04000-5FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Block 3 Write Protect (Block 3 (06000-7FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Registers Write Protect (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protect (Boot block (0000-7FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protect (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Block 0 Table Read Protect (Block 0 is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Block 1 Table Read Protect (Block 1 is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Block 2 Table Read Protect (Block 2 is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Block 3 Table Read Protect (Block 3 is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protect (Boot block is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include "lcd.h"
#define _XTAL_FREQ 12000000
//adc de 10 bits
//voltaje de referencia 5v = 5/1024 = 4.8mV 1 bit

//= 12mhz =  1/12000000 = 83 ns = Tosc 
//TAD = 1.0 us minimo
//16Fosc = 83ns*16 = 1.3 us = TAD
//TACQ = 7.45us < xTAD
// 1.3us * 6 TAD = 7.8us > 7.45us que es el minimo que nos piden

#define VREF 5.0 //referencia de voltaje para la conversion

int v_adc; // resolucion del adc
float volt; //voltaje
char buffer[20]; // donde se almacenara la conversion

void InitPort(void){
    LATB = 0x00; //se incializa en 0
    ANSELB = 0x00; //se declara como puerto digital
    TRISB = 0xFF;//puerto B como entrada
    INTCON2bits.RBPU = 0; //puerto B activado el pull up
    
}

void set_adc(void){
    ANSELAbits.ANSA0 = 1; // se declara como puertos analogos
    TRISAbits.RA0 = 1;// se declara como entrada
    ADCON0 = 0x00;//AN0,GODONE = OFF,ADON = OFF 
    ADCON1 = 0x00; //CCP2=0,PVCFG = 00 internal signal AVdd , NVCFG = 00 internal signal AVss
    ADCON2 = 0b10011101; //ADFM = 1 justificado a la derecha, ACQT = 6 TAD, ADCS = Fosc/16
    ADCON0bits.ADON = 1; //se enciende el ADC
}
void set_adc1(void){
    ANSELAbits.ANSA1 = 1; // se declara como puertos analogos
    TRISAbits.RA1 = 1;// se declara como entrada
    ADCON0 = 0b00000100;//AN1,GODONE = OFF,ADON = OFF 
    ADCON1 = 0x00; //CCP2=0,PVCFG = 00 internal signal AVdd , NVCFG = 00 internal signal AVss
    ADCON2 = 0b10011101; //ADFM = 1 justificado a la derecha, ACQT = 6 TAD, ADCS = Fosc/16
    ADCON0bits.ADON = 1; //se enciende el ADC
}

void set_adc2(void){
    ANSELAbits.ANSA2 = 1; // se declara como puertos analogos
    TRISAbits.RA2 = 1;// se declara como entrada
    ADCON0 = 0b00001000;;//AN2,GODONE = OFF,ADON = OFF 
    ADCON1 = 0x00; //CCP2=0,PVCFG = 00 internal signal AVdd , NVCFG = 00 internal signal AVss
    ADCON2 = 0b10011101; //ADFM = 1 justificado a la derecha, ACQT = 6 TAD, ADCS = Fosc/16
    ADCON0bits.ADON = 1; //se enciende el ADC
}

void main(void){
        InitPort();
        Lcd_Init();//se inicializa el LCD
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("ADC0  BTN 0");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("ADC1 BTN 1");
        __delay_ms(500);
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("ADC2 BTN 2");
        __delay_ms(500);
        Lcd_Clear();
    if(PORTBbits.RB0 == 0){
        while(1){
        set_adc();
        ADCON0bits.GO_DONE = 1; // iniciamos la conversion 
        while(ADCON0bits.GO_DONE == 1);// Espera a que termine le conversion
        v_adc = (int)((ADRESH << 8) + ADRESL); // Almacena el resultado en 10 bits
        volt = (float)((v_adc*VREF)/1023.0); // Obtiene el valor del volaje
        Lcd_Set_Cursor(1,1); //Ponemos la posicion del LCD
        Lcd_Write_String("La Lectura: "); // escribimos los datos de la resolucion del ADC
        Lcd_Set_Cursor(2,1); //hacemos la conversion a char
        sprintf(buffer,"Voltaje %0.2f", volt); //hacemos la conversion del voltaje a char
        Lcd_Write_String(buffer);// escribimos los datos del voltaje en pantalla
        __delay_ms(100); //retardo de 200 ms
        }
    }
    else if(PORTBbits.RB1 == 0){
        while(1){
        set_adc1();
        ADCON0bits.GO_DONE = 1; // iniciamos la conversion 
        while(ADCON0bits.GO_DONE == 1);// Espera a que termine le conversion
        v_adc = (int)((ADRESH << 8) + ADRESL); // Almacena el resultado en 10 bits
        volt = (float)((v_adc*VREF)/1023.0); // Obtiene el valor del volaje
        Lcd_Set_Cursor(1,1); //Ponemos la posicion del LCD
        Lcd_Write_String("La Lectura: "); // escribimos los datos de la resolucion del ADC
        Lcd_Set_Cursor(2,1); //hacemos la conversion a char
        sprintf(buffer,"Voltaje %0.2f", volt); //hacemos la conversion del voltaje a char
        Lcd_Write_String(buffer);// escribimos los datos del voltaje en pantalla
        __delay_ms(100); //retardo de 200 ms
            }      
        }
    else if(PORTBbits.RB2 == 0){
        while(1){
        set_adc2();
        ADCON0bits.GO_DONE = 1; // iniciamos la conversion 
        while(ADCON0bits.GO_DONE == 1);// Espera a que termine le conversion
        v_adc = (int)((ADRESH << 8) + ADRESL); // Almacena el resultado en 10 bits
        volt = (float)((v_adc*VREF)/1023.0); // Obtiene el valor del volaje
        Lcd_Set_Cursor(1,1); //Ponemos la posicion del LCD
        Lcd_Write_String("La Lectura: "); // escribimos los datos de la resolucion del ADC
        Lcd_Set_Cursor(2,1); //hacemos la conversion a char
        sprintf(buffer,"Voltaje %0.2f", volt); //hacemos la conversion del voltaje a char
        Lcd_Write_String(buffer);// escribimos los datos del voltaje en pantalla
        __delay_ms(100); //retardo de 200 ms
            } 
        }
    }
    


