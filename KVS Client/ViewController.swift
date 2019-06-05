//
//  ViewController.swift
//  KVS Client
//
//  Created by Hossein Bahrami on 04/06/2019.
//  Copyright © 2019 Hossein Bahrami. All rights reserved.
//

import UIKit
import GenuineIDMobileFramework

class ViewController: GenuineIDBaseController {

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
        
        // you can perform the upload of the payload to the JenID Solutions GmbH server here or in another UIViewController
        
        if let url = NSURL(string: "https://devdocker01.ktech.local:8889/sdkapi")
        {
            var request = URLRequest(url: url as URL)
            request.httpMethod = "POST"
            request.setValue("application/json", forHTTPHeaderField: "Content-Type")
            
            request.httpBody = postString.data(completeJsonPayload)
            request.timeoutInterval = 40
            
            // create session
            let config = URLSessionConfiguration.ephemeral
            let session = URLSession( configuration: config )
            
            let task = session.dataTask(with: request, completionHandler: { (data, response, error) -> Void in
                if error != nil
                {
                    debugPrint("upload file error: \(error!.localizedDescription): \(error!)")
                }
                else if data != nil
                {
                    if let str = NSString(data: data!, encoding: String.Encoding.utf8.rawValue)
                    {
                        debugPrint("upload file received data:\n\(str)")
                        debugPrint((response as! HTTPURLResponse).statusCode)
                        
                        if ((response as HTTPURLResponse).statusCode == 201)
                        {
                            // aknowledge user ...
                        }
                    }
                }
            })
            
            task.resume()
        }
        else
        {
            debugPrint("Unable to create NSURL")
        }
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


}


