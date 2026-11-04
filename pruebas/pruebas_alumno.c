#include "pa2m.h"
#include "pruebas.h"
#include <stdio.h>


int main()
{
	pa2m_nuevo_grupo("============== PRUEBAS DEL TP2 ===============");

	pa2m_nuevo_grupo("Pruebas del Menu");
	pruebas_menu();


	pa2m_nuevo_grupo("Pruebas del TP1");
	pruebas_leer_linea();

	pruebas_buscar();

	pruebas_combinar();

	pa2m_nuevo_grupo("Pruebas de archivos TP1");
	pruebas_archivos();

	pruebas_iterar();

	return pa2m_mostrar_reporte();
}
