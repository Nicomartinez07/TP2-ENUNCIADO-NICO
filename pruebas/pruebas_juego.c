#include "pa2m.h"
#include <string.h>
#include "../src/informacion.h"

void prueba_obtener_informacion_parametros_invalidos() {

    tp1_t *pokedex = tp1_leer_archivo("./pruebas/archivos/pokemones.csv");
    pa2m_afirmar(pokedex != NULL, "Se pudo procesar el archivo y obtener la pokedex");
    if(!pokedex) return;

    struct pokedex_info info_pokedex = { 0 };

    bool resultado_obtener_informacion_pokedex_nula = pokedex_obtener_info(NULL, &info_pokedex);
    pa2m_afirmar(!resultado_obtener_informacion_pokedex_nula, "No se puede recopilar informacion de una pokedex nula");

    bool resultado_obtener_informacion_informacion_nula = pokedex_obtener_info(pokedex, NULL);
    pa2m_afirmar(!resultado_obtener_informacion_informacion_nula, "No se puede recopilar informacion sin un lugar donde almacenarla.");
    
    tp1_destruir(pokedex);
}

void prueba_obtener_informacion_pokedex() {
    const char *mas_veloz = "Suicune";
    const char *menos_veloz = "Magikarp";
    const char *mas_pesado = "Suicune";
    const char *menos_pesado = "Starmie";
    const int cantidad_pokemones = 5;
    const int cantidad_rarezas_distintas = 3;

	tp1_t *pokedex = tp1_leer_archivo("./pruebas/archivos/pokemones.csv");
    pa2m_afirmar(pokedex != NULL, "Se pudo procesar el archivo y obtener la pokedex");
    if(!pokedex) return;

    struct pokedex_info info_pokedex = { 0 };

    bool resultado_obtener_informacion = pokedex_obtener_info(pokedex, &info_pokedex);
    pa2m_afirmar(resultado_obtener_informacion, "Se pudo recopilar informacion de la pokedex");
    if(!resultado_obtener_informacion) {
        tp1_destruir(pokedex);
    }

    pa2m_afirmar(info_pokedex.total == cantidad_pokemones, "La cantidad de pokemones en la pokedex %i, coincide con la cantidad de pokemones en el archivo %i", info_pokedex.total, cantidad_pokemones);
    pa2m_afirmar(info_pokedex.rarezas_distintas == cantidad_rarezas_distintas, "La cantidad de rarezas en la pokedex %i, coincide con la cantidad de rarezas distintas en el archivo %i", info_pokedex.rarezas_distintas, cantidad_rarezas_distintas);

	pa2m_afirmar(strcmp(mas_veloz, info_pokedex.mas_veloz->nombre) == 0,
		     "El pokemon %s es el mas veloz de la pokedex.", mas_veloz);
    pa2m_afirmar(strcmp(menos_veloz, info_pokedex.menos_veloz->nombre) == 0,
		     "El pokemon %s es el menos veloz de la pokedex.", menos_veloz);
    pa2m_afirmar(strcmp(mas_pesado, info_pokedex.mas_pesado->nombre) == 0,
		     "El pokemon %s es el mas pesado de la pokedex.", mas_pesado);
    pa2m_afirmar(strcmp(menos_pesado, info_pokedex.menos_pesado->nombre) == 0,
		     "El pokemon %s es el menos pesado de la pokedex.\n", menos_pesado);
    

	tp1_destruir(pokedex);
}

