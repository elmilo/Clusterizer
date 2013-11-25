#ifndef DOCUMENTCLUSTERING_H_
#define DOCUMENTCLUSTERING_H_
#include <iostream>
#include  <stdlib.h>
#include  <string>
#include  <list>
#include  <time.h>
#include  <vector>
#include "DocumentVector.h"
#include "centroid.h"

using namespace std;


class DocumentClustering {
	
	int contadorGlobal;
	int contador;
	
	bool CheckStoppingCriteria(list<Centroid> prevClusterCenter, list<Centroid> newClusterCenter);
    int FindClosestClusterCenter(list<Centroid> clusterCenter,DocumentVector* obj);
	list<Centroid> CalculateMeanPoints(list<Centroid> _clusterCenter);
    //void FindRSS(list<Centroid> newCentroid, list<Centroid> _clusterCenter);  //NO SE USA EN EL ORIGINAL
    void GenerateRandomNumber(ref HashSet<int> uniqRand, int k, int docCount);
	void InitializeClusterCentroid(out list<Centroid> centroid,int count);

public:
	DocumentClustering();
	list<Centroid> PrepareDocumentCluster(int k, list<DocumentVector> documentCollection,ref int _counter);
};

#endif /* DOCUMENTCLUSTERING_H_ */
