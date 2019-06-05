//
//  GenuineIDDocumentFinder_ocpp.h
//  GenuineIDMobileFramework
//
//  Created by Konstantin Hotzel on 30.01.18.
//  Copyright © 2018,2019 jenID Solutions GmbH. All rights reserved.
//

#ifndef GenuineIDDocumentFinder_ocpp_h
#define GenuineIDDocumentFinder_ocpp_h

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface DocumentFinder: NSObject
+(int)imageWidth;
+(int)imageHeight;
+(int)dewarpedImageWidth;
+(int)dewarpedImageHeight;
+(int)p1x;
+(int)p1y;
+(int)p2x;
+(int)p2y;
+(int)p3x;
+(int)p3y;
+(int)p4x;
+(int)p4y;
+(int)q1x;
+(int)q1y;
+(int)q2x;
+(int)q2y;
+(int)q3x;
+(int)q3y;
+(int)q4x;
+(int)q4y;

-(bool) isInitialized;
-(void) setIsInitialized:(bool)value;
-(void) initDocumentFinder;
-(UIImage*) dewarpQuad:(UIImage*)uiImage withWidth:(int)width withHeight:(int)height withUpLeftX:(int)upperLeftX withUpLeftY:(int)upperLeftY withUpRightX:(int)upperRightX withUpRightY:(int)upperRightY withLowRightX:(int)lowerRightX withLowRightY:(int)lowerRightY withLowLeftX:(int)lowerLeftX withLowLeftY:(int)lowerLeftY;
-(UIImage*) resize:(UIImage*)uiImage withWidth:(int)width widthHeight:(int)height withDocumentType:(int)documentType;

-(bool) findRect:(UIImage*)uiImage withWidth:(int)width withHeight:(int)height withCropX1:(int)x1 withCropY1:(int)y1 withCropX2:(int)x2 withCropY2:(int)y2 withDocumentType:(int)documentType;
-(bool) findRect2:(UIImage*)uiImage withWidth:(int)width withHeight:(int)height withCropX1:(int)x1 withCropY1:(int)y1 withCropX2:(int)x2 withCropY2:(int)y2 withDocumentType:(int)documentType;


-(bool) isSharp:(UIImage*)uiImage withWidth:(int)width withHeight:(int)height withCropX1:(int)x1 withCropY1:(int)y1 withCropX2:(int)x2 withCropY2:(int)y2;
-(double) calculateSharpness:(UIImage*)uiImage withWidth:(int)width withHeight:(int)height withCropX1:(int)x1 withCropY1:(int)y1 withCropX2:(int)x2 withCropY2:(int)y2;
@end

#endif /* GenuineIDDocumentFinder_ocpp_h */
