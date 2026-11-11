#include <ctype.h>
#include <stdio.h>

#include "menu.h"
#include "leer_linea.h"
#include "consola.h"
#include "informacion.h"

typedef struct contexto_para_menu {
    tp1_t *pokedex;
} contexto_para_menu_t;

bool imprimir_opcion_menu(char tecla, char *texto, bool seleccionada, void *contexto) {
    printf("%c - %s\n", tecla, texto);
    return true;
}

int imprimir_error_al_jugar_en_consola(void *extra) {
    printf("En modo consola no se puede ejecutar el juego.\n");

    return 0;
}

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

int mostrar_informacion_juego(void *extra) {
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

int mostrar_pokemon_buscado(void* extra) {
    contexto_para_menu_t *contexto = extra;
    printf("Ingrese el nombre del pokemon que quiera buscar: \n");

    char *nombre  = leer_linea(stdin);
    if(!nombre) return 1;

    struct pokemon *buscado = tp1_buscar_pokemon(contexto->pokedex, nombre);
	if (!buscado) {
		printf("No se pudo encontrar el pokemon buscado.\n");
	} else {
		//char rareza = obtener_caracter_rareza(buscado->rareza);
		printf("El pokemon buscado es: %s\n", buscado->nombre);
		//imprimir_pokemon(buscado, rareza);
	}
    free(nombre);

    return 0;
}

int salir_del_juego(void *extra) {
    return 1;
}


bool consola_ejecutar(tp1_t *pokedex) {
    menu_t *menu = menu_crear();
    if(!menu) return false;

    struct contexto_para_menu contexto = { 0 };
    contexto.pokedex = pokedex;

    bool agregar_jugar = menu_agregar(menu, 'J', "Jugar", imprimir_error_al_jugar_en_consola, NULL);
    bool agregar_jugar_con_semilla = menu_agregar(menu, 'S', "Jugar con semilla", imprimir_error_al_jugar_en_consola, NULL);
    bool agregar_mostrar_pokemon = menu_agregar(menu, 'M', "Mostrar pokemon", mostrar_pokemon_buscado, &contexto);
    bool agregar_mostrar_info = menu_agregar(menu, 'I', "Mostrar informacion", mostrar_informacion_juego, &contexto);
    bool agregar_salir = menu_agregar(menu, 'Q', "Salir", salir_del_juego, NULL);

    if(!agregar_jugar || !agregar_jugar_con_semilla || !agregar_mostrar_info || !agregar_mostrar_pokemon || !agregar_salir) {
        menu_destruir(menu);
        return false;
    }

    bool seguir = true;
    while(seguir) {

        menu_iterar(menu, imprimir_opcion_menu, &contexto);

        char *tecla = leer_linea(stdin);
        if(!tecla) {
            seguir = false;
        } else {
            int tecla_en_mayuscula = toupper((unsigned char)*tecla);

            enum menu_resultado resultado = menu_ejecutar(menu, (char)tecla_en_mayuscula);
            if (resultado == MENU_NO_EXISTE) printf("Opcion invalida.\n");
            else if(resultado == MENU_TERMINAR || resultado == MENU_ERROR) seguir = false;
        }

        free(tecla);
    }

    menu_destruir(menu);
    return true;
}

