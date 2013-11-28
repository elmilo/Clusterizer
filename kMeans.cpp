#include "kMeans.h"

/**
* Matrix< tipo que guarda, cant filas, cant cols >
* 
* */

kMeans::kMeans(int n_clusters):
    cantClusters(n_clusters),
    puntosClusters(n_clusters, 0),
    cantPuntos(0) {
    };


kMeans::kMeans() {};


kMeans::~kMeans() {};


void kMeans::agregarUnPunto(const Eigen::RowVectorXf& unPunto) {
// Si es el primer punto, se inicializa centroides
    if (cantPuntos == 0) {
        centroides = Eigen::MatrixXf(cantClusters, unPunto.cols());
        centroides.setRandom();
    }
    // Si hay menos puntos que clusters, asignar un punto al primer
    // cluster vacio (supuestamente hace que corverja mas rapido que si es random)
    if (cantPuntos < cantClusters) {
        centroides.row(cantPuntos) = unPunto;
    }
    // calcular el indice mas cercano
    int masCerano = calcularPuntoMasCercano(unPunto);
    // incrementar cantidad de unPunto
    puntosClusters[masCerano] += 1.f;
    cantPuntos++;
    // re calcular promedio
    centroides.row(masCerano) += 
      (unPunto - centroides.row(masCerano));// / puntosClusters[masCerano];
};


void kMeans::agregarPuntos(const Eigen::MatrixXf& puntos) {
    int cantPuntosNuevos = static_cast<int>(puntos.rows());
    for (int r = 0; r < cantPuntosNuevos; r++) {
        agregarUnPunto(puntos.row(r));
    }
};


int kMeans::calcularPuntoMasCercano(const Eigen::RowVectorXf& unPunto) const {
// calcula la distancia desde un punto a cada promedio
    Eigen::VectorXf normas((centroides - unPunto.replicate(cantClusters, 1)).rowwise().norm());
    // encontrar el indice del promedio mas cercano
    int masCercano = -1;
    float min_dist = std::numeric_limits<float>::max(); //le doy un valor muy alto
    for (int m = 0; m < cantClusters; m++) {
        if (normas(m) < min_dist) {
            min_dist = normas(m);
            masCercano = m;
        }
    }
return masCercano;
}


Eigen::MatrixXf kMeans::getCentroides() const { 
        return centroides; 
    };

