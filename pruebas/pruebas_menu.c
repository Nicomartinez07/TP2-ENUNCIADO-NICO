#include "../src/menu.h"
#include "pa2m.h"
#include <string.h>

struct visualizador_interno {
	int cant_llamadas; 
	int a_devolver;
};
 
/*
 * Aumenta un contador por cada opcion del menu
 */
bool contar_opciones(char tecla, char *texto, bool seleccionada, void *contexto)
{
    size_t *contador = contexto;
    (*contador)++;

    return true;
}

/*
 * Dado una opcion, retorna si la tecla de la opcion es igual a la tecla buscada
*/
bool parar_en_cierta_tecla(char tecla, char *texto, bool seleccionada, void *contexto)
{
    char tecla_objetivo = *(char *)contexto;

    return tecla != tecla_objetivo;
}

int accion_reportadora(void *ctx)
{
	struct visualizador_interno *visor = ctx;
	visor->cant_llamadas++;
	return visor->a_devolver;
}


void prueba_crear_menu() {
    menu_t *menu = menu_crear();
    pa2m_afirmar(menu != NULL, "Se pudo crear un menu.");
    if(!menu) return;

    pa2m_afirmar(menu_cantidad(menu) == 0, "Al crearse el menu contiene 0 elementos.\n");
    
    menu_destruir(menu);
}


void prueba_menu_acciones_invalidas() {
    menu_t *menu = menu_crear();

    if(!menu) return;
    struct visualizador_interno visor1;
    visor1.a_devolver = 0;
    visor1.cant_llamadas = 0;

    pa2m_afirmar(!menu_agregar(menu, 'j', NULL, accion_reportadora, &visor1), "No se puede insertar una opcion con texto nulo.");
    pa2m_afirmar(!menu_agregar(menu, 'j', "jugar", NULL, &visor1), "No se puede insertar una opcion con accion nula.");
    pa2m_afirmar(!menu_agregar(NULL, 'j', "jugar", accion_reportadora, &visor1), "No se puede insertar una opcion con menu NULL.");

    pa2m_afirmar(menu_cantidad(NULL) == 0, "Al obtener la cantidad de opciones de un menu nulo, se obtiene 0.");

    pa2m_afirmar(!menu_mover_seleccion(NULL, MENU_SIGUIENTE), "Al intentar mover la seleccion en un menu nulo, se obtiene error");
    pa2m_afirmar(!menu_mover_seleccion(menu, MENU_SIGUIENTE), "Al intentar mover la seleccion en un menu vacio, se obtiene error");
    
    size_t contador = 0;

    pa2m_afirmar(menu_iterar(NULL, contar_opciones, &contador) == 0, "Al intentar iterar un menu nulo, se obtiene que se iteraron 0 elementos.");
    pa2m_afirmar(menu_iterar(menu, NULL, &contador) == 0, "Al intentar iterar un menu con una funcion nula, se obtiene que se iteraron 0 elementos.");

    pa2m_afirmar(menu_iterar(menu, contar_opciones, &contador) == 0, "Al intentar iterar un menu vacio, no se recorren opciones.");


    enum menu_resultado resultado_ejecutar_seleccionada_vacio = menu_ejecutar_seleccionada(menu);
    pa2m_afirmar(resultado_ejecutar_seleccionada_vacio == MENU_NO_EXISTE, "Al intentar ejecutar la opcion seleccionada con un menu vacio devuelve MENU_NO_EXISTE");

    enum menu_resultado resultado_ejecutar_seleccionada_nulo = menu_ejecutar_seleccionada(NULL);
    pa2m_afirmar(resultado_ejecutar_seleccionada_nulo == MENU_ERROR, "Al intentar ejecutar la opcion seleccionada con un menu nulo devuelve MENU_ERROR");



    enum menu_resultado resultado_ejecutar_tecla_nulo = menu_ejecutar(NULL, 'J');
    pa2m_afirmar(resultado_ejecutar_tecla_nulo == MENU_ERROR, "Al intentar ejecutar la opcion relacionada a una tecla con un menu nulo devuelve MENU_ERROR");

    enum menu_resultado resultado_ejecutar_tecla_vacio = menu_ejecutar(menu, 'J');
    pa2m_afirmar(resultado_ejecutar_tecla_vacio == MENU_NO_EXISTE, "Al intentar ejecutar la opcion relacionada a una tecla con un menu vacio devuelve MENU_NO_EXISTE");

    pa2m_afirmar(menu_agregar(menu, 'j', "jugar", accion_reportadora, &visor1), "Se inserto una opcion jugar, tecla: 'j', texto: 'jugar'.");
    enum menu_resultado resultado_ejecutar_tecla_inexistente = menu_ejecutar(menu, 'S');
    pa2m_afirmar(resultado_ejecutar_tecla_inexistente == MENU_NO_EXISTE, "Al intentar ejecutar la opcion que no existe en el menu, devuelve MENU_NO_EXISTE.");
    pa2m_afirmar(visor1.cant_llamadas == 0, "La cantidad de llamadas del visor, sigue en 0.\n");

    menu_destruir(menu);
}


