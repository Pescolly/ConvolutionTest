//
//  main.swift
//  ConvolutionTest
//
//  Created by armen karamian on 5/21/17.
//  Copyright © 2017 armen karamian. All rights reserved.
//

import Foundation
import AVFoundation

//var componentDescription = AudioComponentDescription()
//componentDescription.componentType = kAudioUnitType_MusicDevice
//componentDescription.componentSubType = 0x73696E33 /*'sin3'*/
//componentDescription.componentManufacturer = 0x44656d6f /*'Demo'*/
//componentDescription.componentFlags = 0
//componentDescription.componentFlagsMask = 0
//
// /*
//Register our `AUAudioUnit` subclass, `AUv3InstrumentDemo`, to make it able
//to be instantiated via its component description.
//
//Note that this registration is local to this process.
//*/
//AUAudioUnit.registerSubclass(AUv3InstrumentDemo.self, as: componentDescription, name: "Demo: Local InstrumentDemo", version: UInt32.max)
//
// // Instantiate and insert our audio unit effect into the chain.
//playEngine.selectAudioUnitWithComponentDescription(componentDescription) {
//	// This is an asynchronous callback when complete. Finish audio unit setup.
//	self.connectParametersToControls()
//}
//}




let engine = AVAudioEngine()
let format = engine.outputNode.inputFormat(forBus: 0)
let fileFormat = AVAudioFormat(commonFormat: .pcmFormatFloat32, sampleRate: format.sampleRate, channels: 2, interleaved: true)
var cd : AudioComponentDescription? = AudioComponentDescription()
cd?.componentType = kAudioUnitType_Generator
cd?.componentSubType = 0x636F6E76 				// 'conv'
cd?.componentManufacturer = 0x6772706c			// 'grpl'
cd?.componentFlags = 0
cd?.componentFlagsMask = 0

AUAudioUnit.registerSubclass(ConvolutionUnitAudioUnit.self, as: cd!, name: "Convolution", version: 1)

var convUnit : AVAudioUnit?

if let compDesc = cd {
	AVAudioUnit.instantiate(with: cd!, options: .loadInProcess, completionHandler:
	{
		convolutionUnit, error in
		convUnit = convolutionUnit
		engine.attach(convolutionUnit!)
	})
}
guard convUnit != nil else
{
	print("convunit nil")
	exit(999)
}
do
{
	let file1URL = NSURL(fileURLWithPath: "/Users/armen/Documents/440hz_stereo.aiff")
	let file2URL = NSURL(fileURLWithPath: "/Users/armen/Documents/880hz_stereo.aiff")
//

	let file1 = try AVAudioFile(forReading: file1URL as URL)
	let file2 = try AVAudioFile(forReading: file2URL as URL)

	let buffer1 = AVAudioPCMBuffer(pcmFormat: file1.processingFormat, frameCapacity: AVAudioFrameCount(file1.length))
	let buffer2 = AVAudioPCMBuffer(pcmFormat: file2.processingFormat, frameCapacity: AVAudioFrameCount(file2.length))

	let file1Node = AVAudioPlayerNode()
	try file1.read(into: buffer1)
	let file2Node = AVAudioPlayerNode()
	try file2.read(into: buffer2)

	engine.attach(file1Node)
	engine.attach(file2Node)
	
//	engine.connect(file1Node, to: convUnit!, fromBus: 0, toBus: 0, format: format)
//	engine.connect(file2Node, to: convUnit!, fromBus: 0, toBus: 1, format: format)
	engine.connect(convUnit!, to: engine.mainMixerNode, fromBus: 0, toBus: 0, format: format)

	try engine.start()

//engine.connect(file1Node, to: engine.mainMixerNode, fromBus: 0, toBus: 0, format: format)

//	file1Node.play()
//	file2Node.play()
//	file1Node.scheduleBuffer(buffer1, completionHandler: nil)
//	file2Node.scheduleBuffer(buffer2, completionHandler: nil)

	
	sleep(UInt32(10))
}
catch
{
	assertionFailure("AVAudioEngine start error: \(error)")
}
