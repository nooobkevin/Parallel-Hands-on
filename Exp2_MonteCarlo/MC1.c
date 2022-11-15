#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Master rank = 0
#define Master 0

// Each send gives CHUNK_SIZE points, and this represents the number of points to be tested at each job
#define CHUNK_SIZE 1000000

// Total number of jobs
#define RUN 1000

// Some constant flags to send
#define SUBMIT 1
#define DELIVER 0

int main(int argc, char *argv[]){
  double start, end;
	MPI_Init(&argc, &argv); //Init MPI
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
 
  MPI_Barrier(MPI_COMM_WORLD); /* keep all process start at same time */
  start = MPI_Wtime();  //record the start time
  
	if (rank == Master) {
		doMaster();
	} else {
		doSlave();
	}
   
  MPI_Barrier(MPI_COMM_WORLD); /* Stop the processes until all processes in the communicator complete . */
  end = MPI_Wtime(); //record the end time
  
	MPI_Finalize();
 
  if (rank == 0) { /* use time on master node */
  printf("Runtime = %f\n", end-start);
  }
	return 0;
}

void doMaster(){
	MPI_Status status;

	double randBuf[CHUNK_SIZE * 2]; //Each point has two coordinates.

	long recvBuf;  //This variable is used to receive results
	long nIn = 0, nTotal = 0;

	int i,j,k;

	srand(0);


	while (RUN>k) {

			// Wait for someone to submit
			MPI_Recv(&recvBuf, 1, MPI_LONG, MPI_ANY_SOURCE, SUBMIT, MPI_COMM_WORLD, &status);  
      // MPI_ANY_SOURCE represents that the process will attempt to accept information from all processes
			if (recvBuf >= 0) {  //This section will record the results of each job
					nTotal += CHUNK_SIZE;  //the number of points tested in a job
					nIn += recvBuf;        //the number of points distributed in the circle in a job
					printf("%d  %d   Pi = %.20lf after %ld sampling.\n",k,status.MPI_SOURCE, 4.0 * nIn / nTotal, nTotal);
			}
			// Prepare a new chunk of data
			for (i = 0; i < CHUNK_SIZE * 2; i++) {  //This section will generate a new job
				randBuf[i] = rand() * 1.0 / RAND_MAX;
			}

			// Send a chunk of data, status.MPI_SOURCE represents the process that just finished the work
			MPI_Send(randBuf, CHUNK_SIZE * 2, MPI_DOUBLE, status.MPI_SOURCE, DELIVER, MPI_COMM_WORLD);
      k++;
	}

}


void doSlave(){
	MPI_Status status;

	double randBuf[CHUNK_SIZE * 2];   //Each point has two coordinates. The even number of the array is the x-axis coordinate and the odd number is the y-axis coordinate

	long nIn = -1l;  //Set a negative number
	int i,k=0;

	MPI_Send(&nIn, 1, MPI_LONG, Master, SUBMIT, MPI_COMM_WORLD); //send a negative number to master indicates that the process is ready
 
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);   

	while (RUN/(size-1)>k) {      //size-1 is the total number of slave
		// receive a data trunk, get the positions of all points in this job
		MPI_Recv(randBuf, CHUNK_SIZE * 2, MPI_DOUBLE, Master, DELIVER, MPI_COMM_WORLD, &status);

		nIn = 0; // reset counter
		for (i = 0; i < CHUNK_SIZE ; i++) { //test x^2+y^2, test how many dots are inside the circle
			if (randBuf[2 * i] * randBuf[2 * i] + randBuf[2 * i + 1] * randBuf[2 * i + 1] <= 1.0)  
				nIn++;
		}
		
		// send back the result
		MPI_Send(&nIn, 1, MPI_LONG, Master, SUBMIT, MPI_COMM_WORLD);
    k++;
	}
}

