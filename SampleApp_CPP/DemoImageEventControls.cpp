#include "wx_pch.h"
#include "ZebraCameraDemoMain.h"

void ZebraCameraDemoFrame::OnCheckBoxContinuousEventsClick(wxCommandEvent& event)
{

    wxLogMessage("%s: check status=%d", __func__, event.IsChecked());

    auto camera = GetCamera();
    if (camera)
    {
        if (event.IsChecked())
        {
            camera->AddContinuousImageEventListener(*continuous_image_listener_);
        }
        else
        {
            camera->RemoveContinuousImageEventListener(*continuous_image_listener_);
            continuous_image_received_ = false ;
	    image_event_type_="";
        }
    }

}

void ZebraCameraDemoFrame::OnCheckBoxProduceEventsClick(wxCommandEvent& event)
{

    wxLogMessage("%s: check status=%d", __func__, event.IsChecked());

    auto camera = GetCamera();
    if (camera)
    {
        if (event.IsChecked())
        {
            camera->AddProduceImageEventListener(*produce_image_listener_);
        }
        else
        {
            camera->RemoveProduceImageEventListener(*produce_image_listener_);
	    image_event_type_="";

        }
    }

}

void ZebraCameraDemoFrame::OnCheckBoxSnapshotEventsClick(wxCommandEvent& event)
{

    wxLogMessage("%s: check status=%d", __func__, event.IsChecked());

    auto camera = GetCamera();
    if (camera)
    {
        if (event.IsChecked())
        {
            camera->AddSnapshotImageEventListener(*snapshot_image_listener_);
        }
        else
        {
            camera->RemoveSnapshotImageEventListener(*snapshot_image_listener_);
            image_event_type_="";

        }
    }

}

void ZebraCameraDemoFrame::OnCheckBoxDecodeEventsClick(wxCommandEvent& event)
{

    wxLogMessage("%s: check status=%d", __func__, event.IsChecked());

    auto camera = GetCamera();
    if (camera)
    {
        if (event.IsChecked())
        {
            camera->AddDecodeImageEventListener(*decode_image_listener_);
        }
        else
        {
            camera->RemoveDecodeImageEventListener(*decode_image_listener_);
            image_event_type_="";

        }
    }

}

void ZebraCameraDemoFrame::OnCheckBoxSessionEventsClick(wxCommandEvent& event)
{

    wxLogMessage("%s: check status=%d", __func__, event.IsChecked());

    auto camera = GetCamera();
    if(camera)
    {
        if (event.IsChecked())
        {
            camera->AddDecodeSessionStatusChangeEventListener(*decode_session_status_change_listener_);
        }
        else
        {
            camera->RemoveDecodeSessionStatusChangeEventListener(*decode_session_status_change_listener_);
        }
    }

}

void ZebraCameraDemoFrame::OnCheckBoxStreamEventsClick(wxCommandEvent& event)
{

    wxLogMessage("%s: check status=%d", __func__, event.IsChecked());

    auto camera = GetCamera();
    if(camera)
    {
        if (event.IsChecked())
        {

            camera->AddCameraStreamStatusChangeEventListener(*stream_status_change_event_listener_);

        }
        else
        {


            camera->RemoveCameraStreamStatusChangeEventListener(*stream_status_change_event_listener_);
        }
    }

}





void ZebraCameraDemoFrame::OnDirPickerCtrlSaveImageDirChanged(wxFileDirPickerEvent& event)
{
    (void)event;

    save_image_directory_path_ = std::string(static_cast<const char*>(event.GetPath()));
    wxLogMessage("%s: path=%s", __func__, save_image_directory_path_);
}

void ZebraCameraDemoFrame::OnButtonCaptureSnapshotClick(wxCommandEvent& event)
{

    (void)event;

    auto camera = GetCamera();
    if (camera)
    {
        Image snapshot = camera->CaptureSnapshot();

        zebra::image::ColorConverter converter;

        switch (snapshot.Format())
        {
        case ImageFormat::YUY2:
            converter = zebra::image::ColorConverter::YUY2_TO_RGB;
            break;
        case ImageFormat::UYVY:
            converter = zebra::image::ColorConverter::UYVY_TO_RGB;
            break;
        default:
            return;
        }

        wxLogMessage("%s: wxh: %d x %d", __func__, snapshot.Width(), snapshot.Height());

        // Convert to RGB.
        ImageData image = {snapshot.Width(), snapshot.Height(), snapshot.Stride(), snapshot.Length(), snapshot.Data()};
        zebra::camera_sdk::Image rgb = zebra::image::ConvertColor(converter, image);
        // Save snapshot image.
        image_buffer_.CopyToBuffer(rgb.Data(), rgb.Length());
        last_saved_image_.CopyToBuffer(rgb.Data(), rgb.Length());
        image_event_type_= "_cs";
        UpdateEventInformation("Snapshot","RGB", std::to_string((PanelVideoDisplay->image_data_size_)/1000),GetDateAndTime(),image_resolution_,"","","");

        QueueCaptureSnapshotEvent();

	snapshot_captured_from_ui = true;
    }

}

void ZebraCameraDemoFrame::OnChoiceImageFormatSelect(wxCommandEvent& event)
{
    image_file_format_ = (ImageFileFormat)event.GetSelection();

    wxLogMessage("%s: image_file_format_=%d", __func__, (int)image_file_format_);
}

void ZebraCameraDemoFrame::OnCheckBoxSaveImagesClick(wxCommandEvent& event)
{
    (void)event;
}

void ZebraCameraDemoFrame::ClearVideoEvents()
{
    wxLogMessage("%s", __func__);

    // Clear image event checkboxes.
    CheckBoxContinuousEvents->SetValue(false);
    CheckBoxProduceEvents->SetValue(false);
    CheckBoxSnapshotEvents->SetValue(false);
    CheckBoxDecodeEvents->SetValue(false);
}

void ZebraCameraDemoFrame::StopCameraVideo(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxLogMessage("%s", __func__);

    if (camera)
    {
        camera->RemoveContinuousImageEventListener(*continuous_image_listener_);
        camera->RemoveDecodeImageEventListener(*decode_image_listener_);
        camera->RemoveProduceImageEventListener(*produce_image_listener_);
        camera->RemoveSnapshotImageEventListener(*snapshot_image_listener_);
    }
}
/**
 * Method that saves the image of the last occurred event at the time of the button click
 * @param event
 */
void ZebraCameraDemoFrame::OnButtonSaveImageClick(wxCommandEvent& event)
{
    (void)event;
    
    
    if(image_event_type_ != ""){
        SaveImageOnButtonClick(last_saved_image_, image_event_type_);
	if(snapshot_captured_from_ui == true){
        	snapshot_captured_from_ui = false;
		image_event_type_="";
    	}
    }
    
    if(continuous_image_received_ == true){
        SaveImageOnButtonClick(image_buffer_,"_c");
    }
}
