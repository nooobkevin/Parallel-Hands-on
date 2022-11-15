#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Each send gives CHUNK_SIZE points
#define CHUNK_SIZE 1000000

// Total number of runs
#define RUN 1000

int main(int argc, char *argv[])
{
	int size, rank, source;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	double start, end;
	MPI_Barrier(MPI_COMM_WORLD); /* IMPORTANT */
	start = MPI_Wtime();

	int i = 0, j = 0;
	int count = 0, total = 0;
	double x, y;

	if (rank != 0)
	{ // Sending messages using a process other than 0
		srand((unsigned)time(NULL) + rank * 10);
		for (j = 0; j < RUN / (size - 1); j++)
		{
			for (i = 0; i < CHUNK_SIZE; i++)
			{
				x = rand() / (RAND_MAX + 1.0);
				y = rand() / (RAND_MAX + 1.0);
				if (x * x + y * y < 1)
				{
					count++;
				}
			}
			printf("rank %d loop %d pi is %.20lf \n", rank, j, 4.0 * count / ((j + 1) * CHUNK_SIZE));
		}
		MPI_Send(&count, 1, MPI_INT, 0, 99,
				 MPI_COMM_WORLD);
	}
	else
	{ // myid == 0 getting message from other process
		for (source = 1; source < size; source++)
		{
			MPI_Recv(&count, 1, MPI_INT, source, 99,
					 MPI_COMM_WORLD, &status);
			total += count;
			// printf("get the message from %d: %d\n", source, count);
		}
		printf("the final PI is %.20lf \n", 4.0 * total / (RUN * CHUNK_SIZE));
	}

	MPI_Barrier(MPI_COMM_WORLD); /* IMPORTANT */
	end = MPI_Wtime();

	MPI_Finalize();

	if (rank == 0)
	{ /* use time on master node */
		printf("Runtime = %f\n", end - start);
	}

} /* end main */
