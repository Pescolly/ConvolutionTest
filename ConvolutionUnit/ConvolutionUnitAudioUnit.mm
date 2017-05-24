//
//  ConvolutionUnitAudioUnit.m
//  ConvolutionUnit
//
//  Created by armen karamian on 5/21/17.
//  Copyright © 2017 armen karamian. All rights reserved.
//

#import "ConvolutionUnitAudioUnit.h"
#import "BufferedAudioBus.hpp"
#import <AVFoundation/AVFoundation.h>

// Define parameter addresses.
const AudioUnitParameterID myParam1 = 0;

@interface ConvolutionUnitAudioUnit ()

@property AUAudioUnitBus *outputBus;
@property AUAudioUnitBusArray *inputBusArray;
@property AUAudioUnitBusArray *outputBusArray;
@property (nonatomic, readwrite) AUParameterTree *parameterTree;

@end


@implementation ConvolutionUnitAudioUnit
{
	BufferedInputBus _inputBus;
}

@synthesize parameterTree = _parameterTree;

- (instancetype)initWithComponentDescription:(AudioComponentDescription)componentDescription
									 options:(AudioComponentInstantiationOptions)options
									   error:(NSError **)outError
{
    self = [super initWithComponentDescription:componentDescription
									   options:options
										 error:outError];
    if (self == nil) { return nil; }
	
	
	AVAudioFormat *defaultFormat = [[AVAudioFormat alloc] initWithCommonFormat:AVAudioPCMFormatFloat32  sampleRate:44100 channels:2 interleaved:false];
	
		//	_inputBus.init(defaultFormat, 8);
	_outputBus = [[AUAudioUnitBus alloc] initWithFormat:defaultFormat error:nil];
	
		// Create the input and output bus arrays.
		//	_inputBusArray  = [[AUAudioUnitBusArray alloc] initWithAudioUnit:self busType:AUAudioUnitBusTypeInput busses: @[_inputBus.bus]];
	_outputBusArray = [[AUAudioUnitBusArray alloc] initWithAudioUnit:self busType:AUAudioUnitBusTypeOutput busses: @[_outputBus]];
	
	self.maximumFramesToRender = 512;
    
    return self;
}

#pragma mark - AUAudioUnit Overrides

// If an audio unit has input, an audio unit's audio input connection points.
// Subclassers must override this property getter and should return the same object every time.
// See sample code.
- (AUAudioUnitBusArray *)inputBusses
{
#warning implementation must return non-nil AUAudioUnitBusArray
    return _inputBusArray;
}

// An audio unit's audio output connection points.
// Subclassers must override this property getter and should return the same object every time.
// See sample code.
- (AUAudioUnitBusArray *)outputBusses
{
#warning implementation must return non-nil AUAudioUnitBusArray
    return _outputBusArray;
}

// Allocate resources required to render.
// Subclassers should call the superclass implementation.
- (BOOL)allocateRenderResourcesAndReturnError:(NSError **)outError
{
    if (![super allocateRenderResourcesAndReturnError:outError])
	{
        return NO;
    }
    
    // Validate that the bus formats are compatible.
    // Allocate your resources.
    
    return YES;
}

// Deallocate resources allocated in allocateRenderResourcesAndReturnError:
// Subclassers should call the superclass implementation.
- (void) deallocateRenderResources
{
    // Deallocate your resources.
    [super deallocateRenderResources];
}

-(bool) canPerformInput
{
	return true;
}

#pragma mark - AUAudioUnit (AUAudioUnitImplementation)

// Block which subclassers must provide to implement rendering.
- (AUInternalRenderBlock)internalRenderBlock
{
    // Capture in locals to avoid ObjC member lookups. If "self" is captured in render, we're doing it wrong. See sample code.

		//	__block BufferedInputBus *input = &_inputBus;
	
    return ^AUAudioUnitStatus(AudioUnitRenderActionFlags *actionFlags,
							  const AudioTimeStamp *timestamp,
							  AVAudioFrameCount frameCount,
							  NSInteger outputBusNumber,
							  AudioBufferList *outputData,
							  const AURenderEvent *realtimeEventListHead,
							  AURenderPullInputBlock pullInputBlock)
	{
		AudioUnitRenderActionFlags pullFlags = 0;
		/*
		 Important:
		 If the caller passed non-null output pointers (outputData->mBuffers[x].mData), use those.
		 
		 If the caller passed null output buffer pointers, process in memory owned by the Audio Unit
		 and modify the (outputData->mBuffers[x].mData) pointers to point to this owned memory.
		 The Audio Unit is responsible for preserving the validity of this memory until the next call to render,
		 or deallocateRenderResources is called.
		 
		 If your algorithm cannot process in-place, you will need to preallocate an output buffer
		 and use it here.
		 
		 See the description of the canProcessInPlace property.
		 */
		
			// If passed null output buffer pointers, process in-place in the input buffer.
//		AudioBufferList *outAudioBufferList = outputData;
//		if (outAudioBufferList->mBuffers[0].mData == nullptr)
//		{
//			for (UInt32 i = 0; i < outAudioBufferList->mNumberBuffers; ++i)
//			{
//				outAudioBufferList->mBuffers[i].mData = inAudioBufferList->mBuffers[i].mData;
//			}
//		}
		
        // test sin wave render
		double j = 0;
		double cycleLength = 44100.0 / 440;
			//generate 440 hz tone and load into output bufferes
		for (int frame = 0; frame < frameCount; ++frame)
		{
			Float32 value = (Float32) sin(2 * M_PI * (j / cycleLength));
			outputData->mBuffers[0].mData = &value;

				// copy to right channel too
//			data = (Float32*)outputData->mBuffers[1].mData;
//			(data)[frame] = (Float32) sin(2 * M_PI * (j / cycleLength));
			
				//advance cout
			j += 1.0;
			if (j > cycleLength) j -= cycleLength;
		}
        return noErr;
    };
}

@end

