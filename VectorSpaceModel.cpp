#include "VectorSpaceModel.h"



VectorSpaceModel::VectorSpaceModel(Diccionario *diccionario, unsigned cantDocuments){
	this->miDiccionario = diccionario;
	this->cantDocs = cantDocuments;
	this->cantTerminos = miDiccionario->getCantTerminos();
	//filas = palabras; columnas = docs al reves!!
	//matriz.resize(cantTerminos,cantDocs);
    matriz.resize(cantDocs,cantTerminos);
}

void VectorSpaceModel::procesarDocumentos(){
	limpiarMatriz();
	llenarPalabras();
	llenarMatrizConTFIDF();	
	}


void VectorSpaceModel::limpiarMatriz(){
	for (unsigned i = 0; i<cantDocs; i++)
		for (unsigned j = 0; j<cantTerminos; j++)
			matriz(i,j) = 0;
}


void VectorSpaceModel::llenarPalabras(){
listaD::iterator interno;
mapaDelDiccionario::iterator externo;
Nodo unToken;
unsigned frecuenciaAbsoluta;

			
for (externo = miDiccionario->diccionario.begin(); externo != miDiccionario->diccionario.end();
			externo++) {
	unToken.token = externo->first;
	
	frecuenciaAbsoluta =0;
	for (interno=externo->second.begin(); interno != externo->second.end(); interno++)
			frecuenciaAbsoluta++;
	
	unToken.idf=log10((TipoGuardado)cantDocs / (TipoGuardado)frecuenciaAbsoluta);
	palabras.push_back(unToken);
	}
	
	/*Para mostrar el vector:
	 * cout << "idf: \n";
	for (int i = 0; i<palabras.size(); i++){
		cout << palabras[i].token << " " << palabras[i].idf << endl;
		}*/
}

void VectorSpaceModel::llenarMatrizConTFIDF() {
listaD::iterator interno;
mapaDelDiccionario::iterator externo;

for (externo = miDiccionario->diccionario.begin(); externo != miDiccionario->diccionario.end();
			externo++) {
	int posicionPalabra = bbinaria(externo->first); //busca la posicion del token
	if (posicionPalabra != -1){
		for (interno=externo->second.begin(); interno != externo->second.end(); interno++){
			TipoGuardado idf = palabras[posicionPalabra].idf;
			int ft = interno->second.getFrecuencia();
			matriz(interno->first,posicionPalabra)= (TipoGuardado) ft * idf;
			}
		}
	}
}


TipoMatriz VectorSpaceModel::getMatriz() const { 
        return matriz; 
}


int VectorSpaceModel::bbinaria(const std::string unaPalabra){
    int izquierda = 0;
    int derecha = (int)palabras.size()-1;
    int mid = (derecha+izquierda)/2;

    while(izquierda <= derecha){
        mid = (derecha+izquierda)/2;
        Nodo unNodo = palabras[mid]; 
        if (unNodo.token == unaPalabra) 
            return mid;   
        else if (unaPalabra > unNodo.token)
            izquierda = mid + 1; 
        else if (unaPalabra < unNodo.token)
            derecha = mid - 1; 
    }
    return -1;
}
	
/* ************************************************************************************** */
/*TipoMatriz matrizDesdeArchivo();

void VectorSpaceModel::matrizHaciaArchivo() {
ofstream out("vectores.dat", ios::out | ios::binary);
unsigned docActual=0;
int ft=0;
int idf=0;
int pesoCero=0;
TipoGuardado peso;
mapaDelDiccionario::iterator externo;

for(int i=0; i<cantDocs;i++){
for (externo = miDiccionario->diccionario.begin(); externo != miDiccionario->diccionario.end(); externo++) {

			listaD::iterator interno = externo->second.find(docActual);
	
			if (interno != externo->second.end()){
					ft = interno->second.getFrecuencia();
					idf= externo->second.size();
					peso=(log10((TipoGuardado)cantDocs / (TipoGuardado)idf))*(TipoGuardado)ft;
					out.write((char *)&peso,4);
					}
					else{
						out.write((char *)&pesoCero,4);
						}
			}
			docActual++;
		
}
out.close();

ofstream Addenda("docIDs.dat", ios::out | ios::binary);
docIDs.write(cantDocs);
docIDs.write(cantTerminos);
}

vector<TipoGuardado> VectorSpaceModel::getDocumento(int docID){
	vector<TipoGuardado> vecDocumento;
	TipoGuardado numero;
	int posDoc;
	ifstream in("vectores.dat", ios::in | ios::binary);
	posDoc=docID*cantTerminos*4;
	in.seekg(posDoc);
	while(in.tellg()<(posDoc+cantTerminos*4)){
        in.read((char*)&numero,4);
        vecDocumento.push_back(numero);
        }
	return vecDocumento;
	}*/


//TEMPORAL:
void VectorSpaceModel::mostrarMatriz() {
	std::cout << matriz << std::endl;
}
