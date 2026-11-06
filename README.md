<div align="right">
    <img width="32px" src="img/algo2.svg">
</div>

# TP

> [!IMPORTANT]
> Esto es una plantilla del informe donde cada sección está delimitada por su título. Se recomienda mantener las secciones y tomar los ejemplos de las mismas para hacer el informe. El contenido de las secciones y comentarios como este deben ser eliminados del informe presentado.

## Información del estudiante

* (Nombre y Apellido)
* (Padrón)
* (Mail)
* (Username de GitHub)

---

> [!WARNING]
> Tener en cuenta que el informe se solicita en el ámbito universitario; el texto debe ser coherente, gramatical y ortográficamente correcto y con vocabulario adecuado para dicho contexto.

## Índice
* [1. Instrucciones](#1-Instrucciones)
  * [1.1. Compilar el proyecto](#11-Compilar-el-proyecto)
  * [1.2. Ejecutar las pruebas](#12-Ejecutar-las-pruebas)
  * [1.3. Ejecutar el programa con Valgrind](#13-Ejecutar-el-programa-con-Valgrind)
* [2. Funcionamiento](#2-Funcionamiento)
* [3. Estructura](#3-Estructura)
  * [3.1. Diagrama de memoria](#31-Diagrama-de-memoria)
  * [3.2. Análisis de complejidades](#32-Análisis-de-complejidades)
* [4. Decisiones de diseño y/o complejidades de implementación](#4-Decisiones-de-diseño-yo-complejidades-de-implementación)
* [5. Respuestas a las preguntas teóricas](#5-Respuestas-a-las-preguntas-teóricas)

## 1. Instrucciones

> [!TIP]
> Se recomienda fuertemente crear y usar un Makefile y colocar en esta sección los comandos Make.

### 1.1. Compilar el proyecto
```bash
comando
```

### 1.2. Ejecutar las pruebas
```bash
comando
```

### 1.3. Ejecutar el programa con Valgrind
```bash
comando
```

## 2. Funcionamiento
Explicar **qué** hace el TP implementado, aclarando todas las decisiones de funcionamiento que no estaban definidas por el enunciado. Se deben incluir todos los diagramas que consideren necesarios para explicar el funcionamiento del programa.

> [!IMPORTANT]
> Es muy importante entender la *diferencia entre qué y cómo*. En esta sección **NO** se busca una explicación de cómo implementaste el programa, qué funciones usaste, en qué línea, etc.; se busca una explicación de **qué** es lo que hace el programa en líneas generales. 

> [!WARNING]
> Es importante usar diagramas para explicar los conceptos de forma clara, pero el exceso será negativo. Los diagramas deben tener un fin explicativo y, por lo general, sirven para reemplazar uno o múltiples párrafos de explicación.

## 2. Funcionamiento (EJEMPLO)
El programa recibe 7 números del usuario y una vez obtenidos todos los muestra en pantalla. Para esto define un vector estático de 7 elementos y llena el mismo con los datos que inserta el usuario; cuando termina de insertar todos los números procede a imprimirlos en pantalla.
<div align="center">
  <img src="img/diagrama_flujo_programa.svg" width="70%">
  <p>Diagrama de flujo del programa explicado con más detalle.</p>
</div>

## 3. Estructura
Explicar cómo se implementó la/s estructura/s pedida/s en el [enunciado](./ENUNCIADO.md). En esta sección el objetivo es explicar en líneas generales, no técnicas, qué contiene la estructura, para qué y por qué.

## 3. Estructura (EJEMPLO)
Para implementar la estructura decidí hacerlo con un campo..., además tiene un puntero que... y eso permite que....

### 3.1. Diagrama de memoria
Realizar un diagrama de memoria de la estructura de memoria durante la ejecución del programa, esto debe incluir el stack y el heap con las estructuras contenidas en ellos.

### 3.1 Diagrama de memoria (EJEMPLO)
<div align="center">
  <img src="img/diagrama_memoria__1.svg" width="70%">
  <p>Diagrama de memoria de la estructura.</p>
</div>


### 3.2. Análisis de complejidades
Explicar las complejidades computacionales de las primitvas implementadas en el TP (las funciones del .h) en notación Big-O, justificando por qué cada una tiene esa determinada complejidad.

### 3.2. Análisis de complejidades (EJEMPLO 1)

* `fun1` tiene una complejidad de $O(1)$ ya que tiene como parámetro... y, al leer una línea....
* `fun2` tiene una complejidad de $O(n)$ ya que tiene como parámetro..., la cual....
* `fun3` tiene una complejidad de $O(n^2)$ ya que tiene como parámetro... y se encarga de....

### 3.2. Análisis de complejidades (EJEMPLO 2)

|      Función      |Complejidad|                 Justificación                  |
|:-----------------:|:---------:|:----------------------------------------------:|
|      `fun1`       |  $O(1)$   |Tiene como parámetro... y, al leer una línea....|
|      `fun2`       |  $O(n)$   |Tiene como parámetro..., la cual....            |
|      `fun3`       |  $O(n^2)$ |Tiene como parámetro... y se encarga de....     |

## 4. Decisiones de diseño y/o complejidades de implementación
Explicar las decisiones de diseño y/o las complejidades de implementación que hubo durante la resolución del TP.

## 4. Decisiones de diseño y/o complejidades de implementación (EJEMPLO)
La mayor complejidad en el TP se encuentra en la función `foo` que requiere hacer...; es por esto que decidí.... Además, decidí que el programa haga... para mejorar la implementación.

## 5. Respuestas a las preguntas teóricas 

### 5.1 Cambios en el TP1
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

### 5.2 Menu: 
#### 5.2.1 ¿Que es el menu? 
El menu es un TDA que unicamente se encarga de guardar opciones, operar con la seleccion y responde preguntas. El problema que viene a solucionar es que en este determiando TP, tengo dos interfaces para un mismo menu. Si lo pensaramos de una forma tradicional en donde cada una tiene sus medios y sus formas, deberia realizar 2 funciones por cada misma accion que quiero realizar, una para una interfaz grafica y la otra para la consola. 
Entonces decidi realizar el menu de la forma una forma generica de manera tal que pueda ser consumido por cualquier interfaz/usuario que quiera emplear el menu. Para llevar esto a cabo, el Menu no se puede encargar de las tipicas acciones, como leer, dibujar, escribir, el TDA unicamente cumple el proposito de representar la estructura y ejecutar la logica, mediante punteros a funcion y devolver los resultados obtenidos para que la interfaz sea quien decide hacer con los resultados obtenidos. La comunicacion del menu con el consumidor del mismo, se realiza mediante enums de resultados, el menu de lo unico que se encarga es de actuar y comunicar resultados. La decision de que hacer con ese resultado obtenido queda a cargo de la interfaz que lo utilice. 


#### 5.2.2 Estructura
El menu es un TDA compuesto por una lista de opciones y un indice el cual indica cual es la posicion de la opcion seleccionada actualmente. 

Esta compuesto principalmente de una lista, debido a que las principales operaciones que se realizan con el mismo, son de recorrer las diferentes opciones u obtener la seleccionada. Con una lista al recorrer se obtiene una complejidad 0(N), pero considerando en que contexto se tiene que aplicar, en un menu con tan pocas opciones la complejidad en el peor caso, nunca supera un nivel muy alto. Es por esto que decidi que el Menu sea una lista, y que cada elemento de la lista sea una Opcion.

Cada opcion esta compuesta de una tecla asociada, un texto descriptivo de la accion, una funcion y un contexto. En un prinicipio decidi que cada opcion tenga un campo booleado indicando si estaba seleccionada o no, pero esto conllevaba a que pueda haber mas de una opcion seleccionada, lo cual para un menu no tenia logica.
Por ende opte que la seleccion sea un indice asociado a la opcion seleccionada en el momento. 


#### 5.2.3 Decisiones que tome al diseñar el TDA:

- Las teclas se distinguen entre Mayusculas y Minusculas ('j' y 'J' son distintos). La normalizacion de la tecla depende de quien utilice el menu.
- No se puede repetir teclas, en caso de querer agregar dos opciones con teclas iguales falla la insersion.
- Se realiza una copia del texto original, en caso de que el usuario modifique o libere el texto, no afecta al TDA. La copia es liberada por el menu.
- La seleccion se realiza de manera circular. 
- Existe en el menu, un campo que indica cual es la opcion seleccionada actualmente.
- Los retornos de ejecutar, ya sea por tecla o por seleccionada, devuelven un enum, el cual contiene las diferentes posibles respuestas al ejecutar una opcion. 


#### 5.2.3 Complejidades 

* `menu_crear` tiene una complejidad de $O(1)$ ya que unicamente se realizan una serie finitas de instrucciones, solicitando memoria e inicializando variables.
* `menu_agregar` tiene una complejidad de $O(n)$ debido a que para agregar una nueva opcion en una primera instancia se verifica que la tecla asociada a esa opcion, no se encuentre asociada a otra opcion del menu, para esto se realiza una comparacion con cada opcion del menu hasta encontrarlo o hasta recorrer los N elementos. Posteriormente se realizan solicitudes de memoria y una copia de un texto pero al final la nueva opcion se agrega al final del Menu, por ende para insertarlo en esa posicion tengo que recorrer los N elementos contenidos en el Menu.   
* `menu_cantidad` tiene una complejidad de $O(1)$ debido a que unicamente consulta la cantidad de elementos contenidos en el Menu, y eso implica simplemente consultar un campo de la lista.
* `menu_mover_seleccion` tiene una complejidad de $O(1)$ debido a que unicamente se realiza una actualizacion del campo que indica cual es la opcion seleccionada.
* `menu_seleccionada` tiene una complejidad de $O(1)$ debido a que unicamente consulta el campo que indica cual opcion esta seleccionada.
* `menu_ejecutar` tiene una complejidad de $O(n)$ ya que a pesar de que ejecutar una determinada opcion conlleva una complejidad $O(1)$, primero hay que verificar que la tecla ingresada este asociada a una opcion, es por esto que se realiza una busqueda en la lista. Los peores casos al realizar esa busqueda es recorrer todos los elementos y que el elemento buscado se encuentre en la ultima posicion o que directamente no se encuentre. Ambos casos realizan N recorridos, es por esto que la complejidad termina siendo $O(n)$.
* `menu_ejecutar_seleccionada` tiene una complejidad de $O(n)$ debido a que se realiza la obtencion de la opcion seleccionada asociada a un indice. Para esta obtencion se realiza un recorrido hasta la posicion obtenida. El peor de los casos es que la posicion hasta la cual se tiene que iterar, sea la ultima posicion posible, y para llegar a ella hay que recorrer N elementos. 
* `menu_iterar` tiene una complejidad de $O(n)$ debido a que se realiza una iteracion de las opciones del menu utilizando lista_iterar() con cada opcion adaptada al formato del iterador de la lista utilizando una funcion intermedia. 
* `menu_destruir` tiene una complejidad de $O(n)$ ya que para liberar el menu, se necesita primero destruir y liberar cada elemento de la lista. Para esto se lleva a cabo un recorrido por los N elementos contenidos en la lista. 


#### 5.2.4 Problemas al implementar

Complejidad en Menu iterar: para desarrollar el iterador interno del menu, en un principio tome la decision de implementar un codigo el cual itere por la cantidad de elementos en el menu, en cada iteracion, tenia que utilizar lista_obtener con la posicion indicada del elemento, y posteriormente aplicar la funcion. Esto en un menu de pocas opciones puede llegar a ser viable, pero en un menu de muchas opciones, realizar una doble iteracion, al recorrer cada elemento y posteriormente recorrer la lista buscando cada elemento conlleva una complejidad o(n[2]). Para evitar esto, tengo que utilizar la funcion lista_iterar(), y una funcion intermedia la cual se encargue de adaptar mis parametros actuales a lo que acepta lista_iterar. Es por esto que cree iterar_opcion la cual recibe el contexto de un elemento, lo procesa, y devuelve el resultado de efectuar la operacion. A partir de esto se logra obtener una reduccion de complejidad debido a que cada nodo se visita una unica vez. 

Decision de tener indice_seleccionada: en una primera instancia de la implementacion, decidi que adentro del struct opcion, haya un campo el cual indicaba si la opcion estaba seleccionada o no mediante un booleano. Esto conllevaba a la posibilidad de que haya dos opciones con el estado seleccionada, lo cual no tiene logica en el contexto de un menu. Ademas, me generaba un problema en el momento en el cual queria cambiar de seleccion, porque para cambiar de seleccion tenia que obtener el elemento seleccionado, cambiarle el valor del booleano, insertarlo, ir al siguiente elemento a seleccionar y repetir el proceso, lo cual implicaba una logica grande. En cambio al optar por que el estado seleccionado, sea solamente un campo indicativo externo a la opcion, y que sea un indice el cual indica que posicion esta seleccionada actualmente. 

### 5.3 TP2
El motivo fue....
