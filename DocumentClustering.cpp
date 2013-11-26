#include "DocumentClustering.h"
#define foreachx(_type,_iter,_coll) for (_type::iterator _iter = _coll.begin; _iter != _coll.end(); _iter++)
DocumentClustering::DocumentClustering(){
       	
       	list<Centroid> DocumentClustering::PrepareDocumentCluster(int k, list<DocumentVector*> documentCollection,int _counter){
				
				contadorGlobal = 0;
               //prepara k centroides iniciales y asigna un objeto al azar a cada centroide
               list<Centroid> centroidCollection;
               
               
               /*
                * Avoid repeation of random number, if same no is generated more than once same document is added to the next cluster 
                * so avoid it using HasSet collection
                */
               std::vector<int> uniqRand;
               GenerateRandomNumber(uniqRand[],k,documentCollection.Count);
               
               int pos;               
               foreachx(uniqRand, pos, List) 
               {
                   Centroid c;                
                   c.GroupedDocument = new list<DocumentVector*>();
                   c.GroupedDocument.Add(documentCollection[*pos]);
                   centroidCollection.Add(c);                
               }
   
               bool stoppingCriteria;
               list<Centroid> resultSet;
               list<Centroid> prevClusterCenter;
               
               InitializeClusterCentroid(resultSet, centroidCollection.Count);
   
               do
               {
                   prevClusterCenter = centroidCollection;
   
				   DocumentVector* obj;
				   foreachx(documentCollection, obj, List) 
                   {
                       int index = FindClosestClusterCenter(centroidCollection, *obj);
                       resultSet[index].GroupedDocument.Add(*obj);
                   }
                   InitializeClusterCentroid(out centroidCollection, centroidCollection.Count());
                   centroidCollection = CalculateMeanPoints(resultSet);
                   stoppingCriteria = CheckStoppingCriteria(prevClusterCenter, centroidCollection);
                   if (!stoppingCriteria)
                   {   
                       //initialize the result set for next iteration
                       InitializeClusterCentroid(out resultSet, centroidCollection.Count);
                   }
   
   
               } while (stoppingCriteria == false);
   
               _counter = contador;
               return resultSet;
   
           }


           /// <summary>
           /// Genera numeros al azar unicos y verifica que dichos numeros  
           /// se encuentren dentro del numero total de documentos
           /// </summary>
           /// <param name="uniqRand"></param>
           /// <param name="k"></param>
           /// <param name="docCount"></param>
    
           void DocumentClustering::GenerateRandomNumber(vector<int> uniqRand[], int k, int docCount)
           {
               
               srand(time(NULL));
               int aux = k;
               if (k > docCount)
               {
				  aux = docCount;
				}
				do
				{
				  int pos = (rand()%docCount);
				  uniqRand.push_back(pos);

				} while (uniqRand.Count != aux);
			}
  
          /// <summary>
          /// Initialize the result cluster centroid for the next iteration, that holds the result to be returned
          /// </summary>
          /// <param name="centroid"></param>
          /// <param name="count"></param>
          void DocumentClustering::InitializeClusterCentroid(out List<Centroid> centroid,int count)
          {
			  Centroid c;
              list<Centroid> centroid;
              for (int i = 0; i < count; i++)
              {
                  c = new Centroid();
                  c.GroupedDocument = new list<DocumentVector*>();
                  centroid.Add(c);
              }
  
          }
  
          /// <summary>
          /// Chequea el criterio para dejar de iterar, si el centroide no varia su posicion o si el
          /// numero de iteraciones limite llego a su maximo, la iteracion finaliza.
          /// </summary>
          /// <param name="prevClusterCenter"></param>
          /// <param name="newClusterCenter"></param>
          /// <returns></returns>
          bool DocumentClustering::CheckStoppingCriteria(list<Centroid> prevClusterCenter, list<Centroid> newClusterCenter)
          {
              
              contadorGlobal++;
              contador = contadorGlobal;
              if (contadorGlobal > 11000)
              {
                  return true;
              }
             
              else
              {
                  bool stoppingCriteria;
                  int[] changeIndex = new int[newClusterCenter.Count()]; //1 = centroid has moved 0 == centroid do not moved its position
                  
                  int index = 0;
                  do
                  {
                      int count = 0;
                      if (newClusterCenter[index].GroupedDocument.Count == 0 && prevClusterCenter[index].GroupedDocument.Count == 0)
                      {
                          index++;
                      }
                      else if (newClusterCenter[index].GroupedDocument.Count != 0 && prevClusterCenter[index].GroupedDocument.Count != 0)
                      {
                          for (int j = 0; j < newClusterCenter[index].GroupedDocument[0].VectorSpace.Count(); j++)
                          {
                              //
                              if (newClusterCenter[index].GroupedDocument[0].VectorSpace[j] == prevClusterCenter[index].GroupedDocument[0].VectorSpace[j])
                              {
                                  count++;
                              }
  
                          }
  
                          if (count == newClusterCenter[index].GroupedDocument[0].VectorSpace.Count())
                          {
                              changeIndex[index] = 0;
                          }
                          else
                          {
                              changeIndex[index] = 1;
                          }
                          index++;
                      }
                      else
                      {
                          index++;
                          continue;
                          
                      }
                    
  
                  } while (index < newClusterCenter.Count());
  
                  // if index list contains 1 stopping criteria is set to flase
                  if (changeIndex.Where(s => (s != 0)).Select(r => r).Any())
                  {
                      stoppingCriteria = false;
                  }
                  else
                      stoppingCriteria = true;
  
                  return stoppingCriteria;
              }
              
              
          }
  
          //Devuelve el indice del cluster mas cercano
          int DocumentClustering::FindClosestClusterCenter(list<Centroid> clusterCenter,DocumentVector obj)
          {
             
              float[] similarityMeasure = new float[clusterCenter.Count()];
  
              for (int i = 0; i < clusterCenter.Count(); i++)
              {
  
                  similarityMeasure[i] = SimilarityMatrics.FindCosineSimilarity(clusterCenter[i].GroupedDocument[0].VectorSpace, obj.VectorSpace); 
                  
              }
  
              int index = 0;
              float maxValue = similarityMeasure[0];
              for (int i = 0; i < similarityMeasure.Count(); i++)
              {
                  //if document is similar assign the document to the lowest index cluster center to avoid the long loop
                  if (similarityMeasure[i] >maxValue)
                  {
                      maxValue = similarityMeasure[i];
                      index = i;
  
                  }
              }
              return index;
                  
          }
  
          //Reposicionamiento del centroide
          list<Centroid> DocumentClustering::CalculateMeanPoints(list<Centroid> _clusterCenter)
          {
              
              for (int i = 0; i < _clusterCenter.Count(); i++)
              {
                  
                  if (_clusterCenter[i].GroupedDocument.Count() > 0)
                  {
                      
                      for (int j = 0; j < _clusterCenter[i].GroupedDocument[0].VectorSpace.Count(); j++)
                      {
                          float total = 0;
                          
                          DocumentVector vSpace;
						  foreachx(_clusterCenter[i].GroupedDocument, vSpace, List) 
                          {
  
                              total += *vSpace.VectorSpace[j];
                             
                          }
                         
                          //reassign new calculated mean on each cluster center, It indicates the reposition of centroid
                          _clusterCenter[i].GroupedDocument[0].VectorSpace[j] = total / _clusterCenter[i].GroupedDocument.Count();
                         
                      }
                    
                  }
  
              }
            
              return _clusterCenter;
  
          }
}
