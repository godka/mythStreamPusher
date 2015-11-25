#include <stdio.h>
#include "MythConfig.hh"
#include "mythDecoderPusher.hh"
#include "mythDecoderFactory.hh"
int main(int argc, char* argv[])
{
	if (argc <= 2){
		puts("useage: cyclopsPusher stream1:// stream2://");
		exit(0);
	}
	mythVirtualDecoder* decoder = mythDecoderFactory::CreateNew(argv[1]);
	if (decoder){
		decoder->start();
		mythDecoderPusher* pusher = mythDecoderPusher::CreateNew(decoder, argv[2]);
		if (pusher)
			pusher->start();
	}
	return 0;
}

