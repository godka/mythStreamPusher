#include <stdio.h>
#include "MythConfig.hh"
#include "mythCameraDecoder.hh"
#include "mythCamera.hh"
#include "mythDecoderPusher.hh"
int main(int argc, char* argv[])
{
	mythCamera* camera = mythCamera::CreateNew();
	mythCameraDecoder* decoder = mythCameraDecoder::CreateNew();
	if (decoder)
		decoder->start();

	mythDecoderPusher* pusher = mythDecoderPusher::CreateNew(decoder, argv[1], 5834, atoi(argv[2]));
	if (pusher)
		pusher->start();
	return 0;
}

