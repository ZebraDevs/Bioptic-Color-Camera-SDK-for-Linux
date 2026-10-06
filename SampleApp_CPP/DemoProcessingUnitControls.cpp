#include <wx/valnum.h>  // For wxIntegerValidator.
#include <wx/valgen.h>  // For wxGenericValidator.

#include "wx_pch.h"
#include "ZebraCameraDemoMain.h"

#define WHITE_BALANCE_NUMBER_OF_FRACTION_BITS			12
#define WHITE_BALANCE_RANGE_MAX							0x4000
#define WHITE_BALANCE_RANGE_MIN							0

/**
 * Convert uint16_t value into 4.12 floating point value.
 * round it into 3 decimal points.
 */
static float ConvertUint16ToFloat(uint16_t actual_value, int number_of_fraction_bits)
{
	float return_vlue;
	char value_in_string[17];
	return_vlue = (float)actual_value / (float)(1 << number_of_fraction_bits);

	// round it to .3f
	sprintf(value_in_string, "%.3f", return_vlue);
	sscanf(value_in_string, "%f", &return_vlue);

	return return_vlue;
}

/**
 * Convert floating point vlue into uint16_t value.
 */
static uint16_t ConvertFloatToUint16(float actual_value, int number_of_fraction_bits)
{
	return (uint16_t)(actual_value * (1 << number_of_fraction_bits));
}

void ZebraCameraDemoFrame::PopulateBrightness(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t min = 0, max = 0, val = 0, res = 0;

    SliderBrightness->Enable();
    TextCtrlBrightness->Enable();

    min = camera->Brightness.Minimum();
    max = camera->Brightness.Maximum();
    val = camera->Brightness.Value();
    res = camera->Brightness.Resolution();

    ivalidator = (wxIntegerValidator<int>*)TextCtrlBrightness->GetValidator();
    ivalidator->SetMin(min);
    ivalidator->SetMax(max);

    property_brightness = val;

    SliderBrightness->SetMin(min);
    SliderBrightness->SetMax(max);
    SliderBrightness->SetTickFreq(res);

    ivalidator->TransferToWindow();
    SliderBrightness->GetValidator()->TransferToWindow();
}

void ZebraCameraDemoFrame::PopulateContrast(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t min = 0, max = 0, val = 0, res = 0;

    bool auto_supported = camera->Contrast.IsAutoSupported();
    CheckBoxContrastAuto->Enable(auto_supported);

    SliderContrast->Enable();
    TextCtrlContrast->Enable();

    if (auto_supported)
    {
        bool auto_enabled = camera->Contrast.IsAutoEnabled();
        CheckBoxContrastAuto->SetValue(auto_enabled);

        if (auto_enabled)
        {
            // Auto enabled. Disable the slider and text controls.
            SliderContrast->Disable();
            TextCtrlContrast->Disable();
        }
    }

    try {
        min = camera->Contrast.Minimum();
        max = camera->Contrast.Maximum();
        val = camera->Contrast.Value();
        res = camera->Contrast.Resolution();

        ivalidator = (wxIntegerValidator<int>*)TextCtrlContrast->GetValidator();
        ivalidator->SetMin(min);
        ivalidator->SetMax(max);

        property_contrast = val;

        SliderContrast->SetMin(min);
        SliderContrast->SetMax(max);
        SliderContrast->SetTickFreq(res);

        ivalidator->TransferToWindow();
        SliderContrast->GetValidator()->TransferToWindow();
    }
    catch (...) {
    }
}

void ZebraCameraDemoFrame::PopulateSaturation(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t min = 0, max = 0, val = 0, res = 0;

    SliderSaturation->Enable();
    TextCtrlSaturation->Enable();

    min = camera->Saturation.Minimum();
    max = camera->Saturation.Maximum();
    val = camera->Saturation.Value();
    res = camera->Saturation.Resolution();

    ivalidator = (wxIntegerValidator<int>*)TextCtrlSaturation->GetValidator();
    ivalidator->SetMin(min);
    ivalidator->SetMax(max);

    property_saturation = val;

    SliderSaturation->SetMin(min);
    SliderSaturation->SetMax(max);
    SliderSaturation->SetTickFreq(res);

    ivalidator->TransferToWindow();
    SliderSaturation->GetValidator()->TransferToWindow();
}

