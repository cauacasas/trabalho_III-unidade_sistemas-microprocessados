#include <msp430.h>

#define LED_BIT     BIT0
#define LDR_BIT     BIT5

void configLED(void);
void configADC10(void);

void main(void) {

    WDTCTL = WDTPW | WDTHOLD;

    __enable_interrupt();

    configLED();
    configADC10();

    ADC10CTL0 |= ENC + ADC10SC;

    while(1){
    }
}

void configLED(void){
    P1DIR |= LED_BIT;
    P1OUT &= ~LED_BIT;
}

void configADC10(void){
    ADC10AE0 |= BIT5;

    ADC10CTL1 |= INCH_5;
    ADC10CTL1 |= SHS_0;
    ADC10CTL1 |= ADC10DIV_7;
    ADC10CTL1 |= ADC10SSEL_0;
    ADC10CTL1 |= CONSEQ_2;

    ADC10CTL0 = SREF_0;
    ADC10CTL0 |= ADC10SHT_0;
    ADC10CTL0 |= MSC;
    ADC10CTL0 |= ADC10ON;
    ADC10CTL0 |= ADC10IE;
}

#pragma vector = ADC10_VECTOR
__interrupt void ADC10_ISR(void) {
    int resultado = ADC10MEM; // obtém o valor convertido
    if (resultado <= 0x0200){
        P1OUT |= LED_BIT; // Acende o LED
    }
    else{
        P1OUT &= ~LED_BIT; // Apaga o LED
    }
}
