/*
    Image frame handling and listener implementation.
*/

#include "CameraImageEvents.h"

#include <cstring>
#include <fstream>
#include <sys/time.h> 

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "ImageBuffer.h"
#include "ZebraCameraDemoMain.h"
#include "image_converter.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <iomanip>



// Definition of the CAPTURE_SNAPSHOT_EVENT
wxDEFINE_EVENT(CAPTURE_SNAPSHOT_EVENT, wxCommandEvent);

// Definition of the CONTINUOUS_IMAGE_EVENT
wxDEFINE_EVENT(CONTINUOUS_IMAGE_EVENT, wxCommandEvent);

// Definition of the PRODUCE_IMAGE_EVENT.
wxDEFINE_EVENT(PRODUCE_IMAGE_EVENT, wxCommandEvent);

// Definition of the SNAPSHOT_IMAGE_EVENT.
wxDEFINE_EVENT(SNAPSHOT_IMAGE_EVENT, wxCommandEvent);

// Definition of the DECODE_IMAGE_EVENT.
wxDEFINE_EVENT(DECODE_IMAGE_EVENT, wxCommandEvent);

// Definition of the DECODE_SESSION_STATUS_CHANGE_EVENT.
wxDEFINE_EVENT(DECODE_SESSION_STATUS_CHANGE_EVENT,wxCommandEvent);

// Definition of the TOWER_PLATTER_IMAGE_EVENT.
wxDEFINE_EVENT(TOWER_PLATTER_IMAGE_EVENT, wxCommandEvent);

wxDEFINE_EVENT(STREAM_STATUS_CHANGE_EVENT,wxCommandEvent);

/**
 * Replace any non-printable characters in decode data with spaces.
 */
static std::string GetEncodedDecodeData(std::string& decode_data)
{
	std::string temp_decode_data = "";
	auto it = decode_data.begin();
	for (; it < decode_data.end(); it++)
	{
		if (*it < 0x20)
		{
			temp_decode_data.append(" ");
		}
		else
		{
			temp_decode_data.append(1, *it);
		}
	}
	return temp_decode_data;
}

ContinuousImageObserver::ContinuousImageObserver(ZebraCameraDemoFrame *frame):
    frame_(frame)
{
    wxLogMessage("%s", __func__);
}

void ContinuousImageObserver::ImageReceived(ImageEventData image, ImageEventMetaData md)
{
	(void)md;

	zebra::image::ColorConverter converter;

	switch (image.format)
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

	wxLogMessage("%s: wxh: %d x %d", __func__, image.image.width, image.image.height);

	zebra::camera_sdk::Image rgb = zebra::image::ConvertColor(converter, image.image);

    frame_->image_buffer_.CopyToBuffer(rgb.Data(), rgb.Length());

    frame_->QueueContinuousImageEvent();

    frame_ ->continuous_image_received_ = true ;
}

ProduceImageObserver::ProduceImageObserver(ZebraCameraDemoFrame *frame):
    frame_(frame)
{
    wxLogMessage("%s", __func__);
}

void ProduceImageObserver::ImageReceived(ImageEventData image, ImageEventMetaData md)
{
    (void)image;
	(void)md;

    zebra::image::ColorConverter converter;

	switch (image.format)
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

	zebra::camera_sdk::Image rgb = zebra::image::ConvertColor(converter, image.image);

    frame_->produce_image_.CopyToBuffer(rgb.Data(), rgb.Length());
    
    frame_->last_saved_image_.CopyToBuffer(rgb.Data(), rgb.Length());
    
    frame_ -> image_event_type_ = "_p";


    float final_weight;
    std::string weight_unit = "";
    	

    if(md.weight_unit == 50){

        weight_unit = "N/A";
	final_weight = md.weight_data;

    }else if(md.weight_unit == 49 ){

        weight_unit = "lb";
	final_weight = md.weight_data;


    }else if(md.weight_unit == 48){

        weight_unit = "kg";
	final_weight = (float)md.weight_data / 1000;

    }	

    std::string weight_data = std::to_string(final_weight);
    
    std::string weight_unit_data = weight_data+" "+weight_unit ;

    frame_->QueueProduceImageEvent(weight_unit_data);
}

SnapshotImageObserver::SnapshotImageObserver(ZebraCameraDemoFrame *frame):
    frame_(frame)
{
    wxLogMessage("%s", __func__);
}

