#include "header.h"

void execute_ligne_commande(void){
	int flag, nb;
	int *pFlag = &flag;
	int *pNb = &nb;

	char ***commande = ligne_commande(pFlag, pNb);

    while(flag == 1){
    int pid = fork();

      if(pid == 0){
        execvp(commande[0][0], commande[0]);
        perror("execvp");
        exit(EXIT_FAILURE);
      }
      else if(pid != -1){
        afficher_prompt();
        commande = ligne_commande(pFlag, pNb);
      }
  }

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

int lance_commande( int in, int out, char *com, char ** argv){
  int pid = fork();
  
  if(pid == -1){
    perror("fork");
    return -1;
  }

  if(pid == 0){
    if(in != 0){
      close(0);
      dup(in);
    }
    if(out != 1){
      close(1);
      dup(out);
    }
    execvp(com, argv);
    perror("Ligne de commande");
    return -1;
  }
  return pid;
}