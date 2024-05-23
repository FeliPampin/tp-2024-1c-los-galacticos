// #include "../includes/entradasalida_memoria.h"

// void atender_entradasalida_memoria(){
// while (1) {
// 		int cod_op = recibir_operacion(fd_memoria);
// 		switch (cod_op) {
// 			case MENSAJE:
// 				// recibir_mensaje(fd_memoria);
// 			break;

// 			case PAQUETE:
// 				// lista = recibir_paquete(fd_memoria);
// 				// log_info(entradasalida_logger, "Me llegaron los siguientes valores:\n");
// 				// list_iterate(lista, (void*) iterator);
// 			break;
			
// 			case -1:
// 				log_error(entradasalida_logger, "el cliente se desconecto. Terminando servidor");
// 				exit(EXIT_FAILURE);
// 			default:
// 				log_warning(entradasalida_logger,"Operacion desconocida. No quieras meter la pata");
// 			break;
// 		}
// 	}

// }