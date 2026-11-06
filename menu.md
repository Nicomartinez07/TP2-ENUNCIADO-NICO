# 5.2.1 ¿Que es el menu? 
El menu es un TDA que unicamente se encarga de guardar opciones, operar con la seleccion y responde preguntas. El problema que viene a solucionar es que en este determiando TP, tengo dos interfaces para un mismo menu. Si lo pensaramos de una forma tradicional en donde cada una tiene sus medios y sus formas, deberia realizar 2 funciones por cada misma accion que quiero realizar, una para una interfaz grafica y la otra para la consola. 
Entonces decidi realizar el menu de la forma una forma generica de manera tal que pueda ser consumido por cualquier interfaz/usuario que quiera emplear el menu. Para llevar esto a cabo, el Menu no se puede encargar de las tipicas acciones, como leer, dibujar, escribir, el TDA unicamente cumple el proposito de representar la estructura y ejecutar la logica, mediante punteros a funcion y devolver los resultados obtenidos para que la interfaz sea quien decide hacer con los resultados obtenidos. La comunicacion del menu con el consumidor del mismo, se realiza mediante enums de resultados, el menu de lo unico que se encarga es de actuar y comunicar resultados. La decision de que hacer con ese resultado obtenido queda a cargo de la interfaz que lo utilice. 


# 5.2.2 Estructura
El menu es un TDA compuesto por una lista de opciones y un indice el cual indica cual es la posicion de la opcion seleccionada actualmente. 

Esta compuesto principalmente de una lista, debido a que las principales operaciones que se realizan con el mismo, son de recorrer las diferentes opciones u obtener la seleccionada. Con una lista al recorrer se obtiene una complejidad 0(N), pero considerando en que contexto se tiene que aplicar, en un menu con tan pocas opciones la complejidad en el peor caso, nunca supera un nivel muy alto. Es por esto que decidi que el Menu sea una lista, y que cada elemento de la lista sea una Opcion.

Cada opcion esta compuesta de una tecla asociada, un texto descriptivo de la accion, una funcion y un contexto. En un prinicipio decidi que cada opcion tenga un campo booleado indicando si estaba seleccionada o no, pero esto conllevaba a que pueda haber mas de una opcion seleccionada, lo cual para un menu no tenia logica.
Por ende opte que la seleccion sea un indice asociado a la opcion seleccionada en el momento. 


# 5.2.3 Decisiones que tome al diseñar el TDA:

- Las teclas se distinguen entre Mayusculas y Minusculas ('j' y 'J' son distintos). La normalizacion de la tecla depende de quien utilice el menu.
- No se puede repetir teclas, en caso de querer agregar dos opciones con teclas iguales falla la insersion.
- Se realiza una copia del texto original, en caso de que el usuario modifique o libere el texto, no afecta al TDA. La copia es liberada por el menu.
- La seleccion se realiza de manera circular. 
- Existe en el menu, un campo que indica cual es la opcion seleccionada actualmente.
- Los retornos de ejecutar, ya sea por tecla o por seleccionada, devuelven un enum, el cual contiene las diferentes posibles respuestas al ejecutar una opcion. 


# 5.2.3 Complejidades 

* `menu_crear` tiene una complejidad de $O(1)$ ya que unicamente se realizan una serie finitas de instrucciones, solicitando memoria e inicializando variables.
* `menu_agregar` tiene una complejidad de $O(n)$ debido a que para agregar una nueva opcion en una primera instancia se verifica que la tecla asociada a esa opcion, no se encuentre asociada a otra opcion del menu, para esto se realiza una comparacion con cada opcion del menu hasta encontrarlo o hasta recorrer los N elementos. Posteriormente se realizan solicitudes de memoria y una copia de un texto pero al final la nueva opcion se agrega al final del Menu, por ende para insertarlo en esa posicion tengo que recorrer los N elementos contenidos en el Menu.   
* `menu_cantidad` tiene una complejidad de $O(1)$ debido a que unicamente consulta la cantidad de elementos contenidos en el Menu, y eso implica simplemente consultar un campo de la lista.
* `menu_mover_seleccion` tiene una complejidad de $O(1)$ debido a que unicamente se realiza una actualizacion del campo que indica cual es la opcion seleccionada.
* `menu_seleccionada` tiene una complejidad de $O(1)$ debido a que unicamente consulta el campo que indica cual opcion esta seleccionada.
* `menu_ejecutar` tiene una complejidad de $O(n)$ ya que a pesar de que ejecutar una determinada opcion conlleva una complejidad $O(1)$, primero hay que verificar que la tecla ingresada este asociada a una opcion, es por esto que se realiza una busqueda en la lista. Los peores casos al realizar esa busqueda es recorrer todos los elementos y que el elemento buscado se encuentre en la ultima posicion o que directamente no se encuentre. Ambos casos realizan N recorridos, es por esto que la complejidad termina siendo $O(n)$.
* `menu_ejecutar_seleccionada` tiene una complejidad de $O(n)$ debido a que se realiza la obtencion de la opcion seleccionada asociada a un indice. Para esta obtencion se realiza un recorrido hasta la posicion obtenida. El peor de los casos es que la posicion hasta la cual se tiene que iterar, sea la ultima posicion posible, y para llegar a ella hay que recorrer N elementos. 
* `menu_iterar` tiene una complejidad de $O(n)$ debido a que se realiza una iteracion de las opciones del menu utilizando lista_iterar() con cada opcion adaptada al formato del iterador de la lista utilizando una funcion intermedia. 
* `menu_destruir` tiene una complejidad de $O(n)$ ya que para liberar el menu, se necesita primero destruir y liberar cada elemento de la lista. Para esto se lleva a cabo un recorrido por los N elementos contenidos en la lista. 


# 5.2.4 Problemas al implementar

Complejidad en Menu iterar: para desarrollar el iterador interno del menu, en un principio tome la decision de implementar un codigo el cual itere por la cantidad de elementos en el menu, en cada iteracion, tenia que utilizar lista_obtener con la posicion indicada del elemento, y posteriormente aplicar la funcion. Esto en un menu de pocas opciones puede llegar a ser viable, pero en un menu de muchas opciones, realizar una doble iteracion, al recorrer cada elemento y posteriormente recorrer la lista buscando cada elemento conlleva una complejidad o(n[2]). Para evitar esto, tengo que utilizar la funcion lista_iterar(), y una funcion intermedia la cual se encargue de adaptar mis parametros actuales a lo que acepta lista_iterar. Es por esto que cree iterar_opcion la cual recibe el contexto de un elemento, lo procesa, y devuelve el resultado de efectuar la operacion. A partir de esto se logra obtener una reduccion de complejidad debido a que cada nodo se visita una unica vez. 

Decision de tener indice_seleccionada: en una primera instancia de la implementacion, decidi que adentro del struct opcion, haya un campo el cual indicaba si la opcion estaba seleccionada o no mediante un booleano. Esto conllevaba a la posibilidad de que haya dos opciones con el estado seleccionada, lo cual no tiene logica en el contexto de un menu. Ademas, me generaba un problema en el momento en el cual queria cambiar de seleccion, porque para cambiar de seleccion tenia que obtener el elemento seleccionado, cambiarle el valor del booleano, insertarlo, ir al siguiente elemento a seleccionar y repetir el proceso, lo cual implicaba una logica grande. En cambio al optar por que el estado seleccionado, sea solamente un campo indicativo externo a la opcion, y que sea un indice el cual indica que posicion esta seleccionada actualmente. 

