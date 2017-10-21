/*
 * LCD.c
 */
#include <hidef.h> 			/* for EnableInterrupts macro */
#include "derivative.h"		/* include peripheral declarations */
#include "externa.h"
#include "LCD.h"
#include "Timer.h"


// vari�vel global que armazena o configura��o do display
static char modo_lcd2;	// vari�vel global que armazena o configura��o do display
union ubyte
{
	char _byte;
	struct
	{
		char b0 : 1;                         
		char b1 : 1;
		char b2 : 1;
		char b3 : 1;
		char b4 : 1;
		char b5 : 1;
		char b6 : 1;
		char b7 : 1;
	} bit;
}; 

//**************************************************************************
//* Fun��o de envio de um nibble para o display
//**************************************************************************
//* Argumentos de chamada:
//* char dado : dado a ser enviado para o display (somente o nibble inferior)
//**************************************************************************
//* Retorno : nada
//**************************************************************************
void lcd_envia_nibble(char dado)
{
	union ubyte teste;
	teste._byte = dado;
    //coloca os quatro bits nas saidas
    
	lcd_d4 = teste.bit.b0;
	lcd_d5 = teste.bit.b1;
	lcd_d6 = teste.bit.b2;
	lcd_d7 = teste.bit.b3;
   
	//pulsa a linha enable
	
	lcd_enable = 1;
	//delay_10xuwait(1);
	delay_us(5);//Fun��o delay de 2us - tempo 10us 
	lcd_enable = 0;
	
}
//**************************************************************************
//* Fun��o de escrita de 1 byte no display
//**************************************************************************
//* Argumentos de chamada:
//* char endereco : 0 se instru��o, 1 se dado
//* char dado : dado ou comando a ser escrito
//**************************************************************************
//* Retorno : nada
//**************************************************************************
void lcd_envia_byte( char endereco, char dado )
{
	lcd_rw=0;
	// coloca a linha rs em 0
	// lcd_rs=0;
	// configura a linha rs dependendo do modo selecionado
	lcd_rs = endereco;
    //if(endereco) { lcd_rs_HIGH;} else lcd_rs_LOW;
	delay_us(15);
 	// desativa linha enable
	lcd_enable=0; 
	// envia a primeira parte do byte
	lcd_envia_nibble(dado >> 4);
	// envia a segunda parte do byte
	lcd_envia_nibble(dado & 0x0f);
	delay_us(35);
}
//**************************************************************************
//* Fun��o de inicializa��o do display
//**************************************************************************
//* Argumentos de chamada:
//* char modo1 : modo do display (n�mero de linhas e tamanho dos caracteres
//* char modo2 : modo do display (estado do cursor e do display)
//**************************************************************************
//* Retorno : nada
//**************************************************************************
void lcd_ini(char modo1, char modo2)
{
  char conta;
  // configura os pinos como sa�das
  lcd_enable_dir = 1;
  lcd_rs_dir = 1;
  lcd_rw_dir = 1;
  lcd_d4_dir = 1;
  lcd_d5_dir = 1;
  lcd_d6_dir = 1;
  lcd_d7_dir = 1;
  // coloca os pinos em n�vel l�gico 0
  lcd_d4 = 0;
  lcd_d5 = 0;
  lcd_d6 = 0;
  lcd_d7 = 0;
  lcd_rs = 0;
  lcd_rw = 0;
  lcd_enable = 0;

  lcd_rs = 0;
  lcd_rw = 0;
  
  //delay100US(500);  
  delay_us(25000);
  lcd_envia_nibble(0x03);
  //delay100US(50);    
  delay_us(25000);
  lcd_envia_nibble(0x03);
  //delay100US(50);
  delay_us(2500);
  lcd_envia_nibble(0x03);
  //delay100US(50);
  delay_us(2500);
  lcd_envia_nibble(0x02);
  //delay100US(30);
  delay_us(1500);
  // envia c�digos de inicializa��o do display
  lcd_envia_byte(0,0x20 | modo1);
  //delay100US(30);
  delay_us(1500);
  lcd_envia_byte(0,0x08 | modo2);          
  //delay100US(30);
  delay_us(1500);
  modo_lcd2 = 0x08 | modo2;
  //delay100US(30);
  delay_us(1500);
  lcd_envia_byte(0,1);                                
  //delay100US(30);
  delay_us(1500);
  lcd_envia_byte(0,6);           
  //delay100US(30);    //15
  delay_us(1500);
}              
//**************************************************************************
//* Fun��o de posicionamento do cursor do display
//**************************************************************************
//* Argumentos de chamada:
//* char x : coluna a ser posicionado o cursor (iniciando de 1)
//* char y : linha a ser posicionado o cursor (1 ou 2)
//**************************************************************************
//* Retorno : nada
//**************************************************************************
void lcd_pos_xy(char x, char y)
{
	char endereco;
	//delay(1);  //20
	if(y!=1)
	{
		endereco = lcd_seg_lin;
	}
	else
	{	
		endereco = 0; 
	}

	endereco += x-1;
	endereco |= 0x80;
	lcd_envia_byte(0,endereco);
}

//**************************************************************************
//* Fun��o de escrita de um caractere no display
//**************************************************************************
//* Argumentos de chamada :
//* char c : caractere a ser escrito
//**************************************************************************
//* Retorno : nada
//**************************************************************************
//* Observa��es :
//*	\f apaga o conte�do do display
//* \n e \r retornam o cursor para a primeira coluna da segunda linha
//**************************************************************************
void lcd_escreve_char(char c)
// envia um caractere para o display
{
	//lcd_rw = 0;
	switch (c)
	{
		case '\f' : lcd_envia_byte(0,1);
		//delay(15);
		delay_us(750);
		break;

		case '\n' :
		case '\r' : lcd_pos_xy(1,2);
		break;

		default : lcd_envia_byte(1,c);
  }
}
//**************************************************************************
//* Fun��o lcd_limpa();
//**************************************************************************
//* Argumentos de chamada :  limpa display 
//* Retorno : nada
//**************************************************************************
void lcd_limpa(void)
{
	//delay(1);
	lcd_pos_xy(1,1);
	lcd_escreve_string ("                    ");
	//delay(1);
	lcd_pos_xy(1,2);
	lcd_escreve_string ("                    ");
	//delay(1);
}

