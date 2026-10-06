/***************************************************************
 * Name:      ZebraCameraDemoMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2019-08-16
 * Copyright:  ()
 * License:
 **************************************************************/

#include "ZebraCameraDemoMain.h"
//#include "zebra_camera_manager.h"

#include "image_event_subscription_impl.h"
#include "directory_observer.h"
#include "image_creation_observer.h"
#include <wx/msgdlg.h>

#include <wx/valnum.h>  // For wxIntegerValidator.
#include <wx/valgen.h>  // For wxGenericValidator.

#include <math.h>

//(*InternalHeaders(ZebraCameraDemoFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

#include <iostream>
#include <fstream>
#include <exception>

#include "wx_pch.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(ZebraCameraDemoFrame)
const long ZebraCameraDemoFrame::ID_STATICTEXT9 = wxNewId();
const long ZebraCameraDemoFrame::ID_CHOICE_SELECTED_CAMERA = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL4 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL3 = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT1 = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_SERIAL_NUMBER = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT2 = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_MODEL_NUMBER = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT3 = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_FIRMWARE_VERSION = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT4 = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_HARDWARE_VERSION = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT5 = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_DATE_OF_MANUF = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT6 = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_DATE_OF_PROG = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT7 = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_DATE_OF_SERVICE = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL1 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL_CAMERA_LIST = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT8 = wxNewId();
const long ZebraCameraDemoFrame::ID_SLIDER_BRIGHTNESS = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_BRIGHTNESS = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT10 = wxNewId();
const long ZebraCameraDemoFrame::ID_SLIDER_CONTRAST = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_CONTRAST = wxNewId();
const long ZebraCameraDemoFrame::ID_CHECKBOX_CONTRAST_AUTO = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT11 = wxNewId();
const long ZebraCameraDemoFrame::ID_SLIDER_SATURATION = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_SATURATION = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT12 = wxNewId();
const long ZebraCameraDemoFrame::ID_SLIDER_SHARPNESS = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_SHARPNESS = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT13 = wxNewId();
const long ZebraCameraDemoFrame::ID_SLIDER_GAMMA = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_GAMMA = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT14 = wxNewId();
const long ZebraCameraDemoFrame::ID_SLIDER_WB_BLUE = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_WB_BLUE = wxNewId();
const long ZebraCameraDemoFrame::ID_CHECKBOX_WB_AUTO = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT15 = wxNewId();
const long ZebraCameraDemoFrame::ID_SLIDER_WB_RED = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_WB_RED = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT16 = wxNewId();
const long ZebraCameraDemoFrame::ID_SLIDER_BACKLIGHT = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_BACKLIGHT = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT17 = wxNewId();
const long ZebraCameraDemoFrame::ID_SLIDER_GAIN = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_GAIN = wxNewId();
const long ZebraCameraDemoFrame::ID_SCROLLEDWINDOW1 = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT18 = wxNewId();
const long ZebraCameraDemoFrame::ID_SLIDER_ABS_EXPOSURE_TIME = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_ABS_EXPOSURE_TIME = wxNewId();
const long ZebraCameraDemoFrame::ID_CHECKBOX_EXPOSURE_TIME_AUTO = wxNewId();
const long ZebraCameraDemoFrame::ID_SCROLLEDWINDOW2 = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT20 = wxNewId();
const long ZebraCameraDemoFrame::ID_CHOICE_VIDEO_MODE = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT21 = wxNewId();
const long ZebraCameraDemoFrame::ID_CHOICE_ILLUMINATION_MODE = wxNewId();
const long ZebraCameraDemoFrame::ID_CHECKBOX_POWER_USER_MODE = wxNewId();
const long ZebraCameraDemoFrame::ID_SCROLLEDWINDOW3 = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL1 = wxNewId();
const long ZebraCameraDemoFrame::ID_BUTTON1 = wxNewId();
const long ZebraCameraDemoFrame::ID_BUTTON2 = wxNewId();
const long ZebraCameraDemoFrame::ID_BUTTON3 = wxNewId();
const long ZebraCameraDemoFrame::ID_SCROLLEDWINDOW4 = wxNewId();
const long ZebraCameraDemoFrame::ID_NOTEBOOK1 = wxNewId();
const long ZebraCameraDemoFrame::ID_BUTTONSET_PROPERTY_DEFAULTS = wxNewId();
const long ZebraCameraDemoFrame::ID_BUTTON_REBOOT = wxNewId();

const long ZebraCameraDemoFrame::ID_BUTTON_WRITE_TO_FLASH = wxNewId();
const long ZebraCameraDemoFrame::ID_BUTTON_CAPTURE_SNAPSHOT = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL11 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL22 = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICBITMAP1 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL26 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL10 = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICBITMAP2 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL27 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL23 = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICBITMAP3 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL28 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL24 = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL2 = wxNewId();
const long ZebraCameraDemoFrame::ID_BUTTON5 = wxNewId();
const long ZebraCameraDemoFrame::ID_BUTTON7 = wxNewId();
const long ZebraCameraDemoFrame::ID_BUTTON6 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL29 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL25 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL9 = wxNewId();
const long ZebraCameraDemoFrame::ID_NOTEBOOK2 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL7 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL20 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL_VIDEO_EX = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT19 = wxNewId();
const long ZebraCameraDemoFrame::ID_CHOICE_VIDEO_PROFILES = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL12 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL8 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL6 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL5 = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT23 = wxNewId();
const long ZebraCameraDemoFrame::ID_FILEPICKERCTRL_FIRMWARE = wxNewId();
const long ZebraCameraDemoFrame::ID_BUTTON_UPDATE = wxNewId();
const long ZebraCameraDemoFrame::ID_BUTTON_CANCEL = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL18 = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT25 = wxNewId();
const long ZebraCameraDemoFrame::ID_GAUGE_FW_DOWNLOAD_PROGRESS = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL21 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL17 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL2 = wxNewId();
const long ZebraCameraDemoFrame::ID_CHECKBOX_CONTINUOUS_EVENTS = wxNewId();
const long ZebraCameraDemoFrame::ID_CHECKBOX_PRODUCE_EVENTS = wxNewId();
const long ZebraCameraDemoFrame::ID_CHECKBOX_SNAPSHOT_EVENTS = wxNewId();
const long ZebraCameraDemoFrame::ID_CHECKBOX_DECODE_EVENTS = wxNewId();
const long ZebraCameraDemoFrame::ID_CHECKBOX1 = wxNewId();
const long ZebraCameraDemoFrame::ID_CHECKBOX2 = wxNewId();
const long ZebraCameraDemoFrame::ID_CHECKBOX_DETECT_BOUNDING_BOX = wxNewId();
const long ZebraCameraDemoFrame::ID_BUTTON4 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL15 = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT24 = wxNewId();
const long ZebraCameraDemoFrame::ID_CHOICE_IMAGE_FORMAT = wxNewId();
const long ZebraCameraDemoFrame::ID_CHECKBOX_SAVE_IMAGES = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT27 = wxNewId();
const long ZebraCameraDemoFrame::ID_LED2 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL19 = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT22 = wxNewId();
const long ZebraCameraDemoFrame::ID_DIRPICKERCTRL_SAVE_IMAGE = wxNewId();
const long ZebraCameraDemoFrame::ID_BUTTON_SAVE_IMAGE = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL16 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL14 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL13 = wxNewId();
const long ZebraCameraDemoFrame::ID_PANEL_MISC = wxNewId();
const long ZebraCameraDemoFrame::ID_STATUSBAR1 = wxNewId();
const long ZebraCameraDemoFrame::ID_BUTTON_SET_BACKGROUND = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT_EVENT_TYPE = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT_FORMAT = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT_SIZE = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT_TIME_STAMP = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT_IMAGE_RESOLUTION = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT_DECODE_DATA = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT_WEIGHT_UNIT = wxNewId();
const long ZebraCameraDemoFrame::ID_STATICTEXT_STREAM_STATUS = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_EVENT_TYPE = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_FORMAT = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_SIZE = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_TIME_STAMP = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_IMAGE_RESOLUTION = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_DECODE_DATA = wxNewId(); 
const long ZebraCameraDemoFrame::ID_TEXTCTRL_WEIGHT_UNIT = wxNewId();
const long ZebraCameraDemoFrame::ID_TEXTCTRL_STREAM_STATUS = wxNewId();
const long ZebraCameraDemoFrame::ID_PANELNEW = wxNewId();
const long ZebraCameraDemoFrame::ID_PANELN0 = wxNewId();
const long ZebraCameraDemoFrame::ID_SCROLLEDWINDOWNEW = wxNewId();
//const long ZebraCameraDemoFrame::ID_CHECKBOX_DETECT_BOUNDING_BOX = wxNewId();
//const long ZebraCameraDemoFrame::ID_BUTTON_SAVE_IMAGE = wxNewId();
//*)

