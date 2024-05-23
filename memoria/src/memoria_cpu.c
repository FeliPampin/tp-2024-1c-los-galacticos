// #include "../includes/memoria_cpu.h"

// void atender_memoria_cpu(){
// while (1) {
// 		int cod_op = recibir_operacion(fd_cpu);
// 		switch (cod_op) {
// 			case MENSAJE:
// 				// recibir_mensaje(fd_cpu);
// 			break;

// 			case PAQUETE:
// 				// lista = recibir_paquete(fd_cpu);
// 				// log_info(memoria_logger, "Me llegaron los siguientes valores:\n");
// 				// list_iterate(lista, (void*) iterator);
// 			break;
			
// 			case -1:
// 				log_error(memoria_logger, "el cliente se desconecto. Terminando servidor");
// 				exit(EXIT_FAILURE);
// 			default:
// 				log_warning(memoria_logger,"Operacion desconocida. No quieras meter la pata");
// 			break;
// 		}
// 	}

// }