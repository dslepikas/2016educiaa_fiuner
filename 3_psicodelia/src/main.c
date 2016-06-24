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

/** Actividad3: Aplicación "Psicodelia"
 ** Los leds se encienden secuencialmente
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
 * yyyymmdd v0.0.1 initials initial version
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
	/* perform the needed initialization here */
	int32_t i;
	ledRGB ledsRGB;
	InicializarLeds();


while (1){


	for(i=RETARDO; i!=0; i--){
		asm("nop");
		}

		ApagarLed(LEDROJO); /* Led Amarillo*/
		PrenderLed(LEDAMARILLO);
		ApagarLed(LEDVERDE);

		ledsRGB.rojo=APAGAR;
		ledsRGB.verde=APAGAR;
		ledsRGB.azul= APAGAR;
		ApagarLedRGB(&ledsRGB);
		ledsRGB.azul= ENCENDER; /* Led Azul*/
		PrenderLedRGB(&ledsRGB);

 	for(i=RETARDO; i!=0; i--){
			asm("nop");
		}

 		ApagarLed(LEDAMARILLO);
		PrenderLed(LEDVERDE);   /* Led Verde*/

		ledsRGB.azul= APAGAR;
		ApagarLedRGB(&ledsRGB);
		ledsRGB.verde= ENCENDER; /* Led Verde*/
		PrenderLedRGB(&ledsRGB);

	for(i=RETARDO; i!=0; i--){
			asm("nop");
		}
		PrenderLed(LEDROJO);       /* Led Rojo*/
		ApagarLed(LEDVERDE);

		ledsRGB.verde=APAGAR;
		ApagarLedRGB(&ledsRGB);
		ledsRGB.rojo= ENCENDER;    /* Led Rojo*/
		PrenderLedRGB(&ledsRGB);



	}return 0;

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
