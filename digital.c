//Digital Audio Spectrum Analyzer
//by Michael F. Cloutier
//Started on 02/22/2014

#include <stdlib.h>
#include <stdio.h>
#include <htc.h>
//#include <dspic.h>
//#include <pic24fj64gb002.h>
#include <nvm_interface.h>

#define _XTAL_FREQ 64000000

//configuration bits
__CONFIG(1, JTAGEN_OFF & GCP_OFF & GWRP_OFF & ICS_PGx2 & FWDTEN_OFF & WINDIS_OFF & FWPSA_PR32 & WDTPS_PS8192);
__CONFIG(2, IESO_OFF & FNOSC_FRCPLL & OSCIOFNC_ON & POSCMOD_NONE & PLL96MHZ_ON & PLLDIV_NODIV & FCKSM_CSDCMD & IOL1WAY_OFF);
__CONFIG(3, WPFP_WPFP0 & SOSCSEL_IO & WUTSEL_FST & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM);
__CONFIG(4, DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_LPRC & DSBOREN_OFF & DSWDTEN_OFF);

void main(void)
{
	int i;

  	//set all pin functions to digital
	AD1PCFGL = 0xFFFF;
	TRISB = 0b0000000000000000;

	while (1)
	{
		RB7 = 1;
		__delay_ms(500);
		RB7 = 0;
		__delay_ms(500);
	}
}	
		

