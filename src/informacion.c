#include "informacion.h"

#define CANTIDAD_RAREZAS 3

typedef struct contexto_para_iterar {
	size_t contadores[CANTIDAD_RAREZAS];
	struct pokemon *mas_veloz;
	struct pokemon *menos_veloz;
	struct pokemon *mas_pesado;
	struct pokemon *menos_pesado;
} contexto_para_iterar_t;

/*
 * Actualiza y recopila toda la informacion necesaria de la pokedex iterando cada pokemon y realizando comparaciones.
 * En caso de que dos pokemones tengan el mismo peso o la misma velocidad, se queda con registro que ya esta almacenado.
 * Devuelve false si pokemon o contexto son NULL, true en caso contrario
 */
bool acumular_informacion(struct pokemon *pokemon, void *contexto)
{
    if(!pokemon || !contexto) return false;
    contexto_para_iterar_t *datos = contexto;
    datos->contadores[pokemon->rareza]++;

    if(!datos->mas_pesado)  {
        datos->menos_pesado = pokemon;
        datos->mas_veloz = pokemon;
        datos->menos_veloz = pokemon;
        datos->mas_pesado = pokemon;
    } 

    if(datos->mas_pesado->peso < pokemon->peso) datos->mas_pesado = pokemon;
    if(datos->menos_pesado->peso > pokemon->peso) datos->menos_pesado = pokemon;
    if(datos->mas_veloz->velocidad < pokemon->velocidad) datos->mas_veloz = pokemon;
    if(datos->menos_veloz->velocidad > pokemon->velocidad) datos->menos_veloz = pokemon;
    
    return true;
}

/*
 * Define todos los punteros en NULL, y ademas establece que la cantidad total de pokemones y rarezas distintas es 0.
 */
void inicializar_info(struct pokedex_info *info) {
    if(!info) return;
    info->total = 0;
    info->rarezas_distintas = 0;
    info->mas_veloz = NULL;
    info->menos_veloz = NULL;
    info->mas_pesado = NULL;
    info->menos_pesado = NULL;
}

/*
 * Recorre la pokedex y completa 'info'.
 * Devuelve false si pokedex o info son NULL. Con la pokedex vacía,
 * total es 0 y los punteros quedan en NULL.
 */
bool pokedex_obtener_info(tp1_t *pokedex, struct pokedex_info *info) {
    if(!pokedex || !info) return false;

    inicializar_info(info);
    contexto_para_iterar_t contexto = { 0 };

    info->total = tp1_iterar(pokedex, acumular_informacion, &contexto);

    for(size_t i = 0; i < CANTIDAD_RAREZAS; i++) {
        if(contexto.contadores[i] >= 1)
            info->rarezas_distintas++;
    }
    info->mas_pesado = contexto.mas_pesado;
    info->mas_veloz = contexto.mas_veloz;
    info->menos_pesado = contexto.menos_pesado;
    info->menos_veloz = contexto.menos_veloz;


    return true;
}