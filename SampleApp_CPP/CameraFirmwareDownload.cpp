#include "CameraFirmwareDownload.h"

#include <wx/msgdlg.h>

#include "wx_pch.h"
#include "ZebraCameraDemoMain.h"

// Definition of the CAMERA_FIRMWARE_DOWNLOAD_EVENT
wxDEFINE_EVENT(CAMERA_FIRMWARE_DOWNLOAD_EVENT, wxCommandEvent);

FirmwareDownloadEventObserver::FirmwareDownloadEventObserver(ZebraCameraDemoFrame *frame):
    frame_(frame)
{
    wxLogMessage("%s", __func__);
}

void FirmwareDownloadEventObserver::EventReceived(FirmwareDownloadEventsArgs event)
{
    frame_->QueueFirmwareDownloadEvent(event);
}

void ZebraCameraDemoFrame::CreateFirmwareDownloadEventListener()
{
    // Bind firmware download event listener
    Bind(CAMERA_FIRMWARE_DOWNLOAD_EVENT, &ZebraCameraDemoFrame::OnCameraFirmwareDownloadEvent, this);

    firmware_download_event_listener_ = new FirmwareDownloadEventObserver(this);
    camera_manager_client_->AddFirmwareDownloadEventListener(*firmware_download_event_listener_);
}

void ZebraCameraDemoFrame::ReleaseFirmwareDownloadEventListener()
{
    if (firmware_download_event_listener_)
    {
    	camera_manager_client_->RemoveFirmwareDownloadEventListener(*firmware_download_event_listener_);
        delete firmware_download_event_listener_;
    }

    Unbind(CAMERA_FIRMWARE_DOWNLOAD_EVENT, &ZebraCameraDemoFrame::OnCameraFirmwareDownloadEvent, this);
}

void ZebraCameraDemoFrame::QueueFirmwareDownloadEvent(FirmwareDownloadEventsArgs fwstatus)
{
    wxCommandEvent *event = new wxCommandEvent(CAMERA_FIRMWARE_DOWNLOAD_EVENT, GetId());
    event->SetClientData(new FirmwareDownloadEventsArgs(fwstatus));
    QueueEvent(event);
}

void ZebraCameraDemoFrame::OnCameraFirmwareDownloadEvent(wxCommandEvent& event)
{
    FirmwareDownloadEventsArgs *fwstatus = (FirmwareDownloadEventsArgs*)event.GetClientData();

    if (fwstatus)
    {
        wxLogMessage("%s: total=%d, current=%d, status=%d, opcode=%d",
                     __func__,
                     fwstatus->GetTotalRecords(), fwstatus->GetCurrentRecord(), fwstatus->GetStatus(), fwstatus->GetOperationCode());
        GaugeFirmwareDownloadProgress->SetRange(fwstatus->GetTotalRecords());

        if (FirmwareDownloadEventsArgs::Status::kSuccessful == fwstatus->GetStatus())
        {
            // Update the progress.
            GaugeFirmwareDownloadProgress->SetValue(fwstatus->GetCurrentRecord());
        }
        else if (FirmwareDownloadEventsArgs::Status::kCanceled == fwstatus->GetStatus())
        {
           // Reset progress display.
            GaugeFirmwareDownloadProgress->SetValue(0);
        }

        if ((FirmwareDownloadEventsArgs::OperationCode::kSessionStop == fwstatus->GetOperationCode()) &&
            (fwstatus->GetTotalRecords() == fwstatus->GetCurrentRecord()))
        {
            try
            {
            	camera_manager_client_->InstallFirmware(GetCamera());
            }
            catch (std::exception& e)
            {
                wxString msg;
                msg.Printf(wxT("%s"), e.what());
                wxMessageBox(msg, _("Firmware Install"), wxICON_ERROR);
            }
        }
    }
}
