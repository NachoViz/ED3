/\*

 \* Interrupciones.c

 \*

 \*  Created on: 26 ago 2025

 \*      Author: jnach

 \*

 \*

 \*      NVIC = MANEJA TODAS LAS INTERRUPCIONES, CORE LEVANTA LA MANO PARA QUE ATIENDAN LAS INTERRUPCIONES

 \*

 \*      INTERRUPCION PENDIENTE -> SI HAY UNA SEÑAL EN ALTO, SI EL NVIC NO TIENE UNA INTERR ACTIVA

 \*

 \*      INTERRPMPE -> VA A HABER UNA INTERRPCION PENDIENTE mientras rising edge

 \*

 \*      Se vuelva pendiente setpendig stir-> formas de generar una interrpcion por software

 \*

 \*      +pendiente hasta que el nvic ingresa a atender la interrpcion pasa de PENDIENTE->ACTIVO

 \*

 \*      si llega otro pulso mientras esta activa, pasa de estar activa y pendiente

 \*

 \*      Registro para limpiar interrupciones PENDIENTES -> Interrupcion dei son de prioridad ...

 \*

 \*      INTERRP DE NIVEL \_> LARGO TRECHO EN ALTO -> si la limpio por software, baja pero al estar en alto todavia vuelve a subir

 \*      \_\_\_\_\_-----------------------\_\_\_\_\_

 \*      \_\_\_\_\_\_--------\_-------------\_\_\_\_\_\_

 \*

 \*      Si no limpio la interrupción de nivel vuelve a estar pendiente y puede ponerse activa y pendiente

 \*

 \*      FLAGS EN NVIC y PERIFERICOS; HAY QUE LIMPIARLAS

 \*      NVIC registros map -> ISER - ICER

 \*      				-- ->Estado pendiente o no pendiente ISPRC-ICPR

 \*      				   ->Prioridades similar atiende a la que tiene menor indice de interrupt ID(tabla)

 \*      				   ->PRIGRUP-> DE LOS 5 BITS habilitados separo en 2 grupos ->1y3 como prioridad y el resto como subprioridad-> generando que pueda tener 2 de prioridad y  con el resto de bits pueda configurar cual atender primero

 \*

 \*      INTERRPT REGISTER   (Las podes encontrar en la estructura LPC\_GPIOINT)

 \*      IntEnR -> puerto 0 y 2 ----->IO0IntStaat(R/F) = si se genera una interrupcion se genera en el stack

 \*      IntEnF -> Puedo tener flaco de subida o bajada o ambos

 \*      IntStar-> Si hubo interrpcion

 \*      IO0IntClr->Limpian todas las inter  tanto el status de subida como de bajada.

 \*      IO2IntClr->puerto2

 \*      IntSt->y otro de Status (DONDE ESTAN LAS INTERRUPCIONES Y CANTIDAD)

 \*

 \*      INTERRP EXT  (modulo dedicado)

 \*      EINT0 P2.10   01

 \*      EINT1 P2.11   01

 \*      EINT2 P2.12   01

 \*      EINT3 P2.13   01

 \*

 \*      $INTERRUPCIONES POR PUERTO SON SOLO POR FLANCO

 \*

 \*      FLAGS DE INTERRUPCION

 \*

 \*      EXTINT->INTR POR FLANCO O POR NIVEL

 \*      EXTMODE -> edge or level-senitive

 \*      EXTPOLARx-> depende que eliga en el mode / puedo generar una intrr para cada flanco

 \*      en el handler\_ debo limpiar EINT0 ->(hay FLAGS PERIFERICO Y NVIC) creo que esta es del nvic

 \*

 \*      #EMBEBIDO-> debe tener un SLEEP

 \*     	SCR bit assignemeds

 \*

 \*     	SLEEPDEEP-> SOLO DEL CORE

 \*     	SLEEPONEXIT-> Duerme cuando no hay una interrupcion duerme, depierta cuando sale de la interrupc

 \*     	\_-------\_\_\_\_-\_\_\_\_\_\_\_\_--\_\_\_\_--\_\_\_\_\_\_\_-\_\_\_

 \*

 \*     				while(1){

 \*     					\_\_WFI();      ->Wait for exeption.(todas exc e intrr)

 \*     			    }

 \*

 \*

 \*     	SOLO SE PUEDEN USAR DRIVERS DE core\_m3.h

 \*     	Interrupciones de puerto -> atendidas por el handler de la linea EXT3

 \*     	--funcion-----NVIC\_DISEMBERIRQ(puedo pasar el parametro o numero)

 \*     	(VER TODAS LAS QUE HAY)

 \*

 \*/