void SnapshotImageObserver::ImageReceived(ImageEventData image, ImageEventMetaData md)
{
    (void)image;
	(void)md;

	zebra::image::ColorConverter converter;

	switch (image.format)
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

	zebra::camera_sdk::Image rgb = zebra::image::ConvertColor(converter, image.image);
    frame_->snapshot_image_.CopyToBuffer(rgb.Data(), rgb.Length());
    
    frame_->last_saved_image_.CopyToBuffer(rgb.Data(), rgb.Length());
    
    frame_-> image_event_type_ = "_s";

    frame_->QueueSnapshotImageEvent();
}

DecodeImageObserver::DecodeImageObserver(ZebraCameraDemoFrame *frame):
    frame_(frame)
{
    wxLogMessage("%s", __func__);
}

void DecodeImageObserver::ImageReceived(ImageEventData image, ImageEventMetaData md)
{
    (void)image;
	(void)md;

	zebra::image::ColorConverter converter;

	switch (image.format)
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

	zebra::camera_sdk::Image rgb = zebra::image::ConvertColor(converter, image.image);
    frame_->decode_image_.CopyToBuffer(rgb.Data(), rgb.Length());
    
    frame_->last_saved_image_.CopyToBuffer(rgb.Data(), rgb.Length());

    std::string decode_data = GetEncodedDecodeData(md.decode_data);
    frame_->QueueDecodeImageEvent(decode_data);
}

DecodeSessionStatusChangeEventObserver::DecodeSessionStatusChangeEventObserver(ZebraCameraDemoFrame *frame):
    frame_(frame)
{
    wxLogMessage("%s", __func__);
}

void DecodeSessionStatusChangeEventObserver::DecodeSessionStatusChanged(DecodeSessionStatus status)
{
	frame_->QueueDecodeSessionStatusChangeEvent(status);
}

CameraStreamStatusChangeEventObserver::CameraStreamStatusChangeEventObserver(ZebraCameraDemoFrame *frame):
frame_(frame)
{

    wxLogMessage("%s", __func__);
}

void CameraStreamStatusChangeEventObserver::CameraStreamStatusChanged(CameraStreamStatus status)
{
    frame_->QueueStreamStatusChangeEvent(status);
}

void ZebraCameraDemoFrame::QueueProduceImageEvent(std::string& weight_unit_data)
{
    wxLogMessage("%s", __func__);

    wxCommandEvent *event = new wxCommandEvent(PRODUCE_IMAGE_EVENT, GetId());
    event->SetString(wxString(weight_unit_data));	
    QueueEvent(event);
}

void ZebraCameraDemoFrame::QueueSnapshotImageEvent()
{
    wxCommandEvent *event = new wxCommandEvent(SNAPSHOT_IMAGE_EVENT, GetId());
    QueueEvent(event);
}

void ZebraCameraDemoFrame::QueueDecodeImageEvent(std::string& decode_data)
{
    wxCommandEvent *event = new wxCommandEvent(DECODE_IMAGE_EVENT, GetId());
    event->SetString(wxString(decode_data));
    QueueEvent(event);
}

void ZebraCameraDemoFrame::QueueContinuousImageEvent()
{
    wxCommandEvent *event = new wxCommandEvent(CONTINUOUS_IMAGE_EVENT, GetId());
    event->SetString("Frame Ready");
    QueueEvent(event);
}

void ZebraCameraDemoFrame::QueueCaptureSnapshotEvent()
{
    wxCommandEvent *event = new wxCommandEvent(CAPTURE_SNAPSHOT_EVENT, GetId());
    event->SetString("Frame Ready");
    QueueEvent(event);
}

void ZebraCameraDemoFrame::QueueDecodeSessionStatusChangeEvent(DecodeSessionStatus status)
{
    wxCommandEvent *event = new wxCommandEvent(DECODE_SESSION_STATUS_CHANGE_EVENT, GetId());
    event->SetClientData(new DecodeSessionStatus(status));
    QueueEvent(event);
}
void ZebraCameraDemoFrame::QueueStreamStatusChangeEvent(CameraStreamStatus status)
{
    wxCommandEvent *event = new wxCommandEvent(STREAM_STATUS_CHANGE_EVENT, GetId());
    event->SetClientData(new CameraStreamStatus(status));
    QueueEvent(event);
}

void ZebraCameraDemoFrame::QueueTowerPlatterImageEvent()
{
    wxLogMessage("%s", __func__);
    wxCommandEvent *event = new wxCommandEvent(TOWER_PLATTER_IMAGE_EVENT, GetId());
    QueueEvent(event);
}

