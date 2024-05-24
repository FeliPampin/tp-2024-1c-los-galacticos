#include "../includes/cpu.h"

int main(void) {
//uhhjhjhjhjhj
	//INICIALIZO CPU
    inicializar_cpu();

	//INICIAR SERVER DE CPU DISPATCH
	fd_cpu_dispatch = iniciar_servidor(PUERTO_ESCUCHA_DISPATCH, cpu_logger, "CPU DISPATCH HA SIDO INICIADA");

    //INICIAR SERVER DE CPU INTERRUPT
	fd_cpu_interrupt = iniciar_servidor(PUERTO_ESCUCHA_INTERRUPT, cpu_logger, "CPU INTERRUPT HA SIDO INICIADA");

    //CONECTAR COMO CLIENTE A MEMORIA
	fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA);
	close (fd_memoria);

	//ESPERAR CONEXION KERNEL DISPATCH
    log_info(cpu_logger, "ESPERANDO A KERNEL DISPATCH");
	fd_kernel_dispatch = esperar_cliente(fd_cpu_dispatch, cpu_logger, "KERNEL DISPATCH");

    //ESPERAR CONEXION KERNEL INTERRUPT
	log_info(cpu_logger, "ESPERANDO A KERNEL INTERRUPT");
	fd_kernel_interrupt = esperar_cliente(fd_cpu_interrupt, cpu_logger, "KERNEL INTERRUPT");

	// //ATENDER LOS MENSAJES DE KERNEL DISPATCH
	// pthread_t hilo_kernel_dispatch;
	// pthread_create (&hilo_kernel_dispatch,NULL,(void*)atender_cpu_kernel_dispatch, NULL);
	// pthread_detach(hilo_kernel_dispatch);
	
	// //ATENDER LOS MENSAJES DE KERNEL INTERRUPT
	// pthread_t hilo_kernel_interrupt;
	// pthread_create(&hilo_kernel_interrupt, NULL, (void*)atender_cpu_kernel_interrupt,NULL);
	// pthread_detach(hilo_kernel_interrupt);

	// //ATENDER LOS MENSAJES DE MEMORIA
	// pthread_t hilo_memoria;
	// pthread_create (&hilo_memoria, NULL,(void*)atender_cpu_memoria, NULL);
	// pthread_join(hilo_memoria,NULL);

    return EXIT_SUCCESS;
}
