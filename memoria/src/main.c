#include "../includes/memoria.h"

int main() {
	
	//INICIALIZO MEMORIA
	inicializar_memoria();

	//INICIAR SERVER DE MEMORIA
	fd_memoria = iniciar_servidor(PUERTO_ESCUCHA,memoria_logger,"MEMORIA HA SIDO INICIADA");
	if (fd_memoria == -1) {
        log_error(memoria_logger, "No se pudo iniciar el servidor de memoria");
        log_destroy(memoria_logger);
        return EXIT_FAILURE;
    }
	
	//ESPERAR CONEXION CPU
	log_info(memoria_logger, "ESPERANDO A CPU");
	fd_cpu = esperar_cliente(fd_memoria, memoria_logger,"cpu");
	if (fd_cpu == -1) {
        log_error(memoria_logger, "No se pudo aceptar la conexión de CPU");
    }

	//ESPERAR CONEXION KERNEL
	
	log_info(memoria_logger, "ESPERANDO A KERNEL");
	fd_kernel = esperar_cliente(fd_memoria, memoria_logger,"kernel");
	if (fd_kernel == -1) {
        log_error(memoria_logger, "No se pudo aceptar la conexión de Kernel");
    } else {
        log_info(memoria_logger, "CONECTADO A KERNEL");
    }

	//ESPERAR CONEXION ENTRADAYSALIDA
	log_info(memoria_logger, "ESPERANDO A ENTRADA Y SALIDA");
	fd_entradasalida = esperar_cliente(fd_memoria, memoria_logger,"entrada y salida");
	if (fd_entradasalida == -1) {
        log_error(memoria_logger, "No se pudo aceptar la conexión de Entrada y Salida");
    }

	
	//ATENDER CPU
	pthread_t hilo_cpu;
	pthread_create(&hilo_cpu, NULL, (void*)atender_memoria_cpu, NULL);
	pthread_detach(hilo_cpu);

	//ATENDER KERNEL
	pthread_t hilo_kernel;
	pthread_create(&hilo_kernel, NULL, (void*)atender_memoria_kernel, NULL);
	pthread_detach(hilo_kernel);

	//ATENDER ENTRADA Y SALIDA
	pthread_t hilo_eys;
	pthread_create(&hilo_eys, NULL, (void*)atender_memoria_entradasalida, NULL);
	pthread_join(hilo_eys,NULL);

	//TERMINAR MEMORIA
	
	log_destroy(memoria_logger);

	return EXIT_SUCCESS;
}