void prueba_agregar_menu_validas() {
    menu_t *menu = menu_crear();
    if(!menu) return;
    struct visualizador_interno visor1;
    visor1.a_devolver = 0;
    visor1.cant_llamadas = 0;

    pa2m_afirmar(menu_agregar(menu, 'j', "jugar", accion_reportadora, &visor1), "Se inserto una opcion jugar, tecla: 'j', texto: 'jugar'.");
    pa2m_afirmar(menu_agregar(menu, 'J', "JUGAR", accion_reportadora, &visor1), "Se inserto una opcion jugar, tecla: 'J', texto: 'JUGAR'.");
    pa2m_afirmar(menu_cantidad(menu) == 2, "Se pudo insertar 2 opciones con la misma letra, porque el menu distingue entre Mayusculas y minusculas.");

    pa2m_afirmar(!menu_agregar(menu, 'j', "jugar repetido", accion_reportadora, &visor1), "Al intentar agregar una opcion con una tecla ya existente, nos devuelve error.");
    pa2m_afirmar(menu_cantidad(menu) == 2, "La cantidad sigue siendo 2 a pesar de que se intento agregar una tercera opcion.\n");

    menu_destruir(menu);
}


void prueba_mover_seleccion() {
    menu_t *menu = menu_crear();
    if(!menu) return;
    struct visualizador_interno visor1;
    visor1.a_devolver = 0;
    visor1.cant_llamadas = 0;

    struct visualizador_interno visor2;
    visor1.a_devolver = 0;
    visor1.cant_llamadas = 0;

    struct visualizador_interno visor3;
    visor1.a_devolver = 0;
    visor1.cant_llamadas = 0;

    menu_agregar(menu, 'j', "jugar", accion_reportadora, &visor1);
    menu_mover_seleccion(menu, MENU_ANTERIOR);
    pa2m_afirmar(menu_seleccionada(menu) == 0, "Al mover la seleccion en un menu de una sola opcion, se seleccionada es la unica opcion.");


    menu_agregar(menu, 's', "saludo", accion_reportadora, &visor2);
    menu_agregar(menu, 'b', "bailar", accion_reportadora, &visor3);
    

    pa2m_afirmar(menu_cantidad(menu) == 3, "La cantidad de opciones en el menu es %i, porque se insertaron 2 opciones.", menu_cantidad);

    pa2m_afirmar(menu_seleccionada(menu) == 0, "Al agregar opciones, sin mover la seleccion, la seleccionada siempre es la primera ingresada");
    pa2m_afirmar(menu_mover_seleccion(menu, MENU_SIGUIENTE), "Se movio la seleccion a la siguiente");
    pa2m_afirmar(menu_seleccionada(menu) == 1, "Al mover la seleccion a la siguiente, la seleccionada pasa a ser la segunda opcion");
    pa2m_afirmar(menu_mover_seleccion(menu, MENU_SIGUIENTE), "Se volvio a mover la seleccion a la siguiente");
    pa2m_afirmar(menu_seleccionada(menu) == 2, "Al mover 2 veces la selecion al siguiente, en un menu de 3 opciones, la seleccionada pasa a ser la tercer opcion del menu.");
    pa2m_afirmar(menu_mover_seleccion(menu, MENU_SIGUIENTE), "Se volvio a mover la seleccion a la siguiente");
    pa2m_afirmar(menu_seleccionada(menu) == 0, "Al mover 3 veces la selecion al siguiente, en un menu de 3 opciones, la seleccionada pasa a ser la primera opcion del menu.");
    pa2m_afirmar(menu_mover_seleccion(menu, MENU_ANTERIOR), "Se movio la seleccion a la anterior");
    pa2m_afirmar(menu_seleccionada(menu) == 2, "Al estar en la primera opcion del menu, y mover la seleccion al anterior, la seleccionada pasa a ser la tercera opcion, porque el menu es ciclico.");
    pa2m_afirmar(menu_mover_seleccion(menu, MENU_ANTERIOR), "Se movio la seleccion a la anterior");
    pa2m_afirmar(menu_seleccionada(menu) == 1, "Al estar en la tercera opcion del menu, y mover la seleccion al anterior, la seleccionada pasa a ser la segunda opcion.\n");

    menu_destruir(menu);
}


