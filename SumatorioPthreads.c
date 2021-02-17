/* 
 * FirstMultiThreading.c - Primera aplicación multi-hilo 
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define DMaxThreads 100

/* Definición Estructuras */
typedef struct Intervalo {
	int begin;
	int end;
} TIntervalo;

/* Prototipos Funciones */
long int *Sumatorio(TIntervalo *i);


int main(int argc, char *argv[])
{
	int N, M;
	int h;
	pthread_t Tids[DMaxThreads];
	TIntervalo Interval[DMaxThreads];
	long int SumaTotal=0, *SumaParcial, ResultadoCorrecto;

	
	if (argc<3)
	{
		fprintf(stderr,"Argumentos insuficientes.\n");
		exit(-1);
	}
	
	N = atol(argv[1]);
	M = atoi(argv[2]);
	if (M>DMaxThreads)
			M=DMaxThreads;
   
  	/* Creación Hilos*/
	for (h=0;h<M;h++)
	{
		if (h==0)
			Interval[h].begin = 1;
		else
			Interval[h].begin = Interval[h-1].end;

		if (h==(M-1))
			Interval[h].end = N+1;
		else
			Interval[h].end = Interval[h].begin + ((N-Interval[h].begin)+1)/(M-h);
		
		if (pthread_create(&Tids[h], NULL, (void *(*) (void *)) Sumatorio, &Interval[h])!=0)
		{
			perror("Error creación hilos.\n");
			exit(-1);
		}
		//printf("Hilo %d Creado -> Intervalo (%d,%d].\n",h+1,Interval[h].begin, Interval[h].end);
		
	}
	
	SumaTotal=0;
  	/* Esperar finalización Hilos*/
	for (h=0;h<M;h++)
	{
		pthread_join(Tids[h],(void**)&SumaParcial);
		SumaTotal += *SumaParcial;
		free(SumaParcial);
	}
	
	ResultadoCorrecto = ((long int)N * ((long int)N+1))/2;
	printf("Sumatorio %d primeros numeros: %ld (resultado esperado %ld).\n",N,SumaTotal,ResultadoCorrecto);

  	exit(0);
}


long int *Sumatorio(TIntervalo *i)
{
	int x;
	long int *resp=malloc(sizeof(long int));
	
	*resp=0;
	for(x=i->begin;x<i->end;x++)
		*resp += x;
  	
  	return (resp);
}
