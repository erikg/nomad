//
//  ViewController.swift
//  MoCo
//
//  Created by Erik Greenwald on 8/19/18.
//  Copyright © 2018 ElfGA. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    var left:Int8 = 0
    var right:Int8 = 0

    var timer:Timer?

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        self.timer = Timer.scheduledTimer(withTimeInterval: 0.2, repeats: true) {
            timer in
            NetManager.shared.send(self.left,self.right)
        }
    }

    @IBAction func lf(_ sender:UIControl?) { self.left = Int8.max }
    @IBAction func lb(_ sender:UIControl?) { self.left = Int8.min }
    @IBAction func rf(_ sender:UIControl?) { self.right = Int8.max }
    @IBAction func rb(_ sender:UIControl?) { self.right = Int8.min }

    @IBAction func ltu(_ sendr:UIControl?) { self.left = 0 }
    @IBAction func rtu(_ sendr:UIControl?) { self.right = 0 }
}