BEGIN_EVENT_TABLE(ZebraCameraDemoFrame,wxFrame)
    //(*EventTable(ZebraCameraDemoFrame)
    //*)
END_EVENT_TABLE()

ZebraCameraDemoFrame::ZebraCameraDemoFrame(wxWindow* parent,wxWindowID id)
{
	(void)id;
    //(*Initialize(ZebraCameraDemoFrame)
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer11;
    wxBoxSizer* BoxSizer12;
    wxBoxSizer* BoxSizer13;
    wxBoxSizer* BoxSizer14;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxBoxSizer* BoxSizer9;
    wxBoxSizer* BoxSizerMain;
    wxBoxSizer* BoxSizerSelectedCamera;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer6;
    wxFlexGridSizer* FlexGridSizerCameraDetails;
    wxGridSizer* GridSizer1;
    wxGridSizer* GridSizer2;   
    wxGridSizer* GridSizer4; 
    wxStaticBoxSizer* StaticBoxSizer1;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxStaticBoxSizer* StaticBoxSizer4;
    wxStaticBoxSizer* StaticBoxSizer5;
    wxStaticBoxSizer* StaticBoxSizer6;
    wxStaticBoxSizer* StaticBoxSizer7;
    wxStaticBoxSizer* StaticBoxSizer8;
    wxStaticBoxSizer* StaticBoxSizer9;
    wxStaticBoxSizer* StaticBoxSizerVideoEx;
    wxFlexGridSizer* FlexGridSizerNew;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    BoxSizerMain = new wxBoxSizer(wxVERTICAL);
    PanelCameraList = new wxPanel(this, ID_PANEL_CAMERA_LIST, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_CAMERA_LIST"));
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, PanelCameraList, _("Camera"));
    PanelSelectedCamera = new wxPanel(PanelCameraList, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    BoxSizerSelectedCamera = new wxBoxSizer(wxVERTICAL);
    PanelSelectCamera = new wxPanel(PanelSelectedCamera, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticText1 = new wxStaticText(PanelSelectCamera, ID_STATICTEXT9, _("Selected Camera"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ChoiceSelectedCamera = new wxChoice(PanelSelectCamera, ID_CHOICE_SELECTED_CAMERA, wxDefaultPosition, wxSize(200,28), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_SELECTED_CAMERA"));
    FlexGridSizer1->Add(ChoiceSelectedCamera, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelSelectCamera->SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(PanelSelectCamera);
    FlexGridSizer1->SetSizeHints(PanelSelectCamera);
    BoxSizerSelectedCamera->Add(PanelSelectCamera, 1, wxALL|wxEXPAND, 5);
    PanelSelectedCamera->SetSizer(BoxSizerSelectedCamera);
    BoxSizerSelectedCamera->Fit(PanelSelectedCamera);
    BoxSizerSelectedCamera->SetSizeHints(PanelSelectedCamera);
    StaticBoxSizer2->Add(PanelSelectedCamera, 2, wxALL|wxEXPAND, 5);
    PanelCameraDetails = new wxPanel(PanelCameraList, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizerCameraDetails = new wxFlexGridSizer(0, 4, 0, 0);
    StaticTextSerialNumber = new wxStaticText(PanelCameraDetails, ID_STATICTEXT1, _("Serial Number"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizerCameraDetails->Add(StaticTextSerialNumber, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlSerialNumber = new wxTextCtrl(PanelCameraDetails, ID_TEXTCTRL_SERIAL_NUMBER, wxEmptyString, wxDefaultPosition, wxSize(200,28), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_SERIAL_NUMBER"));
    FlexGridSizerCameraDetails->Add(TextCtrlSerialNumber, 1, wxALL, 5);
    StaticTextModelNumber = new wxStaticText(PanelCameraDetails, ID_STATICTEXT2, _("Model Number"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizerCameraDetails->Add(StaticTextModelNumber, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlModelNumber = new wxTextCtrl(PanelCameraDetails, ID_TEXTCTRL_MODEL_NUMBER, wxEmptyString, wxDefaultPosition, wxSize(200,28), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_MODEL_NUMBER"));
    FlexGridSizerCameraDetails->Add(TextCtrlModelNumber, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextFirmwareVersion = new wxStaticText(PanelCameraDetails, ID_STATICTEXT3, _("Firmware Version"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizerCameraDetails->Add(StaticTextFirmwareVersion, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlFirmwareVersion = new wxTextCtrl(PanelCameraDetails, ID_TEXTCTRL_FIRMWARE_VERSION, wxEmptyString, wxDefaultPosition, wxSize(200,28), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_FIRMWARE_VERSION"));
    FlexGridSizerCameraDetails->Add(TextCtrlFirmwareVersion, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextHardwareVersion = new wxStaticText(PanelCameraDetails, ID_STATICTEXT4, _("Hardware Version"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizerCameraDetails->Add(StaticTextHardwareVersion, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlHardwareVersion = new wxTextCtrl(PanelCameraDetails, ID_TEXTCTRL_HARDWARE_VERSION, wxEmptyString, wxDefaultPosition, wxSize(200,28), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_HARDWARE_VERSION"));
    FlexGridSizerCameraDetails->Add(TextCtrlHardwareVersion, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextDateOfManufacture = new wxStaticText(PanelCameraDetails, ID_STATICTEXT5, _("Date of Manufacture"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizerCameraDetails->Add(StaticTextDateOfManufacture, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlDateOfManufacture = new wxTextCtrl(PanelCameraDetails, ID_TEXTCTRL_DATE_OF_MANUF, wxEmptyString, wxDefaultPosition, wxSize(200,28), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_DATE_OF_MANUF"));
    FlexGridSizerCameraDetails->Add(TextCtrlDateOfManufacture, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextDateOfFirstProgram = new wxStaticText(PanelCameraDetails, ID_STATICTEXT6, _("Date of First Program"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    FlexGridSizerCameraDetails->Add(StaticTextDateOfFirstProgram, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlDateOfFirstProgram = new wxTextCtrl(PanelCameraDetails, ID_TEXTCTRL_DATE_OF_PROG, wxEmptyString, wxDefaultPosition, wxSize(200,28), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_DATE_OF_PROG"));
    FlexGridSizerCameraDetails->Add(TextCtrlDateOfFirstProgram, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextDateOfService = new wxStaticText(PanelCameraDetails, ID_STATICTEXT7, _("Date of Service"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    FlexGridSizerCameraDetails->Add(StaticTextDateOfService, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlDateOfService = new wxTextCtrl(PanelCameraDetails, ID_TEXTCTRL_DATE_OF_SERVICE, wxEmptyString, wxDefaultPosition, wxSize(200,28), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_DATE_OF_SERVICE"));
    FlexGridSizerCameraDetails->Add(TextCtrlDateOfService, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelCameraDetails->SetSizer(FlexGridSizerCameraDetails);
    FlexGridSizerCameraDetails->Fit(PanelCameraDetails);
    FlexGridSizerCameraDetails->SetSizeHints(PanelCameraDetails);
    StaticBoxSizer2->Add(PanelCameraDetails, 3, wxALL|wxEXPAND, 5);
    PanelCameraList->SetSizer(StaticBoxSizer2);
    StaticBoxSizer2->Fit(PanelCameraList);
    StaticBoxSizer2->SetSizeHints(PanelCameraList);
    BoxSizerMain->Add(PanelCameraList, 0, wxALL|wxEXPAND, 5);
    PanelPropertiesAndVideo = new wxPanel(this, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    Panel1 = new wxPanel(PanelPropertiesAndVideo, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    PanelProperties = new wxPanel(Panel1, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    Notebook1 = new wxNotebook(PanelProperties, ID_NOTEBOOK2, wxDefaultPosition, wxSize(400,208), 0, _T("ID_NOTEBOOK2"));
    Panel11 = new wxPanel(Notebook1, ID_PANEL22, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL22"));
    BoxSizer14 = new wxBoxSizer(wxVERTICAL);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, Panel11, wxEmptyString);
    NotebookProperties = new wxNotebook(Panel11, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    ScrolledWindow1 = new wxScrolledWindow(NotebookProperties, ID_SCROLLEDWINDOW1, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_SCROLLEDWINDOW1"));
    
    FlexGridSizer3 = new wxFlexGridSizer(0, 8, 0, 0);
    StaticText2 = new wxStaticText(ScrolledWindow1, ID_STATICTEXT8, _("Brightness"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    FlexGridSizer3->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderBrightness = new wxSlider(ScrolledWindow1, ID_SLIDER_BRIGHTNESS, 0, 0, 100, wxDefaultPosition, wxSize(130,30), 0, wxGenericValidator(&property_brightness), _T("ID_SLIDER_BRIGHTNESS"));
    FlexGridSizer3->Add(SliderBrightness, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlBrightness = new wxTextCtrl(ScrolledWindow1, ID_TEXTCTRL_BRIGHTNESS, wxEmptyString, wxDefaultPosition, wxSize(60,28), 0, wxIntegerValidator<int>(&property_brightness), _T("ID_TEXTCTRL_BRIGHTNESS"));
    FlexGridSizer3->Add(TextCtrlBrightness, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(ScrolledWindow1, ID_STATICTEXT10, _("Contrast"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    FlexGridSizer3->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderContrast = new wxSlider(ScrolledWindow1, ID_SLIDER_CONTRAST, 0, 0, 100, wxDefaultPosition, wxSize(130,30), 0, wxGenericValidator(&property_contrast), _T("ID_SLIDER_CONTRAST"));
    FlexGridSizer3->Add(SliderContrast, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlContrast = new wxTextCtrl(ScrolledWindow1, ID_TEXTCTRL_CONTRAST, wxEmptyString, wxDefaultPosition, wxSize(60,28), 0, wxIntegerValidator<int>(&property_contrast), _T("ID_TEXTCTRL_CONTRAST"));
    FlexGridSizer3->Add(TextCtrlContrast, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxContrastAuto = new wxCheckBox(ScrolledWindow1, ID_CHECKBOX_CONTRAST_AUTO, _("Auto"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_CONTRAST_AUTO"));
    CheckBoxContrastAuto->SetValue(false);
    FlexGridSizer3->Add(CheckBoxContrastAuto, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(ScrolledWindow1, ID_STATICTEXT11, _("Saturation"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    FlexGridSizer3->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderSaturation = new wxSlider(ScrolledWindow1, ID_SLIDER_SATURATION, 0, 0, 100, wxDefaultPosition, wxSize(130,30), 0, wxGenericValidator(&property_saturation), _T("ID_SLIDER_SATURATION"));
    FlexGridSizer3->Add(SliderSaturation, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlSaturation = new wxTextCtrl(ScrolledWindow1, ID_TEXTCTRL_SATURATION, wxEmptyString, wxDefaultPosition, wxSize(60,28), 0, wxIntegerValidator<int>(&property_saturation), _T("ID_TEXTCTRL_SATURATION"));
    FlexGridSizer3->Add(TextCtrlSaturation, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(ScrolledWindow1, ID_STATICTEXT12, _("Sharpness"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    FlexGridSizer3->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderSharpness = new wxSlider(ScrolledWindow1, ID_SLIDER_SHARPNESS, 0, 0, 100, wxDefaultPosition, wxSize(130,30), 0, wxGenericValidator(&property_sharpness), _T("ID_SLIDER_SHARPNESS"));
    FlexGridSizer3->Add(SliderSharpness, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlSharpness = new wxTextCtrl(ScrolledWindow1, ID_TEXTCTRL_SHARPNESS, wxEmptyString, wxDefaultPosition, wxSize(60,28), 0, wxIntegerValidator<int>(&property_sharpness), _T("ID_TEXTCTRL_SHARPNESS"));
    FlexGridSizer3->Add(TextCtrlSharpness, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(ScrolledWindow1, ID_STATICTEXT13, _("Gamma"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    FlexGridSizer3->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderGamma = new wxSlider(ScrolledWindow1, ID_SLIDER_GAMMA, 0, 0, 100, wxDefaultPosition, wxSize(130,30), 0, wxGenericValidator(&property_gamma), _T("ID_SLIDER_GAMMA"));
    FlexGridSizer3->Add(SliderGamma, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlGamma = new wxTextCtrl(ScrolledWindow1, ID_TEXTCTRL_GAMMA, wxEmptyString, wxDefaultPosition, wxSize(60,28), 0, wxIntegerValidator<int>(&property_gamma), _T("ID_TEXTCTRL_GAMMA"));
    FlexGridSizer3->Add(TextCtrlGamma, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText7 = new wxStaticText(ScrolledWindow1, ID_STATICTEXT14, _("White Balance (Blue)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    FlexGridSizer3->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderWhiteBalanceBlue = new wxSlider(ScrolledWindow1, ID_SLIDER_WB_BLUE, 0, 0, 100, wxDefaultPosition, wxSize(130,30), 0, wxGenericValidator(&property_wb_blue), _T("ID_SLIDER_WB_BLUE"));
    FlexGridSizer3->Add(SliderWhiteBalanceBlue, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlWhiteBalanceBlue = new wxTextCtrl(ScrolledWindow1, ID_TEXTCTRL_WB_BLUE, wxEmptyString, wxDefaultPosition, wxSize(60,28), 0, wxFloatingPointValidator<float>(&property_wb_blue_in_float, wxNUM_VAL_NO_TRAILING_ZEROES), _T("ID_TEXTCTRL_WB_BLUE"));
    FlexGridSizer3->Add(TextCtrlWhiteBalanceBlue, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxWhiteBalanceAuto = new wxCheckBox(ScrolledWindow1, ID_CHECKBOX_WB_AUTO, _("Auto"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_WB_AUTO"));
    CheckBoxWhiteBalanceAuto->SetValue(false);
    FlexGridSizer3->Add(CheckBoxWhiteBalanceAuto, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(ScrolledWindow1, ID_STATICTEXT16, _("Backlight"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    FlexGridSizer3->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderBacklight = new wxSlider(ScrolledWindow1, ID_SLIDER_BACKLIGHT, 0, 0, 100, wxDefaultPosition, wxSize(130,30), 0, wxGenericValidator(&property_backlight), _T("ID_SLIDER_BACKLIGHT"));
    FlexGridSizer3->Add(SliderBacklight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlBacklight = new wxTextCtrl(ScrolledWindow1, ID_TEXTCTRL_BACKLIGHT, wxEmptyString, wxDefaultPosition, wxSize(60,28), 0, wxIntegerValidator<int>(&property_backlight), _T("ID_TEXTCTRL_BACKLIGHT"));
    FlexGridSizer3->Add(TextCtrlBacklight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText8 = new wxStaticText(ScrolledWindow1, ID_STATICTEXT15, _("White Balance (Red)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    FlexGridSizer3->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderWhiteBalanceRed = new wxSlider(ScrolledWindow1, ID_SLIDER_WB_RED, 0, 0, 100, wxDefaultPosition, wxSize(130,30), 0, wxGenericValidator(&property_wb_red), _T("ID_SLIDER_WB_RED"));
    FlexGridSizer3->Add(SliderWhiteBalanceRed, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlWhiteBalanceRed = new wxTextCtrl(ScrolledWindow1, ID_TEXTCTRL_WB_RED, wxEmptyString, wxDefaultPosition, wxSize(60,28), 0, wxFloatingPointValidator<float>(&property_wb_red_in_float, wxNUM_VAL_NO_TRAILING_ZEROES), _T("ID_TEXTCTRL_WB_RED"));
    FlexGridSizer3->Add(TextCtrlWhiteBalanceRed, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);    
    StaticText10 = new wxStaticText(ScrolledWindow1, ID_STATICTEXT17, _("Gain"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    FlexGridSizer3->Add(StaticText10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderGain = new wxSlider(ScrolledWindow1, ID_SLIDER_GAIN, 0, 0, 100, wxDefaultPosition, wxSize(130,30), 0, wxGenericValidator(&property_gain), _T("ID_SLIDER_GAIN"));
    FlexGridSizer3->Add(SliderGain, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlGain = new wxTextCtrl(ScrolledWindow1, ID_TEXTCTRL_GAIN, wxEmptyString, wxDefaultPosition, wxSize(60,28), 0, wxIntegerValidator<int>(&property_gain), _T("ID_TEXTCTRL_GAIN"));
    FlexGridSizer3->Add(TextCtrlGain, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ScrolledWindow1->SetSizer(FlexGridSizer3);
    FlexGridSizer3->Fit(ScrolledWindow1);
    FlexGridSizer3->SetSizeHints(ScrolledWindow1);
   

    ScrolledWindow2 = new wxScrolledWindow(NotebookProperties, ID_SCROLLEDWINDOW2, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_SCROLLEDWINDOW2"));
    FlexGridSizer4 = new wxFlexGridSizer(0, 4, 0, 0);
    StaticText11 = new wxStaticText(ScrolledWindow2, ID_STATICTEXT18, _("Absolute Exposure Time"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    FlexGridSizer4->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderAbsoluteExposureTime = new wxSlider(ScrolledWindow2, ID_SLIDER_ABS_EXPOSURE_TIME, 0, 0, 100, wxDefaultPosition, wxSize(200,30), 0, wxGenericValidator(&property_abs_exposure_time), _T("ID_SLIDER_ABS_EXPOSURE_TIME"));
    FlexGridSizer4->Add(SliderAbsoluteExposureTime, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlAbsoluteExposureTime = new wxTextCtrl(ScrolledWindow2, ID_TEXTCTRL_ABS_EXPOSURE_TIME, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxIntegerValidator<int>(&property_abs_exposure_time), _T("ID_TEXTCTRL_ABS_EXPOSURE_TIME"));
    FlexGridSizer4->Add(TextCtrlAbsoluteExposureTime, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxExposureTimeAuto = new wxCheckBox(ScrolledWindow2, ID_CHECKBOX_EXPOSURE_TIME_AUTO, _("Auto"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_EXPOSURE_TIME_AUTO"));
    CheckBoxExposureTimeAuto->SetValue(false);
    FlexGridSizer4->Add(CheckBoxExposureTimeAuto, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ScrolledWindow2->SetSizer(FlexGridSizer4);
    FlexGridSizer4->Fit(ScrolledWindow2);
    FlexGridSizer4->SetSizeHints(ScrolledWindow2);
    ScrolledWindow3 = new wxScrolledWindow(NotebookProperties, ID_SCROLLEDWINDOW3, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_SCROLLEDWINDOW3"));
    FlexGridSizer5 = new wxFlexGridSizer(0, 4, 0, 0);
    StaticText13 = new wxStaticText(ScrolledWindow3, ID_STATICTEXT20, _("Video Mode"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
    FlexGridSizer5->Add(StaticText13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ChoiceVideoMode = new wxChoice(ScrolledWindow3, ID_CHOICE_VIDEO_MODE, wxDefaultPosition, wxSize(200,30), 0, 0, 0, wxGenericValidator(&property_videomode), _T("ID_CHOICE_VIDEO_MODE"));
    ChoiceVideoMode->Append(_("OFF"));
    ChoiceVideoMode->Append(_("WAKEUP"));
    ChoiceVideoMode->Append(_("CONTINUOUS"));
    FlexGridSizer5->Add(ChoiceVideoMode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText14 = new wxStaticText(ScrolledWindow3, ID_STATICTEXT21, _("Illumination Mode"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    FlexGridSizer5->Add(StaticText14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ChoiceIlluminationMode = new wxChoice(ScrolledWindow3, ID_CHOICE_ILLUMINATION_MODE, wxDefaultPosition, wxSize(200,30), 0, 0, 0, wxGenericValidator(&property_illuminationmode), _T("ID_CHOICE_ILLUMINATION_MODE"));
    ChoiceIlluminationMode->Append(_("Standard"));
    ChoiceIlluminationMode->Append(_("Always On"));
    ChoiceIlluminationMode->Append(_("Always Off"));
    FlexGridSizer5->Add(ChoiceIlluminationMode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxPowerUserMode = new wxCheckBox(ScrolledWindow3, ID_CHECKBOX_POWER_USER_MODE, _("Power-user Mode"), wxDefaultPosition, wxDefaultSize, 0, wxGenericValidator(&property_powerusermode), _T("ID_CHECKBOX_POWER_USER_MODE"));
    CheckBoxPowerUserMode->SetValue(false);
    CheckBoxPowerUserMode->SetToolTip(_("Enabling power-user mode will disable gain, exposure and white balance"));
    FlexGridSizer5->Add(CheckBoxPowerUserMode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ScrolledWindow3->SetSizer(FlexGridSizer5);
    FlexGridSizer5->Fit(ScrolledWindow3);
    FlexGridSizer5->SetSizeHints(ScrolledWindow3);
    ScrolledWindow4 = new wxScrolledWindow(NotebookProperties, ID_SCROLLEDWINDOW4, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_SCROLLEDWINDOW4"));
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
    TextCtrlConfiguration = new wxTextCtrl(ScrolledWindow4, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(469,227), wxTE_MULTILINE|wxTE_RICH|wxTE_RICH2|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer2->Add(TextCtrlConfiguration, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1 = new wxGridSizer(6, 1, 0, 0);
    ButtonRetriveConfig = new wxButton(ScrolledWindow4, ID_BUTTON1, _("Retrieve Configuration"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    GridSizer1->Add(ButtonRetriveConfig, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonLoadConfig = new wxButton(ScrolledWindow4, ID_BUTTON2, _("Load Configuration"), wxDefaultPosition, wxSize(164,29), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    GridSizer1->Add(ButtonLoadConfig, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonClearTextConfig = new wxButton(ScrolledWindow4, ID_BUTTON3, _("Clear Text"), wxDefaultPosition, wxSize(166,29), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    GridSizer1->Add(ButtonClearTextConfig, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(GridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ScrolledWindow4->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(ScrolledWindow4);
    FlexGridSizer2->SetSizeHints(ScrolledWindow4);
    
    ScrolledWindowNew = new wxScrolledWindow(NotebookProperties, ID_SCROLLEDWINDOWNEW, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_SCROLLEDWINDOWNEW"));           
    FlexGridSizerNew = new wxFlexGridSizer(4, 4, 30, 50);      
    StaticTextEventType = new wxStaticText(ScrolledWindowNew, ID_STATICTEXT_FORMAT, _("Event Type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_EVENT_TYPE"));
    FlexGridSizerNew->Add(StaticTextEventType, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);    
    TextCtrlEventType = new wxTextCtrl(ScrolledWindowNew, ID_TEXTCTRL_EVENT_TYPE, wxEmptyString, wxDefaultPosition, wxSize(200,28), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_EVENT_TYPE"));
    FlexGridSizerNew->Add(TextCtrlEventType, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);  
    StaticTextFormat = new wxStaticText(ScrolledWindowNew, ID_STATICTEXT_FORMAT, _("Format"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_FORMAT"));
    FlexGridSizerNew->Add(StaticTextFormat, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);//   
    TextCtrlFormat = new wxTextCtrl(ScrolledWindowNew, ID_TEXTCTRL_FORMAT, wxEmptyString, wxDefaultPosition, wxSize(200,28), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_FORMAT"));
    FlexGridSizerNew->Add(TextCtrlFormat, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextSize = new wxStaticText(ScrolledWindowNew, ID_STATICTEXT_SIZE, _("Size(kB)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_SIZE"));
    FlexGridSizerNew->Add(StaticTextSize, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);   
    TextCtrlSize = new wxTextCtrl(ScrolledWindowNew, ID_TEXTCTRL_SIZE, wxEmptyString, wxDefaultPosition, wxSize(200,28), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_SIZE"));
    FlexGridSizerNew->Add(TextCtrlSize, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);       
    StaticTextTimeStamp = new wxStaticText(ScrolledWindowNew, ID_STATICTEXT_SIZE, _("Time Stamp"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_TIME_STAMP"));
    FlexGridSizerNew->Add(StaticTextTimeStamp, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);   
    TextCtrlTimeStamp = new wxTextCtrl(ScrolledWindowNew, ID_TEXTCTRL_TIME_STAMP, wxEmptyString, wxDefaultPosition, wxSize(200,28), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_TIME_STAMP"));
    FlexGridSizerNew->Add(TextCtrlTimeStamp, 1,wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);   
    StaticTextImageResolution = new wxStaticText(ScrolledWindowNew, ID_STATICTEXT_SIZE, _("Image Resolution"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_IMAGE_RESOLUTION"));
    FlexGridSizerNew->Add(StaticTextImageResolution, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);   
    TextCtrlImageResolution = new wxTextCtrl(ScrolledWindowNew, ID_TEXTCTRL_IMAGE_RESOLUTION, wxEmptyString, wxDefaultPosition, wxSize(200,28), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_IMAGE_RESOLUTION"));
    FlexGridSizerNew->Add(TextCtrlImageResolution, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);   
    StaticTextDecodeData = new wxStaticText(ScrolledWindowNew, ID_STATICTEXT_SIZE, _("Decode Data"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_DECODE_DATA"));
    FlexGridSizerNew->Add(StaticTextDecodeData, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);   
    TextCtrlDecodeData = new wxTextCtrl(ScrolledWindowNew, ID_TEXTCTRL_DECODE_DATA, wxEmptyString, wxDefaultPosition, wxSize(200,28), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_DECODE_DATA"));
    FlexGridSizerNew->Add(TextCtrlDecodeData, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    StaticTextWeightUnit = new wxStaticText(ScrolledWindowNew, ID_STATICTEXT_SIZE, _("Weight Data"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_WEIGHT_UNIT"));
    FlexGridSizerNew->Add(StaticTextWeightUnit, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);  
    TextCtrlWeightUnit = new wxTextCtrl(ScrolledWindowNew, ID_TEXTCTRL_WEIGHT_UNIT, wxEmptyString, wxDefaultPosition, wxSize(200,28), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_WEIGHT_UNIT"));
    FlexGridSizerNew->Add(TextCtrlWeightUnit, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
 
    StaticTextStreamStatus = new wxStaticText(ScrolledWindowNew, ID_STATICTEXT_SIZE, _("Stream Status"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_STREAM_STATUS"));
    FlexGridSizerNew->Add(StaticTextStreamStatus, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);  
    TextCtrlStreamStatus = new wxTextCtrl(ScrolledWindowNew, ID_TEXTCTRL_STREAM_STATUS, wxEmptyString, wxDefaultPosition, wxSize(200,28), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_STREAM_STATUS"));
    FlexGridSizerNew->Add(TextCtrlStreamStatus, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);  
   
    ScrolledWindowNew->SetSizer(FlexGridSizerNew);    
    FlexGridSizerNew->Fit(ScrolledWindowNew);
    FlexGridSizerNew->SetSizeHints(ScrolledWindowNew);
    
    
    
    
    NotebookProperties->AddPage(ScrolledWindow1, _("Processing Unit"), false);
    NotebookProperties->AddPage(ScrolledWindow2, _("Camera Terminal"), false);
    NotebookProperties->AddPage(ScrolledWindow3, _("Extension Unit"), false);
    NotebookProperties->AddPage(ScrolledWindow4, _("Configuration"), false);
    NotebookProperties->AddPage(ScrolledWindowNew, _("Event Information"), false);
    
    StaticBoxSizer3->Add(NotebookProperties, 1, wxALL|wxEXPAND, 5);
    StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, Panel11, _("Miscellaneous"));
    Panel3 = new wxPanel(Panel11, ID_PANEL11, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL11"));
    FlexGridSizer6 = new wxFlexGridSizer(0, 5, 0, wxDLG_UNIT(Panel3,wxSize(15,0)).GetWidth());
    ButtonSetPropertyDefaults = new wxButton(Panel3, ID_BUTTONSET_PROPERTY_DEFAULTS, _("Set Defaults"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONSET_PROPERTY_DEFAULTS"));
    ButtonSetPropertyDefaults->SetToolTip(_("Set camera properties to their default values"));
    FlexGridSizer6->Add(ButtonSetPropertyDefaults, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonReboot = new wxButton(Panel3, ID_BUTTON_REBOOT, _("Reboot"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_REBOOT"));
    ButtonReboot->SetToolTip(_("Reboot the camera"));
    FlexGridSizer6->Add(ButtonReboot, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
   
    
    ButtonWriteToFlash = new wxButton(Panel3, ID_BUTTON_WRITE_TO_FLASH, _("Write To Flash"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_WRITE_TO_FLASH"));
    ButtonWriteToFlash->SetToolTip(_("Write current property values to flash memory"));
    FlexGridSizer6->Add(ButtonWriteToFlash, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonCaptureSnapshot = new wxButton(Panel3, ID_BUTTON_CAPTURE_SNAPSHOT, _("Capture Snapshot"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CAPTURE_SNAPSHOT"));
    FlexGridSizer6->Add(ButtonCaptureSnapshot, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    
    
    
    Panel3->SetSizer(FlexGridSizer6);
    FlexGridSizer6->Fit(Panel3);
    FlexGridSizer6->SetSizeHints(Panel3);
    StaticBoxSizer4->Add(Panel3, 1, wxALL|wxEXPAND, 5);
    StaticBoxSizer3->Add(StaticBoxSizer4, 0, wxEXPAND, 0);
    BoxSizer14->Add(StaticBoxSizer3, 0, wxEXPAND, 0);
    Panel11->SetSizer(BoxSizer14);
    BoxSizer14->Fit(Panel11);
    BoxSizer14->SetSizeHints(Panel11);



    Panel2 = new wxPanel(Notebook1, ID_PANEL9, wxPoint(75,14), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL9"));
    Panel2->SetBackgroundColour(wxColour(240,240,240));
    GridSizer2 = new wxGridSizer(2, 2, 0, 0);
    Panel4 = new wxPanel(Panel2, ID_PANEL10, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL10"));
    StaticBoxSizer7 = new wxStaticBoxSizer(wxHORIZONTAL, Panel4, _("Tower Image"));
    PanelTowerImg = new wxPanel(Panel4, ID_PANEL26, wxDefaultPosition, wxSize(442,142), wxTAB_TRAVERSAL, _T("ID_PANEL26"));
    TowerImgBitmap = new wxStaticBitmap(PanelTowerImg, ID_STATICBITMAP1, wxNullBitmap, wxDefaultPosition, wxSize(442,142), 0, _T("ID_STATICBITMAP1"));
    StaticBoxSizer7->Add(PanelTowerImg, 1, wxALL|wxEXPAND, 5);
    Panel4->SetSizer(StaticBoxSizer7);
    StaticBoxSizer7->Fit(Panel4);
    StaticBoxSizer7->SetSizeHints(Panel4);
    GridSizer2->Add(Panel4, 1, wxALL|wxEXPAND, 5);
    Panel12 = new wxPanel(Panel2, ID_PANEL23, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL23"));
    StaticBoxSizer8 = new wxStaticBoxSizer(wxHORIZONTAL, Panel12, _("Platter Image"));
    PanelPlatterImage = new wxPanel(Panel12, ID_PANEL27, wxDefaultPosition, wxSize(442,142), wxTAB_TRAVERSAL, _T("ID_PANEL27"));
    PlatterImgBitmap = new wxStaticBitmap(PanelPlatterImage, ID_STATICBITMAP2, wxNullBitmap, wxPoint(0,0), wxSize(442,142), 0, _T("ID_STATICBITMAP2"));
    StaticBoxSizer8->Add(PanelPlatterImage, 1, wxALL|wxEXPAND, 5);
    Panel12->SetSizer(StaticBoxSizer8);
    StaticBoxSizer8->Fit(Panel12);
    StaticBoxSizer8->SetSizeHints(Panel12);
    GridSizer2->Add(Panel12, 1, wxALL|wxEXPAND, 5);
    Panel13 = new wxPanel(Panel2, ID_PANEL24, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL24"));
    StaticBoxSizer9 = new wxStaticBoxSizer(wxHORIZONTAL, Panel13, _("Color camera decode Image"));
    PanelDecodeImage = new wxPanel(Panel13, ID_PANEL28, wxDefaultPosition, wxSize(442,142), wxTAB_TRAVERSAL, _T("ID_PANEL28"));
    DecodeImgBitmap = new wxStaticBitmap(PanelDecodeImage, ID_STATICBITMAP3, wxNullBitmap, wxPoint(0,0),wxSize(442,142), 0, _T("ID_STATICBITMAP3"));
    StaticBoxSizer9->Add(PanelDecodeImage, 1, wxALL|wxEXPAND, 5);
    Panel13->SetSizer(StaticBoxSizer9);
    StaticBoxSizer9->Fit(Panel13);
    StaticBoxSizer9->SetSizeHints(Panel13);
    GridSizer2->Add(Panel13, 1, wxALL|wxEXPAND, 5);
    Panel14 = new wxPanel(Panel2, ID_PANEL25, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL25"));    
    GridSizer4 = new wxGridSizer(4, 1, 0, 0);
    GridSizer4->Add(1,1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BtnStartMonochrome = new wxButton(Panel14, ID_BUTTON5, _("Start Listening"), wxDefaultPosition, wxSize(111,30), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    GridSizer4->Add(BtnStartMonochrome, 1, wxALL|wxALIGN_RIGHT, 5);
    ButtonStopMonochrome = new wxButton(Panel14, ID_BUTTON7, _("Stop Listening"), wxDefaultPosition, wxSize(111,30), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    GridSizer4->Add(ButtonStopMonochrome, 1, wxALL|wxALIGN_RIGHT, 5);
    BtnClearMonochrome = new wxButton(Panel14, ID_BUTTON6, _("Clear Images"), wxDefaultPosition, wxSize(111,30), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    GridSizer4->Add(BtnClearMonochrome, 1, wxALL|wxALIGN_RIGHT, 5);
    Panel14->SetSizer(GridSizer4);
    GridSizer4->Fit(Panel14);
    GridSizer4->SetSizeHints(Panel14);
   
    GridSizer2->Add(Panel14, 1, wxALL|wxEXPAND, 5);
    Panel2->SetSizer(GridSizer2);
    GridSizer2->Fit(Panel2);
    GridSizer2->SetSizeHints(Panel2);
    Notebook1->AddPage(Panel11, _("Properties"), false);
    Notebook1->AddPage(Panel2, _("Decode Images"), false);
    BoxSizer4->Add(Notebook1, 1, wxALL|wxEXPAND, 5);
    PanelProperties->SetSizer(BoxSizer4);
    BoxSizer4->Fit(PanelProperties);
    BoxSizer4->SetSizeHints(PanelProperties);
    BoxSizer2->Add(PanelProperties, 1, wxALL|wxEXPAND, 5);
    PanelVideoEvents = new wxPanel(Panel1, ID_PANEL8, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL8"));
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    PanelVideoEx = new wxPanel(PanelVideoEvents, ID_PANEL_VIDEO_EX, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_VIDEO_EX"));
    StaticBoxSizerVideoEx = new wxStaticBoxSizer(wxHORIZONTAL, PanelVideoEx, _("Video"));
    PanelVideoDisplay = new VideoPanel(PanelVideoEx, ID_PANEL20, wxDefaultPosition, wxSize(480,300), wxTAB_TRAVERSAL, _T("ID_PANEL20"));
    StaticBoxSizerVideoEx->Add(PanelVideoDisplay, 1, wxALL|wxEXPAND, 5);
    PanelVideoEx->SetSizer(StaticBoxSizerVideoEx);
    StaticBoxSizerVideoEx->Fit(PanelVideoEx);
    StaticBoxSizerVideoEx->SetSizeHints(PanelVideoEx);
    BoxSizer3->Add(PanelVideoEx, 1, wxALL|wxEXPAND, 5);
    PanelVideoProperties = new wxPanel(PanelVideoEvents, ID_PANEL12, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL12"));
    StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, PanelVideoProperties, _("Properties"));
    StaticText12 = new wxStaticText(PanelVideoProperties, ID_STATICTEXT19, _("Video profiles"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    StaticBoxSizer5->Add(StaticText12, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ChoiceVideoProfiles = new wxChoice(PanelVideoProperties, ID_CHOICE_VIDEO_PROFILES, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_VIDEO_PROFILES"));
    StaticBoxSizer5->Add(ChoiceVideoProfiles, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelVideoProperties->SetSizer(StaticBoxSizer5);
    StaticBoxSizer5->Fit(PanelVideoProperties);
    StaticBoxSizer5->SetSizeHints(PanelVideoProperties);
    BoxSizer3->Add(PanelVideoProperties, 0, wxALL|wxEXPAND, 5);
    PanelVideoEvents->SetSizer(BoxSizer3);
    BoxSizer3->Fit(PanelVideoEvents);
    BoxSizer3->SetSizeHints(PanelVideoEvents);
    BoxSizer2->Add(PanelVideoEvents, 1, wxALL|wxEXPAND, 5);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel1);
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND, 5);
    PanelPropertiesAndVideo->SetSizer(BoxSizer1);
    BoxSizer1->Fit(PanelPropertiesAndVideo);
    BoxSizer1->SetSizeHints(PanelPropertiesAndVideo);
    BoxSizerMain->Add(PanelPropertiesAndVideo, 1, wxALL|wxEXPAND, 5);
    PanelMisc = new wxPanel(this, ID_PANEL_MISC, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_MISC"));
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    Panel5 = new wxPanel(PanelMisc, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Panel5, _("Firmware Update"));
    Panel8 = new wxPanel(Panel5, ID_PANEL17, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL17"));
    BoxSizer9 = new wxBoxSizer(wxVERTICAL);
    Panel9 = new wxPanel(Panel8, ID_PANEL18, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL18"));
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    StaticText16 = new wxStaticText(Panel9, ID_STATICTEXT23, _("File"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
    BoxSizer10->Add(StaticText16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FilePickerCtrlFirmware = new wxFilePickerCtrl(Panel9, ID_FILEPICKERCTRL_FIRMWARE, wxEmptyString, wxEmptyString, _T("*.DAT"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN, wxDefaultValidator, _T("ID_FILEPICKERCTRL_FIRMWARE"));
    BoxSizer10->Add(FilePickerCtrlFirmware, 3, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonUpdate = new wxButton(Panel9, ID_BUTTON_UPDATE, _("Update"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_UPDATE"));
    BoxSizer10->Add(ButtonUpdate, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonCancel = new wxButton(Panel9, ID_BUTTON_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CANCEL"));
    BoxSizer10->Add(ButtonCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel9->SetSizer(BoxSizer10);
    BoxSizer10->Fit(Panel9);
    BoxSizer10->SetSizeHints(Panel9);
    BoxSizer9->Add(Panel9, 1, wxALL|wxEXPAND, 5);
    Panel10 = new wxPanel(Panel8, ID_PANEL21, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL21"));
    BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
    StaticText18 = new wxStaticText(Panel10, ID_STATICTEXT25, _("Download progress"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
    BoxSizer12->Add(StaticText18, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GaugeFirmwareDownloadProgress = new wxGauge(Panel10, ID_GAUGE_FW_DOWNLOAD_PROGRESS, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAUGE_FW_DOWNLOAD_PROGRESS"));
    BoxSizer12->Add(GaugeFirmwareDownloadProgress, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel10->SetSizer(BoxSizer12);
    BoxSizer12->Fit(Panel10);
    BoxSizer12->SetSizeHints(Panel10);
    BoxSizer9->Add(Panel10, 1, wxALL|wxEXPAND, 5);
    BoxSizer9->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel8->SetSizer(BoxSizer9);
    BoxSizer9->Fit(Panel8);
    BoxSizer9->SetSizeHints(Panel8);
    StaticBoxSizer1->Add(Panel8, 1, wxALL|wxEXPAND, 5);
    Panel5->SetSizer(StaticBoxSizer1);
    StaticBoxSizer1->Fit(Panel5);
    StaticBoxSizer1->SetSizeHints(Panel5);
    BoxSizer5->Add(Panel5, 1, wxALL|wxEXPAND, 5);
    Panel6 = new wxPanel(PanelMisc, ID_PANEL13, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL13"));
    StaticBoxSizer6 = new wxStaticBoxSizer(wxVERTICAL, Panel6, _("Image Events"));
    Panel7 = new wxPanel(Panel6, ID_PANEL14, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL14"));
    BoxSizer6 = new wxBoxSizer(wxVERTICAL);
    PanelEvents = new wxPanel(Panel7, ID_PANEL15, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL15"));
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    
    
    CheckBoxContinuousEvents = new wxCheckBox(PanelEvents, ID_CHECKBOX_CONTINUOUS_EVENTS, _("Continuous"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_CONTINUOUS_EVENTS"));
    CheckBoxContinuousEvents->SetValue(false);
    BoxSizer7->Add(CheckBoxContinuousEvents, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxProduceEvents = new wxCheckBox(PanelEvents, ID_CHECKBOX_PRODUCE_EVENTS, _("Produce"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_PRODUCE_EVENTS"));
    CheckBoxProduceEvents->SetValue(false);
    BoxSizer7->Add(CheckBoxProduceEvents, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxSnapshotEvents = new wxCheckBox(PanelEvents, ID_CHECKBOX_SNAPSHOT_EVENTS, _("Snapshot"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_SNAPSHOT_EVENTS"));
    CheckBoxSnapshotEvents->SetValue(false);
    BoxSizer7->Add(CheckBoxSnapshotEvents, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxDecodeEvents = new wxCheckBox(PanelEvents, ID_CHECKBOX_DECODE_EVENTS, _("Decode"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_DECODE_EVENTS"));
    CheckBoxDecodeEvents->SetValue(false);
    BoxSizer7->Add(CheckBoxDecodeEvents, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxSessionEvents = new wxCheckBox(PanelEvents, ID_CHECKBOX1, _("Session"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBoxSessionEvents->SetValue(false);
    BoxSizer7->Add(CheckBoxSessionEvents, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  
    CheckBoxStreamEvents = new wxCheckBox(PanelEvents, ID_CHECKBOX2, _("Stream"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBoxStreamEvents->SetValue(false);
    BoxSizer7->Add(CheckBoxStreamEvents, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  
    CheckBoxDetectBoundingBox = new wxCheckBox(PanelEvents, ID_CHECKBOX_DETECT_BOUNDING_BOX, _("Detect Bounding Box"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_DETECT_BOUNDING_BOX"));
    CheckBoxDetectBoundingBox->SetValue(false);
    BoxSizer7->Add(CheckBoxDetectBoundingBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSetBackground = new wxButton(PanelEvents, ID_BUTTON_SET_BACKGROUND, _("Set Background"), wxDefaultPosition, wxSize(90,29), 0, wxDefaultValidator, _T("ID_BUTTON_SET_BACKGROUND"));
    BoxSizer7->Add(ButtonSetBackground, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelEvents->SetSizer(BoxSizer7);
    BoxSizer7->Fit(PanelEvents);
    BoxSizer7->SetSizeHints(PanelEvents);
    BoxSizer6->Add(PanelEvents, 1, wxALL|wxEXPAND, 5);
    PanelImageFormat = new wxPanel(Panel7, ID_PANEL19, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL19"));
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    StaticText17 = new wxStaticText(PanelImageFormat, ID_STATICTEXT24, _("Image Format"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
    BoxSizer11->Add(StaticText17, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    ChoiceImageFormat = new wxChoice(PanelImageFormat, ID_CHOICE_IMAGE_FORMAT, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_IMAGE_FORMAT"));
    ChoiceImageFormat->SetSelection( ChoiceImageFormat->Append(_("JPG")) );
    ChoiceImageFormat->Append(_("BMP"));
    BoxSizer11->Add(ChoiceImageFormat, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxSaveImages = new wxCheckBox(PanelImageFormat, ID_CHECKBOX_SAVE_IMAGES, _("Save Images"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_SAVE_IMAGES"));
    CheckBoxSaveImages->SetValue(false);
    BoxSizer11->Add(CheckBoxSaveImages, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);

    StaticText20 = new wxStaticText(PanelImageFormat, ID_STATICTEXT27, _("Device Awake"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
    BoxSizer13->Add(StaticText20, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    LedDeviceAwake = new wxLed(PanelImageFormat,ID_LED2,wxColour(128,128,128),wxColour(0,255,0),wxColour(255,0,0),wxDefaultPosition,wxDefaultSize);
    LedDeviceAwake->SwitchOn();
    BoxSizer13->Add(LedDeviceAwake, 1, wxALL|wxEXPAND, 5);
    BoxSizer11->Add(BoxSizer13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelImageFormat->SetSizer(BoxSizer11);
    BoxSizer11->Fit(PanelImageFormat);
    BoxSizer11->SetSizeHints(PanelImageFormat);
    BoxSizer6->Add(PanelImageFormat, 1, wxALL, 5);
    PanelSaveImage = new wxPanel(Panel7, ID_PANEL16, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL16"));
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    StaticText15 = new wxStaticText(PanelSaveImage, ID_STATICTEXT22, _("Save images to"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
    BoxSizer8->Add(StaticText15, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    DirPickerCtrlSaveImage = new wxDirPickerCtrl(PanelSaveImage, ID_DIRPICKERCTRL_SAVE_IMAGE, wxEmptyString, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST, wxDefaultValidator, _T("ID_DIRPICKERCTRL_SAVE_IMAGE"));
    BoxSizer8->Add(DirPickerCtrlSaveImage, 2, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSaveImage = new wxButton(PanelSaveImage, ID_BUTTON_SAVE_IMAGE, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SAVE_IMAGE"));
    BoxSizer8->Add(ButtonSaveImage, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelSaveImage->SetSizer(BoxSizer8);
    BoxSizer8->Fit(PanelSaveImage);
    BoxSizer8->SetSizeHints(PanelSaveImage);
    BoxSizer6->Add(PanelSaveImage, 1, wxALL|wxEXPAND, 5);
    Panel7->SetSizer(BoxSizer6);
    BoxSizer6->Fit(Panel7);
    BoxSizer6->SetSizeHints(Panel7);
    StaticBoxSizer6->Add(Panel7, 1, wxALL|wxEXPAND, 5);
    Panel6->SetSizer(StaticBoxSizer6);
    StaticBoxSizer6->Fit(Panel6);
    StaticBoxSizer6->SetSizeHints(Panel6);
    BoxSizer5->Add(Panel6, 1, wxALL|wxEXPAND, 5);
    PanelMisc->SetSizer(BoxSizer5);
    BoxSizer5->Fit(PanelMisc);
    BoxSizer5->SetSizeHints(PanelMisc);
    BoxSizerMain->Add(PanelMisc, 0, wxALL|wxEXPAND, 5);
    SetSizer(BoxSizerMain);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    BoxSizerMain->Fit(this);
    BoxSizerMain->SetSizeHints(this);

    Connect(ID_CHOICE_SELECTED_CAMERA,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnChoiceSelectedCameraSelect);
    Connect(ID_SLIDER_BRIGHTNESS,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnSliderBrightnessCmdScrollChanged);
    Connect(ID_TEXTCTRL_BRIGHTNESS,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnTextCtrlBrightnessText);
    Connect(ID_SLIDER_CONTRAST,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnSliderContrastCmdScrollChanged);
    Connect(ID_TEXTCTRL_CONTRAST,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnTextCtrlContrastText);
    Connect(ID_CHECKBOX_CONTRAST_AUTO,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnCheckBoxContrastAutoClick);
    Connect(ID_SLIDER_SATURATION,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnSliderSaturationCmdScrollChanged);
    Connect(ID_TEXTCTRL_SATURATION,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnTextCtrlSaturationText);
    Connect(ID_SLIDER_SHARPNESS,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnSliderSharpnessCmdScrollChanged);
    Connect(ID_TEXTCTRL_SHARPNESS,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnTextCtrlSharpnessText);
    Connect(ID_SLIDER_GAMMA,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnSliderGammaCmdScrollChanged);
    Connect(ID_TEXTCTRL_GAMMA,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnTextCtrlGammaText);
    Connect(ID_SLIDER_WB_BLUE,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnSliderWhiteBalanceBlueCmdScrollChanged);
    Connect(ID_TEXTCTRL_WB_BLUE,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnTextCtrlWhiteBalanceBlueText);
    Connect(ID_CHECKBOX_WB_AUTO,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnCheckBoxWhiteBalanceAutoClick);
    Connect(ID_SLIDER_WB_RED,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnSliderWhiteBalanceRedCmdScrollChanged);
    Connect(ID_TEXTCTRL_WB_RED,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnTextCtrlWhiteBalanceRedText);
    Connect(ID_SLIDER_BACKLIGHT,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnSliderBacklightCmdScrollChanged);
    Connect(ID_TEXTCTRL_BACKLIGHT,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnTextCtrlBacklightText);
    Connect(ID_SLIDER_GAIN,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnSliderGainCmdScrollChanged);
    Connect(ID_TEXTCTRL_GAIN,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnTextCtrlGainText);
    Connect(ID_SLIDER_ABS_EXPOSURE_TIME,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnSliderAbsoluteExposureTimeCmdScrollChanged);
    Connect(ID_TEXTCTRL_ABS_EXPOSURE_TIME,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnTextCtrlAbsoluteExposureTimeText);
    Connect(ID_CHECKBOX_EXPOSURE_TIME_AUTO,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnCheckBoxExposureTimeAutoClick);
    Connect(ID_CHOICE_VIDEO_MODE,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnChoiceVideoModeSelect);
    Connect(ID_CHOICE_ILLUMINATION_MODE,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnChoiceIlluminationModeSelect);
    Connect(ID_CHECKBOX_POWER_USER_MODE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnCheckBoxPowerUserModeClick);
//    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnButton1Click);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnButtonRegriveConfigClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnButtonLoadConfigClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnButtonClearTextConfigClick);
    Connect(ID_BUTTONSET_PROPERTY_DEFAULTS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnButtonSetPropertyDefaultsClick);
    Connect(ID_BUTTON_REBOOT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnButtonRebootClick);   
    Connect(ID_BUTTON_WRITE_TO_FLASH,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnButtonWriteToFlashClick);
    Connect(ID_BUTTON_CAPTURE_SNAPSHOT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnButtonCaptureSnapshotClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnBtnStartMonochromeClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnButtonStopMonochromeClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnBtnClearMonochromeClick);
    Connect(ID_CHOICE_VIDEO_PROFILES,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnChoiceVideoProfilesSelect);
    Connect(ID_FILEPICKERCTRL_FIRMWARE,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnFilePickerCtrlFirmwareFileChanged);
    Connect(ID_BUTTON_UPDATE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnButtonUpdateClick);
    Connect(ID_BUTTON_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnButtonCancelClick);
    Connect(ID_CHECKBOX_CONTINUOUS_EVENTS,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnCheckBoxContinuousEventsClick);
    Connect(ID_CHECKBOX_PRODUCE_EVENTS,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnCheckBoxProduceEventsClick);
    Connect(ID_CHECKBOX_SNAPSHOT_EVENTS,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnCheckBoxSnapshotEventsClick);
    Connect(ID_CHECKBOX_DECODE_EVENTS,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnCheckBoxDecodeEventsClick);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnCheckBoxSessionEventsClick);

    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnCheckBoxStreamEventsClick);

    Connect(ID_CHOICE_IMAGE_FORMAT,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnChoiceImageFormatSelect);
    Connect(ID_CHECKBOX_SAVE_IMAGES,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnCheckBoxSaveImagesClick);
    Connect(ID_DIRPICKERCTRL_SAVE_IMAGE,wxEVT_COMMAND_DIRPICKER_CHANGED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnDirPickerCtrlSaveImageDirChanged);
    
	
	
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnClose);
    
    Connect(ID_BUTTON_SET_BACKGROUND,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnButtonSetBackgroundClick);
    Connect(ID_CHECKBOX_DETECT_BOUNDING_BOX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnCheckBoxDetectBoundingBoxClick);
    Connect(ID_BUTTON_SAVE_IMAGE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnButtonSaveImageClick);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&ZebraCameraDemoFrame::OnClose);
    //*)


    // Add scrollbars.
    ScrolledWindow1->SetScrollbars(20, 20, 20, 20);
    ScrolledWindow2->SetScrollbars(20, 20, 20, 20);
    ScrolledWindow3->SetScrollbars(20, 20, 20, 20);

    // Set logger to console.
    logger_ = new wxLogStream(&std::cout);
    logger_->SetLogLevel(wxLOG_FatalError);
    wxLog::SetActiveTarget(logger_);

    wxLogMessage("%s", __func__);

    camera_manager_client_ = zebra::camera_sdk::CreateZebraCameraManagerClient();

    ClearAllCameraProperties();

    // Create PnP listener.
    CreatePnpListeners();

    // Create firmware download event listener.
    CreateFirmwareDownloadEventListener();

    // Create image event listeners.
    CreateImageEventListeners();

    // Image file format.
    image_file_format_ = (ImageFileFormat)ChoiceImageFormat->GetSelection();

    // Bind auto white balance timer handler.
    auto_white_balance_monitor_timer_.SetOwner(this);
    Bind(wxEVT_TIMER, &ZebraCameraDemoFrame::OnAutoWhiteBalanceUpdateTimer, this);

    // Enumerate already attched cameras.
    QueueAlreadyAttachedCameraEvents();

}

ZebraCameraDemoFrame::~ZebraCameraDemoFrame()
{
    //(*Destroy(ZebraCameraDemoFrame)
    //*)

	wxLogMessage("%s", __func__);
}

void ZebraCameraDemoFrame::OnQuit(wxCommandEvent& event)
{
    (void)event;

    wxLogMessage("%s", __func__);

    Close();
}

void ZebraCameraDemoFrame::OnAbout(wxCommandEvent& event)
{
    (void)event;
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void ZebraCameraDemoFrame::OnChoiceSelectedCameraSelect(wxCommandEvent& event)
{

    unsigned int selected = event.GetSelection();

    wxLogMessage("%s: selected=%d", __func__, selected);

    for (unsigned int i = 0; i < ChoiceSelectedCamera->GetCount(); i++)
    {
        std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>
            *client_data = (std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>*)
                            ChoiceSelectedCamera->GetClientData(i);
        wxLogMessage("%s: vid=%x, pid=%x, sn=%s, path=%s, selected=%d, cam=%p",
        __func__,
        client_data->first.vid, client_data->first.pid, client_data->first.serial_number, client_data->first.device_path,
        selected,
        client_data->second.get());

        if (i == selected)
        {
            // Found the selected camera information. Create the camera.
            try
            {
                std::shared_ptr<ZebraCameraClient> camera = camera_manager_client_->CreateZebraCamera(client_data->first);    // Create the camera.
                client_data->second = camera;

                // First, clear all properties.
                ClearAllCameraProperties();
                // Then, populate the properties for the new camera.
                PopulateCameraProperties(camera);
            }
            catch (std::exception& e)
            {
                wxMessageBox(e.what(), "Error");
            }
        }
        else
        {
            // Any other camera will be released.
            client_data->second = nullptr;
        }
    }

}


std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> ZebraCameraDemoFrame::GetCamera()
{

    std::shared_ptr<ZebraCameraClient> camera = nullptr;

    int index = ChoiceSelectedCamera->GetSelection();

    if (wxNOT_FOUND != index)
    {
        std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>
            *client_data = (std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>*)
                            ChoiceSelectedCamera->GetClientData(index);
        if (client_data)
        {
                camera = client_data->second;
            }
        }

    return camera;
}

void ZebraCameraDemoFrame::PopulateCameraProperties(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxLogMessage("%s", __func__);

    if (camera)
    {
        PopulateCameraAssetTrackingInfo(camera);
        PopulateProcessingUnitInfo(camera);
        PopulateCameraTerminalInfo(camera);
        PopulateExtensionUnit1Info(camera);
        PopulateVideoProfiles(camera);
        PopulateDeviceAwake(camera);
    }
}

void ZebraCameraDemoFrame::ClearAllCameraProperties()
{

    ClearCameraAssetTrackingInfo();
    ClearProcessingUnitInfo();
    ClearCameraTerminalInfo();
    ClearExtensionUnit1Info();
    ClearVideoProfiles();
    ClearVideoEvents();
    ClearDeviceAwakeInfo();

}
/** This method is responsible for reseting the progress bar of firmware update during camera detach and reboot events*/
void ZebraCameraDemoFrame::ResetFirmwareUpdateProgressBar()
{

    GaugeFirmwareDownloadProgress->SetValue(0);
}
void ZebraCameraDemoFrame::ClearVideoProfiles()
{
    ChoiceVideoProfiles->SetSelection(-1);
    unsigned int count = ChoiceVideoProfiles-> GetCount();
    for (unsigned int i = 0; i < count; i++)
    {
        ChoiceVideoProfiles->Delete(0);
    }
}

void ZebraCameraDemoFrame::ReleaseCameras()
{
	for (unsigned int i = 0; i < ChoiceSelectedCamera->GetCount(); i++)
	{
		std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>
			*client_data = (std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>*)
				ChoiceSelectedCamera->GetClientData(i);
		client_data->second = nullptr;
	}
}

void ZebraCameraDemoFrame::OnClose(wxCloseEvent& event)
{

	(void)event;

    wxLogMessage("%s", __func__);

    // Release image event listeners.
    ReleaseImageEventListeners();

    // Release firmware download event listener.
    ReleaseFirmwareDownloadEventListener();

    // Release PnP listener.
    ReleasePnpListeners();

    // Release cameras so that claimed interfaces (control and streaming) are released.
    ReleaseCameras();

    //delete logger_;

    if (listening_started_)
    {
        // stop listening to directory monochrome
        dir_observer_->StopObserving();
    }

    Destroy();

}


/**
 * Start listening Button clicked event.
 * start the monochrome sdk to observe the pointed directory
 * to receive the events.
 * @param event button clicked event
 */
void ZebraCameraDemoFrame::OnBtnStartMonochromeClick(wxCommandEvent& event)
{
    (void)event;
	try{
		if (!listening_started_)
		{
			if (!observer_created_)
			{
				subscriber_ = new ImageEventSubscriberSample(this);
				// creates DirectoryObserver object and registers the above
				// created ImageEventSubscriber object.
				dir_observer_ = new ImageCreationObserver();
				observer_created_ = true;
			}
                        
			dir_observer_->StartObserving(subscriber_);

                        listening_started_ = true;
			BtnStartMonochrome->Enable(false);
		}
	}
	catch (std::exception& exception)
        {
            listening_started_ = false;
            wxMessageBox(exception.what(), "Error");
        }
}

void ZebraCameraDemoFrame::OnButtonStopMonochromeClick(wxCommandEvent& event)
{
    (void)event;
    try 
    {
        if (listening_started_)
        {
            dir_observer_->StopObserving();

            listening_started_ = false;
            BtnStartMonochrome->Enable(true);

        }
    }
    catch (std::exception& exception)
    {
        wxMessageBox(exception.what(), "Error");
    }
}


/**
 * Shows the resized decode image in the UI
 */
void ZebraCameraDemoFrame::ShowDecodeImage()
{           
    try 
    {
        if (listening_started_)
        {
            // TEST: get tower platter images when a decode event recieved.
            ImageCreationEvent *image_creation_event = dir_observer_->TriggerTowerPlatterImageEvent(); 
            if(image_creation_event){
                    image_creation_event_ = *image_creation_event; 
                    QueueTowerPlatterImageEvent(); 
            }
        }

		int image_height = 200;
		double aspact_ratio = 1.48;
		int image_width = 200 * aspact_ratio;        

        std::string file_name_temp = "decode.jpg";
        decode_image_.SaveAsJpeg(file_name_temp);

        usleep(500);
        wxBitmap temp_bitmap(file_name_temp);
        wxImage image = temp_bitmap.ConvertToImage();
        image.Rescale(image_width, image_height);
        wxBitmap resized_bitmap(image);
        DecodeImgBitmap->SetBitmap(resized_bitmap);
    }
    catch (std::exception& exception)
    {
        wxMessageBox(exception.what(), "Error");
    }
}

void ZebraCameraDemoFrame::OnBtnClearMonochromeClick(wxCommandEvent& event)
{
    (void)event;
    // creating a black image with 1 pixcel
    int width_null_image = 1;
    int height_null_image = 1;
    wxImage null_image(width_null_image, height_null_image);
    
    // add mask to disapear black color from null_bitmap
    // makes 1 pixcel image invicible
    int red_color_value_for_mask = 0;
    int green_color_value_for_mask = 0;
    int blue_color_value_for_mask = 0;
    null_image.SetMaskColour(red_color_value_for_mask, green_color_value_for_mask, blue_color_value_for_mask);
    
    // make invisible null bitmap
    wxBitmap* null_bitmap = new wxBitmap(null_image);
    
    // clear the platter image
    PlatterImgBitmap->SetBitmap(*null_bitmap );
    PlatterImgBitmap->Update();
    
    // clear the tower image
    TowerImgBitmap->SetBitmap(*null_bitmap );
    TowerImgBitmap->Update();
    
    // clear the decode image
    DecodeImgBitmap->SetBitmap(*null_bitmap );
    DecodeImgBitmap->Update();
    
    delete null_bitmap;
}
