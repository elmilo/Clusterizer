#include "Tokenizer.h"
#include "Diccionario.h"
#include "Loader.h"
#include "FrecuenciasPorDocumento.h"
#include "VectorSpaceModel.h"
#include <eigen3/Eigen/Core>

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
    
    for (unsigned i = 0; i<cantidadIDs; i++)
		std::cout << "docID: " << i << " es:  " << archivosCargados.popDocumento(i) << std::endl;    
    
    
    //miDiccionario->mostrar();
     
//inicializa vector space model
VectorSpaceModel vecSpaceModel(miDiccionario, cantidadIDs);
//genera toda la coleccion de vectores de pesos
vecSpaceModel.procesarDocumentos();
// muetra todos los vectores, cada vector es un doc   
vecSpaceModel.mostrarMatriz();

/*for (std::vector<DocumentVector*>::iterator it = matriz.begin();
			it != matriz.end(); ++it) {
		(*it)->mostrarVector();
		cout << endl;
	}*/
	
cout<<endl;
//vecSpaceModel.guardarMatriz();


// recuperamos vector 2 del DISCO
cout<<"doc 2 del disco:";
vector<float> vec;
vec= vecSpaceModel.getDocumento(2);

for (std::vector<float>::iterator it = vec.begin(); it != vec.end(); ++it) 
		cout<<(*it)<<" ";

//delete miDiccionario;

return 0;
}