void prueba_obtener_informacion_pokedex_solamente_un_pokemon() {
    const char *unico_pokemon = "Charizard";
    const int cantidad_pokemones = 1;
    const int cantidad_rarezas_distintas = 1;

	tp1_t *pokedex = tp1_leer_archivo("./pruebas/archivos/pokemon.csv");
    pa2m_afirmar(pokedex != NULL, "Se pudo procesar el archivo y obtener la pokedex");
    if(!pokedex) return;

    struct pokedex_info info_pokedex = { 0 };

    bool resultado_obtener_informacion = pokedex_obtener_info(pokedex, &info_pokedex);
    pa2m_afirmar(resultado_obtener_informacion, "Se pudo recopilar informacion de la pokedex");
    if(!resultado_obtener_informacion) {
        tp1_destruir(pokedex);
    }

    pa2m_afirmar(info_pokedex.total == cantidad_pokemones, "La cantidad de pokemones en la pokedex %i, coincide con la cantidad de pokemones en el archivo %i", info_pokedex.total, cantidad_pokemones);
    pa2m_afirmar(info_pokedex.rarezas_distintas == cantidad_rarezas_distintas, "La cantidad de rarezas en la pokedex %i, coincide con la cantidad de rarezas distintas en el archivo %i", info_pokedex.rarezas_distintas, cantidad_rarezas_distintas);

	pa2m_afirmar(strcmp(unico_pokemon, info_pokedex.mas_veloz->nombre) == 0,
		     "El pokemon %s es el mas veloz de la pokedex debido a que es el unico.", unico_pokemon);
    pa2m_afirmar(strcmp(unico_pokemon, info_pokedex.menos_veloz->nombre) == 0,
		     "El pokemon %s es el menos veloz de la pokedex debido a que es el unico..", unico_pokemon);
    pa2m_afirmar(strcmp(unico_pokemon, info_pokedex.mas_pesado->nombre) == 0,
		     "El pokemon %s es el mas pesado de la pokedex debido a que es el unico..", unico_pokemon);
    pa2m_afirmar(strcmp(unico_pokemon, info_pokedex.menos_pesado->nombre) == 0,
		     "El pokemon %s es el menos pesado de la pokedex debido a que es el unico..\n", unico_pokemon);
    

	tp1_destruir(pokedex);
}


void prueba_obtener_informacion_pokedex_dos_rarezas_distintas() {
    const int cantidad_pokemones = 5;
    const int cantidad_rarezas_distintas = 2;

	tp1_t *pokedex = tp1_leer_archivo("./pruebas/archivos/pokemones_dos_rarezas.csv");
    pa2m_afirmar(pokedex != NULL, "Se pudo procesar el archivo y obtener la pokedex");
    if(!pokedex) return;

    struct pokedex_info info_pokedex = { 0 };

    bool resultado_obtener_informacion = pokedex_obtener_info(pokedex, &info_pokedex);
    pa2m_afirmar(resultado_obtener_informacion, "Se pudo recopilar informacion de la pokedex");
    if(!resultado_obtener_informacion) {
        tp1_destruir(pokedex);
    }

    pa2m_afirmar(info_pokedex.total == cantidad_pokemones, "La cantidad de pokemones en la pokedex %i, coincide con la cantidad de pokemones en el archivo %i", info_pokedex.total, cantidad_pokemones);
    pa2m_afirmar(info_pokedex.rarezas_distintas == cantidad_rarezas_distintas, "La cantidad de rarezas en la pokedex %i, coincide con la cantidad de rarezas distintas en el archivo %i", info_pokedex.rarezas_distintas, cantidad_rarezas_distintas);    

	tp1_destruir(pokedex);
}

void pruebas_juego() {

    pa2m_nuevo_grupo("Prueba obtener informacion de una pokedex con parametros invalidos");
    prueba_obtener_informacion_parametros_invalidos();

    pa2m_nuevo_grupo("Prueba obtener informacion pokedex completa");
    prueba_obtener_informacion_pokedex();

    pa2m_nuevo_grupo("Prueba obtener informacion pokedex con un solo pokemon");
    prueba_obtener_informacion_pokedex_solamente_un_pokemon();

    pa2m_nuevo_grupo("Prueba obtener informacion pokedex con dos rarezas y cinco pokemones");
    prueba_obtener_informacion_pokedex_dos_rarezas_distintas();

}
