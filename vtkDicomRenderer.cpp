// VTK libraries used to render a 3D volume
#include "vtkDicomRenderer.h"

vtkDicomRenderer::vtkDicomRenderer(){
	reader->SetDirectoryName("../finalProject/DICOMs");
	reader->Update();
	imageData->ShallowCopy(reader->GetOutput());

	renderer->SetBackground(0.1, 0.2, 0.3);

	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(500, 500);

	renderWindowInteractor->SetInteractorStyle(interactorStyle);
	renderWindowInteractor->SetRenderWindow(renderWindow);

	volumeMapper->SetBlendModeToComposite();
	volumeMapper->SetRequestedRenderModeToGPU();
	volumeMapper->SetInputData(imageData);

	volumeProperty->ShadeOn();
	volumeProperty->SetInterpolationTypeToLinear();

	volumeProperty->SetAmbient(0.1);
	volumeProperty->SetDiffuse(0.9);
	volumeProperty->SetSpecular(0.2);
	volumeProperty->SetSpecularPower(10.0);

	gradientOpacity->AddPoint(0.0, 0.0);
	gradientOpacity->AddPoint(2000.0, 1.0);
	volumeProperty->SetGradientOpacity(gradientOpacity);

	scalarOpacity->AddPoint(-800.0, 0.0);
	scalarOpacity->AddPoint(-750.0, 1.0);
	scalarOpacity->AddPoint(-350.0, 1.0);
	scalarOpacity->AddPoint(-300.0, 0.0);
	scalarOpacity->AddPoint(-200.0, 0.0);
	scalarOpacity->AddPoint(-100.0, 1.0);
	scalarOpacity->AddPoint(1000.0, 0.0);
	scalarOpacity->AddPoint(2750.0, 0.0);
	scalarOpacity->AddPoint(2976.0, 1.0);
	scalarOpacity->AddPoint(3000.0, 0.0);
	volumeProperty->SetScalarOpacity(scalarOpacity);

	color->AddRGBPoint(-750.0, 0.08, 0.05, 0.03);
	color->AddRGBPoint(-350.0, 0.39, 0.25, 0.16);
	color->AddRGBPoint(-200.0, 0.80, 0.80, 0.80);
	color->AddRGBPoint(2750.0, 0.70, 0.70, 0.70);
	color->AddRGBPoint(3000.0, 0.35, 0.35, 0.35);
	volumeProperty->SetColor(color);

	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);
	renderer->AddVolume(volume);
	renderer->ResetCamera();
}

vtkDicomRenderer::vtkDicomRenderer(char* dirName){
	// TODO: Should be set dynamically, of course
	//reader->SetDirectoryName(dirName);
	reader->SetDirectoryName("../finalProject/DICOMs");
	reader->Update();
	imageData->ShallowCopy(reader->GetOutput());

	renderer->SetBackground(0.1, 0.2, 0.3);

	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(500, 500);

	renderWindowInteractor->SetInteractorStyle(interactorStyle);
	renderWindowInteractor->SetRenderWindow(renderWindow);

	volumeMapper->SetBlendModeToComposite();
	volumeMapper->SetRequestedRenderModeToGPU();
	volumeMapper->SetInputData(imageData);

	volumeProperty->ShadeOn();
	volumeProperty->SetInterpolationTypeToLinear();

	volumeProperty->SetAmbient(0.1);
	volumeProperty->SetDiffuse(0.9);
	volumeProperty->SetSpecular(0.2);
	volumeProperty->SetSpecularPower(10.0);

	gradientOpacity->AddPoint(0.0, 0.0);
	gradientOpacity->AddPoint(2000.0, 1.0);
	volumeProperty->SetGradientOpacity(gradientOpacity);

	scalarOpacity->AddPoint(-800.0, 0.0);
	scalarOpacity->AddPoint(-750.0, 1.0);
	scalarOpacity->AddPoint(-350.0, 1.0);
	scalarOpacity->AddPoint(-300.0, 0.0);
	scalarOpacity->AddPoint(-200.0, 0.0);
	scalarOpacity->AddPoint(-100.0, 1.0);
	scalarOpacity->AddPoint(1000.0, 0.0);
	scalarOpacity->AddPoint(2750.0, 0.0);
	scalarOpacity->AddPoint(2976.0, 1.0);
	scalarOpacity->AddPoint(3000.0, 0.0);
	volumeProperty->SetScalarOpacity(scalarOpacity);

	color->AddRGBPoint(-750.0, 0.08, 0.05, 0.03);
	color->AddRGBPoint(-350.0, 0.39, 0.25, 0.16);
	color->AddRGBPoint(-200.0, 0.80, 0.80, 0.80);
	color->AddRGBPoint(2750.0, 0.70, 0.70, 0.70);
	color->AddRGBPoint(3000.0, 0.35, 0.35, 0.35);
	volumeProperty->SetColor(color);

	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);
	renderer->AddVolume(volume);
	renderer->ResetCamera();
}

