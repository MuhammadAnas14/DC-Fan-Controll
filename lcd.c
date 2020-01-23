#include <avr/io.h>
#define F_CPU 10000000UL
#include <util/delay.h>
void _LCDClear(void);
void _LCDFuncSet(void);
void _LCD_DispCtrl(void);
void _LCDEntryMod(void);

void _PrintChar(char k);

void change_line(void);

void lcd_work(void)
{
	DDRC = 0xFF;
	DDRE = 0xFF;
    /* Replace with your application code */
    while (1) 
    {
		_LCDClear();
		_LCDFuncSet();
		_LCD_DispCtrl();
		_LCDEntryMod();
		
		char name[16] = {' ','M','P','B','S',' ','P','R','O','J','E','C','T'};
		char roll[16] = {'8','8',' ','9','4',' ','9','2',' ','1','0','0',' '};
			for (int j=0; j<13; j++)
			{
				_PrintChar(name[j]);
				_delay_ms(100);
			}
			
			PORTC = 0xC0;
			
			PORTE = 0x00;
			_delay_ms(10);
			PORTE = 0x01;
			_delay_ms(5);
			PORTE = 0x00;
			
			for (int j=0; j<11; j++)
			{
				_PrintChar(roll[j]);
				_delay_ms(200);
			}
	
		    }

}

void _LCDClear(void){
	PORTC = 0x01;
	PORTE = 0x00;
	_delay_ms(10);
	PORTE = 0x01;
	_delay_ms(5);
	PORTE = 0x00;
}
void _LCDFuncSet(void){
	PORTC = 0x3B;
	PORTE = 0x00;
	_delay_ms(10);
	PORTE = 0x01;
	_delay_ms(5);
	PORTE = 0x00;
}
void _LCD_DispCtrl(void){
	PORTC = 0x0F;
	PORTE = 0x00;
	_delay_ms(10);
	PORTE = 0x01;
	_delay_ms(5);
	PORTE = 0x00;
}
void _LCDEntryMod(void){
	PORTC = 0x06;
	PORTE = 0x00;
	_delay_ms(10);
	PORTE = 0x01;
	_delay_ms(5);
	PORTE = 0x00;
}
void _PrintChar(char K){
	PORTC = K;
	PORTE = 0x0D;
	_delay_ms(5);

	PORTE = 0x0C;
}

