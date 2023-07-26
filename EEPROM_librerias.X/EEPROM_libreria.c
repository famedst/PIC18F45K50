/*
 * File:   EEPROM_libreria.c
 * Author: Miguel-Notebook
 *
 * Created on July 16, 2023, 5:13 PM
 */
#include <xc.h>

void EEPROM_Guardar(int dir, char data){
    EEADR = dir;  //Registo que asigna la direccion de los datos EEPROM para leer y escribir, estas son de 8 bits (00h a FFh o 256 bytes)
    EEDATA = data; //Mantiene los 8 bits de datos para leer y escribir
    EECON1bits.EEPGD = 0; //Acceder a la memoria EEPROM
    EECON1bits.CFGS = 0;  //Accede a la memoria EEPROM
    EECON1bits.WREN = 1; //Allows write cycles to Flash program/data EEPROM
    INTCONbits.GIE = 0; //Deshabilita las interrupciones Globales
    EECON2 = 0x55; //Secuencia Requerida cargar 0x55 a EECON2
    EECON2 = 0x0AA; //Secuencia Requerida cargar 0x0AA a EECON2
    EECON1bits.WR = 1;   //Inicializa la escritura
    INTCONbits.GIE = 1; //Habilita la Interrupciones Globales
    while(!PIR2bits.EEIF);//Mientras sea 0 que se quede esperando una vez que sea 1 salte de linea 
    PIR2bits.EEIF = 0;  //Pone la bandera en estado bajo 
    EECON1bits.WREN = 0;  //Apagando la escritura
}

unsigned char EEPROM_Lectura(int dir){
    EEADR = dir;
    EECON1bits.EEPGD = 0; //Acceder a la memoria EEPROM
    EECON1bits.CFGS = 0;  //Accede a la memoria EEPROM
    EECON1bits.RD = 1;   //Inicializa la lectura
    return EEDATA;
}