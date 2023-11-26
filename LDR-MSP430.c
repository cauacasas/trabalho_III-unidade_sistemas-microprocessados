#include <msp430.h>
 
unsigned int value = 0;
 
void ConfigureADC(void)
 
{
ADC10CTL1 = INCH_7 + ADC10DIV_0;
ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON + ADC10IE;
ADC10AE0 |= BIT7;
}
 
void ConfigurePins(void)
{
P1OUT = 0;
P1DIR |= BIT0;
}
 
void main(void) {
 
WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
 
BCSCTL1 = CALBC1_1MHZ;
 
DCOCTL = CALDCO_1MHZ;
 
ConfigurePins();
 
ConfigureADC();
 
while(1)
 
{
 
ADC10CTL0 |= ENC + ADC10SC;
 
__bis_SR_register(CPUOFF + GIE);
 
value = ADC10MEM;
 
if(value <= 511)
 
{
 
P1OUT |= BIT0; //turn ON the Light
 
}
 
else
 
{
 
P1OUT &= ~BIT0; //turn if OFF
 
}
 
}
 
}
 
#pragma vector = ADC10_VECTOR
 
__interrupt void ADC10_ISR(void)
 
{
 
__bic_SR_register_on_exit(CPUOFF);
 
}
