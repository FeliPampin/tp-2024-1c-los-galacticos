#include "../includes/cpu_memoria.h"

void atender_cpu_memoria(){
while (1) {
		int cod_op = recibir_operacion(fd_memoria);
		switch (cod_op) {
			case MENSAJE:
				// recibir_mensaje(fd_memoria);
			break;

			case PAQUETE:
				// lista = recibir_paquete(fd_memoria);
				// log_info(cpu_logger, "Me llegaron los siguientes valores:\n");
				// list_iterate(lista, (void*) iterator);
			break;

			case CREAR_PROCESO_KM: 
				printf("llego\n");
				un_buffer = recibir_buffer(fd_memoria);
				atender_crear_proceso(un_buffer);
			break;
			
			case -1:
				log_error(cpu_logger, "el cliente se desconecto. Terminando servidor");
				exit(EXIT_FAILURE);
			default:
				log_warning(cpu_logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}

}

void atender_crear_proceso(t_buffer* un_buffer){
	int pid = extraer_int_buffer(un_buffer);
	char* path = extraer_string_buffer(un_buffer);
	int size = extraer_int_buffer(un_buffer);

	log_info(cpu_logger, "<PID:%d><PATH:%s><SIZE:%d>",pid,path,size);

	free(path);
}