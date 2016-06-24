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

/** Actividad 9: Manejo de conversor DAC
 ** Consignas
 ** a) Dise~ne e implemente un rmware sobre la EDU-CIAA que genera una se~nal tipo diente de sierra de periodo
 **    100 ms y excursion de 0 a 3V.
 ** b) Incorpore al ejercicio anterior la funcionalidad de variar el periodo y la amplitud de la se~nal.
 **    Tec 1: Aumenta la amplitud de la se~nal.
 **	   Tec 2: Disminuye la amplitud de la se~nal.
 **    Tec 3: Aumenta el periodo de la se~nal.
 **	   Tec 4: Disminuye el periodo de la se~nal.
 **
 ** Para Edu-CIAA
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

#define RETARDO       3000000  /* Retardo en asm nop */
#define RETARDOxCERO 30000000  /* Retardo amplilado p/ esperar en paso x cero*/
#define RANGO 5                /* tonos de color de leds RGB por canal
                                  Si es mayor a 5 se nota el parpadeo */
#define IRQ_RIT 11             /* Interrupción del RIT */


/*==================[internal data declaration]==============================*/
	/*Variables globales*/
    uint32_t contadorCiclo;   /* contador interrupciones por ciclo*/
	ledRGB ledsRGB;           /* color deseado del RGB+intensidad */
	ledRGB contadorRGB;       /* contador de interrupciones por color RGB*/
	uint32_t cicloTotal;      /* RANGO*RANGO ->ciclo total de trabajo del RGB */
	uint8_t baseTiempoDAC;
	uint32_t valorDAC;


/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void Ejecuta_RIT(){
	 /* Secuencia a ejecutar con la llamada de IRQ11 RIT*/
	if (baseTiempoDAC==100)
		{
		baseTiempoDAC=0;
		} else
			{
			baseTiempoDAC++;
			};
	CargarValorDAC(baseTiempoDAC*10);


	if (contadorCiclo>=cicloTotal)
		{
			contadorCiclo=0;
			contadorRGB.rojo=ledsRGB.rojo*ledsRGB.intensidad;
			contadorRGB.verde=ledsRGB.verde*ledsRGB.intensidad;
			contadorRGB.azul=ledsRGB.azul*ledsRGB.intensidad;
			//ConmutaLed(LEDROJO);
		}else
			{
			contadorCiclo ++;
			//ConmutaLed(LEDVERDE);
			}

	if (contadorRGB.rojo>0)
		{
			contadorRGB.rojo--;
		}
	if (contadorRGB.verde>0)
		{
			contadorRGB.verde--;
		}
	if (contadorRGB.azul>0)
		{
			contadorRGB.azul--;
		}
	ExpresaLedRGB(&contadorRGB);

 BorraFlagRIT(); /* Borra el flag de la llamada a la interrupción*/

 }/*Ejecuta_RIT*/

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
	/*Inicializaciones */
	uint8_t tecla;                         	/* Tecla pulsada*/


	InicializarLeds();  				 	 /* Inicializa Leds */
	InicializarTeclas();					 /* Inicializa teclado */
	InicializarTimerRIT();               	 /* Inicializa Timers RIT*/
	InicializarDAC();                        /* Inicializa DAC*/

	ledsRGB.rojo=RANGO-1;                	 /* Valor inicial para los leds del RGB */
	ledsRGB.verde=RANGO-2;
	ledsRGB.azul=APAGAR;
	ledsRGB.intensidad=RANGO-1;

	CargarValorDAC(200);

	cicloTotal=RANGO*RANGO;  /* Calcula el numero de intervalos totales por ciclo*/

