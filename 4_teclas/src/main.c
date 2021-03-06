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

/** Actividad4:  Diseñe e implemente un firmware sobre la EDU-CIAA que haga parpadear un led con un periodo que
permita visualizar el proceso. Mediante las cuatro teclas disponibles se debe poder seleccionar el led activo.
Emplear retardo por software.
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
 * 20160506 v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "main.h"       /* <= own header */


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */



int main(void)

{
	/* Inicialización */
	int32_t i;
	uint8_t ledtecla;
	uint8_t tecla;

	InicializarLeds();          /* Inicializamos puertos*/
	InicializarTeclas();

	ApagarLed(LEDROJO);         /* Apagamos todos los leds*/
	ApagarLed(LEDAMARILLO);
	ApagarLed(LEDVERDE);
	ApagarLed(RGBROJO);
	ApagarLed(RGBVERDE);
	ApagarLed(RGBAZUL);

/* Bucle infinito */
while (1){
	tecla = TeclaPulsada ();
	switch (tecla){
		case NOTECLA:
			ledtecla=0;           /* Si no se pulsa Tecla */
			break;
		case TECLA1:
			ledtecla=RGBAZUL;     /* Tecla 1 parpadea Led RGB Azul*/
			break;
		case TECLA2:
			ledtecla=LEDROJO;     /* Tecla 2 parpadea Led Rojo*/
			break;
		case TECLA3:
			ledtecla=LEDAMARILLO; /* Tecla 3 parpadea Led Amarillo*/
			break;
		case TECLA4:
			ledtecla=LEDVERDE;    /* Tecla 4 parpadea Led Verde*/
			break;
	}

	for(i=RETARDO; i!=0; i--){
		asm("nop");
		}
    PrenderLed(ledtecla);

 	for(i=RETARDO; i!=0; i--){
			asm("nop");
		}

 	 ApagarLed(ledtecla);


	}return 0;

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
