//
//  ViewController.swift
//  MoCo
//
//  Created by Erik Greenwald on 8/19/18.
//  Copyright © 2018 ElfGA. All rights reserved.
//

import UIKit

fileprivate func sq(_ x:CGFloat) -> CGFloat { return x * x }

class ViewController: UIViewController {
    @IBOutlet private weak var leftBar:TreadControl!
    @IBOutlet private weak var rightBar:TreadControl!

    var timer:Timer?


    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        self.timer = Timer.scheduledTimer(withTimeInterval: 0.2, repeats: true) { _ in
            let left = self.leftBar.value / 12.7
            let right = self.rightBar.value / 12.7
            let ldirscale:CGFloat = left < 0 ? -1 : 1
            let rdirscale:CGFloat = right < 0 ? -1 : 1


            let left8:Int8 = Int8(ldirscale * left * left)
            let right8:Int8 = Int8(rdirscale * right * right)
            NetManager.shared.send(left8, right8)
        }
    }

    @IBAction
    func touchUp(_ sender:UIControl?) {
        if let slider = sender as? UISlider {
            slider.setValue(0, animated: true)
        }
    }
}
