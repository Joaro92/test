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
#define LOAD 0x4C4F4144
#define GETM 0x4745544D
#define SETM 0x5345544D
#define MOVR 0x4D4F5652
#define ADDR 0x41444452
#define SUBR 0x53554252
#define MULR 0x4D554C52
#define MODR 0x4D4F4452
#define DIVR 0x44495652
#define INCR 0x494E4352
#define DECR 0x44454352
#define COMP 0x434F4D50
#define CGEQ 0x43474551
#define CLEQ 0x434C4551
#define GOTO 0x474F544F
#define JMPZ 0x4A4D505A
#define JPNZ 0x4A504E5A
#define INTE 0x494E5445
#define SHIF 0x53484946
#define NOPP 0x4E4F5050
#define PUSH 0x50555348
#define TAKE 0x54414B45
#define XXXX 0x58585858
#define MALC 0x4D414C43
#define FREE 0x46524545
#define INNN 0x494E4E4E
#define INNC 0x494E4E43
#define OUTN 0x4F55544E
#define OUTC 0x4F555443
#define CREA 0x43524541
#define JOIN 0x4A4F494E
#define BLOK 0x424C4F4B
#define WAKE 0x57414B45

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
