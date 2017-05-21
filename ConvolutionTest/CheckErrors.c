#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "CheckErrors.h"
#include <CoreFoundation/CoreFoundation.h>

void CheckError(OSStatus error, const char *operation)
{
	if (error == noErr) return;

	char errorString[20];
	*(UInt32 *) (errorString + 1) = CFSwapInt32HostToBig(error);
	if (isprint(errorString[1]) && isprint(errorString[2]) && isprint(errorString[3]) && isprint(errorString[4]))
	{
		errorString[0] = errorString[5] = '\'';
		errorString[6] = '\0';
	} else
	{
		sprintf(errorString, "%d", (int) error);
	}
	fprintf(stderr, "Error: %s (%s)\n", operation, errorString);

	exit(1);
}
