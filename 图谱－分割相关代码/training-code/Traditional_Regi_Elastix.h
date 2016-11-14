#ifndef Traditional_Regi_Elastix_H
#define Traditional_Regi_Elastix_H



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <time.h>

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;


#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIterator.h"



 

 



//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// DIM is DEFINED HERE.
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define DIM 3
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



bool Traditional_Regi_Elastix( int iterIndex, int numSamples, bool USE_HEALTHY_ATLAS_AS_REF, ofstream &ofs );
 

bool writeLE( MatrixXf &hat, int numTrainData, char *baseName );



#endif  //  #ifndef Traditional_Regi_Elastix_H