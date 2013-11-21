#include "common.h"
#include "PosicionesPorDocumento.h"



PosicionesPorDocumento::PosicionesPorDocumento(){
    freq = 0;    
    }
    
void PosicionesPorDocumento::insertarPosicion(){
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
    cout <<freq;
    }
