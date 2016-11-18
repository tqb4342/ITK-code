#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkPasteImageFilter.h"
#include "itkChangeInformationImageFilter.h"
#include "itkPasteImageFilter.h"



const int Dim = 3;	
typedef itk::Image<float, Dim>  ImageType;	
	
	
 
bool createEmptyImage( ImageType::Pointer emptyImage, int w, int h, int d );



int main( int argc, char * argv[] )
{
	typedef itk::ImageFileReader< ImageType  >  ReaderType;
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName( argv[1] );
	reader->Update();
	
	
	ImageType::ConstPointer inputImage = reader->GetOutput();
	
	ImageType::RegionType region = inputImage->GetLargestPossibleRegion();
	ImageType::SizeType size = region.GetSize();
	int width  = size[0];
	int height = size[1];
	int depth  = size[2];	
	printf("\nDimension(%d):\t[%d, %d, %d]\n", 3, width, height, depth);
	
    ImageType::PointType origin = inputImage->GetOrigin();
    ImageType::SpacingType spacing = inputImage->GetSpacing();
    ImageType::DirectionType direction = inputImage->GetDirection();
 
	
	
	
	
	ImageType::Pointer emptyImage = ImageType::New();	
	//createEmptyImage( emptyImage, 512, 512, 220 );
	
	int newDepth = depth + 37;
	createEmptyImage( emptyImage, width, height, newDepth );
    printf("\nNEW Dimension(%d):\t[%d, %d, %d]\n", 3, width, height, newDepth);

	
	
	
	typedef itk::ChangeInformationImageFilter< ImageType > FilterType;
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
		
		
	
		
		
	typedef itk::PasteImageFilter <ImageType, ImageType > PasteImageFilterType;
 
    // The SetDestinationIndex() method prescribes where in the first
    // input to start pasting data from the second input.
    // The SetSourceRegion method prescribes the section of the second
    // image to paste into the first. 
    ImageType::IndexType destinationIndex;
    destinationIndex[0] = 0;
    destinationIndex[1] = 0;
	destinationIndex[2] = 0;
 
    PasteImageFilterType::Pointer pasteFilter = PasteImageFilterType::New();
    pasteFilter->SetSourceImage( inputImage );
    pasteFilter->SetDestinationImage( filter->GetOutput() );
    pasteFilter->SetSourceRegion( inputImage->GetLargestPossibleRegion() );
    pasteFilter->SetDestinationIndex( destinationIndex );
		
	
	
	
	
    typedef itk::ImageFileWriter< ImageType >  WriterType;
    WriterType::Pointer writer = WriterType::New();
    writer->SetInput( pasteFilter->GetOutput() );
    writer->SetFileName( argv[2] );

    try
    {
        writer->Update();
    }
    catch( itk::ExceptionObject & excep )
    {
        std::cerr << "Exception catched !" << std::endl;
        std::cerr << excep << std::endl;
    }

    std::cout << "Resampling Done !" << std::endl;
	
	
	return 0;
}




bool createEmptyImage( ImageType::Pointer emptyImage, int w, int h, int d )
{
	// Create an image with 2 connected components
	ImageType::RegionType region;
    ImageType::IndexType start;
    start[0] = 0;
    start[1] = 0;
	start[2] = 0;
 
    ImageType::SizeType size;
    size[0] = w;
	size[1] = h;
	size[2] = d;
 
    region.SetSize(size);
    region.SetIndex(start);
 
    emptyImage->SetRegions(region);
    emptyImage->Allocate();
	emptyImage->FillBuffer( 0 );
	  
	
	return true;	
}