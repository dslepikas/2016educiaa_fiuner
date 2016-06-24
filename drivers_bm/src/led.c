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

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
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
 *  * 20150512 v0.0.2 Se incorpora intensidad a la estructrua ledRGB y se crea
 * 				   la funcion void ExpresaLedRGB
 */



/*==================[inclusions]=============================================*/


#include "led.h"

#define lpc4337            1
#define mk60fx512vlq15     2

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif


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

void InicializarLeds(){
	/* inicializa el puerto GPIO */
	 Chip_GPIO_Init(LPC_GPIO_PORT);

	 /* Chip_SCU_PinMux (Paquete o puerto, Pin específico, Modo, Función del pin)
	  * configura el pin de salida multiplexada y su función
	  */
     Chip_SCU_PinMux(PUERTO_LED_1,PIN_LED_1,MD_PUP,FUNC0);              /*Led 1*/
     Chip_SCU_PinMux(PUERTO_LED_2,PIN_LED_2,MD_PUP,FUNC0);              /*Led 2*/
     Chip_SCU_PinMux(PUERTO_LED_3,PIN_LED_3,MD_PUP,FUNC0);              /*Led 3*/
     Chip_SCU_PinMux(PUERTO_RGB_ROJO, PIN_RGB_ROJO,MD_PUP,FUNC4);       /*Led ROJO RGB*/
     Chip_SCU_PinMux(PUERTO_RGB_VERDE, PIN_RGB_VERDE,MD_PUP,FUNC4);     /*Led VERDE RGB*/
     Chip_SCU_PinMux(PUERTO_RGB_AZUL, PIN_RGB_AZUL,MD_PUP,FUNC4);       /*Led AZUL RGB*/

     /*Chip_GPIO_SetDir (puerto, GPIO, posición del bit del led, SALIDA/ENTRADA)
      *Define a los pines correspondientes a los leds como de salida
      */
	 Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO_LED_1,BIT_LED_1,SALIDA);         /*Led 1*/
	 Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO_LED_2,BIT_LED_2,SALIDA); 		  /*Led 2*/
	 Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO_LED_3,BIT_LED_3,SALIDA); 		  /*Led 3*/
	 Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO_RGB_ROJO,BIT_RGB_ROJO,SALIDA);   /*Led RGB ROJO*/
	 Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO_RGB_VERDE,BIT_RGB_VERDE,SALIDA); /*Led RGB VERDE*/
	 Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO_RGB_AZUL,BIT_RGB_AZUL,SALIDA);   /*Led RGB AZUL*/

}

void PrenderLed(uint8_t Led){
	/* Enciende Led -> Led */
	switch (Led){
		case LEDROJO:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO_LED_1,NUM_LED_1); /* Led 1*/
			break;
		case LEDAMARILLO:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO_LED_2,NUM_LED_2); /* Led 2*/
			break;
		case LEDVERDE:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO_LED_3,NUM_LED_3); /* Led 3*/
			break;

		/*Las siguientes lineas permiten cambiar el estado de los leds RGB,
		 *si bien esto debería hacerse desde la función específica para la gestión del Led RGB
		 *con variable estructurada, se deja activa por si resulta conveniente en alguna aplicación futura
		 */
		case RGBROJO:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO_RGB_ROJO,NUM_RGB_ROJO); /* Led RGB_ROJO*/
			break;
		case RGBVERDE:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO_RGB_VERDE,NUM_RGB_VERDE); /* Led RGB VERDE*/
			break;
		case RGBAZUL:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO_RGB_AZUL,NUM_RGB_AZUL); /* Led RGB AZUL*/
			break;

	}
}

void ApagarLed(uint8_t Led){
	/* Apaga el Led -> Led */
	switch (Led){
		case LEDROJO:
			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO_LED_1,NUM_LED_1); /*Led 1*/
			break;
	    case LEDAMARILLO:
			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO_LED_2,NUM_LED_2); /*Led 2*/
			break;
		case LEDVERDE:
			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO_LED_3,NUM_LED_3); /*Led 3*/
			break;

		/*Las siguientes lineas permiten cambiar el estado de los leds RGB,
		 *si bien esto debería hacerse desde la función específica para la gestión del Led RGB
		 *con variable estructurada, se deja activa por si resulta conveniente en alguna aplicación futura */
		case RGBROJO:
			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO_RGB_ROJO,NUM_RGB_ROJO);   /*Led RGB_ROJO*/
			break;
		case RGBVERDE:
			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO_RGB_VERDE,NUM_RGB_VERDE); /*Led RGB VERDE*/
			break;
		case RGBAZUL:
			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO_RGB_AZUL,NUM_RGB_AZUL);   /*Led RGB AZUL*/
			break;
	}
}

