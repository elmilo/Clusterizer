#ifndef KMEANS_H
#define KMEANS_H

#include <limits>
#include <vector>
#include <cmath> 
#include <iostream>

#include <stdlib.h>     /* srand, rand */
#include <time.h>

#define FORMATOSALIDA FormatoImpresion(Eigen::StreamPrecision, 0, "; ", "\n", "", "");

#include "TiposGlobales.h"

//#define EIGEN_DEFAULT_IO_FORMAT Eigen::IOFormat(Eigen::StreamPrecision, 0, ", ", " ", "", "")

//#define EIGEN_DEFAULT_IO_FORMAT Eigen::IOFormat(Eigen::FullPrecision)

/**
* Matrix< tipo que guarda, cant filas, cant cols >
* 
* */

class kMeans {
private:
    
    const static TipoGuardado TOLERANCIA = 1e-2;
    
    int cantElementos; //Dimension (de las palabras por ejemplo)
    int cantClusters; // cantidad de clusters que se quieren armar
    int cantVectores; // cantidad de elementos clusterizables (documentos por ejemplo)

    TipoMatriz matrizInicial; // cada fila es el centroide del cluster
    TipoMatriz centroides; // cada fila es el centroide del cluster
    TipoMatriz nuevosCentroides; // cada fila es el centroide del cluster
    
    std::vector<int> cantElementosClusters; // cantidad de elementos en cada cluster
    int cantPuntos; // total de puntos agregados


    // not allowed
    kMeans();
    
    void limpiarNuevosCentroides();
    
    void Inicializacion();

public:
    

    kMeans(int n_clusters);
  
    ~kMeans();
  
    // igual que arriba, pero para una matriz
    void asignarMatriz(const TipoMatriz& matriz);    
    
    // calcular cual centroide es el mas cercano a un punto
    int calcularPuntoMasCercano(const TipoVectorFila& unPunto) const;

    TipoMatriz getCentroides() const;
    
    void imprimirPuntosClusters();
    
    void runner();
    
    void runner2();
};

#endif // KMEANS_H
