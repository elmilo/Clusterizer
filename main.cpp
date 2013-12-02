#include "Tokenizer.h"
#include "Diccionario.h"
#include "Loader.h"
#include "FrecuenciasPorDocumento.h"
#include "VectorSpaceModel.h"
#include "kMeans.h"
#include "FCM.h"

#include <eigen3/Eigen/Core>

#include <iostream>
#include <vector>
#include "TiposGlobales.h"

int main(int argc, char **argv){
    int cantClusters = 8;
    
//    string directorio="otrostextos/textosingles";
    //string directorio="textos";
    string directorio="/home/emilio/Descargas/Clusterizer-eigen3/textos";

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
    
    /*FCM clusterizando(matrizVecSpace, cantClusters);

    clusterizando.runner();

    for (int cluster=0; cluster<cantClusters; cluster++){
        std::vector<int> documentos = clusterizando.mostrarUnDato(cluster);
        std::cout << "Grupo: " << cluster+1 << std::endl;
        std::cout << "("<< documentos.size() << " elementos)"<< std::endl;
        for (unsigned r = 0; r < documentos.size() ; r++){
            std::cout << archivosCargados.popDocumento(documentos[r]) << std::endl;
            }
        std::cout << std::endl;
    }*/
    
    kMeans clusterizando(matrizVecSpace);

    //clusterizando.runner();
    cantClusters = clusterizando.proponerK();
    std::cout << "El k optimo: " <<  cantClusters << std::endl;
    
    for (int cluster=0; cluster<cantClusters; cluster++){
        std::vector<int> documentos = clusterizando.mostrarUnDato(cluster);
        std::cout << "Grupo: " << cluster+1 << std::endl;
        std::cout << "("<< documentos.size() << " elementos)"<< std::endl;
        for (unsigned r = 0; r < documentos.size() ; r++){
            std::cout << archivosCargados.popDocumento(documentos[r]) << std::endl;
            }
        std::cout << std::endl;
        }

    delete miDiccionario;

return 0;
}
