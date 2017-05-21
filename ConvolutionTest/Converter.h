#include  <MacTypes.h>
#include <AudioToolbox/AudioToolbox.h>

#pragma mark user data struct

typedef struct AudioConverterSettings
{
	AudioStreamBasicDescription inputFormat;
	AudioStreamBasicDescription outputFormat;
	AudioFileID 				inputFile;
	UInt64						inputFilePacketIndex;
	UInt64 						inputFilePacketCount;
	UInt32 						inputFilePacketMaxSize;
	AudioStreamPacketDescription *inputFilePacketDesc;
} AudioConverterSettings;

OSStatus AudioConverterCallback(AudioConverterRef inAudioConverter,
		UInt32 *ioDataPacketCount,
		AudioBufferList *ioData,
		AudioStreamPacketDescription **outDataPacketDesc);