class DocumentClustering
       { 
       private:

           int globalCounter;
           int counter;


           //FUNCIONES PRIVADAS
	   bool CheckStoppingCriteria(List<Centroid> prevClusterCenter, List<Centroid> newClusterCenter);
       	   int FindClosestClusterCenter(List<Centroid> clusterCenter,DocumentVector obj);
	   List<Centroid> CalculateMeanPoints(List<Centroid> _clusterCenter);
      	   void FindRSS(List<Centroid> newCentroid, List<Centroid> _clusterCenter);  //NO SE USA EN EL ORIGINAL
      	   void GenerateRandomNumber(ref HashSet<int> uniqRand, int k, int docCount);
	   void InitializeClusterCentroid(out List<Centroid> centroid,int count);
      

      	public:	
       			List<Centroid>PrepareDocumentCluster(int k, List<DocumentVector> documentCollection,ref int _counter);		
    	};


       	List<Centroid> DocumentClustering::PrepareDocumentCluster(int k, List<DocumentVector> documentCollection,ref int _counter){
				
	       globalCounter = 0;
               //prepara k centroides iniciales y asigna un objeto al azar a cada centroide
               List<Centroid> centroidCollection = new List<Centroid>();
               Centroid c;
               
               /*
                * Avoid repeation of random number, if same no is generated more than once same document is added to the next cluster 
                * so avoid it using HasSet collection
                */
               HashSet<int> uniqRand = new HashSet<int>();
               GenerateRandomNumber(ref uniqRand,k,documentCollection.Count);
               
               foreach(int pos in uniqRand) 
               {
                   c = new Centroid();                
                   c.GroupedDocument = new List<DocumentVector>();
                   c.GroupedDocument.Add(documentCollection[pos]);
                   centroidCollection.Add(c);                
               }
   
               bool stoppingCriteria;
               List<Centroid> resultSet;
               List<Centroid> prevClusterCenter;
               
               InitializeClusterCentroid(out resultSet, centroidCollection.Count);
   
               do
               {
                   prevClusterCenter = centroidCollection;
   
                   foreach (DocumentVector obj in documentCollection)
                   {
                       int index = FindClosestClusterCenter(centroidCollection, obj);
                       resultSet[index].GroupedDocument.Add(obj);
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
   
               _counter = counter;
               return resultSet;
   
           }


           /// <summary>
           /// Genera numeros al azar unicos y verifica que dichos numeros  
           /// se encuentren dentro del numero total de documentos
           /// </summary>
           /// <param name="uniqRand"></param>
           /// <param name="k"></param>
           /// <param name="docCount"></param>
    
           void DocumentClustering::GenerateRandomNumber(ref HashSet<int> uniqRand, int k, int docCount)
           {
               
               Random r = new Random();
               
               if (k > docCount)
              {
                  do
                  {
                      int pos = r.Next(0, docCount);
                      uniqRand.Add(pos);
  
                  } while (uniqRand.Count != docCount);
              }            
              else
              {
                  do
                  {
                      int pos = r.Next(0, docCount);
                      uniqRand.Add(pos);
  
                  } while (uniqRand.Count != k);
              }
          }
  
          /// <summary>
          /// Initialize the result cluster centroid for the next iteration, that holds the result to be returned
          /// </summary>
          /// <param name="centroid"></param>
          /// <param name="count"></param>
          void DocumentClustering::InitializeClusterCentroid(out List<Centroid> centroid,int count)
          {
              Centroid c;
              centroid = new List<Centroid>();
              for (int i = 0; i < count; i++)
              {
                  c = new Centroid();
                  c.GroupedDocument = new List<DocumentVector>();
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
          bool DocumentClustering::CheckStoppingCriteria(List<Centroid> prevClusterCenter, List<Centroid> newClusterCenter)
          {
              
              globalCounter++;
              counter = globalCounter;
              if (globalCounter > 11000)
              {
                  return true;
              }
             
              else
              {
                  Boolean stoppingCriteria;
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
          int DocumentClustering::FindClosestClusterCenter(List<Centroid> clusterCenter,DocumentVector obj)
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
          List<Centroid> DocumentClustering::CalculateMeanPoints(List<Centroid> _clusterCenter)
          {
              
              for (int i = 0; i < _clusterCenter.Count(); i++)
              {
                  
                  if (_clusterCenter[i].GroupedDocument.Count() > 0)
                  {
                      
                      for (int j = 0; j < _clusterCenter[i].GroupedDocument[0].VectorSpace.Count(); j++)
                      {
                          float total = 0;
                          
                          foreach (DocumentVector vSpace in _clusterCenter[i].GroupedDocument)
                          {
  
                              total += vSpace.VectorSpace[j];
                             
                          }
                         
                          //reassign new calculated mean on each cluster center, It indicates the reposition of centroid
                          _clusterCenter[i].GroupedDocument[0].VectorSpace[j] = total / _clusterCenter[i].GroupedDocument.Count();
                         
                      }
                    
                  }
  
              }
            
              return _clusterCenter;
  
          }
          


          //ESTO HABRIA QUE SACARLO YA QUE NO ESTA IMPLEMENTADO

          /// <summary>
          /// Find Residual sum of squares it measures how well a cluster centroid represents the member of their cluster
          /// We can use the RSS value as stopping criteria of k-means algorithm when decreses in RSS value falls below a 
          /// threshold t for small t we can terminate the algorithm.
          /// </summary>
          void DocumentClustering::FindRSS(List<Centroid> newCentroid, List<Centroid> _clusterCenter) 
          {
              //TODO:
         }
