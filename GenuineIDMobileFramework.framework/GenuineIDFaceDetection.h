//
//  GenuineIDFaceDetection.hpp
//  GenuineIDMobileFramework
//
//  Created by Jen ID on 07.05.18.
//  Copyright © 2018 Jen ID. All rights reserved.
//

#ifndef GenuineIDFaceDetection_hpp
#define GenuineIDFaceDetection_hpp

#include <iostream>
#include <opencv2/core/core.hpp>

using namespace std;

class CPPGenuineIDFaceDetection
{    
public:
    
    static bool isInitialized;
        
    // variables to store the coordinates of the found document
    
    bool mouthOpen;
    bool eyesOpen;
    double eyeDistance;
    double rotationPitch;
    double rotationRoll;
    double rotationYaw;
    double processingTimeFaceMatch;
    int kptsCount;
    bool matchingResult;
    int* x;
    int* y;
    bool isoFound;
    double processingTimeReference;
    int kptsCountReference;
    bool enoughFound;
    bool faceFound;
    double processingTimeFace;
    double processingTimeIso;
    double processingTime;
    int* kptsX;
    int* kptsY;
    double processingTimeSmile;
    double processingTimeBlink;
    
    int* x1MouthFrame;
    int* y1MouthFrame;
    int* x2MouthFrame;
    int* y2MouthFrame;
    int* lMouthFrame;
    int* x1EyesFrame;
    int* y1EyesFrame;
    int* x2EyesFrame;
    int* y2EyesFrame;
    bool blinkingResult;
    bool closeEyes;
    cv::Mat blinkImage;
    int remainingBlinks;
    bool smilingResult;
    cv::Mat smileImage;
    double x1;
    double y1;
    double x2;
    double y2;
    int x1Frame;
    int y1Frame;
    int x2Frame;
    int y2Frame;
    int width;
    int height;
    cv::Mat image2;
    int faceX1;
    int faceY1;
    int faceX2;
    int faceY2;
    
    void initFaceDetection( string path, string pathSmile, string pathEyes );
    void destroyFaceDetection();
    
    bool detectMouth( cv::Mat image, double dbFactor, double bbFactor, int cropX1, int cropY1 );
    bool detectEyes( cv::Mat image, double dbFactor, double bbFactor, int cropX1, int cropY1 );
    bool detectBlink( cv::Mat matImage, double dbFactor, double bbFactor, int cropX1, int cropY1, cv::Mat blinkImage );
    bool detectSmile( cv::Mat matImage, double dbFactor, double bbFactor, int cropX1, int cropY1, cv::Mat smileImage );
    bool processImageFast( cv::Mat matImage, double factor, int cropX1, int cropY1 );
    
    bool detectBlinkStart( cv::Mat matImage, int width, int height, int cropX1, int cropY1, int cropX2, int cropY2, int expectedRuns );
    bool detectSmileStart( cv::Mat matImage, int width, int height, int cropX1, int cropY1, int cropX2, int cropY2, int expectedRuns );    
    bool findFaceStart( cv::Mat matImage, int width, int height, int cropX1, int cropY1, int cropX2, int cropY2 );
    
    void initTracker( cv::Mat image, double factor, int cropX1, int cropX2, int faceX1, int faceY1, int faceX2, int faceY2 );
    void processFaceTracking( cv::Mat matImage, double factor, int cropX1, int cropY1 );
    void matchFace( cv::Mat matImage, int width, int height, int cropX1, int cropY1, int cropX2, int cropY2 );
};

#endif /* GenuineIDFaceDetection_hpp */
