//NO EMPEZADO
class SimilarityMatrics{

float FindCosineSimilarity(float[] vecA, float[] vecB){
    var dotProduct = DotProduct(vecA, vecB);
    var magnitudeOfA = Magnitude(vecA);
    var magnitudeOfB = Magnitude(vecB);
    float result = dotProduct / (magnitudeOfA * magnitudeOfB);
    //when 0 is divided by 0 it shows result NaN so return 0 in such case.
    if (float.IsNaN(result))
        return 0;
    else
        return (float)result;
}



float DotProduct(float[] vecA, float[] vecB){
    float dotProduct = 0;
    for (var i = 0; i < vecA.Length; i++)
        dotProduct += (vecA[i] * vecB[i]);
    return dotProduct;
}

// Magnitude of the vector is the square root of the dot product of the vector with itself.
float Magnitude(float[] vector){
    return (float)Math.Sqrt(DotProduct(vector, vector));
}


//Computes the similarity between two documents as the distance between their point representations. Is translation invariant.
float FindEuclideanDistance(int[] vecA, int[] vecB){
    float euclideanDistance = 0;
    for (var i = 0; i < vecA.Length; i++)
        euclideanDistance += (float)Math.Pow((vecA[i] - vecB[i]), 2);

    return (float)Math.Sqrt(euclideanDistance);
}


//Combines properties of both cosine similarity and Euclidean distance
float FindExtendedJaccard(float[] vecA, float[] vecB){
    var dotProduct = DotProduct(vecA, vecB);
    var magnitudeOfA = Magnitude(vecA);
    var magnitudeOfB = Magnitude(vecB);

    return dotProduct / (magnitudeOfA + magnitudeOfB - dotProduct);
}

};
