#include "tp1.h"
#include "menu.h"

/*
 * Ejecuta continuamente el juego por la terminal. Genera un menu al cual se le cargan las opciones del juego, la memoria del menu es manejada por la funcion misma.
 * Es indistinto ingresar una tecla en Minuscula o Mayuscula al seleccionar opciones en el menu. La busqueda de un pokemon se hace por el nombre ingresado exacto.
 * En caso de error devuelve false.
 */
bool consola_ejecutar(tp1_t *pokedex);