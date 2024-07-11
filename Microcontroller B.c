/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Advanced
Automatic Program Generator
© Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.


Project : 
Version : 
Date    : 5/15/2019
Author  : Niloofar Zendehdel
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega16.h>
#include <stdlib.h>
#include <delay.h>

// Alphanumeric LCD Module functions
#include <alcd.h>

int data=0;
// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
delay_ms(20);

PORTB.0=1;
PORTB.1=0;
PORTB.3=0;
PORTB.4=0;
#asm ("nop")
if( PIND.2==1)
  {
   lcd_gotoxy(13,0);
   lcd_putsf("OK"); 
   if (data>180) 
    {
      OCR1A=1200;
    }
   else
    {  
      OCR1A=data*5+300;
    }
   delay_ms(1000);
  }
else 
  {
    PORTB.0=0;
    PORTB.1=1;
    PORTB.3=0;
    PORTB.4=0;
    #asm ("nop")
    if( PIND.2==1)
      {
       data=data*10+9;
       //lcd_putchar('9'); 
       #asm ("nop")
       delay_ms(100);
      }
    else 
      {
       PORTB.0=0;
       PORTB.1=0;
       PORTB.3=1;
       PORTB.4=0;
       #asm ("nop")
       if(PIND.2==1)
        {
         data=data*10+6;
         //lcd_putchar('6');   
         #asm ("nop")
         delay_ms(100);
        }  
        else
        {
         PORTB.0=0;
         PORTB.1=0;
         PORTB.3=0;
         PORTB.4=1;
         #asm ("nop")
         if(PIND.2==1)
          {
           data=data*10+3;    
           #asm ("nop")
           delay_ms(100);
          //lcd_putchar('3');
         } 
        }
      }
  }
delay_ms(100);
#asm ("nop")
/*
PORTB=0x1B;
PORTD=0xF3;
*/
PORTB.0=1;
PORTB.1=1;
PORTB.3=1;
PORTB.4=1;

}

// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
delay_ms(20);
lcd_gotoxy(13,0);
PORTB.0=1;
PORTB.1=0;
PORTB.3=0;
PORTB.4=0;
#asm ("nop")
if( PIND.3==1)
{
   data=data*10+0;
   //lcd_putchar('0');   
   #asm ("nop")
   delay_ms(100);
}
else
{
  PORTB.0=0;
  PORTB.1=1;
  PORTB.3=0;
  PORTB.4=0;
  #asm ("nop")
  if( PIND.3==1)
  {
   data=data*10+8;
   //lcd_putchar('8'); 
   #asm ("nop")
   delay_ms(100);
  }
  else
  {
   PORTB.0=0;
   PORTB.1=0;
   PORTB.3=1;
   PORTB.4=0;
   #asm ("nop")
   if( PIND.3==1)
    {
     data=data*10+5;
     //lcd_putchar('5'); 
     #asm ("nop")
     delay_ms(100);
    }
    else
    {
     PORTB.0=0;
     PORTB.1=0;
     PORTB.3=0;
     PORTB.4=1;
     #asm ("nop")
     if( PIND.3==1)
     {
      data=data*10+2;
      //lcd_putchar('2');      
      #asm ("nop")
      delay_ms(100);
     }
    }
  }
}
delay_ms(100);
#asm("nop")
PORTB.0=1;
PORTB.1=1;
PORTB.3=1;
PORTB.4=1;

}

// External Interrupt 2 service routine
interrupt [EXT_INT2] void ext_int2_isr(void)
{
delay_ms(20);
lcd_gotoxy(13,0);
PORTB.0=1;
PORTB.1=0;
PORTB.3=0;
PORTB.4=0;
#asm ("nop")
if( PINB.2==1)
{
  data=0;
  //lcd_putchar('e'); 
  #asm ("nop")
  delay_ms(100);
}
else
{
  PORTB.0=0;
  PORTB.1=1;
  PORTB.3=0;
  PORTB.4=0;
  #asm ("nop")
  if( PINB.2==1)
  {
   data=data*10+7;
   //lcd_putchar('7');   
   #asm ("nop")
   delay_ms(100);
  }
  else
  {
   PORTB.0=0;
   PORTB.1=0;
   PORTB.3=1;
   PORTB.4=0;
   #asm ("nop")
   if( PINB.2==1)
    {
     data=data*10+4;
     //lcd_putchar('4'); 
     #asm ("nop")
     delay_ms(100);
    }
    else
    {
     PORTB.0=0;
     PORTB.1=0;
     PORTB.3=1;
     PORTB.4=1;
     #asm ("nop")
     if( PINB.2==1)
     {
      data=data*10+1;
      //lcd_putchar('1'); 
      #asm ("nop")
      delay_ms(100);
     }
    }
  }
}
delay_ms(100);
#asm("nop")
PORTB.0=1;
PORTB.1=1;
PORTB.3=1;
PORTB.4=1;


}

