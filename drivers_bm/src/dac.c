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
**  Funciones para control del DAC
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



/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 */

void InicializarDAC(){
	/* inicializa el DAC - SCU configura el PIN */
	   Chip_SCU_DAC_Analog_Config();


//	   void Chip_DAC_Init	(	LPC_DAC_T * 	pDAC	)
//	   Initial DAC configuration.
//
//	            - Maximum current is 700 uA
//	            - Value to AOUT is 0
//	   Parameters
//	   pDAC	: pointer to LPC_DAC_T

	   Chip_DAC_Init(LPC_DAC);

	  // Chip_DAC_SetBias(LPC_DAC,DAC_MAX_UPDATE_RATE_400kHz); /*No necesaria*/

	  // Chip_DAC_SetDMATimeOut(LPC_DAC, 0xffff);  /*No necesaria*/


//	   STATIC INLINE void Chip_DAC_ConfigDAConverterControl	(	LPC_DAC_T * 	pDAC,
//	   uint32_t 	dacFlags
//	   )
//	   Enables the DMA operation and controls DMA timer.
//
//	   Parameters
//	   pDAC	: pointer to LPC_DAC_T
//	   dacFlags	: An Or'ed value of the following DAC values:
//	   DAC_DBLBUF_ENA :enable/disable DACR double buffering feature
//	   DAC_CNT_ENA :enable/disable timer out counter
//	   DAC_DMA_ENA :enable/disable DMA access

	   Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_CNT_ENA | DAC_DMA_ENA);

}

void CargarValorDAC (uint32_t dac_value){
	/* Inicializa el DAC*/
//void Chip_DAC_UpdateValue	(LPC_DAC_T *pDAC, uint32_t dac_value)
//Update value to DAC buffer.
//
//Parameters
//pDAC	: pointer to LPC_DAC_T
//dac_value	: value 10 bit to be converted to output

Chip_DAC_UpdateValue(LPC_DAC, dac_value);

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