void prueba_ejecutar() {
	menu_t *menu = menu_crear();
	struct visualizador_interno visor1;
    visor1.a_devolver = 0;
    visor1.cant_llamadas = 0;

    struct visualizador_interno visor2;
    visor2.a_devolver = 1;
    visor2.cant_llamadas = 0;

	menu_agregar(menu, 'J', "Jugar", accion_reportadora, &visor1);
	menu_agregar(menu, 'S', "Saludar", accion_reportadora, &visor2);

	enum menu_resultado respuesta_ejecutar = menu_ejecutar(menu, 'J');

	pa2m_afirmar(respuesta_ejecutar == MENU_SEGUIR, "Ejecutar la opcion con tecla 'J' devuelve MENU_SEGUIR");
	pa2m_afirmar(visor1.cant_llamadas == 1, "La acción de 'J' se ejecutó una vez");
	pa2m_afirmar(visor2.cant_llamadas == 0, "La acción de 'S' no se ejecutó.");

    pa2m_afirmar(menu_seleccionada(menu) == 0, "La opcion seleccionada es la primera.");
    enum menu_resultado respuesta_ejecutar_seleccionada = menu_ejecutar_seleccionada(menu);
    pa2m_afirmar(respuesta_ejecutar_seleccionada == MENU_SEGUIR, "Ejecutar la opcion seleccionada devuelve MENU_SEGUIR");
    pa2m_afirmar(visor1.cant_llamadas == 2, "Se volvio a ejecutar la accion de 'J', debido a que es la seleccionada");
	pa2m_afirmar(visor2.cant_llamadas == 0, "La acción de 'S' no se ejecutó porque no es la selecionada.");

    pa2m_afirmar(menu_mover_seleccion(menu, MENU_SIGUIENTE), "Se movio la selecion a la siguiente opcion");
    enum menu_resultado respuesta_ejecutar_seleccionada_actual = menu_ejecutar_seleccionada(menu);
    pa2m_afirmar(respuesta_ejecutar_seleccionada_actual == MENU_TERMINAR, "Ejecutar la opcion seleccionada devuelve MENU_TERMINAR");
    pa2m_afirmar(visor1.cant_llamadas == 2, "No se ejecuto la opcion de 'J' porque no es la seleccionada.");
	pa2m_afirmar(visor2.cant_llamadas == 1, "Se ejecuto la accion de 'S', debido a que es la seleccionada");

	menu_destruir(menu);
}


void prueba_iterar() {
    menu_t *menu = menu_crear();
    if(!menu) return;
    struct visualizador_interno visor1;
    visor1.a_devolver = 0;
    visor1.cant_llamadas = 0;

    struct visualizador_interno visor2;
    visor2.a_devolver = 0;
    visor2.cant_llamadas = 0;

    struct visualizador_interno visor3;
    visor3.a_devolver = 0;
    visor3.cant_llamadas = 0;

    pa2m_afirmar(menu_agregar(menu, 'J', "JUGAR", accion_reportadora, &visor1), "Se inserto una opcion jugar, tecla: 'J', texto: 'JUGAR'.");
    pa2m_afirmar(menu_agregar(menu, 'S', "SALUDAR", accion_reportadora, &visor2), "Se inserto una opcion jugar, tecla: 'S', texto: 'SALUDAR'.");
    pa2m_afirmar(menu_agregar(menu, 'M', "MOVER", accion_reportadora, &visor3), "Se inserto una opcion jugar, tecla: 'M', texto: 'MOVER'.");
    
    size_t contador = 0;

    pa2m_afirmar(menu_iterar(menu, contar_opciones, &contador) == menu_cantidad(menu), "La funcion se invoco 3 veces, coincide con la cantidad de elementos que hay");
    pa2m_afirmar(contador == menu_cantidad(menu), "El resultado de aplicar la funcion contar opciones coindice con la cantidad de elementos en menu");


    char tecla_para_parar = 'S';
    pa2m_afirmar(menu_iterar(menu, parar_en_cierta_tecla, &tecla_para_parar) == 2, "Itero hasta encontrar la opcion con la tecla buscada (2 elementos iterados)");

    menu_destruir(menu);
}

void pruebas_menu() {
    pa2m_nuevo_grupo("Prueba crear menu");
    prueba_crear_menu();

    pa2m_nuevo_grupo("Pruebas con acciones invalidas");
    prueba_menu_acciones_invalidas();

    pa2m_nuevo_grupo("Prueba agregar menu");
    prueba_agregar_menu_validas();

    pa2m_nuevo_grupo("Prueba mover seleccion del menu");
    prueba_mover_seleccion();

    pa2m_nuevo_grupo("Pruebas ejecutar acciones");
    prueba_ejecutar();

    pa2m_nuevo_grupo("Pruebas iterar menu");
    prueba_iterar();
}