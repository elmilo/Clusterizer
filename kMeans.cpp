#include "kMeans.h"


/**
* Matrix< tipo que guarda, cant filas, cant cols >
* 
* */


kMeans::kMeans(const TipoMatriz& matriz, int n_clusters):
    cantClusters(n_clusters),
    cantElementosClusters(n_clusters, 0),
    cantPuntos(0){
        TOLERANCIA = 1e-10;
        this->matrizInicial = matriz;
        cantElementos = static_cast<unsigned>(matriz.cols());
        cantVectores = static_cast<int>(matriz.rows());
    };

kMeans::kMeans() {};

kMeans::~kMeans() {};

void kMeans::Randomize(TipoMatriz& matrizCentroides){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, cantVectores-1);
    
    for (int i = 0; i<cantClusters; i++){
        int unaPosicion = dis(gen);
        centroides.row(i) = matrizInicial.row(unaPosicion);
        }
}

void kMeans::Inicializacion(){
    this->centroides = TipoMatriz(cantClusters, cantElementos);
    this->nuevosCentroides = TipoMatriz(cantClusters, cantElementos);
    this->Randomize(this->centroides);
}


int kMeans::calcularPuntoMasCercano(const TipoVectorFila& unPunto) const {
    TipoVectorColumna normas((centroides - unPunto.replicate(cantClusters, 1)).rowwise().norm());
   
    //le doy un valor muy alto
    TipoGuardado min_dist = std::numeric_limits<TipoGuardado>::max(); 
    
    int masCercano = -1;
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


TipoMatriz kMeans::getCentroides() const { 
        return centroides; 
    };


void kMeans::limpiarNuevosCentroides(){
    //nuevosCentroides = TipoMatriz::Zero(cantClusters, cantElementos);
    this->Randomize(nuevosCentroides);
}


void kMeans::Clasificar(){
    int alCluster = -1;

    for (int j = 0; j < cantVectores; j++){
        TipoVectorFila otroPunto = matrizInicial.row(j);
        alCluster = calcularPuntoMasCercano(otroPunto);
        clasificados[j] = alCluster;
    }
}


void kMeans::runner(){

this->Inicializacion();

bool bandera = false;
unsigned iter = 0;
while (bandera == false) {
//for (int iterac=0; iterac<150; iterac++){
    iter++;
    bool result = true;
    this->limpiarNuevosCentroides();

    for (int i = 0; i < cantClusters; i++) {
        cantElementosClusters[i] = 0; //resetear valores
    }
  
    for (unsigned i = 0; i < cantVectores; i++) { 
        TipoVectorFila unPunto = matrizInicial.row(i);
        unsigned alCluster = calcularPuntoMasCercano(unPunto);

       for (int j = 0; j < cantVectores; j++){
           TipoVectorFila otroPunto = matrizInicial.row(j);
           if (alCluster == calcularPuntoMasCercano(otroPunto)){
               //Suma las distancias de todos los vectores que pertenezcan a ese cluster
                nuevosCentroides.row(alCluster) += (otroPunto - nuevosCentroides.row(alCluster));
            }
        }
        cantElementosClusters[alCluster]++;
    }
    
    //centroides.row(masCerano) += (unPunto - centroides.row(masCerano))/ cantElementosClusters[masCerano];
      
    //Calcula el promedio de todas las distancias
    //Aca falla cuando divide por 0, se anula un centroide
    for (unsigned i = 0; i < cantClusters; i++)       
        nuevosCentroides.row(i) = nuevosCentroides.row(i) / cantElementosClusters[i];


    //banderas marca si los valores nuevos y viejos de centroides son iguales
    //Por lo tanto no se necesitan mas iteraciones
    for (unsigned i = 0; i < cantClusters; i++) {
        for (unsigned j = 0; j < cantElementos; j++) {
            if(result == true) {
                if( abs(nuevosCentroides(i,j) - centroides (i,j)) < TOLERANCIA){
                    bandera = true;
                    result = true;
                } else {
                    bandera = false;
                    result = false;
                }
            }
        }
    }
    
    /*std::cout<< "Nuevos centroides: " << std::endl;
    std::cout << nuevosCentroides.format(FormatoImpresion) << std::endl;
    
    std::cout << std::endl;*/
    centroides = nuevosCentroides;
   }
   std::cout << "adentro del kmeans: "<< iter << " veces" <<std::endl;
}

