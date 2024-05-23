#include <stdlib.h>
#include <stdio.h>
#include <utils/hello.h>
#include <pthread.h>


extern t_log* memoria_logger;
extern t_log* memoria_log_debug;
extern t_config* memoria_config;

extern int fd_memoria;
extern int fd_cpu;
extern int fd_entradasalida;
extern int fd_kernel;

extern int PUERTO_ESCUCHA;
extern int TAM_MEMORIA;
extern int TAM_PAGINA;
extern char* PATH_INSTRUCCIONES;
extern int RETARDO_RESPUESTA;