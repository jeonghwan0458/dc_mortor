#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
void DC_Motor(int speed)
{
	if(speed< 0) speed= 0;
	if(speed>100) speed=100;
	OCR1A=speed;
}

int main(void)
{
	int arr[6] = {0,60,70,80,90,100};
	int i = 0;
	DDRB=0x60;
	DDRD=0xFF;
	DDRE=0x00;
	TCCR1A=0x82;
	TCCR1B=0x1A;
	OCR1A=0;
	OCR1B=0;
	ICR1=100;
	PORTD = 0b11111110;
	int speed = 0;
	while(1)
	{
		if((PINE&0x08) == 0x00){
			i = 0;
			speed = arr[i];
			_delay_ms(500);
			  
		}
		if((PINE&0x10) == 0x00){
			i++;
			if(i > 5){
				i = 5;
			}
			speed = arr[i];
			_delay_ms(500);
			
		}
		if((PINE&0x20) == 0x00){  
			i--;
			if(i < 0){
				i = 0;
			}
			speed = arr[i];
			
			_delay_ms(500);
			
		}
		
		switch(i){
			case 0 : PORTD = 0b11111110; break;
			case 1 : PORTD = 0b11111101; break;
			case 2 : PORTD = 0b11111011; break;
			case 3 : PORTD = 0b11110111; break;
			case 4 : PORTD = 0b11101111; break;
			case 5 : PORTD = 0b11011111; break;
			default: break;
		}
		DC_Motor(speed);
	}
}