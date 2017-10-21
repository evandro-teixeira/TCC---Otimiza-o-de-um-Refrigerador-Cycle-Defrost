/*
 * Timer.h
 */
//******************************************************************************
//#ifndef TIMER_H_
//#define TIMER_H_
//#endif /* TIMER_H_ */
//******************************************************************************
#include <hidef.h> 			/* for EnableInterrupts macro */
#include "derivative.h"		/* include peripheral declarations */
#include "externa.h"
#include "define.h"
#include "types.h"
/*
 * Prototipo das funções 
 */
void delay_us(unsigned long int t);
