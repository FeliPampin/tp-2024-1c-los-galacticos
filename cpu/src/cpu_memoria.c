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
			
			case -1:
				log_error(cpu_logger, "el cliente se desconecto. Terminando servidor");
				exit(EXIT_FAILURE);
			default:
				log_warning(cpu_logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}

}