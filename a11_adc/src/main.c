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

/** Actividad 11: Manejo de conversor ADC
 ** Consignas
 ** Diseñe e implemente un Firmware sobre la EDU-CIAA que permita adquirir una señal analógica
 ** de excursión entre 0 y 3.3V presente en el pin CH1 del conector P1.
 ** El sistema debe encender el led rojo si la señal toma su valor máximo (>1020 d)
 ** y led verde si la señal toma su valor mínimo (<5 d). Puede resolverlo por pooling.
 **
 ** Para Edu-CIAA
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160520 v0.0.1 initials initial version

 */

/*==================[inclusions]=============================================*/
#include "main.h"       /* <= own header */


/*==================[macros and definitions]=================================*/


/*==================[internal data declaration]==============================*/
	/*Variables globales*/
 	uint16_t dataADC;        /* Valor del ADC */


/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/



int main(void)

{
	/*Inicializaciones */

	InicializarLeds();  				 	 /* Inicializa Leds */
	InicializarADC();                        /* Inicializa DAC*/
	ConmutaLed(LEDROJO);

	/* Ciclo infinito principal */
	while (VERDADERO){

		dataADC=LeerADC();
			 if (dataADC<2)
			   {
			   PrenderLed(LEDVERDE);
			   ApagarLed(LEDROJO);
			   ApagarLed(LEDAMARILLO);
			   }else
			        {
				    if (dataADC>1021)
				       {
					   PrenderLed(LEDROJO);
					   ApagarLed(LEDVERDE);
					   ApagarLed(LEDAMARILLO);
					   }else
					       {
						   PrenderLed(LEDAMARILLO);
						   ApagarLed(LEDVERDE);
						   ApagarLed(LEDROJO);
					       }
			         }

	}return FALSO; /*while */
} /*main*/








