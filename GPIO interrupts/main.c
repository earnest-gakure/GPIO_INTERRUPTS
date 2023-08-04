//When   sw1 and sw2 are pressed an interrupt occurs ,upon occuring the content of the interrupt is going to execute   

#include "TM4C123.h"                    // Device header
void delayMs (int delay);
int main (){
	SYSCTL->RCGCGPIO = 0x20 ; //clock for PORTF
	
	GPIOF->LOCK = 0x4C4F434B ;
	GPIOF->CR =0x01;
	GPIOF->DIR |= 0x0E ;
	GPIOF->DEN  |=0x1F ;
	GPIOF->PUR =0x11 ;
	 
	
	__disable_irq () ;  //disable interrupt
	GPIOF->IS &= ~0x11 ; //configure PF1 and PF0 falling edge trigger interrupt  ;i.e make them edge sensitive
	GPIOF->IBE  &= ~0x11 ;
	GPIOF->IEV &= ~ 0x11 ; // DETECT FALLING EDGE     
	GPIOF->ICR |= 0x11 ;   // CLEAR ANY PRIOR INTERRUPT
	GPIOF->IM |=0x11 ;    //unmask interrupt
	
	NVIC->IP [30] = 3<<5 ; //Set interrupt to priority 3
	NVIC->ISER [0] = 0x40000000 ; //Enable IRQ30
	__enable_irq ();
	while (1){
		//Toggle red LED
		GPIOF->DATA |= 0x02 ;
    delayMs(100	);	
		GPIOF->DATA &= ~0x02;
		delayMs(100);
		
	}
} 

void GPIOF_Handler (void)
{
	volatile int readback ;
	int i;
	//toggle green LED for 3 times
	for(i = 0 ; i < 3 ; i++){
		GPIOF->DATA &= ~0x02;
 		GPIOF->DATA |=0x08 ;
		delayMs(100);
		GPIOF->DATA &= ~0x08 ;
		delayMs(100);
		
	}
	GPIOF->ICR |= 0x11 ; //clear interrupt flag before return
	
	readback = GPIOF->ICR; //helps to force readback clear the interrupt
}
void delayMs (int delay){
	int i,j;
	for( i=0;i<delay;i++){
	  for ( j=0;j<3180;j++){
		}			
	}
}
