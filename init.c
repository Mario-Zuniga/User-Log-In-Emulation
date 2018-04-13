#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define N_procesos 6


void crear_hijo();
 


int main()
{

	int N_procesos_actual=6;
	int status;
	FILE *fp;
	remove("/home/oscrack/Desktop/shutdown.txt");  


	printf("Hola soy el padre, mi pid es %d\n",getpid());		//Imprimimos el Pid padre y saludamos
	
	for (int i = 0; i < N_procesos; ++i)
	{
		crear_hijo();
	}


	while(1){


		wait(&status);
		fp = fopen("/home/oscrack/Desktop/shutdown.txt","r");
  		if(fp == NULL)
   		{
   			 crear_hijo();
     	 	 printf("There was an exit");   

   		}

   		else{
   			printf("There was a Shutdown"); 
   			for (int i = 0; i < N_procesos-1; i++)
				{
					kill(status, SIGKILL );
   					
				}

			exit(0);	
   		}
   	}		
}


void crear_hijo(){
		int pid;
		pid=fork();		//Duplica el proceso y crea un proceso hijo
		if(pid==0)
		execlp("/usr/bin/xterm", "xterm", "-e", "./getty", NULL);
}

