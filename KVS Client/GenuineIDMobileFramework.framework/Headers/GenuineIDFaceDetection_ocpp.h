//
//  GenuineIDFaceDetection_ocpp.h
//  GenuineIDMobileFramework
//
//  Created by Jen ID on 07.05.18.
//  Copyright © 2018 Jen ID. All rights reserved.
//

#ifndef GenuineIDFaceDetection_ocpp_h
#define GenuineIDFaceDetection_ocpp_h

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface FaceDetection: NSObject
+(int)px1;
+(int)py1;
+(int)px2;
+(int)py2;
+(bool)pMouthOpen;
+(bool)pEyesOpen;
+(double)pEyeDistance;
+(double)pRotationPitch;
+(double)pRotationRoll;
+(double)pRotationYaw;
+(double)processingTimeFaceMatch;
+(int) kptsCount;
+(bool) matchingResult;
+(int*) x;
+(int*) y;
+(bool) isoFound;
+(double) processingTimeReference;
+(int) kptsCountReference;
+(bool) enoughFound;
+(bool) faceFound;
+(double) processingTimeFace;
+(double) processingTimeIso;
+(double) processingTime;
+(int*) kptsX;
+(int*) kptsY;
+(int) width;
+(int) height;
+(int) x1Frame;
+(int) y1Frame;
+(int) x2Frame;
+(int) y2Frame;
+(double) processingTimeSmile;
+(double) processingTimeBlink;

+(int*) x1MouthFrame;
+(int*) y1MouthFrame;
+(int*) x2MouthFrame;
+(int*) y2MouthFrame;
+(int*) lMouthFrame;
+(int*) x1EyesFrame;
+(int*) y1EyesFrame;
+(int*) x2EyesFrame;
+(int*) y2EyesFrame;
+(bool) blinkingResult;
+(bool) closeEyes;
+(UIImage*) blinkImage;
+(int) remainingBlinks;
+(bool) smilingResult;
+(UIImage*) smileImage;
+(UIImage*) image2;
+(int) faceX1;
+(int) faceY1;
+(int) faceX2;
+(int) faceY2;





-(bool) isInitialized;
-(void) setIsInitialized:(bool)value;
-(void) initFaceDetection;
-(void) destroyFaceDetection;

-(void) matchFace:  (UIImage*)uiImage withWidth:(int)width withHeight:(int)height withCropX1:(int)cropX1 withCropY1:(int)cropY1 withCropX2:(int)cropX2 withCropY2:(int)cropY2;
-(bool) findFace:   (UIImage*)uiImage withWidth:(int)width withHeight:(int)height withCropX1:(int)cropX1 withCropY1:(int)cropY1 withCropX2:(int)cropX2 withCropY2:(int)cropY2;
-(bool) detectSmile:(UIImage*)uiImage withWidth:(int)width withHeight:(int)height withCropX1:(int)cropX1 withCropY1:(int)cropY1 withCropX2:(int)cropX2 withCropY2:(int)cropY2 withExpectedRuns:(int)expectedRuns;
-(bool) detectBlink:(UIImage*)uiImage withWidth:(int)width withHeight:(int)height withCropX1:(int)cropX1 withCropY1:(int)cropY1 withCropX2:(int)cropX2 withCropY2:(int)cropY2 withExpectedRuns:(int)expectedRuns;

-(double) calculateSharpness:(UIImage*)uiImage withWidth:(int)width withHeight:(int)height withCropX1:(int)x1 withCropY1:(int)y1 withCropX2:(int)x2 withCropY2:(int)y2;
@end

#endif /* GenuineIDFaceDetection_ocpp_h */
