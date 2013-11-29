#include "kMeans.h"
#include <iostream>

/**
* Matrix< tipo que guarda, cant filas, cant cols >
* 
* */

kMeans::kMeans(int n_clusters):
    cantClusters(n_clusters),
    cantElementosClusters(n_clusters, 0),
    cantPuntos(0) {
    cantIteraciones = 25;
    primera = false;
    };


kMeans::kMeans() {};


kMeans::~kMeans() {};


void kMeans::agregarUnPunto(const Eigen::RowVectorXf& unPunto) {
// Si es el primer elemento, se inicializa centroides
    if (cantPuntos == 0) {
        centroides = Eigen::MatrixXf(cantClusters, cantElementos);
        centroides.setRandom();
    }
    // Si hay menos elementos que clusters, asignar un punto al primer
    // cluster vacio (supuestamente hace que corverja mas rapido que si es random)
    if (cantPuntos < cantClusters) {
        centroides.row(cantPuntos) = unPunto;
    }
    
    int masCerano = calcularPuntoMasCercano(unPunto);
    // incrementar cantidad de elementos
    cantElementosClusters[masCerano]++;
    cantPuntos++;
    // re calcular promedio
    centroides.row(masCerano) += 
      (unPunto - centroides.row(masCerano))/ cantElementosClusters[masCerano];
};

void kMeans::imprimirPuntosClusters(){
    for (int i = 0; i<cantClusters; i++)
        std::cout << cantElementosClusters[i] << std::endl;
    }


void kMeans::agregarPuntos(const Eigen::MatrixXf& puntos) {
    matrizInicial = puntos;
    cantElementos = static_cast<int>(matrizInicial.cols());
    
    int cantPuntosNuevos = static_cast<int>(matrizInicial.rows());
    for (int r = 0; r < cantPuntosNuevos; r++) {
        agregarUnPunto(matrizInicial.row(r));
    }
};


int kMeans::calcularPuntoMasCercano(const Eigen::RowVectorXf& unPunto) const {
// calcula la distancia desde un punto a cada promedio
    Eigen::VectorXf normas((centroides - unPunto.replicate(cantClusters, 1)).rowwise().norm());
    // encontrar el indice del centroide mas cercano
    int masCercano = std::numeric_limits<int>::max();
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

void kMeans::limpiarNuevosCentroides(){
    nuevosCentroides = Eigen::MatrixXf::Zero(cantClusters, cantElementos);
    nuevosCentroides.setRandom();
}

/**
* The run method essentially creates new centroids. Firstly, it resets the value of n as this counts
* how many data objects belong to a centroid - it needs to be 0 as the centroids modify themelf at
* every iteration. The closestCentroid variable holds the index of the closest centroid of certain data,
* it does this using Euclidean Distance. It sums up all datum sharing the same closest centroid in order
* to get the mean of all the data belonging to that centroid.
* It calls the terminator method to check for stability between old and new centroids, stability will
* cause the run method to terminate.
* It then calls the getClassification method to assign centroids to a classication value, then print
* output to file.
*/
void kMeans::runner(){

    bool bandera = false;
for (int iter=0; iter<6; iter++){
    //while (bandera == false) {

        bool resultado = true;
        
        this->limpiarNuevosCentroides();
        
        for (int i = 0; i < cantClusters; i++) {
            cantElementosClusters[i] = 0; //resetear valor
        }


        for (int i = 0; i < cantClusters; i++) { //ALL data objects
            Eigen::RowVectorXf unPunto = matrizInicial.row(i);
            int cluster = calcularPuntoMasCercano(unPunto); //gets closest centroid for ALL distances

            for (int j = 0; j < cantElementos; j++) {
                nuevosCentroides(cluster,j) += (unPunto(j) - centroides(cluster,j)); //sums all datum belonging to certain centroid
                
            }
            cantElementosClusters[cluster]++; //counts the no. of members of datum that belong to centroid group
        }

        //finds the average between all datum belonging to certain centroid
        for (int i = 0; i < cantClusters; i++) {
            for (int j = 0; j < cantElementos; j++) {
                nuevosCentroides(i,j)  = nuevosCentroides(i,j) / cantElementosClusters[i];
            }
        }

        //checks if newCentroid values are same as Centroid
        //If they are then there are no more move groups and no more iterations are needed
        /*for (int i = 0; i < cantClusters; i++) {
            for (int j = 0; j < cantElementos; j++) {
                if(resultado == true) {
                    if(std::abs(nuevosCentroides(i,j) - centroides(i,j)) < 0.0001) { //checks for stability
                        bandera = true;
                        resultado = true;
                    } else {
                        bandera = false;
                        resultado = false;
                    }
                }
            }
        }*/
    std::cout << nuevosCentroides.traspose() << std::endl;
    std::cout << std::endl;
        //centroides = nuevosCentroides;
    }
}
