#include "common.h"
#include "PosicionesPorDocumento.h"

PosicionesPorDocumento::PosicionesPorDocumento(unsigned int primera){
    posiciones.push_back(primera);
    freq = 1;
    }

PosicionesPorDocumento::PosicionesPorDocumento(){
    freq = 0;    
    }
    
void PosicionesPorDocumento::insertarPosicion(unsigned int una){
    posiciones.push_back(una);
    freq++;
}

unsigned int PosicionesPorDocumento::getFrecuencia(){
    return freq;
    }

/**
 * 
 * TEMPORAL
 * */
void PosicionesPorDocumento::mostrarPosiciones(){
    //cout << freq << ";";;
    for (list<unsigned int>::iterator enLaPos=posiciones.begin(); enLaPos != posiciones.end(); enLaPos++)
        cout << *enLaPos << " ";
    //cout << endl;
    }
