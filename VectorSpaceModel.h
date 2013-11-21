
#ifndef VECTORSPACEMODEL_H_
#define VECTORSPACEMODEL_H_

#include <iostream>
#include  <stdlib.h>
#include  <string>
#include  <list>
#include  <vector>
#include "DocumentVector.h"
#include "Diccionario.h"
#include <math.h>  

using namespace std;


class VectorSpaceModel {
public:

Diccionario* dic;
vector<DocumentVector*> matriz;
int cantDocs;

VectorSpaceModel(Diccionario* dic, int cantDocs);


void mostrarMatriz();

vector<DocumentVector*> ProcessDocumentCollection();

float FindTFIDF(int ft, int ftd);

};

#endif /* VECTORSPACEMODEL_H_ */
