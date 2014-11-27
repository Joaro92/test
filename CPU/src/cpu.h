#ifndef HEADER_CPU
#define HEADER_CPU

#include "cabecera.h"
#include "ejecutar.h"


// MIS VARIABLES -----------------------------------------------------------------

#define CONFIG_PATH "../bin/config.conf"


t_config *configuracion;
unsigned int retardo;


char r1;
char r2;
int valor;
int protegida;





// Definición de funciones
void cargar_archivo_de_configuracion(char *configPath);
int conectar_al_kernel();
int conectar_al_msp();
void enviar_handshake_al_kernel();


// otros a revisar
char* mapearError(int);
int enviarTCBAKernel(int,t_tcb*, int);

#endif
