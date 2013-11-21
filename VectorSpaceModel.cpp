#include "VectorSpaceModel.h"

using namespace std;

VectorSpaceModel::VectorSpaceModel(Diccionario* diccionario, int cantDocs) {
	this->dic = diccionario;
	this->cantDocs = cantDocs;
	int cantTerminos = diccionario->getCantTerminos();
	for (int i = 0; i < cantDocs; i++) {
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
	listaD::iterator interno;
	mapaDelDiccionario::iterator externo;
	DocumentVector* documentVector;
	int posTermino = 0;
	int ft;
	for (externo = dic->diccionario.begin(); externo != dic->diccionario.end();
			externo++) {
		for (interno = externo->second.begin();
				interno != externo->second.end(); interno++) {
			externo->second.size();
			ft = externo->second.size();
			//agregamos frecuencias a los vectores
			documentVector = matriz[interno->first - 1];
			documentVector->agregarEnPos(posTermino,
			FindTFIDF(ft, interno->second.getFrecuencia()));
		}
		posTermino++;
	}
	return matriz;
}

float VectorSpaceModel::FindTFIDF(int ft, int ftd) {
	float idf;
	idf = log10(cantDocs / ft);
	return (ftd * idf);
}
