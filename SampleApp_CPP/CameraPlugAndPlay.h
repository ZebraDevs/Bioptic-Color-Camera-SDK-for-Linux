/*
    Camera plug-and-play event listenters.
*/

#ifndef CAMERA_PLUGANDPLAY_H_
#define CAMERA_PLUGANDPLAY_H_

#include <wx/wx.h>

#include "device_manager.h"

//using namespace zebra::camera_sdk;

class ZebraCameraDemoFrame;

class AttachedEventObserver: public zebra::DeviceAttachedListener
{
public:
    AttachedEventObserver(ZebraCameraDemoFrame *frame);
	void Attached(zebra::DeviceInfo info) override;

private:
    ZebraCameraDemoFrame *frame_;
};

class DetachedEventObserver: public zebra::DeviceDetachedListener
{
public:
    DetachedEventObserver(ZebraCameraDemoFrame *frame);
	void Detached(zebra::DeviceInfo info) override;

private:
    ZebraCameraDemoFrame *frame_;    
};

// Declaration of the CAMERA_SELECTED_EVENT. Notify when a camera object is created.
wxDECLARE_EVENT(CAMERA_SELECTED_EVENT, wxCommandEvent);

// Declaration of the CAMERA_DESELECTED_EVENT. Notify when a selected camera object is deselected.
wxDECLARE_EVENT(CAMERA_DESELECTED_EVENT, wxCommandEvent);

#endif // CAMERA_PLUGANDPLAY_H_
