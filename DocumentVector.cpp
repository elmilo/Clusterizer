#include "DocumentVector.h"

DocumentVector::DocumentVector() {
}

void DocumentVector::setTamanio(unsigned tamanio){
    for (unsigned i=0; i<tamanio; i++){
        VectorSpace.push_back(0);
    }
}


void DocumentVector::agregarEnPos(unsigned pos, double valor){
    VectorSpace[pos]=valor;
}

void DocumentVector::mostrarVector(){
for (std::vector<float>::iterator it = VectorSpace.begin() ; it != VectorSpace.end(); ++it)
     cout<<(*it)<<" ";
}

DocumentVector::~DocumentVector() {
	// TODO Auto-generated destructor stub
}

