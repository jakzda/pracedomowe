#include <stdio.h>
#include <math.h>
#include "mpi.h"
float f(float x)
{
    return powf(x,2);
}

int main(int argc, char **argv)
{
        int p_id;
        float calka = 0;
        int i = 1; 
        int n;
        int i_tag = 1;
        int calka_tag= 2;
        int xp_tag = 3;
        int xk_tag = 4;
        int dx_tag = 5;
        int suma_tag = 6;
        float xp = 0;
        float xk = 10;
        float dx = 0;
        float suma=0;
        MPI_Status status;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &p_id);
        MPI_Comm_size(MPI_COMM_WORLD, &n);
        if(p_id == n - 1)
        {
                dx = (xk - xp) / (float)n;
                calka += f(xp + i * dx);
                calka*=dx;
                suma += calka;
                calka = 0;  
                i++;
                MPI_Send(&i, 1, MPI_INT ,p_id - 1 , i_tag, MPI_COMM_WORLD);
                MPI_Send(&calka, 1, MPI_FLOAT , p_id - 1, calka_tag, MPI_COMM_WORLD);
                MPI_Send(&xp, 1, MPI_FLOAT, p_id - 1, xp_tag, MPI_COMM_WORLD);
                MPI_Send(&xk, 1, MPI_FLOAT, p_id - 1, xk_tag, MPI_COMM_WORLD);
                MPI_Send(&dx, 1, MPI_FLOAT, p_id - 1, dx_tag, MPI_COMM_WORLD);
                MPI_Send(&suma, 1, MPI_FLOAT, p_id - 1, suma_tag, MPI_COMM_WORLD);
        } 
        if((p_id > 0)&&(p_id < n - 1))
        {
                MPI_Recv(&i, 1, MPI_INT, p_id + 1, i_tag, MPI_COMM_WORLD, &status);
				MPI_Recv(&calka, 1, MPI_FLOAT, p_id + 1, calka_tag, MPI_COMM_WORLD, &status);
                MPI_Recv(&xp, 1, MPI_FLOAT, p_id + 1, xp_tag, MPI_COMM_WORLD, &status);
                MPI_Recv(&xk, 1, MPI_FLOAT, p_id + 1, xk_tag, MPI_COMM_WORLD, &status);
                MPI_Recv(&dx, 1, MPI_FLOAT, p_id + 1, dx_tag, MPI_COMM_WORLD, &status);
                MPI_Recv(&suma, 1, MPI_FLOAT, p_id + 1, suma_tag, MPI_COMM_WORLD, &status);
                calka += f(xp + i * dx);
                calka += (f(xp) + f(xk))/2;
                calka *= dx;
                suma += calka;
                calka = 0;  
                i++;

                MPI_Send(&i, 1, MPI_INT, p_id - 1, i_tag, MPI_COMM_WORLD);
                MPI_Send(&calka, 1, MPI_FLOAT, p_id - 1, calka_tag, MPI_COMM_WORLD);
                MPI_Send(&xp, 1, MPI_FLOAT, p_id - 1, xp_tag, MPI_COMM_WORLD);
                MPI_Send(&xk, 1, MPI_FLOAT, p_id - 1, xk_tag, MPI_COMM_WORLD);
                MPI_Send(&dx, 1, MPI_FLOAT, p_id - 1, dx_tag, MPI_COMM_WORLD); 
                MPI_Send(&suma, 1, MPI_FLOAT, p_id - 1, suma_tag, MPI_COMM_WORLD); 
        } 
        if(p_id == 0)
        {
                MPI_Recv(&i, 1, MPI_INT, p_id + 1, i_tag, MPI_COMM_WORLD, &status);
                MPI_Recv(&calka, 1, MPI_FLOAT, p_id + 1, calka_tag, MPI_COMM_WORLD, &status);
                MPI_Recv(&xp, 1, MPI_FLOAT, p_id + 1, xp_tag, MPI_COMM_WORLD, &status);
                MPI_Recv(&xk, 1, MPI_FLOAT, p_id + 1, xk_tag, MPI_COMM_WORLD, &status);
                MPI_Recv(&dx, 1, MPI_FLOAT, p_id + 1, dx_tag, MPI_COMM_WORLD, &status);
                MPI_Recv(&suma, 1, MPI_FLOAT, p_id + 1, suma_tag, MPI_COMM_WORLD, &status);
                printf("Wynik: %f",suma);
        }    
        MPI_Finalize();
        return 0;
}
