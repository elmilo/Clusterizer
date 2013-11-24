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
    string termino = TokenList.front();
    TokenList.pop_front();
    return termino;
}


bool Tokenizer::tengaTerminos(){
    return !(TokenList.empty());
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
    if ( !isalpha(entrada[i]) ) //isalnum(entrada[i]) para letras y numeros
        return false;
        }
    return true;
}


void Tokenizer::agregarEnContenedor(string unToken){
	//Solamente se guardaran palabras con letras, ningun numero
    if (perteneceAlfabeto(unToken)){
		//Paso todo a minusculas
        transform(unToken.begin(),unToken.end(),unToken.begin(),(int (*)(int))tolower );
        //Pregunto si la longitud es mayor igual a 3 y si no pertecene a los stopwords
        if ((unToken.size()>=3) && (StopWords.count(unToken)==0))
            TokenList.push_back(unToken);//agrego token   
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
            //Busco los espacios que separan las palabras en la linea
            while(getline(sin, posibleToken, ' ') ){
				//Remuevo caracteres no alfanumericos
                posibleToken.erase(std::remove_if(posibleToken.begin(), posibleToken.end(),
                    (int(*)(int))std::ispunct), posibleToken.end() );
                agregarEnContenedor(posibleToken);
            }
        }
    archivoEntrada.close();
    return 0;
}

/** Este trabaja de manera distinta, agarra menos palabras (?)
 * 
 
 void Tokenizer::agregarEnContenedor(string unToken){
	//Solamente se guardaran palabras con letras, ningun numero
    if (perteneceAlfabeto(unToken)){
		//Remuevo caracteres no alfanumericos
		unToken.erase(std::remove_if(unToken.begin(), unToken.end(),
			(int(*)(int))std::ispunct), unToken.end() );
		//Paso todo a minusculas
        transform(unToken.begin(),unToken.end(),unToken.begin(),(int (*)(int))tolower );
        //Pregunto si la longitud es mayor igual a 3 y si no pertecene a los stopwords
        if ((unToken.size()>=3) && (StopWords.count(unToken)==0))
            TokenList.push_back(unToken);        
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
            //Busco los espacios que separan las palabras en la linea
            while(getline(sin, posibleToken, ' ') ){
            //std::cout << posibleToken << std::endl;
                agregarEnContenedor(posibleToken);
            }
        }
    archivoEntrada.close();
    return 0;
}

void Tokenizer::agregarEnContenedor(string unToken){
	//Solamente se guardaran palabras con letras, ningun numero
    if (perteneceAlfabeto(unToken)){
		//Remuevo caracteres no alfanumericos
		unToken.erase(std::remove_if(unToken.begin(), unToken.end(),
			(int(*)(int))std::ispunct), unToken.end() );
		//Paso todo a minusculas
        transform(unToken.begin(),unToken.end(),unToken.begin(),(int (*)(int))tolower );
        //Pregunto si la longitud es mayor igual a 3 y si no pertecene a los stopwords
        if ((unToken.size()>=3) && (StopWords.count(unToken)==0))
            TokenList.push_back(unToken);        
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
            //Busco los espacios que separan las palabras en la linea
            while(getline(sin, posibleToken, ' ') ){
            //std::cout << posibleToken << std::endl;
                agregarEnContenedor(posibleToken);
            }
        }
    archivoEntrada.close();
    return 0;
}*/
