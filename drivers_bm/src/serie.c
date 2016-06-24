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

/**
 **  Funciones para control del Puerto Serie
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
 * 20160520 v0.0.1 initials initial version
 *
 */



/*==================[inclusions]=============================================*/


#include "dac.h"

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
#define PUERTO_SERIE     7  /*Puerto Serie utilizado */
#define PIN_TX           1  /*Pin para TX */
#define PIN_RX           2  /*Pin para RX */
#define BAUDIOS     115200  /*Baudios para comuminicación serie*/


/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 */

void InicializarSerie(){
	/* inicializa el Puerto Serie - Puerto 7, pin 1 tx pin 2 rx */
	Chip_SCU_PinMux(PUERTO_SERIE,PIN_TX, MD_PDN, SCU_MODE_FUNC6); /* UART2 TXD */
	Chip_SCU_PinMux(PUERTO_SERIE,PIN_RX,MD_PLN|MD_EZI|MD_ZI,SCU_MODE_FUNC6); /* UART2 RXD */

	Chip_UART_Init(LPC_USART2);
	Chip_UART_SetBaud(LPC_USART2, BAUDIOS);
	Chip_UART_SetupFIFOS(LPC_USART2, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);
	Chip_UART_TXEnable(LPC_USART2);
}

uint8_t Leer_Byte_Serie (void) {
Chip_UART_ReadByte(LPC_USART2);
}

void Enviar_Byte_Serie (uint8_t dato){
Chip_UART_SendByte(LPC_USART2, dato);
}
