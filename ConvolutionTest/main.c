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

	AUGraphPlayer player_1 = {0};
	AUGraphPlayer player_2 = {0};

	CFURLRef file1URL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
			TEST_FILE_1, kCFURLPOSIXPathStyle, false);
	CFURLRef file2URL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
			TEST_FILE_2, kCFURLPOSIXPathStyle, false);

	AudioFileID fileID1;
	AudioFileID fileID2;

	//open input audio files
	CheckError(AudioFileOpenURL(file1URL,
			kAudioFileReadPermission, 0,
			fileID1), "AudioFileOpenURL Failed");

	CheckError(AudioFileOpenURL(file2URL,
			kAudioFileReadPermission, 0,
			fileID2), "AudioFileOpenURL Failed");


	//get audio data format from files
	UInt32 propSize1 = sizeof(player_1.inputFormat);
	UInt32 propSize2 = sizeof(player_2.inputFormat);

	CheckError(AudioFileGetProperty(player_1.inputFile,
			kAudioFilePropertyDataFormat,
			&propSize1,
			&player_1.inputFormat), "Could not get format for audio file 1");

	CheckError(AudioFileGetProperty(player_2.inputFile,
			kAudioFilePropertyDataFormat,
			&propSize2,
			&player_2.inputFormat), "Could not get format for audio file 2");


	//build a fileplayer->speakers graph

	//start playing

	//wait for files to finish

	//cleanup
	AudioFileClose(fileID1);
	AudioFileClose(fileID2);
	return 0;
}