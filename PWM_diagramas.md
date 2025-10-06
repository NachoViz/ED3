PWM->  Podemos controlar la insensidad del a señal en un periodo definido donde el pulso representaría cuanto tiempo de trabajo realizo con el motor o diodo.

\_\_\_----\_\_\_\_

  50%  T



Ejercicio de prueba

dos detectores en punt oa y punto b donde mediante un pendulo detecte cuando la pelota llegue a cada punto



1ms

24 bit cuenta el Systick



uint\_32->llega a 32 bits

int->16 bits



static-> solo la puedo usar dentro del main y no se puede modificar desde otras funciones



volatile



\#las pull-up están seteadas por defecto



Diagrama de flujo



 	main

 	 |

     Conf syst

 	 |

     EINT 0/1

      pinsel

      pinmode

      SC->EXTPOLAR

        ->EXTMODE

 	    ->EXTINT
        | 
 	    |

      NVIC

       ISER

      NVIC\_ENABLE(EINT0\_IRQn)

 	 |

        LED

 	 |

       IF=1 <-------

 	 |	   |

 	  ----------

   \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

   | Systick\_handler |

 	 |

     cpint dev++

         |

      toggle\_led

 	 |

      EINT0\_Handler

 	 |

      Flanco1 = count dev

         |

     Bajando bandera



     \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

    |EINT1\_Handler()|

 	   |

     Bajamos bandera0

           |

     Flanco2 = contador

           |

       PRINTS



encoder-> investigar como se usa