vtkDicomRenderer::vtkDicomRenderer(dicomSeries::ReaderType::Pointer reader) {

	// From the bridge class

	using CastingType = itk::CastImageFilter<dicomSeries::InputImageType, dicomSeries::OutputImageType>;
	using ConnectorType = itk::ImageToVTKImageFilter<dicomSeries::OutputImageType>;
	using IntensityFilter = itk::RescaleIntensityImageFilter< dicomSeries::InputImageType, dicomSeries::InputImageType >;

	CastingType::Pointer caster = CastingType::New();
  	ConnectorType::Pointer connector = ConnectorType::New();
	IntensityFilter::Pointer rescaleFilter = IntensityFilter::New();

	// Rescale the DICOM image that we read in 
	rescaleFilter->SetInput(reader->GetOutput());
	rescaleFilter->SetOutputMinimum(0);
  	rescaleFilter->SetOutputMaximum(255);

  	// Cast it to...the correct type? 
	caster->SetInput( rescaleFilter->GetOutput() ); 
	// Pass this to the ImageToVTKImageFilter connector and return it (to the VTK constructor)
	connector->SetInput(caster->GetOutput()); 
	connector->Update(); 

	// end bridge class


	imageData->DeepCopy(connector->GetOutput());

	renderer->SetBackground(0.1, 0.2, 0.3);

	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(500, 500);

	renderWindowInteractor->SetInteractorStyle(interactorStyle);
	renderWindowInteractor->SetRenderWindow(renderWindow);

	volumeMapper->SetBlendModeToComposite();
	volumeMapper->SetRequestedRenderModeToGPU();
	volumeMapper->SetInputData(imageData);

	volumeProperty->ShadeOn();
	volumeProperty->SetInterpolationTypeToLinear();

	volumeProperty->SetAmbient(0.1);
	volumeProperty->SetDiffuse(0.9);
	volumeProperty->SetSpecular(0.2);
	volumeProperty->SetSpecularPower(10.0);

	gradientOpacity->AddPoint(0.0, 0.0);
	gradientOpacity->AddPoint(2000.0, 1.0);
	volumeProperty->SetGradientOpacity(gradientOpacity);

	scalarOpacity->AddPoint(-800.0, 0.0);
	scalarOpacity->AddPoint(-750.0, 1.0);
	scalarOpacity->AddPoint(-350.0, 1.0);
	scalarOpacity->AddPoint(-300.0, 0.0);
	scalarOpacity->AddPoint(-200.0, 0.0);
	scalarOpacity->AddPoint(-100.0, 1.0);
	scalarOpacity->AddPoint(1000.0, 0.0);
	scalarOpacity->AddPoint(2750.0, 0.0);
	scalarOpacity->AddPoint(2976.0, 1.0);
	scalarOpacity->AddPoint(3000.0, 0.0);
	volumeProperty->SetScalarOpacity(scalarOpacity);

	color->AddRGBPoint(-750.0, 0.08, 0.05, 0.03);
	color->AddRGBPoint(-350.0, 0.39, 0.25, 0.16);
	color->AddRGBPoint(-200.0, 0.80, 0.80, 0.80);
	color->AddRGBPoint(2750.0, 0.70, 0.70, 0.70);
	color->AddRGBPoint(3000.0, 0.35, 0.35, 0.35);
	volumeProperty->SetColor(color);

	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);
	renderer->AddVolume(volume);
	renderer->ResetCamera();
}

void vtkDicomRenderer::render(){
  // This starts the event loop and as a side effect causes an initial render.
  renderWindow->Render();
  renderWindowInteractor->Start();
}