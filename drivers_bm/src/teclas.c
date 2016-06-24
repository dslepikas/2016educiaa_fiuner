/* Copyright 2016, Slepikas Daniel
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

/** \brief Blinking Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
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
#include "teclas.h"

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

/*
 * Ver -> CHIP: LPC18xx/43xx GPIO driver - LPC18xx/43xx chip specific drivers
 *        ..lpcopen_2_16_docs_18xx_43xx/group___g_p_i_o__18_x_x__43_x_x.html
 * Funciones útiles
 *
 * STATIC INLINE
 * bool Chip_GPIO_GetPinState (LPC_GPIO_T *pGPIO, uint8_t port, uint8_t pin)
 * void Chip_GPIO_SetPinDIRInput (LPC_GPIO_T *pGPIO, uint8_t port, uint8_t pin)
 * bool Chip_GPIO_ReadDirBit (LPC_GPIO_T *pGPIO, uint32_t port, uint8_t bit)
 *
 *
 */

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

/* Tecla   ->     1    2    3    4   */
/* Puerto  ->     1    1    1    1   */
/* Pin     ->     0    1    2    6   */
/* GPIO    ->     0    0    0    1   */
/* Bit     ->     4    8    9    9   */
/* Función ->     0    0    0    0   */

void InicializarTeclas(){
	/* inicializa el puerto GPIO */
	 Chip_GPIO_Init(LPC_GPIO_PORT);

	 /* Configura Multiplexor: Chip_SCU_PinMux (Puerto, Pin específico, Modo, Función del pin)*/
     Chip_SCU_PinMux(PUERTO_TECLA_1,PIN_TECLA_1,MD_PUP|MD_EZI|MD_ZI,FUNC0 );
     Chip_SCU_PinMux(PUERTO_TECLA_2,PIN_TECLA_2,MD_PUP|MD_EZI|MD_ZI,FUNC0);
     Chip_SCU_PinMux(PUERTO_TECLA_3,PIN_TECLA_3,MD_PUP|MD_EZI|MD_ZI,FUNC0);
     Chip_SCU_PinMux(PUERTO_TECLA_4,PIN_TECLA_4,MD_PUP|MD_EZI|MD_ZI,FUNC0);

     /* Setea puertos como Entrada: Chip_GPIO_SetDir (Puerto GPIO, GPIO específico, Bit de Tecla, Sentido)*/
	 Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO_TECLA_1,BIT_TECLA_1,ENTRADA);
	 Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO_TECLA_2,BIT_TECLA_2,ENTRADA);
	 Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO_TECLA_3,BIT_TECLA_3,ENTRADA);
	 Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO_TECLA_4,BIT_TECLA_4,ENTRADA);
}

uint8_t TeclaPulsada (void){
	/* 0:Ninguna, 1..4:tecla que está siendo pulsada */
	uint8_t tecla;

	if (0==Chip_GPIO_GetPinState(LPC_GPIO_PORT, GPIO_TECLA_1, NUM_BIT_TECLA_1)){
			tecla= TECLA1;
	}else
	if (0==Chip_GPIO_GetPinState(LPC_GPIO_PORT, GPIO_TECLA_2, NUM_BIT_TECLA_2)){
			tecla=TECLA2;
	}else
	if (0==Chip_GPIO_GetPinState(LPC_GPIO_PORT, GPIO_TECLA_3, NUM_BIT_TECLA_3)){
			tecla=TECLA3;
	}else
	if (0==Chip_GPIO_GetPinState(LPC_GPIO_PORT, GPIO_TECLA_4, NUM_BIT_TECLA_4)){
			tecla=TECLA4;
	}else tecla=NOTECLA;
return tecla;
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

/* ejemplo
uint32_t LeerTeclas(void){

	return Chip_GPIO_ReadValue(LPC_GPIO_PORT, PUERTO_TECLA_2);
	}
*/
