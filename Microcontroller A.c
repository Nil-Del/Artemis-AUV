/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Advanced
Automatic Program Generator
© Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.


Project : 
Version : 
Date    : 4/13/2016
Author  :Niloofar Zendehdel
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
int joystick0=0;
int joystick1=0;
int joystick2=0;
int left=128;
int right=128;
char buff[8];
char LastM[2]={'0','0'};
void horizon (int joystick0, int joystick1);
void dive(int joystick2);
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
DDRB=0x08;

// Port C initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0x00;

// Port D initialization
// Func7=Out Func6=In Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=In 
// State7=0 State6=T State5=0 State4=0 State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0xB0;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 8 MHz
// Mode: Fast PWM top=0xFF
// OC0 output: Non-Inverted PWM
TCCR0=0x69;
TCNT0=0x00;
OCR0=128;


// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 8000.000 kHz
// Mode: Fast PWM top=0x00FF
// OC1A output: Non-Inv.
// OC1B output: Non-Inv.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0xA1;
TCCR1B=0x09;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=128;
OCR1BH=0x00;
OCR1BL=128;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 8000.000 kHz
// Mode: Fast PWM top=0xFF
// OC2 output: Non-Inverted PWM
ASSR=0x00;
TCCR2=0x69;
TCNT2=0x00;
OCR2=128;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=0x00;
MCUCSR=0x00;

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
// RS - PORTB Bit 0
// RD - PORTB Bit 1
// EN - PORTB Bit 2
// D4 - PORTB Bit 4
// D5 - PORTB Bit 5
// D6 - PORTB Bit 6
// D7 - PORTB Bit 7
// Characters/line: 16                      
lcd_init(16);

while (1)
      { 
      lcd_clear();
      joystick0=read_adc(0);
      joystick1=read_adc(1);
      joystick2=read_adc(2);

      horizon(joystick0, joystick1); 
      dive (joystick2);

      OCR1A=left;
      OCR1B=right;

      lcd_gotoxy(0,1);
      lcd_putsf("Heave:");
      lcd_gotoxy(0,0);
      lcd_putsf("Surge:");
      lcd_gotoxy(9,0); 
      itoa(OCR1A,buff);
      lcd_puts(buff);
      lcd_gotoxy(12,0);
      lcd_putchar(','); 
      lcd_gotoxy(13,0); 
      itoa(OCR1B,buff);
      lcd_puts(buff); 
      lcd_gotoxy(9,1);
      itoa(OCR2,buff);  
      lcd_puts(buff);
      lcd_gotoxy(12,1);
      lcd_putchar(',');
      lcd_gotoxy(13,1); 
      itoa(OCR0,buff);
      lcd_puts(buff);
      delay_ms(50);


      }
}
void horizon (int joystick0, int joystick1)
{     
      if (PINC.7==1)
      {
      left=128;
      right=128;
      LastM[0]='0';
      LastM[1]='0';
      }
      if (joystick0>600)
      {
        lcd_gotoxy(6,0);
        if (joystick1<400)
         {
            left+=2;
            right+=1;
            lcd_putsf("FR");
            LastM[1]='F';
            LastM[0]='R';  
            if (left>255)
                left=255;
            if (right>255)
                right=255;
         }
        else if (joystick1>600) 
         {
            right+=2;
            left+=1; 
            lcd_putsf("FL"); 
            LastM[1]='F';
            LastM[0]='L';  
            if (left>255)
                left=255;
            if (right>255)
                right=255;
         }
        else
         {                   
            lcd_putchar('F'); 
            LastM[1]='F';   
            LastM[0]='0';
            if(left >= 255)
                left=255;  
            if(right >= 255)
                right=255;
            if(left==right)
                {
            if (left < 255) 
            {
                left+=1; 
                right+=1;
            }
        } 
            else if(left!=right)
                {  
            if(left<128 || right<128)
            { 
                right=128;
                left=128;
            }
            else
            {
                 if(left>right)
                 {
                     left=right;
                 }
                 else if(left<right)
                 { 
                    right=left;
                 }
            } 
        }
         }
      }
      else if (joystick0<400)
      {
        lcd_gotoxy(6,0);
        if (joystick1<400)
         {
            left-=2;
            right-=1;
            lcd_putsf("BR");  
            LastM[1]='B';
            LastM[0]='R'; 
            if (left<0)
                left=0;
            if (right<0)
                right=0;
         }
        else if (joystick1>600) 
         {
            right-=2;
            left-=1; 
            lcd_putsf("BL");
            LastM[1]='B';
            LastM[0]='L';   
            if (left<0)
                left=0;
            if (right<0)
                right=0;
         }               
        else        
        {
         lcd_putsf("B"); 
         LastM[1]='B'; 
         LastM[0]='0';
         if(left <= 0)
            left=0; 
         if(right <= 0)
            right=0;
         if(right==left)
          { 
            if(left > 0) 
            {
                left-=1;  
                right-=1; 
            }
          }           
         else if(left!=right)
          {  
            if(right>128 || left>128)
             {
                right=128;
                left=128;
             }
            else
            {
                if(left>right)
                    right=left;
                else if (left<right)
                    left=right;
            }                                                                              
          } 
       }
       }
      else 
      {
         if (joystick1>600)
           {
             lcd_gotoxy(4,0);
             lcd_putsf("L");
             LastM[1]='0';
             LastM[0]='L';   
             if (right >= 255)
                 right=255; 
             else if(right < 255)
                 right+=1; 
             if(left <= 0)
                 left=0;
             else if(left > 0)
                 left-=1;
           }
         else if (joystick1<400)
           {
             lcd_gotoxy(4,0);
             lcd_putsf("R"); 
             LastM[1]='0';
             LastM[0]='R'; 
             if(left >= 255)
                left=255;
             else if(left < 255)
                left+=1;
             if(right <= 0)
                right=0;
            else if(right > 0)
                right-=1;
           }       
         else if (LastM[1]=='0')
           {
            right=128;
            left=128;  
            LastM[0]='0';
          } 
         else if (LastM[1]!='0')
           {
            if (LastM[1]=='F')
             {
                if(left>right)
                     left=right;
                else if(left<right)
                    right=left;
             }
            else if (LastM[1]=='B')
             {
                if(left>right)
                    right=left;
                else if (left<right)
                    left=right;
             }
                              
           }
      } 

}
void dive(int joystick2)
{
    if (joystick2>600)
      {
       lcd_gotoxy(6,1);
       lcd_putsf("D"); 
       if (OCR2>=254)
       {
        OCR2=255;
        OCR0=255;
       } 
       else
       {
        OCR2+=1;
        OCR0+=1;  
       }
      }
      else if (joystick2<400)
      {
       lcd_gotoxy(6,1);
       lcd_putsf("U");
       if (OCR2<=1)
        {
            OCR2=0; 
            OCR0=0;
        }
       else
        {
            OCR2-=1; 
            OCR0-=1; 
        } 
       
      } 
      else
      {
        OCR2=128;
        OCR0=128;
      }

}