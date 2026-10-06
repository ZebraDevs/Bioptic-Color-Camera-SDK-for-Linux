/*
 * Author: (c)2022 Zebra Technologies Corp. and/or affiliates. All rights reserved.
 * Created on March 31, 2020, 10:08 AM
 */

/*
 * File:   image_event_subscription_impl.cpp
 * Contains the method Implemntations of the mageEventSubscriberSample class
 */

#include <iostream>
#include "image_event_subscriber.h"
#include "image_event.h"
#include "image_event_subscription_impl.h"
#include <string>
#include "../ZebraCameraDemoMain.h"



ImageEventSubscriberSample::ImageEventSubscriberSample(ZebraCameraDemoFrame *frame):
    demo_ui_frame_demo_ui_frame_(frame)
{

}

void ImageEventSubscriberSample::RecieveImageEvents(ImageCreationEvent *image_creation_event)
{
    demo_ui_frame_demo_ui_frame_->image_creation_event_ = *image_creation_event;
    demo_ui_frame_demo_ui_frame_->QueueTowerPlatterImageEvent();  

        
}




