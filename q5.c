#include "main.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	
	/* definition des variables */
	
	ssize_t ret;
	char* welcome="Bienvenue dans le Shell ENSEA \nPour quitter, tapez exit \nenseash % ";
	char buf[BUFSIZE];
	char* quitter="Bye bye ...\n";
	int i=0;
	pid_t fpid;
	int status;
	
	
	write(STDOUT_FILENO, welcome, strlen(welcome));
	//fd = descripteur de fichier, 3 standards : STDIN_FILENO (read), STDOUT_FILENO(write),STDERR_FILENO (erreur)



	while(i==0){ // tant que i=0 on est dans l'invite de commande enseash
		
		ret=read(STDIN_FILENO, buf,strlen(buf)+1); // strlen(buf)+1 permet stocker dans buf la chaîne de caractères écrite sur le clavier en entier 
		// +1 correspond à '\0' qui est placé à la fin de toute chaîne de caractères
		// Si on teste en enlevant +1, lorsqu'on écrit fortune : "fortun" est lu puis "e"

		
		if(strncmp(buf,"exit",4)==0){ 
			write(STDOUT_FILENO,quitter,strlen(quitter)); // affichage avant de quitter 
			i=1; //sortie de boucle while = sortie de l'invite de commande enseash
			
		}
		
		else if(ret==1){ // retour à la ligne (entrée) 
			write(STDOUT_FILENO,"enseash % ", 10); // début de ligne qui montre qu'on est toujours dans l'invite de commande enseash
		}
				

		else if(ret==0){ // ctrl+D correspond à la valeur EOF, la chaîne de caractères est vide
			write(STDOUT_FILENO,quitter,strlen(quitter));
			i=1; //sortie de boucle while = sortie de l'invite de commande enseash
		}
			
		else if(ret>1){ 
			struct timespec start, end; // permet de définir un intervalle de temps en s ou ns 
			
			fpid = fork();
			clock_gettime(CLOCK_REALTIME,&start); // stocke dans start l'instant de création du process 
				
			if(fpid==0){ // code fils 
				
				if(strncmp(buf,"fortune",7)==0){ // compare la chaîne de caratère entrée avec "fortune"
				
					write(STDOUT_FILENO, "Today is what happened to yesterday.\n",37);
					exit(0); //sort du code fils et va dans le code père avec le code 0
				}
						
				else{
					
					write(STDOUT_FILENO, "Unknown function\n",17);
					exit(-1); //sort du code fils et va dans le code père avec le code 255
				}
				
			
			}
					
					
			else if(fpid>0){ //code père
				waitpid(fpid,&status,WUNTRACED); // attend qu'un fils soit terminé
				clock_gettime(CLOCK_REALTIME,&end); // stocke dans end la valeur de l'instant auquel le fils meurt
				int time_us = (end.tv_nsec -start.tv_nsec)/1000; // différence des temps de fin de process et de début de process en us (/1000)
				
				if(WIFEXITED(status)){ // WIFEXITED(status)=true si sortie du process fils se termine normalement
					int etat = WEXITSTATUS(status); // etat = valeur de sortie du fils (code de exit)
					printf("enseash[exit:%i|%ius] %% ",etat,time_us); // ecrit plusieurs fois enseash avec deux fonctions de retard et affiche à chaque fois ce qui a été gardé des appels précédents
				}
				
				else if(WIFSIGNALED(status)){ // WIFSIGNALED(status)=true si un signal force la sortie du code fils 
					int etat2 = WTERMSIG(status); // valeur de sortie du fils si il s'est terminé par un signal 
					printf("enseash[sign:%i|%ius] %% ",etat2,time_us); 
						
				}
			}
		}	
	}
		
	return 0;
}
