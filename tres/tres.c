#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define MAX_STRING 100 // Increased buffer size for safety

int main(int argc, char *argv[])
{
    int processor, nprocesadores;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &processor);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocesadores);

    char *str[] = {"tres", "tristes", "tigres", "trigaban", "trigo", "por", "culpa", "del", "bolivar"};
    int length = sizeof(str) / sizeof(str[0]);

    char *out1[length];
    char *out2[length];
    //Usamos memset para limpiar los arrays
    memset(out1, 0, sizeof(out1));
    memset(out2, 0, sizeof(out2));

    // https://web.corral.tacc.utexas.edu/CompEdu/pdf/pcse/EijkhoutParallelProgramming.pdf
    // 39
    
    int messages_to_receive = length / (nprocesadores - 1);
    int excess = length % (nprocesadores - 1);

    if (processor <= excess)
    {
        messages_to_receive += 1;
    }

    char message[MAX_STRING];
    MPI_Status status;
    MPI_Request request;

    if (processor == 0)
    {
        /**
         * Envia todas las tareas a los otros procesadores, tambien se envie un identificador llamado tag
         * este valor es la posicion de la palabra en el array.
        */
        for (int i = 0; i < length; i++)
        {
            int target = (i % (nprocesadores - 1)) + 1;
            int tag = i;
            MPI_Isend(str[i], strlen(str[i]) + 1, MPI_CHAR, target, tag, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);
        }

        /**
         * Espera que los otros procesadores retornen los valores
         * Obtiene el TAG y segun eso lo guarda en el array out1 u out2
        */
        for (int i = 0; i < length; i++)
        {
            MPI_Recv(message, MAX_STRING, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            if (status.MPI_TAG % 2 == 0)
            {
                out1[status.MPI_TAG / 2] = strdup(message);
                //out1[status.MPI_TAG / 2] = message;

            }
            else
            {
                out2[status.MPI_TAG / 2] = strdup(message);
                //out2[status.MPI_TAG / 2] = message;
            }
        }
    }
    else
    {
        /**
         * Los otros procesadores esperan a que lleguen las tareas.
         * Y cuando llegan se envian al procesador principal 0
         * cada tarea se envie con su respectiva TAG
        */
        for (int i = 0; i < messages_to_receive; i++)
        {
            MPI_Irecv(message, MAX_STRING, MPI_CHAR, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);
            MPI_Isend(&message, strlen(message) + 1, MPI_CHAR, 0, status.MPI_TAG, MPI_COMM_WORLD, &request);
        }
    }

    if (processor == 0)
    {
        //Cuando todo termina se imprime los resultados de out1 y out2
        for (int i = 0; out1[i] != NULL; ++i)
        {
            printf("%s ", out1[i]);
        }
        printf("\n");
        for (int i = 0; out2[i] != NULL; ++i)
        {
            printf("%s ", out2[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
