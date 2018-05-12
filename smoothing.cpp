// https://itk.org/ITKExamples/src/Filtering/Thresholding/ThresholdAnImageUsingBinary/Documentation.html?highlight=threshold%20binary
// output at 50 looks to give the best result. 

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImage.h"
#include "itkBinaryThresholdImageFilter.h"



smoothing::applySmoothing(ReaderType::Pointer reader){ 

using PixelType = unsigned char;
constexpr unsigned int Dimension = 3; 

using ImageType = itk::Image< PixelType, Dimension>;
using ReaderType = itk::itkImageFileReader<ImageType>;

// setting up filters
using BinaryThresholdFilterType = itk::itkBinaryThresholdImageFilter< ImageType, ImageType>;
BinaryThresholdFilterType::Pointer binaryFilter = BinaryThresholdFilterType::New();

using WriterType = itk::ImageFileWriter< ImageType >;

  // Applying binary thresholding
  // https://itk.org/ITKExamples/src/Filtering/Thresholding/ThresholdAnImageUsingBinary/Documentation.html?highlight=threshold%20binary

  // setting up parameters, these seem to be the best configuration from testing
  auto lowerThresh = static_cast<PixelType>(30);
  auto upperThresh = static_cast<PixelType>(150);
  auto OutsideValue = static_cast<PixelType>(0);
  auto InsideValue = static_cast<PixelType>(255);

  binaryFilter->SetInput( reader->GetOutput() );
  binaryFilter->SetLowerThreshold( LowerThreshold );
  binaryFilter->SetUpperThreshold( UpperThreshold );
  binaryFilter->SetOutsideValue( OutsideValue );
  binaryFilter->SetInsideValue( InsideValue );


}// end applyBinaryThresholding