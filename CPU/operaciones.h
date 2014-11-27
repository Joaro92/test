#ifndef OPERACIONES_H_
#define OPERACIONES_H_

#include "cabecera.h"

//int crearSegmento(int32_t,u_int32_t, char*);
//int destruirSegmento(int32_t , u_int32_t, char*);
char *leer_de_memoria(u_int32_t pid, u_int32_t direccion, u_int32_t tamanio);
int escribir_en_memoria(u_int32_t pid, u_int32_t direccion, u_int32_t tamanio, char *bytesAEscribir);
int el_valor_del(int registro);
void escribime_en_el(int registro, int numero);

#endif /* OPERACIONES_H_ */
