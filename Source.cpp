#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 20
#define MASTER 0

int main(int argc, char *argv[]) {

	int world_rank, world_size, i;
	int arr[N];


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	srand(time(NULL));

	for (int j = 0; j < N; j++)
	{
		arr[j] = rand() % 3;
	}

	printf("Current Rank: %d\n", world_rank);

	int total = 0;
	int the_piece; 

	the_piece = N / world_size;

	if (world_rank != MASTER){
		int tempTotal = 0;

		for (i = 0; i < the_piece; i++) {
			tempTotal += arr[(world_rank - 1) * the_piece + i];
		}

		printf("* Rank %d sending value %d\n", world_rank, tempTotal);
		MPI_Send(&tempTotal, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		printf("* Rank %d value sent\n", world_rank);

	}
	else {
		printf("RANK 0 receiving values:\n");

		int temp;

		for (i = 1; i < world_size; i++) {
			MPI_Recv(&temp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			printf("Received value %d from rank %d\n", temp, i);

			total += temp;
		}

		printf("Sum of the array = %d\n", total);
	}
	MPI_Finalize();
}