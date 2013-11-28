#ifndef KMEANS_H
#define KMEANS_H

#include <limits>
#include <vector>
#include <cmath>
#include <iostream>
#include <eigen3/Eigen/Core>

/**
* Matrix< tipo que guarda, cant filas, cant cols >
* 
* */

class kMeans {
private:
    
    unsigned cantElementos; //Dimension (de las palabras por ejemplo)
    int cantClusters; // cantidad de clusters que se quieren armar
    Eigen::MatrixXf centroides; // cada fila es el centroide del cluster
    Eigen::MatrixXf nuevosCentroides; // cada fila es el centroide del cluster
    
    std::vector<unsigned> cantElementosClusters; // cantidad de elementos en cada cluster
    int cantPuntos; // total de puntos agregados
    int cantIteraciones;
    // not allowed
    kMeans();

public:
    kMeans(int n_clusters);
  
    ~kMeans();
  
    // agregar un elemento y actualiza centroide
    void agregarUnPunto(const Eigen::RowVectorXf& unPunto);

    // igual que arriba, pero para una matriz
    void agregarPuntos(const Eigen::MatrixXf& puntos);    
    
    // calcular cual centroide es el mas cercano a un punto
    int calcularPuntoMasCercano(const Eigen::RowVectorXf& unPunto) const;

    Eigen::MatrixXf getCentroides() const;
    
    void runner();
    
    void imprimirPuntosClusters();
    
    void limpiarNuevosCentroides();
};

#endif // KMEANS_H
