#include "../includes/cpu.h"

int main(void) {
//uhhjhjhjhjhj
	//INICIALIZO CPU
    inicializar_cpu();

	//INICIAR SERVER DE CPU DISPATCH
	fd_cpu_dispatch = iniciar_servidor(PUERTO_ESCUCHA_DISPATCH, cpu_logger, "CPU DISPATCH HA SIDO INICIADA");
	if (fd_cpu_dispatch == -1) {
        log_error(cpu_logger, "No se pudo iniciar el servidor de CPU dispatch");
        log_destroy(cpu_logger);
        return EXIT_FAILURE;
    }

    //INICIAR SERVER DE CPU INTERRUPT
	fd_cpu_interrupt = iniciar_servidor(PUERTO_ESCUCHA_INTERRUPT, cpu_logger, "CPU INTERRUPT HA SIDO INICIADA");
	if (fd_cpu_interrupt == -1) {
        log_error(cpu_logger, "No se pudo iniciar el servidor de CPU interrupt");
        close(fd_cpu_dispatch);
        log_destroy(cpu_logger);
        return EXIT_FAILURE;
    }

    //CONECTAR COMO CLIENTE A MEMORIA
	fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA);
	if (fd_memoria == -1) {
        log_error(cpu_logger, "No se pudo conectar con la memoria");
    }

	//ESPERAR CONEXION KERNEL DISPATCH
    log_info(cpu_logger, "ESPERANDO A KERNEL DISPATCH");
	fd_kernel_dispatch = esperar_cliente(fd_cpu_dispatch, cpu_logger, "KERNEL DISPATCH");
	if (fd_kernel_dispatch == -1) {
        log_error(cpu_logger, "No se pudo aceptar la conexión de kernel dispatch");
    }

    //ESPERAR CONEXION KERNEL INTERRUPT
	log_info(cpu_logger, "ESPERANDO A KERNEL INTERRUPT");
	fd_kernel_interrupt = esperar_cliente(fd_cpu_interrupt, cpu_logger, "KERNEL INTERRUPT");
	if (fd_kernel_interrupt == -1) {
        log_error(cpu_logger, "No se pudo aceptar la conexión de kernel interrupt");
    }

	//ATENDER LOS MENSAJES DE KERNEL DISPATCH
	pthread_t hilo_kernel_dispatch;
	pthread_create (&hilo_kernel_dispatch,NULL,(void*)atender_cpu_kernel_dispatch, NULL);
	pthread_detach(hilo_kernel_dispatch);
	
	//ATENDER LOS MENSAJES DE KERNEL INTERRUPT
	pthread_t hilo_kernel_interrupt;
	pthread_create(&hilo_kernel_interrupt, NULL, (void*)atender_cpu_kernel_interrupt,NULL);
	pthread_detach(hilo_kernel_interrupt);

	//ATENDER LOS MENSAJES DE MEMORIA
	pthread_t hilo_memoria;
	pthread_create (&hilo_memoria, NULL,(void*)atender_cpu_memoria, NULL);
	pthread_join(hilo_memoria,NULL);

    log_destroy(cpu_logger);


    return EXIT_SUCCESS;
}
