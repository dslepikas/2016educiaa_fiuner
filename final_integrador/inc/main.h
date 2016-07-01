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

#ifndef MAIN_H
#define MAIN_H
/**Consigna
** a) Dise~ne e implemente un Firmware sobre la EDU-CIAA que permita adquirir una se~nal analogica de excursi
** on entre 0 y 3.3V, a una frecuencia de muestreo de 10 Hz. La se~nal debera reproducirse por el conversor
** D-A..
** Interfaz con el usuario:
Tec 1: Aumenta el valor de amplitud de la se~nal.
Tec 2: Disminuye la amplitud de la se~nal.
Tec 3: Lleva la se~nal de salida a 0 (independientemente de la entrada).
Funcionalidad reservada al usuario.
El led 1 debera invertir su estado cada vez que se realiza una conversion.
Adicionalemente cada vez que se presiona una tecla el sistema debera enviar por el puerto serie la siguiente
informacion:
Tec 1: Aumento la ganancia"
Tec 2: Disminuyo la ganancia"
Tec 3: MUTE"
Tec 4: ..."
El dise~no del rmware para la aplicacion debera basarse en drivers para los dispositivos y perifericos,
evitando hacer llamadas a la LPCOpen desde la capa de aplicacion.
 ** Para Edu-CIAA
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
 * 20160701 v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "stdint.h"
#include "led.h"
#include "teclas.h"
#include "timers.h"
#include "dac.h"
#include "adc.h"
#include "serie.h"


/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2

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



void RIT_IRQHandler(void);


#else
#endif

/*==================[external functions declaration]=========================*/
void Ejecuta_RIT(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef BAREMETAL_BLINKING_H */

