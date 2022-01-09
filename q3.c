#include "main.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(){
	
	/* definition des variables */
		
	ssize_t ret;
	char* welcome="Bienvenue dans le Shell ENSEA \nPour quitter, tapez exit \nenseash % ";
	char buf[BUFSIZE];
	char* quitter="Bye bye ...\n";
	int i=0;
	
	
	write(STDOUT_FILENO, welcome, strlen(welcome));
	//fd = descripteur de fichier, 3 standards : STDIN_FILENO (read), STDOUT_FILENO(write),STDERR_FILENO (erreur)

	while(i==0){ // tant que i=0 on est dans l'invite de commande enseash
		
		ret=read(STDIN_FILENO, buf,strlen(buf)+1);
		// strlen(buf)+1 permet stocker dans buf la chaîne de caractères écrite sur le clavier en entier 
		// +1 correspond à '\0' qui est placé à la fin de toute chaîne de caractères
		// Si on teste en enlevant +1, lorsqu'on écrit fortune : "fortun" est lu puis "e"
		
		if(ret>1){ // buf comprend plus d'un caractère dans sa chaîne

			if(strncmp(buf,"fortune",7)==0){ // compare la chaîne de caratère entrée avec "fortune"
				
				write(STDOUT_FILENO, "Today is what happened to yesterday.\n",37);
				write(STDOUT_FILENO,"enseash % ", 10); // écrit deux fois enseash car passe dans la boucle ret==1 la première fois
			} 
			
			else if((strncmp(buf,"exit",4)==0)){ // compare la chaîne de caratère entrée avec "exit"
				write(STDOUT_FILENO,quitter,strlen(quitter)); // affichage avant de quitter 
				i=1; //sortie de boucle while
			}
				
			else{
				
				write(STDOUT_FILENO, "Unknown function\n",17); // chaîne de carcatères ne correspond pas à une fonction implémentée
				write(STDOUT_FILENO,"enseash % ", 10); // montre qu'on est toujours dans l'invite de commande enseash
			}
		
		}
		else if(ret==1){ // retour à la ligne (entrée) 
			
			write(STDOUT_FILENO," enseash % ", 10);
		}
		else{ // ctrl+D correspond à la valeur EOF, la chaîne de caractères est vide
			write(STDOUT_FILENO,quitter,strlen(quitter));
			i=1; //sortie de boucle while
		}
	}
	return 0;
}
