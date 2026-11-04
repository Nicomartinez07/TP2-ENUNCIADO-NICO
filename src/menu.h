#ifndef MENU_H_
#define MENU_H_

#include <stdlib.h>
#include <stdbool.h>

enum menu_resultado { MENU_SEGUIR, MENU_TERMINAR, MENU_ERROR, MENU_NO_EXISTE };

enum menu_direccion { MENU_SIGUIENTE, MENU_ANTERIOR };

typedef struct menu menu_t;

/*
 * Función que el menu ejecuta sobre una opcion. A implementar por el usuario
 *
 * Debe devolver 0 para seguir o cualquier otro valor para terminar.
 */
typedef int (*menu_accion_t)(void *ctx);

/*
 * Crea un menu y lo devuelve. Devuelve NULL en caso de error.
 */
menu_t *menu_crear();

/*
 * Inserta un elemento en el menu y devuelve true si pudo.
 * 
 * En caso de insertar dos elementos con igual tecla retorna false. Se crea una copia del texto ingresado que posteriormente es liberado por el TDA.
 *
 * Si no puede insertar devuelve false.
 */
bool menu_agregar(menu_t *menu, char tecla, char *texto, menu_accion_t funcion, void *contexto);

/*
 * Devuelve la cantidad de opciones que hay en el menu. Devuelve 0 en caso de error
 */
size_t menu_cantidad(menu_t *menu);

/*
 * Mueve la selección a la opción siguiente o anterior. Devuelve true si se pudo realizar el movimiento.
 *
 * Devuelve false en caso de error
 */
bool menu_mover_seleccion(menu_t *menu, enum menu_direccion direccion);

/*
 * Deveulve la posicion de la opcion seleccionada. Encontrada tiene que estar inicializada en false.
 * En caso de error devuelve 0.
 */
size_t menu_seleccionada(menu_t *menu, bool *encontrada);

/*
 * Ejecuta la opcion relacionada a la tecla ingresada.
 *
 * Devuelve seguir o terminar dependiendo lo que devuelve la acción,
 * no_existe si no hay una opcion con esa tecla asociada, o error si menu es NULL.
 */
enum menu_resultado menu_ejecutar(menu_t *menu, char tecla);

/*
 * Ejecuta la opcion seleccionada del menu.
 * 
 * Devuelve seguir o terminar dependiendo lo que devuelve la acción,
 * no_existe si el menú está vacío, o error si menu es NULL.
 */
enum menu_resultado menu_ejecutar_seleccionada(menu_t *menu);

/*
 * Recorre el menu aplicando la función f.
 *
 * Si f devuevle false, se deja de iterar.
 *
 * Devuelve la cantidad de veces que fue invocada f o 0 en caso de error
 */
size_t menu_iterar(menu_t *menu, bool (*f)(char tecla, char *texto, bool seleccionada, void *contexto), void *extra);

/*
 * Libera el menu y toda la memoria asociada.
 */
void menu_destruir(menu_t *menu);

#endif // MENU_H_