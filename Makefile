OBJ = main.o Diccionario.o Loader.o Tokenizer.o FrecuenciasPorDocumento.o VectorSpaceModel.o kMeans.o FCM.o
CXXFLAGS = -fmessage-length=0 -Wall -std=gnu++11
#CXXDEBUG = -O0 -g3
CXXRELEASE = -O3
#LDFLAGS= -m32

#all: debug

#debug: CXX += $(CXXDEBUG)
#debug: clusterizer

release: CXX += $(CXXRELEASE)
release: clusterizer

kMeans.o: kMeans.cpp kMeans.h 
	g++ $(CXXFLAGS) -c kMeans.cpp

FCM.o: FCM.cpp FCM.h 
	g++ $(CXXFLAGS) -c FCM.cpp

FrecuenciasPorDocumento.o: FrecuenciasPorDocumento.cpp FrecuenciasPorDocumento.h
	g++ $(CXXFLAGS) -c FrecuenciasPorDocumento.cpp

Diccionario.o: Diccionario.h Diccionario.cpp FrecuenciasPorDocumento.h
	g++ $(CXXFLAGS) -c Diccionario.cpp

Loader.o: Loader.cpp Loader.h
	g++ $(CXXFLAGS) -c Loader.cpp

Tokenizer.o: Tokenizer.cpp Tokenizer.h
	g++ $(CXXFLAGS) -c Tokenizer.cpp

VectorSpaceModel.o: VectorSpaceModel.cpp VectorSpaceModel.h 
	g++ $(CXXFLAGS) -c VectorSpaceModel.cpp

main.o: main.cpp
	g++ $(CXXFLAGS) -c main.cpp

clusterizer: main.o Diccionario.o Loader.o Tokenizer.o FrecuenciasPorDocumento.o VectorSpaceModel.o kMeans.o FCM.o
	g++ -o clusterizer $(OBJ)


clean:
	rm $(OBJ) clusterizer

.PHONY = clean
