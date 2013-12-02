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

/*TpGrupo13 -d datos/books -c 14 -o Y/N
-d indica el path a donde están almacenados los documentos
-c indica la cantidad de categorias a crear, si no se indica -c el TP debe decidir automaticamente cual es
el número de clusters a generar de acuerdo a su entendimiento de los datos.
-o indica si un documento puede estar en mas de un grupo

TpGrupo13 -l
Lista todos los documentos del repositorio y la categoría a la cual pertenece cada uno.

TpGrupo13 -g
Lista los grupos o categorías existentes y los documentos dentro de cada grupo o categoría

TpGrupo13 -a datos/books/alice_in_wonderland
Agrega y clasifica el texto pasado como parametro e indica a que grupo lo ha agregado (a partir de aqui
debería aparecer al listad con -l o -g)*/

void guardarOpciones(std::string opcionF, int cantClusters){
    std::ofstream salida ("opcionesGeneral");
    salida <<opcionF;
    salida <<cantClusters;
    salida.close();
    return true;
}

void cargarOpciones(std::string& opcionF, int& cantClusters){
    std::ifstream entrada ("opcionesGeneral");
    cantClusters=-1;
    entrada >> opcionF;
    entrada >> cantClusters;
    entrada.close();
    return true;
}



TipoMatriz cargarDiccionario(std::string directorio) const{
    Loader archivosCargados(directorio, "");
    unsigned cantidadIDs = archivosCargados.cantidadDocIDs();

    Diccionario *miDiccionario = new Diccionario;


    for (unsigned docID = 0; docID<cantidadIDs; docID++){
        Tokenizer tokenizer(archivosCargados.popDocumento(docID));
        while (tokenizer.tengaTerminos()){
            miDiccionario->agregarTermino(tokenizer.siguienteTermino(), docID);
        }
    }

    VectorSpaceModel vecSpaceModel(miDiccionario, cantidadIDs);
    //genera toda la coleccion de vectores de pesos
    vecSpaceModel.procesarDocumentos();

    vecSpaceModel.haciaDisco();
    archivosCargados.haciaDisco();

    delete miDiccionario;
    return vecSpaceModel.getMatriz();
}


int main( int argc, char** argv )

    std::string directorio;
    std::string opcionFuzzy;
    int cantClusters;
//    TipoMatriz matriz;

    if (argc==5){
        if (argv[1]=="-d" && argv[3]=="-o"){
            //Proponer K optimo
            directorio = argv[2];
            opcionFuzzy = argv[4];
            if (opcionFuzzy=="Y"){
                FCM clusterizando(cargarDiccionario(directorio));
                cantClusters = clusterizando.proponerK();
            }else{
                kMeans clusterizando(cargarDiccionario(directorio));
                cantClusters = clusterizando.proponerK();
                }
            guardarOpciones(opcionFuzzy,-1);
        }
    }

    if (argc==7){
        if (argv[1]=="-d" && argv[3]=="-c" && argv[5]=="-o"){
            pathDocumentos = argv[2];
            cantClusters = argv[4];
            opcionFuzzy = argv[6];
            if (opcionFuzzy=="Y"){
                FCM clusterizando(cargarDiccionario(directorio),cantClusters);
                clusterizando.runner();
            }else{
                kMeans clusterizando(cargarDiccionario(directorio),cantClusters);
                clusterizando.runner();
                }
            guardarOpciones(opcionFuzzy, cantClusters);
        }
    }
    
    if (argc==2){
        if( argv[1]=="-l"){
            //listar documentos
            Loader archivosCargados();
            archivosCargados.desdeDisco();
            unsigned cantidadIDs = archivosCargados.cantidadDocIDs();
            for (unsigned r = 0; r < cantidadIDs ; r++){
                std::cout << archivosCargados.popDocumento(r) << std::endl;
                }
            }
        if( argv[1]=="-g"){
            //listar documentos y clusters
            VectorSpaceModel vecSpaceModel();
            vecSpaceModel.desdeDisco();
            matrizVecSpace = vecSpaceModel.getMatriz();

            Loader archivosCargados();
            archivosCargados.desdeDisco();
            unsigned cantidadIDs = archivosCargados.cantidadDocIDs();
            
            opcionFuzzy = "N";

            cargarOpciones(opcionFuzzy, cantClusters);
            if (opcionFuzzy=="Y"){
                if (cantClusters == -1){
                    FCM clusterizando.desdeDisco();
                    cantClusters = clusterizando.proponerK();
                    }else{
                        FCM clusterizando.desdeDisco();
                        }
            }else{
                if (cantClusters == -1){
                    kMeans clusterizando.desdeDisco();
                    cantClusters = clusterizando.proponerK();
                    }else{
                        kMeans clusterizando.desdeDisco();
                        }

            for (int cluster=0; cluster<cantClusters; cluster++){
                std::vector<int> documentos = clusterizando.mostrarUnDato(cluster);
                std::cout << "Grupo: " << cluster+1 << std::endl;
                std::cout << "("<< documentos.size() << " elementos)"<< std::endl;
                    for (unsigned r = 0; r < documentos.size() ; r++){
                        std::cout << archivosCargados.popDocumento(documentos[r]) << std::endl;
                    }
                std::cout << std::endl;
                }
            }
            }

        if( argv[1]=="-a"){
            //buscar a donde pertence un documento
            }
    }
  
















int main(int argc, char **argv){
    int cantClusters = 8;
    
    //string directorio="otrostextos/textosingles";
    //string directorio="textos";


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
