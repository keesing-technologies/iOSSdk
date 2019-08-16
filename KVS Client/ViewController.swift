//
//  ViewController.swift
//  KVS Client
//
//  Created by Hossein Bahrami on 04/06/2019.
//  Copyright © 2019 Hossein Bahrami. All rights reserved.
//

import UIKit
import GenuineIDMobileFramework

class ViewController: GenuineIDBaseController, URLSessionDelegate {
    private let sendingLabel = UILabel();
    private let serverUrl = "accdocker01.ktech.local"
    
    //Handler to accept self-signed certificates from devdocker01.ktech.local
    func urlSession(_ session: URLSession, didReceive challenge: URLAuthenticationChallenge, completionHandler: @escaping (URLSession.AuthChallengeDisposition, URLCredential?) -> Void) {
        if(challenge.protectionSpace.authenticationMethod == NSURLAuthenticationMethodServerTrust)
        {
            if(challenge.protectionSpace.host == serverUrl)
            {
                let credential = URLCredential.init(trust: challenge.protectionSpace.serverTrust as SecTrust!)
                completionHandler(URLSession.AuthChallengeDisposition.useCredential, credential)

            }
        }
    }
    
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
        
        self.showSending()
        
        // you can perform the upload of the payload to the JenID Solutions GmbH server here or in another UIViewController
        DispatchQueue.global(qos: .background).async {
            //background code
            self.sendData(jenIdPayload: completeJsonPayload)
            
            DispatchQueue.main.async {
                self.hideSending()
            }
        }
    }
    
    override open func doAfterFail(frontImage: UIImage, encodedFrontImage: String, backImage: UIImage, encodedBackImage: String, completeJsonPayload: String)
    {
       
        debugPrint("doAfterFail")        
       
    }  

    
    func sendData(jenIdPayload:String)
    {
        if let url = NSURL(string: "https://\(serverUrl):8889/sdkapi")
        {
            var request = URLRequest(url: url as URL)
            request.httpMethod = "POST"
            request.setValue("application/json", forHTTPHeaderField: "Content-Type")
            
            
            let data = jenIdPayload.data(using: .utf8) as! Data
            let jsonObj = try? JSONSerialization.jsonObject(with: data, options: .allowFragments) as? NSDictionary
            
            let jsonData = try? JSONSerialization.data(withJSONObject: jsonObj)
            request.httpBody = jsonData
            request.timeoutInterval = 40
            
            // create session
            let config = URLSessionConfiguration.default
            let session = URLSession(configuration: config, delegate: self, delegateQueue: nil)
            
            let task = session.dataTask(with: request, completionHandler: { (data, response, error) -> Void in
                if error != nil
                {
                    debugPrint("upload file error: \(error!.localizedDescription): \(error!)")
                    self.showMessage(title: "Error", message: error!.localizedDescription)
                }
                else if data != nil
                {
                    if let str = NSString(data: data!, encoding: String.Encoding.utf8.rawValue)
                    {
                        debugPrint("upload file received data:\n\(str)")
                        debugPrint((response as! HTTPURLResponse).statusCode)
                        
                        if ((response as! HTTPURLResponse).statusCode == 200)
                        {
                            // aknowledge user ...
                            self.showMessage(title: "Success", message: "Data has been sent")
                        }
                        else
                        {
                            self.showMessage(title: "Error", message: "Status != 200")
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
    
    
    func showSending()
    {
        if (sendingLabel.tag != 999)
        {
            let view = self.view as UIView
            sendingLabel.frame = CGRect(x: 0, y: view.center.y, width: view.frame.width, height: 50)
            sendingLabel.backgroundColor = .black
            sendingLabel.textColor = .white
            sendingLabel.text = "Sending..."
            sendingLabel.tag = 999
        }
        
        self.view.addSubview(sendingLabel)
    }
    
    func hideSending()
    {
        sendingLabel.removeFromSuperview()
    }
    
    func showMessage(title: String, message:String)
    {
        let alert = UIAlertController(title: title, message: message, preferredStyle: UIAlertController.Style.alert)
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: goHome))
        self.present(alert, animated: true, completion: nil)
    }
    
    func goHome(alert: UIAlertAction!)
    {
        DispatchQueue.main.async {
            let storyBoard: UIStoryboard = UIStoryboard(name: "Main", bundle: nil)
            let vc = storyBoard.instantiateViewController(withIdentifier: "HomeScreen") as! ViewController
            self.navigationController!.pushViewController(vc, animated: false)
        }
    }

    
    
}


