/******************************************************************************
* Este arquivo permite a portabilidade do c�digo gerado em linguagem C.
* O porte para uma nova plataforma ser� feito preenchendo os tipos listados
* abaixo.
******************************************************************************/

/******************************************************************************
* Prote��o para inclus�o recursiva
******************************************************************************/
#ifndef TYPES_H
#define TYPES_H

/******************************************************************************
* Defini��es de tipos para portabilidade.
******************************************************************************/

/* Tipos num�ricos sinalizados */
typedef signed char     int8;   /* Inteiro sinalizado de 8 bits */
typedef signed int      int16;  /* Inteiro sinalizado de 16 bits */
typedef signed long     int32;  /* Inteiro sinalizado de 32 bits */

/* Tipos num�ricos n�o-sinalizados */
typedef unsigned char   uint8;  /* Inteiro n�o-sinalizado de 8 bits */
typedef unsigned int    uint16; /* Inteiro n�o-sinalizado de 16 bits */
typedef unsigned long   uint32; /* Inteiro n�o-sinalizado de 32 bits */

/* Tipos booleanos */
typedef unsigned char   bool;

/******************************************************************************
* Defini��es padr�o
******************************************************************************/

#ifndef FALSE
#define FALSE   ((bool) 0)
#endif

#ifndef TRUE
#define TRUE    ((bool) 1)
#endif

#ifndef NULL
#define NULL    (void *) 0
#endif

/******************************************************************************
* Macros padr�o
******************************************************************************/
/*
#define NOP()   asm NOP
#define EINT()  asm CLI
#define DINT()  asm SEI
*/

#endif  /* #ifndef TYPES_H */

/***** Fim de arquivo ********************************************************/
