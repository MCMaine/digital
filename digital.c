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
	AD1CON2 = 0b0000000000000010;
	
}

int main(void)
{
	int i;
	int j;
	int k;

  	//set all pin functions to digital
	AD1PCFGL = 0xFFFF;
	//OUTPUTS:	EVERYTHING ELSE
	TRISB = 0b0000000000000000;

	setup_adc();

	while (1)
	{
		for (i = 0; i < 11; i++)
		{
			//display the value on the LED bar graph
			display(i);
			//delay
			for (j = 0; j < 1000; j++)
				for (k = 0; k < 1000; k++);
		}
	}

	return 0;
}
