#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkAddImageFilter.h"

#include "itkImageRegionIterator.h"



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
	
    typedef itk::Image< short, 3 > ImageType;
    typedef itk::ImageFileReader<ImageType> ReaderType;
	
	
    
	
	
	int middleIndex = numFile/2;
	
	
	
	ReaderType::Pointer firstReader = ReaderType::New();
    firstReader->SetFileName( "liver-BSplinetomean_0.nrrd" );
    firstReader->Update();
	ImageType::Pointer sumImage = firstReader->GetOutput();	
	
{	
	for( int i=1; i<middleIndex; i++ )
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
		

	
	typedef short OutputPixelType;
    typedef itk::Image< OutputPixelType, 3 > OutputImageType;
	typedef itk::ImageFileWriter< ImageType >  WriterType;
    WriterType::Pointer writer =  WriterType::New();
	writer->SetFileName("sum_1.nrrd");
	
	writer->SetInput( sumImage );
    writer->Update();
	
	
	itk::ImageRegionIterator<ImageType> imageIterator(sumImage, sumImage->GetLargestPossibleRegion());
    while(!imageIterator.IsAtEnd())
    {
        // Get the value of the current pixel
        short val = imageIterator.Get();
		short avg = (double)val/(double)(numFile);
        //std::cout << avg << std::endl;
		imageIterator.Set( avg );
 
        ++imageIterator;
    }
	
	WriterType::Pointer writer2 =  WriterType::New();
	writer2->SetFileName("avg_1.nrrd");
	
	writer2->SetInput( sumImage );
    writer2->Update();
}	
	
	
	
	
	



	
	printf("\n\n\nPart2 Begins!!!\n\n");

    char middleIndexFile[512];
	sprintf(middleIndexFile, "liver-BSplinetomean_%d.nrrd", middleIndex);
	printf("middleIndexFile:\t%s\n\n", middleIndexFile);
	
	ReaderType::Pointer firstReader2 = ReaderType::New();
    firstReader2->SetFileName( middleIndexFile );
    firstReader2->Update();
	ImageType::Pointer sumImage2 = firstReader2->GetOutput();
	
{	
	for( int i=middleIndex+1; i<numFile; i++ )
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
        addFilter->SetInput1(sumImage2);
        addFilter->SetInput2(movingImage);
        addFilter->Update();
		
		sumImage2 = addFilter->GetOutput();
	}
		

	
	typedef short OutputPixelType;
    typedef itk::Image< OutputPixelType, 3 > OutputImageType;
	typedef itk::ImageFileWriter< ImageType >  WriterType;
    WriterType::Pointer writer =  WriterType::New();
	writer->SetFileName("sum_2.nrrd");
	
	writer->SetInput( sumImage2 );
    writer->Update();
	
	
	itk::ImageRegionIterator<ImageType> imageIterator(sumImage2, sumImage2->GetLargestPossibleRegion());
    while(!imageIterator.IsAtEnd())
    {
        // Get the value of the current pixel
        short val = imageIterator.Get();
		short avg = (double)val/(double)(numFile);
        //std::cout << avg << std::endl;
		imageIterator.Set( avg );
 
        ++imageIterator;
    }
	
	WriterType::Pointer writer2 =  WriterType::New();
	writer2->SetFileName("avg_2.nrrd");
	
	writer2->SetInput( sumImage2 );
    writer2->Update();
}	
	
	
	
	
{
    typedef itk::AddImageFilter <ImageType, ImageType > AddImageFilterType;
	AddImageFilterType::Pointer addFilter = AddImageFilterType::New ();
	addFilter->SetInput1(sumImage);
	addFilter->SetInput2(sumImage2);
	addFilter->Update();
	
	sumImage = addFilter->GetOutput();
	
	
	typedef short OutputPixelType;
    typedef itk::Image< OutputPixelType, 3 > OutputImageType;
	typedef itk::ImageFileWriter< ImageType >  WriterType;
    WriterType::Pointer writer =  WriterType::New();
	writer->SetFileName("avg.nrrd");
	
	writer->SetInput( sumImage );
    writer->Update();
	
}	
	
	
	
	return 0;
}
	
	
	
	
	
	
	
