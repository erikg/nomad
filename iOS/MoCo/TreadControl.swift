//
//  TreadControl.swift
//  MoCo
//
//  Created by Erik Greenwald on 8/22/18.
//  Copyright © 2018 ElfGA. All rights reserved.
//

import UIKit
import Crashlytics

class TreadControl: UIControl {
    @IBInspectable var maximumValue:CGFloat = 1.0
    @IBInspectable var minimumValue:CGFloat = 0.0
    @IBInspectable var defaultValue:CGFloat = 0.0
    @IBInspectable var setDefaultOnTouchUp:Bool = true
    @IBInspectable var barColor:UIColor = UIColor.red

    var yOffset:CGFloat = 0 { didSet { DispatchQueue.main.async { self.layoutIfNeeded() } } }

    var value:CGFloat { get { return self.minimumValue + (self.maximumValue - self.minimumValue) * (1.0 - self.yOffset / self.frame.size.height) } }

    var cookedDefaultValue:CGFloat {
        get {
            return self.frame.height * 0.5
//            return self.frame.height * defaultValue / (self.maximumValue - self.minimumValue)
        }
    }

    private var bar:UIView!

    override func awakeFromNib() {
        super.awakeFromNib()
        let bar = UIView(frame: .zero)
        bar.tintColor = self.barColor
        self.addSubview(bar)

        self.yOffset = self.frame.height * 0.5

        self.bar = bar
    }

    override func layoutSubviews() {
        super.layoutSubviews()
        self.yOffset = self.frame.height * 0.5
        self.bar.frame = CGRect(x: 0, y: self.yOffset - 10, width: self.frame.width, height: 20)
    }

    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        if let y = touches.first?.location(in: self).y {
            self.yOffset = y
        }
        super.touchesBegan(touches, with: event)
    }

    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        if setDefaultOnTouchUp {
            self.yOffset = self.cookedDefaultValue
            self.layoutIfNeeded()
        }
        super.touchesEnded(touches, with: event)
    }

    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        if let y = touches.first?.location(in: self).y {
            self.yOffset = y
        }
        super.touchesMoved(touches, with: event)
    }

    override func touchesCancelled(_ touches: Set<UITouch>, with event: UIEvent?) {
        if setDefaultOnTouchUp {
            self.yOffset = self.cookedDefaultValue
            self.layoutIfNeeded()
        }
        super.touchesCancelled(touches, with: event)
    }
}
