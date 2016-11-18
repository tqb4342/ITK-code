#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

#include <Eigen/Dense>
using namespace Eigen;

#include "itkCommandLineArgumentParser.h"


#include "DCELTools.h"
#include "global.h"

#include "utils.h"



#define N 4


bool getShapeVariationVertex();
bool calculateWeights( MatrixXf X, VectorXf& W);

bool shapeVariationVertex2Face();
bool segInfoFace2Vertex( bool SEGED );
bool segInfoFaceViz();



int main(int argc, char * argv[])
{
//------------------------------------------------------------------------------------
//    Get file "shapeVariation_Vertex.csv" from training data.	
//------------------------------------------------------------------------------------	
	getShapeVariationVertex();	

//------------------------------------------------------------------------------------
//    Get "shapeVariation_Face.csv" from file "shapeVariation_Vertex.csv".
//    "shapeVariation_Face.csv" is used in MEPP to segment meshes.
//    ""shapeVariation_Vertex.csv"" is from the output of *ASM*.
//------------------------------------------------------------------------------------	
	shapeVariationVertex2Face();
	return 0;
	
	
	
	
	
	
	
	
	
//------------------------------------------------------------------------------------
// Get Vertex Seg Info from Face Seg Info from *MEPP*.
//------------------------------------------------------------------------------------		
	segInfoFace2Vertex( false );
	
	
//------------------------------------------------------------------------------------
// Get Face seg info for viz!!!
//------------------------------------------------------------------------------------		
	segInfoFaceViz();
	
	
	
	
	/*Vector normal;
	for(DCELFace* fWalker=myMesh->firstFace(); fWalker; myMesh->advance(fWalker)) 
	{
		normal = fWalker->normal;
		printf("%f %f %f\n", normal.x, normal.y, normal.z );
	}*/
	
	
	
    return 0;
}





