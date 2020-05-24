# loveisanopendoor-malware

# LoveIsAnOpenDoor Malware (BackDoor)


## Getting Started



### Prerequisites
Two machines; an attacker and a target.

### Installation
Note: You will only need .c files, other files will be recompiled for you attacker machine. 
So instead of downloading those file follow the following steps.

- Replace your attacker machine's IP address in LoveIsAnOpenDoor.c and Server.c 
- Install ming into you attacker device apt-get install mingw64 (Already installed)
- Use following command to compile the Server
	```
	gcc Server.c -o Server 
	```
- Use following command to compile the exe file. 
	i686-w64-mingw32-gcc -o LoveIsAnOpenDoor.exe LoveIsAnOpenDoor.c -lwsock32 -lwininet 
- Send the compiled LoveIsAnOpenDoor.exe to target machine  (Already sent)
- Start Server by using ./Server
- Execute exe file in target machine.
- Check for if shell is opened in attacker machine.
- If shell is opened you can execute commands on target machine remotely


## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc

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


