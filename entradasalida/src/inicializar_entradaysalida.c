#include "../includes/inicializar_entradaysalida.h"

void inicializar_entradasalida(){
    inicializar_logs();
    inicializar_configs();
    imprimir_configs();
}

void inicializar_logs(){
    entradasalida_logger = log_create("cliente.log", "CLIENTE_LOG", 1, LOG_LEVEL_INFO);
    if (entradasalida_logger == NULL)
    {
	    perror("Algo ocurrió con el log");
	    exit(EXIT_FAILURE);
    }

    entradasalida_log_debug = log_create("cliente.log", "CLIENTE_LOG", 1, LOG_LEVEL_INFO);
    if (entradasalida_log_debug == NULL)
    {
	    perror("Algo ocurrió con el log");
	    exit(EXIT_FAILURE);
    }
}

void inicializar_configs(){
    entradasalida_config = config_create("/home/utnso/tp-2024-1c-los-galacticos/entradasalida/entradasalida_config.config"); // ACA CADA UNO DEBE COPIAR SU DIRECCION CON PWD EN CONSOLA
    if (entradasalida_config == NULL)
    {
	    perror("Algo ocurrió con la config");
	    exit(EXIT_FAILURE);
    }

    TIPO_INTERFAZ = config_get_string_value(entradasalida_config,"TIPO_INTERFAZ");
    TIEMPO_UNIDAD_TRABAJO = config_get_int_value(entradasalida_config,"TIEMPO_UNIDAD_TRABAJO");
    IP_KERNEL = config_get_string_value(entradasalida_config,"IP_KERNEL");
    PUERTO_KERNEL = config_get_string_value(entradasalida_config,"PUERTO_KERNEL");
    IP_MEMORIA = config_get_string_value(entradasalida_config,"IP_MEMORIA");
    PUERTO_MEMORIA = config_get_string_value(entradasalida_config,"PUERTO_MEMORIA");
    PATH_BASE_DIALFS = config_get_string_value(entradasalida_config,"PATH_BASE_DIALFS");
    BLOCK_SIZE = config_get_int_value(entradasalida_config,"BLOCK_SIZE");
    BLOCK_COUNT = config_get_int_value(entradasalida_config,"BLOCK_COUNT");
    //RETRASO_COMPACTACION = config_get_int_value(entradasalida_config,"RETRASO_COMPACTACION");
}

void imprimir_configs(){
    log_info(entradasalida_logger,"IP_KERNEL: %s",IP_KERNEL);
}
