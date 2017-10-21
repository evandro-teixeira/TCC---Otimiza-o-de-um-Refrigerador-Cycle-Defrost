/*******************************************************************************************************************
 * Controle_LCD.c
 *      Author: Evandro
 ********************************************************************************************************************/
#include "Controle_LCD.h"
#include <stdio.h>
/*
#include "define.h"
#include "externa.h"
#include "aplicacao.h"
#include "Timer.h"
#include "LCD.h"
#include "types.h"
#include "Controle_LCD.h"*
*/

/*******************************************************************************************************************
* Função de controle de escrita do display LCD
********************************************************************************************************************/
void Atualiza_LCD(void)
{
	//uint8 estado_LCD  = 0;//= 1;
	//estado = st;
	switch(estado_LCD)
	{
		//primeira tela lcd
		case 1:
			//lcd_limpa();
			sprintf(LCD_LINHA_1,"  PROJETO  TCC  " );
			sprintf(LCD_LINHA_2,"  CYCLO DEFROST ");
			lcd_pos_xy(1,1); 
			lcd_escreve_string(LCD_LINHA_1);
			lcd_pos_xy(1,2);
			lcd_escreve_string(LCD_LINHA_2);
			//SET flag para iniciar contagem
			
			Flag_Start_Contador_LCD = TRUE;
			//Se ouver o estouro na contagem muda a msg do lcd
			if(Flag_Overflow_LCD == TRUE)
			{
				Flag_Overflow_LCD 	    = FALSE;
				estado_LCD 			    = 2; //muda para segunda tela LCD
			}
			
			//Se a chave um for precionda muda para SETUP 
			//Zera contador_lcd 
			if(Flag_ch1 == TRUE)
			{
				Flag_Start_Contador_LCD = FALSE;
				Flag_ch1 				= FALSE;
				estado_LCD 				= 3;
			}
			//Caso as outras chaves for precionada não deve ocorrer nenhuma alterção
			//zeras Flag das chaves
			if((Flag_ch2 == TRUE) || (Flag_ch3 == TRUE) || (Flag_ch4 == TRUE))
			{
				Flag_ch2 				= FALSE;
				Flag_ch3 				= FALSE;
				Flag_ch4 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
			}
		break;
		
		case 2:
			//lcd_limpa();
			sprintf(LCD_LINHA_1,"  PROJETO  TCC  ");
			sprintf(LCD_LINHA_2,"AD: %d Te: %d ",temp_mV,temperature);
			lcd_pos_xy(1,1); 
			lcd_escreve_string(LCD_LINHA_1);
			lcd_pos_xy(1,2);
			lcd_escreve_string(LCD_LINHA_2);
			//SET flag para iniciar contagem
			Flag_Start_Contador_LCD = TRUE;
			//Se ouver o estouro na contagem muda a msg do lcd
			if(Flag_Overflow_LCD == TRUE)
			{
				Flag_Overflow_LCD 		= FALSE;
				estado_LCD 			  	= 1;//muda para a primeira tela lcd
			}
			//Se a chave um for precionda muda para SETUP 
			//Zera contador_lcd 
			if(Flag_ch1 == TRUE)
			{
				Flag_Start_Contador_LCD = FALSE;
				Flag_ch1 				= FALSE;
				estado_LCD 				= 3;
			}
			//Caso as outras chaves for precionada não deve ocorrer nenhuma alterção
			//zeras Flag das chaves
			if((Flag_ch2 == TRUE) || (Flag_ch3 == TRUE) || (Flag_ch4 == TRUE))
			{
				Flag_ch2 				= FALSE;
				Flag_ch3 				= FALSE;
				Flag_ch4 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
			}			
		break;
		
		case 3:
			//lcd_limpa();
			sprintf(LCD_LINHA_1,"SETUP Termostato");
			sprintf(LCD_LINHA_2,"Posição: %d      ",posicao_termo);
			lcd_pos_xy(1,1); 
			lcd_escreve_string(LCD_LINHA_1);
			lcd_pos_xy(1,2);
			lcd_escreve_string(LCD_LINHA_2);
			//SET flag para iniciar contagem
			Flag_Start_Contador_LCD = TRUE;
            //Se ouver o estouro na contagem muda pra a primeira tela
			//Caso o usuario não precionar nenhuma tecla retorna para tela 1
			if(Flag_Overflow_LCD == TRUE)
			{
				Flag_Overflow_LCD 		= FALSE;
				estado_LCD 			    = 1;//muda para a primeira tela lcd
			}
			//incrementa a variavel "posicao_termo"
			if(Flag_ch2 == TRUE)
			{
				Flag_ch2 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
				posicao_termo++;
				if(posicao_termo >5)
				{
					posicao_termo = 5;
				}
			}
			//decrementa a variavel "posicao_termo"
			if(Flag_ch3 == TRUE)
			{
				Flag_ch3 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
				posicao_termo--;
				if(posicao_termo == 0)
				{
					posicao_termo = 1;
				}
			}
			//Salva Informação e retorna para a primeira tela
			if(Flag_ch4 == TRUE)
			{
				Flag_ch4 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
				estado_LCD   			= 1;
			}
			//neste estado a chave não realiza nada
			if(Flag_ch1 == TRUE)
			{
				Flag_ch1 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
				estado_LCD   			= 4;
			}
		break;
		
		case 4:
			sprintf(LCD_LINHA_1,"SETUP  BACKLIGHT");
			sprintf(LCD_LINHA_2,"RED             ");
			lcd_pos_xy(1,1); 
			lcd_escreve_string(LCD_LINHA_1);
			lcd_pos_xy(1,2);
			lcd_escreve_string(LCD_LINHA_2);
			//SET flag para iniciar contagem
			Flag_Start_Contador_LCD = TRUE;
			//Se ouver o estouro na contagem muda pra a primeira tela
			//Caso o usuario não precionar nenhuma tecla retorna para tela 1
			if(Flag_Overflow_LCD == TRUE)
			{
				Flag_Overflow_LCD 		= FALSE;
				estado_LCD 			  	= 1;//muda para a primeira tela lcd
			}
			//incrementa a variavel "posicao_termo"
			if(Flag_ch2 == TRUE)
			{
				Flag_ch2 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
				backlight++;
				estado_LCD++;
				//if(posicao_termo >5)
				if(backlight > 3)
				{
					//posicao_termo = 5;
					backlight = 3;
				}
				if(estado_LCD > 6)
				{
					estado_LCD = 6;
				}
			}
			//decrementa a variavel "posicao_termo"
			if(Flag_ch3 == TRUE)
			{
				Flag_ch3 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
				backlight--;
				estado_LCD--;
				if(backlight == 0)
				{
					backlight = 1;
				}
				if(estado_LCD < 4)
				{
					estado_LCD = 4;
				}
			}
			//Salva Informação e retorna para a primeira tela
			if(Flag_ch4 == TRUE)
			{
				Flag_ch4 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
				estado_LCD   = 1;
			}
			//neste estado a chave não realiza nada
			if(Flag_ch1 == TRUE)
			{
				Flag_ch1 = FALSE;
				//estado_LCD   = 5;
			}			
			BackLight(backlight);
		break;
		
		case 5:
			sprintf(LCD_LINHA_1,"SETUP  BACKLIGHT");
			sprintf(LCD_LINHA_2,"BLUE            ");
			lcd_pos_xy(1,1); 
			lcd_escreve_string(LCD_LINHA_1);
			lcd_pos_xy(1,2);
			lcd_escreve_string(LCD_LINHA_2);
			//SET flag para iniciar contagem
			Flag_Start_Contador_LCD = TRUE;
			//Se ouver o estouro na contagem muda pra a primeira tela
			//Caso o usuario não precionar nenhuma tecla retorna para tela 1
			if(Flag_Overflow_LCD == TRUE)
			{
				Flag_Overflow_LCD = FALSE;
				estado_LCD 			  = 1;//muda para a primeira tela lcd
			}
			//incrementa a variavel "posicao_termo"
			if(Flag_ch2 == TRUE)
			{
				Flag_ch2 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
				backlight++;
				estado_LCD++;
				//if(posicao_termo >5)
				if(backlight > 3)
				{
					//posicao_termo = 5;
					backlight = 3;
				}
				if(estado_LCD > 6)
				{
					estado_LCD = 6;
				}
			}
			//decrementa a variavel "posicao_termo"
			if(Flag_ch3 == TRUE)
			{
				Flag_ch3 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
				backlight--;
				estado_LCD--;
				if(backlight == 0)
				{
					backlight = 1;
				}
				if(estado_LCD < 4)
				{
					estado_LCD = 4;
				}
			}
			//Salva Informação e retorna para a primeira tela
			if(Flag_ch4 == TRUE)
			{
				Flag_ch4 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
				estado_LCD   = 1;
			}
			//neste estado a chave não realiza nada
			if(Flag_ch1 == TRUE)
			{
				Flag_ch1 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
				//estado_LCD   = 5;
			}			
			BackLight(backlight);
		break;
		
		case 6:
			sprintf(LCD_LINHA_1,"SETUP  BACKLIGHT");
			sprintf(LCD_LINHA_2,"GREEN           ");
			lcd_pos_xy(1,1); 
			lcd_escreve_string(LCD_LINHA_1);
			lcd_pos_xy(1,2);
			lcd_escreve_string(LCD_LINHA_2);
			//SET flag para iniciar contagem
			Flag_Start_Contador_LCD = TRUE;
			//Se ouver o estouro na contagem muda pra a primeira tela
			//Caso o usuario não precionar nenhuma tecla retorna para tela 1
			if(Flag_Overflow_LCD == TRUE)
			{
				Flag_Overflow_LCD = FALSE;
				estado_LCD 			  = 1;//muda para a primeira tela lcd
			}
			//incrementa a variavel "posicao_termo"
			if(Flag_ch2 == TRUE)
			{
				Flag_ch2 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
				backlight++;
				estado_LCD++;
				//if(posicao_termo >5)
				if(backlight > 3)
				{
					//posicao_termo = 5;
					backlight = 3;
				}
				if(estado_LCD > 6)
				{
					estado_LCD = 6;
				}
			}
			//decrementa a variavel "posicao_termo"
			if(Flag_ch3 == TRUE)
			{
				Flag_ch3 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
				backlight--;
				estado_LCD--;
				if(backlight == 0)
				{
					backlight = 1;
				}
				if(estado_LCD < 4)
				{
					estado_LCD = 4;
				}
			}
			//Salva Informação e retorna para a primeira tela
			if(Flag_ch4 == TRUE)
			{
				Flag_ch4 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
				estado_LCD   = 1;
			}
			//neste estado a chave não realiza nada
			if(Flag_ch1 == TRUE)
			{
				Flag_ch1 				= FALSE;
				Flag_Start_Contador_LCD = FALSE;
				//estado_LCD   = 5;
			}			
			BackLight(backlight);
		break;		
	}
}
/*
 * 
 */
void Tela_inicial(void)
{
	sprintf(LCD_LINHA_1,"  PROJETO  TCC  " );
	sprintf(LCD_LINHA_2,"  CYCLO DEFROST ");
	lcd_pos_xy(1,1); 
	lcd_escreve_string(LCD_LINHA_1);
	lcd_pos_xy(1,2);
	lcd_escreve_string(LCD_LINHA_2);
	//Liga backlight com fundo azul
	BACKLIGHT_BLUE = ON;
}
