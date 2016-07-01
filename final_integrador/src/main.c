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

/** Ejercicio Integrador Consigna
a) Dise~ne e implemente un Firmware sobre la EDU-CIAA que permita adquirir una se~nal analogica de excursi
on entre 0 y 3.3V, a una frecuencia de muestreo de 10 Hz. La se~nal debera reproducirse por el conversor
D-A..
Interfaz con el usuario:
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
 * 20160701 v0.0.1 initials initial version

 */

/*==================[inclusions]=============================================*/
#include "main.h"       /* <= own header */


/*==================[macros and definitions]=================================*/


/*==================[internal data declaration]==============================*/
	/*Variables globales*/
 	uint16_t dataADC;        /* Valor de entrada en el ADC */
 	uint16_t dataDAC;        /* Valor de salida DAC */
 	uint16_t ganancia;       /* Valor de amplificacion */
 	uint8_t  tecla;			 /* Tecla pulsada */
 	char mensaje1[]=" Aumento la ganancia  ";
 	char mensaje2[]=" Disminuyo la ganancia";
 	char mensaje3[]=" Mute                 ";
 	char mensaje4[]=" Ganancia a 1         ";


/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
 	void Ejecuta_RIT(){
 		 /* Secuencia a ejecutar con la llamada de IRQ11 RIT*/

 	dataADC=LeerADC();
 	dataDAC=dataADC*ganancia;
 	if (dataDAC>1023) /*Ajusta la saturacion*/
 	    {
 		PrenderLed(LEDROJO); /* Si satura enciende el led rojo*/
 		dataDAC=1023;
 	    } else /* si no satura apaga el led rojo*/
 	       {
 	    	ApagarLed(LEDROJO);
 	       }

 	CargarValorDAC(dataDAC); /* Asigna el valor de salida al DAC*/
 	ConmutaLed(LEDVERDE);

 	BorraFlagRIT(); /* Borra el flag de la llamada a la interrupción*/

 	 }/*Ejecuta_RIT*/


int main(void)

{

	/*Inicializaciones */

	InicializarLeds();  				 	 /* Inicializa Leds */
	InicializarTeclas();                     /* Inicializa Teclas*/
	InicializarADC();                        /* Inicializa DAC -> CH1*/
	InicializarDAC();                        /* Inicializa Dac*/
	InicializarSerie();                      /* Inicializa Puerto Serie*/
	InicializarTimerRIT();					 /* Inicializa Timer RIT*/



	uint32_t nc;                           /* contador auxiliar para mensaje*/

	/* Ciclo infinito principal */
	while (VERDADERO){

		tecla = TeclaPulsada ();
			switch (tecla){
				case NOTECLA:               /* Si no se pulsa Tecla */

					break;
				case TECLA1:                /* Tecla 1 Aumenta ganancia*/
					if (ganancia<=10)
					  {
						ganancia++;
					  }
					for(nc=0; nc!=22; nc++) /* Envio mensaje */
						{
						 Enviar_Byte_Serie (mensaje1[nc]);
						} /*for nc */
					Enviar_Byte_Serie (10); /*Linea nueva*/
					Enviar_Byte_Serie (13); /*Retorno de carro*/
    				ConmutaLed(LEDAMARILLO);
					break;
				case TECLA2:                /* Tecla 2 Disminuye ganancia*/
					if (ganancia >=2)
					  {
						ganancia--;
					  }
					for(nc=0; nc!=22; nc++) /* Envio mensaje */
					  {
						Enviar_Byte_Serie (mensaje2[nc]);
    					} /*for nc */

					Enviar_Byte_Serie (10); /*Linea nueva*/
					Enviar_Byte_Serie (13); /*Retorno de carro*/
					ConmutaLed(LEDAMARILLO);
					break;
				case TECLA3:                /* Tecla 3 Mute*/
					ganancia=0;
					for(nc=0; nc!=22; nc++) /* Envio mensaje */
					  {
						Enviar_Byte_Serie (mensaje3[nc]);
    					} /*for nc */
					Enviar_Byte_Serie (10); /*Linea nueva*/
					Enviar_Byte_Serie (13); /*Retorno de carro*/
					ConmutaLed(LEDAMARILLO);
					break;
				case TECLA4:                /* Tecla 4 Setea Ganancia en 1 */
					ganancia=1;

					for(nc=0; nc!=22; nc++) /* Envio mensaje */
						{
						 Enviar_Byte_Serie (mensaje4[nc]);
						} /*for nc */
					Enviar_Byte_Serie (10); /*Linea nueva*/
					Enviar_Byte_Serie (13); /*Retorno de carro*/


					ConmutaLed(LEDAMARILLO);
					break;
			}

			RetardoAsmNop (5000000);


      //  Enviar_Byte_Serie (dataADC/4+32);    /* Prueba de comunicación*/

	}return FALSO; /*while */
} /*main*/








