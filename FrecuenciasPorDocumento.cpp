#include "FrecuenciasPorDocumento.h"

FrecuenciasPorDocumento::FrecuenciasPorDocumento(){
    freq = 0.0;    
    }

void FrecuenciasPorDocumento::aumentarFrecuencia(){
    freq = freq +1;
    }

unsigned int FrecuenciasPorDocumento::getFrecuencia(){
    return freq;
    }

