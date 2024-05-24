#ifndef UTILS_HELLO_H_
#define UTILS_HELLO_H_

#include <stdlib.h>
#include <stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<commons/log.h>
#include<commons/config.h>
#include<errno.h>

typedef enum
{
	MENSAJE,
	PAQUETE
}op_code;

// typedef struct
// {
// 	int size;
// 	void* stream;
// } t_buffer;

// typedef struct
// {
// 	op_code codigo_operacion;
// 	t_buffer* buffer;
// } t_paquete;





void decir_hola(char* quien);
int crear_conexion(char *ip, int puerto);
int iniciar_servidor(int puerto, t_log* un_log, char* mensaje_servidor);
int esperar_cliente(int socket_servidor, t_log* un_log,char* msj);
// int recibir_operacion(int socket_cliente);
#endif
