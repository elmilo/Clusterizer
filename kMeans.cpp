#include "kMeans.h"


/**
* Matrix< tipo que guarda, cant filas, cant cols >
* 
* */


kMeans::kMeans(const TipoMatriz& matriz, int n_clusters):
    cantClusters(n_clusters),
    cantElementosClusters(n_clusters, 0),
    cantPuntos(0){
        TOLERANCIA = 1e-30;
        this->matrizInicial = matriz;
        
        cantElementos = static_cast<unsigned>(matriz.cols());
        cantVectores = static_cast<int>(matriz.rows());
        
        clusters.resize(cantClusters);
        //Normalizacion de la matriz (variante)
        this->Normalizar(this->matrizInicial, cantVectores);
    };

kMeans::kMeans() {};

kMeans::~kMeans() {};

void kMeans::Randomize(TipoMatriz& matrizCentroides){
    //centroides.setRandom();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, cantVectores-1);
    
    for (int i = 0; i<cantClusters; i++){
        int unaPosicion = dis(gen);
        centroides.row(i) = matrizInicial.row(unaPosicion);
        }
}

void kMeans::Inicializacion(){
    this->LimpiarMatriz(this->centroides,cantClusters, cantElementos);
    this->LimpiarMatriz(this->nuevosCentroides,cantClusters, cantElementos);
    this->Randomize(this->centroides);
}


//Euclidea
/*
 * NO ES LA MEJOR PARA DOCUMENTOS
 * */
/*int kMeans::calcularPuntoMasCercano(const TipoVectorFila& unPunto) const {
    TipoVectorColumna normas((centroides - unPunto.replicate(cantClusters, 1)).rowwise().norm());

    //le doy un valor muy alto
    TipoGuardado min_dist = std::numeric_limits<TipoGuardado>::max(); 
    
    int masCercano = -1;//std::numeric_limits<int>::min();
    for (int m = 0; m < cantClusters; m++) {
        if (normas(m) < min_dist) {
            min_dist = normas(m);
            masCercano = m;
        }
    }
    
    return masCercano;
}*/


int kMeans::calcularPuntoMasCercano(const TipoVectorFila& unPunto) const {
    TipoVectorColumna normas;
    normas.resize(cantClusters);

    for (int i=0; i<cantClusters; i++){
        TipoVectorFila unCentroide = this->centroides.row(i);
        normas(i) = CalcularSimilaridad(unPunto, unCentroide);
        //normas(i) = Jaccard(unPunto, unCentroide);
        }
    //le doy un valor imposible para el coseno
    TipoGuardado maxValue = -2.0; 
    int masCercano = -1;
    for (int m = 0; m < cantClusters; m++) {
        if (normas(m) > maxValue) {
            maxValue = normas(m);
            masCercano = m;
        }
    }
    return masCercano;
}

//Jaccard: parecido al coseno
TipoGuardado kMeans::Jaccard(TipoVectorFila vecA, TipoVectorFila vecB) const{
    TipoGuardado producto = vecA.dot(vecB);
    
    TipoGuardado normaA = vecA.norm();
    TipoGuardado normaB = vecB.norm();
    
    TipoGuardado resultado = producto / (normaA * normaB - producto);
    return resultado;
}

//Coseno
TipoGuardado kMeans::CalcularSimilaridad(TipoVectorFila vecA, TipoVectorFila vecB) const{
    TipoGuardado producto = vecA.dot(vecB);
    
    TipoGuardado normaA = vecA.norm();
    TipoGuardado normaB = vecB.norm();
    
    TipoGuardado resultado = producto / (normaA * normaB);
    return resultado;
}


void kMeans::LimpiarMatriz(TipoMatriz& unaMatriz, int filas, int columnas){
    unaMatriz = TipoMatriz::Zero(filas, columnas);
}