//**********************************************************************************************************	
//    Get file "shapeVariation_Vertex.csv" from training data.	
//**********************************************************************************************************	
bool getShapeVariationVertex()
{
//************************************************************************************************
// Step I. Prepare Data Matrix.  
//************************************************************************************************
	// -------------------------------------------------------------------------------------------------
	// Ref. http://en.wikipedia.org/wiki/Data_matrix_%28multivariate_statistics%29
	// Ref. http://en.wikipedia.org/wiki/Design_matrix
	//
	// Data Matrix:
	//
	// In multivariate statistics, a *data matrix* is a mathematical matrix of data of dimension n-by-p,
	// where n is the number of samples drawn, and p is the number of variables in each sample.
    //
    // In this representation different rows represent different repetitions of an experiment, 
	// while columns represent different types of data (say, the results from particular probes). 
	// -------------------------------------------------------------------------------------------------
	printf("\n\n*****************************************************************************\n");
	printf("**************************    Prepare Data Matrix!!!    *********************\n");	
	printf("*****************************************************************************\n");
	
	int N2 = 5;  // Number of samples.
	cout << "n = " << N2;
	
	// Number of used features.
	int cols = 0;// = 9;//3*3;  // 3k	
	
	// Open the OFF files.
    char *baseName = "training/liver-";
	int numSuccessFile;	
	MatrixXf X0;  // The Data Matrix.
	bool readFlag = readTrainingData( X0, baseName, N2, cols, numSuccessFile );
	cout << "\np = " << cols << endl;
	
	if( false == readFlag )
	{
		printf("\n\nThere are problems with your FIRST Training Data!!!!!\n\n");
		return 0;		
	}
	
	if( numSuccessFile<2 )
	{
		printf("\n\n(%d) Trainning Data are not successfully read!!!!!\n\n", N-numSuccessFile );
		printf("\n\nSorry!!! We need at least TWO Training Data for ASM to work!!!\n\n");	
		return 0;
	}
	
	if( N2!=numSuccessFile  )
	{
		printf("\n\n(%d) Trainning Data are not successfully read!!!!!\n\n", N-numSuccessFile );
		
		N2 = numSuccessFile;
		X0.conservativeResize( numSuccessFile, Eigen::NoChange );
		cout <<X0.rows() <<" "<< X0.cols() << endl <<endl;		
	}
	else
	{
		printf("\n\nALL Trainning Data are successfully read!!!!!\n\n");
	}	

	//cout << "\nData Matrix X0:[nxp]" << endl << X0.transpose() << endl;
	//saveMatrixX2Off( X0, "result/liverRe-" );	
	
	


	// Calculate weight for every point.
	//???????????????????????????????????????????????????????????????????
	VectorXf W;
	calculateWeights( X0, W );
	//cout << "\n\nWeight Vetor W:\t\n" << endl << W << endl;	
	
	
	// Weight Normalization.
	//printf("\nSum of Weight Vetor W:\t%f\n", W.sum());	
    //W = W/W.sum();	
	//cout << "\n\nWeight Vetor W( After Normalization ):\t\n" << endl << W << endl;
	//printf("\nSum of Weight Vetor W( After Normalization ):\t%f\n", W.sum());
	
	
	
	return true;	
}
//???????????????????????????????????????????????????????????????????
// Calculate weight for every point.
//???????????????????????????????????????????????????????????????????
// The weights can be chosen to give more significance to those points 
// which tend to be most 'stable' over the set - the ones which move 
// about least with respect to the other points in a shape.
//???????????????????????????????????????????????????????????????????
bool calculateWeights( MatrixXf X, VectorXf& W)
{
	int numPoints = X.cols()/3;
	int numSamples = X.rows();
	
	// Change every Shape to a Matrix of numPoints by 3.
	MatrixXf *X1 = new MatrixXf[numSamples];
	for( int i=0; i<numSamples; i++ )
	{
		X1[i] = MatrixXf::Zero( numPoints, 3 );
		
		for( int j=0; j<numPoints; j++ )
		{
			X1[i]( j, 0 ) = X( i, 3*j );
		    X1[i]( j, 1 ) = X( i, 3*j+1 );
		    X1[i]( j, 2 ) = X( i, 3*j+2 );		
		}
	}
	
	
	// Calculate the centroid of every Shape.
	MatrixXf centroid( numSamples, 3 );
	RowVectorXf muS;
	for( int i=0; i<numSamples; i++ )
	{
		muS = X1[i].colwise().mean();
        centroid.row(i) = muS;	
	} 
	//cout << "\n\ncentroid:\t\n" <<endl << centroid << endl;
	
	// Calculate the distance between every Point and 
	// its Shape's centroid for every Shape.
	MatrixXf centroidDist( numSamples, numPoints );
	VectorXf tmp;
	for( int i=0; i<numSamples; i++ )
	{
		for( int j=0; j<numPoints; j++ )
		{
			tmp = X1[i].row(j) - centroid.row(i);
			centroidDist( i, j ) = tmp.norm();				
		}
	}
	//cout << "\n\ncentroidDist:\t\n" <<endl << centroidDist << endl;

	
	// Compute Weight for every point.	
	RowVectorXf muDist = centroidDist.colwise().mean();
	MatrixXf centroidDist2 = centroidDist.rowwise() - muDist;	
	//cout << "\n\ncentroidDist( After centered ):\t\n" <<endl << centroidDist2 << endl;	
	RowVectorXf rDiff = centroidDist2.colwise().squaredNorm();
	//cout << "\n\nrDiff:\n" << rDiff <<endl <<endl;
	
	
	// Compute *SAMPLE* Variance for every point
    // to measure the *Spread* of the source points around its mean.
    // !!!It NEED divided by (numSamples-1).!!! to make an
    // *Unbiased* estimator of the variance of the random variable being sampled.
    // see: http://en.wikipedia.org/wiki/Bessel%27s_correction
    //      Fundamentals of Linear Algebra and Optimization CIS515, Some Notes( P385 ).
	double rVariance;
    W = VectorXf::Zero( numPoints );


    ofstream ofs( "shapeVariation_Vertex.csv" );	
	if( ofs.is_open() )
	{
		ofs << numPoints << endl;
		
	    for( int i=0; i<numPoints; i++ )
	    {
			rVariance = sqrt( rDiff[i]/(double)( numSamples-1 ) );
	        //cout << "\nrVariance:\t" << rVariance <<endl <<endl;	
			ofs << rVariance << endl;
		    //printf("%f\n", rVariance);	
		    W[i] = 1.0/rVariance; 
		    //printf("W[%d]:\t%f\n", i, W[i]);
		}
	}
	else
	{
		printf("\n\nThe Main EigenVectors file \"shapeVariation_Vertex.csv\" can not be read correctly!!!\n\n");
		ofs.close();	
	    return false;
	}
	ofs.close();
    //cout << "\n\nWeight Vetor W:\t\n" << endl << W << endl;	
	
	delete[] X1;
	
	
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Method 2: 
	// Training models of shape from sets of examples(P4) 
	//
	// This Calculation is VERY VERY EXPENSIVE!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*MatrixXf *R = new MatrixXf[numPoints];
	VectorXf tmp;
    for( int i=0; i<numPoints; i++ )
	{
		R[i] = MatrixXf::Zero( numSamples, numPoints );
		for( int j=0; j<numSamples; j++ )
		{
			for( int k=0; k<numPoints; k++ )
	        {
			    tmp = X1[j].row(i) - X1[j].row(k);
				R[i]( j, k ) = tmp.norm();				
			}		
		}			
	}
	
	
	// Compute *SAMPLE* Variance for every point
    // to measure the *Spread* of the source points around its mean.
    // !!!It NEED divided by (numSamples-1).!!! to make an
    // *Unbiased* estimator of the variance of the random variable being sampled.
    // see: http://en.wikipedia.org/wiki/Bessel%27s_correction
    //      Fundamentals of Linear Algebra and Optimization CIS515, Some Notes( P385 ).
	double rVariance;
	VectorXf W( numPoints );
	RowVectorXf muR;
	MatrixXf r2, rDiff;
	for( int i=0; i<numPoints; i++ )
	{
		muR = R[i].colwise().mean();
		r2 = R[i].rowwise() - muR;	
			
		rDiff = r2.colwise().squaredNorm();
	    //cout << "\n\nrDiff:\n" << rDiff <<endl <<endl;
		
	    rVariance = rDiff.sum()/(double)( numSamples-1 );
	    //cout << "\nrVariance:\t" << rVariance <<endl <<endl;	
			
		W[i] = 1/rVariance; 
		//printf("\nW[%d]:\t%f\n", i, W[i]);
	}
    cout << "\n\nWeight Vetor W:\t\n" << endl << W << endl;
	
	delete[] R;
    delete[] X1;*/
	//???????????????????????????????????????????????????????????????????
	//???????????????????????????????????????????????????????????????????
	
	
	return true;
}