void ZebraCameraDemoFrame::PopulateSharpness(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t min = 0, max = 0, val = 0, res = 0;

    SliderSharpness->Enable();
    TextCtrlSharpness->Enable();

    min = camera->Sharpness.Minimum();
    max = camera->Sharpness.Maximum();
    val = camera->Sharpness.Value();
    res = camera->Sharpness.Resolution();

    ivalidator = (wxIntegerValidator<int>*)TextCtrlSharpness->GetValidator();
    ivalidator->SetMin(min);
    ivalidator->SetMax(max);

    property_sharpness = val;

    SliderSharpness->SetMin(min);
    SliderSharpness->SetMax(max);
    SliderSharpness->SetTickFreq(res);

    ivalidator->TransferToWindow();
    SliderSharpness->GetValidator()->TransferToWindow();
}

void ZebraCameraDemoFrame::PopulateGamma(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t min = 0, max = 0, val = 0, res = 0;

    SliderGamma->Enable();
    TextCtrlGamma->Enable();

    min = camera->Gamma.Minimum();
    max = camera->Gamma.Maximum();
    val = camera->Gamma.Value();
    res = camera->Gamma.Resolution();

    ivalidator = (wxIntegerValidator<int>*)TextCtrlGamma->GetValidator();
    ivalidator->SetMin(min);
    ivalidator->SetMax(max);

    property_gamma = val;

    SliderGamma->SetMin(min);
    SliderGamma->SetMax(max);
    SliderGamma->SetTickFreq(res);

    ivalidator->TransferToWindow();
    SliderGamma->GetValidator()->TransferToWindow();
}

