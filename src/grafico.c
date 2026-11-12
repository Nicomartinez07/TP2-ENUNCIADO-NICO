#include "grafico.h"
#include "informacion.h"
#include "../extra/engine.h"

#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define BLANCO 0xFFFFFF
#define AMARILLO 0xFFE060
#define GRIS 0xA0A0A0
#define LILA 0xA700A7
#define MAX_ENTRADA 12

enum estados { ESTADO_MENU, ESTADO_MUESTREO_POKEMON, ESTADO_MUESTREO_INFORMACION, ESTADO_PIDIENDO_NOMBRE, ESTADO_PIDIENDO_SEMILLA, ESTADO_JUEGO };

struct estado_grafico {
	enum estados estado_actual;
    menu_t *menu;
	tp1_t *pokedex;
    //partida_t *partida;
    
    struct pokemon *pokemon_mostrado;
    struct pokedex_info info_pokemones;

    bool usar_semilla;
    unsigned int semilla;
	char entrada[MAX_ENTRADA];
};

typedef struct contexto_para_dibujar_menu {
    pantalla_t *p;
    size_t indice_opcion_actual;
    size_t indice_seleccionada;
} contexto_para_dibujar_menu_t;

int pasar_al_juego(void *extra) {
    struct estado_grafico *estado = extra;

    estado->usar_semilla = false;
    estado->estado_actual = ESTADO_JUEGO;
    return 0;
}

int pasar_a_pedir_semilla(void *extra) {
    struct estado_grafico *estado = extra;

    estado->usar_semilla = true;
    memset(estado->entrada, 0, sizeof(estado->entrada));
    estado->estado_actual = ESTADO_PIDIENDO_SEMILLA;
    return 0;
}

/*
 * Limpia la entrada del estado. Setea el estado actual a muestreo de informacion y retorna 0.
 */
int pasar_a_mostrar_pokemon(void *extra) {
    struct estado_grafico *estado = extra;

    memset(estado->entrada, 0, sizeof(estado->entrada));
    estado->estado_actual = ESTADO_PIDIENDO_NOMBRE;
    return 0;
}

/*
 * Setea el estado actual a muestreo de informacion y retorna 0.
 */
int pasar_a_mostrar_informacion(void *extra) {
    struct estado_grafico *estado = extra;
    
    estado->estado_actual = ESTADO_MUESTREO_INFORMACION;
    return 0;
}

/*
 * Retorna un valor distinto de 0 para finalizar el juego.   
 */
int terminar_juego(void *extra) {
    return 1;
}

unsigned color_condicional(bool condicion, unsigned color_verdadero,
			   unsigned color_falso)
{
	if (condicion)
		return color_verdadero;
	return color_falso;
}

/*
 * Imprime por pantalla, la opcion del menu. En caso de ser la seleccionada la imprime de color lila.
 * Para imprimir tecla - texto genera un texto con ambas partes, utilizando snprintf
 */
bool imprimir_opcion_menu(char tecla, char *texto, bool seleccionada, void *contexto) {
    if(!texto) return false;

    contexto_para_dibujar_menu_t *informacion = contexto;

    char texto_a_imprimir[256];
    int n = snprintf(texto_a_imprimir, sizeof(texto_a_imprimir), "%c - %s", tecla, texto);
    if (n < 0 || (size_t)n >= sizeof(texto_a_imprimir)) return false;

    engine_texto(informacion->p , 40, 60 + ((int)informacion->indice_opcion_actual * 10),
		     color_condicional(informacion->indice_opcion_actual == informacion->indice_seleccionada, LILA, BLANCO),
		     texto_a_imprimir);
    informacion->indice_opcion_actual++;

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
        enum menu_resultado resultado_ejecutar_por_tecla = menu_ejecutar(estado->menu, (char)caracter);
        if(resultado_ejecutar_por_tecla == MENU_TERMINAR) return 1;
    }

    contexto_para_dibujar_menu_t contexto;
    contexto.p = p;
    contexto.indice_opcion_actual = 0;
    contexto.indice_seleccionada = menu_seleccionada(estado->menu);

    menu_iterar(estado->menu, imprimir_opcion_menu, &contexto);
	
	return 0;
}

int procesar_frame(const struct entrada *e, pantalla_t *p, void *ctx)
{
	struct estado_grafico *estado = ctx;

    switch (estado->estado_actual) {
        case ESTADO_JUEGO:
            dibujar_juego(e, p, ctx);
            break;
        case ESTADO_MENU:
            dibujar_menu(e, p, ctx);
            break;
        case ESTADO_MUESTREO_POKEMON:
            dibujar_muestreo_pokemon(e, p, ctx);
            break;
        case ESTADO_MUESTREO_INFORMACION:
            dibujar_muestreo_informacion(e, p, ctx);
            break;
        case ESTADO_PIDIENDO_NOMBRE:
            dibujar_entrada_nombre(e, p, ctx);
            break;
        case ESTADO_PIDIENDO_SEMILLA:
            dibujar_entrada_semilla(e, p, ctx);
            break;
        default:
            dibujar_juego(e, p, ctx);
    }
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
    estado.usar_semilla = false;
    
    bool resultado_obtener_informacion = pokedex_obtener_info(estado.pokedex, &(estado.info_pokemones));
    if(!resultado_obtener_informacion) return false;
	
    estado.menu = menu_crear();
    if(!estado.menu) return false;

    struct engine_config configuracion = { 0 };
	configuracion.titulo = "Juego TP2";

	if (puerto != NULL)
		configuracion.puerto = puerto;

    bool agregar_jugar = menu_agregar(estado.menu, 'J', "Jugar", pasar_al_juego, &estado);
    bool agregar_jugar_con_semilla = menu_agregar(estado.menu, 'S', "Jugar con semilla", pasar_a_pedir_semilla, &estado);
    bool agregar_mostrar_pokemon = menu_agregar(estado.menu, 'M', "Mostrar pokemon", pasar_a_mostrar_pokemon, &estado);
    bool agregar_mostrar_info = menu_agregar(estado.menu, 'I', "Mostrar informacion", pasar_a_mostrar_informacion, &estado);
    bool agregar_salir = menu_agregar(estado.menu, 'Q', "Salir", terminar_juego, &estado);

    if(!agregar_jugar || !agregar_jugar_con_semilla || !agregar_mostrar_info || !agregar_mostrar_pokemon || !agregar_salir) {
        menu_destruir(estado.menu);
        return false;
    }

    if (engine_correr(&configuracion, procesar_frame, &estado) != 0) {
        menu_destruir(estado.menu);
		return false;
    }


    menu_destruir(estado.menu);
    return true;
}