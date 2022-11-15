#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define MASTER 0   //set the first process as master to send message
#define TAG 1      //set the communication key

int main(int argc, char* argv[])
{
    MPI_Status status;
    char Hostname[81];
    char Buffer[81] = "Me";
    int myRank,nTasks, Slave;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &nTasks);   
    gethostname(Hostname,80);
    if (myRank == MASTER) {  //here is master process need to do
      for (Slave = 1; Slave < nTasks; Slave++) {
            MPI_Send(Hostname,80, MPI_CHAR, Slave, TAG,
                MPI_COMM_WORLD);
      }
    }
    else{//here is slave process need to do
            MPI_Recv(Buffer, 80, MPI_CHAR, MASTER, TAG,
                MPI_COMM_WORLD, &status);
    }
    printf("Hello World from Host %s \t rank %d : Master is %s\n",Hostname,myRank,Buffer);
    MPI_Finalize();
    return 0;
} /* end main */

