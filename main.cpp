#include "Tokenizer.h"
#include "Diccionario.h"
#include "ListadorDeArchivos.h"
#include "VectorSpaceModel.h"
#include "DocumentVector.h"
#include <iostream>


int main(int argc, char **argv){
    
    Diccionario* eldicc= new Diccionario();
    
    string directorio="textos";

    ListadorDeArchivos lister(directorio);
    
    Tokenizer *parser;

    unsigned cantidadIDs = lister.tamanio();
    /**********************************************************/
    
    for (unsigned i = 0; (i < cantidadIDs); i++){
    
    parser = new Tokenizer(lister.documento(i));
    
    while ( parser->tengaTerminos() ) {
        eldicc->insertar( parser->unTermino(), i); 
        }
    
    delete parser;
    }
    
//muestra los terminos    
	eldicc->mostrar();

//inicializa vector space model
   VectorSpaceModel vecSpaceModel(eldicc, cantidadIDs);
//genera toda la coleccion de vectores de pesos
vector<DocumentVector*> matriz=vecSpaceModel.ProcessDocumentCollection();
// muetra todos los vectores, cada vector es un doc   
//vecSpaceModel.mostrarMatriz();

for (std::vector<DocumentVector*>::iterator it = matriz.begin();
			it != matriz.end(); ++it) {
		(*it)->mostrarVector();
		cout << endl;
	}

return 0;
}
