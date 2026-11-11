#include "tp1.h"

#define RARO 'R'
#define COMUN 'C'
#define LEGENDARIO 'L'

struct pokedex_info {
	size_t total;
	size_t rarezas_distintas;
	struct pokemon *mas_veloz;
	struct pokemon *menos_veloz;
	struct pokemon *mas_pesado;
	struct pokemon *menos_pesado;
};

/*
 * Recorre la pokedex y completa 'info'.
 * Devuelve false si pokedex o info son NULL. Con la pokedex vacía,
 * total es 0 y los punteros quedan en NULL.
 */
bool pokedex_obtener_info(tp1_t *pokedex, struct pokedex_info *info);