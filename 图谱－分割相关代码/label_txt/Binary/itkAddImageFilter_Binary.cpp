#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkAddImageFilter.h"

#include "itkImageRegionIterator.h"

#include "itkRescaleIntensityImageFilter.h"
#include "itkCastImageFilter.h"



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;


int main(int argc, char *argv[])
{
	//const int numFile = 9;
	const int numFile = atoi( argv[1] );
	
    typedef itk::Image< char, 3 > ImageType;
    typedef itk::ImageFileReader<ImageType> ReaderType;
	
	
    ReaderType::Pointer firstReader = ReaderType::New();
    firstReader->SetFileName( "liver-BSplinetomean_0.nrrd" );
    firstReader->Update();
	ImageType::Pointer sumImage = firstReader->GetOutput();
	
	
	for( int i=1; i<numFile; i++ )
	{
		ostringstream ss;
		string datasetFilename;
		
		char *baseName = "liver-BSplinetomean_";
		ss << baseName << i << ".nrrd";
	    datasetFilename = ss.str();
	    const char *inputFile = datasetFilename.c_str();
	    printf("Input File:\t%s\n", inputFile);
		
		
		ReaderType::Pointer movingReader = ReaderType::New();
	    movingReader->SetFileName( inputFile );
	    movingReader->Update();
	    ImageType::Pointer movingImage = movingReader->GetOutput();
		
	    typedef itk::AddImageFilter <ImageType, ImageType > AddImageFilterType;
	    AddImageFilterType::Pointer addFilter = AddImageFilterType::New ();
        addFilter->SetInput1(sumImage);
        addFilter->SetInput2(movingImage);
        addFilter->Update();
		
		sumImage = addFilter->GetOutput();
	}
		

	
	typedef char OutputPixelType;
    typedef itk::Image< OutputPixelType, 3 > OutputImageType;
	typedef itk::ImageFileWriter< OutputImageType >  WriterType;
    WriterType::Pointer writer =  WriterType::New();
	writer->SetFileName("sum.nrrd");
	
	writer->SetInput( sumImage );
    writer->Update();
	
	
	typedef itk::Image< float, 3 > OutputImageType2;
	typedef itk::RescaleIntensityImageFilter< ImageType, ImageType >
    RescaleType;
    RescaleType::Pointer rescale = RescaleType::New();
    rescale->SetInput( sumImage );
    rescale->SetOutputMinimum( 0 );
    rescale->SetOutputMaximum( numFile );
    rescale->Update();
	
    typedef itk::CastImageFilter< ImageType, OutputImageType2 > FilterType;
    FilterType::Pointer filter = FilterType::New();
    filter->SetInput( rescale->GetOutput() );
    filter->Update();
    OutputImageType2::Pointer sumImageFloat = filter->GetOutput();
	
	
	
	itk::ImageRegionIterator<OutputImageType2> imageIterator(sumImageFloat, sumImageFloat->GetLargestPossibleRegion());
    while(!imageIterator.IsAtEnd())
    {
        // Get the value of the current pixel
        float val = imageIterator.Get();
		float avg = val/(double)(numFile);
        //std::cout << avg << std::endl;
		imageIterator.Set( avg );
 
        ++imageIterator;
    }
	

   
	typedef itk::ImageFileWriter< OutputImageType2 >  WriterType2;
	WriterType2::Pointer writer2 =  WriterType2::New();
	writer2->SetFileName("avg.nrrd");
	
	writer2->SetInput( sumImageFloat );
    writer2->Update();
	
	
	
	
	
	return 0;
}
	
	
	
	
	
	
	
