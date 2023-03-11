#include "FreeRTOSConfig.h"

#ifndef configGENERATE_RUN_TIME_STATS
	#define configGENERATE_RUN_TIME_STATS 0
#endif

#if(configGENERATE_RUN_TIME_STATS == 1)
#include "chip.h"



void vConfigureTimerForRunTimeStats( void ) {
	const unsigned long TCR_COUNT_RESET = 2, CTCR_CTM_TIMER = 0x00, TCR_COUNT_ENABLE = 0x01;

	/* This function configures a timer that is used as the time base when
	collecting run time statistical information - basically the percentage
	of CPU time that each task is utilising.  It is called automatically when
	the scheduler is started (assuming configGENERATE_RUN_TIME_STATS is set
	to 1). */

	/* Power up and feed the timer. */
	LPC_SYSCTL->PCONP |= 0x02UL;
	LPC_SYSCTL->PCLKSEL[0] = (LPC_SYSCTL->PCLKSEL[0] & (~(0x3<<2))) | (0x01 << 2);

	/* Reset Timer 0 */
	LPC_TIMER0->TCR = TCR_COUNT_RESET;

	/* Just count up. */
	LPC_TIMER0->CTCR = CTCR_CTM_TIMER;

	/* Prescale to a frequency that is good enough to get a decent resolution,
	but not too fast so as to overflow all the time. */
	LPC_TIMER0->PR =  ( configCPU_CLOCK_HZ / 10000UL ) - 1UL;

	/* Start the counter. */
	LPC_TIMER0->TCR = TCR_COUNT_ENABLE;
}
#else
void vConfigureTimerForRunTimeStats( void ) {}

#endif
