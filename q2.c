#include "main.h"
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(){
	
	ssize_t ret;
	char* welcome="Bienvenue dans le Shell ENSEA \nPour quitter, tapez exit \nenseash % ";
	char buf[BUFSIZE];

	
	write(STDOUT_FILENO, welcome, strlen(welcome));
	//fd = descripteur de fichier, 3 standards : STDIN_FILENO (write), STDOUT_FILENO(read),STDERR_FILENO (erreur)


	while(1){
		
		ret=read(STDIN_FILENO,buf,strlen(buf)+1); // strlen(buf)+1 permet stocker dans buf la chaîne de caractères écrite sur le clavier en entier 
		// +1 correspond à '\0' qui est placé à la fin de toute chaîne de caractères
		// Si on teste en enlevant +1, lorsqu'on écrit fortune : "fortun" est lu puis "e"
		
		if (ret>1){
			if(strncmp(buf,"fortune",7)==0){ // compare la chaîne de caratère entrée avec "fortune"
				
					write(STDOUT_FILENO, "Today is what happened to yesterday.\n",37);
					write(STDOUT_FILENO,"enseash % ", 10); // pour montrer qu'on est toujours dans l'invite de commande
					 
				}
		

			else{ // Si la chaîne de caractère entrée n'est pas connue

				write(STDOUT_FILENO, "Unknown function\n",17);
				write(STDOUT_FILENO,"enseash % ", 10);
			}
		}
	}

	return 0;
}
