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
    
    
    
    
    //miDiccionario->mostrar();
     
//inicializa vector space model
VectorSpaceModel vecSpaceModel(miDiccionario, cantidadIDs);
//genera toda la coleccion de vectores de pesos
vecSpaceModel.procesarDocumentos();
// muetra todos los vectores, cada vector es un doc   
//vecSpaceModel.mostrarMatriz();

/*for (std::vector<DocumentVector*>::iterator it = matriz.begin();
			it != matriz.end(); ++it) {
		(*it)->mostrarVector();
		cout << endl;
	}*/

    kMeans clusterizando(3);
    TipoMatriz salida = vecSpaceModel.getMatriz();
    //for (int iteraciones=0; iteraciones<500; iteraciones++){
    clusterizando.agregarPuntos(salida);
    clusterizando.runner2();
    //}
    
    //Eigen::MatrixXf paraMostrar = clusterizando.getCentroides();
    //cout << "Esto es (cant de palabras X cant de clusters): " << endl;
    
    //cout << paraMostrar.transpose() << endl;
  
  for (unsigned r = 0; r < cantidadIDs; r++){
        std::cout << "docID: " << r << " es:  " << archivosCargados.popDocumento(r) << std::endl;
        std::cout << "Pertenece al cluster: " << clusterizando.calcularPuntoMasCercano (salida.row(r)) << std::endl;
        std::cout << std::endl;
        }
      

  cout << "\n Puntos clusters: " << endl;
  clusterizando.imprimirPuntosClusters();

    //cout << "Esto es (cant de palabras X docs): " << endl;
    
    //cout << salida.transpose() << endl;
    
delete miDiccionario;

return 0;
}
