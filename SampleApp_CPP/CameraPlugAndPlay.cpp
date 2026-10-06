/*
    Plug-and-play listener implementation.
*/

#include "CameraPlugAndPlay.h"

#include <string>

#include "ZebraCameraDemoMain.h"

// Definition of the CAMERA_SELECTED_EVENT
wxDEFINE_EVENT(CAMERA_SELECTED_EVENT, wxCommandEvent);

// Definition of the CAMERA_DESELECTED_EVENT
wxDEFINE_EVENT(CAMERA_DESELECTED_EVENT, wxCommandEvent);


AttachedEventObserver::AttachedEventObserver(ZebraCameraDemoFrame *frame):
    frame_(frame)
{
    wxLogMessage("%s", __func__);
}

void AttachedEventObserver::Attached(zebra::DeviceInfo info)
{
    wxLogMessage("%s: SN: %s, (%s)", __func__, info.serial_number, info.device_path);

    frame_->QueueCameraArrivedEvent(info);
}

DetachedEventObserver::DetachedEventObserver(ZebraCameraDemoFrame *frame):
    frame_(frame)
{
    wxLogMessage("%s", __func__);
}

void DetachedEventObserver::Detached(zebra::DeviceInfo info)
{
    wxLogMessage("%s: SN: %s, (%s)", __func__, info.serial_number, info.device_path);
    frame_->ResetFirmwareUpdateProgressBar();
    frame_->QueueCameraLeftEvent(info);
}

void ZebraCameraDemoFrame::CreatePnpListeners()
{
    wxLogMessage("%s", __func__);

    // Bind camera-selected listener
    Bind(CAMERA_SELECTED_EVENT, &ZebraCameraDemoFrame::OnCameraArrivedEvent, this);

    // Bind camera-deselected listener
    Bind(CAMERA_DESELECTED_EVENT, &ZebraCameraDemoFrame::OnCameraLeftEvent, this);

    attached_listener_ = new AttachedEventObserver(this);
    detached_listener_ = new DetachedEventObserver(this);

    device_manager_.AddDeviceAttachedListener(*attached_listener_);
    device_manager_.AddDeviceDetachedListener(*detached_listener_);
}


void ZebraCameraDemoFrame::ReleasePnpListeners()
{
    wxLogMessage("%s", __func__);

    if (attached_listener_)
    {
        device_manager_.RemoveDeviceAttachedListener(*attached_listener_);
        delete attached_listener_;
    }
    if (detached_listener_)
    {
        device_manager_.RemoveDeviceDetachedListener(*detached_listener_);
        delete detached_listener_;
    }

    // Unbind camera-selected listener
    Unbind(CAMERA_SELECTED_EVENT, &ZebraCameraDemoFrame::OnCameraArrivedEvent, this);

    // Unbind camera-deselected listener
    Unbind(CAMERA_DESELECTED_EVENT, &ZebraCameraDemoFrame::OnCameraLeftEvent, this);
}

void ZebraCameraDemoFrame::QueueCameraArrivedEvent(zebra::DeviceInfo info)
{
    wxLogMessage("%s", __func__);

    wxCommandEvent *event = new wxCommandEvent(CAMERA_SELECTED_EVENT, GetId());
    event->SetClientData(new zebra::DeviceInfo(info));
    QueueEvent(event);
}

void ZebraCameraDemoFrame::QueueCameraLeftEvent(zebra::DeviceInfo info)
{
    wxLogMessage("%s", __func__);
    ResetFirmwareUpdateProgressBar();
    wxCommandEvent *event = new wxCommandEvent(CAMERA_DESELECTED_EVENT, GetId());
    event->SetClientData(new zebra::DeviceInfo(info));
    QueueEvent(event);
}

void ZebraCameraDemoFrame::QueueAlreadyAttachedCameraEvents()
{
	wxLogMessage("%s", __func__);

	std::vector<zebra::DeviceInfo> existing_dev_info = device_manager_.EnumerateDevices();
	for (zebra::DeviceInfo& info: existing_dev_info)
	{
		QueueCameraArrivedEvent(info);
	}
}

void ZebraCameraDemoFrame::OnCameraArrivedEvent(wxCommandEvent& event)
{

    wxLogMessage("%s", __func__);

    zebra::DeviceInfo *info = (zebra::DeviceInfo*)event.GetClientData();
    if (info)
    {
        wxLogMessage("%s: vid=%x, pid=%x, sn=%s, path=%s", __func__, info->vid, info->pid, info->serial_number, info->device_path);

        std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>
            *client_data = new std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>
            (*info, nullptr);

        // Add this to the choice list.
        std::string item_name = client_data->first.device_path;
        ChoiceSelectedCamera->Append(wxString(item_name.c_str()), client_data);

        if (wxNOT_FOUND == ChoiceSelectedCamera->GetSelection())
        {
            // We have a new camera and nothing has been selected yet, so select the newly arrived camera.
            try
            {
                client_data->second = camera_manager_client_->CreateZebraCamera(client_data->first);    // Create the camera.
                ChoiceSelectedCamera->SetSelection(ChoiceSelectedCamera->GetCount() - 1);       // Set it as the current selection.

                PopulateCameraProperties(client_data->second);
            }
            catch (std::exception& e)
            {
                wxMessageBox(e.what(), "Error");
            }
        }
    }

}

void ZebraCameraDemoFrame::OnCameraLeftEvent(wxCommandEvent& event)
{

    wxLogMessage("%s", __func__);

    zebra::DeviceInfo *info = (zebra::DeviceInfo*)event.GetClientData();
    unsigned int selected = ChoiceSelectedCamera->GetSelection();

    if (info)
    {
        wxLogMessage("%s: vid=%x, pid=%x, sn=%s, path=%s, selected=%d",
        __func__, info->vid, info->pid, info->serial_number, info->device_path, selected);

        for (unsigned int i = 0; i < ChoiceSelectedCamera->GetCount(); i++)
        {
            std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>
                *client_data = (std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>*)
                                ChoiceSelectedCamera->GetClientData(i);
            if (client_data->first.device_path == info->device_path)
            {
                wxLogMessage("%s: camera left %d", __func__, i);

                // If this is the currently selected camera, then release it.
                if (i == selected)
                {
                    
                    /**
                     * stopping image/video is handled in client library itself when
                     * detaching a camera. StopCameraVideo(client_data->second); was using 
                     * for stopping.
					 * Delete the client. Unlike in single-client camera, multi-client client is still valid if this is a reboot.
                	 * So, if we do this last (i.e. before ClearAllCameraProperties), old values will be set to the camera
                	 * if the detach cause is a reboot.
                     */
                    ResetFirmwareUpdateProgressBar();
                    ClearAllCameraProperties();

                    client_data->second = nullptr;
                }
                // Delete the item.
                ChoiceSelectedCamera->Delete(i);
                break;
            }
        }
    }
    
}
