#include "main.h"
#include <unistd.h>
#include<sys/types.h>

int main(){
	
	write(STDIN_FILENO, "Bienvenue dans le Shell ENSEA \n", 31); 
//fd = descripteur de fichier, 3 standards : STDIN_FILENO (write), STDOUT_FILENO(read),STDERR_FILENO (erreur)
	write(STDIN_FILENO,"Pour quitter, tapez exit \n", 26);

	return 0;
}