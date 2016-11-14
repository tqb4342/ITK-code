#include "Traditional_Regi_Elastix.h"



bool Traditional_Regi_Elastix( int iterIndex, int numSamples, bool USE_HEALTHY_ATLAS_AS_REF, ofstream &ofs )
{	
	printf("\n\n*************************************************************************************\n");
	printf("*************************************************************************************\n");
	printf("\nTraditional_Regi Sart!!!\n\n\n");	 
	
	
	
	// The _Index_Atlas_ input image is 
	// employed as the atlas image 
	// for the first iteration.
	const int Index_Atlas = 0;
	
	// The _Index_Atlas_ input image is 
    // employed as the atlas image 
	// for the first iteration.
	bool use_Index_Atlas = true;
	
	
	
	
	
 
	
	
//************************************************************************************************
// Step I. Prepare Data Matrix.  
//************************************************************************************************
	printf("\n\n*****************************************************************************\n");
	printf("**************************    Prepare Data Matrix!!!    *********************\n");	
	printf("*****************************************************************************\n");
	
	int N = numSamples;  // Number of samples.
	cout << "n = " << N <<endl <<endl <<endl;
	
	// Number of used features.
	int cols = 0;// = 9;//3*3;  // 3k	
	
	
	
	//************************************************************************************************
	// Get INPUT Volume. 
	//************************************************************************************************		
	// Some consts.
	const unsigned int  Dimension = DIM;
	typedef short PixelType;
	typedef short OutputPixelType;

	// TYPEDEF's
	typedef itk::Image< PixelType, Dimension >          ImageType;	
	typedef itk::Image< OutputPixelType, Dimension >    OutputImageType;
	typedef ImageType::Pointer                          ImagePointer;	
	typedef OutputImageType::Pointer                    OutputImagePointer;	
	typedef itk::ImageFileReader< ImageType >           ReaderType;

	typedef itk::ImageRegionConstIterator< ImageType >  IteratorType;
    typedef itk::ImageRegionIterator< ImageType >       IteratorTypeRef;





	
// Read image.
int numTrainData = N;

RowVectorXf X0;
for( int i=0; i<numTrainData; i++ )
{
	char *inputFile = NULL;
	if( 0 == iterIndex )
	{
		// The _Index_Atlas_ input image is 
		// employed as the atlas image 
        // for the first iteration.		
		ostringstream ss;
	    string datasetFilename;
	
		if( use_Index_Atlas )
		{
			char *baseName = "training/liver-mask_";	
	        ss << baseName << Index_Atlas << ".nrrd";
		}
		else
		{
		    char *baseName = "training/liver-ref";		     
		    ss << baseName << ".nrrd";
		}
		
		
		datasetFilename = ss.str();
		inputFile = new char[datasetFilename.size()+1];
		strcpy( inputFile, datasetFilename.c_str() );
		printf("\nInput File:\t%s\n\n", inputFile);	
	}
	else
	{
		ostringstream ss;
	    string datasetFilename;
	
	    char *baseName = "REG_UAB/Iter";	
	    ss << baseName << (iterIndex-1) << "_" << i << "_Warped.nrrd";
		datasetFilename = ss.str();
		inputFile = new char[datasetFilename.size()+1];
		strcpy( inputFile, datasetFilename.c_str() );
		printf("\nInput File:\t%s\n\n", inputFile);		
	}
	
	
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName( inputFile );

	try
	{
		reader->Update();
	}
	catch( itk::ExceptionObject & excp )
	{
		std::cerr << "ERROR: caught ITK exception while reading image "
			<< inputFile << "." << std::endl;
		std::cerr << excp << std::endl;
		return 1;
	}

	//typedef short ProcessPixelType;
	//typedef itk::Image< ProcessPixelType, Dimension >      ProcessImageType;

	//typedef itk::RescaleIntensityImageFilter<ImageType, ProcessImageType > RescaleFilterTypeIn;
	//RescaleFilterTypeIn::Pointer rescalerIn = RescaleFilterTypeIn::New();
	//rescalerIn->SetOutputMinimum( 0 );
	//rescalerIn->SetOutputMaximum( 1024*2 );
	//rescalerIn->SetInput( reader->GetOutput() );

	ImagePointer inputImage = reader->GetOutput();




	// Get the spacing.
	ImageType::RegionType region = inputImage->GetLargestPossibleRegion();
	ImageType::SizeType size = region.GetSize();
	int width  = size[0];
	int height = size[1];
	
	int depth = 0;
	if( 2 == Dimension )
	{
		depth = 1;
	}
	else
	{
		depth  = size[2];	
	}
	
	if( 0 == i)
	{
	    printf("Dimension(%d):\t[%d, %d, %d]\n\n", 3, width, height, depth);
	}
	




    if( 0==i )
	{
		cols = width*height*depth;  // 3*k
		//cout << "\np = " << cols << endl;
			
		// Allocate and initialize space for the Data Matrix.
		X0 = RowVectorXf::Zero( cols );
	}
				
 
	IteratorType imageIterator(inputImage, inputImage->GetLargestPossibleRegion());
	int j = 0;
	RowVectorXf mu = RowVectorXf::Zero( cols );
	while( !imageIterator.IsAtEnd() )
    {
        // Get the value of the current pixel.
        float val = imageIterator.Get();

		mu(j++) = val;
        //std::cout << (int)val << std::endl;
 
        ++imageIterator;
    }
	//mu.normalize();
	X0 = X0 + mu;
    
	
	// We ONLY need to read the atlas image
	// in the FIRST iteration.
	if( 0 == iterIndex )
	{
		break;		
	}
}
	cout << "\n\nData Matrix X0:[nxp]" << endl << X0.rows() << "\t" << X0.cols() << endl;



	
	
	
//---------------------------------------------------------	
// Get the mean of input image as the *NEW* atlas image.
//---------------------------------------------------------
    
	MatrixXf A_hat;	
	
    // Get the mean shape.
    VectorXf atlasIm;
    if( 0 == iterIndex )
	{
		// We ONLY need to read the atlas image
	    // in the FIRST iteration.
		A_hat = X0.transpose();
	}
	else
	{
		X0 = X0 / (float)(numTrainData);
		A_hat = X0.transpose();
	}
	atlasIm = A_hat.col( 0 );
	
	
	ostringstream ss4;
	string datasetFilename4;
        
	char *baseName4 = "REG_UAB/Average_UAB_iter";
	ss4 << baseName4 << iterIndex << "-";
	datasetFilename4 = ss4.str();
	char *inputFile4 = new char[datasetFilename4.size()+1];
	strcpy( inputFile4, datasetFilename4.c_str() );
	printf("\natlasIm File:\t%s\n\n", inputFile4);
	char *atlasImFile = inputFile4;	
	
	
	MatrixXf atlasIm2 = MatrixXf::Zero( A_hat.rows(), 1);
	for( int i=0; i<A_hat.rows(); i++ )
	{
		atlasIm2(i, 0) = atlasIm[i];
	}
	
	writeLE( atlasIm2, 1, atlasImFile );
	
	
	
	if( 0 == iterIndex )
	{
		if( use_Index_Atlas )
		{
		    char cmd_CP[512];
		    sprintf(cmd_CP, "cp training/liver-%d.nrrd REG_UAB/Iter0_%d.nrrd & "
		                    "cp REG_UAB/Average_UAB_iter0-0.nrrd REG_UAB/Affine_Iter0_%d_Warped.nrrd & "
						    "cp REG_UAB/Average_UAB_iter0-0.nrrd REG_UAB/Iter0_%d_Warped.nrrd & ", 
		                    Index_Atlas, Index_Atlas, Index_Atlas, Index_Atlas);
						  
		    int ret = system( cmd_CP );  
            printf("\ncmd_CP:\t%d\n", ret);	
		}			
	}	
 



 

    // Last iteration No Registration!!!
    if( 4 == iterIndex )
	{
		return 0;
	}

	
	
	
	
	
	
	
	
	
	

//---------------------------------------------------------
// Register input images to the atlas(average) image.
//---------------------------------------------------------


//******************************************************************************************************
//******************************************************************************************************
// Registration Parameters!!!
//******************************************************************************************************
//******************************************************************************************************
    //const unsigned int Dimension = DIM;

//----------------------------------------------------------------------------------
//  antsRegistration
//
//  This program is a user-level registration application meant to utilize 
//  ITKv4-only classes. The user can specify any number of "stages" where a stage 
//  consists of a transform; an image metric; and iterations, shrink factors, and 
//  smoothing sigmas for each level.Note that dimensionality, metric, transform, 
//  output, convergence, shrink-factors and smoothing-sigmas parameters are mandatory. 
//----------------------------------------------------------------------------------
    char *EXE_REGISTER = "./elastix";


	
    char *fixedIm = NULL;
    if( USE_HEALTHY_ATLAS_AS_REF )
	{
		fixedIm = "training/healthy_atlas.nrrd";
	}
	else
	{
		ostringstream ss4;
	    string datasetFilename4;
        
	    char *baseName4 = "REG_UAB/Average_UAB_iter";
	    ss4 << baseName4 << iterIndex << "-0.nrrd";
	    datasetFilename4 = ss4.str();
	    char *inputFile4 = new char[datasetFilename4.size()+1];
	    strcpy( inputFile4, datasetFilename4.c_str() );
	    printf("\nfixedIm File:\t%s\n\n", inputFile4);
		
	    fixedIm = inputFile4;	
	}
//******************************************************************************************************
//******************************************************************************************************

	
//******************************************************************************************************************
//******************************************************************************************************************
	// Register all others to mean.
	const bool FixedAsMoving = false;
	const bool FirstIterationAffine = false;
	
	

//******************************************************************************************************************	
//******************************************************************************************************************
    for( int i=0; i<numSamples; i++ )
	{
		
		if( use_Index_Atlas )
		{
			if( (Index_Atlas==i) && (0==iterIndex) )
	        {
		        continue;		
	        }
		}
	
	
	
        
		
		char *movingIm_Affine = NULL;
		bool NON_GREEDY = true;
		if( NON_GREEDY || (0 == iterIndex)  )
		{
			// NON_GREEDY ALWAYS use the *ORIGINAL* input images
			// to perform registration.
			ostringstream ss;
	        string datasetFilename;
	
	        char *baseName = "training/liver-mask_";	
	        ss << baseName << i << ".nrrd";
		    datasetFilename = ss.str();
		    char *inputFile = new char[datasetFilename.size()+1];
		    strcpy( inputFile, datasetFilename.c_str() );
		    printf("\nmovingIm File2:\t%s\n\n", inputFile);
		
            movingIm_Affine = inputFile;			
		}
		else			
		{
			// GREEDY ALWAYS use the *PREVIOUS* input images
			// to perform registration.
		    ostringstream ss;
		    string datasetFilename;
		
		    char *baseName = "REG_UAB/Iter";
	        ss << baseName << (iterIndex-1) << "-" << i << "_Warped.nrrd";
		    datasetFilename = ss.str();
		    char *inputFile = new char[datasetFilename.size()+1];
		    strcpy( inputFile, datasetFilename.c_str() );
		    printf("\nmovingIm File:\t%s\n\n", inputFile);
		
            movingIm_Affine = inputFile;
		}

		
        
		
		
		//----------------------------------------------------------------------------------
		//  -o, --output outputTransformPrefix
		//
        //  [outputTransformPrefix,<outputWarpedImage>,<outputInverseWarpedImage>]
		//  Specify the output transform prefix (output format is .nii.gz ). Optionally, one 
		//  can choose to warp the moving image to the fixed space and, if the inverse 
		//  transform exists, one can also output the warped fixed image. Note that only the 
		//  images specified in the first metric call are warped. Use antsApplyTransforms to 
		//  warp other images using the resultant transform(s). 
		//----------------------------------------------------------------------------------
		/*ostringstream ss2;
		string datasetFilename2;
		
		char *baseName2 = "REG_UAB/Iter";
		ss2 << baseName2 << iterIndex << "_" << i << "_";
		datasetFilename2 = ss2.str();
		char *inputFile2 = new char[datasetFilename2.size()+1];
		strcpy( inputFile2, datasetFilename2.c_str() );
		printf("\noutputTransformPrefix File:\t%s\n\n", inputFile2);
		char *outputTransformPrefix = inputFile2;*/
		
		
		
		char *parameters_Affine = "./parameters_Affine.txt";
		char *parameters_BSpline = "./parameters_BSpline.txt";
   
		
		char cmd_ELASTIX[512];
		
		
		
		if( 0 == iterIndex )
		{
			if ( !FixedAsMoving )
			{
			    // We ONLY perform AFFINE transform 
	            // in the FIRST iteration to avoid
			    // BIG bias towards the _Index_Atlas_ input image.
			    //sprintf(cmd_ELASTIX, "%s -f %s -m %s -out REG_UAB/tmp -p %s", 
		                          //EXE_REGISTER, fixedIm, movingIm_Affine, parameters_Affine);
			
				
				if( FirstIterationAffine )
				{
					sprintf(cmd_ELASTIX, "%s -f %s -m %s -out REG_UAB/tmp -p %s", 
		                                  EXE_REGISTER, fixedIm, movingIm_Affine, 
				                          parameters_Affine);
				}
				else
				{
					sprintf(cmd_ELASTIX, "%s -f %s -m %s -out REG_UAB/tmp -p %s -p %s ", 
		                                 EXE_REGISTER, fixedIm, movingIm_Affine, 
							             parameters_Affine, parameters_BSpline);					
				}
			}
			else  // For Inversely registeration (i.e. Exchange FixIm and MovingIm).
			{
				
				if( FirstIterationAffine )
				{
					sprintf(cmd_ELASTIX, "%s -f %s -m %s -out REG_UAB/tmp -p %s", 
		                                  EXE_REGISTER, movingIm_Affine, fixedIm, 
				                          parameters_Affine);
				}
				else
				{
					sprintf(cmd_ELASTIX, "%s -f %s -m %s -out REG_UAB/tmp -p %s -p %s ", 
		                                  EXE_REGISTER, movingIm_Affine, fixedIm,  
                                          parameters_Affine, parameters_BSpline);
				}
			}
		}
		else  // if( 0 != iterIndex )
		{
			if ( !FixedAsMoving )
			{
				sprintf(cmd_ELASTIX, "%s -f %s -m %s -out REG_UAB/tmp -p %s -p %s ", 
		                             EXE_REGISTER, fixedIm, movingIm_Affine, 
							         parameters_Affine, parameters_BSpline);
			}
			else
			{
				// For Inversely registeration (i.e. Exchange FixIm and MovingIm).
                sprintf(cmd_ELASTIX, "%s -f %s -m %s -out REG_UAB/tmp -p %s -p %s ", 
		                              EXE_REGISTER, movingIm_Affine, fixedIm,  
                                      parameters_Affine, parameters_BSpline);	
			}				
		}
        		

        //char *cmd = "./elastix -f exampleinput/liver-mask_1.nrrd -m exampleinput/liver-mask_2.nrrd -out exampleoutput -p exampleinput/parameters_Affine.txt -p exampleinput/parameters_BSpline.txt";
	
	    //char temp[512];
        //sprintf(temp, "ls -%s -%s > test.txt ", "a", "l");
	
        int ret = system( cmd_ELASTIX );  
        printf("\ncmd_ELASTIX:\t%d\n", ret);
		
		
		
		
		
		
		
		char cmd_POST[512];
        /*sprintf(cmd_POST, "mkdir REG_UAB/%d & " 
						  "mv REG_UAB/result.0.nrrd REG_UAB/liver_AFFINE-%d.nrrd & "
						  "mv REG_UAB/result.1.nrrd REG_UAB/liver-%d.nrrd & "
                          "mv REG_UAB/*.* REG_UAB/%d/ & "
						  "mv REG_UAB/%d/Average_UAB_iter0-0.nrrd REG_UAB/Average_UAB_iter0-0.nrrd",
						  i, i, i, i, i);*/
		
		
		if( 0 == iterIndex )
		{
			// We ONLY perform AFFINE transform 
	        // in the FIRST iteration to avoid
			// BIG bias towards the _Index_Atlas_ input image.
			//sprintf(cmd_POST, "cp REG_UAB/tmp/result.0.nrrd REG_UAB/Affine_Iter%d_%d_Warped.nrrd & "
						      //"mv REG_UAB/tmp/result.0.nrrd REG_UAB/Iter%d_%d_Warped.nrrd & ",
						      //iterIndex, i, iterIndex, i);
			
			
			if( FirstIterationAffine )
			{
			    sprintf(cmd_POST, "mv REG_UAB/tmp/TransformParameters.0.txt REG_UAB/Affine_Iter%d_%d.txt & " 
							      "mv REG_UAB/tmp/result.0.nrrd REG_UAB/Iter%d_%d_Warped.nrrd & ",
							       iterIndex, i, iterIndex, i);
			}
			else
			{
				sprintf(cmd_POST, "mv REG_UAB/tmp/TransformParameters.0.txt REG_UAB/Affine_Iter%d_%d.txt & "
                                  "mv REG_UAB/tmp/TransformParameters.1.txt REG_UAB/BSpline_Iter%d_%d.txt & "
			                      "mv REG_UAB/tmp/result.0.nrrd REG_UAB/Affine_Iter%d_%d_Warped.nrrd & "
						          "mv REG_UAB/tmp/result.1.nrrd REG_UAB/Iter%d_%d_Warped.nrrd & ",
						          iterIndex, i, iterIndex, i, iterIndex, i, iterIndex, i);				
			}			
		}
		else  // if( 0 != iterIndex )
		{
		    sprintf(cmd_POST, "mv REG_UAB/tmp/TransformParameters.0.txt REG_UAB/Affine_Iter%d_%d.txt & "
                              "mv REG_UAB/tmp/TransformParameters.1.txt REG_UAB/BSpline_Iter%d_%d.txt & "
			                  "mv REG_UAB/tmp/result.0.nrrd REG_UAB/Affine_Iter%d_%d_Warped.nrrd & "
						      "mv REG_UAB/tmp/result.1.nrrd REG_UAB/Iter%d_%d_Warped.nrrd & ",
						      iterIndex, i, iterIndex, i, iterIndex, i, iterIndex, i);
		}
						  
		int ret2 = system( cmd_POST );  
        printf("\ncmd_POST:\t%d\n", ret2);		
			
		
	}





	printf("\n\nTraditional_Regi End!!!\n");
	printf("*************************************************************************************\n");
	printf("*************************************************************************************\n\n");
	
	return true;	
}