void ZebraCameraDemoFrame::PopulateWhiteBalanceComponent(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxFloatingPointValidator<float>* fvalidator;
    WhiteBalance min, max, val, res;

    bool auto_supported = camera->WhiteBalanceComponent.IsAutoSupported();
    CheckBoxWhiteBalanceAuto->Enable(auto_supported);

    SliderWhiteBalanceBlue->Enable();
    TextCtrlWhiteBalanceBlue->Enable();

    SliderWhiteBalanceRed->Enable();
    TextCtrlWhiteBalanceRed->Enable();

    if (auto_supported)
    {
        bool auto_enabled = camera->WhiteBalanceComponent.IsAutoEnabled();
        CheckBoxWhiteBalanceAuto->SetValue(auto_enabled);

        if (auto_enabled)
        {
            // Auto enabled. Disable the slider and text controls.
            SliderWhiteBalanceBlue->Disable();
            TextCtrlWhiteBalanceBlue->Disable();

            SliderWhiteBalanceRed->Disable();
            TextCtrlWhiteBalanceRed->Disable();

            // Start value field refresh timer.
            auto_white_balance_monitor_timer_.Start(WHITE_BALANCE_POLLING_INTERVAL_IN_MILLISECONDS);
        }
        else
        {
        	auto_white_balance_monitor_timer_.Stop();
        }
    }

    try {
    	min = camera->WhiteBalanceComponent.Minimum();
    	max = camera->WhiteBalanceComponent.Maximum();
    	val = camera->WhiteBalanceComponent.Value();
    	res = camera->WhiteBalanceComponent.Resolution();

    	// Update blue component properties, but DO NOT UPDATE THE UI CONTROLLERS YET!
        fvalidator = (wxFloatingPointValidator<float>*)TextCtrlWhiteBalanceBlue->GetValidator();
        fvalidator->SetMin(ConvertUint16ToFloat(min.Blue(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS));
        fvalidator->SetMax(ConvertUint16ToFloat(max.Blue(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS));

        property_wb_blue = val.Blue();
        property_wb_blue_in_float = ConvertUint16ToFloat(val.Blue(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);

        SliderWhiteBalanceBlue->SetMin(min.Blue());
        SliderWhiteBalanceBlue->SetMax(max.Blue());
        SliderWhiteBalanceBlue->SetTickFreq(res.Blue());

        // Update red component properties
        fvalidator = (wxFloatingPointValidator<float>*)TextCtrlWhiteBalanceRed->GetValidator();
		fvalidator->SetMin(ConvertUint16ToFloat(min.Red(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS));
		fvalidator->SetMax(ConvertUint16ToFloat(max.Red(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS));

        property_wb_red = val.Red();
        property_wb_red_in_float = ConvertUint16ToFloat(val.Red(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);

        SliderWhiteBalanceRed->SetMin(min.Red());
        SliderWhiteBalanceRed->SetMax(max.Red());
        SliderWhiteBalanceRed->SetTickFreq(res.Red());

        // Finally transfer the property values to UI controllers.
        /*
         * IMPORTANT: If we update properties one after the other along with their UI controllers,
         * the control that is updated last will not reflect the actual value.
         * This is because property_wb_blue, property_wb_red are used inside UI control update handlers
         * OnTextCtrlWhiteBalanceBlueText, OnTextCtrlWhiteBalanceRedText and set to camera white-balance.
         * So, if we update property_wb_blue first and then invoke TransferToWindow for blue component
         * before updating property_wb_red, old value of the red component will be set to camera in
         * OnTextCtrlWhiteBalanceBlueText.
         * This is causing issues SSDK-11434, SSDK-11456.
         */
        TextCtrlWhiteBalanceBlue->GetValidator()->TransferToWindow();
        TextCtrlWhiteBalanceRed->GetValidator()->TransferToWindow();

        SliderWhiteBalanceBlue->GetValidator()->TransferToWindow();
        SliderWhiteBalanceRed->GetValidator()->TransferToWindow();
    }
    catch (...) {
    }
}

void ZebraCameraDemoFrame::PopulateBacklight(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t min = 0, max = 0, val = 0, res = 0;

    SliderBacklight->Enable();
    TextCtrlBacklight->Enable();

    min = camera->BacklightCompensation.Minimum();
    max = camera->BacklightCompensation.Maximum();
    val = camera->BacklightCompensation.Value();
    res = camera->BacklightCompensation.Resolution();

    ivalidator = (wxIntegerValidator<int>*)TextCtrlBacklight->GetValidator();
    ivalidator->SetMin(min);
    ivalidator->SetMax(max);

    property_backlight = val;

    SliderBacklight->SetMin(min);
    SliderBacklight->SetMax(max);
    SliderBacklight->SetTickFreq(res);

    ivalidator->TransferToWindow();
    SliderBacklight->GetValidator()->TransferToWindow();
}

void ZebraCameraDemoFrame::PopulateGain(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t min = 0, max = 0, val = 0, res = 0;

    SliderGain->Enable();
    TextCtrlGain->Enable();

    min = camera->Gain.Minimum();
    max = camera->Gain.Maximum();
    val = camera->Gain.Value();
    res = camera->Gain.Resolution();

    ivalidator = (wxIntegerValidator<int>*)TextCtrlGain->GetValidator();
    ivalidator->SetMin(min);
    ivalidator->SetMax(max);

    property_gain = val;

    SliderGain->SetMin(min);
    SliderGain->SetMax(max);
    SliderGain->SetTickFreq(res);

    ivalidator->TransferToWindow();
    SliderGain->GetValidator()->TransferToWindow();
}

void ZebraCameraDemoFrame::PopulateProcessingUnitInfo(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxLogMessage("%s", __func__);

    if (camera)
    {
        try
        {
            PopulateBrightness(camera);
            PopulateContrast(camera);
            PopulateSaturation(camera);
            PopulateSharpness(camera);
            PopulateGamma(camera);
            PopulateWhiteBalanceComponent(camera);
            PopulateBacklight(camera);
            PopulateGain(camera);
        }
        catch (...) {}
    }
}


void ZebraCameraDemoFrame::OnSliderBrightnessCmdScrollChanged(wxScrollEvent& event)
{
    SliderBrightness->GetValidator()->TransferFromWindow();
    TextCtrlBrightness->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_brightness=%d", __func__, event.GetPosition(), property_brightness);
}

void ZebraCameraDemoFrame::OnSliderContrastCmdScrollChanged(wxScrollEvent& event)
{
    SliderContrast->GetValidator()->TransferFromWindow();
    TextCtrlContrast->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_contrast=%d", __func__, event.GetPosition(), property_contrast);
}

void ZebraCameraDemoFrame::OnSliderSharpnessCmdScrollChanged(wxScrollEvent& event)
{
    SliderSharpness->GetValidator()->TransferFromWindow();
    TextCtrlSharpness->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_sharpness=%d", __func__, event.GetPosition(), property_sharpness);
}

void ZebraCameraDemoFrame::OnSliderGammaCmdScrollChanged(wxScrollEvent& event)
{
    SliderGamma->GetValidator()->TransferFromWindow();
    TextCtrlGamma->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_gamma=%d", __func__, event.GetPosition(), property_gamma);
}

void ZebraCameraDemoFrame::OnSliderWhiteBalanceBlueCmdScrollChanged(wxScrollEvent& event)
{
    SliderWhiteBalanceBlue->GetValidator()->TransferFromWindow();
    property_wb_blue_in_float = ConvertUint16ToFloat(property_wb_blue, WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);
    TextCtrlWhiteBalanceBlue->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_wb_red_in_float=%f", __func__, event.GetPosition(), property_wb_blue_in_float);
}

void ZebraCameraDemoFrame::OnSliderWhiteBalanceRedCmdScrollChanged(wxScrollEvent& event)
{
    SliderWhiteBalanceRed->GetValidator()->TransferFromWindow();
    property_wb_red_in_float = ConvertUint16ToFloat(property_wb_red, WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);
    TextCtrlWhiteBalanceRed->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_wb_red_in_float=%f", __func__, event.GetPosition(), property_wb_red_in_float);
}

void ZebraCameraDemoFrame::OnSliderBacklightCmdScrollChanged(wxScrollEvent& event)
{
    SliderBacklight->GetValidator()->TransferFromWindow();
    TextCtrlBacklight->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_backlight=%d", __func__, event.GetPosition(), property_backlight);
}

void ZebraCameraDemoFrame::OnSliderGainCmdScrollChanged(wxScrollEvent& event)
{
    SliderGain->GetValidator()->TransferFromWindow();
    TextCtrlGain->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_gain=%d", __func__, event.GetPosition(), property_gain);
}

void ZebraCameraDemoFrame::OnSliderSaturationCmdScrollChanged(wxScrollEvent& event)
{
    SliderSaturation->GetValidator()->TransferFromWindow();
    TextCtrlSaturation->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_saturation=%d", __func__, event.GetPosition(), property_saturation);
}

void ZebraCameraDemoFrame::OnTextCtrlBrightnessText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlBrightness->GetValidator()->TransferFromWindow();
    SliderBrightness->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->Brightness.Value(property_brightness);
    	}
    	catch (...) {}
    }

}

void ZebraCameraDemoFrame::OnTextCtrlContrastText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlContrast->GetValidator()->TransferFromWindow();
    SliderContrast->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		if (camera->Contrast.IsAutoSupported() &&
    				camera->Contrast.IsAutoEnabled())
    		{
    			return;
    		}
    		camera->Contrast.Value(property_contrast);
    	}
    	catch (...) {}
    }

}

