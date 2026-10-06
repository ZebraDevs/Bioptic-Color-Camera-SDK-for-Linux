#ifndef CAMERA_IMAGE_EVENTS_H_
#define CAMERA_IMAGE_EVENTS_H_

#include <wx/wx.h>

#include "zebra_camera_client.h"

using namespace zebra::camera_sdk;

class ZebraCameraDemoFrame;

/*
    Continuous image event listener.
*/
class ContinuousImageObserver: public ContinuousImageEventListener
{
public:
	ContinuousImageObserver(ZebraCameraDemoFrame *frame);
	void ImageReceived(ImageEventData image, ImageEventMetaData md) override;

private:
    ZebraCameraDemoFrame *frame_;
};

/*
    Produce image event listener.
*/
class ProduceImageObserver: public ProduceImageEventListener
{
public:
	ProduceImageObserver(ZebraCameraDemoFrame *frame);
	void ImageReceived(ImageEventData image, ImageEventMetaData md) override;

private:
    ZebraCameraDemoFrame *frame_;
};

/*
    Snapshot image event listener.
*/
class SnapshotImageObserver: public SnapshotImageEventListener
{
public:
	SnapshotImageObserver(ZebraCameraDemoFrame *frame);
	void ImageReceived(ImageEventData image, ImageEventMetaData md) override;

private:
    ZebraCameraDemoFrame *frame_;
};

/*
    Decode image event listener.
*/
class DecodeImageObserver: public DecodeImageEventListener
{
public:
	DecodeImageObserver(ZebraCameraDemoFrame *frame);
	void ImageReceived(ImageEventData image, ImageEventMetaData md) override;

private:
    ZebraCameraDemoFrame *frame_;
};

/*
    Decode session status change event listener.
*/
class DecodeSessionStatusChangeEventObserver: public DecodeSessionStatusChangeEventListener
{
public:
	DecodeSessionStatusChangeEventObserver(ZebraCameraDemoFrame *frame);
	void DecodeSessionStatusChanged(DecodeSessionStatus status) override;

private:
    ZebraCameraDemoFrame *frame_;
};

class CameraStreamStatusChangeEventObserver: public CameraStreamStatusChangeEventListener
{
public:
    CameraStreamStatusChangeEventObserver(ZebraCameraDemoFrame *frame);
    void CameraStreamStatusChanged(CameraStreamStatus status) override;

private:
    ZebraCameraDemoFrame *frame_;
};

// Declaration of the CONTINUOUS_IMAGE_EVENT.
wxDECLARE_EVENT(CONTINUOUS_IMAGE_EVENT, wxCommandEvent);

// Declaration of the CAPTURE_SNAPSHOT_EVENT.
wxDECLARE_EVENT(CAPTURE_SNAPSHOT_EVENT, wxCommandEvent);

// Declaration of the PRODUCE_IMAGE_EVENT.
wxDECLARE_EVENT(PRODUCE_IMAGE_EVENT, wxCommandEvent);

// Declaration of the SNAPSHOT_IMAGE_EVENT.
wxDECLARE_EVENT(SNAPSHOT_IMAGE_EVENT, wxCommandEvent);

// Declaration of the DECODE_IMAGE_EVENT.
wxDECLARE_EVENT(DECODE_IMAGE_EVENT, wxCommandEvent);

// Declaration of the DECODE_SESSION_STATUS_CHANGE_EVENT.
wxDECLARE_EVENT(DECODE_SESSION_STATUS_CHANGE_EVENT, wxCommandEvent);

wxDECLARE_EVENT(STREAM_STATUS_CHANGE_EVENT,wxCommandEvent);
#endif // CAMERA_IMAGE_EVENTS_H_