/*
 Generates image file name with given postfix : image_YYYYMMDD_HHMMSS_MILLISec_postfix
 @param file_postfix Postfix to add to file name at the end (one of _c, _s, _p, _d, _sb)
 @return Generated file name as a std::string
*/
std::string GetFileName(std::string file_postfix)
{
    std::string file_prefix = "image_";

    //calculate date time	
    std::time_t t = std::time(nullptr);
    char mbstr[128];
    std::strftime(mbstr, sizeof(mbstr), "%Y%m%d_%H%M%S", std::localtime(&t));

    //calculate milli seconds	
    timeval current_time;
    gettimeofday(&current_time, 0);
    int milli_seconds = current_time.tv_usec / 1000;
    char milli_string[128];
    sprintf(milli_string, "_%03d", milli_seconds);

    //generate file name
    std::string file_name = file_prefix + std::string(mbstr) + std::string(milli_string) + file_postfix;
    return file_name;
}
std::string ZebraCameraDemoFrame::GetDateAndTime(){
     //calculate date time	
    std::time_t t = std::time(nullptr);
    char mbstr[128];
    std::strftime(mbstr, sizeof(mbstr), "%Y_%m_%d_%H:%M:%S", std::localtime(&t));

    //calculate milli seconds	
    timeval current_time;
    gettimeofday(&current_time, 0);
    int milli_seconds = current_time.tv_usec / 1000;
    char milli_string[128];
    sprintf(milli_string, "_%03d", milli_seconds);
    
    std::string date_time = std::string(mbstr) + std::string(milli_string);
    return date_time;
}
void ZebraCameraDemoFrame::SaveImage(ImageBuffer& image, std::string str_event_type)
{
    if (!save_image_directory_path_.empty() && CheckBoxSaveImages->GetValue())
    {
        std::time_t t = std::time(nullptr);
        char mbstr[128];
        std::strftime(mbstr, sizeof(mbstr), "%c", std::localtime(&t));
       
        std::string filepath = save_image_directory_path_ + std::string("/") + GetFileName(str_event_type);
        switch (image_file_format_)
        {
        case ImageFileFormat::JPG:
            image.SaveAsJpeg(filepath + std::string(".jpg"));
            break;
        case ImageFileFormat::BMP:
            image.SaveAsBmp(filepath + std::string(".bmp"));
            break;
        default:
            image.SaveAsJpeg(filepath + std::string(".jpg"));
            break;
        }
    }
}
/**
 * Method that saves the image of the last occurred event on the command of the 'save' button click
 * @param image
 * @param str_event_type
 */
void ZebraCameraDemoFrame::SaveImageOnButtonClick(ImageBuffer& image, std::string str_event_type)
{
    if (!save_image_directory_path_.empty() )
    {
        std::time_t t = std::time(nullptr);
        char mbstr[128];
        std::strftime(mbstr, sizeof(mbstr), "%c", std::localtime(&t));
       
        std::string filepath = save_image_directory_path_ + std::string("/") + GetFileName(str_event_type);
        switch (image_file_format_)
        {
        case ImageFileFormat::JPG:
            image.SaveAsJpeg(filepath + std::string(".jpg"));
            break;
        case ImageFileFormat::BMP:
            image.SaveAsBmp(filepath + std::string(".bmp"));
            break;
        default:
            image.SaveAsJpeg(filepath + std::string(".jpg"));
            break;
        }
    }
}

void ZebraCameraDemoFrame::UpdateEventInformation(string event_type_,string image_format_,string image_size_,string time_stamp_, string image_resolution_,string decode_data_,string weight_unit_data_, string stream_status_){
   
    TextCtrlEventType->SetValue(event_type_);
    TextCtrlTimeStamp->SetValue(time_stamp_);
    TextCtrlDecodeData->SetValue(decode_data_);
    TextCtrlFormat->SetValue(image_format_);
    TextCtrlImageResolution->SetValue(image_resolution_);
    TextCtrlSize->SetValue(image_size_);
    TextCtrlWeightUnit->SetValue(weight_unit_data_);
    TextCtrlStreamStatus->SetValue(stream_status_);

}
    