//**************************************************************************
//* Fun��o lcd_limpa_2linha();
//**************************************************************************
//* Argumentos de chamada :  limpa 2 linha do display 
//* Retorno : nada
//**************************************************************************
void lcd_limpa_2linha(void)
{
   lcd_pos_xy(1,2);
   lcd_escreve_string ("                    ");
 
}
//**************************************************************************
//* Fun��o de escrita de uma string no display
//**************************************************************************
//* Argumentos de chamada:
//* char *c : um ponteiro para um caractere
//**************************************************************************
//* Retorno : nada
//**************************************************************************
void lcd_escreve_string (char *c)
{
	while (*c)
	{
        //delay(2);
		lcd_escreve_char(*c);
		c++;
		//delay(1);		
		
		/*
		if (lcd_readbusy());
		else lcd_readbusy();
		*/
	}
}

//**************************************************************************
//* Fun��o para ativar o display
//**************************************************************************
//* Argumentos de chamada : nenhum
//* Retorno : nada
//**************************************************************************
void lcd_liga_display(void)
{
	modo_lcd2 |= 4;
	lcd_envia_byte (0,modo_lcd2);
}

//**************************************************************************
//* Fun��o para desativar o display
//**************************************************************************
//* Argumentos de chamada : nenhum
//* Retorno : nada
//**************************************************************************
void lcd_desliga_display(void)
{
	modo_lcd2 &= 0b11111011;
	lcd_envia_byte (0,modo_lcd2);
}

//**************************************************************************
//* Fun��o para ativar o cursor
//**************************************************************************
//* Argumentos de chamada : nenhum
//* Retorno : nada
//**************************************************************************
void lcd_liga_cursor(void)
{
	modo_lcd2 |= 2;
	lcd_envia_byte (0,modo_lcd2);
}

//**************************************************************************
//* Fun��o para desativar o cursor
//**************************************************************************
//* Argumentos de chamada : nenhum
//* Retorno : nada
//**************************************************************************
void lcd_desliga_cursor(void)
{
	modo_lcd2 &= 0b11111101;
	lcd_envia_byte (0,modo_lcd2);
}

//**************************************************************************
//* Fun��o para ativar o cursor piscante
//**************************************************************************
//* Argumentos de chamada : nenhum
//* Retorno : nada
//**************************************************************************
void lcd_liga_cursor_piscante(void)
{
	modo_lcd2 |= 1;
	lcd_envia_byte (0,modo_lcd2);
}

//**************************************************************************
//* Fun��o para desativar o cursor piscante
//**************************************************************************
//* Argumentos de chamada : nenhum
//* Retorno : nada
//**************************************************************************
void lcd_desliga_cursor_piscante(void)
{
	modo_lcd2 &= 0b11111110;
	lcd_envia_byte (0,modo_lcd2);
}
//**************************************************************************
//* Fun��o para ligar ou desativar o Backlight
//**************************************************************************
//* Argumentos de chamada :  state 
//* Retorno : nada
//**************************************************************************
void lcd_BackLight (unsigned int State)
{  
  /* DDRK   |= (uint8_t) 0x10;                                        
  /* Configure o registro de sa�da de controle do backlight */
  /*if (lcd_BACKLIGHT_OFF == State)
  {
    PORTK |= 0x10;
  } else 
  {
    PORTK &= 0xEF;
  }
  */
  /* lcd_BackLight (uint16_t State) */
/*  lcd_backlight_dir = 1;
  if(State == lcd_BACKLIGHT_ON){
	lcd_backlight = 1;
  }
  else if(State == lcd_BACKLIGHT_ON){
	lcd_backlight = 0;
  }	*/
	return;
}
//**************************************************************************
//* Fun��o readbusy
//**************************************************************************
//* Argumentos de chamada :  status display 
//* Retorno : 1- ok     0- busy
//**************************************************************************                                   
void lcd_readbusy (void)
{
  volatile char busy_flag = 1;
  
  lcd_d4_dir = 1;     		
  lcd_d5_dir = 1;
  lcd_d6_dir = 1;
  lcd_d7_dir = 1;
  
  lcd_rw=1;
  lcd_rs=0;
      
  do
  {
    lcd_enable=1;
    //delay(5); 
    delay_us(2500);
    lcd_enable=0;
    //delay(5); 
    delay_us(2500);
    busy_flag = lcd_d7;
    lcd_enable=1;
    //delay(5); 
    delay_us(2500);
    lcd_enable=0;
    //delay(5);
    delay_us(2500);
  }
  while(busy_flag == 1);
  
  lcd_d4_dir = 0;     		
  lcd_d5_dir = 0;
  lcd_d6_dir = 0;
  lcd_d7_dir = 0;
  
}

/******************************************************************************
* Fun��o    : void delay (uint32_t T)
* Descri��o : Contagem de tempo
* Cria��o   : 17/05/2007
* Entrada   : tempo ms
* Sa�da     : Nada
* Retorna   : Nada
* Notas     :
******************************************************************************/
/*void delay (unsigned long int T)
{
 int temp = 0;
 int tempo =0;
 for(temp=0;temp<=T;temp++) 
{
  for(tempo=0;tempo<1000;tempo++);  
}
*/ 
