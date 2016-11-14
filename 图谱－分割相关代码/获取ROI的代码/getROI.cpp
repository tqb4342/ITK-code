/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;



#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImageRegionIteratorWithIndex.h"

#include "itkExtractImageFilter.h"



int main(int argc, char* argv[])
{
  const unsigned Dimension = 3;

  typedef short                       PixelType;
  typedef itk::Image< PixelType, Dimension >  ImageType;

  typedef itk::ImageFileReader< ImageType >   ReaderType;
 
	
	
	
	
	
	
	const int numFile = 3;
	
	int startX, endX, startY, endY, startZ, endZ;
	
	
	
	char *inputROIFile = "roi.txt";
	printf("\n\nInput File:\t%s\n", inputROIFile);	
	
	ifstream ifs( inputROIFile );
	
	
	int initialIndex = 61;
for( int i=initialIndex; i<initialIndex+numFile; i++ )
{		
		char inputFile[512];
        sprintf(inputFile, "img-%d-flip.nrrd", i);
		
		 ReaderType::Pointer reader = ReaderType::New();
		reader->SetFileName( inputFile );
        reader->Update();	
	    ImageType::Pointer inputImage = reader->GetOutput();
 
    
	    startX = endX = startY = endY = startZ = endZ = 0; 
	
	
	
	int tmp = 0;
	if( ifs.is_open() )
	{
		ifs >> startX >> startY >> startZ >> endX >> endY  >> endZ;
	}
	else
	{
		printf("\n\nThe File \"%s\" can not be read correctly!!!\n\n", inputFile);
			
		ifs.close();	
		return 1;
	}
		
	
	
	startX -= 1;
	startY -= 1;
	startZ -= 1;
	
	endX -= 1;
	endY -= 1;
	endZ -= 1;
	


	int sizeX = endX - startX + 1;
	int sizeY = endY - startY + 1;	
	int sizeZ = endZ - startZ + 1;
	
 
	
	
  ImageType::IndexType desiredStart;
  desiredStart[0] = startX;
  desiredStart[1] = startY;
  desiredStart[2] = startZ; 
 
  ImageType::SizeType desiredSize;
  desiredSize[0] = sizeX;
  desiredSize[1] = sizeY;
  desiredSize[2] = sizeZ;  
  
  ImageType::RegionType desiredRegion(desiredStart, desiredSize); 
  std::cout << "desiredRegion: " << desiredRegion << std::endl;
	
	
	
  typedef itk::ExtractImageFilter< ImageType, ImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetExtractionRegion( desiredRegion );
  filter->SetInput( inputImage );
  filter->SetDirectionCollapseToIdentity(); // This is required.
  filter->Update();


	
	
	char outputFile[512];
	sprintf(outputFile, "img-%d-flip-spleen-roi-our.nrrd", i);
		
  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFile );
  writer->SetInput( filter->GetOutput() );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & e )
    {
    std::cerr << "Error: " << e << std::endl;
    return EXIT_FAILURE;
    }
}
	ifs.close();
	
	

  return EXIT_SUCCESS;
}