void ZebraCameraDemoFrame::OnProduceImageEvent(wxCommandEvent& event)
{
    (void)event;

    produce_image_.CopyFromBuffer(PanelVideoDisplay->image_data_,
                                 PanelVideoDisplay->image_data_size_);
    PanelVideoDisplay->DrawFrame();
    PanelVideoDisplay->Refresh();
    PanelVideoDisplay->Update();

    SaveImage(produce_image_, "_p");

    std::stringstream ss(event.GetString().ToStdString());
    double value;
    std::string unit;
    std::string correctedWeight ="";
 
    if (ss >> value >> unit) {
    
    
    if (unit == "lb") {
        value = value / 1000.0; 
    }
    
    
    std::stringstream formattedStream;
    formattedStream << std::fixed << std::setprecision(3) << value << " " << unit;
    
    correctedWeight = formattedStream.str();   
 
    }
    UpdateEventInformation("Produce","RGB", std::to_string((PanelVideoDisplay->image_data_size_)/1000),GetDateAndTime(),image_resolution_,"",correctedWeight,"");
  
}

void ZebraCameraDemoFrame::OnSnapshotImageEvent(wxCommandEvent& event)
{
    (void)event;

    snapshot_image_.CopyFromBuffer(PanelVideoDisplay->image_data_,
                                 PanelVideoDisplay->image_data_size_);
    PanelVideoDisplay->DrawFrame();
    PanelVideoDisplay->Refresh();
    PanelVideoDisplay->Update();

    SaveImage(snapshot_image_, "_s");
    UpdateEventInformation("Snapshot","RGB", std::to_string((PanelVideoDisplay->image_data_size_)/1000),GetDateAndTime(),image_resolution_,"","","");
   
}

void ZebraCameraDemoFrame::OnDecodeImageEvent(wxCommandEvent& event)
{
    (void)event;

    decode_image_.CopyFromBuffer(PanelVideoDisplay->image_data_,
                                 PanelVideoDisplay->image_data_size_);
    PanelVideoDisplay->DrawFrame();
    PanelVideoDisplay->Refresh();
    PanelVideoDisplay->Update();
    
    image_event_type_ = "_" + event.GetString().ToStdString() + "_d";
    
    SaveImage(decode_image_, "_" + event.GetString().ToStdString() + "_d");
    
    ShowDecodeImage();
    
    UpdateEventInformation("Decode","RGB", std::to_string((PanelVideoDisplay->image_data_size_)/1000),GetDateAndTime(),image_resolution_,event.GetString().ToStdString(),"","");
   

}

void ZebraCameraDemoFrame::OnContinuousImageEvent(wxCommandEvent& event)
{
    (void)event;

    image_buffer_.CopyFromBuffer(PanelVideoDisplay->image_data_,
                                 PanelVideoDisplay->image_data_size_);
    PanelVideoDisplay->DrawFrame();
    PanelVideoDisplay->Refresh();
    PanelVideoDisplay->Update();
    
    SaveImage(image_buffer_, "_c");
    UpdateEventInformation("Continuous","RGB", std::to_string((PanelVideoDisplay->image_data_size_)/1000),GetDateAndTime(),image_resolution_,"","","");
   
}

void ZebraCameraDemoFrame::OnCaptureSnapshotEvent(wxCommandEvent& event)
{
    (void)event;

    image_buffer_.CopyFromBuffer(PanelVideoDisplay->image_data_,
                                 PanelVideoDisplay->image_data_size_);
    PanelVideoDisplay->DrawFrame();
    PanelVideoDisplay->Refresh();
    PanelVideoDisplay->Update();
    
    SaveImage(image_buffer_, "_cs");
    UpdateEventInformation("Snapshot","RGB", std::to_string((PanelVideoDisplay->image_data_size_)/1000),GetDateAndTime(),image_resolution_,"","","");

}

void ZebraCameraDemoFrame::OnDecodeSessionStatusChangeEvent(wxCommandEvent& event)
{
    (void)event;

    DecodeSessionStatus *status = (DecodeSessionStatus*)event.GetClientData();
    DecodeSessionStatus status_received = *status;

    switch (status_received)
	{
    case DecodeSessionStatus::DECODE_SESSION_START:
        LedDeviceAwake->SwitchOn();
        break;
    case DecodeSessionStatus::DECODE_SESSION_END:
         LedDeviceAwake->SwitchOff();
        break;
    default:
        LedDeviceAwake->SwitchOff();
        break;
	}
}


