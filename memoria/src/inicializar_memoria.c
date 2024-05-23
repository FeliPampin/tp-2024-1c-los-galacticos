#include "../includes/inicializar_memoria.h"

void inicializar_memoria(){
    inicializar_logs();
    inicializar_configs();
    imprimir_configs();
}

void inicializar_logs(){
    memoria_logger = log_create("cliente.log", "CLIENTE_LOG", 1, LOG_LEVEL_INFO);
	if (memoria_logger == NULL)
	{
	 	perror("Algo ocurrio con el log");   
	 	exit(EXIT_FAILURE);
 	}



    memoria_log_debug = log_create("cliente.log", "CLIENTE_LOG", 1, LOG_LEVEL_INFO);
	if (memoria_log_debug == NULL)
 	{
		perror("Algo ocurrio con el log");
		exit(EXIT_FAILURE);
 	}
	printf("\nLogs inicializados");
}

void inicializar_configs(){
    
    memoria_config = config_create("/home/utnso/tp-2024-1c-los-galacticos/memoria/memoria_config.config"); // ACA CADA UNO DEBE COPIAR SU DIRECCION CON PWD EN CONSOLA
	if (memoria_config == NULL)
 	{
		perror("Algo ocurrio con la config");
		exit(EXIT_FAILURE);
	}

	PUERTO_ESCUCHA = config_get_int_value( memoria_config,"PUERTO_ESCUCHA");
	TAM_MEMORIA = config_get_int_value(memoria_config,"TAM_MEMORIA");
	TAM_PAGINA = config_get_int_value(memoria_config,"TAM_PAGINA");
	PATH_INSTRUCCIONES = config_get_string_value(memoria_config,"PATH_INSTRUCCIONES");
	RETARDO_RESPUESTA= config_get_int_value(memoria_config,"RETARDO_RESPUESTA");
	printf("\nConfigs inicializados");
}

void imprimir_configs(){
	log_info(memoria_logger,"PATH_INSTRUCCIONES: %s",PATH_INSTRUCCIONES);
}