#include "Tokenizer.h"

const char* Tokenizer::delim = ".,:;`/\"+-_(){}[]<>*&^%$#@!?~/|\\= \t\n'";

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

};


bool Tokenizer::tengaTerminos(){
    return !(posiciones.empty());
};


/**********************************************************************************/
/****PRIVATE***********/
/**********************************************************************************/

/*bool Tokenizer::esAlfaNum (string entrada){
  locale loc;
  for (unsigned i=0; i< entrada.length() ; i++){
    if ( !isalnum(entrada[i]) )
        return false;
        }
    return true;
}*/

bool Tokenizer::setearStopWords(){
    ifstream ifile;
    ifile.open(direccion);
    if(!ifile)
        return false;   //could not read the file.
    string linea;
    while(ifile>>linea){
        StopWords.insert(linea);
    }
    return true;
}

bool Tokenizer::esLetraAlfabeto (string entrada){
  locale loc;
  for (unsigned i=0; i< entrada.length() ; i++){
    if ( !isalpha(entrada[i]) )
        return false;
        }
    return true;
}

void Tokenizer::agregarEnContenedor(char *palabra){

    int tamanio = 0;
    char *s = palabra;
    for (s = palabra; *s; s++)
        tamanio++;

    string tokenito(palabra, tamanio);
    
    if (esLetraAlfabeto(tokenito)){
        transform(tokenito.begin(),tokenito.end(),tokenito.begin(),(int (*)(int))tolower );
        if ((tokenito.size()>3) && (StopWords.count(tokenito)!=0))
            posiciones.push_back(tokenito);        
    }
}

/**
 * Codigo C
 * */
int Tokenizer::separarTokens(){
        char *archivoEnMemoria, *palabra, *agregada;
        FILE *fp = fopen(direccion, "r");
        struct stat sb;
 
        if (!fp)
                return 0;
 
        if (stat(direccion, &sb))
                return 0;
 
        archivoEnMemoria = (char *) malloc(sb.st_size); //<-- ¬¬
        
        if (!archivoEnMemoria) {
                fclose(fp);
                return 0;
        }
 
        fread(archivoEnMemoria, sizeof(char), sb.st_size, fp);
 
        palabra = strtok(archivoEnMemoria, delim);
        
        while(palabra != NULL) {
                agregada = strdup(palabra);
                
                agregarEnContenedor(agregada);
 
                palabra = strtok(NULL, delim);
        }
 
        free(archivoEnMemoria);
        fclose(fp);
 
        return 1;
}
