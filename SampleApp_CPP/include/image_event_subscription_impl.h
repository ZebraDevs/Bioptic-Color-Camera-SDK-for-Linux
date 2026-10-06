/*
 * Author: (c)2022 Zebra Technologies Corp. and/or affiliates. All rights reserved.
 * Created on March 31, 2020, 10:08 AM
 */

/*
 * File:   image_event_subscription_impl.h
 * Contains the ImageEventSubscriberSample class
 */


#ifndef IMAGE_EVENT_SUBSCRIPTION_IMPL_H
#define IMAGE_EVENT_SUBSCRIPTION_IMPL_H

#include "image_event_subscriber.h"
#include "image_event.h"

class ZebraCameraDemoFrame;


/**
 * Sample implementation of the ImageEventSubscriber class.
 * ImageEventSubscriber is a pure abstract class. User can implement(inherit)
 * the class to own class and override the RecieveImageEvents method to get the image events.
 */
class ImageEventSubscriberSample : public ImageEventSubscriber {

    public:

        /**
         * Constructor, initializes ImageEventSubscriberSample class variables
         */
        ImageEventSubscriberSample(ZebraCameraDemoFrame *frame);

        /**
         * Sample implementation of the pure virtual method RecieveImageEvents
         * given in the ImageEventSubscriber class.
         * @param image_creation_event ImageCreationEvent object contains the tower platter image data.
         */
        void RecieveImageEvents(ImageCreationEvent *image_creation_event);

    private:
        ZebraCameraDemoFrame *demo_ui_frame_demo_ui_frame_;
};


#endif /* IMAGE_EVENT_SUBSCRIPTION_IMPL_H */
