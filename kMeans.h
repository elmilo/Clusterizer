#ifndef KMEANS_H
#define KMEANS_H

#include <limits>
#include <vector>
#include <eigen3/Eigen/Core>

/**
* Matrix< tipo que guarda, cant filas, cant cols >
* 
* */

class kMeans {
private:
    int cantClusters; // cantidad de clusters
    Eigen::MatrixXf promedios; // cada fila es el centro de un cluster
    std::vector<float> puntosClusters; // cantidad de puntos en cada cluster
    int cantPuntos; // total de puntos agregados
  
    // not allowed
    kMeans();

public:
    kMeans(int n_clusters);
  
    ~kMeans();
  
    // agregar un punto y actualiza promedios
    void agregarUnPunto(const Eigen::RowVectorXf& unPunto);

    // igual que arriba, pero para toda una matriz
    void agregarPuntos(const Eigen::MatrixXf& puntos);    
    
    // calcular cual promedios es el mas cercano a un punto
    int calcularPuntoMasCercano(const Eigen::RowVectorXf& unPunto) const;

    Eigen::MatrixXf getPromedios() const;
};

#endif // KMEANS_H
