#include "operaciones.h"

//extern char *msgRetorno;

void escribime_en_el(int registro, int numero)
{
	switch(registro)
	{
		case 'A':
			tcb->a = numero;
			return;
		case 'B':
			tcb->b = numero;
			return;
		case 'C':
			tcb->c = numero;
			return;
		case 'D':
			tcb->d = numero;
			return;
		case 'E':
			tcb->e = numero;
			return;
		case 'M':
			tcb->baseSegCod = numero;
			return;
		case 'P':
			tcb->punteroInstruccion = numero;
			return;
		case 'X':
			tcb->baseStack = numero;
			return;
		case 'S':
			tcb->cursorStack = numero;
			return;
	}
	//setear algun error
}

int el_valor_del(int registro)
{
	switch(registro)
	{
		case 'A':
			return tcb->a;
		case 'B':
			return tcb->b;
		case 'C':
			return tcb->c;
		case 'D':
			return tcb->d;
		case 'E':
			return tcb->e;
		case 'M':
			return tcb->baseSegCod;
		case 'P':
			return tcb->punteroInstruccion;
		case 'X':
			return tcb->baseStack;
		case 'S':
			return tcb->cursorStack;
	}
	//setear algun error
	return -1;
}




// Operaciones de memoria


/*

int malc(t_tcb* tcb) {
	int resultadoCreacion=0;

	char *msgError;

	if (tcb->a==0)
		// Este error hace abortar la ejecucion ya que no se especifica la memoria a pedir
		return ERR_MEMORIA_MALC;

	resultadoCreacion = crearSegmento(tcb->pid,tcb->a,msgError);

	if (resultadoCreacion == ERROR) {
		msgRetorno=msgError;
		return ERROR;
	}
	else
		tcb->a=resultadoCreacion;

	return 0;

}

int freeseg(t_tcb* tcb) {
	int resultadoDestruccion;

	char *msgError;

	if (tcb->a==0)
		// Este error hace abortar la ejecucion ya que no se especifica la direccion del segmento a destruir
		return ERR_MEMORIA_MALC;

	resultadoDestruccion = destruirSegmento(tcb->pid,tcb->a,msgError);
	return resultadoDestruccion;

}

// Interrupcion

void inte(t_tcb *tcb, uint32_t direccion) {
	enviarInterrupcionAKernel(tcb, direccion, socketKernel);
}




// *** Servicios del kernel ***

int invocarServicioKernel(t_tcb* tcb, int servicioKernel) {
	int resultado = 0;
	char *mensaje = servicioKernel;
	resultado = send(socketKernel, mensaje, sizeof(*mensaje), MSG_NOSIGNAL);

	if (resultado==-1)
		return ERR_FALLOENVIO;

	return atoi(deserializar_respuesta_solicitud(socketKernel));
}

// ****** Funciones privadas ******


void enviarInterrupcionAKernel(t_tcb *tcb, uint32_t direccion, int socketKernel) {
	;
}

*/
















char *leer_de_memoria(u_int32_t pid, u_int32_t direccion, u_int32_t tamanio)
{
	t_solicitar solicitud;
	solicitud.PID = pid;
	solicitud.tamanio = tamanio;
	solicitud.dirLogica = direccion;
	size_t size = sizeof(int32_t) * 2 + sizeof(t_solicitar);
	void *mensajeSerializado = serializar_solicitar_segmento(solicitud, LEERSEG);
	send(msp.socket, mensajeSerializado, size, 0);
	free(mensajeSerializado);

	// ahora esperamos la respuesta
	int32_t tipo;
	recv(msp.socket, &tipo, sizeof(int32_t), 0);
	if (tipo == LEERSEGOK)
	{
		char *lectura = deserializar_respuesta_solicitud(msp.socket);
		return lectura;
	}
	if (tipo == ERROR)
	{
		//char *lectura = deserializar_respuesta_error_MSP(socketMSP);
		//aca se deberia de guardar el error en algun lado
		return NULL;
	}
	exit(1);
}

