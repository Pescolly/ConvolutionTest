#include <stdio.h>
#include <CoreFoundation/CoreFoundation.h>
#include <AudioToolbox/AudioToolbox.h>
#include "CheckErrors.h"
#include "Converter.h"
#include "AUGraphPlayer.h"


#pragma mark test files
#define TEST_FILE_1 CFSTR("/Users/armen/Documents/440hz.aiff")
#define TEST_FILE_2 CFSTR("/Users/armen/Documents/880hz.aiff")




#pragma mark main
int main(int argc, char *argv[])
{
	//TODO implement conversion, V1 is using constant settings defined above
//	AudioConverterSettings audioFile1ConverterSettings = {0};
//	AudioConverterSettings audioFile2ConverterSettings = {0};
	
	printf("this is the c main");
	
	AUGraphPlayer player_1 = {0};

	CFURLRef file1URL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
			TEST_FILE_1, kCFURLPOSIXPathStyle, false);
	CFURLRef file2URL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
			TEST_FILE_2, kCFURLPOSIXPathStyle, false);

	//open input audio files
	CheckError(AudioFileOpenURL(file1URL,
			kAudioFileReadPermission, 0,
			&player_1.inputFile_1), "AudioFileOpenURL Failed");

	CheckError(AudioFileOpenURL(file2URL,
			kAudioFileReadPermission, 0,
			&player_1.inputFile_2), "AudioFileOpenURL Failed");


	//get audio data format from files
	UInt32 propSize1 = sizeof(player_1.inputFormat);
	UInt32 propSize2 = sizeof(player_1.inputFormat);

	CheckError(AudioFileGetProperty(player_1.inputFile_1,
			kAudioFilePropertyDataFormat,
			&propSize1,
			&player_1.inputFormat), "Could not get format for audio file 1");

	CheckError(AudioFileGetProperty(player_1.inputFile_2,
			kAudioFilePropertyDataFormat,
			&propSize2,
			&player_1.inputFormat), "Could not get format for audio file 2");


	//build a fileplayer->speakers graph
	CreateAUGraph(&player_1);

	//start playing
	Float64 fileDuration = PrepareFileAU(&player_1);
	CheckError(AUGraphStart(player_1.graph), "AUGraph start fail");

	//wait for files to finish
	usleep((int)(fileDuration * 1000.0 * 1000.0));

	//cleanup
	AudioFileClose(player_1.inputFile_1);
	AudioFileClose(player_1.inputFile_2);
	return 0;
}