//**********************************************************************************************************	
//    Get "shapeVariation_Face.csv" from file "shapeVariation_Vertex.csv".
//    "shapeVariation_Face.csv" is used in MEPP to segment meshes.
//    ""shapeVariation_Vertex.csv"" is from the output of *ASM*.
//**********************************************************************************************************	
bool shapeVariationVertex2Face()
{
	ifstream ifs( "shapeVariation_Vertex.csv" );	
	
	double *vertexVariation;
	int numOfVertex;
	// When the OFF file is successfully opened.
	if( ifs.is_open() ) 
	{
		ifs >> numOfVertex;
		vertexVariation = new double[numOfVertex];
		
		double variation;
		// !!! In Reverse Order!!!
		for( int i=numOfVertex-1; i>-1; i-- )
		{
			ifs >> variation;
		    vertexVariation[i] = variation;	
		}			
	}
	else
	{
		printf("\n\nThe file \"shapeVariation_Vertex.csv\" can not be read correctly!!!\n\n");
		ifs.close();	
	    return 1;
	}
	ifs.close();
	
	for( int i=0; i<numOfVertex; i++ )
	{
		printf("vertexVariation[%d]: %f\n", i, vertexVariation[i]);
	}	
	
	
	
//------------------------------------------------------------------------------------
// II. Tag ALL the Faces.
//------------------------------------------------------------------------------------	
    DCELMesh *myMesh = new DCELMesh();	
	DCELTools::loadFromOFF( "meanShape_liver.off", myMesh );
	int numVertices = myMesh->getNumVertices();
	int numFaces = myMesh->getNumFaces();
	
	int counter = 0;	
	for( DCELVertex*  vWalker=myMesh->firstVertex(); vWalker; myMesh->advance(vWalker) ) 
	{
		int *ID = new int(counter++);
		vWalker->auxData = ID;
		//if( 0 == *ID )
		//{
			//printf("%d  [%f, %f, %f]", *ID, vWalker->coords.x, vWalker->coords.y, vWalker->coords.z);
		//}
	}
	 
	
	DCELHalfEdge* walkerE;	
	int vertexID;	
	double *faceVariation = new double[numFaces];
	
	// In Reverse Order.
	int counterr = numFaces-1;
	for(DCELFace* fWalker=myMesh->firstFace(); fWalker; myMesh->advance(fWalker)) 
	{
		faceVariation[counterr] = 0;
		
		walkerE = fWalker->edge;		
		for( int j=0; j<fWalker->getEdgeCount(); j++ )
		{
			vertexID = *((int*)(walkerE->origin->auxData));
		    faceVariation[counterr] += vertexVariation[vertexID];
			
			walkerE = walkerE->next;            		
		}	
        faceVariation[counterr] = faceVariation[counterr]/(double)( fWalker->getEdgeCount() );
        counterr--;			
	}

	
	for( int i=0; i<numFaces; i++ )
	{
		cout <<  faceVariation[i] << endl;
		//printf("%f\n", faceVariation[i]);
	}		
	
	
	ofstream ofs( "shapeVariation_Face.csv" );	
	
    // When the OFF file is successfully opened.
    if( ofs.is_open() )
	{
		ofs << numFaces << endl;
		
		for( int i=0; i<numFaces; i++ )
	    {
			ofs << faceVariation[i] << endl;			
		}		
	}
	else
	{
		printf("\n\nThe Main EigenVectors file \"shapeVariation_Face.csv\" can not be read correctly!!!\n\n");
		ofs.close();	
		
	    return false;
	}	
	ofs.close();	
				
	
	return true;	
}

















