#include <stdlib.h>
#include <stdio.h>
#include <utils/hello.h>
#include "k_gestor.h"

#include "inicializar_kernel.h"
#include "kernel_cpu_dispatch.h"
#include "kernel_cpu_interrupt.h"
#include "kernel_memoria.h"
#include "kernel_entradaysalida.h"

//AGREGO VARIABLES GLOBALES
t_log* kernel_logger;
t_log* kernel_log_debug;
t_config* kernel_config;

int fd_kernel;
int fd_memoria;
int fd_entradasalida;
int fd_cpu_dispatch;
int fd_cpu_interrupt;


int PUERTO_ESCUCHA;
char* IP_MEMORIA;
int PUERTO_MEMORIA;
char* IP_CPU;
int PUERTO_CPU_DISPATCH;
int PUERTO_CPU_INTERRUPT;
char* ALGORITMO_PLANIFICACION;
int QUANTUM;
char** RECURSOS;
char** INSTANCIAS_RECURSOS; 
int GRADO_MULTIPROGRAMACION;