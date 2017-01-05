#include "header.h"

int *pids;
int nbpids;
void execute_ligne_commande() {
  int flag = -1 , nb = -1;
  char ***argv = ligne_commande(&flag,&nb);
  int pid , din , dout , t[2];

  if(argv == NULL) {
    printf("Ligne de commande incorrecte \n");
  }

  din = 0;
  pids = (int *)malloc(sizeof(int)*nb);
  
  int i = 0;
  for(i=0;i<nb;i++) {
    if(i == nb-1) {
      dout=1;
    }else {
      pipe(t);
      dout = t[1];
    }
    pid = lance_commande(din,dout,argv[i][0],argv[i]);
    if(pid == -1) {
      printf("Error");
    }
    pids[i] = pid;
    nbpids = (i + 1);
    if(!flag) {
      waitpid(pid,NULL,0);
    }
    if(i!=nb-1) {
      close(dout);
      if(i!=0) {
  close(din);
      }
    }else if(nb>1 && i==(nb-1)) {
      close(din);
    }
    if(nb!=1)
      din = t[0];
  }
  free(pids);
  nbpids = 0;
  clean(argv);
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

void clean() {
  pid_t pid;
  int status;
  while((pid = waitpid( pid, &status, WNOHANG ) ) > 0 ){}
}