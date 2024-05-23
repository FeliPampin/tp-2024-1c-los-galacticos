#include "m_gestor.h"
#include "inicializar_memoria.h"
#include "memoria_cpu.h"
#include "memoria_entradasalida.h"
#include "memoria_kernel.h"

t_log* memoria_logger;
t_log* memoria_log_debug;
t_config* memoria_config;

int fd_memoria;
int fd_cpu;
int fd_entradasalida;
int fd_kernel;

int PUERTO_ESCUCHA;
int TAM_MEMORIA;
int TAM_PAGINA;
char* PATH_INSTRUCCIONES;
int RETARDO_RESPUESTA;