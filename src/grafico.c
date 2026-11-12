#include "grafico.h"
#include "informacion.h"
#include "extra/engine.h"

#define BLANCO 0xFFFFFF
#define AMARILLO 0xFFE060
#define GRIS 0xA0A0A0
#define LILA 0xA700A7
#define MAX_ENTRADA 12

typedef struct contexto_para_menu {
    struct estado_grafico *estado;
} contexto_para_menu_t;


enum estados { ESTADO_MENU, ESTADO_MUESTREO_POKEMON, ESTADO_MUESTREO_INFORMACION, ESTADO_PIDIENDO_NOMBRE, ESTADO_PIDIENDO_SEMILLA, ESTADO_JUEGO };

struct estado_grafico {
	enum estados estado_actual;
    menu_t *menu;
	tp1_t *pokedex;
    
    struct pokemon *pokemon_mostrado;
    struct pokedex_info info_pokemones;

    unsigned int semilla;
	char entrada[MAX_ENTRADA];
};

typedef struct contexto_para_dibujar_menu {
    pantalla_t *p;
    int indice_opcion_actual;
} contexto_para_dibujar_menu_t;

unsigned color_condicional(bool condicion, unsigned color_verdadero,
			   unsigned color_falso)
{
	if (condicion)
		return color_verdadero;
	return color_falso;
}

/*
 * Imprime tecla - texto, devuelve false en caso de error.
 */
bool imprimir_opcion_menu(char tecla, char *texto, bool seleccionada, void *contexto) {
    if(!texto) return false;

    contexto_para_dibujar_menu_t *informacion = contexto;

    char texto_a_imprimir[256];
    int n = snprintf(texto_a_imprimir, sizeof(texto_a_imprimir), "%c - %s", tecla, texto);
    if (n < 0 || (size_t)n >= sizeof(texto_a_imprimir)) return false;

    engine_texto(informacion->p , 40, 50 + (informacion->indice_opcion_actual * 10),
		     color_condicional(seleccionada, LILA, BLANCO),
		     texto_a_imprimir);


    return true;
}

int dibujar_menu(const struct entrada *e, pantalla_t *p, void *ctx)
{
	struct estado_grafico *estado = ctx;
	if (engine_presionado(e, BOTON_ABAJO))
		menu_mover_seleccion(estado->menu, MENU_SIGUIENTE);
	else if (engine_presionado(e, BOTON_ARRIBA))
		menu_mover_seleccion(estado->menu, MENU_ANTERIOR);

    if(engine_presionado(e, BOTON_ENTER)) {
        enum menu_resultado resultado_ejecutar = menu_ejecutar_seleccionada(estado->menu);
        if(resultado_ejecutar == MENU_TERMINAR) return 1;
    }

    int caracter = toupper((unsigned char)e->caracter);
    if(caracter) {
        enum menu_resultado resultado_ejecutar_por_tecla = menu_ejecutar(estado->menu, caracter);
        if(resultado_ejecutar_por_tecla == MENU_TERMINAR) return 1;
    }

    while(menu_iterar(estado->menu, , p))
	

	return 0;
}

/*
 * 
 */
bool grafico_ejecutar(tp1_t *pokedex, char *puerto) {
    if(!pokedex) return false;

    struct estado_grafico estado;
	memset(&estado, 0, sizeof(estado));
	estado.estado_actual = ESTADO_MENU;
    estado.pokedex = pokedex;
    
    bool resultado_obtener_informacion = pokedex_obtener_info(estado.pokedex, &(estado.info_pokemones));
    if(!resultado_obtener_informacion) return false;
	
    estado.menu = menu_crear();
    if(!estado.menu) return false;

    struct engine_config configuracion = { 0 };
	configuracion.titulo = "Juego TP2";

	if (puerto != NULL)
		configuracion.puerto = puerto;

    bool agregar_jugar = menu_agregar(estado.menu, 'J', "Jugar", NULL, NULL);
    bool agregar_jugar_con_semilla = menu_agregar(estado.menu, 'S', "Jugar con semilla", NULL, NULL);
    bool agregar_mostrar_pokemon = menu_agregar(estado.menu, 'M', "Mostrar pokemon", NULL, &estado);
    bool agregar_mostrar_info = menu_agregar(estado.menu, 'I', "Mostrar informacion", NULL, &estado);
    bool agregar_salir = menu_agregar(estado.menu, 'Q', "Salir", NULL, NULL);

    if(!agregar_jugar || !agregar_jugar_con_semilla || !agregar_mostrar_info || !agregar_mostrar_pokemon || !agregar_salir) {
        menu_destruir(estado.menu);
        return false;
    }


    menu_destruir(estado.menu);
    return true;
}



/*
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


*/