#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//converti l'entrée en binaire
void chtobin(char ** argv,int *tab,int a,int b,int x){
	for(int i = a; i< b; i++){
		if(argv[x][i] == '0'){
			tab[i-a] = 0;
		}else if(argv[x][i] == '1'){
			tab[i-a] = 1;
		}
		else{
			printf("erreur");
			exit;
		}
	}
}

//affiche tableau
void print_tab_int(int *tab,int n){
	for(int i = 0; i<n; i++){
		printf("%d",tab[i]);
		
	}
	printf("\n");
	
}

//decalage à gauche de X bit d'une suite de bit : decale puis push la valeur décalé à droite de la suite
void offset_x(int *tab,int x,int n){

	int new_value = 0;
	for(int j = 0; j<x; j++){
		new_value = tab[n-1];
	for(int i = n-1 ; i >= 0 ; i = i-1){
		tab[i] = tab[i-1];
	}
	tab[0]=new_value;
}
	
}

//XOR deux tableau de même taille
void tab_xor(int *tab1,int *tab2,int *tab_res,int n){
	for(int i = 0; i< n; i++){
		tab_res[i] = tab1[i] ^ tab2[i];
	}
	
}


void main(int argc,char ** argv){
	/*K0 = [( X0L ꚛ X0R) <<< 7] ꚛ X1L
         K1 = [(X1L ꚛ X0R) <<< 7 ] ꚛ  X1R*/
         //il faut que x0 et x1 ait la même taille
         
         
         if(argc == 5 &&  strlen(argv[2]) == 32 && strlen(argv[1]) == 32 && strlen(argv[3]) == 32 && strlen(argv[4]) == 32)
         {
			 //assigne les valeurs au tableau correspondant
			int x0R[32] = {0};
			chtobin(argv,x0R,0,32,1);
			int x0L[32] = {0};
			chtobin(argv,x0L,0,32,2);
			int x1R[32] = {0};
			chtobin(argv,x1R,0,32,3);
			int x1L[32] = {0};
			chtobin(argv,x1L,0,32,4); 
			int K0[32] = {0};
			int K1[32] = {0};
       
			//K0 = [( X0L ꚛ X0R) <<< 7] ꚛ X1L
			tab_xor(x0L,x0R,K0,32);
			offset_x(K0,7,32);
			tab_xor(K0,x1L,K0,32);
       
			//K1 = [(X1L ꚛ X0R) <<< 7 ] ꚛ  X1R
			tab_xor(x1L,x0R,K1,32);
			offset_x(K1,7,32);
			tab_xor(K1,x1R,K1,32);
         
         
			//affiche resultat
			for(int i = 0; i<30;i++){printf("\n");}
			printf("K0 = ");
			print_tab_int(K0,32);
			printf("\n");
			printf("K1 = ");
			print_tab_int(K1,32);
			printf("\n");
         
		}
	  
		else
		{
		  printf("erreur");
		  exit;
		  
		}
         
	
}