int escribir_en_memoria(u_int32_t pid, u_int32_t direccion, u_int32_t tamanio, char *bytesAEscribir)
{
	t_escribir solicitud;
	solicitud.PID = pid;
	solicitud.tamanio = tamanio;
	solicitud.dirLogica = direccion;
	memcpy(solicitud.buffer, bytesAEscribir, tamanio);
	size_t size = sizeof(int32_t) * 2 + sizeof(int32_t) * 3 + tamanio;
	void *mensajeSerializado = serializar_escribir_segmento(solicitud, ESCRIBIRSEG);
	send(msp.socket, mensajeSerializado, size, 0);
	free(mensajeSerializado);

	// ahora esperamos la respuesta
	int32_t tipo;
	recv(msp.socket, &tipo, sizeof(int32_t), 0);
	if (tipo == ESCRIBIRSEGOK) return OK;
	if (tipo == ERROR)
	{
		//analizar error
		return ERROR;
	}
	exit(1);
}

/*
int crearSegmento(int32_t pid, u_int32_t tamanio, char *msgError){

	int32_t baseSegCod = 0;
	
	t_crear solicitud;
	solicitud.PID=pid;
	solicitud.tamanio=tamanio;

	int32_t tamanio_mensaSerializado = sizeof(int32_t)+sizeof(int32_t)+sizeof(solicitud.PID)+sizeof(solicitud.tamanio);

			//Enviamos la operacion a la MSP
	char * mensaje = serializar_crear_segmento(solicitud, RESERVASEG);
	if ( send(socketMSP, mensaje, tamanio_mensaSerializado, MSG_NOSIGNAL) == -1 ){
			printf("Error al solicitar creación de segmento en la MSP... \n");
		   exit(1);
	}
	free(mensaje);
	//Recibimos el tipo de respuesta:
	int32_t * tipo = malloc(sizeof(int32_t));
	if (recv(socketMSP, tipo, sizeof(int32_t), 0) == -1){
			printf("Error al recibir respuesta de creación de segmento en la MSP... \n");
			exit(1);
	}


    if (tipo==RESERVASEGOK)
       return deserializar_respuesta_segmento(socketMSP);
    else {
    	*msgError = deserializar_respuesta_error_MSP(socketMSP);
       return ERROR;
    }


}

int destruirSegmento(int32_t pid, u_int32_t direccion, char *msgError){ //el pid es int y la direccion u_int
    
    t_destruir solicitudDestruccion;
    solicitudDestruccion.PID=pid;
    solicitudDestruccion.baseSegmento=direccion;

    //CALCULO ACA EL TAMANIO DE MENSAJE, ES MAS SEGURO. Tipo+tamanioMensajeInterno+MensajeInterno
    int32_t tamanio_mensaSerializado = sizeof(int32_t)+sizeof(int32_t)+sizeof(solicitudDestruccion.PID)+sizeof(solicitudDestruccion.baseSegmento);
	//Enviamos la operacion a la MSP
	char * mensaje = serializar_destruir_segmento(solicitudDestruccion, DESTRUIRSEG );
	if ( send(socketMSP, mensaje, tamanio_mensaSerializado, MSG_NOSIGNAL) == -1 ){
			printf("Error al solicitar destruccion de segmento en la MSP... \n");
		   exit(1);
	}

	free(mensaje);
	//Recibimos el tipo de respuesta:

	int32_t * tipo = malloc(sizeof(int32_t));
	if (recv(socketMSP, tipo, sizeof(int32_t), 0) == -1){
			printf("Error al recibir respuesta de destruccion de segmento en la MSP... \n");
			exit(1);
	}
    
    if (tipo==DESTRUIRSEGOK)
       return 0;
    else {
    	*msgError = deserializar_respuesta_error_MSP(socketMSP);
       return ERROR;
    }
        
}
*/
