#include "main.h"


int main(int argc, char* argv[], char* envp[])
{
  
    int i = 0;
	
	
	char *copy_env[100];
	int a;
	a=0;
	a = a + argc;
	argc = 0;
	argv[1]=0;
    while (envp[i] != NULL) {
        /*printf("%s\n", envp[i]);*/
		copy_env[i] = envp[i];
		argv[2] = copy_env[1];
        i++;
    }
	
    lsh_loop(copy_env);

 

  return EXIT_SUCCESS;
}

