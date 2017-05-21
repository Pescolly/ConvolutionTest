//
//  AUGraphPlayer.h
//  ConvolutionTest
//
//  Created by armen karamian on 5/21/17.
//  Copyright (c) 2017 armen karamian. All rights reserved.
//

#ifndef AUGraphPlayer_h
#define AUGraphPlayer_h

#include <stdio.h>
#include <AudioToolbox/AudioToolbox.h>
#include "CheckErrors.h"
#include "Constants.h"

typedef struct AUGraphPlayer
{
	AudioStreamBasicDescription inputFormat;
	AudioFileID 				inputFile;
	AUGraph 					graph;
	AudioUnit 					fileAU;
} AUGraphPlayer;

void CreateAUGraph(AUGraphPlayer *player);

#endif /* AUGraphPlayer_h */
