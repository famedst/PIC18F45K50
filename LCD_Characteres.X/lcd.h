#include <xc.h>
#define _XTAL_FREQ 12000000

#define USE_CGRAM_LCD

#define RS LATDbits.LD5
#define EN LATDbits.LD4
#define D4 LATDbits.LD0
#define D5 LATDbits.LD1
#define D6 LATDbits.LD2
#define D7 LATDbits.LD3

#define RS_DIR TRISDbits.TRISD5
#define EN_DIR TRISDbits.TRISD4
#define D4_DIR TRISDbits.TRISD0
#define D5_DIR TRISDbits.TRISD1
#define D6_DIR TRISDbits.TRISD2
#define D7_DIR TRISDbits.TRISD3

void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear(void);
void Lcd_Set_Cursor(char a, char b);
void Lcd_Init(void);
void Lcd_Write_Char(char a);
void Lcd_Write_String(const char *a);
void Lcd_Shift_Right(void);
void Lcd_Shift_Left(void);
void Lcd_Blink(void);
void Lcd_NoBlink(void);

#ifdef USE_CGRAM_LCD
void Lcd_CGRAM_CreateChar(char add, const char* chardata);
void Lcd_CGRAM_Init(void);
void Lcd_CGRAM_Close(void);
#endif