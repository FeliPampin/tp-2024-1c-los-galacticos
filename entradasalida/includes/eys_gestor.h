#include <stdio.h>
#include <stdlib.h>
#include <utils/hello.h>
#include <pthread.h>


extern t_log* entradasalida_logger;
extern t_log* entradasalida_log_debug;
extern t_config* entradasalida_config;

extern int fd_memoria;
extern int fd_entradasalida;
extern int fd_kernel;

extern char* TIPO_INTERFAZ;
extern int TIEMPO_UNIDAD_TRABAJO; 
extern char* IP_KERNEL;
extern int PUERTO_KERNEL; 
extern char* IP_MEMORIA;
extern int PUERTO_MEMORIA; 
extern char* PATH_BASE_DIALFS; 
extern int BLOCK_SIZE;
extern int BLOCK_COUNT; 
extern int RETRASO_COMPACTACION;