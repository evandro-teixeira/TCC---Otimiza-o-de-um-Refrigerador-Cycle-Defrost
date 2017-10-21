/******************************************************************************
* Este arquivo permite a portabilidade do código gerado em linguagem C.
* O porte para uma nova plataforma será feito preenchendo os tipos listados
* abaixo.
******************************************************************************/

/******************************************************************************
* Proteção para inclusão recursiva
******************************************************************************/
#ifndef TYPES_H
#define TYPES_H

/******************************************************************************
* Definições de tipos para portabilidade.
******************************************************************************/

/* Tipos numéricos sinalizados */
typedef signed char     int8;   /* Inteiro sinalizado de 8 bits */
typedef signed int      int16;  /* Inteiro sinalizado de 16 bits */
typedef signed long     int32;  /* Inteiro sinalizado de 32 bits */

/* Tipos numéricos não-sinalizados */
typedef unsigned char   uint8;  /* Inteiro não-sinalizado de 8 bits */
typedef unsigned int    uint16; /* Inteiro não-sinalizado de 16 bits */
typedef unsigned long   uint32; /* Inteiro não-sinalizado de 32 bits */

/* Tipos booleanos */
typedef unsigned char   bool;

/******************************************************************************
* Definições padrão
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
* Macros padrão
******************************************************************************/
/*
#define NOP()   asm NOP
#define EINT()  asm CLI
#define DINT()  asm SEI
*/

#endif  /* #ifndef TYPES_H */

/***** Fim de arquivo ********************************************************/
