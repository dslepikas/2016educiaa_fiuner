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

/** ACTIVIDAD 5: CONTROL DE LEDS

 ** Programe una aplicación que emplee los drivers led.c y teclas.c
 ** para seleccionar el led que parapdea de la EDU-CIAA.
 ** Al iniciar la aplicación debe parpadear el LED 2.

 ** Mediante la tecla TEC1 se debe poder seleccionar el led a la izquierda
 ** del actual para que para que parpadee, y a través de la tecla TEC4
 ** el de la derecha del actual. La interfaz debe permitir mantener
 ** la tecla presionada para modificar la selección de manera
 ** reiterativa a una velocidad cómoda para el usuario.
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
 * 20160507 v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "main.h"       /* <= own header */


#define RETARDO 5000000



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
	int32_t i;                     /* variable de retardo */
	uint8_t ledActivo;             /* led que va a parpadear */
	uint8_t tecla;                 /* tecla pulsada */

	InicializarLeds();             /* Inicialización de drivers */
	InicializarTeclas();

	ApagarLed(LEDROJO);            /* Apagamos todos los leds antes de empezar */
	ApagarLed(LEDAMARILLO);
	ApagarLed(LEDVERDE);
	ApagarLed(RGBROJO);
	ApagarLed(RGBVERDE);
	ApagarLed(RGBAZUL);

	ledActivo = LEDAMARILLO;       /* Iniciamos con led Amarillo */


while (1){

	for(i=RETARDO; i!=0; i--){       /* Retardo */
		asm("nop");
	}

	tecla = TeclaPulsada ();         /* Lee teclado */

	switch (tecla){
		case NOTECLA:                /*  no cambia    */
			break;
		case TECLA1:                 /* Si pulsa Tecla 1 -> rota a izquierda */
			if (ledActivo==LEDROJO) ledActivo=LEDVERDE; else ledActivo--;
			break;
		case TECLA2:                 /*  no cambia    */
			break;
		case TECLA3:                 /*  no cambia    */
			break;
		case TECLA4:                 /* Si pulsa Tecla 4 -> rota a derecha */
			if (ledActivo==LEDVERDE)	ledActivo=LEDROJO; else ledActivo ++;
			break;
	}


	ConmutaLed(ledActivo);

	for(i=RETARDO; i!=0; i--){       /* Retardo */
			asm("nop");
	}

	ConmutaLed(ledActivo);

 	} return 0;

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
