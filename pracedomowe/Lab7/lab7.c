#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "mpi.h"

#define LOTNISKO 1
#define START 2
#define LOT 3
#define KONIEC_LOTU 4
#define BUM 5
#define TANKOWANIE 1000
#define KONIEC_PALIWA 500

int LONDOWANIE = 1;
int LATANIE = 0;
int paliwo = 1500;
int iloscSamolotow;
int liczba_lotnisk = 3;
int zajete_lotniska = 0;
int tag = 1;
int WYSYLKA[2];
int ODBIUR[2];
int n;
int p_id;
MPI_Status mpi_status;

void Pilot()
{
	sleep(2);
	if(ODBIUR[0] == LOT)
		printf("Pilot samolotu nr %d przelecia³ nad miastem \n", ODBIUR[1]);
	if(ODBIUR[0] == START)
		printf("Pilot samolotu nr %d wystartowal \n", ODBIUR[1]);
	if(ODBIUR[0] == KONIEC_LOTU)
		printf("Pilot samolotu nr %d musi przeprowadzic ladowanie \n", ODBIUR[1]);
	if(ODBIUR[0] == LOTNISKO)
		printf("Pilot samolotu nr %d przebywa na lotnisku \n", ODBIUR[1]);
	if(ODBIUR[0] == BUM)
		printf("Pilot samolotu nr %d nie zyje \n", ODBIUR[1]);
}

void Wyslij(int stan, int nrSamolotu)
{
	WYSYLKA[0] = stan;
	WYSYLKA[1] = numer_samolotu;
	MPI_Send(&WYSYLKA, 2, MPI_INT, 0, tag, MPI_COMM_WORLD);
	sleep(1);
}

void Ladowisko(int n)
{
	int numer_samolotu;
	int stan;
	
	iloscSamolotow = n - 1;
	
	while(liczba_lotnisk <= iloscSamolotow)
	{
		MPI_Recv(&ODBIUR,2,MPI_INT,MPI_ANY_SOURCE,tag,MPI_COMM_WORLD, &mpi_status);
		stan = ODBIUR[0];
		numer_samolotu = ODBIUR[1];
		
		if(stan == LOTNISKO)
		{
			printf("Samolot nr %d stoi na lotnisku \n", numer_samolotu);
		}
			
		if(stan == START)
		{
			printf("Pozwolenia na start samolotowi nr %d \n", numer_samolotu);
			zajete_lotniska--;
		}
			
		if(stan == LOT)
		{
			printf("Samolot nr %d lata \n", numer_samolotu);
			Pilot();
		}
			
		if(stan == KONIEC_LOTU)
		{
			if(zajete_lotniska < liczba_lotnisk)
			{
				zajete_lotniska++;
				MPI_Send(&LONDOWANIE, 1, MPI_INT, numer_samolotu, tag, MPI_COMM_WORLD);
			}
			else
			{
				MPI_Send(&LATANIE, 1, MPI_INT, numer_samolotu, tag, MPI_COMM_WORLD);
			}
		}
		
		if(stan == BUM)
		{
			iloscSamolotow--;
			printf("Wybuch Samolotu nr %d, pozostalo %d statkow \n", numer_samolotu, iloscSamolotow);
		}
	}
}

void Samolot()
{
	int stan = LOT;
	int suma;
	int i;
	
	while(1)
	{
		if(stan == LONDOWANIE)
		{
			if(rand()%4 == 1)
			{
				stan = START;
				paliwo = TANKOWANIE;
				printf("Na lotnisku prosze o pozwolenie na start, Samolot nr %d \n", p_id);
				
			}
			else
			{
				printf("Samolot jeszcze poczeka \n");
			}
			Wyslij(stan, p_id);
		}
		
		if(stan == START)
		{
			printf("Wystartowalem, samolot nr %d \n", p_id);
			stan = LOT;
			Wyslij(stan, p_id);
		}
		
		if(stan == LOT)
		{
			paliwo -= rand()%200;
			if(paliwo <= KONIEC_PALIWA)
			{
				stan = KONIEC_LOTU;
				Wyslij(stan, p_id);
			}
			else
			{
				sleep(3);
			}
		}
		
		if(stan == KONIEC_LOTU)
		{
			int st;
			MPI_Recv(&st, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &mpi_status);
			if(st == LONDOWANIE)
			{
				stan = LOTNISKO;
				printf("Wyladowalem, samolot nr %d \n", p_id);
			}
			else
			{
				paliwo -= rand()%200;
				if(paliwo > 0)
				{
					Wyslij(stan, p_id);
				}
				else
				{
					stan = BUM;
					printf("gwaltowna kolizja z ziemia \n");
					Wyslij(stan, p_id);
					return;
				}
			}
		}	
	}
}

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&p_id);
	MPI_Comm_size(MPI_COMM_WORLD,&n);
	srand(time(NULL));
	
	if(p_id == 0)
		Ladowisko(n);
	else
		Samolot();
	
	MPI_Finalize();
	return 0;
}