void ZebraCameraDemoFrame::OnStreamStatusChangeEvent(wxCommandEvent& event)
{
    (void)event;
   
    CameraStreamStatus *status = (CameraStreamStatus*)event.GetClientData();
    CameraStreamStatus status_received = *status;


    switch (status_received)
    {
    case CameraStreamStatus::STREAM_CONTINUED:
        TextCtrlStreamStatus->SetForegroundColour(*wxBLACK);
        UpdateEventInformation("Stream","RGB","",GetDateAndTime(),"","","","STREAM_CONTINUED");
   
        break;
    case CameraStreamStatus::STREAM_DISCONTINUED:
        TextCtrlStreamStatus->SetForegroundColour(*wxRED);
        UpdateEventInformation("Stream","RGB","",GetDateAndTime(),"","","","STREAM_DISCONTINUED");
        
        break;
    default:

        break;
    }
}
/**
 * Creates WxImage from opencv 's Mat object.
 * Current use-case (Tower/Platter images) only uses omni channel
 * monochrome images conversion only. apart from that 4 channel image data 
 * (most genaric) coversion is also handled for the sake of completion.
 * @param mat_image mat image that you get through opencv imdecode call
 * @return wxImage 
 */
wxImage ZebraCameraDemoFrame::CreateWxImageFromMat(cv::Mat &mat_image) {
    cv::Mat mat_image_temp;
    if(mat_image.channels()==1)
    {
        // image data channel count = 1 Greyscale
        // tower / platter images goes through this channel.
        cv::cvtColor(mat_image,mat_image_temp,cv::COLOR_GRAY2RGB);
    }
    else if (mat_image.channels() == 4) 
    {
        // image data channel count = 4 RGBA.  General jpeg image
        cv::cvtColor(mat_image, mat_image_temp, cv::COLOR_RGBA2BGR);
    }
    else 
    {
        // images with othe number of channel counts.
        cv::cvtColor(mat_image,mat_image_temp,cv::COLOR_RGBA2BGR);
    }
    
    long image_size = mat_image_temp.rows*mat_image_temp.cols*mat_image_temp.channels();
    
    // creating an empty wx image file.
    wxImage wx_image(mat_image_temp.cols, mat_image_temp.rows,(unsigned char*)malloc(image_size), false);
    
    // fill up the wx image from data taken from Mat image object
    unsigned char* image_data_from_mat_image = mat_image_temp.data;
    unsigned char* image_data_location_in_wx_image = wx_image.GetData();
    for (int index = 0; index < image_size; index++) 
    { 
        image_data_location_in_wx_image[index] = image_data_from_mat_image[index];
    }
    return wx_image;
}

void ZebraCameraDemoFrame::OnTowerPlatterImageRecievedEvent(wxCommandEvent& event)
{
    (void)event;
    
    // ststic image ui measurments
    int image_height = 200;
    double aspact_ratio = 1.48;
    int image_width = 200 * aspact_ratio;   
    
    // creating a bitmap to load to UI if the tower or platter image validation failed.
    int width_null_image = 1;
    int height_null_image = 1;
    wxImage null_image(width_null_image, height_null_image);
    
    // add mask to disapear black color from null_bitmap
    // makes 1 pixcel image invicible
    int red_color_value_for_mask = 0;
    int green_color_value_for_mask = 0;
    int blue_color_value_for_mask = 0;
    null_image.SetMaskColour(red_color_value_for_mask, green_color_value_for_mask, blue_color_value_for_mask);
    
    wxBitmap* null_bitmap = new wxBitmap(null_image);
    
    int flag_return_loaded_image_as_it_is = -1; // No color conversion needed in opencv
    int tower_image_data_begin_index = 0;
    int platter_image_data_begin_index = 0;
    
    try {       
        // to validate the tower image, call imdecode() in opencv.
        uint8_t *tower_image_ptr = image_creation_event_.GetTowerImage();
        std::vector<char> tower_image_vector(&tower_image_ptr[tower_image_data_begin_index], &tower_image_ptr[image_creation_event_.GetTowerImageSize()]);
        errno = 0;
        cv::Mat tower_image_mat = cv::imdecode(tower_image_vector, flag_return_loaded_image_as_it_is );
        
        if (tower_image_mat.data != NULL)
        {
            wxImage wx_image_tower = CreateWxImageFromMat(tower_image_mat);                      
            wx_image_tower.Rescale(image_width, image_height);
            wxBitmap resized_bitmap(wx_image_tower);
            TowerImgBitmap->SetBitmap(resized_bitmap);
        }  else {
	    TowerImgBitmap->SetBitmap(*null_bitmap );
	    TowerImgBitmap->Update();
            wxMessageBox("Invalid tower image returned.");
        }
    }catch(std::exception &ex) {
        TowerImgBitmap->SetBitmap(*null_bitmap );
	TowerImgBitmap->Update();
	wxMessageBox(ex.what(), "Failed to load the tower image. ");
    }

            
    try {
        // to validate the platter image, call imdecode() in opencv.
        uint8_t *platter_image_ptr = image_creation_event_.GetPlatterImage();
        std::vector<char> platter_image_vector(&platter_image_ptr[platter_image_data_begin_index], &platter_image_ptr[image_creation_event_.GetPlatterImageSize()]);
        errno = 0;
        cv::Mat platter_image_mat = cv::imdecode(platter_image_vector, flag_return_loaded_image_as_it_is);

        if (platter_image_mat.data != NULL)
        {       
            wxImage wx_image_platter = CreateWxImageFromMat(platter_image_mat);                      
            wx_image_platter.Rescale(image_width, image_height);
            wxBitmap resized_bitmap(wx_image_platter);
            PlatterImgBitmap->SetBitmap(resized_bitmap);
        } else {
            PlatterImgBitmap->SetBitmap(*null_bitmap );
	    PlatterImgBitmap->Update();
            wxMessageBox("Invalid platter image returned.");
        }
    }catch(std::exception &ex) {
        PlatterImgBitmap->SetBitmap(*null_bitmap );
	PlatterImgBitmap->Update();
	wxMessageBox(ex.what(), "Failed to load the platter image. ");
    }
    
    delete null_bitmap;

}





