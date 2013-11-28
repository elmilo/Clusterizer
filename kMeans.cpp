#include "kMeans.h"


/**
* Matrix< tipo que guarda, cant filas, cant cols >
* 
* */

kMeans::kMeans(int n_clusters):
    cantClusters(n_clusters),
    cantElementosClusters(n_clusters, 0),
    cantPuntos(0) {
    cantIteraciones = 25;
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
    cantElementos = static_cast<unsigned>(puntos.cols());
    
    int cantPuntosNuevos = static_cast<int>(puntos.rows());
    for (int r = 0; r < cantPuntosNuevos; r++) {
        agregarUnPunto(puntos.row(r));
    }
}


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


Eigen::MatrixXf kMeans::getCentroides() const { 
        return centroides; 
    }


void kMeans::limpiarNuevosCentroides(){
    nuevosCentroides = Eigen::MatrixXf::Zero(cantClusters, cantElementos);
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
void kMeans:: runner(){

bool bandera = false;

while (bandera == false) {

    bool result = true;
    this->limpiarNuevosCentroides();
    for (int cluster = 0; cluster < cantClusters; cluster++) {
        cantElementosClusters[cluster] = 0; //resetear valores
    }
  
  

    for (unsigned i = 0; i < cantElementos; i++) { 
        Eigen::RowVectorXf unPunto = centroides.row(i);
        unsigned alCluster = calcularPuntoMasCercano(unPunto); //gets closest centroid for ALL distances

        cantElementosClusters[alCluster]++;
        nuevosCentroides.row(alCluster) += (unPunto - nuevosCentroides.row(alCluster));//////posible mejora
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
                if( abs(nuevosCentroides(i,j) - centroides (i,j)) < 1e-10){
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


/**
* Assigns new centroid arrays with a clasification value of 1 or 0. It looks for target
* (classified) data that are closest to the new centroid being processed and checks to see if the
* classification value for the classifiedData array being processed is a 1 or a 0 then assigns
* that classification value to the centroid array being processed.
*/
/*void kMeans::getClassification(double[][] datum, double[][] centroid) {

    int positive = 0; //represents 1
    int negative = 0; //represents 0

    for (int i = 0; i < centroid.length; i++) {
        for (int j = 0; j < datum.length; j++) {
            if (i == getClosestCentroid(datum[j])) { //if data is closest to current newCentroid
                if (datum[j][6] == 1) { //count positive or negative
                    positive++;
                } else {
                    negative++;
                }
            }

            if (positive > negative) { //use counted values to label new centroid
                centroid[i][6] = 1;
            } else {
                centroid[i][6] = 0;
            }
        }

        positive = 0;
        negative = 0;
    }
}*/

