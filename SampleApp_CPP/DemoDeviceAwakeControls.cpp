#include <wx/valnum.h>  // For wxIntegerValidator.
#include <wx/valgen.h>  // For wxGenericValidator.

#include "wx_pch.h"
#include "ZebraCameraDemoMain.h"


void ZebraCameraDemoFrame::PopulateDeviceAwake(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{

    try
    {
    	VideoMode mode = camera->VideoModeSetting.Value();
    	// Change the session controller disable if video mode = off.
    	SetDeviceAwake(mode);
    }
    catch (...) {}
}

void ZebraCameraDemoFrame::ClearDeviceAwakeInfo()
{
    LedDeviceAwake->Disable();
}

void ZebraCameraDemoFrame::SetDeviceAwake(VideoMode mode)
{
    if(VideoMode::OFF == mode)
    {
        LedDeviceAwake->Disable();
    }
    else
    {
    	LedDeviceAwake->Enable();
    	LedDeviceAwake->SwitchOff();
    }
}
