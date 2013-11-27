#include "kMeans.h"

//passed in datos must be organized into rows-dimensions, cols-observations and MUST be a matrix in RowMajor
void kMeans::cluster(Matrix<float, Dynamic, Dynamic, RowMajor>* datosa, int clusters){
	
  // ** crear una nueva matriz traspuesta  ** //
  datosTemporales = new Matrix<double, Dynamic, Dynamic, RowMajor>;
  (*datosTemporales) = datosa->transpose().cast<double>(); 
  const int cantFilas = datosTemporales->rows();
  const int cantCols = datosTemporales->cols();
  
  // ** create pointer to the datos within the matrix ** //
  double** datos_pointer;
  datos_pointer = (double**) malloc(datosTemporales->rows()*sizeof(double*));
  for (int i=0; i<datosTemporales->rows(); i++) datos_pointer[i] = &(*datosTemporales)(i, 0);

  // ** create mask ** //
  int** mask = (int**) malloc(cantFilas * sizeof(int*));
  for(int i=0; i<cantFilas; i++) mask[i] = (int*) malloc(cantCols*sizeof(int));
  for(int i=0; i<cantFilas; i++)
	  for(int j=0; j<cantCols;j++)
		  mask[i][j] = 1;
  
  // ** perform clustering ** //
  kmeans(cantFilas, cantCols, datos_pointer, mask, clusters);

  // ** free memory ** //
  datosTemporales->resize(0,0);
  free(datosTemporales);
}

int* kMeans::getClusterIDs() {
	return clusterID; 
}


void kMeans::kmeans(int cantFilas, int cantCols, double** datos, int** mask, int clusters){
  int i, j;
  const int nclusters = clusters;
  const int transpose = 0;
  const char dist = 'e'; // distancia euclidea
  const char method = 'a';
  int npass = 1;
  int ifound = 0;
  double error;
  double distance;
  int** index;
  int* count;
  
  double* weight = (double*) malloc(cantCols*sizeof(double));
  
  clusterID = (int*) malloc(cantFilas*sizeof(int));
  
  double** cdatos = (double**) malloc(nclusters*sizeof(double*));
  
  int** cmask = (int**) malloc(nclusters*sizeof(int*));
  
  for (i = 0; i < nclusters; i++){
	cdatos[i] = (double*) malloc(cantCols*sizeof(double));
    cmask[i] = (int*) malloc(cantCols*sizeof(int));
  }
  
  for (i = 0; i < cantCols; i++) weight[i] = 1.0;
  printf("======================== k-means clustering ====================\n");
  printf("\n");
  printf("----- one pass of the EM algorithm (results may change)\n");
  kcluster(nclusters,cantFilas,cantCols,datos,mask,weight,transpose,npass,method,dist, 
    clusterID, &error, &ifound);
  printf ("Solution found %d times; within-cluster sum of distances is %f\n",
    ifound, error);
  printf ("Cluster assignments:\n");
  for (i = 0; i < cantFilas; i++)
    printf ("Gene %d: cluster %d\n", i, clusterID[i]);

  printf ("\n");
  printf("----- 1000 passes of the EM algorithm (result should not change)\n");
  npass = 1000;
  kcluster(nclusters,cantFilas,cantCols,datos,mask,weight,transpose,npass,method,dist, 
    clusterID, &error, &ifound);
  printf ("Solution found %d times; ", ifound);
  printf ("within-cluster sum of distances is %f\n", error);
  printf ("Cluster assignments:\n");
  for (i = 0; i < cantFilas; i++)
    printf ("Gene %d: cluster %d\n", i, clusterID[i]);
  printf ("\n");
  printf ("------- Distance between clusters:\n");
  index = (int**) malloc(nclusters*sizeof(int*));
  count = (int*) malloc(nclusters*sizeof(int));
  for (i = 0; i < nclusters; i++) count[i] = 0;
  for (i = 0; i < cantFilas; i++) count[clusterID[i]]++;
  for (i = 0; i < nclusters; i++) index[i] = (int*) malloc(count[i]*sizeof(int));
  for (i = 0; i < nclusters; i++) count[i] = 0;
  for (i = 0; i < cantFilas; i++){
	int id = clusterID[i];
    index[id][count[id]] = i;
    count[id]++;
  } 
  
  /////////////ESTO 
  /////////////ESTO
  /////////////ESTO
  /////////////ESTO/////////////ESTO
  /////////////ESTO
  /////////////ESTO
  /////////////ESTO
  /////////////ESTO
  distance =
    clusterdistance(cantFilas, cantCols, datos, mask, weight, count[0], count[1],
		    index[0], index[1], 'e', 'a', 0); 
  printf("Distance between 0 and 1: %7.3f\n", distance);
  distance =
    clusterdistance(cantFilas, cantCols, datos, mask, weight, count[0], count[2],
		    index[0], index[2], 'e', 'a', 0); 
  printf("Distance between 0 and 2: %7.3f\n", distance);
  distance =
    clusterdistance(cantFilas, cantCols, datos, mask, weight, count[1], count[2],
		    index[1], index[2], 'e', 'a', 0); 
  printf("Distance between 1 and 2: %7.3f\n", distance);

  printf ("\n");
  printf ("------- Cluster centroids:\n");
  getclustercentroids(nclusters, cantFilas, cantCols, datos, mask, clusterID,
                      cdatos, cmask, 0, 'a');
  printf("   Microarray:");
  for(i=0; i<cantCols; i++) printf("\t%7d", i);
  printf("\n");
  for (i = 0; i < nclusters; i++)
  { printf("Cluster %2d:", i);
    for (j = 0; j < cantCols; j++) printf("\t%7.3f", cdatos[i][j]);
    printf("\n");
  }
  printf("\n");
  for (i = 0; i < nclusters; i++) free(index[i]);
  free(index);
  free(count);

  for (i = 0; i < nclusters; i++)
  { free(cdatos[i]);
    free(cmask[i]);
  }
  free(cdatos);
  free(cmask);
  //free(clusterID);
  free(weight);
  return;
}

