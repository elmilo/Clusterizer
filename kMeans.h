#ifndef KMEANS_H
#define KMEANS_H

#include <limits>
#include <vector>
#include <cmath> 
#include <iostream>
#include <random>

#include "TiposGlobales.h"

/**
* Matrix< tipo que guarda, cant filas, cant cols >
* 
* */

class kMeans {
private:
    
    TipoGuardado TOLERANCIA;
    
    int cantElementos; //Dimension (de las palabras por ejemplo)
    int cantClusters; // cantidad de clusters que se quieren armar
    int cantVectores; // cantidad de elementos clusterizables (documentos por ejemplo)

    TipoMatriz matrizInicial; // guarda la matriz de datos
    TipoMatriz centroides; // cada fila es el centroide del cluster
    TipoMatriz nuevosCentroides; // idem
    TipoMatriz dataOrdenada; // guarda a que cluster pertenece cada elemento clusterizable
    
    std::vector<int> cantElementosClusters; // cantidad de elementos en cada cluster
    std::vector<int> clasificados; // [elementos clusterizables] -> el cluster a donde pertenecen
    int cantPuntos; // total de puntos agregados


    // not allowed
    kMeans();
    
    void limpiarNuevosCentroides();
    
    void Inicializacion();
    
    void Clasificar();//No funciona
    
    void Randomize(TipoMatriz& matrizCentroides);

public:
    

    kMeans(const TipoMatriz& matriz, int n_clusters);
  
    ~kMeans();
  
    // calcular cual centroide es el mas cercano a un punto
    int calcularPuntoMasCercano(const TipoVectorFila& unPunto) const;

    TipoMatriz getCentroides() const;
    
    void imprimirPuntosClusters();
    
    void runner();
};

#endif // KMEANS_H
