#include "../includes/kernel.h"

int main(void) {

	// inicializar kernel
	inicializar_kernel();

	//INICIAR SERVER DE KERNNEL
	fd_kernel = iniciar_servidor(PUERTO_ESCUCHA, kernel_logger, "KERNEL HA SIDO INICIADA");

	//conectarse con memoria 
	fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA);

	//conectarse con cpu 
	fd_cpu_dispatch = crear_conexion(IP_CPU, PUERTO_CPU_DISPATCH);
	log_info(kernel_logger,"fd_cpu_dispatch: %d",fd_cpu_dispatch);
	//log_info(kernel_logger, "Conexion con CPU DISPATCH exitosa");
	fd_cpu_interrupt = crear_conexion(IP_CPU, PUERTO_CPU_INTERRUPT);
	log_info(kernel_logger,"fd_cpu_interrupt: %d",fd_cpu_interrupt);
	//log_info(kernel_logger, "Conexion con CPU INTERRUPT exitosa");

	//esperar conexion de entradasalida
	fd_entradasalida = esperar_cliente(fd_kernel, kernel_logger, "Entrada y salida");

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

	return EXIT_SUCCESS;
}