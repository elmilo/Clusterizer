#ifndef KMEANS_H
#define KMEANS_H

#include <limits>
#include <vector>
#include <cmath> 
#include <iostream>

#include "TiposGlobales.h"

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

public:
    

    kMeans(int n_clusters);
  
    ~kMeans();
  
    // agregar un elemento y actualiza centroide
    void agregarUnPunto(const TipoVectorFila& unPunto);

    // igual que arriba, pero para una matriz
    void agregarPuntos(const TipoMatriz& puntos);    
    
    // calcular cual centroide es el mas cercano a un punto
    int calcularPuntoMasCercano(const TipoVectorFila& unPunto) const;

    TipoMatriz getCentroides() const;
    
    void imprimirPuntosClusters();
    
    void limpiarNuevosCentroides();
    
    void runner();
    
    void runner2();
};

#endif // KMEANS_H
