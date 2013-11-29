#ifndef KMEANS_H
#define KMEANS_H

#include <limits>
#include <vector>
#include <cmath> 
#include <eigen3/Eigen/Core>

/**
* Matrix< tipo que guarda, cant filas, cant cols >
* 
* */

class kMeans {
private:
    
    int cantElementos; //Dimension (de las palabras por ejemplo)
    int cantClusters; // cantidad de clusters que se quieren armar
    int cantVectores; // cantidad de elementos clusterizables (documentos por ejemplo)

    Eigen::MatrixXf matrizInicial; // cada fila es el centroide del cluster
    Eigen::MatrixXf centroides; // cada fila es el centroide del cluster
    Eigen::MatrixXf nuevosCentroides; // cada fila es el centroide del cluster
    
    std::vector<int> cantElementosClusters; // cantidad de elementos en cada cluster
    int cantPuntos; // total de puntos agregados


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
    
    void imprimirPuntosClusters();
    
    void limpiarNuevosCentroides();
    
    void runner();
    
    void runner2();
};

#endif // KMEANS_H
