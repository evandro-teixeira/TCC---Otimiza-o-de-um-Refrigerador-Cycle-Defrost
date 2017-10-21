/********************************************************************************************************************
 * Controle_LCD.h
 *
 *  Created on: Aug 13, 2013
 *      Author: Evandro
#ifndef CONTROLE_LCD_H_
#define CONTROLE_LCD_H_
//#endif /* CONTROLE_LCD_H_ */
/*******************************************************************************************************************/
#include <hidef.h> 			/* for EnableInterrupts macro */
#include "derivative.h"		/* include peripheral declarations */
#include <stdio.h>
#include "types.h"
#include <math.h>
#include "define.h"
#include "externa.h"
#include "aplicacao.h"
#include "Timer.h"
#include "LCD.h"
#include "types.h"

void Atualiza_LCD(void);
void Tela_inicial(void);
