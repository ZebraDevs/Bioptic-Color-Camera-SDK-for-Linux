#include <wx/valnum.h>  // For wxIntegerValidator.
#include <wx/valgen.h>  // For wxGenericValidator.

#include "wx_pch.h"
#include "ZebraCameraDemoMain.h"

void ZebraCameraDemoFrame::PopulateAbsoluteExposureTime(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t min = 0, max = 0, val = 0, res = 0;

    try {
    	bool auto_supported = camera->AbsoluteExposureTime.IsAutoSupported();
    	CheckBoxExposureTimeAuto->Enable(auto_supported);

    	SliderAbsoluteExposureTime->Enable();
    	TextCtrlAbsoluteExposureTime->Enable();

    	if (auto_supported)
    	{
    		bool auto_enabled = camera->AbsoluteExposureTime.IsAutoEnabled();
    		CheckBoxExposureTimeAuto->SetValue(auto_enabled);

    		if (auto_enabled)
    		{
    			// Auto enabled. Disable the slider and text controls.
    			SliderAbsoluteExposureTime->Disable();
    			TextCtrlAbsoluteExposureTime->Disable();
    		}
    	}


    	min = camera->AbsoluteExposureTime.Minimum();
    	max = camera->AbsoluteExposureTime.Maximum();
    	val = camera->AbsoluteExposureTime.Value();
    	res = camera->AbsoluteExposureTime.Resolution();

    	ivalidator = (wxIntegerValidator<int>*)TextCtrlAbsoluteExposureTime->GetValidator();
    	ivalidator->SetMin(min);
    	ivalidator->SetMax(max);

    	property_abs_exposure_time = val;

    	SliderAbsoluteExposureTime->SetMin(min);
    	SliderAbsoluteExposureTime->SetMax(max);
    	SliderAbsoluteExposureTime->SetTickFreq(res);

    	ivalidator->TransferToWindow();
    	SliderAbsoluteExposureTime->GetValidator()->TransferToWindow();
    }
    catch(...) {
    }
}

void ZebraCameraDemoFrame::PopulateCameraTerminalInfo(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    PopulateAbsoluteExposureTime(camera);
}

void ZebraCameraDemoFrame::OnSliderAbsoluteExposureTimeCmdScrollChanged(wxScrollEvent& event)
{
    SliderAbsoluteExposureTime->GetValidator()->TransferFromWindow();
    TextCtrlAbsoluteExposureTime->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_abs_exposure_time=%d", __func__, event.GetPosition(), property_abs_exposure_time);
}

void ZebraCameraDemoFrame::OnTextCtrlAbsoluteExposureTimeText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlAbsoluteExposureTime->GetValidator()->TransferFromWindow();
    SliderAbsoluteExposureTime->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
        try
        {
        	if (camera->AbsoluteExposureTime.IsAutoSupported() &&
        			camera->AbsoluteExposureTime.IsAutoEnabled())
        	{
        		return;
        	}
        	camera->AbsoluteExposureTime.Value(property_abs_exposure_time);
        }
        catch (...) {}
    }

}

void ZebraCameraDemoFrame::OnCheckBoxExposureTimeAutoClick(wxCommandEvent& event)
{

    wxLogMessage("%s: checked=%d", __func__, event.IsChecked());

    auto camera = GetCamera();
    if (camera)
    {
        try
        {
        	camera->AbsoluteExposureTime.AutoEnable(event.IsChecked());
        	bool auto_enabled = camera->AbsoluteExposureTime.IsAutoEnabled();

        	wxLogMessage("%s: auto_enabled=%d", __func__, auto_enabled);

        	if (auto_enabled)
        	{
        		// Auto enabled. Disable the slider and text controls.
        		SliderAbsoluteExposureTime->Disable();
        		TextCtrlAbsoluteExposureTime->Disable();
        	}
        	else
        	{
        		SliderAbsoluteExposureTime->Enable();
        		TextCtrlAbsoluteExposureTime->Enable();

        		PopulateAbsoluteExposureTime(camera);
        	}
        }
        catch (...) {}
    }

}

void ZebraCameraDemoFrame::ClearCameraTerminalInfo()
{
    wxSlider *sliders[] = {
        SliderAbsoluteExposureTime
    };

    wxTextCtrl *textboxes[] = {
        TextCtrlAbsoluteExposureTime
    };

    for (unsigned int i = 0; i < sizeof(sliders)/sizeof(sliders[0]); i++)
    {
        wxSlider *slider = sliders[i];
        wxTextCtrl *txtbox = textboxes[i];

        txtbox->Clear();
        slider->Disable();
        txtbox->Disable();
    }

    CheckBoxExposureTimeAuto->Disable();
}
