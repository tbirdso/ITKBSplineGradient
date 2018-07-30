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
#ifndef itkImageToImageOfVectorsFilter_h
#define itkImageToImageOfVectorsFilter_h

#include "itkImageToImageFilter.h"
#include "itkVector.h"

namespace itk
{
/** \class ImageToImageOfVectorsFilter
 *
 * \brief This class takes as input 'n' itk::Image's and composes them into
 * a single itk::Image<itk::Vector<P,C>, D>.
 *
 * \par Inputs and Usage
 * \code
 *    filter->SetInput( 0, image0 );
 *    filter->SetInput( 1, image1 );
 *    ...
 *    filter->Update();
 *    itk::Image< itk::Vector<PixelType, Components>,  Dimension >::Pointer = filter->GetOutput();
 * \endcode
 * All input images are expected to have the same template parameters and have
 * the same size and origin.
 *
 * \sa Vector
 * \sa ImageToVectorImageFilter
 * \sa ScalarToArrayCastImageFilter
 *
 * \todo replace this with something that can make an image of any array type,
 * like ScalarToArrayCastImageFilter, if possible.
 *
 * \ingroup BSplineGradient
 */
template< typename TInputImage, unsigned int NComponents = 3 >
class ITK_TEMPLATE_EXPORT ImageToImageOfVectorsFilter :
  public ImageToImageFilter< TInputImage,
                             Image< Vector< typename TInputImage::InternalPixelType,
                                            NComponents >, TInputImage::ImageDimension > >
{
public:
  ITK_DISALLOW_COPY_AND_ASSIGN(ImageToImageOfVectorsFilter);

  typedef ImageToImageFilter< TInputImage,
                             Image< Vector< typename TInputImage::InternalPixelType,
                                            NComponents >, TInputImage::ImageDimension > > Superclass;
  typedef ImageToImageOfVectorsFilter Self;
  typedef SmartPointer< Self >        Pointer;
  typedef SmartPointer< const Self >  ConstPointer;
  itkNewMacro( Self );
  itkTypeMacro( ImageToImageOfVectorsFilter, ImageToImageFilter );

  typedef TInputImage InputImageType;
  itkStaticConstMacro(ImageDimension, unsigned int, TInputImage::ImageDimension);

  typedef typename InputImageType::InternalPixelType InputPixelType;

  typedef Vector< InputPixelType, NComponents >    OutputPixelType;
  typedef Image< OutputPixelType, ImageDimension > OutputImageType;
  typedef typename OutputImageType::RegionType     RegionType;

  typedef typename Superclass::DataObjectPointerArraySizeType DataObjectPointerArraySizeType;

  virtual void SetNthInput(DataObjectPointerArraySizeType idx, const InputImageType *inputImage)
  { this->SetInput(idx, inputImage); }

protected:
  ImageToImageOfVectorsFilter();
  virtual ~ImageToImageOfVectorsFilter() {}

  void BeforeThreadedGenerateData() override;

  void DynamicThreadedGenerateData(const RegionType & outputRegionForThread) override;

private:
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkImageToImageOfVectorsFilter.hxx"
#endif

#endif