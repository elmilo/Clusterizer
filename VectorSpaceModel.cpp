#include "VectorSpaceModel.h"

using namespace std;

VectorSpaceModel::VectorSpaceModel(Diccionario *diccionario, unsigned cantDocs) {
	this->dic = diccionario;
	this->cantDocs = cantDocs;
	unsigned cantTerminos = diccionario->getCantTerminos();
	for (unsigned i = 0; i < cantDocs; i++) {
		DocumentVector* vector = new DocumentVector();
		vector->setTamanio(cantTerminos);
		matriz.push_back(vector);
	}
}

void VectorSpaceModel::mostrarMatriz() {
	for (std::vector<DocumentVector*>::iterator it = matriz.begin();
			it != matriz.end(); ++it) {
		(*it)->mostrarVector();
		cout << endl;
	}
}

vector<DocumentVector*> VectorSpaceModel::ProcessDocumentCollection() {
	listaD::iterator unsignederno;
	mapaDelDiccionario::iterator externo;
	DocumentVector* documentVector;
	unsigned posTermino = 0;
	unsigned ft;
	for (externo = dic->diccionario.begin(); externo != dic->diccionario.end();
			externo++) {
		for (unsignederno = externo->second.begin();
				unsignederno != externo->second.end(); unsignederno++) {
			externo->second.size();
			ft = externo->second.size();
			//agregamos frecuencias a los vectores
			documentVector = matriz[unsignederno->first - 1];
			documentVector->agregarEnPos(posTermino,
			FindTFIDF(ft, unsignederno->second.getFrecuencia()));
		}
		posTermino++;
	}
	return matriz;
}

float VectorSpaceModel::FindTFIDF(unsigned ft, unsigned ftd) {
	float idf;
	idf = log10(cantDocs / ft);
	return (ftd * idf);
}
