#include <stdio.h>

/*Pour getenv*/
#include <stdlib.h>
/*Pour fork()*/
#include <unistd.h>
/* Pour perror() et errno */
#include <errno.h>
/* Pour le type pid_t */
#include <sys/types.h>
/* Pour wait() */
#include <sys/wait.h>

#include <string.h>

#include "ligne_commande.h"
#include "fonction.h"