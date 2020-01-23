#include <avr/io.h> 
#define F_CPU 10000000UL
#include <inttypes.h> 
#include <util/delay.h>

#define adc_port PINA 
#define rd PB0 
#define wr PB4 
#define cs PB2 
#define intr PB3

//ADC work
void convert(void); 
void read(void);
unsigned char adc_val;
//PWM work
void Initiate_PWM()
{  TCCR2|=(1<<WGM20)|(1<<WGM21)|(1<<COM21)|(1<<CS21);
	DDRB|=(1<<PB1);
}
void SetPWM_DutyCycle(uint8_t duty_cycle)
{
	OCR2=duty_cycle; //OC2 pin
}
void Wait()
{
	_delay_ms(4);
}
//LCD work
void _LCDClear(void);
void _LCDFuncSet(void);
void _LCD_DispCtrl(void);
void _LCDEntryMod(void);
void _PrintChar(char k);
void change_line(void);


int main(void) 
{

	DDRA=0b00000000; // set port A as input
	DDRB=0b00010111; // INTR as Input ,CS, WR & RD set as output 
	DDRD=0b11111111; //Port D set as output
	PORTA = 0x00; 
	
	uint8_t pwm=0;
    Initiate_PWM();
	while(1) 
{	
	convert();
	read();
	PORTD=adc_val;  //Output of adc
 	lcd_work();

    for(pwm=0;pwm<255;pwm++)
    {
		SetPWM_DutyCycle(pwm);
	    Wait();
	 }
	for(pwm=255;pwm>0;pwm--)
	{
		SetPWM_DutyCycle(pwm);
	    Wait();
	}

	}
}//main ends

void convert(void)
{
	PORTB=PORTB&(~(1<<cs)|(1<<wr)); // CS, WR are asserted
	_delay_ms(15);
	PORTB=PORTB|(1<<cs)|(1<<wr);
	while(PINB&(1<<intr));
}//convert ends
void read()
{
	PORTB=PORTB&(~((1<<cs)|(1<<rd)));
	adc_val=adc_port;
	PORTB=PORTB|((1<<cs)|(1<<rd));
}//read ends


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
		for (int j=0; j<15; j++)
		{
			_PrintChar(name[j]);
			_delay_ms(50);
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
			_delay_ms(50);
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

