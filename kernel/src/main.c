#include "../includes/kernel.h"

int main(void) {

	// inicializar kernel
	inicializar_kernel();

	//INICIAR SERVER DE KERNNEL
	fd_kernel = iniciar_servidor(PUERTO_ESCUCHA, kernel_logger, "KERNEL HA SIDO INICIADA");
	if (fd_kernel == -1) {
        log_error(kernel_logger, "No se pudo iniciar el servidor del kernel");
        log_destroy(kernel_logger);
        return EXIT_FAILURE;
    }

	//conectarse con memoria 
	fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA);
	if (fd_memoria == -1) {
        log_error(kernel_logger, "No se pudo conectar con la memoria");
    }

	//conectarse con cpu 
	fd_cpu_dispatch = crear_conexion(IP_CPU, PUERTO_CPU_DISPATCH);
	if (fd_cpu_dispatch == -1) {
        log_error(kernel_logger, "No se pudo conectar con CPU dispatch");
    } else {
        log_info(kernel_logger, "fd_cpu_dispatch: %d", fd_cpu_dispatch);
    }

	fd_cpu_interrupt = crear_conexion(IP_CPU, PUERTO_CPU_INTERRUPT);
	if (fd_cpu_interrupt == -1) {
        log_error(kernel_logger, "No se pudo conectar con CPU interrupt");
    } else {
        log_info(kernel_logger, "fd_cpu_interrupt: %d", fd_cpu_interrupt);
    }

	//esperar conexion de entradasalida
	log_info(kernel_logger, "ESPERANDO A ENTRADASALIDA");
	fd_entradasalida = esperar_cliente(fd_kernel, kernel_logger, "Entrada y salida");
	if (fd_entradasalida == -1) {
        log_error(kernel_logger, "No se pudo aceptar la conexión de entrada y salida");
    }

	//ATENDER MEMORIA
	pthread_t hilo_memoria;
	pthread_create(&hilo_memoria, NULL, (void*)atender_kernel_memoria, NULL);
	pthread_detach(hilo_memoria);
	
	//ATENDER CPU DISPATCH
	pthread_t hilo_cpu_dispatch;
	pthread_create(&hilo_cpu_dispatch, NULL, (void*)atender_kernel_dispatch, NULL);
	pthread_detach(hilo_cpu_dispatch);

	//ATENDER CPU INTERRUPT
	pthread_t hilo_cpu_interrupt;
	pthread_create(&hilo_cpu_interrupt, NULL, (void*)atender_kernel_interrupt, NULL);
	pthread_detach(hilo_cpu_interrupt);

	//ATENDER ENTRADA Y SALIDA
	pthread_t hilo_entradasalida;
	pthread_create(&hilo_entradasalida, NULL, (void*)atender_kernel_entradasalida, NULL);
	pthread_join(hilo_entradasalida, NULL);


    log_destroy(kernel_logger);

	return EXIT_SUCCESS;
}