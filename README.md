# LoveIsAnOpenDoor Malware (BackDoor)


## Getting Started
LoveIsAnOpenDoor is currently developing malware can be used in both Windows, Linux. It can be executed on both 32 and 64-bits systems. After it is executed, it creates connection between attacker and target machine and provides attacker to get control of target systems command line without knowledge of the victim.


### Prerequisites
Two machines; an attacker and a target.

### Installation
Note: You will only need .c files, other files will be recompiled for you attacker machine. 
So instead of downloading those file follow the following steps.

- Replace your attacker machine's IP address in LoveIsAnOpenDoor.c and Server.c 
- Install ming into you attacker device 
	```
	apt-get install mingw64 
	```
- Use following command to compile the Server
	```
	gcc Server.c -o Server 
	```
- Use following command to compile the exe file. 
	```
	i686-w64-mingw32-gcc -o LoveIsAnOpenDoor.exe LoveIsAnOpenDoor.c -lwsock32 -lwininet 
	```
- Send the compiled LoveIsAnOpenDoor.exe to target machine  (Already sent)
- Start Server by using 
	```
	./Server
	```
- Execute exe file in target machine.
- Check for if shell is opened in attacker machine.

## Basic Usage 
If shell is opened you can start executing codes in target machine on your backdoor.
Try whoami, ls etc commands.

	```
	whoami 
	netstat
	dir
	```
## Keylogging
Use following command to start keylogger in target system. It will create a file named windows in the desktop of the target device and holds each key pressed. Hence this software is only for educational purpose, those files are not hidden in the system.
```
start_keylog	
```
## Persistance
Gain persistance on the remote system by executing payload in boot time by using following command
```
persist
```
## Demonstration
Checkout the Demonstration.mp4, can be found in current repository. In demonstration, used Kali Linux machine as attacker and Flare as target machine to be able to examine the malware code in target machine.



## Authors

* **Özlem Körpe** - *Initial work* - [ozlemkorpe](https://github.com/ozlemkorpe)
