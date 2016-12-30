#include "header.h"

void execute_ligne_commande(void){
	int flag, nb;
	int *pFlag = &flag;
	int *pNb = &nb;

	char ***commande = ligne_commande(pFlag, pNb);
	//affiche(commande);

	if(flag == 0){
		pid_t id = fork();

		if(id == 0){
			execvp(commande[0][0], commande[0]);
			perror("execvp");
		}
		else if(id != -1){
      if (wait(NULL) == -1) {
        perror("wait :");
        exit(EXIT_FAILURE);
      }
      fflush(stdout);
			//waitpid(id, int *status, int options);
		}
	}
}

void afficher_prompt(void){
  
    char *directory = NULL;
  	char *user = NULL;
  	char *home = NULL;
  	char hostname[20];
  	gethostname(hostname, 20);
  	user = getenv("USER");
  	home = getenv("HOME");
  	directory = getcwd(NULL, 128);
  	char *repertoire = malloc(sizeof(char)*130);
  	
    if(strstr(directory,home)==NULL){
    	printf("%s@%s:%s$ ", user, hostname, directory);
  	}
    else{
    	repertoire[0]='~';
    	int temp = strlen(home);
    	addStr(repertoire, 1, directory+temp, 128-temp);
    	printf("%s@%s:%s$ ", user, hostname, repertoire);
  	}

  	fflush(stdout);
  	free(repertoire);
  	free(directory);
  	return;	
}

void addStr(char *chaine, int n, char *directory, int len) {
  int i;
  for(i = 0 ; i < len ; i++){
    chaine[i+n] = directory[i];
  }
}