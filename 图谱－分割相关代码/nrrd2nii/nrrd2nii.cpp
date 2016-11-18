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
 



int main(int argc, char* argv[])
{
  const unsigned Dimension = 3;

  typedef short                       PixelType;
  typedef itk::Image< PixelType, Dimension >  ImageType;

  typedef itk::ImageFileReader< ImageType >   ReaderType;
 
 	
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName( argv[1] );
	reader->Update();	
	ImageType::Pointer inputImage = reader->GetOutput();
 

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[2] );
  writer->SetInput( inputImage );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & e )
    {
    std::cerr << "Error: " << e << std::endl;
    return EXIT_FAILURE;
    }
 
 
	

  return EXIT_SUCCESS;
}