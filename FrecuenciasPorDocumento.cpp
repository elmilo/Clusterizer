#include "FrecuenciasPorDocumento.h"

FrecuenciasPorDocumento::FrecuenciasPorDocumento(){
    freq = 0;    
    }

void FrecuenciasPorDocumento::aumentarFrecuencia(){
    freq++;
    }

unsigned int FrecuenciasPorDocumento::getFrecuencia(){
    return freq;
    }

