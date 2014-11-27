#include "ejecutar.h"

int ejecutar(unsigned int instruccion)
{
	int resultado = OK;
	char registro1, registro2;
	int valor;
	int i;
	char *aux;
	int aux2;
	char *lectura;
	char *bytesAEscribir = malloc(sizeof(int));

	printf("estoy haciendo la instruccion %d\n", instruccion);
	switch(instruccion)
	{
		case LOAD:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 4);
			memcpy(&valor, aux, 4);
			tcb->punteroInstruccion += 4;

			escribime_en_el(registro1, valor);
			break;
		case GETM:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro2 = aux[0];
			tcb->punteroInstruccion += 1;

			lectura = leer_de_memoria(tcb->pid, el_valor_del(registro2), 1);
			//si no hubo error
			escribime_en_el(registro1, (int) lectura[0]);
			break;
		case SETM:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 4);
			memcpy(&valor, aux, 4);
			tcb->punteroInstruccion += 4;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro2 = aux[0];
			tcb->punteroInstruccion += 1;

			aux2 = el_valor_del(registro2);
			memcpy(bytesAEscribir, &aux2, sizeof(int));
			resultado = escribir_en_memoria(tcb->pid, el_valor_del(registro1), valor, bytesAEscribir);
			//ver si hubo error
			break;
		case MOVR:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro2 = aux[0];
			tcb->punteroInstruccion += 1;

			escribime_en_el(registro1, el_valor_del(registro2));
			break;
		case ADDR:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro2 = aux[0];
			tcb->punteroInstruccion += 1;

			tcb->a = el_valor_del(registro1) + el_valor_del(registro2);
			break;
		case SUBR:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro2 = aux[0];
			tcb->punteroInstruccion += 1;

			tcb->a = el_valor_del(registro1) - el_valor_del(registro2);
			break;
		case MULR:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro2 = aux[0];
			tcb->punteroInstruccion += 1;

			tcb->a = el_valor_del(registro1) * el_valor_del(registro2);
			break;
		case MODR:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro2 = aux[0];
			tcb->punteroInstruccion += 1;

			tcb->a = el_valor_del(registro1) % el_valor_del(registro2);
			break;
		case DIVR:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro2 = aux[0];
			tcb->punteroInstruccion += 1;

			if (el_valor_del(registro2) == 0) resultado = ZERO_DIV;
			else tcb->a = el_valor_del(registro1) / el_valor_del(registro2);
			break;
		case INCR:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;

			escribime_en_el(registro1, el_valor_del(registro1) + 1);
			break;
		case DECR:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;

			escribime_en_el(registro1, el_valor_del(registro1) - 1);
			break;
		case COMP:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro2 = aux[0];
			tcb->punteroInstruccion += 1;

			tcb->a = el_valor_del(registro1) == el_valor_del(registro2);
			break;
		case CGEQ:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro2 = aux[0];
			tcb->punteroInstruccion += 1;

			tcb->a = el_valor_del(registro1) >= el_valor_del(registro2);
			break;
		case CLEQ:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro2 = aux[0];
			tcb->punteroInstruccion += 1;

			tcb->a = el_valor_del(registro1) <= el_valor_del(registro2);
			break;
		case GOTO:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;

			tcb->punteroInstruccion = tcb->baseSegCod + el_valor_del(registro1);
			break;
		case JMPZ:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 4);
			memcpy(&valor, aux, 4);
			tcb->punteroInstruccion += 4;

			if (tcb->a == 0) tcb->punteroInstruccion = tcb->baseSegCod + valor;
			break;
		case JPNZ:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 4);
			memcpy(&valor, aux, 4);
			tcb->punteroInstruccion += 4;

			if (tcb->a != 0) tcb->punteroInstruccion = tcb->baseSegCod + valor;
			break;
		case INTE:
			//todavia nada

			break;
		case SHIF:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 4);
			memcpy(&valor, aux, 4);
			tcb->punteroInstruccion += 4;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;

			if (valor > 0) escribime_en_el(registro1, el_valor_del(registro1) >> valor);
			if (valor < 0) escribime_en_el(registro1, el_valor_del(registro1) << valor);
			break;
		case NOPP:
			// No hace nada
			break;
		case PUSH:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 4);
			memcpy(&valor, aux, 4);
			tcb->punteroInstruccion += 4;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;

			aux2 = el_valor_del(registro1);
			memcpy(bytesAEscribir, &aux2, sizeof(int));
			resultado = escribir_en_memoria(tcb->pid, tcb->cursorStack, valor, bytesAEscribir);
			//ver si hubo error
			tcb->cursorStack += valor;
			break;
		case TAKE:
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 4);
			memcpy(&valor, aux, 4);
			tcb->punteroInstruccion += 4;
			aux = leer_de_memoria(tcb->pid, tcb->punteroInstruccion, 1);
			registro1 = aux[0];
			tcb->punteroInstruccion += 1;

			lectura = leer_de_memoria(tcb->pid, tcb->cursorStack - valor, valor);
			//si no hubo error
			bzero(aux, 4);
			if (valor < 4) for(i = 3; i > 0; i--)
			{
				aux[i] = lectura[--valor];
				if (valor == 0) break;
			}
			memcpy(&valor, aux, 4);
			escribime_en_el(registro1, valor);
			break;
		case XXXX:
			resultado = finHilo;
			break;


		// SysCalls --------------------------------------------------------------

/*
		case MALC:
			resultado = malc(tcb);
			if (resultado == 0)
				tcb->punteroInstruccion += instruccion->tamanio;
			break;
		case FREE:
			resultado = freeseg(tcb);
			if (resultado == 0)
				tcb->punteroInstruccion += instruccion->tamanio;
			break;
		case INNN:
			resultado = invocarServicioKernel(tcb, entradaEstandarInt);
			if (resultado == 0)
				tcb->punteroInstruccion += instruccion->tamanio;
			break;
		case INNC:
			resultado = invocarServicioKernel(tcb, entradaEstandarChar);
			if (resultado == 0)
				tcb->punteroInstruccion += instruccion->tamanio;
			break;
		case OUTN:
			resultado = invocarServicioKernel(tcb, salidaEstandarInt);
			if (resultado == 0)
				tcb->punteroInstruccion += instruccion->tamanio;
			break;
		case OUTC:
			resultado = invocarServicioKernel(tcb, salidaEstandarChar);
			if (resultado == 0)
				tcb->punteroInstruccion += instruccion->tamanio;
			break;
		case CREA:
			resultado = invocarServicioKernel(tcb, crearHilo);
			if (resultado == 0)
				tcb->punteroInstruccion += instruccion->tamanio;
			break;
		case JOIN:
			resultado = invocarServicioKernel(tcb, join);
			if (resultado == 0)
				tcb->punteroInstruccion += instruccion->tamanio;
			break;
		case BLOK:
			resultado = invocarServicioKernel(tcb, join);
			if (resultado == 0)
				tcb->punteroInstruccion += instruccion->tamanio;
			break;
		case WAKE:
			resultado = invocarServicioKernel(tcb, despertar);
			if (resultado == 0)
				tcb->punteroInstruccion += instruccion->tamanio;
			break;
*/
		default:
			puts("Instrucción invalida");
			exit(1);
	}

	return resultado;
}
