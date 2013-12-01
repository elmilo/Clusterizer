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
    
    std::vector<int> cantElementosClusters; // cantidad de elementos en cada cluster
    int cantPuntos; // total de puntos agregados
    
    std::vector< std::vector<int> > clusters; //Para guardar los elementos clusterizados
    
    TipoGuardado Jaccard(TipoVectorFila vecA, TipoVectorFila vecB) const;
    TipoGuardado CalcularSimilaridad(TipoVectorFila vecA, TipoVectorFila vecB) const;

    // not allowed
    kMeans();
    
    void LimpiarMatriz(TipoMatriz& unaMatriz, int filas, int columnas);
    
    void Inicializacion();
    
    void Randomize(TipoMatriz& matrizCentroides);

    void Normalizar(TipoMatriz& unaMatriz, int tamanio);
public:
    

    kMeans(const TipoMatriz& matriz, int n_clusters);
  
    ~kMeans();
  
    // calcular cual centroide es el mas cercano a un punto
    int calcularPuntoMasCercano(const TipoVectorFila& unPunto) const;
    
    void runner();
    
    void runner2();
    
    void mostrarDatos();
    
    void actualizarCentroides();
};

#endif // KMEANS_H
