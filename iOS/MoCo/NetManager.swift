//
//  NetManager.swift
//  MoCo
//
//  Created by Erik Greenwald on 8/19/18.
//  Copyright © 2018 ElfGA. All rights reserved.
//

import Foundation
import SwiftSocket

class NetManager: NSObject {
    static var shared = NetManager()
    let socket = SwiftSocket.UDPClient(address: "nomad", port: 5128)

    func send(_ left:Int8, _ right:Int8) {
        let lb = Byte(bitPattern: left)
        let rb = Byte(bitPattern: right)
        let _ = self.socket.send(data: [lb, rb])
        return
    }
}
