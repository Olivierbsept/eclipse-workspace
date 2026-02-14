/*
 ============================================================================
 Name        : Df.c
 Author      : Olivier Bessette
 Version     :
 Copyright   : Your copyright notice
 Description : Calcul de la décomposition en base 424
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void funcRec(int n);
void displayBase(int b);
void displayN(int n, int nbBases);
void record(int n);
int tab[18][262144][18];// 15 itérations, 65536 lignes, 15 colonnes, 0 = nombre en 424
long tab2[18][262144]; // dmf pour sortie
long tab3[18][262144]; // décodage du dmf
int tab4[18][262144]; // pour noter les exceptions

int main(void) {
	// première initialisation
	tab[1][0][0]=0;
	tab[1][1][0]=1;
	tab[1][2][0]=1;
	tab[1][3][0]=3;

	tab2[1][0]=0;
	tab2[1][1]=1;
	tab2[1][2]=1;
	tab2[1][3]=3;
	tab3[1][0]=0;
	tab3[1][1]=1;
	tab3[1][2]=1;
	tab3[1][3]=3;

	funcRec(2);
	funcRec(3);
	funcRec(4);
	funcRec(5);
	funcRec(6);
	funcRec(7);
	funcRec(8);
	funcRec(9);
	funcRec(10);
	funcRec(11);
	funcRec(12);
	funcRec(13);
	funcRec(14);
	funcRec(15);
	funcRec(16);
	funcRec(17);

	displayBase(6);
	//record(17);
	/*displayN(8,15);
	displayN(9,15);
	displayN(10,15);
	displayN(11,15);
	displayN(12,15);
	displayN(16,15);*/

	return EXIT_SUCCESS;
}


void funcRec(int n){
	int l0=2*pow(2,n);

	//// encodage
	//initialisation avec 4 et non 0
	for(int i =0; i<l0 ;i++){
	   for (int j=0;j<n;j++){
		   tab[n][i][j]=4;
	   }
	}
	for(int i =0; i<l0 ;i++){
		   tab2[n][i]=0;
		   tab3[n][i]=0;
	}

	//init : copier la table n-1
	if (n>=2){
		int offsetl = pow(2,n-1);
		int offsetc = 1;
		int nbl = pow(2,n);
		int nbc = n-1;

		for (int l=0;l<nbl;l++){
			for (int c=0;c<nbc;c++){
				tab[n][l+offsetl][c+offsetc]=tab[n-1][l][c];
			}
		}
	}

	//propager la table n-1 : les 0
	for (int l=0;l<pow(2,n);l++){
		tab[n][l][0]=0;
	}

	//propager la table n-1 : les 1
	for (int l=0;l<pow(2,n);l++){
		tab[n][l+(int)(pow(2,n-1))][0]=1;
	}
	//propager la table n-1 : les 3
	for (int l=pow(2,n);l<pow(2,n)+pow(2,n-1);l++){
		tab[n][l+(int)(pow(2,n-1))][0]=3;
	}

	//copier la table n-2
	if (n>=3){
		int offsetl1 = 0;
		int offsetl2 = pow(2,n+1)-pow(2,n-1);
		int offsetc = 1;
		int nbl = pow(2,n-1);
		int nbc = n-2;

		for (int l=0;l<nbl;l++){
			for (int c=0;c<nbc;c++){
				tab[n][l+offsetl1][c+offsetc]=tab[n-2][l][c];
				tab[n][l+offsetl2][c+offsetc]=tab[n-2][l][c];
			}
		}
	}

	//mettre les 01 en +/-3
	int l1 = pow(2,n)-3;
	int l2 = pow(2,n)+3;
	tab[n][l1-1][n-1]=0;
	tab[n][l1][n-1]=1;
	tab[n][l2-1][n-1]=0;
	tab[n][l2][n-1]=1;

	//// Décodage
	for(int i=0;i<l0;i++){
	   int nz=0;
	   for (int j=0;j<n;j++){
		   if (tab[n][i][j]>0){
			   nz=1;
		   }
		   if (tab[n][i][j]<=3 && nz==1){
			   tab2[n][i]= 10*tab2[n][i]+tab[n][i][j];
			   if (j==0){
				   tab3[n][i]=tab[n][i][j];
			   }
			   else{
				   if (tab[n][i][j-1]==1){
					   tab3[n][i]= 2*tab3[n][i]+tab[n][i][j];
				   }
				   else{// 0 ou 3
					   tab3[n][i]= 4*tab3[n][i]+tab[n][i][j];
				   }
			   }
		   }
	   }
	   // exceptions : le 0 et le 3 en position dizaine doit être multiplié par 2**2 et non 2**4
	   if (n%2==0){
		   if (i%6==0 || i%6==1){
			   tab3[n][i]=tab3[n][i]/2;
			   tab4[n][i]=2;
		   }
	   }
	   else{
		   if (i%6==4 || i%6==5){
			   tab3[n][i]=tab3[n][i]/2;
			   tab4[n][i]=2;
		   }
	   }
	   // pour traiter le fait que 1->1 et 2->1,111... mais ,111... n'est pas mentionné
	   tab3[1][2]=2;
	   if (i>0 && tab3[n][i]==tab3[n][i-1]){
		   tab3[n][i]++;
	   }
	}
}

void displayBase(int b){
	int l0=2*pow(2,b);
	for(int i=0;i<l0;i++){
		double puis;int puiss;
		double puis2;int puiss2;
		if (i<4){
			puis = 1;
		}
		else{
			puis = floor(log(i)/log(2));
		}
	   puis2=puis;
	   puiss = (int)puis;
	   puiss2 = puiss;
	   if (tab4[puiss][i]==2){
		   puiss2=puiss+1;puis2=puis+1;
	   }
	   printf("%5i %15lu-%2i /%5g : %12lu",i,tab2[puiss][i],tab4[puiss][i],pow(2,puis+1),tab3[puiss][i]);
       printf("%15lu-%2i /%5g : %12lu",tab2[b][i],tab4[b][i],pow(2,b+1),tab3[b][i]);
       printf("%15lu /%5g",tab2[puiss2][i],pow(2,puis2+1));
	   printf("\n");
	}
	printf ( "\n");
}

void displayN(int n, int nbBases){
	printf("%5i \n",n);
	for (int i=2; i< nbBases;i++){
		printf("%5i %15lu-%2i \n",i,tab2[i][n],tab4[i][n]);
	}
	printf("\n");
}


void record(int n){
    FILE* fichier = NULL;
    fichier = fopen("Df.txt", "w");
    if (fichier != NULL)
    {
    	int l0=2*pow(2,n);
    	for(int i=0;i<l0;i++){
    		double puis;int puiss;
    		double puis2;int puiss2;
    		if (i<4){
    			puis = 1;
    		}
    		else{
    			puis = floor(log(i)/log(2));
    		}
    		puis2=puis;
    		puiss = (int)puis;
    		puiss2 = puiss;
    	   if (tab4[puiss][i]==2){
    		   puiss2=puiss+1;puis2=puis+1;
    	   }
    	   fprintf(fichier,"%5i %20lu-%2i /%5g : %12lu",i,tab2[puiss][i],tab4[puiss][i],pow(2,puis+1),tab3[puiss][i]);
           fprintf(fichier,"%20lu-%2i /%5g : %12lu",tab2[n][i],tab4[n][i],pow(2,n+1),tab3[n][i]);
           fprintf(fichier,"%15lu /%5g",tab2[puiss2][i],pow(2,puis2+1));
    	   fprintf(fichier,"\n");
    	}
        fclose(fichier);
	}
}
