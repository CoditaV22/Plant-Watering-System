#include <mega164a.h>
#include <delay.h>
#include <alcd.h>
#include <stdlib.h>
#include <string.h>
#include <sleep.h>


        //TODO
        //1. Automatic watering
        
volatile int count = 0; 

//Timer2 ISR 
interrupt [TIM2_OVF] void timer2_ovf_isr(void)  
{   
    TCNT2=0x06;
    count ++;
}



void ADC_init()
{
    DDRA = 0x00;
    ADCSRA = 0b10000111; //Enable ADC | Freq/128
    ADMUX = 0b01000000;  //VREF = AVcc , pin 0
} 



int ADC_Read(int pin)
{
    ADMUX = (ADMUX & 0xF0) | (pin & 0x0F);  //selecting which ADC pin to use when reading data
    ADCSRA |= (1<<ADSC);  
    while ((ADCSRA &(1<<ADSC)));    
    return (ADCW);
}



void main(void)
{
char array[10];
int adc_value0 , adc_value1;
float moisture;
float water;

//Timer 2 initialization
ASSR=(0<<EXCLK) | (0<<AS2);
TCCR2A=(0<<COM2A1) | (0<<COM2A0) | (0<<COM2B1) | (0<<COM2B0) | (0<<WGM21) | (0<<WGM20);
TCCR2B=(0<<WGM22) | (1<<CS22) | (1<<CS21) | (1<<CS20);
TCNT2=0x06;
OCR2A=0x00;
OCR2B=0x00;

//Timer2 Overflow Interrupt 
TIMSK2=(0<<OCIE2B) | (0<<OCIE2A) | (1<<TOIE2);

lcd_init(16); 
lcd_clear();
ADC_init();


#asm("sei") //global enable interrupts


while (1)
      {  
        if(count >= 6000)  // 1 min has passed 
        { 
        
        sleep_disable();  
        delay_ms(300); //delay after waking up 
        
        
        
        
        
        
        
        /* Reading soil moisture */
        adc_value0 = ADC_Read(0);    // read ADC value
        moisture = 100-(adc_value0*100.00)/1023.00;  // Calculate moisture in %  (10 bit ADC so 1023 steps)
        lcd_gotoxy(0,0); // 1st row
        lcd_puts("Moisture: ");
        itoa(moisture,array);
        strcat(array,"%");    // add '%' at end of value
        lcd_puts(array);    // Print moisture value 
        
        
        
        
        
        
        
        /* Reading water level */ 
        adc_value1 = ADC_Read(1); // read ADC value 
        water = (adc_value1*100.00)/1023.00;;        
        lcd_gotoxy(0,1); // 2nd row
        lcd_puts("Water: ");
        
        
        
        
        
        
        /* Printing water instructions*/
        if(water > 64) //sensor fully immersed in water threshold
        {
            lcd_puts("GOOD");
        }
        else if(water > 58) //sensor partially immersed in water threshold
        {
            lcd_puts("OK");
        }
        else if(water > 50) //sensor barely immersed in water threshold
        {
            lcd_puts("FILL");
        }
        else                //sensor is dry threshold
        {
            lcd_puts("FILL NOW!");
        }
        
        
        delay_ms(2500); 
        lcd_clear();
        count = 0; //reset and prepare for another counter
        }
        
        
        else
        /* Power Saving Mode */
        { 
            sleep_enable(); 
            powersave();
        }
        
      
      
        
            
      }
}