#define ADC_VREF_TYPE 0x00

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}

// Declare your global variables here
int joystick0=512;
int joystick1=512;
int joystick2=512;
char buff[32];
int deg1=0;
int deg2=0;
void pan(int joystick2);
void tilt(int joystick0);
void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0x00;

// Port C initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x30;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 8000.000 kHz
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off

TCCR1A=0xA0;
TCCR1B=0x12;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x27;
ICR1L=0x0F;
OCR1A=300;
OCR1B=300;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Rising Edge
// INT1: On
// INT1 Mode: Rising Edge
// INT2: On
// INT2 Mode: Rising Edge
GICR|=0xE0;
MCUCR=0x0F;
MCUCSR=0x40;
GIFR=0xE0;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// USART initialization
// USART disabled
UCSRB=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC Clock frequency: 1000.000 kHz
// ADC Voltage Reference: AREF pin
// ADC Auto Trigger Source: ADC Stopped
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x83;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;

// Alphanumeric LCD initialization
// Connections specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTC Bit 0
// RD - PORTC Bit 1
// EN - PORTC Bit 2
// D4 - PORTC Bit 4
// D5 - PORTC Bit 5
// D6 - PORTC Bit 6
// D7 - PORTC Bit 7
// Characters/line: 8
lcd_init(16);

// Global enable interrupts
#asm("sei")
DDRB.0=1;
DDRB.1=1;
DDRB.3=1;
DDRB.4=1;
PORTB.0=1;
PORTB.1=1;
PORTB.3=1;
PORTB.4=1;
while (1)
      { 
        joystick0=read_adc(0);
        joystick1=read_adc(1);
        joystick2=read_adc(2);
        
        lcd_clear();
        lcd_gotoxy(0,0);
        lcd_putsf("P:");
        
        if (OCR1A>300)
            deg1=(OCR1A-300)/5; 
        else
            deg1=0;
        
        lcd_gotoxy(4,0);
        itoa(deg1,buff);
        lcd_puts(buff);
        
        lcd_gotoxy(0,1); 
        lcd_putsf("T:");
        if (OCR1B>300)
            deg2=(OCR1B-300)/5;
        else
            deg2=0;
        lcd_gotoxy(4,1);
        itoa(deg2,buff);
        lcd_puts(buff);
        
        lcd_gotoxy(9,0);
        lcd_putsf("New:");
        lcd_gotoxy(13,0);
        itoa(data,buff);
        lcd_puts(buff);
        

        pan(joystick2);
        tilt(joystick0); 
        
        delay_ms(20);

      }
}
void pan(int joystick2)
{
    if (joystick2>600)
      {
       lcd_gotoxy(2,0); 
       lcd_putsf("L,"); 
       if (OCR1A>=1200) 
        {
            OCR1A=1200; 
            delay_ms(100);
        } 
       else
        {    
            OCR1A+=1;
            //delay_ms(20); 
        } 
      }
    else if (joystick2<400)
      {
       lcd_gotoxy(2,0); 
       lcd_putsf("R,");  
       if (OCR1A<=300) 
        {
            OCR1A=300;
            delay_ms(100);
        }  
       else
        {
            OCR1A-=1;
            //delay_ms(20); 
        }
      }  
}
void tilt(int joystick0)
{
    if (joystick0>600)
      { 
       lcd_gotoxy(2,1); 
       lcd_putsf("D,");  
       if (OCR1B>=1200) 
        {
            OCR1B=1200;
            delay_ms(100);
        } 
       else
        {    
            OCR1B+=1;
            //delay_ms(20); 
        } 
      }
    else if (joystick0<400)
      { 
       lcd_gotoxy(2,1); 
       lcd_putsf("U,"); 
       if (OCR1B<=300) 
        {
            OCR1B=300;
            delay_ms(100);
        }  
       else
        {
            OCR1B-=1;
            //delay_ms(20); 
        }
      }  
}