void ConmutaLed(uint8_t Led){
	/*Conmuta el estado del led*/
	switch (Led){
		case LEDROJO:
			Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,GPIO_LED_1,NUM_LED_1);   /* Led 1*/
			break;
		case LEDAMARILLO:
			Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,GPIO_LED_2,NUM_LED_2);   /*Led 2*/
			break;
		case LEDVERDE:
			Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,GPIO_LED_3,NUM_LED_3);   /*Led 3*/
			break;

		/*Las siguientes lineas permiten cambiar el estado de los leds RGB,
		 *si bien esto debería hacerse desde la función específica para la gestión del Led RGB
		 *con variable estructurada, se deja activa por si resulta conveniente en alguna aplicación futura
		 */
		case RGBROJO:
			Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,GPIO_RGB_ROJO,NUM_RGB_ROJO);   /*Led RGB_ROJO*/
			break;
		case RGBVERDE:
			Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,GPIO_RGB_VERDE,NUM_RGB_VERDE); /*Led RGB VERDE*/
			break;
		case RGBAZUL:
			Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,GPIO_RGB_AZUL,NUM_RGB_AZUL);   /*Led RGB AZUL*/
			break;
				}
}

void ConmutarLedRGB(ledRGB *localRGB){
	/*Conmuta el estado del led RGB indicado*/

	if (localRGB->rojo==CAMBIAR) {
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,GPIO_RGB_ROJO,NUM_RGB_ROJO);  /*Led RGB_ROJO*/
	}
	if (localRGB->verde==CAMBIAR) {
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,GPIO_RGB_VERDE,NUM_RGB_VERDE); /*Led RGB VERDE*/
	}
	if (localRGB->azul==CAMBIAR) {
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,GPIO_RGB_AZUL,NUM_RGB_AZUL); /*Led RGB AZUL*/
	}
}

void PrenderLedRGB(ledRGB *localRGB){
	/*Enciende el led RGB indicado forzando a "1" el bit correspondiente*/

	if (localRGB->rojo==ENCENDER) {
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO_RGB_ROJO,NUM_RGB_ROJO);  /*Led RGB_ROJO*/
	}
	if (localRGB->verde==ENCENDER) {
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO_RGB_VERDE,NUM_RGB_VERDE); /*Led RGB VERDE*/
	}
	if (localRGB->azul==ENCENDER) {
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO_RGB_AZUL,NUM_RGB_AZUL); /*Led RGB AZUL*/
	}
}

void ApagarLedRGB(ledRGB *localRGB){
	/*Apaga el led RGB indicado forzando a "0" el bit correspondiente*/

	if (localRGB->rojo==APAGAR) {
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO_RGB_ROJO,NUM_RGB_ROJO);  /*Led RGB_ROJO*/
	}
	if (localRGB->verde==APAGAR) {
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO_RGB_VERDE,NUM_RGB_VERDE); /*Led RGB VERDE*/
	}
	if (localRGB->azul==APAGAR) {
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO_RGB_AZUL,NUM_RGB_AZUL); /*Led RGB AZUL*/
	}

}

void ExpresaLedRGB(ledRGB *localRGB){
	/*Apaga o enciende el led RGB indicado forzando a "0" o a "1" el bit correspondiente*/

	if (localRGB->rojo==APAGAR) {
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO_RGB_ROJO,NUM_RGB_ROJO);  /*Led RGB_ROJO*/
		}else Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO_RGB_ROJO,NUM_RGB_ROJO);

	if (localRGB->verde==APAGAR) {
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO_RGB_VERDE,NUM_RGB_VERDE); /*Led RGB VERDE*/
	    }else Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO_RGB_VERDE,NUM_RGB_VERDE);

	if (localRGB->azul==APAGAR) {
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,GPIO_RGB_AZUL,NUM_RGB_AZUL); /*Led RGB AZUL*/
	   }else Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,GPIO_RGB_AZUL,NUM_RGB_AZUL);

}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

