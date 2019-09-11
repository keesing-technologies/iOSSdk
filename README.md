**iOS SDK Integration with KVS**

List of Contents

- [System Requirements](#System-Requirements)
- [Access Rights](#Access-Rights)
- [Base Controller](#Base-Controller)
- [SDK](#SDK) 
- [Integration](#Integration)
- [Using the class](#Using-the-class)
- [Configuration](#Configuration)
- [Code Example](#Code-Example)
- [Sending the Payload to Genuine-ID HUB Server](#Sending-the-Payload-to-Genuine-ID-HUB-Server)
- [Send Data](#Send-Data)
- [Retrieve Data](#Retrieve-Data)
- [UI Customization](#UI-Customization)

The Genuine-ID Capture SDK provides functionality to integrate ID document and facial capture functionality
into your App to be later on verified by the Genuine-ID CLOUD (or a Genuine-ID HUB Server on premises installation).
The SDK is easy and simple to understand to limit the effort for integration and encapsulates all the complicated
image processing functions for you. You simply need to integrate and configure only one _UIViewController_: GenuineIDBaseController

## System Requirements

The SDK does support all Apple's mobile devices. The required minimum version of the iOS operating system is 10.

## Access Rights

The SDK needs demands access to cameras. The user has to grant these rights otherwise your App will not work as expected.

## Base Controller

This _UIViewController_ leads the end-user through the process of detecting id-documents, detecting
ISO conform faces and proceeding a liveness check. As a result there will be cropped images of
the id-documents pages, as well as valid _JSON_ data to be send to the verification server
for further processing, extracting of data and verification.

The steps to be taken by the end-user are:

1. selection of the document type, from _TD3_ (Passports) and _TD1_ (national id-cards & driver licenses)
2. capturing one or two pages of a document
3. detecting an ISO conform image of the end user
4. performing a liveness check

Note: the selection of the document type is critical for correctly detecting the right document
proportions in an image. It does make a difference to search for a _TD1_ or _TD3_ document.

The capturing process consists of two sub steps. First the user takes an image, whether
automatically or manually (after the automatic process took too long). Second the user reviews
the found document and can correct it if needed. The better the cropping result, the better
the verification of the document will perform.

Also note, that the last two steps are optional. It is possible to configure the _UIViewController_ to
not perform the face detection. A liveness check will only be performed if an ISO conform image
was detected.

## SDK

### Integration

In order to use the functionality of the Genuine-ID Capture SDK you will have to copy the archive
_GenuineIDMobileFramework.framework_ to your project. In XCode this can be simply done by drag and drop
into your project.

If the _Framework_ is visible in the _Frameworks_ section of your project everything is set correctly.

### Using the class

The _GenuineIDBaseController_ is an open class, that extends an _UIViewController_.
When implemented by your App, the user is guided through the whole process by a couple of
specialized _UIViews_. These _UIViews_ use partly either the front (face detection) or back
(document detection) camera. They deal with all the camera related topics: displaying the camera
stream, triggering auto focus when possible or let the user set focus manually by touching the
desired area. Additionally, the user interface guides the user throughout the entire process
when needed and displays important information on the screen.

Note: It is crucial, that your _UIViewController_ is embedded in a _NavigationController_. This
is very easy to accomplish: Make sure your _UIViewController_ is selected and go to
"Editor > Embed In > Navigation Controller"

There are two possible callbacks to be used by the integrating developer:

1. _doAfterDocumentFound_
2. _doAfterFail_

The first callback will be called, when a document could be successfully detected and - if
configured to do so - an ISO conform face image could be made and verified by a liveness check.

The second callback will be called when the process of detecting an ISO conform face and/or the
performing of the liveness check failed. This will happen for example when the end user does not
keep his face in the screen, or it is not possible to get an ISO conform image of his face. The
end user can try three times. After that, the _doAfterFail_ callback will be called.

Since both callbacks are abstract methods, they have to be implemented by the integrating
developer of this Genuine-ID Mobile SDK and serve as entry points for further actions, like
presenting the found document and the face image to the end suer and starting new *UIViewController*s
and so on.

In either way the instance will provide you the images in different formats
and the compiled JSON formatted payload to be send to the Server.

The callbacks will have the following parameters:

- frontImage:UIImage -- the image of first captured side
- encodedFrontImage:String -- base64 encoded format of the front image
- backImage:UIImage -- the image of the second captured side of a double sided document; empty in case of a passport document
- encodedBackImage:String -- base64 encoded format of the back image
- faceImage:UIImage -- facial image in case face capture is enabled or empty if face capture is disabled (see configuration)
- encodedFaceImage:String -- base64 encoded format of the face image
- completeJsonPayload:String -- JSON formatted payload as input for the Genuine-ID HUB Server

The resulting images of the pages of the document com in both, a _UIImage_
and a Base64 _String_ representation. The former could be used for your individual processing
or showing to the end user. The Base64 _String_ is optimized for uploading to the verification server order to process the document.

**Note:** The images are already compressed please DO NOT further compress the images
since this will have negative impact on the performance of the Genuine-ID verification engine.

The payload must be used as is. **Do not change** the payload as it might result in errors
and will be rejected by the server.

### Configuration

There are only two possible configuration parameters for an instance of the _GenuineIDBaseController_.

_takePhotoTimeout_ can be used to override the default time setting before the _UIViewController_ starts
the manual capture in case the automatic capture routine will not find any document. The default value
is set to 15000 ms.

_enableFaceDetection_ can be used to enable or disable the face capture funcionality. If set to _false_
the _UIViewController_ will only capture the document images. The default setting is _true_.

### Code Example

The following code snippet demonstrate how to use the _GenuineIDBaseController_ in your App:

    import UIKit
    import GenuineIDMobileFramework

    class CaptureController: GenuineIDBaseController
    {
    	...

        override func viewWillAppear(_ animated: Bool)
        {
            super.viewWillAppear(animated)
        }

        override func viewDidLoad()
        {
            super.viewDidLoad()

            super.takePhotoTimeout = 15
            super.enableFaceDetection = true
        }

        override open func doAfterDocumentFound(
            frontImage:UIImage,
            encodedFrontImage:String,
            backImage:UIImage,
            encodedBackImage:String,
            faceImage:UIImage,
            encodedFaceImage:String,
            completeJsonPayload:String)
        {

            // you can perform the upload of the payload to the verification server here or in another UIViewController
        }

        override open func doAfterFail(
            frontImage:UIImage,
            encodedFrontImage:String,
            backImage backImage:UIImage,
            encodedBackImage encodedBackImage:String,
            completeJsonPayload:String)
        {
            // you can do some handling here e.g. in case you allow an upload of the transaction without the facial image do it here
            // or do display some user guidance how to capture a face successfully...
        }

        ...
    }

**Note:** Please note, that if the end user captures a _TD3_ document (passport), only one page will be
captured. Therefore, _backImage_ and _encodedBackImage_ will be empty. If the face detection
functionality is disabled, _faceImage_ and _encodedFaceImage_ will be empty too.

**Note:** Sometimes it is difficult for the end users to use the capturing process like intended.
Therefore, there is a functionality added, which uses a button to take a photo after a certain
timeout. The photo taken, is processed like the camera stream before and leads to a successfully
detected document, if the photo being taken allows that.

## Sending the Payload to Genuine-ID HUB Server

In this section, you will find information on how to upload the result payload to the server.
The server implements a REST API interface to support stateless (WEB) application design.

# UI Customization

UI customization is possible via various methods available is the main activity, following list is those methods.

- **setBackgroundColor**: sets the background color of the capturing UI pages.
- **setPrimaryColor**: sets the primary color which is suitable to set the enterprice color code.
- **setFontColor1**: sets one of the two font color of the capturing UI pages.
- **setFontColor2**: same as `setFontColor1`.
- **setTextFont**: sets the primary font of all texts available in the capturing process pages.
- **setSecondaryTextFont**: sets the fonts of pages after main page.
- **setCorrectionColor**: sets the color of the rectangle shown during the manual capturing (when automatic capturing fails).
- **setFaceColor1**: sets the color of an indicator over the face during liveness check.
- **setFaceColor2**: sets the color of an indicator over the face when face detection succeeds.
- **setFaceTrackColor**: sets the color of square around the face during the liveness check.
- **setFaceFeatureColor**: sets the color of the squares around face features (eyes/mouth) during liveness check.
- **setWarnColor**: sets the warning color while process failed during capturing or liveness check process.