void kMeans::runner(){

this->Inicializacion();

bool bandera = false;
unsigned iter = 0;
//for (int kj= 0; kj <10; kj++){
while (bandera == false) {
    iter++;
    bool result = true;
    
    this->LimpiarMatriz(nuevosCentroides, cantClusters, cantElementos);

    for (int i = 0; i < cantClusters; i++) {
        cantElementosClusters[i] = 0; //resetear valores
    }
  
    for (int i = 0; i < cantVectores; i++){
        TipoVectorFila unPunto = matrizInicial.row(i);
        int alCluster = calcularPuntoMasCercano(unPunto);

        for (int j = 0; j < cantVectores; j++){
           TipoVectorFila otroPunto = matrizInicial.row(j);
           //Calcula las distancias de todos los puntos (nuevamente)
           //Para sumar los puntos que correspondan
           if (alCluster == calcularPuntoMasCercano(otroPunto)){
                //Suma las distancias de todos los vectores que pertenezcan a ese cluster
                //Este metodo es k-medians
                ////nuevosCentroides.row(alCluster) += (otroPunto - nuevosCentroides.row(alCluster));
                
                //Suma los valores de todos los vectores que pertenezcan a ese cluster
                //Este metodo es k-means
                nuevosCentroides.row(alCluster) += (otroPunto);
            }
        }
        cantElementosClusters[alCluster]++;
    }

    //Calcula el promedio de todas las distancias
    //Aca falla cuando divide por 0, se anula un centroide
    for (int i = 0; i < cantClusters; i++)       
        nuevosCentroides.row(i) = nuevosCentroides.row(i) / cantElementosClusters[i];


    //banderas marca si los valores nuevos y viejos de centroides son iguales
    //Por lo tanto no se necesitan mas iteraciones
    for (int i = 0; i < cantClusters; i++) {
        for (int j = 0; j < cantElementos; j++) {
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
   //std::cout << "adentro del kmeans: "<< iter << " veces" <<std::endl;
}


    // store cluster points
    //std::vector< std::vector<int> > clusters;
    //k= cant de clusterss
    //clusters.resize(k);
    
void kMeans::runner2() {
    
    this->Inicializacion();
    this->LimpiarMatriz(nuevosCentroides, cantClusters, cantElementos);
    
    bool bandera = true;
    int alCluster = -1;
    TipoGuardado suma = 0;
    int step = 0;
    
    while (bandera) {
        step++;
        
        for (int j = 0; j < cantClusters; j++)
            clusters[j].clear();
        
        for (int i = 0; i < cantVectores; i++){
            TipoVectorFila unPunto = matrizInicial.row(i);
            alCluster = calcularPuntoMasCercano(unPunto);
            clusters[alCluster].push_back(i);
            }

        nuevosCentroides = centroides;
        
        this->actualizarCentroides();

        suma = 0;
        for (int i = 0; i < cantClusters; i++) {
            for (int j = 0; j < cantElementos; j++) {
                suma += nuevosCentroides(i,j) - centroides(i,j);
            }
        }
        if (abs(suma) < TOLERANCIA) //Condicion de corte
            bandera = false;
    }
   //std::cout << "adentro del kmeans: "<< step << " veces" <<std::endl;
   this->mostrarDatos();
}

/*Esto es del paper "A Modified k-means Algorithm to Avoid Empty Clusters"
* Suma uno mas para no dividir por cero, un genio
* Ademas, suma los centroides en cada iteracion
* */
/*suma += matrizInicial(clusters[i][j], d) + centroides(i,d);
    this->centroides(i,d) = suma / (clusters[i].size()+1);*/

/*Esto es el algoritmo comun:*/    
/*suma += matrizInicial(clusters[i][j], d);
    this->centroides(i,d) = suma / (TipoGuardado)clusters[i].size();*/
void kMeans::actualizarCentroides() {
    TipoGuardado suma = 0;
    for (int i = 0; i < cantClusters; i++) {
        TipoVectorFila sumador;
        sumador.resize(cantElementos);
        sumador.setZero();
        /* Paper:
        * Efficient Online Spherical K-means Clustering (Shi Zhong)
        * */
        for (unsigned j = 0; j < clusters[i].size(); j++){
            sumador += matrizInicial.row(clusters[i][j]);
            }
        TipoGuardado norma = sumador.norm();
        this->centroides.row(i) = sumador /norma;
    }
    //Creo que no es necesario hacerlo de nuevo, pero da mejor en los resultados hacerlo
    this->Normalizar(this->centroides,cantClusters);
}


void kMeans::mostrarDatos() {
    std::vector<int>::iterator p;
    for (int i = 0; i < cantClusters; i++) {
        std::cout << "Cluster " << i << ", " << clusters[i].size() <<" elementos"<< std::endl;
        //std::cout << "Elementos: " << std::endl;
        for (p = clusters[i].begin(); p < clusters[i].end(); ++p)
            std::cout << *p << std::endl;
    }
    //std::cout << "****************************************************\n" << std::endl;
}


/*
 * Experimental: normalizacion
 * */
void kMeans::Normalizar(TipoMatriz& unaMatriz, int tamanio){
    for (int i = 0; i< tamanio; i++){
        TipoVectorFila vector = unaMatriz.row(i);
        vector.normalize();
        unaMatriz.row(i) = vector;
        }
}