void ZebraCameraDemoFrame::OnTextCtrlSaturationText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlSaturation->GetValidator()->TransferFromWindow();
    SliderSaturation->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->Saturation.Value(property_saturation);
    	}
    	catch (...) {}
    }

}

void ZebraCameraDemoFrame::OnTextCtrlSharpnessText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlSharpness->GetValidator()->TransferFromWindow();
    SliderSharpness->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->Sharpness.Value(property_sharpness);
    	}
    	catch (...) {}
    }

}

void ZebraCameraDemoFrame::OnTextCtrlGammaText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlGamma->GetValidator()->TransferFromWindow();
    SliderGamma->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->Gamma.Value(property_gamma);
    	}
    	catch (...) {}
    }

}

void ZebraCameraDemoFrame::OnTextCtrlWhiteBalanceBlueText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlWhiteBalanceBlue->GetValidator()->TransferFromWindow();

    SliderWhiteBalanceBlue->GetValidator()->TransferToWindow();

    property_wb_blue = (uint16_t)ConvertFloatToUint16(property_wb_blue_in_float, WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);

    SliderWhiteBalanceBlue->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		if (camera->WhiteBalanceComponent.IsAutoSupported() &&
    				camera->WhiteBalanceComponent.IsAutoEnabled())
    		{
    			return;
    		}
    		wxLogMessage("%s: property_wb_blue=%d, property_wb_red=%d", __func__, property_wb_blue, property_wb_red);

    		camera->WhiteBalanceComponent.Value(WhiteBalance((uint16_t)property_wb_blue, (uint16_t)property_wb_red));
    	}
    	catch (...) {}
    }

}

void ZebraCameraDemoFrame::OnTextCtrlWhiteBalanceRedText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlWhiteBalanceRed->GetValidator()->TransferFromWindow();
    SliderWhiteBalanceRed->GetValidator()->TransferToWindow();

    property_wb_red = (uint16_t)ConvertFloatToUint16(property_wb_red_in_float, WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);

	SliderWhiteBalanceRed->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		if (camera->WhiteBalanceComponent.IsAutoSupported() &&
    				camera->WhiteBalanceComponent.IsAutoEnabled())
    		{
    			return;
    		}
    		wxLogMessage("%s: property_wb_blue=%d, property_wb_red=%d", __func__, property_wb_blue, property_wb_red);

    		camera->WhiteBalanceComponent.Value(WhiteBalance((uint16_t)property_wb_blue, (uint16_t)property_wb_red));
    	}
    	catch (...) {}
    }

}

void ZebraCameraDemoFrame::OnTextCtrlBacklightText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlBacklight->GetValidator()->TransferFromWindow();
    SliderBacklight->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->BacklightCompensation.Value(property_backlight);
    	}
    	catch (...) {}
    }

}

