El cambio mas significativo que realice en el TP1, es el cambio de estructura, al pasar de un vector dinamico de pokemones a una lista compuesta por pokemones.
Este cambio lo que me permite es realizar las operaciones solicitadas, de una manera mas sencilla debido a que el TDA Lista, me brinda primitivas lo que me posibilitan tener un nivel superior de abstraccion al no tener que estar pendiente por ejemplo, de como insertar un Pokemon en la estructura.

Ademas del condicionamieto de las funciones, a la nueva estructura, realice correciones que podian conllevar a errores o complejizar la lectura del codigo.

* 'strcasecmp': Debido a que utilice una funcion no contenida en la biblioteca estandar de C99, la reemplace con una funcion comparadora, que utiliza tolower() (funcion que convierte un caracter a minuscula). La funcion recorre con aritmetica de punteros los dos strings ingresados por parametro, conviritiendo sus caracteres a minusculas y verificando si son el mismo string. En caso de que no lo sean, devuelve el resultado de la resta de los codigos ASCI de ambos caracteres. 

* 'Condiciones de corte': Hice correciones en las condiciones de corte de ciclos iterativos, debido a que simplemente se podian reescribir la condiciones de iteracion y funcionaba de igual manera. Esto ayuda a tener un codigo mucho mas lejible. 

* 'Liberar memoria': decidi modularizar el proceso de liberar en particular cada pokemon, debido a que se puede reutilizar en diferentes funciones, invocandola como destructor en lista_destruir_todo()

* 'Guardar_pokemones': Realice una modularizacion de la funcion que se encarga de procesar el archivo para guardarlo en la estructura. Ahora la funcion se puede dividir dos en etapas.
 La primera es el parseo de la linea actual, en este parseo se genera el pokemon correspondiente a la linea actual. Para esto se obtiene el nombre del pokemon con la funcion obtener_nombre_pokemon(), posteriormente se obtiene el resto de las caracteristicas del pokemon y se verifica que sea un pokemon valido.
 La segunda etapa consta de una insersion del pokemon obtenido previamente. Para ello se realiza una busqueda del mismo, en caso no encontrarlo, se guarda el pokemon en la posicion correspondiente para que la estructura mantega el orden alfabetico.
 Realizar una modularizacion en la funcion guardar_pokemones() me ayudo mucho a mantener una prolijidad del codigo en general, debido que era una funcion de mas de 100 lineas de codigo, lo que conllevaba a ser dificl de leerla.

* 'tp1_combinar': Realice una modularizacion de la funcion, debido a que a pesar de que no era muy larga, se repetia mucho un proceso en comun. 
Ahora la funcion itera ambos TP1, obtiene cada pokemon y realiza una comparacion. Posterior a eso dependiendo del resultado de la comparacion, inserta el pokemon correspondiente a uno de los dos TP1, generando una copia del pokemon original y insertandolo en la lista.
A pesar de que modularizar la funcion, no aporto un cambio significativo como al modularizar guardar_pokemones, ayuda al entendimiento del codigo de una manera mas sencilla

* 'leer_linea.c': Realice una modularizacion en la funcion leer_linea() debido a que se podia reutilizar leer_linea_ptr() para retornar un string en la funcion leer_linea().