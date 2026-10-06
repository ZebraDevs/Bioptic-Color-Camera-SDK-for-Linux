#include <wx/valnum.h>  // For wxIntegerValidator.
#include <wx/valgen.h>  // For wxGenericValidator.

#include "wx_pch.h"
#include "ZebraCameraDemoMain.h"

void ZebraCameraDemoFrame::PopulateCameraAssetTrackingInfo(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxLogMessage("%s", __func__);

    try
    {
    	std::string serial_number = camera->GetSerialNumber();
    	std::string model_number = camera->GetModelNumber();
    	std::string firmware_version = camera->GetFirmwareVersion();
    	std::string hardware_version = camera->GetHardwareVersion();
    	std::string date_of_manufacture = camera->GetDateOfManufacture();
    	std::string date_of_program = camera->GetDateOfFirstProgram();
    	std::string date_of_service = camera->GetFirstServiceDate();

    	TextCtrlSerialNumber->SetValue(serial_number.c_str());
    	TextCtrlModelNumber->SetValue(model_number.c_str());
    	TextCtrlFirmwareVersion->SetValue(firmware_version.c_str());
    	TextCtrlHardwareVersion->SetValue(hardware_version.c_str());
    	TextCtrlDateOfManufacture->SetValue(date_of_manufacture.c_str());
    	TextCtrlDateOfFirstProgram->SetValue(date_of_program.c_str());
    	TextCtrlDateOfService->SetValue(date_of_service.c_str());
    }
    catch (...) {}
}

void ZebraCameraDemoFrame::PopulateVideoMode(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    ChoiceVideoMode->Enable();

    try
    {
    	VideoMode mode = camera->VideoModeSetting.Value();
    	property_videomode = (int)mode;
    	ChoiceVideoMode->GetValidator()->TransferToWindow();
    	wxLogMessage("%s: mode=%d", __func__, (int)mode);

	//Enabling the Reboot button if it has been greyed out during the camera reboot process
	ButtonReboot->Enable(true);		
	
    }
    catch (...) {}
}

void ZebraCameraDemoFrame::PopulateIlluminationMode(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    ChoiceIlluminationMode->Enable();

    try
    {
    	IlluminationMode mode = camera->IlluminationModeSetting.Value();
    	property_illuminationmode = (int)mode;
    	ChoiceIlluminationMode->GetValidator()->TransferToWindow();
    	wxLogMessage("%s: mode=%d", __func__, (int)mode);
    }
    catch (...) {}
}

void ZebraCameraDemoFrame::PopulatePowerUserMode(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    CheckBoxPowerUserMode->Enable();

    try
    {
    	PowerUserMode mode = camera->PowerUserModeSetting.Value();
    	property_powerusermode = (int)mode;
    	CheckBoxPowerUserMode->GetValidator()->TransferToWindow();

    	OnPowerUserModeChange(!property_powerusermode);

    	wxLogMessage("%s: mode=%d", __func__, (int)mode);
    }
    catch (...) {}
}

void ZebraCameraDemoFrame::PopulateExtensionUnit1Info(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxLogMessage("%s", __func__);

    if (camera)
    {
        try
        {
            PopulateVideoMode(camera);
            PopulateIlluminationMode(camera);
            PopulatePowerUserMode(camera);
        }
        catch (...)
        {

        }
    }
}

void ZebraCameraDemoFrame::OnChoiceVideoModeSelect(wxCommandEvent& event)
{

    (void)event;

    ChoiceVideoMode->GetValidator()->TransferFromWindow();
    wxLogMessage("%s: property_videomode=%d", __func__, property_videomode);

    SetDeviceAwake((VideoMode)property_videomode);

    auto camera = GetCamera();
    if (camera)
    {
        try
        {
        	camera->VideoModeSetting.Value((VideoMode)property_videomode);
        }
        catch (...) {}
    }

}

void ZebraCameraDemoFrame::OnChoiceIlluminationModeSelect(wxCommandEvent& event)
{

    (void)event;

    ChoiceIlluminationMode->GetValidator()->TransferFromWindow();
    wxLogMessage("%s: property_illuminationmode=%d", __func__, property_illuminationmode);

    auto camera = GetCamera();
    if (camera)
    {
        try
        {
        	camera->IlluminationModeSetting.Value((IlluminationMode)property_illuminationmode);
        }
        catch (...) {}
    }

}

void ZebraCameraDemoFrame::OnCheckBoxPowerUserModeClick(wxCommandEvent& event)
{

    (void)event;

    CheckBoxPowerUserMode->GetValidator()->TransferFromWindow();
    wxLogMessage("%s: property_powerusermode=%d", __func__, property_powerusermode);

    auto camera = GetCamera();
    if (camera)
    {
        try
        {
            camera->PowerUserModeSetting.Value((PowerUserMode)property_powerusermode);

            OnPowerUserModeChange(!property_powerusermode);
        }
        catch (...) {}
    }

}

void ZebraCameraDemoFrame::OnPowerUserModeChange(bool mode)
{
    wxLogMessage("%s: mode=%d", __func__, (int)mode);

    SliderGain->Enable(mode);
    TextCtrlGain->Enable(mode);

    if (!CheckBoxExposureTimeAuto->IsChecked())
    {
        // If exposure auto is checked, it's okay to enable/disable it. Otherwise don't enable the controls.
        SliderAbsoluteExposureTime->Enable(mode);
        TextCtrlAbsoluteExposureTime->Enable(mode);
        CheckBoxExposureTimeAuto->Enable(mode);
    }
    CheckBoxExposureTimeAuto->Enable(mode);

    if (!CheckBoxWhiteBalanceAuto->IsChecked())
    {
        // If white balance auto is checked, it's okay to enable/disable it. Otherwise don't enable the controls.
        SliderWhiteBalanceBlue->Enable(mode);
        SliderWhiteBalanceRed->Enable(mode);
        TextCtrlWhiteBalanceBlue->Enable(mode);
        TextCtrlWhiteBalanceRed->Enable(mode);
        CheckBoxWhiteBalanceAuto->Enable(mode);
    }
    CheckBoxWhiteBalanceAuto->Enable(mode);
}

void ZebraCameraDemoFrame::ClearExtensionUnit1Info()
{
    ChoiceVideoMode->Disable();
    ChoiceIlluminationMode->Disable();
    CheckBoxPowerUserMode->Disable();
}

void ZebraCameraDemoFrame::ClearCameraAssetTrackingInfo()
{
    TextCtrlSerialNumber->SetValue("");
    TextCtrlModelNumber->SetValue("");
    TextCtrlFirmwareVersion->SetValue("");
    TextCtrlHardwareVersion->SetValue("");
    TextCtrlDateOfManufacture->SetValue("");
    TextCtrlDateOfFirstProgram->SetValue("");
    TextCtrlDateOfService->SetValue("");
}

void ZebraCameraDemoFrame::SetVideoMode(VideoMode mode)
{
    auto camera = GetCamera();
    if (camera)
    {
        try
        {
            camera->VideoModeSetting.Value(mode);

            property_videomode = (int)mode;
            ChoiceVideoMode->GetValidator()->TransferToWindow();
            SetDeviceAwake(mode);

            wxLogMessage("%s: property_videomode=%d", __func__, property_videomode);
        }
        catch (...) {}
    }
}

