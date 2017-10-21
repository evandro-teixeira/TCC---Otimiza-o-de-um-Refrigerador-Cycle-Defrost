/*
 * LCD.h
 */
//#ifndef LCD_H_
//#define LCD_H_
//#endif /* LCD_H_ */
#include <hidef.h> 			/* for EnableInterrupts macro */
#include "derivative.h"		/* include peripheral declarations */
#include "externa.h"
#include "Timer.h"

typedef unsigned char byte;
#define REG_BASE 0x0000                /* Base address for the I/O register block */
/*
 * Definicões dos pinos do LCD 16x2
 */
/*
//PLACA NOVA
#define lcd_enable 	PTAD_PTAD4
#define lcd_rs 		PTAD_PTAD6
#define lcd_rw 		PTAD_PTAD5
#define lcd_d4 		PTAD_PTAD3
#define lcd_d5 		PTAD_PTAD2
#define lcd_d6 		PTAD_PTAD1
#define lcd_d7 		PTAD_PTAD0
*/
/*
 * Configura a direção pinos do LCD
 */
//PLACA NOVA
/*
#define lcd_enable_dir 	PTADD_PTADD4
#define lcd_rs_dir 		PTADD_PTADD6
#define lcd_rw_dir 		PTADD_PTADD5
#define lcd_d4_dir 		PTADD_PTADD3
#define lcd_d5_dir 		PTADD_PTADD2
#define lcd_d6_dir 		PTADD_PTADD1
#define lcd_d7_dir 		PTADD_PTADD0
*/
//PROTOTIPO

#define lcd_enable 	PTDD_PTDD5
#define lcd_rs 		PTDD_PTDD3
#define lcd_rw 		PTDD_PTDD4
#define lcd_d4 		PTED_PTED0
#define lcd_d5 		PTED_PTED1
#define lcd_d6 		PTED_PTED2
#define lcd_d7 		PTED_PTED3

#define lcd_enable_dir 	PTDDD_PTDDD5
#define lcd_rs_dir 		PTDDD_PTDDD3
#define lcd_rw_dir 		PTDDD_PTDDD4
#define lcd_d4_dir 		PTEDD_PTEDD0
#define lcd_d5_dir 		PTEDD_PTEDD1
#define lcd_d6_dir 		PTEDD_PTEDD2
#define lcd_d7_dir 		PTEDD_PTEDD3

/*
 * Definição do pino do backlight
 */
//#define lcd_backlight PTDD_PTDD7
/*
 * Configura direção do pino do backlight
 */
//#define lcd_backlight_dir PTDDD_PTDDD7//_PTDD7

#define lcd_seg_lin 0xC0    // Endereço da segunda linha na RAM do LCD

// Definições utilizadas para configuração do display
#define cursor_ligado      2
#define cursor_desligado   0
#define cursor_piscante    1
#define cursor_fixo        0
#define display_ligado     4
#define display_desligado  0
#define display_8x5        0
#define display_10x5       4
#define _2_linhas          8
#define _1_linha           0
/* 
 * Estados do backlight 
 */
//#define lcd_BACKLIGHT_ON   0
//#define lcd_BACKLIGHT_OFF  1
/* 
 * Definição de caracteres especiais (0 - 7) 
 */
//#define LCD_GRAU		      	0		// simbolo de grau (bolinha)
//#define LCD_SETA_ACIMA			1		// seta para acima
//#define LCD_SETA_ABAIXO			2		// seta para abaixo
//#define LCD_AUM       			3		// ã

/*static const char_t cgram[8][8]={      //unsigned char
{
0b01100,				// simbolo de grau (bolinha)
0b10010,
0b10010,
0b01100,
0b00000,
0b00000,                          
0b00000,             
0b00000,
},
{
0b00100,				// seta para acima 
0b01110,
0b11011,
0b01010,
0b01010,
0b01010,
0b01110,
0b00000,
},
{
0b01110,				// seta para baixo
0b01010,
0b01010,
0b01010,
0b11011,
0b01010,
0b00100,
0b00000,
},
{
0b01001,				// ã 
0b10110,
0b01110,
0b00001,
0b01111,
0b10001,
0b01111,
0b00000,
},
{
0b00000,				// simbolo 
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
},
{
0b00000,				// simbolo 
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
},
{
0b00000,				// simbolo 
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
},
{
0b00000,				// simbolo 
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
},
};
*/
/******************************************************************************
* Protótipos de funções
******************************************************************************/
void lcd_envia_nibble(char dado);
void lcd_envia_byte(char endereco, char dado );
void lcd_ini(char modo1, char modo2 );
void lcd_pos_xy(char x, char y);
void lcd_escreve_char(char c);
void lcd_escreve_string (char *c);
void lcd_liga_display(void);
void lcd_desliga_display(void);
void lcd_liga_cursor(void);
void lcd_desliga_cursor(void);
void lcd_liga_cursor_piscante(void);
void lcd_desliga_cursor_piscante(void);
void lcd_BackLight (unsigned int State);
void lcd_readbusy (void);
void lcd_limpa(void);
void lcd_limpa_2linha(void);
void delay (unsigned long int T);
//void delay (uint32_t T);
//void lcd_especial(char_t cod[7],int16_t end,char_t col,char_t lin);
//#endif  /* #ifndef lcd_H */

/***** Fim de arquivo ********************************************************/



