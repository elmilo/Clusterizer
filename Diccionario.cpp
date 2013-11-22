#include "Diccionario.h"


void Diccionario::agregarTermino(std::string unTermino, unsigned unDocID){

/*string unTermino = termino.palabra;
unsigned int unaPosicion = termino.posicion;*/

unsigned docID = unDocID + 1; //Los guardo con el docID empezando de 1

if (diccionario.count(unTermino) == 1){
    if (diccionario[unTermino].count(docID)==1){
        //El termino y el documento existen en el diccionario
        //Entonces, aumento la frecuencia de ese término en ese documento
        diccionario[unTermino][docID].aumentarFrecuencia();
        
        }else{
        //Significa que el termino existe, pero el mapa del documento no.
        FrecuenciasPorDocumento nuevo;
        nuevo.aumentarFrecuencia();
        diccionario[unTermino].insert(make_pair(docID, nuevo));
        }
    }else{
    /**
     * No existe el termino en el mapa del diccionario, por ende se  
     * debe crear el mapa para ese termino y el del documento
     * */
    listaD mapita;
    FrecuenciasPorDocumento nuevo;
    nuevo.aumentarFrecuencia();
    
    mapita[docID] = nuevo;
    
    diccionario.insert(make_pair(unTermino, mapita));
    }
};

unsigned Diccionario::getCantTerminos(){
	return diccionario.size();
	}
    

/**
 * 
 * TEMPORAL
 * */
void Diccionario::mostrar(){
    
    listaD::iterator interno;
    mapaDelDiccionario::iterator externo;

  for (externo=diccionario.begin(); externo!=diccionario.end(); externo++){
        cout << "--------------------" << endl;
        cout << "Termino: " << externo->first << endl;
    for (interno=externo->second.begin(); interno != externo->second.end(); interno++){
        cout << "docID: " << interno->first << endl;
        cout << "Frecuencia: " <<
        interno->second.getFrecuencia() << endl;
        cout << "--------------------" << endl;}
    }
    
};

