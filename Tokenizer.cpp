#include "Tokenizer.h"

/******************************************************************************/
/****PUBLIC***********/

Tokenizer::Tokenizer(string direccionArchivo){
    inicializar(direccionArchivo);
    }


void Tokenizer::inicializar(string direccionArchivo){
    direccion = direccionArchivo.c_str();
    setearStopWords();
    separarTokens();
}


string Tokenizer::siguienteTermino(){
    string termino = posiciones.front();
    posiciones.pop_front();
    return termino;
}


bool Tokenizer::tengaTerminos(){
    return !(posiciones.empty());
}


/******************************************************************************/
/****PRIVATE***********/


bool Tokenizer::setearStopWords(){
    ifstream ifile;
    ifile.open("stopwords.txt");
    if(!ifile)
        return false;   
    string linea;
    while(ifile>>linea){
        StopWords.insert(linea);
    }
    return true;
}

bool Tokenizer::perteneceAlfabeto (string entrada){
  locale loc;
  for (unsigned i=0; i< entrada.length() ; i++){
    if ( !isalpha(entrada[i]) )
        return false;
        }
    return true;
}


void Tokenizer::agregarEnContenedor(string tokenito){
    if (perteneceAlfabeto(tokenito)){
        transform(tokenito.begin(),tokenito.end(),tokenito.begin(),(int (*)(int))tolower );
        if ((tokenito.size()>3) && (StopWords.count(tokenito)==0))
            posiciones.push_back(tokenito);        
    }
}


int Tokenizer::separarTokens(){
    ifstream archivoEntrada(direccion);
    string unaLinea;
    if(archivoEntrada.is_open())
        while(archivoEntrada.good()){
            getline(archivoEntrada, unaLinea);
            stringstream sin(unaLinea);
            string posibleToken;
            while(getline(sin, posibleToken, ' ') ){
                posibleToken.erase(std::remove_if(posibleToken.begin(), posibleToken.end(),
                    (int(*)(int))std::ispunct), posibleToken.end() );
            //std::cout << posibleToken << std::endl;
                agregarEnContenedor(posibleToken);
            }
        }
    archivoEntrada.close();
    return 0;
}
