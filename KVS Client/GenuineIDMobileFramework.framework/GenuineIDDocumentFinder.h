//
//  GenuineIDDocumentFinder.h
//  GenuineIDMobileFramework
//
//  Created by Konstantin Hotzel on 30.01.18.
//  Copyright © 2018,2019 jenID Solutions GmbH. All rights reserved.
//

#ifndef GenuineIDDocumentFinder_h
#define GenuineIDDocumentFinder_h

#include <iostream>
#include <opencv2/core/core.hpp>

using namespace std;

/**
 *
 * Class that serves as a wrapper to the functionality an iOS app would need to
 *
 *  1. find a document (rectangle) in a camera frame
 *  2. dewarp/normalize the found rectangle to,
 *
 * which uses mainly the JenID Solutions code base.
 *
 * @since 2018-01-30
 * @author Konstantin Hotzel
 * @copyright (c) JenID Solutions GmbH 2014-2019, All rights reserved
 *
 */
class CPPGenuineIDDocumentFinder
{
    
public:
    
    static bool isInitialized;
        
    // variables to store the dimensions of the current image used for finding a document:
    int imageWidth;
    int imageHeight;
    
    // variables to store the dimensions of the current image used for the dewarped document:
    int dewarpedImageWidth;
    int dewarpedImageHeight;
    
    // variables to store the coordinates of the found document
    int p1x; int p1y;
    int p2x; int p2y;
    int p3x; int p3y;
    int p4x; int p4y;
    
    int q1x; int q1y;
    int q2x; int q2y;
    int q3x; int q3y;
    int q4x; int q4y;
    
    void initDocumentFinder( string path );
    unsigned char* dewarpQuad ( cv::Mat matImage,
                               int upperLeftX, int upperLeftY,
                               int upperRightX, int upperRightY,
                               int lowerRightX, int lowerRightY,
                               int lowerLeftX, int lowerLeftY,
                               int width, int height);
    unsigned char* resize( cv::Mat matImage, int width, int height, int documentType );
    bool findRect( cv::Mat matImage, int width, int height, int x1, int y1, int x2, int y2, int documentType );
    bool findRect2( cv::Mat matImage, int width, int height, int x1, int y1, int x2, int y2, int documentType );
};

#endif /* GenuineIDDocumentFinder_h */