/* Ciclo infinito principal */
while (VERDADERO){

	tecla = TeclaPulsada();


	switch (tecla){
		case NOTECLA:
			                                       /* Si no se pulsa Tecla  */
			ApagarLed(LEDROJO);
			ApagarLed(LEDAMARILLO);
			ApagarLed(LEDVERDE);
			//CargarValorDAC (200);
			break;

		case TECLA1:
			if (ledsRGB.rojo>= RANGO)
			{
				ledsRGB.rojo=APAGAR;
					PrenderLed(LEDAMARILLO);        /* Indica paso por cero*/
					PrenderLed(LEDVERDE);
					RetardoAsmNop(RETARDOxCERO);    /* Retardo extendido */

			}else ledsRGB.rojo++;                   /* Tecla 1 aumenta RGB rojo*/
			ConmutaLed(LEDROJO);
			//CargarValorDAC (100);
			break;

		case TECLA2:
			if (ledsRGB.verde>= RANGO)
			{
				ledsRGB.verde=APAGAR;
					PrenderLed(LEDAMARILLO);        /* Indica paso por cero*/
					PrenderLed(LEDROJO);
					RetardoAsmNop (RETARDOxCERO);   /* Retardo extendido */
			}else ledsRGB.verde++;                  /* Tecla 2 aumenta RGB verde*/
			ConmutaLed(LEDVERDE);
			//CargarValorDAC (500);
			break;

		case TECLA3:
			if (ledsRGB.azul>= RANGO)
			{
				ledsRGB.azul=APAGAR;
					PrenderLed(LEDROJO);            /* Indica paso por cero*/
					PrenderLed(LEDVERDE);
					RetardoAsmNop (RETARDOxCERO);   /* Retardo extendido */
			}else ledsRGB.azul++;                   /* Tecla 3 aumenta RGB azul*/
			ConmutaLed(LEDAMARILLO);                /* acusa incremento azul RGB */
			//CargarValorDAC (700);
			break;

		case TECLA4:
			if (ledsRGB.intensidad>= RANGO)
			{
				ledsRGB.intensidad=APAGAR;
					ConmutaLed(LEDAMARILLO);       /* Indica paso por cero*/
					ConmutaLed(LEDVERDE);
					RetardoAsmNop (RETARDOxCERO);  /* Retardo extendido */
				}else ledsRGB.intensidad++;        /* Tecla 4 aumenta la intensidad*/
			ConmutaLed(LEDROJO);                   /* acusa incremento*/
			//CargarValorDAC (1000);
			break;
	 }/*switch */

	RetardoAsmNop (RETARDO);                    /* Retardo entre lectura de teclado */


  }return FALSO; /*while */
} /*main*/


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

//while (VERDADERO){
//
//	tecla = TeclaPulsada();
//
//	switch (tecla){
//		case NOTECLA:
//			                                       /* Si no se pulsa Tecla  */
//			ApagarLed(LEDROJO);
//			ApagarLed(LEDAMARILLO);
//			ApagarLed(LEDVERDE);
//			CargarValorDAC (200);
//			break;
//
//		case TECLA1:
//			if (ledsRGB.rojo>= RANGO)
//			{
//				ledsRGB.rojo=APAGAR;
//					PrenderLed(LEDAMARILLO);        /* Indica paso por cero*/
//					PrenderLed(LEDVERDE);
//					RetardoAsmNop(RETARDOxCERO);    /* Retardo extendido */
//
//			}else ledsRGB.rojo++;                   /* Tecla 1 aumenta RGB rojo*/
//			ConmutaLed(LEDROJO);
//			CargarValorDAC (100);
//			break;
//
//		case TECLA2:
//			if (ledsRGB.verde>= RANGO)
//			{
//				ledsRGB.verde=APAGAR;
//					PrenderLed(LEDAMARILLO);        /* Indica paso por cero*/
//					PrenderLed(LEDROJO);
//					RetardoAsmNop (RETARDOxCERO);   /* Retardo extendido */
//			}else ledsRGB.verde++;                  /* Tecla 2 aumenta RGB verde*/
//			ConmutaLed(LEDVERDE);
//			CargarValorDAC (500);
//			break;
//
//		case TECLA3:
//			if (ledsRGB.azul>= RANGO)
//			{
//				ledsRGB.azul=APAGAR;
//					PrenderLed(LEDROJO);            /* Indica paso por cero*/
//					PrenderLed(LEDVERDE);
//					RetardoAsmNop (RETARDOxCERO);   /* Retardo extendido */
//			}else ledsRGB.azul++;                   /* Tecla 3 aumenta RGB azul*/
//			ConmutaLed(LEDAMARILLO);                /* acusa incremento azul RGB */
//			CargarValorDAC (700);
//			break;
//
//		case TECLA4:
//			if (ledsRGB.intensidad>= RANGO)
//			{
//				ledsRGB.intensidad=APAGAR;
//					ConmutaLed(LEDAMARILLO);       /* Indica paso por cero*/
//					ConmutaLed(LEDVERDE);
//					RetardoAsmNop (RETARDOxCERO);  /* Retardo extendido */
//				}else ledsRGB.intensidad++;        /* Tecla 4 aumenta la intensidad*/
//			ConmutaLed(LEDROJO);                   /* acusa incremento*/
//			CargarValorDAC (1000);
//			break;
//	 }/*switch */
//
//	RetardoAsmNop (RETARDO);                    /* Retardo entre lectura de teclado */
//
//
//  }return FALSO; /*while */
