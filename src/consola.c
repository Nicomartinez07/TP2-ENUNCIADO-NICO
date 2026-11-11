#include <ctype.h>
#include <stdio.h>

#include "menu.h"
#include "leer_linea.h"
#include "consola.h"
#include "informacion.h"

#define TEXTO_RAREZA_COMUN "Comun"
#define TEXTO_RAREZA_RARO "Raro"
#define TEXTO_RAREZA_LEGENDARIA "Legendario"

typedef struct contexto_para_menu {
    tp1_t *pokedex;
} contexto_para_menu_t;

/*
 * Imprime por consola el pokemon. La rareza la convierte a texto. 
 */
void imprimir_pokemon(struct pokemon *actual) {
        printf("El pokemon buscado es: %s\n", actual->nombre);
        printf("Pesa exactamente: %f\n", actual->peso);
        printf("Su velocidad es: %i\n", actual->velocidad);
        char *rareza_texto;
        switch (actual->rareza) {
            case RAREZA_COMUN:
                rareza_texto = TEXTO_RAREZA_COMUN;
                break;
            case RAREZA_LEGENDARIO:
                rareza_texto = TEXTO_RAREZA_LEGENDARIA;
                break;
            case RAREZA_RARO:
                rareza_texto = TEXTO_RAREZA_RARO;
                break;
            }

        printf("Y es de tipo: %s\n", rareza_texto);
}

/*
 * Imprime tecla - texto, devuelve false en caso de error.
 */
bool imprimir_opcion_menu(char tecla, char *texto, bool seleccionada, void *contexto) {
    if(!texto) return false;
    printf("%c - %s\n", tecla, texto);
    return true;
}

/*
 * Imprime un mensaje de alerta
 */
int imprimir_error_al_jugar_en_consola(void *extra) {
    printf("En modo consola no se puede ejecutar el juego.\n");
    printf("\n");
    return 0;
}

/*
 * Imprime toda la informacion recolectada de la pokedex
 */
void imprimir_informacion_juego(struct pokedex_info *informacion) {
    printf("\n");
    printf("A continuacion se muestra la informacion obtenida de la pokedex:\n");
    printf("\n");

    printf("- Cantidad de pokemones en la pokedex: %zu.\n", informacion->total);
    printf("- Cantidad de rarezas distintas en la pokedex: %zu.\n", informacion->rarezas_distintas);
    printf("\n");

    if(informacion->total > 0) {
        printf("- El Pokemon mas veloz en la pokedex es: %s, y su velocidad es %i.\n", informacion->mas_veloz->nombre, informacion->mas_veloz->velocidad);
        printf("\n");
        printf("- El Pokemon menos veloz en la pokedex es: %s, y su velocidad es %i.\n", informacion->menos_veloz->nombre, informacion->menos_veloz->velocidad);
        printf("\n");
        printf("- El Pokemon mas pesado en la pokedex es: %s, y pesa %f\n", informacion->mas_pesado->nombre, informacion->mas_pesado->peso);
        printf("\n");
        printf("- El Pokemon menos pesado en la pokedex es: %s, y pesa %f.\n", informacion->menos_pesado->nombre, informacion->menos_pesado->peso);
    } else {
        printf("No se imprimen estadisticas de los mejores ni peores porque la pokedex esta vacia.\n");
    }
    printf("\n");
}

/*
 * Obtiene e imprime la informacion relacionada a la pokedex. En caso de que no se obtenga, imprime un mensaje avisando que no se pudo realizar la obtencion de informacion.
 */
int mostrar_informacion_pokedex(void *extra) {
    contexto_para_menu_t *contexto = extra;

    struct pokedex_info info_pokedex = { 0 };
    
    bool resultado_obtener_info = pokedex_obtener_info(contexto->pokedex, &info_pokedex);
    if(!resultado_obtener_info) {
        printf("No se pudo obtener la informacion necesaria de la pokedex");
        return 0;   
    }
    imprimir_informacion_juego(&info_pokedex);

    return 0;
}

/*
 * Solicita al usuario que ingrese un nombre, y busca en la pokedex un pokemon con ese nombre. En caso de encontrarlo lo imprime.
 * Devuelve 0. En caso de error devuelve 1.
 */
int mostrar_pokemon_buscado(void* extra) {
    contexto_para_menu_t *contexto = extra;
    printf("\n");
    printf("Ingrese el nombre del pokemon que quiera buscar: \n");

    char *nombre  = leer_linea(stdin);
    if(!nombre) return 1;

    struct pokemon *buscado = tp1_buscar_pokemon(contexto->pokedex, nombre);
	if (!buscado) {
		printf("No se pudo encontrar el pokemon buscado.\n");
	} else {
		
        printf("\n");
        imprimir_pokemon(buscado);
        printf("\n");
	}
    free(nombre);

    return 0;
}

int salir_del_juego(void *extra) {
    return 1;
}

/*
 * Ejecuta continuamente el juego por la terminal. Genera un menu al cual se le cargan las opciones del juego, la memoria del menu es manejada por la funcion misma.
 * Es indistinto ingresar una tecla en Minuscula o Mayuscula al seleccionar opciones en el menu. La busqueda de un pokemon se hace por el nombre ingresado exacto.
 * En caso de error devuelve false.
 */
bool consola_ejecutar(tp1_t *pokedex) {
    menu_t *menu = menu_crear();
    if(!menu) return false;

    struct contexto_para_menu contexto = { 0 };
    contexto.pokedex = pokedex;

    bool agregar_jugar = menu_agregar(menu, 'J', "Jugar", imprimir_error_al_jugar_en_consola, NULL);
    bool agregar_jugar_con_semilla = menu_agregar(menu, 'S', "Jugar con semilla", imprimir_error_al_jugar_en_consola, NULL);
    bool agregar_mostrar_pokemon = menu_agregar(menu, 'M', "Mostrar pokemon", mostrar_pokemon_buscado, &contexto);
    bool agregar_mostrar_info = menu_agregar(menu, 'I', "Mostrar informacion", mostrar_informacion_pokedex, &contexto);
    bool agregar_salir = menu_agregar(menu, 'Q', "Salir", salir_del_juego, NULL);

    if(!agregar_jugar || !agregar_jugar_con_semilla || !agregar_mostrar_info || !agregar_mostrar_pokemon || !agregar_salir) {
        menu_destruir(menu);
        return false;
    }


    printf("Bienvenido al juego de los pokemones: \n");
    printf("\n");
    printf("Seleccione una tecla para arrancar\n");
    printf("\n");
    bool ejecucion_valida = true;
    bool seguir = true;
    while(seguir) {

        menu_iterar(menu, imprimir_opcion_menu, &contexto);
        printf("\n");
        char *tecla = leer_linea(stdin);
        if(!tecla) {
            ejecucion_valida = false; 
            seguir = false;
        } else {
            int tecla_en_mayuscula = toupper((unsigned char)*tecla);

            enum menu_resultado resultado = menu_ejecutar(menu, (char)tecla_en_mayuscula);
            if (resultado == MENU_NO_EXISTE) printf("Opcion invalida.\n");
            else if(resultado == MENU_TERMINAR) seguir = false;
            else if(resultado == MENU_ERROR) {
                ejecucion_valida = false;
                seguir = false;
            }
        }

        free(tecla);
    }

    menu_destruir(menu);
    return ejecucion_valida;
}

