#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main(int argc,char* argv[])
{
	const unsigned int Dimension = 2; //定义图像维数
	typedef unsigned char PixelType;  //定义像素类型
	typedef itk::Image< PixelType,Dimension > ImageType;
	typedef itk::ImageFileReader< ImageType > ReaderType;
	typedef itk::ImageFileWriter< ImageType > WriterType;

	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);

	WriterType::Pointer writer = WriterType::New();
	writer->SetFileName(argv[2]);
	writer->SetInput(reader->GetOutput());
	writer->Update();
	return 0;
}
