#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkExtractImageFilter.h"

int main(int argc,char* argv[])
{
	const unsigned int Dimension = 3; //定义图像维数
	typedef short PixelType;  //定义像素类型
	typedef itk::Image< PixelType,Dimension > InputImageType;  //输入图像类型

	const unsigned int Dimension1 = 3; //定义图像维数
	typedef short PixelType1;  //定义像素类型
	typedef itk::Image< PixelType1,Dimension1 > OutputImageType;  //输出图像类型

	  typedef itk::ImageFileReader< InputImageType >  ReaderType;
	  ReaderType::Pointer reader = ReaderType::New();
	  reader->SetFileName( argv[1] );
	  reader->Update();	


	//1、指定区域大小,沿着Z轴提取切片(X-0; Y-1; Z-2)
	InputImageType::RegionType inputRegion = reader->GetOutput()->GetLargestPossibleRegion();
	InputImageType::SizeType size = inputRegion.GetSize();
	size[2] = 0;
	//2、指定提取的切片号
	InputImageType::IndexType start = inputRegion.GetIndex();
	const unsigned int sliceNumber = atoi( argv[2] );
	start[2] = sliceNumber;
	//3、组合切片区域
	InputImageType::RegionType desiredRegion; //组合区域 
	desiredRegion.SetSize( size );
	desiredRegion.SetIndex( start );
	//4、定义filter,并提取切片
	typedef itk::ExtractImageFilter<InputImageType, OutputImageType> ExtractFilterType;
	ExtractFilterType ::Pointer filter = ExtractFilterType::New();
	filter->SetInput(reader->GetOutput());
	filter->SetExtractionRegion( desiredRegion );
	filter->Update();

	return 0;
}
