#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define USER 1
#define PASS 2
#define PASS2 3
#define IDLE 4

void crear_hijo();

typedef struct user_PASSWORD {
	
	char usernameF[10];
	char passwordF[10];

} user_PASSWORD;


int main()
{
	FILE *fp;
	int state=USER;
	int status;

	user_PASSWORD user_PASSWORDD;
	user_PASSWORD user_PASSWORDF[2];


	fp = fopen("/home/oscrack/Desktop/user.txt","r");
    if(fp == NULL)
   {
      printf("Error no such file found /home/oscrack/Desktop/user.txt");   
      exit(1);             
   }

    for(int i=0;i<2;i++){
   			fscanf(fp, "%s", user_PASSWORDF[i].usernameF);
      		fscanf(fp, "%s", user_PASSWORDF[i].passwordF);
    }


	while(1){

		switch(state)
		{
		  case USER:
		  	 printf("Nombre de usuario: ");	
			 scanf("%s", user_PASSWORDD.usernameF);
			

			 if(strcmp( user_PASSWORDD.usernameF, user_PASSWORDF[0].usernameF) == 0){
		     	 state = PASS;
		    	 break;
		 	 }
		 	 else if(strcmp(user_PASSWORDD.usernameF, user_PASSWORDF[1].usernameF) == 0){
	 		     state = PASS2;
		    	 break;
		 	 }
		 	 else{
		 	 	 printf("Usuario Incorrecto\n\n");
		 	 	 break;
		 	 }


		  case PASS:
		   
		  	 printf("Contraseña ");	
			 scanf("%s", user_PASSWORDD.passwordF);
			

			 if(strcmp( user_PASSWORDD.passwordF, user_PASSWORDF[0].passwordF) == 0){
		     	 state = IDLE;
		    	 break;
		 	 }
		 
		 	 else{
		 	 	 printf("Contraseña Incorrecta\n\n");
		 	 	 break;
		 	 }
		     
		 case PASS2:
		  	 printf("Contraseña ");	
			 scanf("%s", user_PASSWORDD.passwordF);
			

			 if(strcmp( user_PASSWORDD.passwordF, user_PASSWORDF[1].passwordF) == 0){
		     	 state = IDLE;
		    	 break;
		 	 }
		 
		 	 else{
		 	 	 printf("Contraseña Incorrecta\n\n");
		 	 	 break;
		 	 }


		 case IDLE:
		 		printf("Login\n");
		 		crear_hijo();
		 		wait(&status);
		 		exit(0);
		 		break;

		 default:
		  break;   
		}
	}
}

void crear_hijo(){
		int pid;
		pid=fork();		//Duplica el proceso y crea un proceso hijo
		if(pid==0)
		execlp("/usr/bin/xterm", "xterm", "-e", "./sh", NULL);
}