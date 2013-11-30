#include "Tokenizer.h"
#include "Diccionario.h"
#include "Loader.h"
#include "FrecuenciasPorDocumento.h"
#include "VectorSpaceModel.h"
#include "kMeans.h"

#include <eigen3/Eigen/Core>

#include <iostream>
#include "TiposGlobales.h"

int main(int argc, char **argv){
    
    //string directorio="otrostextos/textosingles";
    string directorio="textos";

    Loader archivosCargados(directorio, "");
    unsigned cantidadIDs = archivosCargados.cantidadDocIDs();
    
    Diccionario *miDiccionario = new Diccionario;
    

    for (unsigned docID = 0; docID<cantidadIDs; docID++){
        Tokenizer tokenizer(archivosCargados.popDocumento(docID));
        while (tokenizer.tengaTerminos()){
            miDiccionario->agregarTermino(tokenizer.siguienteTermino(), docID);
        }
    }
    
    
    //inicializa vector space model
    VectorSpaceModel vecSpaceModel(miDiccionario, cantidadIDs);

    //genera toda la coleccion de vectores de pesos
    vecSpaceModel.procesarDocumentos();


    
    TipoMatriz matrizVecSpace = vecSpaceModel.getMatriz();
    kMeans clusterizando(matrizVecSpace,3);
    
    for (int iteraciones=0; iteraciones<15; iteraciones++){
    cout << "*********************************************************** " << endl;
    cout << "Iteracion : " << iteraciones << endl;
    
    clusterizando.runner();
    
      for (unsigned r = 0; r < cantidadIDs; r++){
        std::cout << "docID: " << r << " es:  " 
                            << archivosCargados.popDocumento(r) << std::endl;
        std::cout << "Pertenece al cluster: " 
                << clusterizando.calcularPuntoMasCercano (matrizVecSpace.row(r)) << std::endl;
        std::cout << std::endl;
        }


    cout << "\n Puntos clusters: " << endl;
    clusterizando.imprimirPuntosClusters();
    cout << "***********************------------------************************* \n\n" << endl;
    }


delete miDiccionario;

return 0;
}