void ZebraCameraDemoFrame::OnTextCtrlGainText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlGain->GetValidator()->TransferFromWindow();
    SliderGain->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->Gain.Value(property_gain);
    	}
    	catch (...) {}
    }

}

void ZebraCameraDemoFrame::OnCheckBoxContrastAutoClick(wxCommandEvent& event)
{

    wxLogMessage("%s: checked=%d", __func__, event.IsChecked());

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->Contrast.AutoEnable(event.IsChecked());
    		bool auto_enabled = camera->Contrast.IsAutoEnabled();

    		if (auto_enabled)
    		{
    			// Auto enabled. Disable the slider and text controls.
    			SliderContrast->Disable();
    			TextCtrlContrast->Disable();
    		}
    		else
    		{
    			SliderContrast->Enable();
    			TextCtrlContrast->Enable();

    			PopulateContrast(camera);
    		}
    	}
    	catch (...) {}
    }

}

void ZebraCameraDemoFrame::OnCheckBoxWhiteBalanceAutoClick(wxCommandEvent& event)
{

    wxLogMessage("%s: checked=%d", __func__, event.IsChecked());

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->WhiteBalanceComponent.AutoEnable(event.IsChecked());
    		bool auto_enabled = camera->WhiteBalanceComponent.IsAutoEnabled();

    		wxLogMessage("%s: auto_enabled=%d", __func__, auto_enabled);

    		if (auto_enabled)
    		{
    			// Auto enabled. Disable the slider and text controls.
    			SliderWhiteBalanceBlue->Disable();
    			TextCtrlWhiteBalanceBlue->Disable();

    			SliderWhiteBalanceRed->Disable();
    			TextCtrlWhiteBalanceRed->Disable();

    			// Start value field refresh timer.
    			auto_white_balance_monitor_timer_.Start(WHITE_BALANCE_POLLING_INTERVAL_IN_MILLISECONDS);
    		}
    		else
    		{
    			SliderWhiteBalanceBlue->Enable();
    			TextCtrlWhiteBalanceBlue->Enable();

    			SliderWhiteBalanceRed->Enable();
    			TextCtrlWhiteBalanceRed->Enable();

    			PopulateWhiteBalanceComponent(camera);

    			// Stop value field refresh timer.
    			auto_white_balance_monitor_timer_.Stop();
    		}
    	}
    	catch (...) {}
    }

}

void ZebraCameraDemoFrame::OnAutoWhiteBalanceUpdateTimer(wxTimerEvent& event)
{

    (void)event;

    wxLogMessage("%s", __func__);

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    	    // Get the values.
    		WhiteBalance white_balance = camera->WhiteBalanceComponent.Value();
    		property_wb_red = white_balance.Red();
    		property_wb_red_in_float = ConvertUint16ToFloat(white_balance.Red(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);
    		property_wb_blue = white_balance.Blue();
    		property_wb_blue_in_float = ConvertUint16ToFloat(white_balance.Blue(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);

    		// Transfer the values to controls.
    		TextCtrlWhiteBalanceRed->GetValidator()->TransferToWindow();
    		TextCtrlWhiteBalanceBlue->GetValidator()->TransferToWindow();

    		SliderWhiteBalanceRed->GetValidator()->TransferToWindow();
    		SliderWhiteBalanceBlue->GetValidator()->TransferToWindow();
    	}
    	catch (...) {}
    }

}

void ZebraCameraDemoFrame::ClearProcessingUnitInfo()
{
    wxSlider *sliders[] = {
        SliderBacklight,
        SliderBrightness,
        SliderContrast,
        SliderGain,
        SliderGamma,
        SliderSaturation,
        SliderSharpness,
        SliderWhiteBalanceBlue,
        SliderWhiteBalanceRed,
    };

    wxTextCtrl *textboxes[] = {
        TextCtrlBacklight,
        TextCtrlBrightness,
        TextCtrlContrast,
        TextCtrlGain,
        TextCtrlGamma,
        TextCtrlSaturation,
        TextCtrlSharpness,
        TextCtrlWhiteBalanceBlue,
        TextCtrlWhiteBalanceRed
    };

    for (unsigned int i = 0; i < sizeof(sliders)/sizeof(sliders[0]); i++)
    {
        wxSlider *slider = sliders[i];
        wxTextCtrl *txtbox = textboxes[i];

        txtbox->Clear();
        slider->Disable();
        txtbox->Disable();
    }

    CheckBoxContrastAuto->Disable();
    CheckBoxWhiteBalanceAuto->Disable();

    auto_white_balance_monitor_timer_.Stop();
}
