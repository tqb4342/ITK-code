#ifndef UTILS_H
#define UTILS_H



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;



bool readTrainingData( MatrixXf& X, char *baseName, int numTrainData , int& cols, int& numSuccessFile);
bool readInputShape( char *inputFile, VectorXf& inputShape );



bool savePointSet2Off( VectorXf mu, char *outputFile, char *refFile );
bool saveMatrixX2Off( MatrixXf X, char *baseName );



#endif  //  #ifndef UTILS_H