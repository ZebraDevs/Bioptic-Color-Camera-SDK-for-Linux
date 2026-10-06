#include "wx_pch.h"
#include "ZebraCameraDemoMain.h"

void ZebraCameraDemoFrame::OnFilePickerCtrlFirmwareFileChanged(wxFileDirPickerEvent& event)
{
    (void)event;

    firmware_file_ = std::string(static_cast<const char*>(event.GetPath()));
    wxLogMessage("%s: path=%s", __func__, firmware_file_);
}

void ZebraCameraDemoFrame::OnButtonUpdateClick(wxCommandEvent& event)
{

    (void)event;

    auto camera = GetCamera();
    if (camera && !firmware_file_.empty())
    {
        try
        {
        	camera_manager_client_->DownloadFirmware(camera, firmware_file_);
        }
        catch (std::exception& e)
        {
            wxString msg;
            msg.Printf(wxT("%s"), e.what());
            wxMessageBox(msg, _("Firmware Update"), wxICON_ERROR);
        }
    }

}

void ZebraCameraDemoFrame::OnButtonCancelClick(wxCommandEvent& event)
{

    (void)event;

    auto camera = GetCamera();
    if (camera)
    {
        try
        {
        	camera_manager_client_->CancelFirmwareDownload(camera);
        }
        catch (std::exception& e)
        {
            wxString msg;
            msg.Printf(wxT("%s"), e.what());
            wxMessageBox(msg, _("Firmware Update"), wxICON_ERROR);
        }
    }

}
