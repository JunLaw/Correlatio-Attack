
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*Decalage de bits et rajoute le nouvelle retroaction a la fin du LFSR*/
void pop_and_push(int *tab,int n,int new_value){
	int temp1=0;
	int temp2=new_value;
	int temp3 = tab[0];
	
	for(int i = n-1; i >= 0  ; i = i-2){
		temp1 = tab[i];
		tab[i] = temp2;
		temp2 = tab[i-1];
		tab[i-1] = temp1;
		
	}
	
	
}

/* tRransforme le charactère en binaire */
int chtobin(char z){
	if( z == '1'){
			 return 1;
		}else if( z == '0'){
			return 0;
		}
		else{
			fprintf(stderr, "le char passé n'est pas convertible");
		}
}

/*Effectue l'operation de LFSR Geffe*/
void geffe(int* L1,int* L2,int* L3,int n,int* result,int* F){
	int a,b,c,d;
		for(int i = 0; i< n;i++)
		{
			//faire la fonction de filtrage//
			a = L1[0];
			b = L2[0];
			c = L3[0];
			d = a + b + c;
			result[i] = F[d];
			////////////////////////////////	
			
			//calculer le nouveau s(i+m)//
		 int new_L1 = L1[1] ^ L1[4] ^ L1[7] ^ a; 
		 int new_L2 = L2[1] ^ L2[7] ^ L2[11] ^ b; 
		 int new_L3 = L3[2] ^ L3[3] ^ L3[5] ^ c; 
			/////////////////////////
		
			//decaler et rajouter la nouvelle valeur dans le tableau//
		 pop_and_push(L1,16,new_L1);
		 pop_and_push(L2,16,new_L2);
		 pop_and_push(L3,16,new_L3);
		 /////////////////////////////////////		
		}	
	
}

/* remplis les lfsr des clé d'initialisation*/
int cast_value(int* L1,int* L2,int* L3,int* F,char **argv){
	for(int i = 0;i< 48;i++){
			if(chtobin(argv[2][i]) == 1 || chtobin(argv[2][i]) == 0)
			{
				if(i >= 0 && i < 16)
				{
					if(i < 8)
					{
						if(chtobin(argv[1][i]) == 1 || chtobin(argv[1][i]) == 0)
						{
							F[i] = chtobin(argv[1][i]);
						}else{
							
							fprintf(stderr,"fichier corrompu : ce ne sont pas des bits");
							return 20;
						}
					}
					L1[i] = chtobin(argv[2][i]);
				}
				else if(i >= 16 && i < 32)
				{
					L2[i-16] = chtobin(argv[2][i]);
				}
				else
				{
					L3[i-32] = chtobin(argv[2][i]);
				}
			}else{
				fprintf(stderr,"fichier corrompu : ce ne sont pas des bits");
							return 10;
			}
		
		}
	return 0;
}
