#include "../includes/entradasalida.h"

int main() {
    
    //INICIALIZO ENTRADA Y SALIDA
    inicializar_entradasalida();
    
    //conectarse con memoria 
    fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA);
	if (fd_memoria == -1) {
        log_error(entradasalida_logger, "No se pudo conectar con la memoria");
    } else {
        log_info(entradasalida_logger, "Conexión con MEMORIA exitosa");
    }

    //conectarse con KERNEL
	fd_kernel = crear_conexion(IP_KERNEL, PUERTO_KERNEL); 
	if (fd_kernel == -1) {
        log_error(entradasalida_logger, "No se pudo conectar con el kernel");
    } else {
        log_info(entradasalida_logger, "Conexión con KERNEL exitosa");
    }


    // //ATENDER MEMORIA
    // pthread_t hilo_memoria;
    // pthread_create(&hilo_memoria,NULL,atender_entradasalida_memoria,NULL);
    // pthread_detach(hilo_memoria);

    // //ATENDER KERNEL
    // pthread_t hilo_kernel;
    // pthread_create(&hilo_kernel,NULL,atender_entradasalida_kernel,NULL);
    // pthread_join(hilo_kernel, NULL);
    log_destroy(entradasalida_logger);
      
    return EXIT_SUCCESS;
}