#include <stdlib.h>
#include <stdio.h>
#include <p24FJ64GB002.h>

#define _XTAL_FREQ 64000000

#define TEN    0b0000011110111111
#define NINE   0b0000001110111111
#define EIGHT  0b0000000110111111
#define SEVEN  0b0000000010111111
#define SIX    0b0000000000111111
#define FIVE   0b0000000000011111
#define FOUR   0b0000000000001111
#define THREE  0b0000000000000111
#define TWO    0b0000000000000011
#define ONE    0b0000000000000001
#define ZERO   0b0000000000000000

//configuration bits
_CONFIG1 (JTAGEN_OFF & GCP_OFF & GWRP_OFF & ICS_PGx2 & FWDTEN_OFF & WINDIS_OFF & FWPSA_PR32 & WDTPS_PS8192)
_CONFIG2 (IESO_OFF & FNOSC_FRCPLL & OSCIOFNC_ON & POSCMOD_NONE & PLL96MHZ_ON & PLLDIV_NODIV & FCKSM_CSDCMD & IOL1WAY_OFF)
_CONFIG3 (WPFP_WPFP0 & SOSCSEL_IO & WUTSEL_FST & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
_CONFIG4 (DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_LPRC & DSBOREN_OFF & DSWDTEN_OFF)

void display(int value)
{
	if (value == 0)
		PORTB = ZERO;
	else if (value == 1)
		PORTB = ONE;
	else if (value == 2)
		PORTB = TWO;
	else if (value == 3)
		PORTB = THREE;
	else if (value == 4)
		PORTB = FOUR;
	else if (value == 5)
		PORTB = FIVE;
	else if (value == 6)
		PORTB = SIX;
	else if (value == 7)
		PORTB = SEVEN;
	else if (value == 8)
		PORTB = EIGHT;
	else if (value == 9)
		PORTB = NINE;
	else if (value == 10)
		PORTB = TEN;
}

void setup_adc(void)
{
	AD1PCFG = 0xFFFE;
	//SSRC<2:0> = 111 implies internal counter ends sampling and starts converting.
	AD1CON1 = 0x00E0;
 	//set AN0 as S/H input.
	AD1CHS = 0x0000;
	AD1CSSL = 0;
 	//sample time = 31Tad, Tad = 3Tcy
	AD1CON3 = 0x1F02;
	AD1CON2 = 0;
 	//turn on ADC
	AD1CON1bits.ADON = 1;
}

void delay()
{
	int j;
	int k;

	for (j = 0; j < 1000; j++)
		for (k = 0; k < 1000; k++);
}

int main(void)
{
	int adc_value;
	float voltage;
	float bar_value;

	TRISB = 0b0000000000000000;	//all PORTB pins are outputs

	setup_adc();

	while (1) // repeat continuously
	{
		AD1CON1bits.SAMP = 1; // start sampling, then after 31Tad go to conversion
		while (!AD1CON1bits.DONE){}; // conversion done?
		adc_value = ADC1BUF0; // yes then get ADC value
		voltage = (adc_value / 1023.0) * 3.3;	//caculate voltage
		bar_value = (voltage / 3.3) * 10.0;		//calculate value to display on bar
		//round to nearest integer, display value on bar graph
		if (floor(bar_value) < (bar_value - 0.5))
			display(((int) bar_value) + 1);
		else
			display((int) bar_value);
		
	}

	//unreached
	return 0;
}