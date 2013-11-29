#include "kMeans.h"
#include <iostream>

/**
* Matrix< tipo que guarda, cant filas, cant cols >
* 
* */

kMeans::kMeans(int n_clusters):
    cantClusters(n_clusters),
    cantElementosClusters(n_clusters, 0),
    cantPuntos(0){
    };


kMeans::kMeans() {};


kMeans::~kMeans() {};


void kMeans::agregarPuntos(const Eigen::MatrixXf& puntos) {
	this->matrizInicial = puntos;
    cantElementos = static_cast<unsigned>(matrizInicial.cols());
    cantVectores = static_cast<int>(puntos.rows());
    
    int cantPuntosNuevos = static_cast<int>(matrizInicial.rows());
    for (int r = 0; r < cantPuntosNuevos; r++) {
        agregarUnPunto(matrizInicial.row(r));
    }
}

/*void kMeans::agregarPuntos(const Eigen::MatrixXf& puntos) {

    cantElementos = static_cast<int>(puntos.cols());
    cantvectores = static_cast<int>(puntos.rows());
    
    matrizInicial = Eigen::MatrixXf(cantvectores, cantElementos);
    matrizInicial = puntos;
    
    for (int r = 0; r < cantvectores; r++) {
        agregarUnPunto(puntos.row(r));
    }
}*/


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


int kMeans::calcularPuntoMasCercano(const Eigen::RowVectorXf& unPunto) const {
// calcula la distancia desde un punto a cada promedio
    Eigen::VectorXf normas((centroides - unPunto.replicate(cantClusters, 1)).rowwise().norm());
    // encontrar el indice del centroide mas cercano
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


void kMeans::imprimirPuntosClusters(){
    for (int i = 0; i<cantClusters; i++)
        std::cout << cantElementosClusters[i] << std::endl;
    }
    

Eigen::MatrixXf kMeans::getCentroides() const { 
        return centroides; 
    };

void kMeans::limpiarNuevosCentroides(){
    nuevosCentroides = Eigen::MatrixXf::Zero(cantClusters, cantElementos);
    //nuevosCentroides.setRandom();
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
for (int iter=0; iter<100; iter++){
    //while (bandera == false) {

        bool resultado = true;
        
        this->limpiarNuevosCentroides();
        
        for (int i = 0; i < cantClusters; i++) {
            cantElementosClusters[i] = 0; //resetear valor
        }


        for (int r1 = 0; r1 < cantVectores; r1++) { //ALL data objects
            Eigen::RowVectorXf unPunto = matrizInicial.row(r1);
            /*std::cout << "\n\n En runner: \n" << std::endl;
            std::cout << "\n matrizInicialrow(i): "<< i << std::endl;
            std::cout << matrizInicial.row(i) << std::endl;
            
            for (int k = 0; k<cantClusters; k++)
                std::cout << "k= "<< k << " tiene: " <<cantElementosClusters[k] << std::endl;
            
            std::cout << "\n nuevos centroides: " << std::endl;
            std::cout << nuevosCentroides << std::endl;
            std::cout << "\n" << std::endl;*/
            
            int alCluster = calcularPuntoMasCercano(unPunto); //gets closest centroid for ALL distances
            cantElementosClusters[alCluster]++; //counts the no. of members of datum that belong to centroid group
           //nuevosCentroides.row(alCluster) += (unPunto - nuevosCentroides.row(cluster));
            
            for (int j = 0; j < cantElementos; j++) {
                nuevosCentroides(alCluster,j) += matrizInicial(r1,j); //sums all datum belonging to certain centroid
                
            }
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
    std::cout << nuevosCentroides.transpose() << std::endl;
    std::cout << std::endl;
    centroides = nuevosCentroides;
    }
}


void kMeans::runner2(){

bool bandera = false;

//while (bandera == false) {
for (int iter=0; iter<200; iter++){
    bool result = true;
    this->limpiarNuevosCentroides();
    for (int cluster = 0; cluster < cantClusters; cluster++) {
        cantElementosClusters[cluster] = 0; //resetear valores
    }
  
    for (unsigned i = 0; i < cantVectores; i++) { //cantClusters
        Eigen::RowVectorXf unPunto = matrizInicial.row(i);
        unsigned alCluster = calcularPuntoMasCercano(unPunto); //gets closest centroid for ALL distances

        cantElementosClusters[alCluster]++;
       // nuevosCentroides.row(alCluster) += (unPunto - nuevosCentroides.row(alCluster));//////posible mejora
        for (int j = 0; j < cantElementos; j++) {
                nuevosCentroides(alCluster,j) += matrizInicial(i,j); //sums all datum belonging to certain centroid
                
            }
    }

    //finds the average between all datum belonging to certain centroid
    for (unsigned i = 0; i < cantClusters; i++) {
 //       for(int j = 0; j < cantElementos; j++) {
     //       nuevosCentroides(i,j) = nuevosCentroides[i][j] / n(i);
            nuevosCentroides.row(i) = nuevosCentroides.row(i) / cantElementosClusters[i];
   //     }
    }
    //;


    //banderas if newCentroid values are same as Centroid
    //If they are then there are no more move groups and no more iterations are needed
    for (unsigned i = 0; i < cantClusters; i++) {
        for (unsigned j = 0; j < cantElementos; j++) {
            if(result == true) {
                if( abs(nuevosCentroides(i,j) - centroides (i,j)) < 1e-15){
                //newCentroids[i][j] == centroids[i][j])
                    bandera = true;
                    result = true;
                } else {
                    bandera = false;
                    result = false;
                }
            }
        }
    }

    centroides = nuevosCentroides;
    //getClassification(classifiedData, centroids);
    }
}