void ZebraCameraDemoFrame::CreateImageEventListeners()
{

    // Bind image-event listeners
    Bind(CONTINUOUS_IMAGE_EVENT, &ZebraCameraDemoFrame::OnContinuousImageEvent, this);
    Bind(PRODUCE_IMAGE_EVENT, &ZebraCameraDemoFrame::OnProduceImageEvent, this);
    Bind(SNAPSHOT_IMAGE_EVENT, &ZebraCameraDemoFrame::OnSnapshotImageEvent, this);
    Bind(DECODE_IMAGE_EVENT, &ZebraCameraDemoFrame::OnDecodeImageEvent, this);
    Bind(CAPTURE_SNAPSHOT_EVENT, &ZebraCameraDemoFrame::OnCaptureSnapshotEvent, this);
    Bind(DECODE_SESSION_STATUS_CHANGE_EVENT, &ZebraCameraDemoFrame::OnDecodeSessionStatusChangeEvent,this);
    Bind(TOWER_PLATTER_IMAGE_EVENT, &ZebraCameraDemoFrame::OnTowerPlatterImageRecievedEvent, this);
    Bind(STREAM_STATUS_CHANGE_EVENT, &ZebraCameraDemoFrame::OnStreamStatusChangeEvent,this);

    continuous_image_listener_ = new ContinuousImageObserver(this);
    produce_image_listener_ = new ProduceImageObserver(this);
    snapshot_image_listener_ = new SnapshotImageObserver(this);
    decode_image_listener_ = new DecodeImageObserver(this);
    decode_session_status_change_listener_ = new DecodeSessionStatusChangeEventObserver(this);
    tower_platter_image_listener_ = new ImageEventSubscriberSample(this);
    stream_status_change_event_listener_ = new CameraStreamStatusChangeEventObserver(this);

}

void ZebraCameraDemoFrame::ReleaseImageEventListeners()
{

    auto camera = GetCamera();

    StopCameraVideo(camera);

    Unbind(CONTINUOUS_IMAGE_EVENT, &ZebraCameraDemoFrame::OnContinuousImageEvent, this);    
    Unbind(PRODUCE_IMAGE_EVENT, &ZebraCameraDemoFrame::OnProduceImageEvent, this);
    Unbind(SNAPSHOT_IMAGE_EVENT, &ZebraCameraDemoFrame::OnSnapshotImageEvent, this);
    Unbind(DECODE_IMAGE_EVENT, &ZebraCameraDemoFrame::OnDecodeImageEvent, this);
    Unbind(CAPTURE_SNAPSHOT_EVENT, &ZebraCameraDemoFrame::OnCaptureSnapshotEvent, this);
    Unbind(DECODE_SESSION_STATUS_CHANGE_EVENT, &ZebraCameraDemoFrame::OnDecodeSessionStatusChangeEvent,this);
    Unbind(STREAM_STATUS_CHANGE_EVENT, &ZebraCameraDemoFrame::OnStreamStatusChangeEvent,this);
    Unbind(TOWER_PLATTER_IMAGE_EVENT, &ZebraCameraDemoFrame::OnTowerPlatterImageRecievedEvent, this);
}
