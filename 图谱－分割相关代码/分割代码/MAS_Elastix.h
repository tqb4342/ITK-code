#ifndef MAS_Elastix_H
#define MAS_Elastix_H



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


#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIterator.h"

#include "itkBinaryThresholdImageFilter.h"
#include "itkMaskImageFilter.h"
#include "itkStatisticsImageFilter.h"


#include "itkBinaryImageToLabelMapFilter.h"
#include "itkLabelMapToLabelImageFilter.h"
#include "itkLabelStatisticsImageFilter.h"




#include "itkMedianImageFilter.h"
#include "itkBinaryMedianImageFilter.h"


#include "itkOtsuThresholdImageFilter.h"
#include "itkOtsuMultipleThresholdsImageFilter.h"


#include "itkRelabelComponentImageFilter.h"


#include "itkConnectedComponentImageFilter.h"
#include "itkScalarConnectedComponentImageFilter.h"
#include "itkLabelShapeKeepNObjectsImageFilter.h"


#include "itkVotingBinaryIterativeHoleFillingImageFilter.h"


#include "itkBinaryBallStructuringElement.h"
#include "itkBinaryMorphologicalOpeningImageFilter.h"
#include "itkBinaryMorphologicalClosingImageFilter.h"
#include "itkBinaryDilateImageFilter.h"
#include "itkBinaryErodeImageFilter.h"


#include "itkMutualInformationImageToImageMetric.h"
#include "itkMattesMutualInformationImageToImageMetric.h"
#include "itkNormalizedMutualInformationHistogramImageToImageMetric.h"
#include "itkNormalizedCorrelationImageToImageMetric.h"
#include "itkMeanSquaresImageToImageMetric.h"


#include "itkLinearInterpolateImageFunction.h"
#include "itkTranslationTransform.h"

#include "itkNormalizeImageFilter.h"
#include "itkDiscreteGaussianImageFilter.h"

#include "itkRegionOfInterestImageFilter.h"

#include "itkAddImageFilter.h"
#include "itkImageRegionIterator.h"


#include "itkHistogramMatchingImageFilter.h"

#include "itkCastImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"



#include "itkVector.h"
#include "itkListSample.h"

#include "itkGaussianMixtureModelComponent.h"
#include "itkExpectationMaximizationMixtureModelEstimator.h"



 


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// DIM is DEFINED HERE.
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define DIM 3
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



 
bool MAS_Elastix( int numSamples, bool USE_HEALTHY_ATLAS_AS_REF ); 



//---------------------------------------------------------		
// Propagate label image to the input image space.
//---------------------------------------------------------
bool MAS_PropagateLabel_Elastix( int dataIndex );
bool MAS_PropagateLabel_Elastix_Affine( int dataIndex );


//---------------------------------------------------------		
// Calculate the Likelihood image.
//---------------------------------------------------------	
bool calLikelihood( int dataIndex, bool Use_Process_Ori_mask_9par, double PAThreshold);
bool getGaussianParameters( int dataIndex, double &avg, double &std );



//---------------------------------------------------------		
// Get the FINAL MAS result by using MAP theory.
//---------------------------------------------------------		
bool MAP( int dataIndex, bool TUMOR_CASE_USE_PA_EQUAL_ONE); 


 



#endif  //  #ifndef MAS_Elastix_H