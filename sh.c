#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CHECK 1
#define EXIT 2
#define SHUT 3
#define EXPORT 4
#define ECHO 5

typedef struct echo_Export {
	
	char variable[50];
	char contenido[50];

} echo_Export;

void variable_Contenido(char export[50], char variable[50], char contenido[50]);
void variable_Contenido_echo(char echo[50],char echo_uncoded[50], int *type);

int main()
{
	FILE *fp, *fptr;
	echo_Export echo_ExportF[50]={'\0'};

	char exitcmd[9]="exit";
	char shutcmd[9]="shutdown";
	char exptcmd[9]="export";
	char echocmd[9]="echo";
	char cadena[9];
	char export[50];
	char echo[50];
	char echo_uncoded[50];
	char contenido[50];
	char variable[50];
	char nope[50]={'\0'};

	

	int state=CHECK;
	int i;
	int exist;
	int type;
	int loc;

	printf("Ingrese algun comando exit|shutdown|export|echo y despues presione enter: ");	//Imprimimos "Hola mundo" y el Pid hijo
	

	while(1){

		fptr = fopen("/home/oscrack/Desktop/shutdown.txt","r");
  		if(fptr == NULL)
   		{
     	 	 
   		}

   		else{
   			exit(0);	
   		}

   		//fclose(fptr);



		switch(state)
		{
		  case CHECK:
		  	scanf("%s",cadena);


		  	 if(strcmp(cadena,exitcmd) == 0){
		     	 state = EXIT;
		    	 break;
		 	 }
		 	 
		 	 else if(strcmp(cadena, shutcmd) == 0){
	 		     state = SHUT;
		    	 break;
		 	 }
		 	  else if(strcmp(cadena, exptcmd) == 0){
	 		     state = EXPORT;
			     fgets(export, 51, stdin);
		    	 break;
		 	 }
		 	  else if(strcmp(cadena, echocmd) == 0){
	 		     state = ECHO;
			     fgets(echo, 51, stdin);
		    	 break;
		 	 }

		 	 else{
		 	 	 printf("Comando Incorrecto\n\n");
		 	 	 break;
		 	 }

	
				  	
		  case EXIT:

		  		exit(0);
		  		break;

		  case SHUT:
		    	
   				fp = fopen("/home/oscrack/Desktop/shutdown.txt","w");
   				if(fp == NULL)
   				{
      				printf("Error creating SHUTFILE");   
      				exit(0);             
   				}
   				fclose(fp);
   				exit(1);
		  		break;

		  	case EXPORT:

		  		strcpy(export,nope);
		  		printf("Escriba en el siguiente formato para hacer un export 'variable'='contenido': ");   
		  		fgets(export, 51, stdin);
		  		variable_Contenido(export, variable, contenido);

///////////////////////////////////////////////READFILE

		  		i=0;
		  		exist=0;
				fp = fopen("/home/oscrack/Desktop/program.txt","r");
			    
			    if(fp == NULL)
			   {
			      printf("Error no such file found /home/oscrack/Desktop/program.txt");   
			      exit(1);             
			   }

			    while(!feof(fp)){
			   			fscanf(fp, "%s", echo_ExportF[i].variable);
			      		fscanf(fp, "%s", echo_ExportF[i].contenido);

			    		if(strcmp(echo_ExportF[i].variable, variable)==0){
			    				strcpy(echo_ExportF[i].contenido,contenido);
			    				exist=1;
			    		} 

			      		i++;
			    }

			    strcpy(echo_ExportF[i-1].variable,nope);
			    strcpy(echo_ExportF[i-1].contenido,nope);

     		    fclose(fp);	



///////////////////////////////////////////////WRITEFILE

			    i=0;
			    fp = fopen("/home/oscrack/Desktop/program.txt","w");

			    if(fp == NULL)
			    {
			      printf("Error!");   
			      exit(1);             
			    }

			    while (1){

			    		if(strcmp(echo_ExportF[i].variable, nope)==0)
			    			break;
			    		else{
			    		
			    			fprintf(fp,"%s\n%s\n", echo_ExportF[i].variable, echo_ExportF[i].contenido);
			    			i++;
			    		}
				}


			    if(exist!=1)
			 	   fprintf(fp,"%s\n%s\n", variable, contenido);

			    fclose(fp);
////////////////////////////////////////////////////////////

		  		break;

		  	case ECHO:

		  		strcpy(echo,nope);
		  		printf("Escriba en el siguiente formato para hacer un echo $'variable':  ");   
		  		scanf("%s", echo);		  		

///////////////////////////////////////////////READFILE		  		
		  		i=0;
		  		exist=0;		 
		  		loc=0; 		
				fp = fopen("/home/oscrack/Desktop/program.txt","r");
			    
			    if(fp == NULL)
			   {
			      printf("Error no such file found /home/oscrack/Desktop/program.txt");   
			      exit(1);             
			   }

			   variable_Contenido_echo(echo, echo_uncoded,&type);

			    while(!feof(fp)){
			   			fscanf(fp, "%s", echo_ExportF[i].variable);
			      		fscanf(fp, "%s", echo_ExportF[i].contenido);		
			      		
			    			if(strcmp(echo_ExportF[i].variable, echo_uncoded)==0){
			    			loc=i;
			   				exist=1;	
			    			}
			    		i++;
				}
			   

			    if (type==0)
			    {
			    	  printf("%s\n", echo_uncoded);	
			    }
			    else if (type==1&&exist==1)
			    {
			    	  printf("%s\n", echo_ExportF[loc].contenido);	
			    }
			    else if (type==1&&exist==0)
			    {
			    	  printf("\n");
			    }
	
			   	strcpy(echo_ExportF[i-1].variable,nope);
			   	strcpy(echo_ExportF[i-1].contenido,nope);

			    fclose(fp);	
/////////////////////////////////////////////////////////////

		  		break;

		  default:
		 	 break;
		
		}
	}

}

void variable_Contenido(char export[50],char variable[50],char contenido[50]){

	int state=1;
	int j=0;
	char nope[50]={'\0'};

	strcpy(variable,nope);
	strcpy(contenido,nope);

	for (int i=0; i<50; i++){

		switch(state)
		{
		  case 1: 

			  if (export[i]=='='){
					state=2;
					j=i+1;
					break;
				}
				else{
					variable[i]=export[i];
					break;
				}		  		
				  	
		  case 2:
		  		contenido[i-j]=export[i];	
		  		variable[i-1]='\0';	  		
		  		break;

		  default:
		  		break;

		}
	}
	printf("variable %s\ncontenido %s\n", variable, contenido);
}

void variable_Contenido_echo(char echo[50],char echo_uncoded[50], int *type){

	int state=1;
	int i;

	while (i<50){

		switch(state)
		{
		  case 1: 


			  if (echo[i]=='$'){
					state=2;
					i=0;
					break;
				}
				else{
					echo_uncoded[i]=echo[i];
					*type=0;
					break;
				}		  		
				  	
		  case 2:
		  		echo_uncoded[i-1]=echo[i];	
		  		*type=1;	  		
		  		break;

		  default:
		  		break;

		}

		i++;
	}
}

