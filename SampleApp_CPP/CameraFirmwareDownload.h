#ifndef CAMERA_FIRMWARE_DOWNLOAD_H_
#define CAMERA_FIRMWARE_DOWNLOAD_H_

#include <wx/wx.h>

#include "zebra_camera_manager_client.h"

using namespace zebra::camera_sdk;

class ZebraCameraDemoFrame;

/*
    Firmware download event listener.
*/
class FirmwareDownloadEventObserver: public FirmwareDownloadEventListener
{
public:
    FirmwareDownloadEventObserver(ZebraCameraDemoFrame *frame);
	void EventReceived(FirmwareDownloadEventsArgs event) override;

private:
    ZebraCameraDemoFrame *frame_;
};

// Declaration of the CAMERA_FIRMWARE_DOWNLOAD_EVENT. Notify when a camera object is created.
wxDECLARE_EVENT(CAMERA_FIRMWARE_DOWNLOAD_EVENT, wxCommandEvent);

#endif // CAMERA_FIRMWARE_DOWNLOAD_H_
