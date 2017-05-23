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
	AUGraph 					graph;
	AudioFileID 				inputFile_1;
	AudioUnit 					fileAU_1;
	AudioFileID 				inputFile_2;
	AudioUnit 					fileAU_2;
} AUGraphPlayer;

typedef struct AUGraphNodes
{
	AUNode outputNode;
	AUNode filePlayer1Node;
	AUNode filePlayer2Node;
};


void CreateAUGraph(AUGraphPlayer *player);
Float64 PrepareFileAU(AUGraphPlayer *player);
#endif /* AUGraphPlayer_h */
