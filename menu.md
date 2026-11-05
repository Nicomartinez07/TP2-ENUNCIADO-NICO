- Explique cómo funciona el menú y cómo abstrae el problema de la independencia de la interfaz gráfica.




# Estructura
El menu es un TDA compuesto por una lista de opciones y un indice el cual indica cual es la posicion de la opcion seleccionada actualmente. 

Esta compuesto principalmente de una lista, debido a que las principales operaciones que se realizan con el mismo, son de recorrer las diferentes opciones u obtener la seleccionada. Con una lista al recorrer se obtiene una complejidad 0(N), pero considerando en que contexto se tiene que aplicar, en un menu con tan pocas opciones la complejidad en el peor caso, nunca supera un nivel muy alto. Es por esto que decidi que el Menu sea una lista, y que cada elemento de la lista sea una Opcion.

Cada opcion esta compuesta de una tecla asociada, un texto descriptivo de la accion, una funcion y un contexto. En un prinicipio decidi que cada opcion tenga un campo booleado indicando si estaba seleccionada o no, pero esto conllevaba a que pueda haber mas de una opcion seleccionada, lo cual para un menu no tenia logica.
Por ende opte que la seleccion sea un indice asociado a la opcion seleccionada en el momento. 


# Decisiones que tome al diseñar el TDA:

- Las teclas se distinguen entre Mayusculas y Minusculas ('j' y 'J' son distintos). La normalizacion de la tecla depende de quien utilice el menu.
- No se puede repetir teclas, en caso de querer agregar dos opciones con teclas iguales falla la insersion.
- Se realiza una copia del texto original, en caso de que el usuario modifique o libere el texto, no afecta al TDA. La copia es liberada por el menu.
- La seleccion se realiza de manera circular. 
- Existe en el menu, un campo que indica cual es la opcion seleccionada actualmente.
- Los retornos de ejecutar, ya sea por tecla o por seleccionada, devuelven un enum, el cual contiene las diferentes posibles respuestas al ejecutar una opcion. 


# Complejidades 

* `menu_crear` tiene una complejidad de $O(1)$ ya que unicamente se realizan una serie finitas de instrucciones, solicitando memoria e inicializando variables.
* `menu_agregar` tiene una complejidad de $O(n)$ debido a que para agregar una nueva opcion en una primera instancia se verifica que la tecla asociada a esa opcion, no se encuentre asociada a otra opcion del menu, para esto se realiza una comparacion con cada opcion del menu hasta encontrarlo o hasta recorrer los N elementos. Posteriormente se realizan solicitudes de memoria y una copia de un texto pero al final la nueva opcion se agrega al final del Menu, por ende para insertarlo en esa posicion tengo que recorrer los N elementos contenidos en el Menu.   
* `menu_cantidad` tiene una complejidad de $O(1)$ debido a que unicamente consulta la cantidad de elementos contenidos en el Menu, y eso implica simplemente consultar un campo de la lista.
* `menu_mover_seleccion` tiene una complejidad de $O(1)$ debido a que unicamente se realiza una actualizacion del campo que indica cual es la opcion seleccionada.
* `menu_seleccionada` tiene una complejidad de $O(1)$ debido a que unicamente consulta el campo que indica cual opcion esta seleccionada.
* `menu_ejecutar` tiene una complejidad de $O(n)$ ya que a pesar de que ejecutar una determinada opcion conlleva una complejidad $O(1)$, primero hay que verificar que la tecla ingresada este asociada a una opcion, es por esto que se realiza una busqueda en la lista. Los peores casos al realizar esa busqueda es recorrer todos los elementos y que el elemento buscado se encuentre en la ultima posicion o que directamente no se encuentre. Ambos casos realizan N recorridos, es por esto que la complejidad termina siendo $O(n)$.
* `menu_ejecutar_seleccionada` tiene una complejidad de $O(n)$ debido a que se realiza la obtencion de la opcion seleccionada asociada a un indice. Para esta obtencion se realiza un recorrido hasta la posicion obtenida. El peor de los casos es que la posicion hasta la cual se tiene que iterar, sea la ultima posicion posible, y para llegar a ella hay que recorrer N elementos. 
* `menu_iterar` tiene una complejidad de $O(n)$ ya que se itera el menu aplicandole la funcion, hasta que algun elemento devuelve false. El peor caso es que ningun elemento devuelva false por ende se recorren todos los elementos.
* `menu_destruir` tiene una complejidad de $O(n)$ ya que para liberar el menu, se necesita primero destruir y liberar cada elemento de la lista. Para esto se lleva a cabo un recorrido por los N elementos contenidos en la lista. 




¿Por qué no alcanza con “poner el menú en una función”? Acá va lo del flujo de control. La consola es bloqueante (vos llamás a scanf y esperás). El engine invierte el control: él te llama a vos en cada frame, y no te podés bloquear. Por eso el TDA no puede tener el loop adentro ni hacer entrada/salida. Es el argumento más fino del informe. Si lo explicás bien, se nota que entendiste el problema de fondo.

¿Qué hace el TDA y qué no hace? Guarda las opciones y la selección, y responde consultas. No imprime, no lee el teclado, no conoce el juego. Una forma clara de decirlo es separar modelo y vista: el TDA es el modelo, y consola y engine son dos vistas del mismo modelo.

¿Cómo ejecuta acciones sin conocer el juego? Con punteros a función y un void *contexto por opción. Mencioná que es el mismo mecanismo que usa el engine con engine_frame_t y su ctx. Usar un ejemplo que el corrector ya conoce ayuda mucho.

¿Cómo se comunica el menú con quien lo usa? El enum menu_resultado: por qué un bool no alcanzaba (seguir, terminar, opción inexistente y error son cuatro casos distintos), y que el menú solo propaga el pedido de terminar, la decisión la toma la interfaz.

¿Cómo lo usa cada interfaz? Un párrafo corto por interfaz. Por ejemplo, “la consola lee una tecla y llama a ejecutar”. Y el engine: “en cada frame traduce las flechas a mover selección, el Enter a ejecutar la seleccionada y dibuja con iterar”. Acá es muy útil la opción Jugar (J), que hace cosas distintas según la interfaz: demuestra que las acciones tienen que venir de afuera.