//**********************************************************************************************************	
// Get Vertex Seg Info from Face Seg Info from *MEPP*.
//**********************************************************************************************************
bool segInfoFace2Vertex( bool SEGED )
{	
//************************************************************************************************
// When Vertex SEG Info("labels/v.csv") has *NOT already* been calculated.
//************************************************************************************************
if( !SEGED )
{	
//------------------------------------------------------------------------------------
// I. Get the Seg Info from file "seg.csv".
//    "seg.csv" is from the output of *MEPP*.
//------------------------------------------------------------------------------------	
	ifstream ifs( "seg.csv" );	
	
	int *faceLabel;
	int numOfFace;
	// When the OFF file is successfully opened.
	if( ifs.is_open() ) 
	{
		ifs >> numOfFace;
		faceLabel = new int[numOfFace];
		
		int label;
		// !!! In Reverse Order!!!
		for( int i=numOfFace-1; i>-1; i-- )
		{
			ifs >> label;
		    faceLabel[i] = label;	
		}			
	}
	else
	{
		printf("\n\nThe Seg file \"seg.csv\" can not be read correctly!!!\n\n");
		ifs.close();	
	    return 1;
	}
	ifs.close();
	
	//for( int i=0; i<numOfFace; i++ )
	//{
		//printf("%d\n", faceLabel[i]);
	//}
	
	
//------------------------------------------------------------------------------------
// II. Tag ALL the Faces.
//------------------------------------------------------------------------------------	
    DCELMesh *myMesh = new DCELMesh();	
	DCELTools::loadFromOFF( "meanShape_liver.off", myMesh );
	int numVertices = myMesh->getNumVertices();
	
	int counter = 0;	
	for(DCELFace* fWalker=myMesh->firstFace(); fWalker; myMesh->advance(fWalker)) 
	{
		int *ID = new int(counter++);
		fWalker->auxData = ID;
	}
	
	
//------------------------------------------------------------------------------------
// III. Get Vertex Seg Info.
//------------------------------------------------------------------------------------	
    // Store all the Vertex *ID* for each Label.	
	int *VertexLabel[N];
	for( int i=0; i<N; i++ )
	{
		VertexLabel[i] = new int[numVertices];		
	}	

	
	// Store all the Vertex *Cooords* for each Label.	
	Vector *VertexSeg[N];
	for( int i=0; i<N; i++ )
	{
		VertexSeg[i] = new Vector[numVertices];	
	}	

	
	// Store *Label ID* for each Vertex.	
	int *allVertexLabel = new int[numVertices];
	
	// Store the number of Vertex for each Label.
	int label[N] = {0};
	
	
	int curfaceLabel;
	
	// !!! In Reverse Order!!!
	int counter2 = numVertices;
	
	DCELHalfEdge* walkerE;
	DCELFace* walkerF;
    int faceID;	
	for( DCELVertex*  vWalker=myMesh->firstVertex(); vWalker; myMesh->advance(vWalker) ) 
	{
	//-------------------------------------------------------------
	// Get All the Labels of the Faces *Incident* to this Vertex.
	//-------------------------------------------------------------
		int curLabel[N] = {0};
		
		walkerE = vWalker->leaving;
		walkerF = walkerE->face;
		faceID = *((int*)(walkerF->auxData));
		curfaceLabel = faceLabel[faceID];
		
		curLabel[ curfaceLabel ]++;
   
		walkerE = walkerE->twin->next;
		while( walkerE != vWalker->leaving )
		{
			walkerF = walkerE->face;
		    faceID = *((int*)(walkerF->auxData));
		    curfaceLabel = faceLabel[faceID];
		
		    curLabel[ curfaceLabel ]++;
			
			walkerE = walkerE->twin->next;
		}
		
	//-------------------------------------------------------------
	// Get the Label of current Vertex.
	//-------------------------------------------------------------
		//printf("\n%d %d %d %d", curLabel[0], curLabel[1], curLabel[2], curLabel[3]);
		int maxLabel = 0;
		int maxNumSeg = curLabel[0];
		for( int i=1; i<N ; i++ )
		{
			if( curLabel[i] > maxNumSeg )
			{
			    maxNumSeg = curLabel[i];	
			    maxLabel = i;				
			}				
		}
		allVertexLabel[counter2-1] = maxLabel;
		
	//-------------------------------------------------------------	
	// Add this Vertex to the label info.
	//-------------------------------------------------------------
		VertexLabel[maxLabel][ label[maxLabel] ] = counter2;
		VertexSeg[maxLabel][ label[maxLabel]++ ] = vWalker->coords;		 
		
		counter2--;
	}
	
		
//------------------------------------------------------------------
// IV. Save Vertex Seg Info into file "labels/v.csv".
//------------------------------------------------------------------
    ofstream ofs( "labels/v.csv" );	
	// When the OFF files are successfully opened.
	if( ofs.is_open() ) 
	{		
		// Write File Header.
		ofs << numVertices << "\n"; 
		
		// Save all Vertex Labels.
		for (int i=0; i<numVertices; i++) 
		{
			ofs << allVertexLabel[i] << "\n"; 
		}
	}
	else
	{
		printf("\n\nThe Saved Label file(\"labels/v.csv\") can not be Created Successfully!!!\n\n");
		ofs.close();	
		
		return 1;
	}
	ofs.close();

		
	for( int i=0; i<N; i++ )
	{
		ostringstream ss;
		string datasetFilename;
		
		ss << "labels/l" << i <<".csv";
		datasetFilename = ss.str();
		char *outputFile = new char[datasetFilename.size()+1];
		strcpy( outputFile, datasetFilename.c_str() );
		
		printf("\nOutput File:\t%s\n", outputFile);
		
	    ofstream ofs( outputFile );	
	    // When the OFF files are successfully opened.
	    if( ofs.is_open() ) 
	    {		
		    // Write File Header.
		    ofs << label[i] << "\n"; 
		
		    // Save all the Vertex *ID* for each Label.	
			// !!! In Reverse Order!!!
		    for (int j=label[i]-1; j>-1; j--) 
		    {
			    ofs << VertexLabel[i][j] << "\n"; 
		    }
	    }
	    else
	    {
		    printf("\n\nThe Saved Label file(%s) can not be Created Successfully!!!\n\n", outputFile);
		    ofs.close();	
		
	        return 1;
	    }
	    ofs.close();
	}	
	
	
//-------------------------------------------------------		
// V. Save Seg Info for the file "meanShape_liver.off".	
//-------------------------------------------------------	
	for( int i=0; i<N; i++ )
	{
		ostringstream ss;
		string datasetFilename;
		
		ss << "segs/s" << i <<".off";
		datasetFilename = ss.str();
		char *outputFile = new char[datasetFilename.size()+1];
		strcpy( outputFile, datasetFilename.c_str() );
		
		printf("\nOutput File:\t%s\n", outputFile);
		
	    ofstream ofs( outputFile );	
	    // When the OFF files are successfully opened.
	    if( ofs.is_open() ) 
	    {		
		    // Write File Header.
			ofs << "OFF\n";
			
		    ofs << label[i] <<" " <<0 <<" " <<0 <<"\n"; 
		
		    // Save all the Vertex *Cooords* for each Label.	
			// !!! In Reverse Order!!!
		    for (int j=label[i]-1; j>-1; j--) 
		    {
			    ofs << VertexSeg[i][j].x <<" " << VertexSeg[i][j].y <<" " << VertexSeg[i][j].z << "\n"; 
		    }
	    }
	    else
	    {
		    printf("\n\nThe Saved Label file(%s) can not be Created Successfully!!!\n\n", outputFile);
		    ofs.close();	
		
	        return 1;
	    }
	    ofs.close();
	}

	
	for( int i=0; i<N; i++ )
	{
		printf(" %d ", label[i]);
	}
	
	delete myMesh;
}


//**********************************************************************************************************	
// When Vertex SEG Info( "labels/v.csv" ) has *already* been calculated.
//**********************************************************************************************************
else
{
//------------------------------------------------------------------------------------
// I. Get *Label ID* of each Vertex from file "v.csv".
//------------------------------------------------------------------------------------	
	ifstream ifs( "labels/v.csv" );	
	
	int numVertices;
	int *allVertexLabel;
	// When the OFF file is successfully opened.
	if( ifs.is_open() ) 
	{
		ifs >> numVertices;
		allVertexLabel = new int[numVertices];
		
		int label;
		for( int i=0; i<numVertices; i++ )
		{
			ifs >> label;
		    allVertexLabel[i] = label;	
		}			
	}
	else
	{
		printf("\n\nThe Seg file \"labels/v.csv\" can not be read correctly!!!\n\n");
		ifs.close();	
	    return 1;
	}
	ifs.close();
	
	//for( int i=0; i<numVertices; i++ )
	//{
		//printf("%d\n", allVertexLabel[i]);
	//}	
	
	
//------------------------------------------------------------------------------------
// II. Get the Seg Info for each training file.
//------------------------------------------------------------------------------------		
    for( int i=0; i<50; i++ )
	{
	//--------------------------------------------
	// Get the Seg Info for this training file.
	//--------------------------------------------	
		ostringstream ss;
	    string datasetFilename;
		
		ss << "data/liver-" << i << ".off";
	    datasetFilename = ss.str();
		char *inputFile = new char[datasetFilename.size()+1];
		strcpy( inputFile, datasetFilename.c_str() );
		
	    printf("\n\n\nInput File:\t%s\n\n", inputFile);
		
		
		DCELMesh *myMesh = new DCELMesh();	
	    DCELTools::loadFromOFF( inputFile, myMesh );
	    int numVertices = myMesh->getNumVertices();
		
		
		
		// Store all the Vertex *Cooords* for each Label.	
		Vector *VertexSeg[N];
	    for( int j=0; j<N; j++ )
	    {
		    VertexSeg[j] = new Vector[numVertices];	
	    }	
	
	    // Store the number of Vertex for each Label.
	    int label[N] = {0};
		
		// !!! In Reverse Order!!!
		int counter = numVertices;
		for( DCELVertex*  vWalker=myMesh->firstVertex(); vWalker; myMesh->advance(vWalker) ) 
	    {
			//-------------------------------------------------------------	
	        // Add this Vertex to the label info.
	        //-------------------------------------------------------------
			int maxLabel = allVertexLabel[counter-1];
			VertexSeg[maxLabel][ label[maxLabel]++ ] = vWalker->coords;				     
		
		    counter--;			
		}			
		
	//--------------------------------------------		
	// Save Seg Info for this training file.	
	//--------------------------------------------	
		for( int j=0; j<N; j++ )
	    {
		    ostringstream ss;
		    string datasetFilename;
		
		    ss << "segs/" << i << "-(s" <<j <<").off";
		    datasetFilename = ss.str();
		    char *outputFile = new char[datasetFilename.size()+1];
		    strcpy( outputFile, datasetFilename.c_str() );
		
		    printf("\nOutput File:\t%s\n", outputFile);
		
	        ofstream ofs( outputFile );	
	        // When the OFF files are successfully opened.
	        if( ofs.is_open() ) 
	        {		
		        // Write File Header.
			    ofs << "OFF\n";
			
		        ofs << label[j] <<" " <<0 <<" " <<0 <<"\n"; 
		
		        // Save all the Vertex *Cooords* for each Label.	
				// !!! In Reverse Order!!!
		        for (int k=label[j]-1; k>-1; k--) 
		        {
			        ofs << VertexSeg[j][k].x <<" " << VertexSeg[j][k].y <<" " << VertexSeg[j][k].z << "\n"; 
		        }
	        }
	        else
	        { 
		        printf("\n\nThe Saved Label file(%s) can not be Created Successfully!!!\n\n", outputFile);
		        ofs.close();	
		
	            return 1;
	        }
	        ofs.close();
	    }
			

		for( int i=0; i<N; i++ )
	    {
			delete [] VertexSeg[i];
		}
	
		delete myMesh;
	}
}


	return true;	
}










