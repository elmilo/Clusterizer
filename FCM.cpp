#include "FCM.h"

FCM::FCM(const TipoMatriz& matriz, int n_clusters):
    cantClusters(n_clusters){
        TOLERANCIA = 1e-10;
        fuzzyness = 1.5;
        
        this->matrizInicial = matriz;
        
        cantElementos = static_cast<unsigned>(matriz.cols());
        cantVectores = static_cast<int>(matriz.rows());
        
        //Use the estimated means to find the degree of membership u(j,i) of xj in Cluster i;
        this->LimpiarMatriz(this->gradoDeMembresia, cantVectores, cantClusters);
        
        gradoDeMembresia.setRandom();
        clusters.resize(cantClusters);
        
        //Normalizacion de la matriz inicial (variante)
        this->Normalizar(this->matrizInicial, cantVectores);
    };

FCM::FCM() {};

FCM::~FCM() {};

void FCM::Randomize(TipoMatriz& matrizCentroides){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, cantVectores-1);
    for (int i = 0; i<cantClusters; i++){
        int unaPosicion = dis(gen);
        centroides.row(i) = matrizInicial.row(unaPosicion);
        }
}

void FCM::Inicializacion(){
    this->LimpiarMatriz(this->centroides,cantClusters, cantElementos);
    this->LimpiarMatriz(this->nuevosCentroides,cantClusters, cantElementos);
    this->Randomize(this->centroides);
}


int FCM::calcularPuntoMasCercano(const TipoVectorFila& unPunto) const {
    TipoVectorColumna normas;
    normas.resize(cantClusters);

    for (int i=0; i<cantClusters; i++){
        TipoVectorFila unCentroide = this->centroides.row(i);
        normas(i) = CalcularSimilaridad(unPunto, unCentroide);
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

//Coseno
TipoGuardado FCM::CalcularSimilaridad(TipoVectorFila vecA, TipoVectorFila vecB) const{
    TipoGuardado producto = vecA.dot(vecB);
    
    TipoGuardado normaA = vecA.norm();
    TipoGuardado normaB = vecB.norm();
    
    TipoGuardado resultado = producto / (normaA * normaB);
    return resultado;
}


void FCM::LimpiarMatriz(TipoMatriz& unaMatriz, int filas, int columnas){
    unaMatriz = TipoMatriz::Zero(filas, columnas);
}


void FCM::runner2() {
    
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
        
        //Estrategia para clusters vacios: reiniciar todos centroides con vectores random
        bool clusterVacios = false;
        /*for (int i = 0; i < cantVectores; i++)
            if (clusters[i].size()==0){
                this->Randomize(this->centroides);
                clusterVacios = true;
            }*/
        
        if (!clusterVacios){
            nuevosCentroides = centroides;
            this->actualizarCentroides();
            suma = 0;
            for (int i = 0; i < cantClusters; i++)
                for (int j = 0; j < cantElementos; j++)
                    suma += nuevosCentroides(i,j) - centroides(i,j);
            if (abs(suma) < TOLERANCIA) //Condicion de corte
                bandera = false;
        }
    }
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
void FCM::actualizarCentroides() {
    for (int i = 0; i < cantClusters; i++) {
        TipoVectorFila sumador;
        sumador.resize(cantElementos);
        sumador.setZero();
        /* Paper:
        * Efficient Online Spherical K-means Clustering (Shi Zhong)
        * Se suman los centroides y se divide por su norma
        * Parece que queda normalizado (y no vale la pena normalizar)
        * */
        for (unsigned j = 0; j < clusters[i].size(); j++){
            sumador += centroides.row(i); //<-paper "a modified..."
            //sumador += matrizInicial.row(clusters[i][j]);
            }
        this->centroides.row(i) = sumador / sumador.norm();
        //this->centroides.row(i) = sumador / (clusters[i].size());
    }
    //Creo que no es necesario hacerlo de nuevo
    //this->Normalizar(this->centroides,cantClusters);
}


std::vector<int> FCM::mostrarUnDato(int i) const{
    return clusters[i];
}


/*
 * Experimental: normalizacion
 * */
void FCM::Normalizar(TipoMatriz& unaMatriz, int tamanio){
    for (int i = 0; i< tamanio; i++){
        TipoVectorFila vector = unaMatriz.row(i);
        vector.normalize();
        unaMatriz.row(i) = vector;
        }
}


void FCM::runner() {

    TipoMatriz temporal;
    this->LimpiarMatriz(temporal, cantVectores, cantClusters);
    bool bandera = true;
    TipoGuardado suma = 0;

    while (!bandera){
        for (int i = 0; i < cantVectores; i++)
            for (int j = 0; j < cantClusters; j++){
                TipoVectorFila unVector;
                unVector = matrizInicial.row(i) - centroides.row(j);
                temporal(i,j) = exp(- (unVector.squaredNorm()));
                }
        
        for (int i = 0; i < cantVectores; i++){
            TipoGuardado suma = 0
            for (int j = 0; j < cantClusters; j++)
                suma += temporal(i,j);
            gradoDeMembresia.row(i) = temporal.row(i)/suma;
            }
            
        for (int i = 0; i < cantClusters; i++)
            for (int j = 0; j < cantVectores; j++){
            TipoVectorFila unVector = gradoDeMembresia.row(i);
            TipoGuardado norma22 = unVector.squaredNorm(); //Cuadrado de la norma
            centroides.row(i) = norma22 * matrizInicial.row(j);
            centroides.row(i) /= norma22;
            }

        nuevosCentroides = centroides;
        this->actualizarCentroides();

        suma = 0;
        for (int i = 0; i < cantClusters; i++)
            for (int j = 0; j < cantElementos; j++)
                suma += nuevosCentroides(i,j) - centroides(i,j);

        if (abs(suma) < TOLERANCIA) //Condicion de corte
                bandera = false;
    }
    std::cout << gradoDeMembresia << std::endl;
}
