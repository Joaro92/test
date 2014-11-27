#ifndef CONSTANTES
#define CONSTANTES

#include <commons/config.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <network/network.h>


// Otros defines
#define OK 1201
#define ZERO_DIV 1202

// Instrucciones en forma numerica
#define LOAD 0x44414F4C
#define GETM 0x4D544547
#define SETM 0x4D544553
#define MOVR 0x52564F4D
#define ADDR 0x52444441
#define SUBR 0x52425553
#define MULR 0x524C554D
#define MODR 0x52444F4D
#define DIVR 0x52564944
#define INCR 0x52434E49
#define DECR 0x52434544
#define COMP 0x504D4F43
#define CGEQ 0x51454743
#define CLEQ 0x51454C43
#define GOTO 0x4F544F47
#define JMPZ 0x5A504D4A
#define JPNZ 0x5A4E504A
#define INTE 0x45544E49
#define SHIF 0x46494853
#define NOPP 0x50504F4E
#define PUSH 0x48535550
#define TAKE 0x454B4154
#define XXXX 0x58585858
#define MALC 0x434C414D
#define FREE 0x45455246
#define INNN 0x4E4E4E49
#define INNC 0x434E4E49
#define OUTN 0x4E54554F
#define OUTC 0x4354554F
#define CREA 0x41455243
#define JOIN 0x4E494F4A
#define BLOK 0x4B4F4C42
#define WAKE 0x454B4157

// Variables globales

typedef struct {
	int socket;
	int puerto;
	char *ip;
} t_socket;


t_tcb* tcb;
t_socket msp;
t_socket kernel;

#endif
