#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "function.h"


int main(int argc,char ** argv){
		if(argc == 4)
		{
		int n = atoi(argv[3]);
		int result[n]; //tableau de bits pour la suite chiffrante
		int L1[16] ={0};
		int L2[16]={0};
		int L3[16]={0};
		int F[8]={0};
		
		
		if(strlen(argv[1]) == 8 && strlen(argv[2]) == 48)
		{	
		if(!cast_value(L1,L2,L3,F,argv))
		{
		printf("fonction de filtrage : ");
		for(int i = 0;i < 8;i++){printf("%d",F[i]);}
		printf("\nLFSR1 = ");
		for(int i = 0; i< 16;i++){printf("%d",L1[i]);}
		printf("\nLFSR2 = ");
		for(int i = 0; i< 16;i++){printf("%d",L2[i]);}
		printf("\nLFSR3 = ");
		for(int i = 0; i< 16;i++){printf("%d",L3[i]);}
		printf("\n");
		geffe(L1,L2,L3,n,result,F);	
		printf("suite chiffrante : ");
		for(int i = 0; i < n;i++){printf("%d",result[i]);}
		printf("\n");
		}else
		{
			fprintf(stderr,"fichier corrompu : ce ne sont pas des bits");
			return 20;
		}
		}else
		{
			fprintf(stderr,"nombre de bit invalide ");
			return 3;
		}
		}else
		{
			fprintf(stderr,"nombre d'argument invalide");
			return 15;
		}
		return 0;
}

