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
unsigned frecuenciaAbsoluta; //Guarda en cuantos documentos aparece un token

			
for (externo = miDiccionario->diccionario.begin(); externo != miDiccionario->diccionario.end();
			externo++) {
	unToken.token = externo->first;
	
	frecuenciaAbsoluta =0;
	for (interno=externo->second.begin(); interno != externo->second.end(); interno++)
			frecuenciaAbsoluta++;
	if (frecuenciaAbsoluta != 0){
        unToken.idf=log10((TipoGuardado)cantDocs / (TipoGuardado)frecuenciaAbsoluta);
        palabras.push_back(unToken);}
    //std::cout << "token: " << unToken.token << "frec absoluta: " << frecuenciaAbsoluta << std::endl;
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
//TipoMatriz mostrar = TipoMatriz::Zero(cantDocs, cantTerminos);

for (externo = miDiccionario->diccionario.begin(); externo != miDiccionario->diccionario.end();
			externo++) {
	int posicionPalabra = bbinaria(externo->first); //busca la posicion del token
	if (posicionPalabra != -1){
		for (interno=externo->second.begin(); interno != externo->second.end(); interno++){
			TipoGuardado idf = palabras[posicionPalabra].idf;
			int ft = interno->second.getFrecuencia();
			matriz(interno->first,posicionPalabra) = (TipoGuardado) ft * idf;
            /*mostrar(interno->first,posicionPalabra)=(TipoGuardado) ft;*/
			}
		}
	}
    /*std::cout<< "matriz TF:" << std::endl;
    std::cout<< mostrar << std::endl;
    for (int i=0; i<palabras.size(); i++){
        std::cout<< palabras[i].token << " "<< palabras[i].idf << std::endl;
        }*/
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

/*
void VectorSpaceModel::haciaDisco(){
ofstream data_file("dic.dat", std::ios::binary);
const unsigned int maxPalabra=16;
mapaDelDiccionario::iterator externo;
float idf;

 unsigned char * buf_ptr = new unsigned char [16];
  unsigned char * buf_grabar=buf_ptr;
        
  for (externo=miDiccionario->diccionario.begin(); externo!=miDiccionario->diccionario.end(); externo++){
         fill_n(buf_ptr, 16,0);
         idf=log10((TipoGuardado)cantDocs / (TipoGuardado)externo->second.size());
         //externo->first es una palabra
        strncpy((char *) buf_ptr, externo->first.c_str(), maxPalabra);
                data_file.write((char *)&idf, 4);
        data_file.write((char *) buf_grabar, 16);
        }
    data_file.close();
    delete [] buf_ptr;
        }


void VectorSpaceModel::desdeDisco(){
                        char * buf_ptr = new char [16];
                        vector<Nodo> vecDic;
                        ifstream in("dic.dat", ios::in | ios::binary);
                        Nodo nodo;
                        in.read((char*)&nodo.idf,4);
            in.read(buf_ptr,16);                        
        while(!in.eof()){
            nodo.token = string((char *) buf_ptr);
                        vecDic.push_back(nodo);
                        in.read((char*)&nodo.idf,4);
            in.read(buf_ptr,16);                
            }
           palabrasDeDisco=vecDic;
}*/

  /* ejemplo prueba
nodo=vecDic[0];
cout<<nodo.idf<<endl;
cout<<nodo.token<<endl;
cout<<nodo.token.size()<<endl;
nodo=vecDic[1];
cout<<nodo.idf<<endl;
cout<<nodo.token<<endl;
*/
