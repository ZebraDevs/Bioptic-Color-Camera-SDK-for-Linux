/***************************************************************
 * Name:      ZebraCameraDemoMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2019-08-16
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef ZEBRACAMERADEMOMAIN_H
#define ZEBRACAMERADEMOMAIN_H

//(*Headers(ZebraCameraDemoFrame)
#include <wx/gauge.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/scrolwin.h>
#include <wx/slider.h>
#include <wx/statusbr.h>
#include <wx/filepicker.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/statbmp.h>
//*)

#include <sstream>
#include <string>
#include "led.h"

#include "CameraFirmwareDownload.h"
#include "CameraImageEvents.h"
#include "CameraPlugAndPlay.h"

#include "ImageBuffer.h"
#include "VideoPanel.h"

#include "image_converter.h"

#include "device_manager.h"
#include "zebra_camera_client.h"
#include "zebra_camera_manager_client.h"
#include "image_event_subscription_impl.h"
#include "directory_observer.h"
#include "image_event.h"

#include <opencv2/core/core.hpp>

enum ImageFileFormat
{
    JPG,
    BMP,
};

#define WHITE_BALANCE_POLLING_INTERVAL_IN_MILLISECONDS 	1000

class ZebraCameraDemoFrame: public wxFrame
{
    public:

        ZebraCameraDemoFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ZebraCameraDemoFrame();

    public:
        void QueueCameraArrivedEvent(zebra::DeviceInfo info);
        void QueueCameraLeftEvent(zebra::DeviceInfo info);

        void QueueAlreadyAttachedCameraEvents();

        void QueueContinuousImageEvent();
        void QueueProduceImageEvent(std::string& weight_unit_data);
        void QueueSnapshotImageEvent();
        void QueueDecodeImageEvent(std::string& decode_data);

        void QueueCaptureSnapshotEvent();
        void QueueDecodeSessionStatusChangeEvent(DecodeSessionStatus status);
        void QueueStreamStatusChangeEvent(CameraStreamStatus status);
        void QueueTowerPlatterImageEvent();

        void QueueFirmwareDownloadEvent(FirmwareDownloadEventsArgs fwstatus);
        void ShowDecodeImage();
        void OnButtonSaveImageClick(wxCommandEvent& event);

        /** This method is responsible for reseting the progress bar of firmware update during camera detach and reboot events*/
        void ResetFirmwareUpdateProgressBar();

    private:
        // PnP
        void CreatePnpListeners();
        void ReleasePnpListeners();

        void CreateFirmwareDownloadEventListener();
        void ReleaseFirmwareDownloadEventListener();

        void CreateImageEventListeners();
        void ReleaseImageEventListeners();

        void ReleaseCameras();

        void SaveImage(ImageBuffer& image, std::string str_event_type);
	void SaveImageOnButtonClick(ImageBuffer& image, std::string str_event_type);
        std::string GetDateAndTime();
        void UpdateEventInformation(string event_type_,string image_format_,string image_size_,string time_stamp_, string image_resolution_,string decode_data_,string weight_unit_data_,string stream_Status);   
        std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> GetCamera();

        void PopulateCameraProperties(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void PopulateCameraAssetTrackingInfo(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void PopulateProcessingUnitInfo(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void PopulateCameraTerminalInfo(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void PopulateExtensionUnit1Info(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void PopulateVideoProfiles(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);

        // Reset controls when the selected camera leaves.
        void ClearAllCameraProperties();
        void ClearCameraAssetTrackingInfo();
        void ClearProcessingUnitInfo();
        void ClearCameraTerminalInfo();
        void ClearExtensionUnit1Info();
        void ClearVideoProfiles();
        void ClearVideoEvents();
        void ClearDeviceAwakeInfo();

        void StopCameraVideo(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);

        void PopulateBrightness(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void PopulateContrast(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void PopulateSaturation(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void PopulateSharpness(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void PopulateGamma(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void PopulateWhiteBalanceComponent(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void PopulateBacklight(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void PopulateGain(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);

        void PopulateAbsoluteExposureTime(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void PopulateDeviceAwake(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);

        void PopulateVideoMode(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void PopulateIlluminationMode(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void PopulatePowerUserMode(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void OnPowerUserModeChange(bool mode);

        void ChangeCameraVideoProfile(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera, const FrameType& frame_type);

        void OnCameraArrivedEvent(wxCommandEvent& event);
        void OnCameraLeftEvent(wxCommandEvent& event);

        void OnContinuousImageEvent(wxCommandEvent& event);
        void OnProduceImageEvent(wxCommandEvent& event);
        void OnSnapshotImageEvent(wxCommandEvent& event);
        void OnDecodeImageEvent(wxCommandEvent& event);
        void OnCaptureSnapshotEvent(wxCommandEvent& event);
        void OnDecodeSessionStatusChangeEvent(wxCommandEvent& event);
        void OnStreamStatusChangeEvent(wxCommandEvent& event);
        void OnTowerPlatterImageRecievedEvent(wxCommandEvent& event);

        void OnCameraFirmwareDownloadEvent(wxCommandEvent& event);

        void SetVideoMode(VideoMode mode);
        void SetDeviceAwake(VideoMode mode);

        void OnAutoWhiteBalanceUpdateTimer(wxTimerEvent& event);
        
        wxImage CreateWxImageFromMat(cv::Mat &mat_image);

    private:
        int property_brightness;
        int property_contrast;
        int property_saturation;
        int property_sharpness;
        int property_gamma;
        int property_wb_blue;
        float property_wb_blue_in_float;
        int property_wb_red;
        float property_wb_red_in_float;
        int property_backlight;
        int property_gain;

        int property_abs_exposure_time;
        int property_auto_exposure_mode;

        int property_videomode;
        int property_illuminationmode;
        bool property_powerusermode;

    private:
        wxLog* logger_;

        wxTimer auto_white_balance_monitor_timer_;   

        zebra::DeviceManager device_manager_;

        std::unique_ptr<zebra::camera_sdk::ZebraCameraManagerClient> camera_manager_client_;

        AttachedEventObserver *attached_listener_;
        DetachedEventObserver *detached_listener_;

        ContinuousImageObserver *continuous_image_listener_;
        ProduceImageObserver *produce_image_listener_;
        SnapshotImageObserver *snapshot_image_listener_;
        DecodeImageObserver *decode_image_listener_;
        DecodeSessionStatusChangeEventObserver *decode_session_status_change_listener_;
        CameraStreamStatusChangeEventObserver *stream_status_change_event_listener_;
        ImageEventSubscriberSample *tower_platter_image_listener_;

        FirmwareDownloadEventObserver *firmware_download_event_listener_;

        std::string save_image_directory_path_;
        std::string firmware_file_;

        ImageFileFormat image_file_format_;

        ImageEventSubscriber* subscriber_;
        DirectoryObserver *dir_observer_;
        bool listening_started_ = false;
        bool observer_created_ = false;

    public:
        ImageBuffer image_buffer_;

        ImageBuffer continuous_image_;
        ImageBuffer produce_image_;
        ImageBuffer snapshot_image_;
        ImageBuffer decode_image_;
        ImageCreationEvent image_creation_event_;

	    string image_event_type_ = "";
        bool snapshot_captured_from_ui = false;
        ImageBuffer last_saved_image_;
        bool continuous_image_received_ = false ;
        string image_resolution_="";                

    private:

        //(*Handlers(ZebraCameraDemoFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnCheckBoxContinuousEventsClick(wxCommandEvent& event);
        void OnChoiceSelectedCameraSelect(wxCommandEvent& event);
        void OnSliderBrightnessCmdScrollChanged(wxScrollEvent& event);
        void OnChoiceVideoModeSelect(wxCommandEvent& event);
        void OnSliderContrastCmdScrollChanged(wxScrollEvent& event);
        void OnSliderSharpnessCmdScrollChanged(wxScrollEvent& event);
        void OnSliderGammaCmdScrollChanged(wxScrollEvent& event);
        void OnSliderWhiteBalanceBlueCmdScrollChanged(wxScrollEvent& event);
        void OnSliderWhiteBalanceRedCmdScrollChanged(wxScrollEvent& event);
        void OnSliderBacklightCmdScrollChanged(wxScrollEvent& event);
        void OnSliderGainCmdScrollChanged(wxScrollEvent& event);
        void OnSliderSaturationCmdScrollChanged(wxScrollEvent& event);
        void OnTextCtrlBrightnessText(wxCommandEvent& event);
        void OnTextCtrlContrastText(wxCommandEvent& event);
        void OnTextCtrlSaturationText(wxCommandEvent& event);
        void OnTextCtrlSharpnessText(wxCommandEvent& event);
        void OnTextCtrlGammaText(wxCommandEvent& event);
        void OnTextCtrlWhiteBalanceBlueText(wxCommandEvent& event);
        void OnTextCtrlWhiteBalanceRedText(wxCommandEvent& event);
        void OnTextCtrlBacklightText(wxCommandEvent& event);
        void OnTextCtrlGainText(wxCommandEvent& event);
        void OnCheckBoxContrastAutoClick(wxCommandEvent& event);
        void OnCheckBoxWhiteBalanceAutoClick(wxCommandEvent& event);
        void OnSliderAbsoluteExposureTimeCmdScrollChanged(wxScrollEvent& event);
        void OnTextCtrlAbsoluteExposureTimeText(wxCommandEvent& event);
        void OnChoiceAutoExposureModeSelect(wxCommandEvent& event);
        void OnChoiceIlluminationModeSelect(wxCommandEvent& event);
        void OnCheckBoxExposureTimeAutoClick(wxCommandEvent& event);
        void OnChoiceVideoProfilesSelect(wxCommandEvent& event);
        void OnCheckBoxProduceEventsClick(wxCommandEvent& event);
        void OnCheckBoxSnapshotEventsClick(wxCommandEvent& event);
        void OnCheckBoxDecodeEventsClick(wxCommandEvent& event);
        void OnButtonSetPropertyDefaultsClick(wxCommandEvent& event);
        void OnButtonRebootClick(wxCommandEvent& event);
        
        void OnFilePickerCtrlFirmwareFileChanged(wxFileDirPickerEvent& event);
        void OnButtonUpdateClick(wxCommandEvent& event);
        void OnButtonCancelClick(wxCommandEvent& event);
        void OnDirPickerCtrlSaveImageDirChanged(wxFileDirPickerEvent& event);
        void OnCheckBoxPowerUserModeClick(wxCommandEvent& event);
        void OnButtonWriteToFlashClick(wxCommandEvent& event);
        void OnButtonCaptureSnapshotClick(wxCommandEvent& event);
        void OnChoiceImageFormatSelect(wxCommandEvent& event);
        void OnCheckBoxSaveImagesClick(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnGenerateConfigClick(wxCommandEvent& event);
        void OnButtonRegriveConfigClick(wxCommandEvent& event);
        void OnButtonLoadConfigClick(wxCommandEvent& event);
        void OnButtonClearTextConfigClick(wxCommandEvent& event);
        void OnCheckBoxSessionEventsClick(wxCommandEvent& event);
        void OnCheckBoxStreamEventsClick(wxCommandEvent& event);
        void OnButtonSetBackgroundClick(wxCommandEvent& event);
        void OnCheckBoxDetectBoundingBoxClick(wxCommandEvent& event);
        void OnBtnStartMonochromeClick(wxCommandEvent& event);
        void OnButtonStopMonochromeClick(wxCommandEvent& event);
        void OnBtnClearMonochromeClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(ZebraCameraDemoFrame)
        static const long ID_STATICTEXT9;
        static const long ID_CHOICE_SELECTED_CAMERA;
        static const long ID_PANEL4;
        static const long ID_PANEL3;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL_SERIAL_NUMBER;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL_MODEL_NUMBER;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL_FIRMWARE_VERSION;
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL_HARDWARE_VERSION;
        static const long ID_STATICTEXT5;
        static const long ID_TEXTCTRL_DATE_OF_MANUF;
        static const long ID_STATICTEXT6;
        static const long ID_TEXTCTRL_DATE_OF_PROG;
        static const long ID_STATICTEXT7;
        static const long ID_TEXTCTRL_DATE_OF_SERVICE;
        static const long ID_PANEL1;
        static const long ID_PANEL_CAMERA_LIST;
        static const long ID_STATICTEXT8;
        static const long ID_SLIDER_BRIGHTNESS;
        static const long ID_TEXTCTRL_BRIGHTNESS;
        static const long ID_STATICTEXT10;
        static const long ID_SLIDER_CONTRAST;
        static const long ID_TEXTCTRL_CONTRAST;
        static const long ID_CHECKBOX_CONTRAST_AUTO;
        static const long ID_STATICTEXT11;
        static const long ID_SLIDER_SATURATION;
        static const long ID_TEXTCTRL_SATURATION;
        static const long ID_STATICTEXT12;
        static const long ID_SLIDER_SHARPNESS;
        static const long ID_TEXTCTRL_SHARPNESS;
        static const long ID_STATICTEXT13;
        static const long ID_SLIDER_GAMMA;
        static const long ID_TEXTCTRL_GAMMA;
        static const long ID_STATICTEXT14;
        static const long ID_SLIDER_WB_BLUE;
        static const long ID_TEXTCTRL_WB_BLUE;
        static const long ID_CHECKBOX_WB_AUTO;
        static const long ID_STATICTEXT15;
        static const long ID_SLIDER_WB_RED;
        static const long ID_TEXTCTRL_WB_RED;
        static const long ID_STATICTEXT16;
        static const long ID_SLIDER_BACKLIGHT;
        static const long ID_TEXTCTRL_BACKLIGHT;
        static const long ID_STATICTEXT17;
        static const long ID_SLIDER_GAIN;
        static const long ID_TEXTCTRL_GAIN;
        static const long ID_SCROLLEDWINDOW1;
        static const long ID_STATICTEXT18;
        static const long ID_SLIDER_ABS_EXPOSURE_TIME;
        static const long ID_TEXTCTRL_ABS_EXPOSURE_TIME;
        static const long ID_CHECKBOX_EXPOSURE_TIME_AUTO;
        static const long ID_SCROLLEDWINDOW2;
        static const long ID_STATICTEXT20;
        static const long ID_CHOICE_VIDEO_MODE;
        static const long ID_STATICTEXT21;
        static const long ID_CHOICE_ILLUMINATION_MODE;
        static const long ID_CHECKBOX_POWER_USER_MODE;
        static const long ID_SCROLLEDWINDOW3;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_SCROLLEDWINDOW4;
        static const long ID_NOTEBOOK1;
        static const long ID_BUTTONSET_PROPERTY_DEFAULTS;
        static const long ID_BUTTON_REBOOT;
        
        static const long ID_BUTTON_WRITE_TO_FLASH;
        static const long ID_BUTTON_CAPTURE_SNAPSHOT;
        static const long ID_PANEL11;
        static const long ID_PANEL22;
        static const long ID_STATICBITMAP1;
        static const long ID_PANEL26;
        static const long ID_PANEL10;
        static const long ID_STATICBITMAP2;
        static const long ID_PANEL27;
        static const long ID_PANEL23;
        static const long ID_STATICBITMAP3;
        static const long ID_PANEL28;
        static const long ID_PANEL24;
        static const long ID_TEXTCTRL2;
        static const long ID_BUTTON5;
        static const long ID_BUTTON7;
        static const long ID_BUTTON6;
        static const long ID_PANEL29;
        static const long ID_PANEL25;
        static const long ID_PANEL9;
        static const long ID_NOTEBOOK2;
        static const long ID_PANEL7;
        static const long ID_PANEL20;
        static const long ID_PANEL_VIDEO_EX;
        static const long ID_STATICTEXT19;
        static const long ID_CHOICE_VIDEO_PROFILES;
        static const long ID_PANEL12;
        static const long ID_PANEL8;
        static const long ID_PANEL6;
        static const long ID_PANEL5;
        static const long ID_STATICTEXT23;
        static const long ID_FILEPICKERCTRL_FIRMWARE;
        static const long ID_BUTTON_UPDATE;
        static const long ID_BUTTON_CANCEL;
        static const long ID_PANEL18;
        static const long ID_STATICTEXT25;
        static const long ID_GAUGE_FW_DOWNLOAD_PROGRESS;
        static const long ID_PANEL21;
        static const long ID_PANEL17;
        static const long ID_PANEL2;
        static const long ID_CHECKBOX_CONTINUOUS_EVENTS;
        static const long ID_CHECKBOX_PRODUCE_EVENTS;
        static const long ID_CHECKBOX_SNAPSHOT_EVENTS;
        static const long ID_CHECKBOX_DECODE_EVENTS;
        static const long ID_CHECKBOX1;
        static const long ID_CHECKBOX2;
        static const long ID_BUTTON4;
        static const long ID_PANEL15;
        static const long ID_STATICTEXT24;
        static const long ID_CHOICE_IMAGE_FORMAT;
        static const long ID_CHECKBOX_SAVE_IMAGES;
        static const long ID_STATICTEXT27;
        static const long ID_LED2;
        static const long ID_PANEL19;
        static const long ID_STATICTEXT22;
        static const long ID_DIRPICKERCTRL_SAVE_IMAGE;
        static const long ID_PANEL16;
        static const long ID_PANEL14;
        static const long ID_PANEL13;
        static const long ID_PANEL_MISC;
        static const long ID_STATUSBAR1;
        static const long ID_BUTTON_SET_BACKGROUND;
        static const long ID_CHECKBOX_DETECT_BOUNDING_BOX;
        static const long ID_BUTTON_SAVE_IMAGE;
        static const long ID_STATICTEXT_EVENT_TYPE;
        static const long ID_STATICTEXT_FORMAT;
        static const long ID_STATICTEXT_SIZE;
        static const long ID_STATICTEXT_TIME_STAMP;
        static const long ID_STATICTEXT_IMAGE_RESOLUTION;
        static const long ID_STATICTEXT_DECODE_DATA;
	static const long ID_STATICTEXT_WEIGHT_UNIT;
	static const long ID_STATICTEXT_STREAM_STATUS;
        static const long ID_TEXTCTRL_EVENT_TYPE;
        static const long ID_TEXTCTRL_FORMAT;
        static const long ID_TEXTCTRL_SIZE;
        static const long ID_TEXTCTRL_TIME_STAMP;
        static const long ID_TEXTCTRL_IMAGE_RESOLUTION;
        static const long ID_TEXTCTRL_DECODE_DATA;	
	static const long ID_TEXTCTRL_STREAM_STATUS;
	static const long ID_TEXTCTRL_WEIGHT_UNIT;
        static const long ID_PANELNEW;  
        static const long ID_PANELN0;  
        static const long ID_SCROLLEDWINDOWNEW;
        //*)

        //(*Declarations(ZebraCameraDemoFrame)
        VideoPanel* PanelVideoDisplay;
        wxButton* BtnClearMonochrome;
        wxButton* BtnStartMonochrome;
        wxButton* ButtonCancel;
        wxButton* ButtonCaptureSnapshot;
        wxButton* ButtonClearTextConfig;
 
        wxButton* ButtonLoadConfig;
        wxButton* ButtonReboot;
        wxButton* ButtonRetriveConfig;
        wxButton* ButtonSaveImage;
        wxButton* ButtonSetBackground;
        wxButton* ButtonSetPropertyDefaults;
        wxButton* ButtonStopMonochrome;
        wxButton* ButtonUpdate;
        wxButton* ButtonWriteToFlash;
        wxCheckBox* CheckBoxContinuousEvents;
        wxCheckBox* CheckBoxContrastAuto;
        wxCheckBox* CheckBoxDecodeEvents;
        wxCheckBox* CheckBoxDetectBoundingBox;
        wxCheckBox* CheckBoxExposureTimeAuto;
        wxCheckBox* CheckBoxPowerUserMode;
        wxCheckBox* CheckBoxProduceEvents;
        wxCheckBox* CheckBoxSaveImages;
        wxCheckBox* CheckBoxSessionEvents;
        wxCheckBox* CheckBoxStreamEvents;
        wxCheckBox* CheckBoxSnapshotEvents;
        wxCheckBox* CheckBoxWhiteBalanceAuto;
        wxChoice* ChoiceIlluminationMode;
        wxChoice* ChoiceImageFormat;
        wxChoice* ChoiceSelectedCamera;
        wxChoice* ChoiceVideoMode;
        wxChoice* ChoiceVideoProfiles;
        wxDirPickerCtrl* DirPickerCtrlSaveImage;
        wxFilePickerCtrl* FilePickerCtrlFirmware;
        wxGauge* GaugeFirmwareDownloadProgress;
        wxLed* LedDeviceAwake;
        wxNotebook* Notebook1;
        wxNotebook* NotebookProperties;
        wxPanel* Panel10;
        wxPanel* Panel11;
        wxPanel* Panel12;
        wxPanel* Panel13;
        wxPanel* Panel14;
        wxPanel* Panel18;
        wxPanel* Panel1;
        wxPanel* Panel2;
        wxPanel* Panel3;
        wxPanel* Panel4;
        wxPanel* Panel5;
        wxPanel* Panel6;
        wxPanel* Panel7;
        wxPanel* Panel8;
        wxPanel* Panel9;
        wxPanel* PanelCameraDetails;
        wxPanel* PanelCameraList;
        wxPanel* PanelDecodeImage;
        wxPanel* PanelEvents;
        wxPanel* PanelImageFormat;
        wxPanel* PanelMisc;
        wxPanel* PanelPlatterImage;
        wxPanel* PanelProperties;
        wxPanel* PanelPropertiesAndVideo;
        wxPanel* PanelSaveImage;
        wxPanel* PanelSelectCamera;
        wxPanel* PanelSelectedCamera;
        wxPanel* PanelTowerImg;
        wxPanel* PanelVideoEvents;
        wxPanel* PanelVideoEx;
        wxPanel* PanelVideoProperties;
        wxScrolledWindow* ScrolledWindow1;
        wxScrolledWindow* ScrolledWindow2;
        wxScrolledWindow* ScrolledWindow3;
        wxScrolledWindow* ScrolledWindow4;
        wxSlider* SliderAbsoluteExposureTime;
        wxSlider* SliderBacklight;
        wxSlider* SliderBrightness;
        wxSlider* SliderContrast;
        wxSlider* SliderGain;
        wxSlider* SliderGamma;
        wxSlider* SliderSaturation;
        wxSlider* SliderSharpness;
        wxSlider* SliderWhiteBalanceBlue;
        wxSlider* SliderWhiteBalanceRed;
        wxStaticBitmap* DecodeImgBitmap;
        wxStaticBitmap* PlatterImgBitmap;
        wxStaticBitmap* TowerImgBitmap;
        wxStaticText* StaticText10;
        wxStaticText* StaticText11;
        wxStaticText* StaticText12;
        wxStaticText* StaticText13;
        wxStaticText* StaticText14;
        wxStaticText* StaticText15;
        wxStaticText* StaticText16;
        wxStaticText* StaticText17;
        wxStaticText* StaticText18;
        wxStaticText* StaticText1;
        wxStaticText* StaticText20;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText6;
        wxStaticText* StaticText7;
        wxStaticText* StaticText8;
        wxStaticText* StaticText9;
        wxStaticText* StaticTextDateOfFirstProgram;
        wxStaticText* StaticTextDateOfManufacture;
        wxStaticText* StaticTextDateOfService;
        wxStaticText* StaticTextFirmwareVersion;
        wxStaticText* StaticTextHardwareVersion;
        wxStaticText* StaticTextModelNumber;
        wxStaticText* StaticTextSerialNumber;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrlAbsoluteExposureTime;
        wxTextCtrl* TextCtrlBacklight;
        wxTextCtrl* TextCtrlBrightness;
        wxTextCtrl* TextCtrlConfiguration;
        wxTextCtrl* TextCtrlContrast;
        wxTextCtrl* TextCtrlDateOfFirstProgram;
        wxTextCtrl* TextCtrlDateOfManufacture;
        wxTextCtrl* TextCtrlDateOfService;
        wxTextCtrl* TextCtrlFirmwareVersion;
        wxTextCtrl* TextCtrlGain;
        wxTextCtrl* TextCtrlGamma;
        wxTextCtrl* TextCtrlHardwareVersion;
        wxTextCtrl* TextCtrlModelNumber;
        wxTextCtrl* TextCtrlMonoChromeLogs;
        wxTextCtrl* TextCtrlSaturation;
        wxTextCtrl* TextCtrlSerialNumber;
        wxTextCtrl* TextCtrlSharpness;
        wxTextCtrl* TextCtrlWhiteBalanceBlue;
        wxTextCtrl* TextCtrlWhiteBalanceRed;
        wxStaticText* StaticTextEventType;
        wxStaticText* StaticTextFormat;
        wxStaticText* StaticTextSize;
        wxStaticText* StaticTextTimeStamp;
        wxStaticText* StaticTextImageResolution;
        wxStaticText* StaticTextDecodeData;
	wxStaticText* StaticTextStreamStatus;
	wxStaticText* StaticTextWeightUnit;
        wxTextCtrl*TextCtrlEventType;
        wxTextCtrl*TextCtrlFormat;
        wxTextCtrl*TextCtrlSize;
        wxTextCtrl*TextCtrlTimeStamp;
        wxTextCtrl*TextCtrlImageResolution;
        wxTextCtrl*TextCtrlDecodeData;	
	wxTextCtrl*TextCtrlWeight;
	wxTextCtrl*TextCtrlWeightUnit;
    wxTextCtrl*TextCtrlStreamStatus;

        wxPanel* PanelNew;
        wxPanel* PanelNew0;
        wxScrolledWindow* ScrolledWindowNew;
        //*)


        DECLARE_EVENT_TABLE()
};

#endif // ZEBRACAMERADEMOMAIN_H
