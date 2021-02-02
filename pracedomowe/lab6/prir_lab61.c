#include <stdio.h>
#include <math.h>
#include "mpi.h"


int main(int argc, char **argv)
{
        int i = 1;
        int p_id;
        int n;
        int i_tag = 1;
        int suma_tag = 2;
        
        float suma = 0;
        float wynik = 0;
     
        MPI_Status status;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &p_id);
        MPI_Comm_size(MPI_COMM_WORLD, &n);
        
        if(p_id == 0)
        {
                wynik=powf(-1, i-1) / (2 * i - 1);
                suma=suma+wynik*4;
                printf("Proces: %d ,i:%i wynik: %f, suma %f\n", p_id, i, wynik, suma);  
                i++;
                MPI_Send(&i, 1, MPI_INT ,p_id + 1 ,i_tag, MPI_COMM_WORLD);
                MPI_Send(&suma, 1, MPI_FLOAT ,p_id + 1 ,suma_tag, MPI_COMM_WORLD);
        } 
        if((p_id > 0)&&(p_id < n - 1))
        {
                MPI_Recv(&i, 1, MPI_INT, p_id - 1, i_tag, MPI_COMM_WORLD, &status);
                MPI_Recv(&suma, 1, MPI_FLOAT, p_id - 1, suma_tag, MPI_COMM_WORLD, &status);
                wynik=powf(-1, i-1) / (2 * i - 1);
                suma = suma + wynik * 4;
                printf("Proces: %d ,i:%i wynik: %f, suma %f\n", p_id, i, wynik, suma);  
                i++;
                if(p_id != n - 1)
                {
                
                        MPI_Send(&i, 1, MPI_INT, p_id + 1, i_tag, MPI_COMM_WORLD);
                        MPI_Send(&suma, 1, MPI_FLOAT, p_id + 1, suma_tag, MPI_COMM_WORLD);
                }
        }    
        
        MPI_Finalize();
        return 0;
}
