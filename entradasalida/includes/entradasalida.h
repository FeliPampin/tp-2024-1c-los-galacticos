#include "eys_gestor.h"
#include "inicializar_entradaysalida.h"
#include "entradasalida_kernel.h"
#include "entradasalida_memoria.h"


t_log* entradasalida_logger;
t_log* entradasalida_log_debug;
t_config* entradasalida_config;

int fd_memoria;
int fd_entradasalida;
int fd_kernel;

char* TIPO_INTERFAZ;
int TIEMPO_UNIDAD_TRABAJO; 
char* IP_KERNEL;
char* PUERTO_KERNEL; 
char* IP_MEMORIA;
char* PUERTO_MEMORIA; 
char* PATH_BASE_DIALFS; 
int BLOCK_SIZE;
int BLOCK_COUNT; 
int RETRASO_COMPACTACION;