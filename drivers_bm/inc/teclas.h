/* Copyright 2016, Daniel Slepikas
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef TECLAS_H
#define TECLAS_H
/** \brief Bare Metal example header file
 **
 ** This is a mini example of the CIAA Firmware
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example header file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160506 v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "stdint.h"


/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2

/* Tecla ->     1    2    3    4   */
/* Puerto->     1    1    1    1   */
/* Pin   ->     0    1    2    6   */
/* GPIO  ->     0    0    0    1   */
/* Bit   ->     4    8    9    9   */
/*
 */


/* Paquete de pines correspondiente al puerto de teclas */
#define PUERTO_TECLA_1 	1
#define PUERTO_TECLA_2 	1
#define PUERTO_TECLA_3 	1
#define PUERTO_TECLA_4 	1

/* Correspondencia Pines Teclas */
#define PIN_TECLA_1	    0
#define PIN_TECLA_2	    1
#define PIN_TECLA_3     2
#define PIN_TECLA_4     6

/*Correspondencia de GPIO de cada tecla*/
#define GPIO_TECLA_1    0
#define GPIO_TECLA_2    0
#define GPIO_TECLA_3    0
#define GPIO_TECLA_4    1

/*Correspondencia de bits de cada tecla*/
#define BIT_TECLA_1     1<<4
#define NUM_BIT_TECLA_1    4
#define BIT_TECLA_2     1<<8
#define NUM_BIT_TECLA_2    8
#define BIT_TECLA_3     1<<9
#define NUM_BIT_TECLA_3    9
#define BIT_TECLA_4     1<<9
#define NUM_BIT_TECLA_4    9


/*Pseudo booleans*/
#define VERDADERO 1
#define FALSO     0

#define PULSADA   1
#define NOPULSADA 0

#define ENTRADA   0

#define NOTECLA 0
#define TECLA1  1
#define TECLA2  2
#define TECLA3  3
#define TECLA4  4


/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/
#if (CPU == mk60fx512vlq15)
/* Reset_Handler is defined in startup_MK60F15.S_CPP */
void Reset_Handler( void );

extern uint32_t __StackTop;
#elif (CPU == lpc4337)
/** \brief Reset ISR
 **
 ** ResetISR is defined in cr_startup_lpc43xx.c
 **
 ** \remark the definition is in
 **         externals/drivers/cortexM4/lpc43xx/src/cr_startup_lpc43xx.c
 **/
extern void ResetISR(void);

/** \brief Stack Top address
 **
 ** External declaration for the pointer to the stack top from the Linker Script
 **
 ** \remark only a declaration is needed, there is no definition, the address
 **         is set in the linker script:
 **         externals/base/cortexM4/lpc43xx/linker/ciaa_lpc4337.ld.
 **/
extern void _vStackTop(void);



//void RIT_IRQHandler(void);


#else
#endif

/*==================[external functions declaration]=========================*/
void InicializarTeclas();
uint8_t TeclaPulsada ();

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef BAREMETAL_BLINKING_H */

