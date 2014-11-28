#include "cpu.h"

int main(int argc, char *argv[])
{
	char *instruccionESO;
	unsigned int instruccion = 0;
	int resultadoEjecucion;
	cargar_archivo_de_configuracion(CONFIG_PATH);
	int header = 0;

	// Conectar con kernel
	if (conectar_al_kernel() == -1)
	{
		printf("No se pudo conectar con el kernel\n");
		exit(1);
	}
	printf("\nConexión con kernel establecida\n");
	enviar_handshake_al_kernel();

	// Conectar con MSP
	if (conectar_al_msp() == -1)
	{
		printf("No se pudo conectar con la MSP\n");
		exit(1);
	}
	printf("Conexión con MSP establecida\n");

	// Me quedo esperando TCBs del kernel
	while(1)
	{
		// Recibe desde socket los tcbs que vienen del kernel.
		recv(kernel.socket, &header, sizeof(int32_t), 0);
		if (header == solicitudEjecucion) tcb = deserializarTCB(kernel.socket);
		else
		{
			printf("me mandaron fruta %d", header);
			exit(1);
			//analizar porque me mandaron fruta
		}
		if (tcb == NULL)
		{
			//ver que pasa si no recibimos nada del kernel
		}
		printf("TCB recibido. PID: %d TID: %d Quantum: %d\n", tcb->pid, tcb->tid, tcb->quantum);

		// Mientras el quantum no se termine y el puntero no llegue a fin de codigo, sigo pidiendo instrucciones a la memoria para ejecutar
		while (tcb->quantum > 0)
		{
			instruccionESO = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 4);
			{
				//ver que pasa si no recibimos nada de la MSP
			}
			memcpy(&instruccion, instruccionESO, sizeof(int));
			tcb->punteroInstruccion += sizeof(int);

			resultadoEjecucion = ejecutar(instruccion);
			switch(resultadoEjecucion)
			{
				//INTE
				//finquantum
				//XXXX
				//error
				//analizar los posibles casos de finalizacion
			}
			tcb->quantum--;
			if (tcb->quantum == 0)
			{
				size_t size = sizeof(int32_t) * 2 + sizeof(t_tcb);
				char *mensajeSerializado = serializar_envio_TCB(*tcb, finQuantum);
				send(kernel.socket, mensajeSerializado, size, 0);
				free(mensajeSerializado);
			}
			usleep(retardo);
		}
	}
	//me pinche o algo
	exit(1);
}


// ----------------------------------------------------------------------


// Funciones privadas

void cargar_archivo_de_configuracion(char *configPath)
{
	configuracion = config_create(configPath);
	if (config_has_property(configuracion, "IP_MSP")) msp.ip = config_get_string_value(configuracion, "IP_MSP");
	if (config_has_property(configuracion, "PUERTO_MSP")) msp.puerto = config_get_int_value(configuracion, "PUERTO_MSP");
	if (config_has_property(configuracion, "IP_KERNEL")) kernel.ip = config_get_string_value(configuracion, "IP_KERNEL");
	if (config_has_property(configuracion, "PUERTO_KERNEL")) kernel.puerto = config_get_int_value(configuracion, "PUERTO_KERNEL");
	if (config_has_property(configuracion, "RETARDO")) retardo = config_get_int_value(configuracion, "RETARDO") * 1000;
	//por 1000 porque el usleep son microsegundos y el que viene en el archivo cfg son milisegundos

	printf("IP kernel: %s\n", kernel.ip);
	printf("Puerto kernel: %d\n", kernel.puerto);
	printf("IP MSP: %s\n", msp.ip);
	printf("Puerto MSP: %d\n", msp.puerto);
	printf("Retardo ejecución: %d milisegundos\n", retardo / 1000);
}

int conectar_al_kernel()
{
	kernel.socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in direccion;
	direccion.sin_addr.s_addr = inet_addr(kernel.ip);
	direccion.sin_port = htons(kernel.puerto);
	direccion.sin_family = AF_INET;
	return connect(kernel.socket, (struct sockaddr *) &direccion, sizeof(struct sockaddr));
}

int conectar_al_msp()
{
	msp.socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in direccion;
	direccion.sin_addr.s_addr = inet_addr(msp.ip);
	direccion.sin_port = htons(msp.puerto);
	direccion.sin_family = AF_INET;
	return connect(msp.socket, (struct sockaddr *) &direccion, sizeof(struct sockaddr));
}

void enviar_handshake_al_kernel()
{
	size_t size;
	void *mensajeSerializado = serializar_handshake(soyCpu, &size);
	send(kernel.socket, mensajeSerializado, size, 0);
	mensajeSerializado = serializar_handshake(estructuraCpu, &size);
	send(kernel.socket, mensajeSerializado, size, 0); //esta actualmente manejado como 2 handshake seguidos
	free(mensajeSerializado);
}





// ----------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------




/*
int enviarTCBAKernel(int socket, int codigoRetorno)
{
	char *msgRetorno=string_new();

	// Hay mensaje de retorno para las respuestas de la memoria

	char * mensaje = serializar_envio_TCB(*tcb, codigoRetorno, msgRetorno);


	if (!offlineKernel) {
	if ( send(socketKernel, mensaje, sizeof(*mensaje), MSG_NOSIGNAL) == -1 ){
			printf("Error al enviar tcb al kernel\n");
			exit(1);
	}
	free(mensaje);

	int32_t * tipo = malloc(sizeof(int32_t));
	if (recv(socketMSP, tipo, sizeof(int32_t), 0) == -1){
			printf("Error al recibir respuesta de envio de tcb al kernel\n");
			exit(1);
	}
	}

	if (offlineKernel)
		return 0;
	else
		return atoi(deserializar_respuesta_solicitud(socketKernel));
}

char* mapearError(int codigoError) {
	switch (codigoError) {
	case ERR_EJECUCION_DIVCERO:
		return "DIVR: Division por cero";
		break;
	case ERR_EJECUCION_INSTPROT:
		return "No se puede ejecutar la instruccion protegida en modo usuario";
		break;
	case MEMORIA_NOCONEXION:
		return "No hay conexion con la memoria";
		break;
	case ERR_MEMORIA_MALC:
		return "MALC: El valor del registro A es 0";
		break;
	case EJECUCION_TERMINAR:
		return "XXXX: Fin de programa";
		break;
	case MEMORIA_INSTRINVALIDA:
		return "Instruccion invalida";
		break;
	case EJECUCION_QUANTUMFINALIZADO:
		return "Ejecucion terminada por quantum";
		break;
	case MEMORIA_NODATOS:
		return "Error de transmision de datos con la MSP";
		break;
	}
}
*/
