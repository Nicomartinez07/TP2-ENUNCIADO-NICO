#include "menu.h"
#include "lista.h"
#define NO_ENCONTRADO -1

#include <stdlib.h>
#include <string.h>


struct menu {
    lista_t *opciones;
    size_t indice_seleccionada;
};

typedef struct opcion {
	char tecla;
    char *texto;
    int (*f)(void*);
    void *contexto;
} opcion_t ;

void destruir_cada_opcion(void *elemento) {
    opcion_t *opcion = elemento;
    free(opcion->texto);
    free(opcion);
}

/*
 * Busca la opción asociada a la tecla. Devuelve NULL si no existe.
 */
opcion_t *buscar_opcion(menu_t *menu, char tecla)
{
	void *encontrada = NULL;
	lista_buscar(menu->opciones, &tecla, comparar_teclas, &encontrada);
	return encontrada;
}

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
 * Dado un elemento, y una tecla, retorna el resultado de la comparacion entre ambos.
 */
int comparar_teclas(void *elemento, void *buscado) {
    opcion_t *opcion = elemento;
    char *tecla = buscado;

    return (opcion->tecla - *tecla);
}

/*
 * Dada una opcion, ejecuta su accion utilizando el contexto. Retorna Seguir si el resultado de la opcion es 0, terminar en caso contrario. En caso de error devuelve no existe.
 */
enum menu_resultado ejecutar_opcion(opcion_t *opcion) {
    if(!opcion) return MENU_NO_EXISTE;

    enum menu_resultado resultado_de_ejecutar;

    int seguir = opcion->f(opcion->contexto);
    if(seguir == 0) {
        resultado_de_ejecutar = MENU_SEGUIR;
    } else {
        resultado_de_ejecutar = MENU_TERMINAR;
    }

    return resultado_de_ejecutar;
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

    menu->indice_seleccionada = 0;

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
    if(!menu || !texto || !funcion) return false;

    if(buscar_opcion(menu, tecla)) return false;

    opcion_t *opcion = malloc(sizeof(opcion_t));
    if(!opcion) return false;

    opcion->texto = copiar_texto(texto);
    if(!opcion->texto) {
        free(opcion);
        return false;
    }

    opcion->tecla = tecla;
    opcion->f = funcion;
    opcion->contexto = contexto;

    if(!lista_insertar(menu->opciones, opcion, lista_cantidad(menu->opciones))) {
        destruir_cada_opcion(opcion);
        return false;
    }

    return true;
}

/*
 * Devuelve la cantidad de opciones que hay en el menu. Devuelve 0 en caso de error
 */
size_t menu_cantidad(menu_t *menu) {
    if(!menu) return 0;

    return lista_cantidad(menu->opciones);
}

/*
 * Mueve la selección a la opción siguiente o anterior. Devuelve true si se pudo realizar el movimiento.
 *
 * Devuelve false en caso de error
 */
bool menu_mover_seleccion(menu_t *menu, enum menu_direccion direccion) {
    size_t cantidad = menu_cantidad(menu);
    if(cantidad == 0) return false;

    if(direccion == MENU_SIGUIENTE) {
        menu->indice_seleccionada = (menu->indice_seleccionada + 1) % cantidad;
    } else if (direccion == MENU_ANTERIOR){
        menu->indice_seleccionada = (menu->indice_seleccionada + cantidad - 1) % cantidad;
    } else {
        return false;
    }

    return true;
}

/*
 * Devuelve la posicion de la opcion seleccionada. 
 * En caso de error devuelve 0.
 */
size_t menu_seleccionada(menu_t *menu) {
    if(!menu) return 0;

    return menu->indice_seleccionada;
}

/*
 * Ejecuta la opcion relacionada a la tecla ingresada.
 *
 * Devuelve seguir o terminar dependiendo lo que devuelve la acción,
 * no_existe si no hay una opcion con esa tecla asociada, o error si menu es NULL.
 */
enum menu_resultado menu_ejecutar(menu_t *menu, char tecla) {
    if(!menu) return MENU_ERROR;

    return ejecutar_opcion(buscar_opcion(menu, tecla));
}


/*
 * Ejecuta la opcion seleccionada del menu.
 * 
 * Devuelve seguir o terminar dependiendo lo que devuelve la acción,
 * no_existe si el menú está vacío, o error si menu es NULL.
 */
enum menu_resultado menu_ejecutar_seleccionada(menu_t *menu) {
    if(!menu) return MENU_ERROR;

    opcion_t *opcion = lista_obtener(menu->opciones, menu->indice_seleccionada);

    return ejecutar_opcion(opcion);
}

/*
 * Recorre el menu aplicando la función f.
 *
 * Si f devuevle false, se deja de iterar.
 *
 * Devuelve la cantidad de veces que fue invocada f o 0 en caso de error
 */
size_t menu_iterar(menu_t *menu, bool (*f)(char tecla, char *texto, bool seleccionada, void *contexto), void *extra) {
    if (!menu || !f)
		return 0;
	size_t contador = 0;
	bool seguir = true;

	while (contador < lista_cantidad(menu->opciones) && seguir) {
        opcion_t *opcion = lista_obtener(menu->opciones, contador);
		if(!opcion) {
			seguir = false;
		} else {
			seguir = f(opcion->tecla, opcion->texto, contador == menu->indice_seleccionada, extra);
			contador++;
		}
	}

	return contador;
}

/*
 * Libera el menu y toda la memoria asociada.
 */
void menu_destruir(menu_t *menu) {
    if(!menu) return;

    lista_destruir_todo(menu->opciones, destruir_cada_opcion);
    free(menu);
}
