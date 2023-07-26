/*
 * File:   main_lcd.c
 * Author: Miguel-Notebook
 *
 * Created on June 15, 2023, 11:00 PM
 */

#include "configuraciones.h"
#include "lcd.h"
#include <stdio.h>
#define _XTAL_FREQ 12000000

int v = 1023; //esta variable es de prueba para representarla en la LCD
float t = 24.32; //Esta variable es de prueba para representarla en la LCD
char buffer[20]; //Esta variable almacenara la conversion de los enteros y flotantoes a un char 


void InitPort(void){
    ANSELD = 0x00; //ponemos el portd como digital
}

void main(void){
    InitPort(); //llamamos la variable initPort
    Lcd_Init(); //Iniciailizamos el LCD
    Lcd_Clear(); //Limpiamos el LCD
    while(1){  //Iniciamos un Bucle
        TRISEbits.RE0 = 0;
        TRISEbits.RE1 = 1;
        TRISEbits.RE2 = 1;
        __delay_ms(500);
        TRISEbits.RE0 = 1;
        TRISEbits.RE1 = 0;
        TRISEbits.RE2 = 1;
        __delay_ms(500);
        TRISEbits.RE0 = 1;
        TRISEbits.RE1 = 1;
        TRISEbits.RE2 = 0;
        __delay_ms(500);
        Lcd_Set_Cursor(1,1);  //seteamos la posicion donde imprimiremos el mensaje
        Lcd_Write_String("Test LCD 16x2"); //imprimimos el mensaje
        Lcd_Set_Cursor(2,1);//seteamos la posicion donde imprimiremos el mensaje
        Lcd_Write_String("PIC18F45K50"); //imprimimos el mensaje
        Lcd_Set_Cursor(2,12); //dejamos el sensor en la siguiente posicion
        Lcd_Blink(); //habilitamos el parpadeo del sensor
        __delay_ms(2000);// retardo de 2 segundos
        Lcd_NoBlink(); //apagamos el parpadeo
        Lcd_Clear(); // limpiamos la lcd
        __delay_ms(400); //retarod de 0.4 seg
        
        Lcd_Set_Cursor(1,1); //seteamos la posicion donde imprimiremos el mensaje
        Lcd_Write_String("Hola a todos"); //imprimimos el mensaje
        __delay_ms(500); //Retardo de 0.5 seg
        for(char i=0; i<15; i++){  //cuando i  es igual a 0 y menor que 15 va aunmentar en uno en uno 
            Lcd_Shift_Right(); //activa el desplazamiento hacia la derecha
            __delay_ms(300); //retardo de  0.3 seg
        }
        __delay_ms(300); //retardo de 0.3 seg
        for(char i=0; i<15; i++){ //cuando i  es igual a 0 y menor que 15 va aunmentar en uno en uno 
            Lcd_Shift_Left(); //activa el desplzamiento hacia la izquierda
            __delay_ms(300); //retardo de 0.3 seg
        }
        Lcd_Clear(); //limpia el LCD
        __delay_ms(400); //retardo de 0.4 seg
        
        Lcd_Set_Cursor(1,1); //seteamos la posicion donde imprimiremos el mensaje
        sprintf(buffer, "Int: %u", v); //convertimos el int en char 
        Lcd_Write_String(buffer); // imprimimos el buffer 
        Lcd_Set_Cursor(2,1); //seteamos la posicion donde imprimiremos el mensaje
        sprintf(buffer, "Float: %0.2f", t); //convertimos el mensaje a char y asignamos solo 2 decimales
        Lcd_Write_String(buffer); //imprimimos el buffer
        __delay_ms(1500); //retardo de 1.5 seg
        Lcd_Clear(); //limpiamos el lcd
        __delay_ms(100); //reatardo de 0.1 seg 
    }   
    return;
}
