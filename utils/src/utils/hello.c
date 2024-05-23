#include <utils/hello.h>

void decir_hola(char* quien) {
    printf("Hola desde %s!!\n", quien);
}

int crear_conexion(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	int err;
	err = getaddrinfo("127.0.0.1", "4444", &hints, &server_info);
	// Ahora vamos a crear el socket.
	//int socket_cliente = 0;
	int socket_cliente = socket(server_info->ai_family,
                         server_info->ai_socktype,
                         server_info->ai_protocol);
	// Ahora que tenemos el socket, vamos a conectarlo
	
	err = connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen);

	freeaddrinfo(server_info);

	return socket_cliente;
}

int iniciar_servidor(char* puerto, t_log* un_log, char* mensaje_servidor)
{
	int err;
	
	struct addrinfo hints, *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	// Creamos el socket de escucha del servidor

	getaddrinfo(NULL, "4444", &hints, &server_info);

	int socket_servidor = socket(server_info->ai_family,
                        server_info->ai_socktype,
                        server_info->ai_protocol);

	// Asociamos el socket a un puerto
	err = bind(socket_servidor, server_info->ai_addr, server_info->ai_addrlen);
	
	log_info(un_log, "resultado de bind: %d", err);

	// Escuchamos las conexiones entrantes

	err = listen(socket_servidor, SOMAXCONN);

	log_info(un_log, "resultado de listen: %d", err);

	freeaddrinfo(server_info);
	log_info(un_log,"SERVER: %s",mensaje_servidor);

	return socket_servidor;
}

int esperar_cliente(int socket_servidor, t_log* un_log,char* msj)
{
	// Aceptamos un nuevo cliente
	int socket_cliente = accept(socket_servidor, NULL, NULL);

	log_info(un_log, "Se recibio conexion desde: %s",msj);

	return socket_cliente;
}
int recibir_operacion(int socket_cliente)
{
	int cod_op;
	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) > 0)
		return cod_op;
	else
	{
		close(socket_cliente);
		return -1;
	}
}

t_buffer* crear_buffer(){

	t_buffer* un_buffer = malloc(sizeof(t_buffer));
	un_buffer -> size = 0;
	un_buffer -> stream = NULL;
	
	return un_buffer;
}

void* extraer_cosas_del_buffer(t_buffer* un_buffer){
	if(un_buffer->size == 0){
		printf("\n[ERROR] Al intentar extraer ");
		exit(EXIT_FAILURE);
	}
	
	if(un_buffer->size < 0){
    	printf("\n[ERROR] El t_buffer tiene un size negativo");
		exit(EXIT_FAILURE);	} 

	int size_cosas;
	memcpy(&size_cosas, un_buffer->stream, sizeof(int));
	void* cosas = malloc(size_cosas);
	memcpy(cosas, un_buffer->stream + sizeof(int), size_cosas);

	int nuevo_size = un_buffer->size - sizeof(int) - size_cosas;
	if(nuevo_size == 0){
		un_buffer->size = 0;
		free(un_buffer->stream);;
		un_buffer->stream = NULL;
		return cosas;
	}
	
	if(nuevo_size < 0){
    	printf("\n[ERROR] Buffer tiene un size negativo");
		exit(EXIT_FAILURE);
	} 

	void* nuevo_stream = malloc(nuevo_size);
	memcpy(nuevo_stream, un_buffer->stream + sizeof(int) + size_cosas, nuevo_size);
	free(un_buffer->stream);
	un_buffer->size = nuevo_size;
	un_buffer->stream = nuevo_stream;

	return cosas;
}

t_buffer* recibir_buffer(int conexion){
	
	t_buffer* un_buffer = malloc(sizeof(t_buffer));

	if(recv(conexion, &(un_buffer->size),sizeof(int),MSG_WAITALL)>0)
	{
		un_buffer->stream = malloc(un_buffer->size);
		if(recv(conexion, un_buffer->stream, un_buffer->size, MSG_WAITALL)>0)
		{
			return un_buffer;
		}
		else
		{
			perror("Error al recibir el void* del buffer de la conexion");
			exit(EXIT_FAILURE);
		}
	}else
	{
		perror("Error al recibir el tamanio del buffer de la conexion");
		exit(EXIT_FAILURE);
	}
	return un_buffer;
}
void enviar_paquete(t_paquete* paquete, int conexion){
	
	void* a_enviar = serialzizar_paquete(paquete);

	int bytes = paquete->buffer->size + 2 * sizeof(int);
	send(conexion, a_enviar, bytes, 0);

	free(a_enviar);
}

int extraer_int_buffer (t_buffer* un_buffer){
	int* un_entero = extraer_cosas_del_buffer(un_buffer);
	int valor_retorno = *un_entero;
	free (un_entero);
	return valor_retorno;
}

char* extraer_string_buffer(t_buffer* un_buffer){
	
	char* un_string = extraer_cosas_del_buffer(un_buffer);
	return un_string;
}

void cargar_string_al_buffer(t_buffer* un_buffer, char* un_string){
	cargar_cosas_al_buffer(un_buffer, un_string, strlen(un_string)+1);
}

void cargar_cosas_al_buffer(t_buffer* un_buffer, void* una_cosa, int size_cosas){
	if(un_buffer->size == 0){
		un_buffer->stream = malloc(sizeof(int) + size_cosas);
		memcpy (un_buffer->stream, &size_cosas, sizeof(int));
		memcpy (un_buffer->stream + sizeof(int), una_cosa, size_cosas);
	}
	else{
		un_buffer->stream = realloc(un_buffer->stream, un_buffer->size + sizeof(int) + size_cosas);
		memcpy(un_buffer->stream + un_buffer->size, &size_cosas,sizeof(int));
		memcpy(un_buffer->stream + un_buffer->size + sizeof(int), una_cosa,size_cosas);
	}

	un_buffer->size += sizeof(int);
	un_buffer->size += size_cosas;
}

void paquete(int conexion){
	char* leido = NULL;
	t_paquete* paquete = crear_paquete();

	leido = readline("> ");
	while(strcmp(leido,"") != 0){
		agregar_a_paquete(paquete,leido,strlen(leido) + 1);
		free(leido);
		leido = readline("> ");
	}
}
 
t_paquete* crear_super_paquete(op_code cod_op, t_buffer* un_buffer){
	t_paquete* un_paquete = malloc(sizeof(t_paquete));
	un_paquete->codigo_operacion = cod_op;
	un_paquete->buffer = un_buffer;
	return un_paquete;
}

void destruir_paquete(t_paquete* un_paquete){
	destruir_buffer(un_paquete->buffer)	free(un_paquete);	
}