#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int serie_par(int i) {
    return i * 2;
}

int serie_impar(int i) {
    return i * i + 1;
}

int main(int argc, char *argv[]) {
    int procesador, nprocesadores, i;
    int inicio = 1, fin = 10000 + 2;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocesadores);

    int out1[fin + 1];
    int out2[fin + 1];

    memset(out1, 0, sizeof(out1));
    memset(out2, 0, sizeof(out2));

    //Crea grupos para distribuir la carga entre los procesadores
    int rango = (fin - inicio + 1) / nprocesadores;
    int local_inicio = inicio + procesador * rango;
    int local_fin = (procesador == nprocesadores - 1) ? fin + 1 : local_inicio + rango;

    for (i = local_inicio; i < local_fin; i++) {
        int par = serie_par(i);
        int impar = serie_impar(i);

        if (procesador == 0) {
            out1[i] = par;
            out2[i] = impar;
        } else {
            MPI_Send(&par, 1, MPI_INT, 0, i, MPI_COMM_WORLD);
            MPI_Send(&impar, 1, MPI_INT, 0, i, MPI_COMM_WORLD);
        }
    }

    if (procesador == 0) {
        //Itera todos los procesadores y obtiene el rango de tareas que se mando a esos procesadores
        for (int j = 1; j < nprocesadores; j++) {
            for (i = inicio + j * rango; i < inicio + (j + 1) * rango; i++) {
                MPI_Recv(&out1[i], 1, MPI_INT, j, i, MPI_COMM_WORLD, &status);
                MPI_Recv(&out2[i], 1, MPI_INT, j, i, MPI_COMM_WORLD, &status);
            }
        }

        for (i = inicio; i <= fin; i++) {
            printf("%d %d ", out1[i], out2[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
