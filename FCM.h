#ifndef FCM_H
#define FCM_H

#include <limits>
#include <vector>
#include <cmath> 
#include <math.h>
#include <iostream>
#include <random>

#include "TiposGlobales.h"

/**
* Matrix< tipo que guarda, cant filas, cant cols >
* 
* */

class FCM {
private:
    TipoGuardado TOLERANCIA;
    //TipoGuardado fuzzyness; //"m" en los papers, mayor a 1
    TipoGuardado MSHIP_PARAM;
    
    int cantElementos; //Dimension (cantidad de palabras por ejemplo)
    int cantClusters; // cantidad de clusters que se quieren armar
    int cantVectores; // cantidad de elementos clusterizables (documentos por ejemplo)
    
    std::vector<int> asignaciones;
    
    /*int iteracion; 
    int maxIteraciones;*/
    
    TipoMatriz matrizInicial; // guarda la matriz de datos
    
    //grado de membresia (i,j) del vector xj en el cluster i;
    TipoMatriz gradoDeMembresia;


    TipoMatriz centroides; // cada fila es el centroide del cluster
    TipoMatriz nuevosCentroides; // idem
    
    std::vector< std::vector<int> > clusters; //Para guardar los elementos clusterizados, y su cantidad
    
    //Inicializar con ceros una matriz
    void LimpiarMatriz(TipoMatriz& unaMatriz, int filas, int columnas);
    
    //Asignar valores random a la matriz de centroides
    void Randomize(TipoMatriz& matrizCentroides);

    //Normalizar las filas de una matriz
    void Normalizar(TipoMatriz& unaMatriz, int tamanio);
    
    //Procedimiento apra recalcular centroides, aca se puede utilizar otros algoritmos
    void actualizarCentroides();
    
    FCM(); //No se puede
    
    void Inicializacion();
    
    void calcularClusters();
    
    void llenarMembresias();
    
    TipoGuardado CalcularSimilaridad(TipoVectorFila vecA, TipoVectorFila vecB) const;
    
    TipoGuardado getMaximo(TipoVectorFila vector) const;
    
public:
    int proponerK(int maximosClusters = 32);
        
    FCM(const TipoMatriz& matriz, int n_clusters);
    FCM(const TipoMatriz& matriz);
  
    ~FCM();
    
    std::vector<int> mostrarUnDato(int i) const;
        
    void runner();
};

#endif //FCM_H
