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
    
    int cantElementos; //Dimension (cantidad de palabras por ejemplo)
    int cantClusters; // cantidad de clusters que se quieren armar
    int cantVectores; // cantidad de elementos clusterizables (documentos por ejemplo)

    TipoMatriz matrizInicial; // guarda la matriz de datos
    
    TipoMatriz centroides; // cada fila es el centroide del cluster
    TipoMatriz nuevosCentroides; // idem
    
    TipoVectorClusters clusters; //Para guardar los elementos clusterizados, y su cantidad
    
    /*typedef struct Registro {
        int kpropuesto = 0;
        int cantCeros = 0; //cant de clusters con cero elementos
    TipoVectorClusters vector;} Registro;
    
    std::vector< Registro > propuestos; //elementos propuestos
    */
    //Distancia Coseno
    TipoGuardado CalcularSimilaridad(TipoVectorFila vecA, TipoVectorFila vecB) const;

    //Inicializar con ceros una matriz
    void LimpiarMatriz(TipoMatriz& unaMatriz, int filas, int columnas);
    
    //Asignar valores random a la matriz de centroides
    void Randomize(TipoMatriz& matrizCentroides);

    //Normalizar las filas de una matriz
    void Normalizar(TipoMatriz& unaMatriz, int tamanio);
    
    //Procedimiento apra recalcular centroides, aca se puede utilizar otros algoritmos
    void actualizarCentroides();
    
    kMeans(); //No se puede
    
    void Inicializacion();
    
    int calcularCantidadClustersVacios();
    
    int buscarKoptimo(int maximosClusters);
    
public:

    kMeans(const TipoMatriz& matriz, int n_clusters);
    
    kMeans(const TipoMatriz& matriz);
  
    ~kMeans();
  
    // calcular cual centroide es el mas cercano a un punto
    int calcularPuntoMasCercano(const TipoVectorFila& unPunto) const;
    
    std::vector<int> mostrarUnDato(int i) const;
    
    int proponerK(int maximosClusters = 32);
        
    void runner();
};

#endif // KMEANS_H
