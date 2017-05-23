//
//  AUGraphPlayer.c
//  ConvolutionTest
//
//  Created by armen karamian on 5/21/17.
//  Copyright (c) 2017 armen karamian. All rights reserved.
//

#include "AUGraphPlayer.h"

void CreateAUGraph(AUGraphPlayer *player)
{
	CheckError(NewAUGraph(&player->graph), "New AUGraph Failed");

	//generate description that matches the output device
	AudioComponentDescription outputCD = {0};
	outputCD.componentType = kAudioUnitType_Output;
	outputCD.componentSubType = kAudioUnitSubType_DefaultOutput;
	outputCD.componentManufacturer = kAudioUnitManufacturer_Apple;

	//add a node with above description to the graph
	AUNode outputNode;
	CheckError(AUGraphAddNode(player->graph,
			&outputCD,
			&outputNode), "AUGraph Add Output node failed");

	AudioComponentDescription filePlayer1Desc = {0};
	filePlayer1Desc.componentType = kAudioUnitType_Generator;
	filePlayer1Desc.componentSubType = kAudioUnitSubType_AudioFilePlayer;
	filePlayer1Desc.componentManufacturer = kAudioUnitManufacturer_Apple;

	//adds a node with the above desc to the graph
	AUNode filePlayer1Node;
	CheckError(AUGraphAddNode(player->graph,
			&filePlayer1Desc,
			&filePlayer1Node), "AUGraph Add PLayer 1 Node Failed");

	AUNode filePlayer2Node;
	CheckError(AUGraphAddNode(player->graph,
			&filePlayer1Desc,
			&filePlayer2Node), "AUGraph Add PLayer 2 Node Failed");


	//open the nodes/units within the graph for editing
	CheckError(AUGraphOpen(player->graph), "AU Open Graph Failed!");

	//get the reference to the audiounit object
	CheckError(AUGraphNodeInfo(player->graph,
			filePlayer1Node,
			NULL,
			&player->fileAU_1), "AUGraph Node 1 info failed");

	CheckError(AUGraphNodeInfo(player->graph,
			filePlayer2Node,
			NULL,
			&player->fileAU_2), "AUGraph Node 1 info failed");


	CheckError(AUGraphConnectNodeInput(player->graph,
			filePlayer1Node,
			0,
			outputNode,
			0), "Connect player 1 node to output failed");

	CheckError(AUGraphConnectNodeInput(player->graph,
			filePlayer2Node,
			0,
			outputNode,
			0), "Connect player 2 node to output failed");


	//init graph
	CheckError(AUGraphInitialize(player->graph), "AUGraph init failed");
}

Float64 PrepareFileAU(AUGraphPlayer *player)
{
	//tell the file player to load the file we want to play
	CheckError(AudioUnitSetProperty(player->fileAU_1,
			kAudioUnitProperty_ScheduledFileIDs,
			kAudioUnitScope_Global,
			0,
			&player->inputFile_1,
			sizeof(player->inputFile_1)), "Audio Unit set property schedule file ID 1 failed");

	//tell the file player to load the file we want to play
//	CheckError(AudioUnitSetProperty(player->fileAU_2,
//			kAudioUnitProperty_ScheduledFileIDs,
//			kAudioUnitScope_Global,
//			0,
//			&player->inputFile_2,
//			sizeof(player->inputFile_2)), "Audio Unit set property schedule file ID 2 failed");

	UInt64 nPackets;
	UInt32 propSize = sizeof(nPackets);
	CheckError(AudioFileGetProperty(player->inputFile_1,
			kAudioFilePropertyAudioDataPacketCount,
			&propSize,
			&nPackets), "Audio file get property failed");

//	CheckError(AudioFileGetProperty(player->inputFile_2,
//			kAudioFilePropertyAudioDataPacketCount,
//			&propSize,
//			&nPackets), "Audio file get property failed");

	//tell the file player AU to play entire file
	ScheduledAudioFileRegion rgn_1;
	memset(&rgn_1.mTimeStamp, 0, sizeof(rgn_1.mTimeStamp));
	rgn_1.mTimeStamp.mFlags = kAudioTimeStampSampleTimeValid;
	rgn_1.mTimeStamp.mSampleTime = 0;
	rgn_1.mCompletionProc = NULL;
	rgn_1.mCompletionProcUserData = NULL;
	rgn_1.mAudioFile = player->inputFile_1;
	rgn_1.mLoopCount = 1;
	rgn_1.mStartFrame = 0;
	rgn_1.mFramesToPlay = nPackets * player->inputFormat.mFramesPerPacket;

	CheckError(AudioUnitSetProperty(player->fileAU_1,
			kAudioUnitProperty_ScheduledFileRegion,
			kAudioUnitScope_Global,
			0,
			&rgn_1,
			sizeof(rgn_1)), "Audio unit set property scheduled file region failed");

//	ScheduledAudioFileRegion rgn_2;
//	memset(&rgn_2.mTimeStamp, 0, sizeof(rgn_2.mTimeStamp));
//	rgn_2.mTimeStamp.mFlags = kAudioTimeStampSampleTimeValid;
//	rgn_2.mTimeStamp.mSampleTime = 0;
//	rgn_2.mCompletionProc = NULL;
//	rgn_2.mCompletionProcUserData = NULL;
//	rgn_2.mAudioFile = player->inputFile_2;
//	rgn_2.mLoopCount = 1;
//	rgn_2.mStartFrame = 0;
//	rgn_2.mFramesToPlay = nPackets * player->inputFormat.mFramesPerPacket;
//
//	CheckError(AudioUnitSetProperty(player->fileAU_2,
//			kAudioUnitProperty_ScheduledFileRegion,
//			kAudioUnitScope_Global,
//			0,
//			&rgn_2,
//			sizeof(rgn_2)), "Audio unit set property scheduled file region failed");


	AudioTimeStamp startTime;
	memset(&startTime, 0, sizeof(startTime));
	startTime.mFlags = kAudioTimeStampSampleTimeValid;
	startTime.mSampleTime = -1;
	CheckError(AudioUnitSetProperty(player->fileAU_1,
			kAudioUnitProperty_ScheduleStartTimeStamp,
			kAudioUnitScope_Global,
			0,
			&startTime,
			sizeof(startTime)), "Schedule start tiem stamp failed");

//	CheckError(AudioUnitSetProperty(player->fileAU_2,
//			kAudioUnitProperty_ScheduleStartTimeStamp,
//			kAudioUnitScope_Global,
//			0,
//			&startTime,
//			sizeof(startTime)), "Schedule start tiem stamp failed");
//

	return (nPackets * player->inputFormat.mFramesPerPacket) / player->inputFormat.mSampleRate;


}
