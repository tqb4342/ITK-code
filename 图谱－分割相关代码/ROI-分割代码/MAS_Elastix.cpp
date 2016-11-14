#include "MAS_Elastix.h"
 
 






bool MAS_Elastix( int numSamples, bool USE_HEALTHY_ATLAS_AS_REF )
{	
	printf("\n\n*************************************************************************************\n");
	printf("*************************************************************************************\n");
	printf("\nMAS_Elastix Sart!!!\n\n\n");	
	
	
	

//*************************************************************************************************************
// Register the PAs to the target images.
//*************************************************************************************************************
	

//******************************************************************************************************
//******************************************************************************************************
// Registration Parameters!!!
//******************************************************************************************************
//******************************************************************************************************
    const unsigned int Dimension = DIM;

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




	const bool FixedAsMoving = true;
	const bool useBSpline = true;
	
	
	
	
	
	
	
	bool TUMOR_CASE_USE_PA_EQUAL_ONE = false;
	bool Use_Process_Ori_mask_9par = false;
	
	
	
	
	
	double PAThreshold = 0.2;
//******************************************************************************************************************	
    for( int i=0; i<numSamples; i++ )
	//for( int i=numSamples-1; i<numSamples; i++ )
	{
		if( 10 == i ||
		    11 == i )
		{
			continue;
		}		

		//calLikelihood( i, Use_Process_Ori_mask_9par, PAThreshold);
		//MAP( i, TUMOR_CASE_USE_PA_EQUAL_ONE);		
		//continue;
		
		
		
		
		
		char cmd_RMM[512];		
		sprintf(cmd_RMM, "rm MAS/tmp/*.* & "
						 "rm MAS/tmp2/*.* ");
						  
		int ret_RMM = system( cmd_RMM );  
        printf("\nret_RMM:\t%d\n", ret_RMM);		
		
		
		
		char fixedIm[128];
        if( USE_HEALTHY_ATLAS_AS_REF )
	    {
			sprintf(fixedIm, "training/healthy_atlas.nrrd");
	  	    //fixedIm = "training/healthy_atlas.nrrd";
	    }
	    else
	    {
			sprintf(fixedIm, "training/avg.nrrd");
			
	 	    printf("\nfixedIm File:\t%s\n\n", fixedIm);
	    }	
	
	
		
		char *movingIm_Affine = NULL;
		{
			// NON_GREEDY ALWAYS use the *ORIGINAL* input images
			// to perform registration.
			ostringstream ss;
	        string datasetFilename;
	        
			// Using the new LRSDed target image. 
	        char *baseName = NULL;	
			baseName = "training/liver-";
			
	        ss << baseName << i << ".nrrd";
		    datasetFilename = ss.str();
		    char *inputFile = new char[datasetFilename.size()+1];
		    strcpy( inputFile, datasetFilename.c_str() );
		    printf("\nmovingIm File2:\t%s\n\n", inputFile);
		
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
		
		char *parameters_Affine = "./parameters_Affine.txt";
		char *parameters_BSpline = "./parameters_BSpline.txt";
   
		
		char cmd_ELASTIX[512];
		
		
		
		 
		if( !FixedAsMoving )
		{
			if( useBSpline )
			{
				sprintf(cmd_ELASTIX, "%s -f %s -m %s -out MAS/tmp -p %s -p %s ", 
								  EXE_REGISTER, fixedIm, movingIm_Affine, 
							      parameters_Affine, parameters_BSpline);				
			}
			else
			{
				sprintf(cmd_ELASTIX, "%s -f %s -m %s -out MAS/tmp -p %s ", 
								  EXE_REGISTER, fixedIm, movingIm_Affine, 
							      parameters_Affine);				
			}			
		}
		else
		{
			if( useBSpline )
			{
				// For Inversely registeration (i.e. Exchange FixIm and MovingIm).
			    sprintf(cmd_ELASTIX, "%s -f %s -m %s -out MAS/tmp -p %s -p %s ", 
		                              EXE_REGISTER, movingIm_Affine, fixedIm,  
                                      parameters_Affine, parameters_BSpline);				
			}
			else
			{
				// For Inversely registeration (i.e. Exchange FixIm and MovingIm).
			    sprintf(cmd_ELASTIX, "%s -f %s -m %s -out MAS/tmp -p %s ", 
		                              EXE_REGISTER, movingIm_Affine, fixedIm,  
                                      parameters_Affine);				
			}				
		}				
		
        
	
        int ret = system( cmd_ELASTIX );  
        printf("\ncmd_ELASTIX:\t%d\n", ret);
		
		
		
		
		
		
		
		char cmd_POST[512];
		
		
		if( useBSpline )
		{
			sprintf(cmd_POST, "cp MAS/tmp/TransformParameters.0.txt MAS/%d/Affine_avg.txt & "
						      "cp MAS/tmp/TransformParameters.1.txt MAS/%d/BSpline_avg.txt & "
			                  "mv MAS/tmp/result.0.nrrd MAS/%d/Affine_avg_Warped.nrrd & "
						      "mv MAS/tmp/result.1.nrrd MAS/%d/avg_Warped.nrrd & ",
						      i, i, i, i);	
		}
		else
		{
			sprintf(cmd_POST, "cp MAS/tmp/TransformParameters.0.txt MAS/%d/Affine_avg.txt & "
			                  "mv MAS/tmp/result.0.nrrd MAS/%d/avg_Warped.nrrd & ",
						      i, i);		
		}
        		
 
		
						  
		int ret2 = system( cmd_POST );  
        printf("\ncmd_POST:\t%d\n", ret2);
		
	 
		
		
		
		
		
		
//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************

//---------------------------------------------------------		
// Propagate label image to the input image space.
//---------------------------------------------------------
        bool flag = true;
        if( useBSpline )
		{
			flag = MAS_PropagateLabel_Elastix( i );
			
		//---------------------------------------------------------------------------				
		// For Special Cases that 
		// MAS_PropagateLabel_Elastix( i )
		// MAY FAILLLLLL! 	
        //---------------------------------------------------------------------------			
			char warpedFile[128]; 
			sprintf(warpedFile, "MAS/%d/avg_mask_Warped.nrrd", i);
	
			ifstream warpedFileStream; 
			warpedFileStream.open( warpedFile, std::ifstream::in );
			
			bool warpFlagFail = true;
			while( warpFlagFail )
			{
				// When the warped file is exist.
				if( warpedFileStream.good() )
				{
					printf("\n\n%s IS EXIST!!!\n\n", warpedFile);
					warpedFileStream.close();
			
					warpFlagFail = false;
				}
				else
				{
					printf("\n\n%s ISN'T EXIST!!!\n\n", warpedFile);
					warpFlagFail = true;
					warpedFileStream.close();
			
					// When the warped file isn't exist,
					// we REDO the MAS_PropagateMaskTransformToOriImage_Elastix().
					MAS_PropagateLabel_Elastix( i );
					warpedFileStream.open( warpedFile, std::ifstream::in );
				}	    
			}
		}
		else
		{
			flag = MAS_PropagateLabel_Elastix_Affine( i );

		//---------------------------------------------------------------------------				
		// For Special Cases that 
		// MAS_PropagateLabel_Elastix_Affine( i )
		// MAY FAILLLLLL! 	
        //---------------------------------------------------------------------------			
			char warpedFile[128]; 
			sprintf(warpedFile, "MAS/%d/avg_mask_Warped.nrrd", i);
	
			ifstream warpedFileStream; 
			warpedFileStream.open( warpedFile, std::ifstream::in );
			
			bool warpFlagFail = true;
			while( warpFlagFail )
			{
				// When the warped file is exist.
				if( warpedFileStream.good() )
				{
					printf("\n\n%s IS EXIST!!!\n\n", warpedFile);
					warpedFileStream.close();
			
					warpFlagFail = false;
				}
				else
				{
					printf("\n\n%s ISN'T EXIST!!!\n\n", warpedFile);
					warpFlagFail = true;
					warpedFileStream.close();
			
					// When the warped file isn't exist,
					// we REDO the MAS_PropagateMaskTransformToOriImage_Elastix().
					MAS_PropagateLabel_Elastix_Affine( i );
					warpedFileStream.open( warpedFile, std::ifstream::in );
				}	    
			}			
		}
		
		
		
		
		
		
		
//---------------------------------------------------------		
// Calculate the Likelihood image.
//---------------------------------------------------------		
		flag = calLikelihood( i, Use_Process_Ori_mask_9par, PAThreshold);
		
		
//---------------------------------------------------------		
// Get the FINAL MAS result by using MAP theory.
//---------------------------------------------------------			
		flag = MAP( i, TUMOR_CASE_USE_PA_EQUAL_ONE );
		
//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************
	}
	
	
	
	
	
//******************************************************************************************	
//******************************************************************************************
// Reconstruct ROI to original size!!!	
//******************************************************************************************		
//******************************************************************************************	
	char *inputROIFile = "roi.txt";
	printf("\n\nInput File:\t%s\n", inputROIFile);		
	ifstream ifs( inputROIFile );
	
	
	int startX, endX, startY, endY, startZ, endZ;
	
	const int numFile = 20;
	int initialIndex = 0;
	
	int startXs[numFile], startYs[numFile], startZs[numFile];
	int endXs[numFile], endYs[numFile], endZs[numFile];
	
for( int ii=initialIndex; ii<initialIndex+numFile; ii++ )
{
	if( ifs.is_open() )
	{
		ifs >> startXs[ii] >> startYs[ii] >> startZs[ii] 
		    >> endXs[ii] >> endYs[ii]  >> endZs[ii];
	}
	else
	{
		printf("\n\nThe File \"%s\" can not be read correctly!!!\n\n");
			
		ifs.close();	
		return 1;
	}
	 
}
	ifs.close();




 
const int numFile2 = 20;
int initialIndex2 = 0;
for( int ii=initialIndex2; ii<initialIndex2+numFile2; ii++ )
{
	//5-0
		/*if( 3 ==ii ||
			7 ==ii )
		{
			continue;
		}*/
 
		
		
		
	printf("%d:\t%d, %d, %d, %d, %d, %d\n\n", ii, 
		  startXs[ii], startYs[ii], startZs[ii], 
	      endXs[ii], endYs[ii], endZs[ii]);
	
	
	typedef itk::Image<char, 3>  ImageType_Short;
    typedef itk::ImageFileReader<ImageType_Short> ReaderType_Short;
	
	char inputFINALFile[128];
	sprintf(inputFINALFile, "MAS/%d/FINALLL.nrrd", ii);	
	
	ReaderType_Short::Pointer readerF = ReaderType_Short::New();
    readerF->SetFileName( inputFINALFile );
	readerF->Update();
	
	
	ImageType_Short::ConstPointer inputImage = readerF->GetOutput();
	
	ImageType_Short::RegionType region = inputImage->GetLargestPossibleRegion();
	ImageType_Short::SizeType size = region.GetSize();
	int width  = size[0];
	int height = size[1];
	int depth  = size[2];	
	printf("\nDimension(%d):\t[%d, %d, %d]\n", 3, width, height, depth);
	
    ImageType_Short::PointType origin = inputImage->GetOrigin();
    ImageType_Short::SpacingType spacing = inputImage->GetSpacing();
    ImageType_Short::DirectionType direction = inputImage->GetDirection();



// Original image 
	ImageType_Short::Pointer emptyImage = ImageType_Short::New();
	ImageType_Short::RegionType region2;
    ImageType_Short::IndexType start2;
    start2[0] = 0;
    start2[1] = 0;
	start2[2] = 0;
 
    ImageType_Short::SizeType size2;
    size2[0] = 512;
	size2[1] = 512;	
	size2[2] = depth;
	
 
    region2.SetSize(size2);
    region2.SetIndex(start2);
 
    emptyImage->SetRegions(region2);
    emptyImage->Allocate();
	emptyImage->FillBuffer( 0 );
	
	
	
// Restore image info	
	typedef itk::ChangeInformationImageFilter< ImageType_Short > FilterType;
    FilterType::Pointer filter = FilterType::New();    
	
	//filter->SetReferenceImage( inputImage );
	//filter->SetUseReferenceImage( true );	
	
	filter->SetOutputSpacing( spacing );
    filter->ChangeSpacingOn();
	
	filter->SetOutputOrigin( origin );
    filter->ChangeOriginOn();
	
	filter->SetOutputDirection( direction );
    filter->ChangeDirectionOn();
	
	filter->SetInput( emptyImage );
	
	
	
// start pasting		
	typedef itk::PasteImageFilter <ImageType_Short, ImageType_Short > PasteImageFilterType;
 
    // The SetDestinationIndex() method prescribes where in the first
    // input to start pasting data from the second input.
    // The SetSourceRegion method prescribes the section of the second
    // image to paste into the first. 
    ImageType_Short::IndexType destinationIndex;
    //destinationIndex[0] = 0;
    //destinationIndex[1] = 0;
	//destinationIndex[2] = 0;
	
	
	destinationIndex[0] = startXs[ii];
    destinationIndex[1] = startYs[ii];
	destinationIndex[2] = 0;
 
    PasteImageFilterType::Pointer pasteFilter = PasteImageFilterType::New();
    pasteFilter->SetSourceImage( inputImage );
    pasteFilter->SetDestinationImage( filter->GetOutput() );
    pasteFilter->SetSourceRegion( inputImage->GetLargestPossibleRegion() );
    pasteFilter->SetDestinationIndex( destinationIndex );
	
	
	
	
	char inputFINALFile2[128];
	sprintf(inputFINALFile2, "MAS/%d/FINALLLL.nrrd", ii);	
	
	typedef itk::ImageFileWriter< ImageType_Short >  WriterType;
    WriterType::Pointer writer = WriterType::New();
    writer->SetInput( pasteFilter->GetOutput() );
    writer->SetFileName( inputFINALFile2 );

    try
    {
        writer->Update();
    }
    catch( itk::ExceptionObject & excep )
    {
        std::cerr << "Exception catched !" << std::endl;
        std::cerr << excep << std::endl;
    }
}
//******************************************************************************************	
//******************************************************************************************
// Reconstruct ROI to original size ENDs!!!	
//******************************************************************************************		
//******************************************************************************************
    


	printf("\n\nMAS_Elastix End!!!\n");
	printf("*************************************************************************************\n");
	printf("*************************************************************************************\n\n");
	
	return true;	
}








 









bool MAS_PropagateLabel_Elastix( int dataIndex )
{
	    char *EXE_WarpImage = "./transformix";		
		
	    char InputImage[128];
	    sprintf(InputImage, "training/avg_mask.nrrd", dataIndex);

 		
	    char newInputImage[128];
	    sprintf(newInputImage, "MAS/%d/avg_mask_Warped.nrrd", dataIndex);
        
	
	
	
	//---------------------------------------------------------------------------
    // Change TransformParameters.0.txt and TransformParameters.1.txt
	// to _char_ type to propagate the label image.
	//---------------------------------------------------------------------------
	    char affineFile[128];
	    char bSplineFile[128];
	
	    sprintf(affineFile, "MAS/%d/Affine_avg.txt", dataIndex);		
		sprintf(bSplineFile, "MAS/%d/BSpline_avg.txt", dataIndex);
					

		
		
	    char cmd_COPY[512];		
		sprintf(cmd_COPY, "cp %s MAS/tmp/Affine.txt & "
						  "cp %s MAS/tmp/BSpline.txt ", affineFile, bSplineFile);
						  
		int ret = system( cmd_COPY );  
        printf("\ncmd_POST:\t%d\n", ret);
		
		char cmd_RM[512];		
		sprintf(cmd_RM, "rm MAS/tmp/TransformParameters.0.txt & "
						"rm MAS/tmp/TransformParameters.1.txt ");
						  
		int ret2 = system( cmd_RM );  
        printf("\ncmd_RM:\t%d\n", ret2);
		
	    
	    char *inputFileAffine = "MAS/tmp/Affine.txt";
	    char *outputFileAffine = "MAS/tmp/TransformParameters.0.txt";
	    ifstream ifsAffine( inputFileAffine );	
		ofstream ofsAffine( outputFileAffine );
		// When the OFF file is successfully opened.
        if( ifsAffine.is_open() && ofsAffine.is_open() )
	    {
			string inputLine;
			for( int j=0; j<27; j++ )
	        {
				getline( ifsAffine, inputLine );
                
				ofsAffine << inputLine << endl;
				
			    //cout << endl << inputLine << endl;
		    }

            ofsAffine << "(DefaultPixelValue 0)" << endl;
			ofsAffine << "(ResultImageFormat \"nrrd\")" << endl;
			ofsAffine << "(ResultImagePixelType \"float\")" << endl;
			ofsAffine << "(CompressResultImage \"false\")" << endl;    
		}
		else
	    {
		    printf("\n\nThe File \"%s and %s\" can not be read correctly!!!\n\n", inputFileAffine, outputFileAffine);
			
		    ifsAffine.close();	
			ofsAffine.close();
	        return 1;
	    }       
		
		ifsAffine.close();
		ofsAffine.close();
	
	
	
	
		char *inputFileBSpline = "MAS/tmp/BSpline.txt";
	    char *outputFileBSpline = "MAS/tmp/TransformParameters.1.txt";
		ifstream ifsBSpline( inputFileBSpline );	
		ofstream ofsBSpline( outputFileBSpline );
		// When the OFF file is successfully opened.
        if( ifsBSpline.is_open() && ofsBSpline.is_open() )
	    {
			string inputLine;
			for( int j=0; j<33; j++ )
	        {
				getline( ifsBSpline, inputLine );
                
				ofsBSpline << inputLine << endl;
				
			    //cout << endl << inputLine << endl;
		    }

            ofsBSpline << "(DefaultPixelValue 0)" << endl;
			ofsBSpline << "(ResultImageFormat \"nrrd\")" << endl;
			ofsBSpline << "(ResultImagePixelType \"float\")" << endl;
			ofsBSpline << "(CompressResultImage \"false\")" << endl;    
		}
		else
	    {
		    printf("\n\nThe File \"%s and %s\" can not be read correctly!!!\n\n", inputFileBSpline, outputFileBSpline);
			
		    ifsBSpline.close();	
			ofsBSpline.close();
	        return 1;
	    }
		
		ifsBSpline.close();
		ofsBSpline.close();	
		
		
		
		
		
	
	    char *SeriesOfTransformations = "MAS/tmp2/TransformParameters.1.txt";
	
        char cmd_Transformix[512];
	    sprintf(cmd_Transformix, "cp MAS/tmp/TransformParameters.1.txt MAS/tmp2/TransformParameters.1.txt & " 
		                         "%s -out MAS/tmp2 -tp %s -in %s ", 
								 EXE_WarpImage, SeriesOfTransformations, InputImage);
		

        	
        int ret3 = system( cmd_Transformix );  
        printf("\ncmd_Transformix:\t%d\n", ret3); 




        char cmd_POST2[512];

		sprintf(cmd_POST2, "mv MAS/tmp2/result.nrrd %s ", newInputImage);
						  
		int ret4 = system( cmd_POST2 );  
        printf("\ncmd_POST2:\t%d\n", ret4);				
	
	
	
	return true;	
}



bool MAS_PropagateLabel_Elastix_Affine( int dataIndex )
{
	    char *EXE_WarpImage = "./transformix";		
		
	    char InputImage[128];
	    sprintf(InputImage, "MAS/%d/avg_mask.nrrd", dataIndex);

 		
	    char newInputImage[128];
	    sprintf(newInputImage, "MAS/%d/avg_mask_Warped.nrrd", dataIndex);
        
	
	
	
	//---------------------------------------------------------------------------
    // Change TransformParameters.0.txt 
	// to _char_ type to propagate the label image.
	//---------------------------------------------------------------------------
	    char affineFile[128];
	    sprintf(affineFile, "MAS/%d/Affine_avg.txt", dataIndex);		
	
	    char cmd_COPY[512];		
		sprintf(cmd_COPY, "cp %s MAS/tmp/Affine.txt ", affineFile);
						  
		int ret = system( cmd_COPY );  
        printf("\ncmd_POST:\t%d\n", ret);
		
		
		
		char cmd_RM[512];		
		sprintf(cmd_RM, "rm MAS/tmp/TransformParameters.0.txt ");
						  
		int ret2 = system( cmd_RM );  
        printf("\ncmd_RM:\t%d\n", ret2);
		
		
	    
	    char *inputFileAffine = "MAS/tmp/Affine.txt";
	    char *outputFileAffine = "MAS/tmp/TransformParameters.0.txt";
	    ifstream ifsAffine( inputFileAffine );	
		ofstream ofsAffine( outputFileAffine );
		// When the OFF file is successfully opened.
        if( ifsAffine.is_open() && ofsAffine.is_open() )
	    {
			string inputLine;
			for( int j=0; j<27; j++ )
	        {
				getline( ifsAffine, inputLine );
                
				ofsAffine << inputLine << endl;
				
			    //cout << endl << inputLine << endl;
		    }

            ofsAffine << "(DefaultPixelValue 0)" << endl;
			ofsAffine << "(ResultImageFormat \"nrrd\")" << endl;
			ofsAffine << "(ResultImagePixelType \"float\")" << endl;
			ofsAffine << "(CompressResultImage \"false\")" << endl;    
		}
		else
	    {
		    printf("\n\nThe File \"%s and %s\" can not be read correctly!!!\n\n", inputFileAffine, outputFileAffine);
			
		    ifsAffine.close();	
			ofsAffine.close();
	        return 1;
	    }
		
		ifsAffine.close();
		ofsAffine.close();
	 
		
		
		
	
	    char *SeriesOfTransformations = "MAS/tmp2/TransformParameters.0.txt";
	
        char cmd_Transformix[512];
	    sprintf(cmd_Transformix, "cp MAS/tmp/TransformParameters.0.txt MAS/tmp2/TransformParameters.0.txt & " 
		                         "%s -out MAS/tmp2 -tp %s -in %s ", 
								 EXE_WarpImage, SeriesOfTransformations, InputImage);
		

        	
        int ret3 = system( cmd_Transformix );  
        printf("\ncmd_Transformix:\t%d\n", ret3); 




        char cmd_POST2[512];
		sprintf(cmd_POST2, "mv MAS/tmp2/result.nrrd %s ", newInputImage);
						  
		int ret4 = system( cmd_POST2 );  
        printf("\ncmd_POST2:\t%d\n", ret4);				
	
	
	
	return true;	
}









//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************	
// Calculate the Likelihood image.
//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************
bool calLikelihood( int dataIndex, bool Use_Process_Ori_mask_9par, double PAThreshold)
{
	const int Dim = 3;
	typedef itk::Image<short, Dim>  ImageType;
	typedef itk::Image<float, Dim>  ImageTypeFloat;
	typedef itk::ImageFileReader<ImageType> ReaderType;
    typedef itk::ImageFileReader<ImageTypeFloat> ReaderTypeFloat;
	typedef itk::ImageRegionIterator< ImageType > IteratorType;
	
	
	char inputFile[128];
	sprintf(inputFile, "MAS/%d/avg_mask_Warped.nrrd", dataIndex);
	
 
    ReaderTypeFloat::Pointer reader = ReaderTypeFloat::New();
    reader->SetFileName( inputFile );
	reader->Update();	
	
 
    
	
	typedef itk::ImageRegionIterator<ImageTypeFloat> IteratorType_Float;
	
	ImageTypeFloat::Pointer inputImage = reader->GetOutput();
	IteratorType_Float imageIterator_Float(inputImage, inputImage->GetLargestPossibleRegion());
	

    while( !imageIterator_Float.IsAtEnd() )
    {
		float val = imageIterator_Float.Get();
		
		//if( val >= 0.9 )
		//if( val >= 0.2 )			
		if( val >= PAThreshold )
		{
			imageIterator_Float.Set( 1.0 );		
		}
		else
		{
			imageIterator_Float.Set( 0.0 );
		}
		
		++imageIterator_Float;
	}
		
		
	
		
	char newInputImage[128];
	sprintf(newInputImage, "MAS/%d/avg_mask_Warped_Threshold.nrrd", dataIndex);
		
	typedef itk::ImageFileWriter< ImageTypeFloat > WriterType;

	// Write the output image. 
	WriterType::Pointer writer = WriterType::New();    
	//writer->SetInput( thresholdFilter->GetOutput() );
	writer->SetInput( inputImage );
	writer->SetFileName( newInputImage );
	try
	{
		writer->Update();
	}
	catch( itk::ExceptionObject & excp )
	{
		std::cerr << "ERROR: caught ITK exception while writing image "
			<< "gradient.nrrd" << "." << std::endl;
		std::cerr << excp << std::endl;
		return 2;
	}	
	
	
	
	
	
	
	
	
	
	
	
	
	
	typedef itk::Image<short, Dim>  ImageType_Short;
    typedef itk::ImageFileReader<ImageType_Short> ReaderType_Short;
	
	
	
	
	ostringstream ss2;
	string datasetFilename2;
	
	char *baseName2 = "training/liver-";	
    ss2 << baseName2 << dataIndex << ".nrrd";
	datasetFilename2 = ss2.str();
	char *inputFile2 = new char[datasetFilename2.size()+1];
	strcpy( inputFile2, datasetFilename2.c_str() );
	printf("\ninputFile2:\t%s\n\n", inputFile2);		

    ReaderType_Short::Pointer reader_Short = ReaderType_Short::New();
	reader_Short->SetFileName( inputFile2 );
	reader_Short->Update();
			
			
	typedef itk::MaskImageFilter< ImageType_Short, ImageTypeFloat > MaskFilterType;
	
	MaskFilterType::Pointer maskFilter = MaskFilterType::New();
	maskFilter->SetInput1( reader_Short->GetOutput() );
	//maskFilter->SetInput2( thresholdFilter->GetOutput() );
	maskFilter->SetInput2( inputImage );
	maskFilter->SetOutsideValue( -1024 );
	//maskFilter->Print(std::cout);

	
	
	char newInputImage2[128];
	
	
	if( Use_Process_Ori_mask_9par )
	{
	    sprintf(newInputImage2, "MAS/%d/Ori_mask_9par_Ori.nrrd", dataIndex);
	}
	else
	{
		sprintf(newInputImage2, "MAS/%d/Ori_mask_9par.nrrd", dataIndex);		
	}
	
	typedef itk::ImageFileWriter< ImageType_Short >       WriterType_Short;

	// Write the output image. 
	WriterType_Short::Pointer writer_Short = WriterType_Short::New();    
	writer_Short->SetInput( maskFilter->GetOutput() );
	writer_Short->SetFileName( newInputImage2 );
	try
	{
		writer_Short->Update();
	}
	catch( itk::ExceptionObject & excp )
	{
		std::cerr << "ERROR: caught ITK exception while writing image "
			<< "gradient.nrrd" << "." << std::endl;
		std::cerr << excp << std::endl;
		return 2;
	}




    
if( Use_Process_Ori_mask_9par )
{
//---------------------------------------------------------------------	
// Step 1. Median Filter.
//---------------------------------------------------------------------	
    typedef itk::MedianImageFilter<ImageType_Short,ImageType_Short> MedianFilterType;
    MedianFilterType::Pointer medianFilter = MedianFilterType::New();
	
	const int radiusValue = 3;
	MedianFilterType::InputSizeType radius_MedianFilter;
	radius_MedianFilter.Fill( radiusValue );

    medianFilter->SetRadius( radius_MedianFilter );
    medianFilter->SetInput( maskFilter->GetOutput() ); 	
		
		
//---------------------------------------------------------------------	
// Step 2. Otsu Thresholding Filter.
//---------------------------------------------------------------------			
//typedef itk::OtsuThresholdImageFilter <ImageType, ImageType> OtsuFilterType;
	typedef itk::OtsuMultipleThresholdsImageFilter <ImageType_Short, ImageType_Short> OtsuFilterType;
	OtsuFilterType::Pointer otsuFilter = OtsuFilterType::New();
	otsuFilter->SetInput( medianFilter->GetOutput() );
	//otsuFilter->SetOutsideValue( 1 );
	//otsuFilter->SetInsideValue( 0 );
	otsuFilter->SetNumberOfThresholds( 2 );
	
	
	otsuFilter->Update();
	//double threshold = otsuFilter->GetThreshold();
	//std::cout << "\n\nThreshold [OtsuThresholdImageFilter]:\t" << threshold << std::endl;
		
	OtsuFilterType::ThresholdVectorType thresholds = otsuFilter->GetThresholds();    
	printf("\n\nOtsuMultipleThresholdsImageFilter:\n");		
	for (unsigned int i = 0; i < thresholds.size(); i++)
	{
		cout << endl << itk::NumericTraits<OtsuFilterType::InputPixelType>::PrintType(thresholds[i]) << " ";
	}
	
	
	
	
	
	
	
	    ImageType::Pointer relabelFilterImage = otsuFilter->GetOutput();		
		
		ImageType::RegionType region = relabelFilterImage->GetLargestPossibleRegion();	
		itk::ImageRegionIterator<ImageType_Short> imageIterator( relabelFilterImage, region );
 
	    short val = 0;
        while( !imageIterator.IsAtEnd() )
        {
            // Get the value of the current pixel
            val = imageIterator.Get();
			
			// Label #0 is assumed to be the background 
			// and is left unaltered by the relabeling.
			// Ref: http://www.itk.org/Doxygen/html/classitk_1_1RelabelComponentImageFilter.html
//*******************************************************************************************************************
//*******************************************************************************************************************
//*******************************************************************************************************************
            //if( 1 == val )
			if( 2 == val )
		    {
				imageIterator.Set( 1 );				
		    }
			else
			{
				imageIterator.Set( 0 );	
			}
 
            ++imageIterator;
        }
		
		
		
		
		
		
		
	typedef itk::ConnectedComponentImageFilter <ImageType_Short, ImageType_Short > CCFilterType;
 
	CCFilterType::Pointer connectedFilter = CCFilterType::New ();
	connectedFilter->SetInput( relabelFilterImage );
	connectedFilter->Update(); 
	std::cout << "\n\nNumber of objects: " << connectedFilter->GetObjectCount() << std::endl << std::endl;
 
	typedef itk::LabelShapeKeepNObjectsImageFilter< ImageType_Short > LabelShapeKeepNObjectsFilterType;
	LabelShapeKeepNObjectsFilterType::Pointer labelShapeFilter = LabelShapeKeepNObjectsFilterType::New();
	labelShapeFilter->SetInput( connectedFilter->GetOutput() );
	labelShapeFilter->SetBackgroundValue( 0 );
	labelShapeFilter->SetNumberOfObjects( 1 );
	labelShapeFilter->SetAttribute( LabelShapeKeepNObjectsFilterType::LabelObjectType::NUMBER_OF_PIXELS );
		
		
	
	
	
	
 
	typedef itk::MaskImageFilter< ImageType_Short, ImageType_Short > MaskFilterType2;
	MaskFilterType2::Pointer maskFilter2 = MaskFilterType2::New();
	maskFilter2->SetInput1( reader_Short->GetOutput() );
	//maskFilter->SetInput2( thresholdFilter->GetOutput() );
	maskFilter2->SetInput2( labelShapeFilter->GetOutput() );
	maskFilter2->SetOutsideValue( -1024 );
	//maskFilter->Print(std::cout);
	
		
		
	// Write the output image.	
	char otsuFilterFile[128];	
	sprintf(otsuFilterFile, "MAS/%d/Ori_mask_9par.nrrd", dataIndex);		

	
	typedef itk::ImageFileWriter< ImageType_Short > WriterType_Short2;
	
	WriterType_Short2::Pointer writer_Short2 = WriterType_Short2::New();    
	writer_Short2->SetInput( maskFilter2->GetOutput() );
	writer_Short2->SetFileName( otsuFilterFile );
	try
	{
		writer_Short2->Update();
	}
	catch( itk::ExceptionObject & excp )
	{
		std::cerr << "ERROR: caught ITK exception while writing image "
				  << "gradient.nrrd" << "." << std::endl;
		std::cerr << excp << std::endl;
		return 2;
	}		
}
	







	
	

	
	
//--------------------------------------------------------------------------
// Assuming the liver internsity value are distributed as 
// Gaussian distribution.
// We estimate its [avg, std] using EM algorithm.
//--------------------------------------------------------------------------		
	double avg, std;
	getGaussianParameters( dataIndex, avg, std );
	printf("\n\n[avg1, std1]:\t[%f, %f]\n\n", avg, std);	
	
	
	
	
	typedef itk::CastImageFilter< ImageType_Short, ImageTypeFloat > CastFilterType;
	CastFilterType::Pointer firstCastfilter = CastFilterType::New();
    firstCastfilter->SetInput( reader_Short->GetOutput() );
	firstCastfilter->Update();
	
	
	ImageTypeFloat::Pointer inputFloatImage = firstCastfilter->GetOutput();
	
	
	
	ImageTypeFloat::RegionType region_InputFloat = inputFloatImage->GetLargestPossibleRegion();	
	itk::ImageRegionIterator<ImageTypeFloat> imageIterator3( inputFloatImage, region_InputFloat );

//---------------------------------------------------------------------
// Without Gaussian Normalize Factor.  
//---------------------------------------------------------------------	
	double val1, val2;
	//int val3;
	while( !imageIterator3.IsAtEnd() )
    {
        // Get the value of the current pixel
        val1 = imageIterator3.Get();
		//printf("\nval1:\t%f\n", val1);
        val2 = exp( -(val1 - avg)*(val1 - avg)/(2*std) );
		//printf("\nval2:\t%f\n", val2);
		//val3 = (int)( val2*100 );
		imageIterator3.Set( val2 );
		
        ++imageIterator3;
    }

	
	
	
	
		
	char newInputImage3[128];
	sprintf(newInputImage3, "MAS/%d/Ori_Likelihood.nrrd", dataIndex);
	printf("\nnewInputImage3 File:\t%s\n", newInputImage3);
	
	
    // Write the output image. 
    typedef itk::Image< float, 3 > OutputImageTypeFloat;
	typedef itk::ImageFileWriter< OutputImageTypeFloat >  WriterTypeFloat;
	
	WriterTypeFloat::Pointer writer_Float2 = WriterTypeFloat::New();    
	writer_Float2->SetInput( inputFloatImage );
	writer_Float2->SetFileName( newInputImage3 );
	try
	{
		writer_Float2->Update();
	}
	catch( itk::ExceptionObject & excp )
	{
		std::cerr << "ERROR: caught ITK exception while writing image "
			<< "gradient.nrrd" << "." << std::endl;
		std::cerr << excp << std::endl;
		return 2;
	}	
	
	
	
	return true;
}



bool getGaussianParameters( int dataIndex, double &avg, double &std )
{
	// Some consts.
	const unsigned int  Dimension = 3;
	typedef short PixelType;


	// TYPEDEF's
	typedef itk::Image< PixelType, Dimension > ImageType;
    typedef ImageType::Pointer ImagePointer;		
	typedef itk::ImageFileReader<ImageType> ReaderInputType; 
	
	
	// Read the masked original image.
	char inputFile[128];
	sprintf(inputFile, "MAS/%d/Ori_mask_9par.nrrd", dataIndex);
	printf("Input File:\t%s\n", inputFile);
	
	
	ReaderInputType::Pointer readerInput = ReaderInputType::New();
	readerInput->SetFileName( inputFile );
	readerInput->Update();

 
	typedef itk::ImageRegionIterator< ImageType >       IteratorType;
	
	
	
	
	
	
//----------------------------------------------------------------------------------
// Step 1:
// Esimate Initial Gaussian Parameters (i.e. avg, std) for EM Initialization.
// _avg_ is the intensity value that has the maximum peak in the histogram.
//----------------------------------------------------------------------------------
	
	ImagePointer inputImage = readerInput->GetOutput();
	IteratorType imageIterator(inputImage, inputImage->GetLargestPossibleRegion());
	IteratorType imageIterator2(inputImage, inputImage->GetLargestPossibleRegion());
	
	double max, min;
	int counter = 0;
	while( !imageIterator.IsAtEnd() )
    {
		float val = imageIterator.Get();
		
		if( 0==counter )
		{
			min = 1e5;
			max = val;
		}
		
		if( -1024 != val )
		{
		    if( val<min )
		    {
			    min = val;
		    }
		}
		
		if( val>max )
		{
			max = val;
		}
				
		++imageIterator;		
		counter++;
	}
	printf("[min, max]:\t[%f, %f]\n", min, max);
	
	if( -1024>min )
	{
		min = -1023;
		printf("[min2, max]:\t[%f, %f]\n", min, max);
	}
		
	
	
	// Allocate space to store histogram.
	int numBins = max - min + 1;
	int *histogram = new int [numBins];
	for( int i=0; i<numBins; i++ )
	{
		histogram[i] = 0;
	}
	
	
	
	
	while( !imageIterator2.IsAtEnd() )
    {
        // Get the value of the current pixel.
        short val = imageIterator2.Get();
		
		if( val>=min )
		{
		    val = val - min;
		    histogram[ val ]++;	
		}			
 
        ++imageIterator2;
    }
	
	
	
	
	// Get the maximum frequency of the histogram.
	int maxFrequencyBinIndex;
	int maxFrequency = 0;
	for(int i=0; i<numBins; i++)
	{
		if( histogram[i]>maxFrequency )
		{
			maxFrequencyBinIndex = i + min;
			maxFrequency = histogram[i];
		}
	}
	printf("MAX Frequency[%d]:\t%d\n\n", maxFrequencyBinIndex, maxFrequency);
	
	
	// Initial Gaussian Parameters for EM Initialization.
	double GaussianParameters[2];
	// avg.
	GaussianParameters[0] = maxFrequencyBinIndex;
	// std.
	// 3*sigma = 20.
	GaussianParameters[1] = (20/3)*(20/3);
	/*int indexTmp = maxFrequencyBinIndex - min - 20;
	int threeSigma = maxFrequency - histogram[indexTmp];
	GaussianParameters[1] = (threeSigma/3)*(threeSigma/3);*/
	
	
	
	
	
	// Create the histogram image and initialize it as a white image.
	ImageType::Pointer histogramImage = ImageType::New();
	
	
	ImageType::RegionType region;
    ImageType::IndexType start;
    start[0] = 0;
    start[1] = 0;
	start[2] = 0;
 
    ImageType::SizeType size;
    size[0] = numBins;
	size[1] = numBins;
	size[2] = 1;
 
    region.SetSize(size);
    region.SetIndex(start);
 
    histogramImage->SetRegions( region );
    histogramImage->Allocate();
	histogramImage->FillBuffer( 6500 );
	
	
	// Calculate the display value of the histogram 
	// as (histogram[i]/maxFrequency)*numBins.
	ImageType::IndexType pixelIndex;
	
	int data = 0;
	for(int i=0; i<numBins; i++)
	{
		data = (int)( ((float)histogram[i]/(float)maxFrequency)*(float)numBins );

		for(int j=0; j<data; j++)
		{
			pixelIndex[0] = i;
		    pixelIndex[1] = numBins-j-1;
		    pixelIndex[2] = 0;
			
			histogramImage->SetPixel( pixelIndex, -1024 );	
		}
	}
	
  

// Write the histogram image. 
	typedef itk::ImageFileWriter< ImageType >       WriterType;

	// Write the output image. 
	char outputFile[128];
	sprintf(outputFile, "MAS/%d/Ori_mask_9par_histogram.nrrd", dataIndex);
	printf("Output File:\t%s\n", outputFile);	
	
	WriterType::Pointer writer = WriterType::New();    
	writer->SetInput( histogramImage );
	writer->SetFileName( outputFile );
	try
	{
		writer->Update();
	}
	catch( itk::ExceptionObject & excp )
	{
		std::cerr << "ERROR: caught ITK exception while writing image "
			<< "gradient.nrrd" << "." << std::endl;
		std::cerr << excp << std::endl;
		return NULL;
	}
	
	
	
	
	
	
	
	
	
	
//----------------------------------------------------------------------------------
// Step 2:
// Assuming the liver internsity value are distributed as 
// Gaussian distribution.
// Esimate Gaussian Parameters (i.e. avg, std) using EM Initialization.
//----------------------------------------------------------------------------------
	
	IteratorType imageIterator3(inputImage, inputImage->GetLargestPossibleRegion());
	IteratorType imageIterator4(inputImage, inputImage->GetLargestPossibleRegion());
	
	int numVoxels = 0;
	printf("\n\nnumVoxels:\t%d\n\n", numVoxels);
	while( !imageIterator3.IsAtEnd() )
    {
		short val = imageIterator3.Get();
		
		if( -1024 != val )
		{
			numVoxels++;
		}
		
		++imageIterator3;
	}

	
	int *voxelValues = new int[numVoxels];
	
	int counter2 = 0;
	while( !imageIterator4.IsAtEnd() )
    {
        // Get the value of the current pixel.
        short val = imageIterator4.Get();
		
		if( -1024 != val )
		{
		    voxelValues[ counter2++ ] = val;
		}			
 
        ++imageIterator4;
    }
	printf("\n\nnumVoxels:\t%d\n\n", numVoxels);
	//printf("\n\nvoxelValues[%d]:\t%d\n\n", numVoxels, voxelValues[numVoxels-1]);

	
	
	
	
	unsigned int numberOfClasses = 1;
    typedef itk::Vector< int, 1 > MeasurementVectorType;
    typedef itk::Statistics::ListSample< MeasurementVectorType > SampleType;
    SampleType::Pointer sample = SampleType::New();	
	// length of measurement vectors
    sample->SetMeasurementVectorSize( 1 ); 
	
	
	MeasurementVectorType mv;
	for(int i=0; i<numVoxels; i++)
	{
		//printf("\nvoxelValues[%d]:\t%d", i, voxelValues[i]);
		mv[0] = voxelValues[i];				
		sample->PushBack( mv );
		//cout << "\nmv[0]:\t" << mv[0];
	}
	
	
	
	
	typedef itk::Array< double > ParametersType;
    ParametersType params( 2 );
    std::vector< ParametersType > initialParameters( numberOfClasses );
    params[0] = GaussianParameters[0];
    params[1] = GaussianParameters[1];
	
	initialParameters[0] = params;
	
	
	typedef itk::Statistics::GaussianMixtureModelComponent< SampleType > ComponentType;
    std::vector< ComponentType::Pointer > components;
    for ( unsigned int i=0; i<numberOfClasses; i++ )
    {
        components.push_back( ComponentType::New() );
        ( components[i] )->SetSample( sample );
        ( components[i] )->SetParameters( initialParameters[i] );
    }
	
	
	
	typedef itk::Statistics::ExpectationMaximizationMixtureModelEstimator<SampleType > EstimatorType;
	EstimatorType::Pointer estimator = EstimatorType::New();
    estimator->SetSample( sample );
    estimator->SetMaximumIteration( 200 );
	
	
    itk::Array< double > initialProportions( numberOfClasses );
    initialProportions[0] = 0.9;
    estimator->SetInitialProportions( initialProportions );
	
    for ( unsigned int i=0; i<numberOfClasses; i++)
    {
        estimator->AddComponent( (ComponentType::Superclass*)(components[i]).GetPointer() );
    }
    estimator->Update();
	
	
	
	for ( unsigned int i=0; i<numberOfClasses; i++ )
    {
        std::cout << "\n\nCluster[" << i << "]" << std::endl;
        std::cout << " Parameters:\t";
        std::cout << " " << (components[i])->GetFullParameters() << std::endl;
        std::cout << " Proportion: ";
		std::cout << " " << estimator->GetProportions()[i] << std::endl;
    }
	
	
	ParametersType finalParameters = (components[0])->GetFullParameters();
	avg = finalParameters[0];
	std = finalParameters[1];
	
	printf("\n\n[avg0, std0]:\t[%f, %f]\n\n", avg, std);
	
	
	
	delete [] histogram;
	delete [] voxelValues;
	
	
	
	return true;
}










//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************
// Get the FINAL MAS result by using MAP theory.
//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************
bool MAP( int dataIndex, bool TUMOR_CASE_USE_PA_EQUAL_ONE)
{
	const int Dim = 3;
	typedef itk::Image<short, Dim>  ImageType;
    typedef itk::ImageFileReader<ImageType> ReaderType;
	
	typedef itk::Image<short, Dim>  ImageType_Short;
    typedef itk::ImageFileReader<ImageType_Short> ReaderType_Short;
	
	typedef itk::Image<float, Dim>  ImageTypeFloat;
    typedef itk::ImageFileReader<ImageTypeFloat> ReaderTypeFloat;
	
		

    char inputPAFile[128];
	sprintf(inputPAFile, "MAS/%d/avg_mask_Warped.nrrd", dataIndex);	
	
	ReaderTypeFloat::Pointer reader_PA = ReaderTypeFloat::New();
    reader_PA->SetFileName( inputPAFile );
	reader_PA->Update();
	
	
	
	
	
	char inputLikelihoodFile[128];
	sprintf(inputLikelihoodFile, "MAS/%d/Ori_Likelihood.nrrd", dataIndex);	
	
	ReaderTypeFloat::Pointer reader_Likelihood = ReaderTypeFloat::New();
    reader_Likelihood->SetFileName( inputLikelihoodFile );
	reader_Likelihood->Update();
	
	
	
	ImageTypeFloat::Pointer PAImage = reader_PA->GetOutput();	
	ImageTypeFloat::RegionType region_PA= PAImage->GetLargestPossibleRegion();	
	itk::ImageRegionIterator<ImageTypeFloat> imageIterator_PA( PAImage, region_PA );
	
	
	ImageTypeFloat::Pointer LikelihoodImage = reader_Likelihood->GetOutput();	
	ImageTypeFloat::RegionType region_Likelihood = LikelihoodImage->GetLargestPossibleRegion();	
	itk::ImageRegionIterator<ImageTypeFloat> imageIterator_Likelihood( LikelihoodImage, region_Likelihood );
	double val1, val2;
	double val3;
	while( !imageIterator_Likelihood.IsAtEnd() && !imageIterator_PA.IsAtEnd() )
    {
        // Get the value of the current pixel
        val1 = imageIterator_PA.Get();
		val2 = imageIterator_Likelihood.Get();
	
	
		if( TUMOR_CASE_USE_PA_EQUAL_ONE )
		{
		    if( 1.0 == val1 && val2>0.01 )
		    //if( 1.0 == val1 )
		    {
			    val3 = 1.0;
		    }
			else
		    {
			    val3 = val1*val2;			
		    }
		}
		else
		{
			val3 = val1*val2;			
		}		
		
		imageIterator_Likelihood.Set( val3 );
		
        ++imageIterator_Likelihood;
		++imageIterator_PA;
    }
	
	
	
	
	
	char newInputImage[128];
	sprintf(newInputImage, "MAS/%d/MAP.nrrd", dataIndex);
	printf("\nnewInputImage:\t%s\n\n", newInputImage);
	
	
    // Write the output image. 
	typedef itk::ImageFileWriter< ImageTypeFloat >       WriterTypeFloat;
	
	WriterTypeFloat::Pointer writerFloat = WriterTypeFloat::New();    
	writerFloat->SetInput( LikelihoodImage );
	writerFloat->SetFileName( newInputImage );
	try
	{
		writerFloat->Update();
	}
	catch( itk::ExceptionObject & excp )
	{
		std::cerr << "ERROR: caught ITK exception while writing image "
			<< "gradient.nrrd" << "." << std::endl;
		std::cerr << excp << std::endl;
		return 2;
	}


	
	
	
	
	
	
	
	


//---------------------------------------------------------------------	
// Step 1. Median Filter.
//---------------------------------------------------------------------	
    typedef itk::MedianImageFilter<ImageTypeFloat,ImageTypeFloat> MedianFilterType;
    MedianFilterType::Pointer medianFilter = MedianFilterType::New();
	
	const int radiusValue = 3;
	MedianFilterType::InputSizeType radius_MedianFilter;
	radius_MedianFilter.Fill( radiusValue );

    medianFilter->SetRadius( radius_MedianFilter );
    medianFilter->SetInput( LikelihoodImage ); 	
	
	
	char newInputImage_MedianFilter[128];
	sprintf(newInputImage_MedianFilter, "MAS/%d/MAP_Median_R%d.nrrd", dataIndex, radiusValue);
	printf("\nnewInputImage_MedianFilter:\t%s\n\n", newInputImage_MedianFilter);	
	
    WriterTypeFloat::Pointer writerFloat_MedianFilter = WriterTypeFloat::New();    
	writerFloat_MedianFilter->SetInput( medianFilter->GetOutput() );
	writerFloat_MedianFilter->SetFileName( newInputImage_MedianFilter );
	try
	{
		writerFloat_MedianFilter->Update();
	}
	catch( itk::ExceptionObject & excp )
	{
		std::cerr << "ERROR: caught ITK exception while writing image "
			<< "gradient.nrrd" << "." << std::endl;
		std::cerr << excp << std::endl;
		return 2;
	}	
	
	
	// Normalize MAP to [0, 1].
	typedef itk::RescaleIntensityImageFilter< ImageTypeFloat, ImageTypeFloat > RescaleType;
    RescaleType::Pointer rescaleFilter = RescaleType::New();
    rescaleFilter->SetInput( medianFilter->GetOutput() );
    rescaleFilter->SetOutputMinimum( 0 );
    rescaleFilter->SetOutputMaximum( 1 );
		
	
	
//---------------------------------------------------------------------	
// Step 2. Otsu Threshold Filter.
//---------------------------------------------------------------------		
	
	typedef itk::OtsuThresholdImageFilter <ImageTypeFloat, ImageType> OtsuFilterType;
    OtsuFilterType::Pointer thresholdFilter = OtsuFilterType::New();
    //otsuFilter->SetInput( LikelihoodImage );
	thresholdFilter->SetInput( rescaleFilter->GetOutput() );
	thresholdFilter->SetOutsideValue( 1 );
    thresholdFilter->SetInsideValue( 0 );	
	
	thresholdFilter->Update();
	double threshold = thresholdFilter->GetThreshold();
    std::cout << "\n\nThreshold [OtsuThresholdImageFilter]:\t" << threshold << std::endl;
	
	
	
//---------------------------------------------------------------------	
// Step 3. Median Filter.
//---------------------------------------------------------------------	
	
	typedef itk::MedianImageFilter <ImageType, ImageType > BinaryMedianFilterType;  
	BinaryMedianFilterType::Pointer bmFilter = BinaryMedianFilterType::New ();
	
	const int radiusValueBM = 3;
	BinaryMedianFilterType::InputSizeType radius_BMedianFilter;
	radius_BMedianFilter.Fill( radiusValueBM );

    bmFilter->SetRadius( radius_BMedianFilter );	


	bmFilter->SetInput( thresholdFilter->GetOutput() );
    bmFilter->Update();
	
	
 	typedef itk::ConnectedComponentImageFilter <ImageType, ImageType > CCFilterType;
 
	CCFilterType::Pointer connectedFilter = CCFilterType::New ();
	connectedFilter->SetInput( bmFilter->GetOutput() );
	connectedFilter->Update(); 
	std::cout << "\n\nNumber of objects: " << connectedFilter->GetObjectCount() << std::endl << std::endl;
 
	typedef itk::LabelShapeKeepNObjectsImageFilter< ImageType > LabelShapeKeepNObjectsFilterType;
	LabelShapeKeepNObjectsFilterType::Pointer labelShapeFilter = LabelShapeKeepNObjectsFilterType::New();
	labelShapeFilter->SetInput( connectedFilter->GetOutput() );
	labelShapeFilter->SetBackgroundValue( 0 );
	labelShapeFilter->SetNumberOfObjects( 1 );
	labelShapeFilter->SetAttribute( LabelShapeKeepNObjectsFilterType::LabelObjectType::NUMBER_OF_PIXELS );
	

		
//------------------------------------------------------------
// Step 4:
// To remove fat etc.
// Erode    ==>    CC    ==>    Dilate  
//------------------------------------------------------------		
    typedef itk::BinaryBallStructuringElement<ImageType::PixelType, ImageType::ImageDimension> StructuringElementType;
	StructuringElementType structuringElement;
	structuringElement.SetRadius( 5 );
	structuringElement.CreateStructuringElement();
		
	typedef itk::BinaryErodeImageFilter <ImageType, ImageType, StructuringElementType> erodeImageFilterType;
	erodeImageFilterType::Pointer erodeFilter = erodeImageFilterType::New();
	erodeFilter->SetInput( labelShapeFilter->GetOutput() );
	erodeFilter->SetKernel( structuringElement );
	erodeFilter->Update();
	
	
	
	typedef itk::ConnectedComponentImageFilter <ImageType, ImageType > CCFilterType2;
 
	CCFilterType2::Pointer connectedFilter2 = CCFilterType2::New ();
	connectedFilter2->SetInput( erodeFilter->GetOutput() );
	connectedFilter2->Update(); 
	std::cout << "\n\nNumber of objects: " << connectedFilter2->GetObjectCount() << std::endl << std::endl;
 
	typedef itk::LabelShapeKeepNObjectsImageFilter< ImageType > LabelShapeKeepNObjectsFilterType2;
	LabelShapeKeepNObjectsFilterType2::Pointer labelShapeFilter2= LabelShapeKeepNObjectsFilterType2::New();
	labelShapeFilter2->SetInput( connectedFilter2->GetOutput() );
	labelShapeFilter2->SetBackgroundValue( 0 );
	labelShapeFilter2->SetNumberOfObjects( 1 );
	labelShapeFilter2->SetAttribute( LabelShapeKeepNObjectsFilterType::LabelObjectType::NUMBER_OF_PIXELS ); 
		
	
		
	typedef itk::BinaryDilateImageFilter <ImageType, ImageType, StructuringElementType> dilateImageFilterType;
	dilateImageFilterType::Pointer dilateFilter = dilateImageFilterType::New();
	dilateFilter->SetInput( labelShapeFilter2->GetOutput() );
	dilateFilter->SetKernel( structuringElement );
	dilateFilter->Update();
	
	
	
		
		
//-------------------------------------------------------------------
// Step 5: 
// Fill holes using VotingBinaryIterativeHoleFillingImageFilter.
//
// Ref: 
// http://itk-insight-users.2283740.n2.nabble.com/How-to-fill-the-hole-in-itk-td6389364.html
// http://www.slicer.org/slicerWiki/index.php/Documentation/4.0/Modules/VotingBinaryHoleFillingImageFilter
//-------------------------------------------------------------------	
	typedef itk::VotingBinaryIterativeHoleFillingImageFilter< ImageType > HoleFillingFilterType;
    HoleFillingFilterType::Pointer HoleFillingFilter = HoleFillingFilterType::New();
	
    HoleFillingFilter->SetInput( dilateFilter->GetOutput() );
	
	
	// The radius of a hole to be filled.
	HoleFillingFilterType::InputSizeType radius;
    radius.Fill( 5 );		
	
	/*ImageType::SizeType radius;
    radius[0] = 3; // radius along x
    radius[1] = 3; // radius along y
	radius[2] = 3; // radius along z*/

    HoleFillingFilter->SetRadius( radius );
		

	// The number of pixels over 50% that will decide whether an OFF pixel will become ON or not. 
	// For example, if the neighborhood of a pixel has 124 pixels (excluding itself), the 50% will be 62, 
	// and if you set a Majority threshold of 5, 
	// that means that the filter will require 67 or more neighbor pixels to be ON 
	// in order to switch the current OFF pixel to ON.
    //
    // If you want to fill large holes, set the majority to a small value,
    // and use a large number of iterations. 
    HoleFillingFilter->SetMajorityThreshold( 2 );
	//HoleFillingFilter->SetMajorityThreshold( 5 );
	
    HoleFillingFilter->SetBackgroundValue( 0 );
    HoleFillingFilter->SetForegroundValue( 1 );
	
	// The more iterations you ran, 
	// the larger the cavities that will be filled in.
    HoleFillingFilter->SetMaximumNumberOfIterations( 5 );






		

	
		
	char newInputImage2[128];
	sprintf(newInputImage2, "MAS/%d/FINALLL.nrrd", dataIndex);
	printf("\nnewInputImage File2:\t%s\n\n", newInputImage2);
	
    // Write the output image. 
	typedef itk::ImageFileWriter< ImageType > WriterType;
	
	WriterType::Pointer writer = WriterType::New();   
	
	writer->SetInput( HoleFillingFilter->GetOutput() );
	//writer->SetInput( otsuFilter->GetOutput() );
	
	writer->SetFileName( newInputImage2 );
	try
	{
		writer->Update();
	}
	catch( itk::ExceptionObject & excp )
	{
		std::cerr << "ERROR: caught ITK exception while writing image "
			<< newInputImage2 << "." << std::endl;
		std::cerr << excp << std::endl;
		return 2;
	}	
	
	
	
	
	return true;
}