#include "Diccionario.h"


void Diccionario::insertar(palabraPos termino, unsigned unDocID){

string unTermino = termino.palabra;


unsigned docID = unDocID + 1; //Los guardo con el docID empezando de 1

if (diccionario.count(unTermino) == 1){
    if (diccionario[unTermino].count(docID)==1){
        //El termino y el documento existen en el diccionario
        diccionario[unTermino][docID].insertarPosicion();
        
        }else{
        //Significa que el termino existe, pero el mapa del documento no.
        PosicionesPorDocumento listado;
        //sumamos frecuencia +1
        listado.insertarPosicion();
        diccionario[unTermino].insert(make_pair(docID, listado));
        }
    }else{
    /**
     * No existe el termino en el mapa del diccionario, por ende se  
     * debe crear el mapa para ese termino y el del documento
     * */
    listaD mapita;

    PosicionesPorDocumento listado;
    //sumamos frecuencia +1
    listado.insertarPosicion();
    mapita[docID] = listado;

    diccionario.insert(make_pair(unTermino, mapita));
    }
};

/**
 * 
 * TEMPORAL
 * */
 
int Diccionario::getCantTerminos(){
	return diccionario.size();
	}
 
void Diccionario::mostrar(){
    listaD::iterator interno;
    mapaDelDiccionario::iterator externo;

  for (externo=diccionario.begin(); externo!=diccionario.end(); externo++){
        cout << externo->first <<endl;
    }
    
};