//**********************************************************************************************************	
// Get Face seg info for viz!!!
//**********************************************************************************************************	
bool segInfoFaceViz()
{
//------------------------------------------------------------------------------------
// I. Get the Seg Info from file "seg.csv".
//    "seg.csv" is from the output of *MEPP*.
//------------------------------------------------------------------------------------	
	ifstream ifs( "seg.csv" );	
	
	int *faceLabel;
	int numOfFace;
	// When the OFF file is successfully opened.
	if( ifs.is_open() ) 
	{
		ifs >> numOfFace;
		faceLabel = new int[numOfFace];
		
		int label;
		// !!! In Reverse Order!!!
		for( int i=numOfFace-1; i>-1; i-- )
		{
			ifs >> label;
		    faceLabel[i] = label;	
		}			
	}
	else
	{
		printf("\n\nThe Seg file \"seg.csv\" can not be read correctly!!!\n\n");
		ifs.close();	
	    return 1;
	}
	ifs.close();
	
	//for( int i=0; i<numOfFace; i++ )
	//{
		//printf("%d\n", faceLabel[i]);
	//}
	
	
//------------------------------------------------------------------------------------
// II. Tag ALL the Faces.
//------------------------------------------------------------------------------------	
    DCELMesh *myMesh = new DCELMesh();	
	DCELTools::loadFromOFF( "meanShape_liver.off", myMesh );
	int numVertices = myMesh->getNumVertices();
	int numFaces = myMesh->getNumFaces();
	
	int counter = 0;	
	for(DCELFace* fWalker=myMesh->firstFace(); fWalker; myMesh->advance(fWalker)) 
	{
		int *ID = new int(counter++);
		fWalker->auxData = ID;
	}	
	int counter2 = 0;	
	for(DCELVertex *vWalker=myMesh->firstVertex();vWalker;myMesh->advance(vWalker) ) 
	{
		int *ID = new int(counter2++);
		vWalker->auxData = ID;
	}
	
	
	ofstream ofs[N];
	int counterFace[N] = {0};
	for( int i=0; i<N; i++ )
	{
		ostringstream ss;
		string datasetFilename;
		
		ss << "segsF/f" << i <<".off";
		datasetFilename = ss.str();
		char *outputFile = new char[datasetFilename.size()+1];
		strcpy( outputFile, datasetFilename.c_str() );
		
		printf("\nOutput File:\t%s\n", outputFile);
		
		ofs[i].open(outputFile); 
	    // When the OFF files are successfully opened.
	    if( ofs[i].is_open() ) 
	    {
			ofs[i] << "OFF\n";
			ofs[i] << numVertices << " " << numFaces << " " << 0 << "\n"; 
			
			for(DCELVertex *vWalker=myMesh->firstVertex();vWalker;myMesh->advance(vWalker) ) 
		    {
				ofs[i] << vWalker->coords.x <<" " << vWalker->coords.y <<" " << vWalker->coords.z << "\n";				
			}			
			
			DCELHalfEdge* walkerE;	
	        int vertexID;	
	        int faceID;
			
	        for(DCELFace* fWalker=myMesh->firstFace(); fWalker; myMesh->advance(fWalker)) 
	        {
				faceID = *((int*)(fWalker->auxData));
				//printf("face \t%d:\t%d\n", faceID, faceLabel[faceID]);
				if( i == faceLabel[faceID] )
				{
					counterFace[i]++;
					
					ofs[i] << 3 << " ";
					walkerE = fWalker->edge;		
		            for( int j=0; j<fWalker->getEdgeCount(); j++ )
		            {
			            vertexID = *((int*)(walkerE->origin->auxData));    
						ofs[i] << vertexID << " ";
						
						walkerE = walkerE->next; 
		            }	
					ofs[i] << "\n";
				}
			}			
			printf("Number of faces for seg %d:\t%d", i, counterFace[i]);
	
		    //ofs << label[i] <<" " <<0 <<" " <<0 <<"\n"; 
		
		    // Save all the Vertex *Cooords* for each Label.	
			// !!! In Reverse Order!!!
		    //for (int j=label[i]-1; j>-1; j--) 
		    //{
			    //ofs << VertexSeg[i][j].x <<" " << VertexSeg[i][j].y <<" " << VertexSeg[i][j].z << "\n"; 
		    //}
	    }
	    else
	    {
		    printf("\n\nThe Saved Label file(%s) can not be Created Successfully!!!\n\n", outputFile);
		    ofs[i].close();	
		
	        return 1;
	    }
	    ofs[i].close();
	}
		
	
	
//------------------------------------------------------------------------------------
// II. Get the Seg Info for each training file.
//------------------------------------------------------------------------------------		
    for( int i=0; i<50; i++ )
	{
	//--------------------------------------------
	// Get the Seg Info for this training file.
	//--------------------------------------------	
		ostringstream ss;
	    string datasetFilename;
		
		ss << "data/liver-" << i << ".off";
	    datasetFilename = ss.str();
		char *inputFile = new char[datasetFilename.size()+1];
		strcpy( inputFile, datasetFilename.c_str() );
		
	    printf("\n\n\nInput File:\t%s\n\n", inputFile);
		
		
		
//------------------------------------------------------------------------------------
// II. Tag ALL the Faces.
//------------------------------------------------------------------------------------	
    DCELMesh *myMesh = new DCELMesh();	
	DCELTools::loadFromOFF( inputFile, myMesh );
	int numVertices = myMesh->getNumVertices();
	
	
	int counter = 0;	
	for(DCELFace* fWalker=myMesh->firstFace(); fWalker; myMesh->advance(fWalker)) 
	{
		int *ID = new int(counter++);
		fWalker->auxData = ID;
	}	
	int counter2 = 0;	
	for(DCELVertex *vWalker=myMesh->firstVertex();vWalker;myMesh->advance(vWalker) ) 
	{
		int *ID = new int(counter2++);
		vWalker->auxData = ID;
	}
	
	
	ofstream ofs[N];
	for( int j=0; j<N; j++ )
	{
		ostringstream ss;
		string datasetFilename;
		
		ss << "segsF/" << i << "-(s" <<j <<").off";
		datasetFilename = ss.str();
		char *outputFile = new char[datasetFilename.size()+1];
		strcpy( outputFile, datasetFilename.c_str() );
		
		printf("\nOutput File:\t%s\n", outputFile);
		
		
		ofs[j].open(outputFile); 
	    // When the OFF files are successfully opened.
	    if( ofs[j].is_open() ) 
	    {
			ofs[j] << "OFF\n";
			ofs[j] << numVertices << " " << counterFace[j] << " " << 0 << "\n"; 
			
			for(DCELVertex *vWalker=myMesh->firstVertex();vWalker;myMesh->advance(vWalker) ) 
		    {
				ofs[j] << vWalker->coords.x <<" " << vWalker->coords.y <<" " << vWalker->coords.z << "\n";				
			}			
			
			DCELHalfEdge* walkerE;	
	        int vertexID;	
	        int faceID;
			
	        for(DCELFace* fWalker=myMesh->firstFace(); fWalker; myMesh->advance(fWalker)) 
	        {
				faceID = *((int*)(fWalker->auxData));
				//printf("face \t%d:\t%d\n", faceID, faceLabel[faceID]);
				if( j == faceLabel[faceID] )
				{
					ofs[j] << 3 << " ";
					walkerE = fWalker->edge;		
		            for( int k=0; k<fWalker->getEdgeCount(); k++ )
		            {
			            vertexID = *((int*)(walkerE->origin->auxData));    
						ofs[j] << vertexID << " ";
						
						walkerE = walkerE->next; 
		            }	
					ofs[j] << "\n";
				}
			}			
	
		    //ofs << label[i] <<" " <<0 <<" " <<0 <<"\n"; 
		
		    // Save all the Vertex *Cooords* for each Label.	
			// !!! In Reverse Order!!!
		    //for (int j=label[i]-1; j>-1; j--) 
		    //{
			    //ofs << VertexSeg[i][j].x <<" " << VertexSeg[i][j].y <<" " << VertexSeg[i][j].z << "\n"; 
		    //}
	    }
	    else
	    {
		    printf("\n\nThe Saved Label file(%s) can not be Created Successfully!!!\n\n", outputFile);
		    ofs[j].close();	
		
	        return 1;
	    }
	    ofs[j].close();
	}
	
	
		delete myMesh;
	}


    return 0;	
}