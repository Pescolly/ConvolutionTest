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

	//TODO Player 2 goes here.......
//
//
//
//
//
	//open the nodes/units within the graph for editing
	CheckError(AUGraphOpen(player->graph), "AU Open Graph Failed!");

	//get the reference to the audiounit object
	CheckError(AUGraphNodeInfo(player->graph,
			filePlayer1Node,
			NULL,
			&player->fileAU), "AUGraph Node info failed");

	/// todo player 2 node refence 


	CheckError(AUGraphConnectNodeInput(player->graph,
			filePlayer1Node,
			0,
			outputNode,
			0), "Connect player 1 node to output failed");

	//TODO player 2 conenct


}
