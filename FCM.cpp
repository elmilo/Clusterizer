#include "FCM.h"

FCM::FCM(const TipoMatriz& matriz, int n_clusters):
    cantClusters(n_clusters){
        TOLERANCIA = 1e-15;
        MSHIP_PARAM = 0.58;
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

kMeans::kMeans(const TipoMatriz& matriz){
        TOLERANCIA = 1e-10;
        MSHIP_PARAM = 0.58;
        this->matrizInicial = matriz;
        
        cantElementos = static_cast<unsigned>(matriz.cols());
        cantVectores = static_cast<int>(matriz.rows());
        
        //Normalizacion de la matriz (variante)
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


void FCM::LimpiarMatriz(TipoMatriz& unaMatriz, int filas, int columnas){
    unaMatriz = TipoMatriz::Zero(filas, columnas);
}


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
            sumador += centroides.row(i); //<-paper 
            }
        this->centroides.row(i) = sumador / sumador.norm();
    }
    //Creo que no es necesario hacerlo de nuevo
    //this->Normalizar(this->centroides,cantClusters);
}


std::vector<int> FCM::mostrarUnDato(int i) const{
    return clusters[i];
}

//Coseno
TipoGuardado FCM::CalcularSimilaridad(TipoVectorFila vecA, TipoVectorFila vecB) const{
    TipoGuardado producto = vecA.dot(vecB);
    
    TipoGuardado normaA = vecA.norm();
    TipoGuardado normaB = vecB.norm();
    
    TipoGuardado resultado = producto / (normaA * normaB);
    return resultado;
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

void FCM::llenarMembresias() {
    TipoVectorFila unCentroide;
    TipoVectorFila unPunto;
    for (int i = 0; i<cantClusters; i++)
        for (int j = 0; j<cantVectores; j++){
            TipoVectorFila unCentroide = this->centroides.row(i);
            TipoVectorFila unPunto = this->matrizInicial.row(j);
            gradoDeMembresia(j,i) = CalcularSimilaridad(unPunto, unCentroide);
        }
    /*std::cout << "gradoDeMembresia: " <<  std::endl;
    std::cout << gradoDeMembresia <<  std::endl;*/
}


void FCM::runner() {
    this->Inicializacion();
    this->LimpiarMatriz(nuevosCentroides, cantClusters, cantElementos);

    bool bandera = true;
    TipoGuardado suma = 0;
    int step = 0;

    while (bandera) {
        step++;
        suma = 0;
        this->llenarMembresias();
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

    //Normalizar membresia
    for (int i = 0; i< cantClusters; i++){
        TipoVectorColumna vector = gradoDeMembresia.col(i);
        vector.normalize();
        gradoDeMembresia.col(i) = vector;
        }
    this->calcularClusters();
}


TipoGuardado FCM::getMaximo(TipoVectorFila vector) const{
    TipoGuardado maximo = std::numeric_limits<TipoGuardado>::min();
    for (int i = 0; i<vector.cols(); i++){
        if (vector(i) > maximo){
            maximo = vector(i);
            }
    }
    return maximo;
}


void FCM::calcularClusters(){
    for (int j = 0; j < cantClusters; j++)
            clusters[j].clear();

    for (int i = 0; i<cantVectores; i++){
        TipoGuardado maximaSimilitud = getMaximo(gradoDeMembresia.row(i));
        for (int j = 0; j<cantClusters; j++)
            if (gradoDeMembresia(i,j) > MSHIP_PARAM * maximaSimilitud)
                clusters[j].push_back(i);
        }
}

int FCM::proponerK(int maximosClusters){
    int iter = floor(pow(cantVectores/2,0.5));
    cantClusters = iter;
    
    this->LimpiarMatriz(this->gradoDeMembresia, cantVectores, cantClusters);
    gradoDeMembresia.setRandom();
    clusters.resize(cantClusters);
    
    for (int j = 0; j < cantClusters; j++)
        clusters[j].clear();
        
    this->runner();

    return iter;
}
