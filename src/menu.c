#include "src/menu.h"

struct opcion {
	char tecla;
    char *texto;
    bool seleccionada;
    int (*f)(void* , void*);
    void *contexto;
};