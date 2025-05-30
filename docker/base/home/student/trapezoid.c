#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

double f(double x);

int main(int argc, char * argv[] ) {
  int rank;     /* rank of each MPI process */
  int size;     /* total number of MPI processes */
  double a, b;  /* default left and right endpoints of the interval */
  int n;        /* total number of trapezoids */
  double h;        /* height of the trapezoids */
  double local_a, local_b; /* left and right endpoints on each MPI process */
  int local_n;  /* number of trapezoids assigned to each individual MPI process */
  double result = 0.0;       /* final integration result */
  double local_result = 0.0; /* partial integration result at each process */
  int i;        /* counter */
  double start, end; /* timer */

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  start = MPI_Wtime();

  a = atof(argv[1]);
  b = atof(argv[2]);
  n = atoi(argv[3]);

  // calculate work interval for each process
  h = (b - a) / n;
  local_n = n / size;
  local_a = a + rank * local_n * h;
  local_b = local_a + h;
  for (i = 0; i < local_n; i++) {
    local_result += 0.5 * h * (f(local_a) + f(local_b));
    local_a = local_b;
    local_b += h;
  }

  // sending the results back to the master
  MPI_Reduce(&local_result,&result,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
  end = MPI_Wtime();

  // displaying output at the master node
  if (rank == 0){
    printf("The integral of f(x) from %lf to %lf using %d processses is %lf\n", 
           a, b, size, result);
    printf("Runtime: %lf seconds \n", end - start);
  }

  MPI_Finalize();
}

double f(double x) {
  return ( x*x*x*x );
}