bool writeLE( MatrixXf &hat, int numTrainData, char *baseName )
{		
	// Read image.
	MatrixXf L = hat.transpose();
	

	// Some consts.
	const unsigned int  Dimension = DIM;
	typedef short PixelType;
	typedef short OutputPixelType;

	// TYPEDEF's
	typedef itk::Image< PixelType, Dimension >          ImageType;	
	typedef itk::Image< OutputPixelType, Dimension >    OutputImageType;
	typedef ImageType::Pointer                          ImagePointer;	
	typedef OutputImageType::Pointer                    OutputImagePointer;	
	typedef itk::ImageFileReader< ImageType >           ReaderType;

	typedef itk::ImageRegionConstIterator< ImageType >  IteratorType;
    typedef itk::ImageRegionIterator< ImageType >       IteratorTypeRef;
	typedef short WritePixelType;
    typedef itk::Image< WritePixelType, Dimension >      WriteImageType;
    typedef itk::ImageFileWriter< WriteImageType >       WriterType;
	
	
	
for( int i=0; i<numTrainData; i++ )
{
	ReaderType::Pointer readerRef = ReaderType::New();
	
	
//**************************************************************************************************
//**************************************************************************************************
	readerRef->SetFileName( "training/liver-mask_0.nrrd" );
	//readerRef->SetFileName( "training/liver-ref.nrrd" );
//**************************************************************************************************
//**************************************************************************************************	
	
	
	try
	{
		readerRef->Update();
	}
	catch( itk::ExceptionObject & excp )
	{
		std::cerr << "ERROR: caught ITK exception while reading image "
			<< "training/liver-0.mhd" << "." << std::endl;
		std::cerr << excp << std::endl;
		return 1;
	}

	//typedef short ProcessPixelType;
	//typedef itk::Image< ProcessPixelType, Dimension >      ProcessImageType;

	//typedef itk::RescaleIntensityImageFilter<ImageType, ProcessImageType > RescaleFilterTypeIn;
	//RescaleFilterTypeIn::Pointer rescalerIn = RescaleFilterTypeIn::New();
	//rescalerIn->SetOutputMinimum( 0 );
	//rescalerIn->SetOutputMaximum( 1024*2 );
	//rescalerIn->SetInput( reader->GetOutput() );

	ImagePointer inputImageRef = readerRef->GetOutput();


   
	IteratorTypeRef imageIteratorRef(inputImageRef, inputImageRef->GetLargestPossibleRegion());
	int j = 0;

	while( !imageIteratorRef.IsAtEnd() )
    {
        // Set the current pixel to white
		float val = L(i, j++);
		int val2 = (int)( val );
        imageIteratorRef.Set( val2 );
 
        ++imageIteratorRef;
    }
	
	
	// Write the output image. 
	ostringstream ss;
	string datasetFilename;
	
	//char *baseName2= "LRR/liverLRR-";	
	ss << baseName << i << ".nrrd";
	datasetFilename = ss.str();
	char *outputFile = new char[datasetFilename.size()+1];
	strcpy( outputFile, datasetFilename.c_str() );
		
	printf("\nOutput File:\t%s", outputFile);
		
	
	
    WriterType::Pointer writer = WriterType::New();
    writer->SetInput( inputImageRef );
    writer->SetFileName( outputFile );
    try
    {
	    writer->Update();
    } 
    catch( itk::ExceptionObject & excp )
    { 
	    std::cerr << "ERROR: caught ITK exception while writing image "
		<< "" << "Snake3D_refined.nrrd" << std::endl;
	    std::cerr << excp << std::endl;
	    return 2;
    }
}
}
