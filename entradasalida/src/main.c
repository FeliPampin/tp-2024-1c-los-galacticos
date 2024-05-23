#include "../includes/entradasalida.h"

int main() {
    
    //INICIALIZO ENTRADA Y SALIDA
    inicializar_entradasalida();
    
    //conectarse con memoria 
    fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA);
	log_info(entradasalida_logger, "Conexion con MEMORIA exitosa");

    //conectarse con KERNEL
	fd_entradasalida = crear_conexion(IP_KERNEL, PUERTO_KERNEL); //HAY ALGO RARO ACA, NO TENDRIA QUE SER FD_KERNEL, PQ ARRIBA DICE FD_MEMORIA
	log_info(entradasalida_logger, "Conexion con KERNEL exitosa");

    //ATENDER MEMORIA
    pthread_t hilo_memoria;
    pthread_create(&hilo_memoria,NULL,atender_entradasalida_memoria,NULL);
    pthread_detach(hilo_memoria);

    //ATENDER KERNEL
    pthread_t hilo_kernel;
    pthread_create(&hilo_kernel,NULL,atender_entradasalida_kernel,NULL);
    pthread_join(hilo_kernel, NULL);

      
    return EXIT_SUCCESS;
}