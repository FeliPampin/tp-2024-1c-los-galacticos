#include "../includes/inicializar_kernel.h"

void inicializar_kernel(){
    inicializar_logs();
    inicializar_configs();
    imprimir_configs();
}

void inicializar_logs(){
    kernel_logger = log_create("cliente.log", "CLIENTE_LOG", 1, LOG_LEVEL_INFO);
	if (kernel_logger == NULL)
	{
		perror("Algo ocurrió con el log");
		exit(EXIT_FAILURE);
	}

	kernel_log_debug = log_create("cliente.log", "CLIENTE_LOG", 1, LOG_LEVEL_INFO);
	if (kernel_log_debug == NULL)
	{
		perror("Algo ocurrió con el log");
		exit(EXIT_FAILURE);
	}
}

void inicializar_configs(){
	kernel_config = config_create("/home/utnso/tp-2024-1c-los-galacticos/kernel/kernel_config.config"); // ACA CADA UNO DEBE COPIAR SU DIRECCION CON PWD EN CONSOLA
	if (kernel_config == NULL)
	{
		perror("Algo ocurrió con la config");
		exit(EXIT_FAILURE);
	}

	PUERTO_ESCUCHA = config_get_string_value(kernel_config,"PUERTO_ESCUCHA");
	IP_MEMORIA = config_get_string_value(kernel_config,"IP_MEMORIA");
	PUERTO_MEMORIA = config_get_string_value(kernel_config,"PUERTO_MEMORIA");
	IP_CPU = config_get_string_value(kernel_config,"IP_CPU");
	PUERTO_CPU_DISPATCH = config_get_string_value(kernel_config,"PUERTO_CPU_DISPATCH");
	PUERTO_CPU_INTERRUPT = config_get_string_value(kernel_config,"PUERTO_CPU_INTERRUPT");
	ALGORITMO_PLANIFICACION = config_get_string_value(kernel_config,"ALGORITMO_PLANIFICACION");
	QUANTUM = config_get_int_value(kernel_config,"QUANTUM");
	RECURSOS = config_get_array_value(kernel_config,"RECURSOS");
	INSTANCIAS_RECURSOS = config_get_array_value(kernel_config,"INSTANCIAS_RECURSOS");
	GRADO_MULTIPROGRAMACION = config_get_int_value(kernel_config,"GRADO_MULTIPROGRAMACION");

}

void imprimir_configs(){
    log_info(kernel_logger,"IP_MEMORIA: %s",IP_MEMORIA);
	log_info(kernel_logger,"[RECURSOS]: %s|%s|%s",RECURSOS[0],RECURSOS[1],RECURSOS[2]);
	log_info(kernel_logger,"[INSTANCIAS_RECURSOS]: %s|%s|%s",INSTANCIAS_RECURSOS[0],INSTANCIAS_RECURSOS[1],INSTANCIAS_RECURSOS[2]);
}