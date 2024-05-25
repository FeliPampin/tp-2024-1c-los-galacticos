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
#include<readline/readline.h>
#include<errno.h>

typedef enum
{
	MENSAJE,
	PAQUETE,
	CREAR_PROCESO_KM
}op_code;

typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;




void decir_hola(char* quien);
int crear_conexion(char *ip, int puerto);
int iniciar_servidor(int puerto, t_log* un_log, char* mensaje_servidor);
int esperar_cliente(int socket_servidor, t_log* un_log,char* msj);
int recibir_operacion(int socket_cliente);
void recibir_mensaje(int socket_cliente);
t_list* recibir_paquete(int socket_cliente);

t_buffer* crear_buffer();
void* extraer_cosas_del_buffer(t_buffer* un_buffer);
t_buffer* recibir_buffer(int conexion);
void enviar_paquete(t_paquete* paquete, int conexion);
int extraer_int_buffer (t_buffer* un_buffer);
char* extraer_string_buffer(t_buffer* un_buffer);
void cargar_string_al_buffer(t_buffer* un_buffer, char* un_string);
void cargar_cosas_al_buffer(t_buffer* un_buffer, void* una_cosa, int size_cosas);
t_paquete* crear_paquete(op_code cod_op, t_buffer* un_buffer);
void destruir_paquete(t_paquete* un_paquete);
void cargar_int_al_buffer(t_buffer* un_buffer, int int_value);
void cargar_uint32_al_buffer(t_buffer* un_buffer, uint32_t un_valor);
uint32_t extraer_uint32_del_buffer(t_buffer* un_buffer);
//void agregar_a_paquete( t_paquete* paquete, void* valor, int tamanio);
void* serializar_paquete(t_paquete* un_paquete);

#endif
