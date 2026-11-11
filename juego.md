8- Un pokemon no puede aparecer 2 veces en una partida.

La dificultad hace un cambio en la cantidad de pokemones, y la velocidad, hay 2 opciones de dificultad, facil o dificil
En facil va a haber 3 pokemones, con una velocidad x
En cambio en dificil podria ser que hayan 5 pokemones y con una velocidad mayor a la anterior

Mostrare la rareza con la opcion A, en nombre con engine_texto en un color por rareza

No entiendo a que te referis con formas tipo lo lei del enunciado pero no se a que refiere

Las preguntas que va a tener mi pool van a ser
- **¿Cuántos pokemon totales viste pasar?**
- **¿Cuántos pokemon legendarios viste?**
- **¿Cuál de estos pokemon fue el mas rápido?**
- **¿Cuántos pokemon viste pasar de derecha a izquierda?**
- **¿Cuál de estos pokemon fue el mas lento?**
- **¿Cuántos pokemon comunes viste?**


Jugar con semilla en consola directamente muestra el aviso





Decisiones de diseño:

informacion.h

Basicamente es una funcion la cual obtiene toda la informacion de la pokedex necesaria para el la opcion del juego (I). 
La informacion esta almacenada en un struct pokedex_info el cual contiene toda la informacion necesaria para el muestro de datos sobre el juego. Lo que hace esta funcion es una iteracion de la pokedex, con tp1_iterar, la funcion que hace la acumulacion de la informacion recibe el pokemon actual y un contexto en el cual se encuentran los punteros y los contadores de cada rareza. 
Es necesario pasar este struct de contexto debido a que al iterar solamente se puede pasar un puntero extra y para poder recolectar toda la informacion en una sola pasada, se necesita una estructura que contenga todos los datos posibles. 

Como la informacion se recolecta solamente en un recorrido la complejidad es o(n). 

