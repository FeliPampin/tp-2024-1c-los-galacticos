#include "../includes/kernel_entradaysalida.h"

void atender_kernel_entradasalida(){
   while (1) {
		int cod_op = recibir_operacion(fd_entradasalida);
		switch (cod_op) {
			case MENSAJE:
				// recibir_mensaje(fd_entradasalida);
			break;

			case PAQUETE:
				// lista = recibir_paquete(fd_entradasalida);
				// log_info(kernel_logger, "Me llegaron los siguientes valores:\n");
				// list_iterate(lista, (void*) iterator);
			break;

			case CREAR_PROCESO_KM:
				printf("llego\n");
				t_buffer* un_buffer = recibir_buffer(fd_entradasalida);
				atender_crear_proceso_entradaysalida(un_buffer);
			break;
			
			case -1:
				log_error(kernel_logger, "el cliente se desconecto. Terminando servidor");
				exit(EXIT_FAILURE);
			default:
				log_warning(kernel_logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	} 
}

void atender_crear_proceso_entradaysalida(t_buffer* un_buffer){
	int pid = extraer_int_buffer(un_buffer);
	char* path = extraer_string_buffer(un_buffer);
	int size = extraer_int_buffer(un_buffer);

	log_info(kernel_logger, "<PID:%d><PATH:%s><SIZE:%d>",pid,path,size);

	free(path);
}