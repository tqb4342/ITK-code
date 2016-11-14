#include <iostream>
using namespace std;

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"


int main(int argc,char* argv[])
{
	
	const unsigned int Dimension = 3; //定义图像维数
	typedef unsigned char PixelType;  //定义像素类型
	typedef itk::Image< PixelType,Dimension > ImageType;
	typedef itk::ImageFileReader< ImageType > ReaderType;
	//typedef itk::ImageFileWriter< ImageType > WriterType;

	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);
	reader->Update();

	ImageType::Pointer image = reader->GetOutput();

	//2、定义迭代器,需要给定图像指针和需要访问的图像区域大小
	typedef itk::ImageRegionIterator<ImageType> ItType;
	ItType it( image, image->GetRequestedRegion() );
	//3、将迭代器移动到首个元素
	it.GoToBegin();
	//4、遍历像素,直至结束
	cout<<"开始啦！"<<endl;
	while( !it.IsAtEnd() )
	{
		//cout<<"开始啦！"<<endl;
	//5、获取像素值
	ImageType::PixelType vlaue = it.Get();
	cout<<(int)vlaue<<" ";
	//6、重新设置像素值
	//it.Set( 255 );

	//7、迭代器移动至下一元素
	++it;
	}

	return 0;
}
