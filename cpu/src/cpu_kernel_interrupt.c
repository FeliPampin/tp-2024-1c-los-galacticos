#include "../includes/cpu_kernel_interrupt.h"

void atender_cpu_kernel_interrupt(){
   while (1) {
		int cod_op = recibir_operacion(fd_kernel_interrupt);
		switch (cod_op) {
			case MENSAJE:
				// recibir_mensaje(fd_kernel_interrupt);
			break;

			case PAQUETE:
				// lista = recibir_paquete(fd_kernel_interrupt);
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