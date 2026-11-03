#include "src/menu.h"
#include "src/lista.h"

struct menu {
    lista_t *opciones;
};

typedef struct opcion {
	char tecla;
    char *texto;
    bool seleccionada;
    int (*f)(void* , void*);
    void *contexto;
} opcion_t ;

/*
 * Copia el texto recibido por parametros
 */
char *copiar_texto(char *texto)
{
	size_t longitud = strlen(texto);
	char *copia = malloc(sizeof(char) * longitud + 1);
	if (!copia)
		return NULL;

	strcpy(copia, texto);

	return copia;
}


/*
 * Crea un menu y lo devuelve. Devuelve NULL en caso de error.
 */
menu_t *menu_crear() {
    menu_t *menu = malloc(sizeof(menu_t));
    if(!menu) return NULL;

    menu->opciones = lista_crear();
    if(!menu->opciones) {
        free(menu);
        return NULL;
    }

    return menu;
}

/*
 * Inserta un elemento en el menu y devuelve true si pudo.
 * 
 * En caso de insertar dos elementos con igual tecla retorna false. Se crea una copia del texto ingresado que posteriormente es liberado por el TDA.
 *
 * Si no puede insertar devuelve false.
 */
bool menu_agregar(menu_t *menu, char tecla, char *texto, menu_accion_t funcion, void *contexto) {
    if(!menu || !texto || !funcion) return NULL;

    bool pudo_insertar = true;


    char *copia = copiar_texto(texto);
    if(!copia) return false; 

    opcion_t *opcion = malloc(sizeof(opcion_t));
    if(!opcion) {
        free(copia);
        return false;
    }

    opcion->tecla = tecla;
    opcion->texto = copia;
    opcion->seleccionada = false;
    opcion->f = funcion;
    opcion->contexto = contexto;

    pudo_insertar = lista_insertar(menu->opciones, opcion, lista_cantidad(menu->opciones));

    if(!pudo_insertar) {
        free(copia);
        free(opcion);
    }

    return pudo_insertar;
}

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
 * Deveulve la posicion de la opcion seleccionada.
 * En caso de error devuelve 0.
 */
size_t menu_seleccionada(menu_t *menu);

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
