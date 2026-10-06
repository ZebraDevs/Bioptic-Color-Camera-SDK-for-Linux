#include "wx_pch.h"
#include "ZebraCameraDemoMain.h"

void ZebraCameraDemoFrame::PopulateVideoProfiles(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    std::vector<FrameType> frameTypes = camera->GetSupportedFrameTypes();

    for (FrameType& item: frameTypes)
    {
        char stritem[64];

        snprintf(stritem, sizeof(stritem), "%s, %d x %d, @%d fps",
         (FrameDataFormat::YUY2 == item.format) ? "YUY2" : 
         ((FrameDataFormat::UYVY == item.format) ? "UYVY" : "UNKNOWN"),
         item.width, 
         item.height, 
         item.framerate);

        ChoiceVideoProfiles->Append(wxString(stritem), new FrameType(item));
        
        image_resolution_ = std::to_string(frameTypes[0].width)+"x"+std::to_string(frameTypes[0].height);
    }

    if (ChoiceVideoProfiles->GetCount())
    {
        int selected_index = 0;
        ChoiceVideoProfiles->SetSelection(selected_index);

        ChangeCameraVideoProfile(camera, frameTypes[selected_index]);
    }
}

void ZebraCameraDemoFrame::ChangeCameraVideoProfile(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera, const FrameType& frame_type)
{
    if (CheckBoxContinuousEvents->GetValue())
    {
        camera->RemoveContinuousImageEventListener(*continuous_image_listener_);
    }
    if (CheckBoxDecodeEvents->GetValue())
    {
        camera->RemoveDecodeImageEventListener(*decode_image_listener_);
    }
    if (CheckBoxProduceEvents->GetValue())
    {
        camera->RemoveProduceImageEventListener(*produce_image_listener_);
    }
    if (CheckBoxSnapshotEvents->GetValue())
    {
        camera->RemoveSnapshotImageEventListener(*snapshot_image_listener_);
    }

    // Unregistering from bounding box detection while frame type is getting adjusted  
    PanelVideoDisplay-> bounding_box_detection = false;
	
    // Allocate frame buffer.
    image_buffer_.AllocateBuffer(frame_type.width, frame_type.height);

    produce_image_.AllocateBuffer(frame_type.width, frame_type.height);
    snapshot_image_.AllocateBuffer(frame_type.width, frame_type.height);
    decode_image_.AllocateBuffer(frame_type.width, frame_type.height);
    last_saved_image_.AllocateBuffer(frame_type.width, frame_type.height);

    PanelVideoDisplay->AllocateImageBuffer(frame_type.width, frame_type.height);

    // Set camera frame profile.
    camera->SetCurrentFrameType(frame_type);

    if (CheckBoxContinuousEvents->GetValue())
    {
        camera->AddContinuousImageEventListener(*continuous_image_listener_);
    }
    if (CheckBoxDecodeEvents->GetValue())
    {
        camera->AddDecodeImageEventListener(*decode_image_listener_);
    }
    if (CheckBoxProduceEvents->GetValue())
    {
        camera->AddProduceImageEventListener(*produce_image_listener_);
    }
    if (CheckBoxSnapshotEvents->GetValue())
    {
        camera->AddSnapshotImageEventListener(*snapshot_image_listener_);
    }
    //In here, the background is programetically set to prevent a crash from occuring.
    PanelVideoDisplay-> SetBackground();	

    // Un-checking the checkbox programetically after the frame type has been adjusted.
    if (CheckBoxDetectBoundingBox->GetValue()){	

        CheckBoxDetectBoundingBox->SetValue(false);
	
    }		
}

void ZebraCameraDemoFrame::OnChoiceVideoProfilesSelect(wxCommandEvent& event)
{

    (void)event;

    int index = ChoiceVideoProfiles->GetSelection();

    if (wxNOT_FOUND != index)
    {
        FrameType frametype = *(FrameType*)ChoiceVideoProfiles->GetClientData(index);

        wxLogMessage("%s: %d x %d, @ %d fps", __func__, frametype.width, frametype.height, frametype.framerate);

        ChangeCameraVideoProfile(GetCamera(), frametype);
        
        image_resolution_=std::to_string(frametype.width)+"x"+std::to_string(frametype.height);

	// Prompting the user to reset background to prevent the application from crashing
	wxMessageBox("Video profile changed. \nReset Background and enable Bounding Box detection if Bounding Box feature is required");
    }

}
