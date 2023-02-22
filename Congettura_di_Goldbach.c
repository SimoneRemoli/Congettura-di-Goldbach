/*
 ============================================================================
 Name        : Congettura.c
 Author      : Simone Remoli
 Description : Congettura di Goldbach
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include ".../gmp.h"

//Essa afferma che ogni numero pari maggiore di 2
//può essere scritto come somma di due numeri primi (che possono essere anche uguali).

long long int conta_primi(mpz_t,mpz_t,mpz_t*);
void views_array(mpz_t*,long long int);
void Congettura_di_Goldbach(mpz_t*, long long int,mpz_t);


int main(void)
{
	mpz_t *A,numero,app,numerotot;
	long long int dimensione = 0;
	A = (mpz_t *)malloc(100000 * sizeof(mpz_t));
	mpz_init_set_str(numero, "0", 10);
	mpz_init_set_str(app, "0", 10);
	mpz_init_set_str(numerotot, "0", 10);

	gmp_printf("\n");
	gmp_printf("\t \t Inserisci il valore per dimostrare la Congettura_di_Goldbach: ");
	gmp_scanf (" %Zd", numero);

	mpz_set(app,numero);
	mpz_set(numerotot,numero);

	dimensione = conta_primi(app,numero,A);
	views_array(A,dimensione);
	Congettura_di_Goldbach(A,dimensione,numerotot);

	mpz_clear(numero);
	mpz_clear(app);
	mpz_clear(numerotot);
	mpz_clear(*A);
	return 0;
}

void Congettura_di_Goldbach(mpz_t *A,long long int dimensione, mpz_t numero)
{
	printf("\n");
	mpz_t mom;
	mpz_init_set_str(mom, "0", 10);
	for(int i=0;i<dimensione-1;i++)
	{
		for(int j=i+1;j<dimensione;j++)
		{
			mpz_init_set_str(mom, "0", 10);
			mpz_add(mom,A[i],A[j]);
			if(mpz_cmp(mom,numero)==0)
				gmp_printf("\t \t %Zd + %Zd = %Zd \n",A[i],A[j],numero);
		}
		mpz_init_set_str(mom, "0", 10);
		mpz_add(mom,A[i],A[i]);
		if(mpz_cmp(mom,numero)==0)
			gmp_printf("\t \t %Zd + %Zd = %Zd \n",A[i],A[i],numero);
	}
}
void views_array(mpz_t *A,long long int dimensione)
{
	printf("\n");
	printf("\t \t Lista dei numeri primi precedenti : \n ");
	for (int i=0; i<dimensione; i++)
	{
		gmp_printf(" \t \t %Zd \n",A[i]);
	}
	printf("\n");
}

long long int conta_primi(mpz_t app,mpz_t numero,mpz_t *A) 
{
	mpz_t singolo,doppio;
	mpz_init_set_str(singolo, "1", 10);
	mpz_init_set_str(doppio, "2", 10);
	bool check = false;
	mpz_sub(app,app,singolo);
	mpz_sub(numero,numero,doppio);
	long long int i = 0;
	while(mpz_cmp(app,doppio)!=0)
	{
		if(mpz_cmp(numero,singolo)==0)
		{
			if(check == false)
			{
				mpz_set(A[i],app);
				i = i + 1;
			}
			check = false;
			mpz_sub(app,app,singolo);
			mpz_set(numero,app);
			mpz_sub(numero,numero,singolo);
		}
		if(mpz_divisible_p(app, numero)>0)
			check = true;
		mpz_sub(numero,numero,singolo);
	}
	mpz_set(A[i],doppio);
	i = i + 1;
	return i;
}



