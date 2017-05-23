//
//  ConvolutionUnitAudioUnit.h
//  ConvolutionUnit
//
//  Created by armen karamian on 5/21/17.
//  Copyright © 2017 armen karamian. All rights reserved.
//

#import <AudioToolbox/AudioToolbox.h>


// Define parameter addresses.
extern const AudioUnitParameterID myParam1;

@interface ConvolutionUnitAudioUnit : AUAudioUnit
- (instancetype) initWithComponentDescription:(AudioComponentDescription)componentDescription
									 options:(AudioComponentInstantiationOptions)options
									   error:(NSError **)outError;

- (bool) canPerformInput;
@end
