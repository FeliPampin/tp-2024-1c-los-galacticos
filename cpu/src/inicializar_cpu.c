#include "../includes/inicializar_cpu.h"

void inicializar_cpu(){
	inicializar_logs();
	inicializar_configs();
	imprimir_configs();
}

void inicializar_logs(){
	cpu_logger = log_create("cliente.log", "CLIENTE_LOG", 1, LOG_LEVEL_INFO);
	if (cpu_logger == NULL)
	{
		perror("Algo ocurrió con el log");
		exit(EXIT_FAILURE);
 	}

	cpu_log_debug = log_create("cliente.log", "CLIENTE_LOG", 1, LOG_LEVEL_INFO);
	if (cpu_log_debug == NULL)
	{
		perror("Algo ocurrió con el log");
		exit(EXIT_FAILURE);
 	}
}

void inicializar_configs(){
	cpu_config = config_create("/home/utnso/tp-2024-1c-los-galacticos/cpu/cpu_config.config"); // ACA CADA UNO DEBE COPIAR SU DIRECCION CON PWD EN CONSOLA
	if (cpu_config == NULL)
	{
		perror("Algo ocurrió con la config");
		exit(EXIT_FAILURE);
	}


    IP_MEMORIA = config_get_string_value(cpu_config,"IP_MEMORIA");
    PUERTO_MEMORIA = config_get_string_value(cpu_config,"PUERTO_MEMORIA");
	PUERTO_ESCUCHA_DISPATCH = config_get_string_value(cpu_config,"PUERTO_ESCUCHA_DISPATCH");
    PUERTO_ESCUCHA_INTERRUPT = config_get_string_value(cpu_config, "PUERTO_ESCUCHA_INTERRUPT");
	CANTIDAD_ENTRADAS_TLB = config_get_int_value(cpu_config, "CANTIDAD_ENTRADAS_TLB");
    ALGORITMO_TLB = config_get_string_value(cpu_config, "ALGORITMO_TLB" );
}

void imprimir_configs(){
    log_info(cpu_logger,"IP_MEMORIA: %s",IP_MEMORIA);
    log_warning(cpu_logger,"PUERTO_MEMORIA: %s",PUERTO_MEMORIA);
}
