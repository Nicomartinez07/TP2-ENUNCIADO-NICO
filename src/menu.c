#include "menu.h"
#include "lista.h"


#include <stdlib.h>
#include <string.h>

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

void destruir_cada_opcion(opcion_t *opcion) {
    free(opcion->texto);
    free(opcion);
}

const int NO_ENCONTRADO = -1;

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


int comparar_teclas(void *elemento, void *buscado) {
    opcion_t *opcion = elemento;
    char *tecla = buscado;

    return (opcion->tecla - *tecla);
}

enum menu_resultado ejecutar_opcion(opcion_t *opcion) {
    if(!opcion) return MENU_NO_EXISTE;

    enum menu_resultado resultado_de_ejecutar;

    bool seguir = f(opcion->tecla, opcion->texto, opcion->seleccionada, NULL);
    if(seguir) {
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

    bool pudo_insertar = true;


    char *copia = copiar_texto(texto);
    if(!copia) return false; 

    opcion_t *opcion = malloc(sizeof(opcion_t));
    if(!opcion) {
        free(copia);
        return false;
    }

    opcion_t *encontrada = NULL;
    if(lista_buscar(menu->opciones, &tecla, comparar_teclas, &encontrada)) {
        pudo_insertar = false;
    } else {
        opcion->tecla = tecla;
        opcion->texto = copia;
        opcion->seleccionada = false;
        opcion->f = funcion;
        opcion->contexto = contexto;

        pudo_insertar = lista_insertar(menu->opciones, opcion, lista_cantidad(menu->opciones));
    }

    if(!pudo_insertar) {
        free(copia);
        free(opcion);
    }

    return pudo_insertar;
}

/*
 * Devuelve la cantidad de opciones que hay en el menu. Devuelve 0 en caso de error
 */
size_t menu_cantidad(menu_t *menu) {
    if(!menu) return 0;

    return lista_cantidad(menu->opciones);
}

/*
 * Devuelve la posicion de la opcion seleccionada. Encontrada tiene que estar inicializada en false. 
 * En caso de error devuelve 0.
 */
size_t menu_seleccionada(menu_t *menu, bool *encontrada) {
    if(!menu || !encontrada) return 0;

    size_t posicion = 0;
    size_t i = 0;

    while(i < menu_cantidad(menu) && !(*encontrada)) {
        opcion_t *actual = lista_obtener(menu->opciones, i);
        if(actual->seleccionada) {
            if(encontrada) {
                *encontrada = true;
            }
            posicion = i;
        }
        i++;
    }

    return posicion;
}

/*
 * Ejecuta la opcion relacionada a la tecla ingresada.
 *
 * Devuelve seguir o terminar dependiendo lo que devuelve la acción,
 * no_existe si no hay una opcion con esa tecla asociada, o error si menu es NULL.
 */
enum menu_resultado menu_ejecutar(menu_t *menu, char tecla) {
    if(!menu) return MENU_ERROR;

    if(menu_cantidad(menu) == 0) return MENU_NO_EXISTE;

    opcion_t *opcion;
    bool seguir = true;
    int resultado_busqueda = lista_buscar(menu->opciones, &tecla, comparar_teclas, &opcion);

    if(resultado_busqueda == NO_ENCONTRADO) return MENU_NO_EXISTE;

    return ejecutar_opcion(opcion);
}

/*
 * Mueve la selección a la opción siguiente o anterior. Devuelve true si se pudo realizar el movimiento.
 *
 * Devuelve false en caso de error
 */
bool menu_mover_seleccion(menu_t *menu, enum menu_direccion direccion) {
    if(!menu || (direccion != MENU_ANTERIOR && direccion != MENU_SIGUIENTE)) return false;

    bool encontrada = false;
    size_t indice_seleccionada_actual = menu_seleccionada(menu, &encontrada);
    if(!encontrada) return false;

    opcion_t *actual = lista_obtener(menu->opciones, indice_seleccionada_actual);
    actual->seleccionada = false;
    opcion_t *reemplazado = lista_reemplazar(menu->opciones, actual, indice_seleccionada_actual);
    
    if(direccion == MENU_SEGUIR) {
        opcion_t *siguiente = lista_obtener(menu->opciones, indice_seleccionada_actual + 1);
        siguiente->seleccionada = true;
        opcion_t *siguiente_reemplazado = lista_reemplazar(menu->opciones, actual, indice_seleccionada_actual + 1);
    } else {
        opcion_t *anterior = lista_obtener(menu->opciones, indice_seleccionada_actual - 1);
        anterior->seleccionada = true;
        opcion_t *anterior_reemplazado = lista_reemplazar(menu->opciones, actual, indice_seleccionada_actual - 1);
    }
}

/*
 * Ejecuta la opcion seleccionada del menu.
 * 
 * Devuelve seguir o terminar dependiendo lo que devuelve la acción,
 * no_existe si el menú está vacío, o error si menu es NULL.
 */
enum menu_resultado menu_ejecutar_seleccionada(menu_t *menu) {
    if(!menu) return MENU_ERROR;

    if(menu_cantidad(menu) == 0) return MENU_NO_EXISTE;

    bool encontro_opcion_seleccionada = false;
    bool seguir = true;
    size_t posicion_seleccionada = menu_seleccionada(menu, &encontro_opcion_seleccionada);
    if(!encontro_opcion_seleccionada) return MENU_NO_EXISTE;

    opcion_t *opcion = lista_obtener(menu->opciones, posicion_seleccionada);

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
		seguir = f(opcion->tecla, opcion->texto, opcion->seleccionada, extra);
		contador++;
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
    return;
}
