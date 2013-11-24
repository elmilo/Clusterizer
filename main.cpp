#include "Tokenizer.h"
#include "Diccionario.h"
#include "Loader.h"
#include "FrecuenciasPorDocumento.h"


#include "VectorSpaceModel.h"
#include "DocumentVector.h"

#include <iostream>


int main(int argc, char **argv){
    
    string directorio="otrostextos/textosingles";
    //string directorio="textos";

    Loader archivosCargados(directorio, "");
    unsigned cantidadIDs = archivosCargados.cantidadDocIDs();
    
    Diccionario *miDiccionario = new Diccionario;
    

    for (unsigned i = 0; i<cantidadIDs; i++){
        Tokenizer tokenizer(archivosCargados.popDocumento(i));
        while (tokenizer.tengaTerminos()){
            miDiccionario->agregarTermino(tokenizer.siguienteTermino(), i);
        }
    }
    
    
    
    miDiccionario->mostrar();
     
//inicializa vector space model
VectorSpaceModel vecSpaceModel(miDiccionario, cantidadIDs);
//genera toda la coleccion de vectores de pesos
vector<DocumentVector*> matriz=vecSpaceModel.ProcessDocumentCollection();
// muetra todos los vectores, cada vector es un doc   
//vecSpaceModel.mostrarMatriz();

/*for (std::vector<DocumentVector*>::iterator it = matriz.begin();
			it != matriz.end(); ++it) {
		(*it)->mostrarVector();
		cout << endl;
	}*/

delete miDiccionario;

return 0;
}
