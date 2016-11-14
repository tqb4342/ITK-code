/**
  \file Upsampling.cxx
  \date 15 april 2011
  \author Francis Girard
 
  A simple example showing how to use the ResampleImageFilter and the 
  BSplineInterpolateImageFunction to (up)scale an image using bicubic
  interpolation.
*/
 
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkIdentityTransform.h"
#include "itkBSplineInterpolateImageFunction.h"
#include "itkResampleImageFilter.h"
 
#include <iostream>
 
 
 
int main( int argc, char * argv[] )
{
  const int DIM = 3;
  // Typedef's for pixel, image, reader and writer types
  typedef short T_InputPixel;
  typedef short T_OutputPixel;
 
  // Doesn't work for RGB pixels
  //typedef itk::CovariantVector<unsigned char, 3> T_InputPixel;
  //typedef itk::CovariantVector<unsigned char, 3> T_OutputPixel;
 
  typedef itk::Image<T_InputPixel, DIM> T_Image;
  typedef itk::ImageFileReader<T_Image> T_Reader;
 
  typedef short T_WritePixel;
  typedef itk::Image<T_WritePixel, DIM> T_WriteImage;
  typedef itk::ImageFileWriter<T_WriteImage> T_Writer;
 
	
	
	
	
  // Typedefs for the different (numerous!) elements of the "resampling"
 
  // Identity transform.
  // We don't want any transform on our image except rescaling which is not
  // specified by a transform but by the input/output spacing as we will see
  // later.
  // So no transform will be specified.
  typedef itk::IdentityTransform<double, DIM> T_Transform;
 
  // If ITK resampler determines there is something to interpolate which is
  // usually the case when upscaling (!) then we must specify the interpolation
  // algorithm. In our case, we want bicubic interpolation. One way to implement
  // it is with a third order b-spline. So the type is specified here and the
  // order will be specified with a method call later on.
  typedef itk::BSplineInterpolateImageFunction<T_Image, double, double> T_Interpolator;
 
  // The resampler type itself.
  typedef itk::ResampleImageFilter<T_Image, T_Image> T_ResampleFilter;
 
 
 
 
 
 
 
  // Prepare the reader and update it right away to know the sizes beforehand. 
  T_Reader::Pointer pReader = T_Reader::New();
  pReader->SetFileName( argv[1] );
  pReader->Update();
  
  T_Image::ConstPointer inputImage = pReader->GetOutput();
  
  
  
 
 
  // Prepare the resampler.
 
  // Instantiate the transform and specify it should be the id transform.
  T_Transform::Pointer _pTransform = T_Transform::New();
  _pTransform->SetIdentity();
 
 
  // Instantiate the b-spline interpolator and set it as the third order
  // for bicubic.
  T_Interpolator::Pointer _pInterpolator = T_Interpolator::New();
  _pInterpolator->SetSplineOrder(3);
 
 
  // Instantiate the resampler. Wire in the transform and the interpolator.
  T_ResampleFilter::Pointer _pResizeFilter = T_ResampleFilter::New();
  _pResizeFilter->SetTransform(_pTransform);
  _pResizeFilter->SetInterpolator(_pInterpolator);
  
  
  _pResizeFilter->SetDefaultPixelValue( -1024 ); // value for regions without source
 
 
 
 
  // Set the output origin. You may shift the original image "inside" the
  // new image size by specifying something else than 0.0, 0.0 here. 
  //const double vfOutputOrigin[3]  = { 0.0, 0.0, 0.0};
  //_pResizeFilter->SetOutputOrigin(vfOutputOrigin);
  
  
  // The origin and direction of the input image is preserved 
  // and passed to the output image.
  _pResizeFilter->SetOutputOrigin( inputImage->GetOrigin() );
  _pResizeFilter->SetOutputDirection( inputImage->GetDirection() );
  
  
  
 
  //     Compute and set the output spacing
  //     Compute the output spacing from input spacing and old and new sizes.
  //     
  //     The computation must be so that the following holds:
  //     
  //     new width         old x spacing
  //     ----------   =   ---------------
  //     old width         new x spacing
  //    
  //    
  //     new height         old y spacing
  //    ------------  =   ---------------
  //     old height         new y spacing
  //
  //     So either we specify new height and width and compute new spacings (as
  //     we do here) or we specify new spacing and compute new height and width
  //     and computations that follows need to be modified a little (as it is
  //     done at step 2 there:
  //       http://itk.org/Wiki/ITK/Examples/DICOM/ResampleDICOM)
  //
  

  const double factorX = atof( argv[3] );
  const double factorY = atof( argv[4] );
  const double factorZ = atof( argv[5] );
 
  
 
  // Fetch original image size.
  const T_Image::RegionType& inputRegion = pReader->GetOutput()->GetLargestPossibleRegion();
  const T_Image::SizeType& vnInputSize = inputRegion.GetSize();
  unsigned int nOldWidth = vnInputSize[0];
  unsigned int nOldHeight = vnInputSize[1];
  unsigned int nOldDepth = vnInputSize[2];
  
  
// From ResampleVolumesToBeIsotropic.cxx:
//
// The number of pixels to use along each dimension in the grid of the
// resampled image is computed using the ratio between the pixel spacings of the
// input image and those of the output image. Note that the computation of the
// number of pixels along the $Z$ direction is slightly different with the
// purpose of making sure that we don't attempt to compute pixels that are
// outside of the original anisotropic dataset.
  typedef T_Image::SizeType::SizeValueType SizeValueType;
  unsigned int nNewWidth = static_cast< SizeValueType >( nOldWidth*factorX );
  unsigned int nNewHeight = static_cast< SizeValueType >( nOldHeight*factorY );
  unsigned int nNewDepth = static_cast< SizeValueType >( (nOldDepth-1)*factorZ );
 
 
 
  // Fetch original image spacing.
  const T_Image::SpacingType& vfInputSpacing = pReader->GetOutput()->GetSpacing();
                                            // Will be {1.0, 1.0} in the usual
                                            // case. 
  double vfOutputSpacing[3];
  vfOutputSpacing[0] = vfInputSpacing[0] / factorX;
  vfOutputSpacing[1] = vfInputSpacing[1] / factorY;
  vfOutputSpacing[2] = vfInputSpacing[2] / factorZ;
 
 
 
  // Set the output spacing. If you comment out the following line, the original
  // image will be simply put in the upper left corner of the new image without
  // any scaling.
  _pResizeFilter->SetOutputSpacing(vfOutputSpacing);
 
 
 
  // Set the output size as specified on the command line. 
  itk::Size<3> vnOutputSize = { {nNewWidth, nNewHeight, nNewDepth} };
  _pResizeFilter->SetSize(vnOutputSize);
   
  
  // Specify the input. 
  _pResizeFilter->SetInput(pReader->GetOutput());
 
  
  // Write the result
  T_Writer::Pointer pWriter = T_Writer::New();
  pWriter->SetFileName(argv[2]);
  pWriter->SetInput( _pResizeFilter->GetOutput() );
  pWriter->Update();
 
  return EXIT_SUCCESS;
}