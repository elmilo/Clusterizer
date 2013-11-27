#ifndef KMEANS_H_
#define KMEANS_H_

#include <eigen2/Eigen/Dense>
#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include <cluster.h>
}

using namespace Eigen;

/**
 * Matrix< tipo que guarda, cant filas, cant cols, orden (no importante): RowMajor o ColMajor >
 * */
class kMeans {
private:
	// matriz temporal para guardar los datos de entrada en RowMajor (eficiencia)
	Matrix<double, Dynamic, Dynamic, RowMajor>* datosTemporales;
	// Array para guardar los ids
	int* clusterID;
	// Algoritmo para calcular los kmeans
	void kmeans(int cantFilas, int cantCols, double** datos, int** mask, int clusters);

public:
	//Llamadas sucesivas
	void cluster(Matrix<float, Dynamic, Dynamic, RowMajor>* datosa, int clusters);
	//Retorna un clusterID
	int* getClusterIDs();
};

#endif
