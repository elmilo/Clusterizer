#include "Tokenizer.h"
#include "Diccionario.h"
#include "ListadorDeArchivos.h"
#include <iostream>


int main(int argc, char **argv){
    
    Diccionario eldicc;
    
    string directorio="textos";

    ListadorDeArchivos lister(directorio);
    
    Tokenizer *parser;

    unsigned cantidadIDs = lister.tamanio();
    /**********************************************************/
    
    for (unsigned i = 0; (i < cantidadIDs); i++){
    
    parser = new Tokenizer(lister.documento(i));
    //parser->parsearArchivo(  );
    
    //unsigned maximo = parser-> cantidad();
    
    while ( parser->tengaTerminos() ) {
        eldicc.insertar( parser->unTermino(), i); 
        }
    
    delete parser;
    }
    
    eldicc.mostrar();
        
	return 0;
}
