/*
 * Timer.c
 */
#include <hidef.h> 			/* for EnableInterrupts macro */
#include "derivative.h"		/* include peripheral declarations */
#include "externa.h"
#include "Timer.h"

/***************************************************************************************************
Função Delay com interrupção de 2 micro segundos
****************************************************************************************************/
void delay_us(unsigned long int t)
{
	number =  t;
	while(Flag_Overflow_TPM2 == 0)
	{}
	Flag_Overflow_TPM2		= FALSE;
}
//**************************************************************************************************
