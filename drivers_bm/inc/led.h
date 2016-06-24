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

#ifndef LED_H
#define LED_H
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
 * 20150512 v0.0.2 Se incorpora intensidad a la estructrua ledRGB y se crea
 * 				   la funcion void ExpresaLedRGB
 */

/*==================[inclusions]=============================================*/

#include "stdint.h"

/*==================[macros]=================================================*/

/* Led      ->     1     2     3      4     5     6    */
/* Led Tipo ->   <-- Monocromo -->  <----  RGB  ---->  */
/* Color    ->  Rojo Amarillo Verde  Rojo  Verde  Azul */
/* Puerto   ->     2     2     2      2     2     2    */
/* Pin      ->    10    11    12      0     1     2    */
/* GPIO     ->     0     1     1      5     5     5    */
/* Bit      ->    14    11    12      0     1     2    */



/* Paquete de pines correspondiente al puerto de leds */
#define PUERTO_LED_1     2  /*Rojo    */
#define PUERTO_LED_2     2  /*Amarillo*/
#define PUERTO_LED_3     2  /*Verde   */
#define PUERTO_RGB_ROJO  2
#define PUERTO_RGB_VERDE 2
#define PUERTO_RGB_AZUL  2

/* Correspondencia Pines Leds*/
#define PIN_LED_1     10   /*Rojo    */
#define PIN_LED_2     11   /*Amarillo*/
#define PIN_LED_3     12   /*Verde   */
#define PIN_RGB_ROJO   0
#define PIN_RGB_VERDE  1
#define PIN_RGB_AZUL   2

/*Correspondencia de GPIO de cada led*/
#define GPIO_LED_1     0   /*Rojo    */
#define GPIO_LED_2     1   /*Amarillo*/
#define GPIO_LED_3     1   /*Verde   */
#define GPIO_RGB_ROJO  5
#define GPIO_RGB_VERDE 5
#define GPIO_RGB_AZUL  5

/*Correspondencia de bits de cada led
 * BIT_LED_x y BIT_RGB_xxxx es la posición del bit del estado del led en el puerto en notación binaria
 * NUM_LED_x y NUM_RGB_xxxx Corresponde a la misma posición en notación decimal
 * */
#define BIT_LED_1    1<<14    /*Rojo    */
#define NUM_LED_1       14
#define BIT_LED_2    1<<11    /*Amarillo*/
#define NUM_LED_2       11
#define BIT_LED_3    1<<12    /*Verde   */
#define NUM_LED_3       12
#define BIT_RGB_ROJO  1<<0
#define NUM_RGB_ROJO     0
#define BIT_RGB_VERDE 1<<1
#define NUM_RGB_VERDE    1
#define BIT_RGB_AZUL  1<<2
#define NUM_RGB_AZUL     2

/*Pseudo booleanos*/
#define VERDADERO 1
#define FALSO     0

#define SALIDA    1

#define ENCENDER  1
#define APAGAR    0

#define CAMBIAR   1
#define NOCAMBIAR 0

/*Definir leds por colores*/
#define LEDROJO      1
#define LEDAMARILLO  2
#define LEDVERDE     3
#define RGBROJO      4
#define RGBVERDE     5
#define RGBAZUL      6

/*No logré que funcione usando enum

 enum led_color{LEDROJO, LEDAMARILLO, LEDVERDE, RGBROJO, RGBVERDE, RGBAZUL};

*/

/*==================[typedef]================================================*/
/*definicion de la variable estructurada ledRGB */

 typedef struct {
	uint8_t rojo;
	uint8_t verde;
	uint8_t azul;
	uint8_t intensidad;
    }ledRGB;

/*==================[external data declaration]==============================*/






/*==================[external functions declaration]=========================*/
    void InicializarLeds();
    void PrenderLed(uint8_t Led);
    void ApagarLed(uint8_t Led);
    void ConmutarLed(uint8_t Led);

	void PrenderLedRGB(ledRGB *localRGB);
	void ApagarLedRGB(ledRGB *localRGB);
	void ConmutarLedRGB(ledRGB *localRGB);
	void ExpresaLedRGB(ledRGB *localRGB);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef MI_NUEVO_PROYECTO_H */

