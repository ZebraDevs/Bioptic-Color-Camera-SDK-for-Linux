#include "wx_pch.h"
#include "ZebraCameraDemoMain.h"

void ZebraCameraDemoFrame::OnButtonSetPropertyDefaultsClick(wxCommandEvent& event)
{

    (void)event;

    auto camera = GetCamera();
    if (camera)
    {
        camera->SetDefaults();

        
        /**
         * Uncomment the following two methods if it is needed to stop any video events and clear video event checkboxes.
         */
            //StopCameraVideo(camera);
            //ClearVideoEvents();
        
        /**
         * Update the UI.
         */ 
        PopulateCameraProperties(camera);
    }

}

void ZebraCameraDemoFrame::OnButtonRebootClick(wxCommandEvent& event)
{

    (void)event;

    auto camera = GetCamera();
    if (camera)
    {
        /**
          * stopping image/video is handled in client library itself when
          * detaching a camera. StopCameraVideo(camera); was using 
          * for stopping
          */ 

	// Greying out the Reboot button until the camera has fully completed the reboot process.
	ButtonReboot->Enable(false);
    	camera_manager_client_->Reboot(camera);
        ClearAllCameraProperties();        
        
    }
            
}



void ZebraCameraDemoFrame::OnButtonWriteToFlashClick(wxCommandEvent& event)
{

    (void)event;

    auto camera = GetCamera();
    if (camera)
    {
        camera->WriteToFlash();
    }
}

/**
 * Method takes the current frame on display as the background for bounding box detection
 */
void ZebraCameraDemoFrame::OnButtonSetBackgroundClick(wxCommandEvent& event)
{  
    (void)event;
    PanelVideoDisplay-> SetBackground();
}

/**
 *Method that is responsible for assigning boolean values to variable bounding_box_detection based on the checkbox selection
 */
void ZebraCameraDemoFrame::OnCheckBoxDetectBoundingBoxClick(wxCommandEvent& event)
{
    if(event.IsChecked()){        
        PanelVideoDisplay-> bounding_box_detection = true ;
    }else{          
        PanelVideoDisplay-> bounding_box_detection = false ;
    }
}
