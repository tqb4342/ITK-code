#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkNumericSeriesFileNames.h"
#include "itkImageSeriesWriter.h"
#include "itkPNGImageIO.h"
#include "itkImageSeriesReader.h"




int main( int argc, char* argv[] )
{
 
  //const char * inputFileName = argv[1];
//  const char * outputFileName = argv[1];
  const unsigned int first = atoi( argv[1] );
  const unsigned int last  = atoi( argv[2] );

  //std::string inname = argv[5];
	
// std::string format =  std::string( outputFileName ) +
 //                       std::string( "%d_spleen.png" );
 std::string format = argv[3];   //输出图像的位置和命名
	     format += "%d";
	     format += argv[4];

std::string format2 = argv[5];   //输入图像的位置和命名
	     format2 += "%d";
	     format2 += argv[4];
	
  const unsigned int Dimension = 3;
  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > InputImageType;    //注意：输入图像时 Dimension = 3;
  typedef itk::ImageSeriesReader< InputImageType >  ReaderType;   //定义读取批量图像的类
  ReaderType::Pointer reader = ReaderType::New();
 // reader->SetFileName( inputFileName );
 // reader->Update();	
	

  //定义需要处理的图像位置和命名方式
  typedef itk::NumericSeriesFileNames    NameGeneratorType;
  NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();
  //nameGenerator->SetSeriesFormat( "label/a_01_%d_spleen.png" );
  nameGenerator->SetSeriesFormat( format2.c_str() );
  nameGenerator->SetStartIndex( first );
  nameGenerator->SetEndIndex( last );
  nameGenerator->SetIncrementIndex( 1 );

//批量读取图像
  reader->SetImageIO( itk::PNGImageIO::New() );
  reader->SetFileNames( nameGenerator->GetFileNames()  );

 //像素值处理	
  typedef unsigned char OutputPixelType;
  typedef itk::Image< OutputPixelType, Dimension > RescaleImageType;
  typedef itk::RescaleIntensityImageFilter< InputImageType, RescaleImageType >
    RescaleFilterType;
  RescaleFilterType::Pointer rescale = RescaleFilterType::New();
  rescale->SetInput( reader->GetOutput() );
  rescale->SetOutputMinimum( 0 );
  rescale->SetOutputMaximum( 255 );
  rescale->UpdateLargestPossibleRegion();
	
	
	
	
 //定义输出图像的命名方式
  itk::NumericSeriesFileNames::Pointer fnames = itk::NumericSeriesFileNames::New();
  fnames->SetStartIndex( first );
  fnames->SetEndIndex(last);
  fnames->SetIncrementIndex( 1 );
  fnames->SetSeriesFormat( format.c_str() );
  
 
  
  typedef itk::Image< OutputPixelType, 2 > OutputImageType;   //注意：输出图像时 Dimension = 2;
  typedef itk::ImageSeriesWriter< RescaleImageType, OutputImageType >
    WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( rescale->GetOutput() );
  writer->SetFileNames( fnames->GetFileNames() );
  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
