/********************************************************************
Created by MythKAst
©2013 MythKAst Some rights reserved.


You can build it with vc2010,gcc.
Anybody who gets this source code is able to modify or rebuild it anyway,
but please keep this section when you want to spread a new version.
It's strongly not recommended to change the original copyright. Adding new version
information, however, is Allowed. Thanks.
For the latest version, please be sure to check my website:
Http://code.google.com/mythkast


你可以用vc2010,gcc编译这些代码
任何得到此代码的人都可以修改或者重新编译这段代码，但是请保留这段文字。
请不要修改原始版权，但是可以添加新的版本信息。
最新版本请留意：Http://code.google.com/mythkast
B
MythKAst(asdic182@sina.com), in 2013 June.
*********************************************************************/
#include "mythStreamDecoder.hh"

mythStreamDecoder::mythStreamDecoder(char* ip, int port, int CameraID)
	:mythVirtualDecoder(){
	flag = 0;
	m_ip = ip;
	m_port = port;
	m_cameraid = CameraID;
	startthread = NULL;
	msocket = NULL;
	buf = new char[BUFF_COUNT];
}
mythStreamDecoder* mythStreamDecoder::CreateNew(char* ip, int CameraID){
	return new mythStreamDecoder(ip, 5834, CameraID);
}
mythStreamDecoder* mythStreamDecoder::CreateNew(char* ip, int port, int CameraID){
	return new mythStreamDecoder(ip, port, CameraID);
}
void mythStreamDecoder::start(){
	startthread = SDL_CreateThread(decodethreadstatic,"decode",this);
}
void mythStreamDecoder::stop(){
	//this->startthread = SDL_CreateThread(decodethreadstatic,"decode",this);
	flag = 1;
	if (startthread)
		SDL_WaitThread(startthread,NULL);
	return;
}
int mythStreamDecoder::decodethreadstatic(void* data){
	mythStreamDecoder* m_decoder = (mythStreamDecoder*) data;
	return m_decoder->decodethread();
}
int mythStreamDecoder::decodethread(){
	msocket = PEOPLE::CreateNew(m_ip.c_str(), m_port);
	if (msocket != NULL){
		char tmpsendstr[100];
		SDL_snprintf(tmpsendstr, 100, "GET /CameraID=%d&Type=zyh264 HTTP/1.0\r\n\r\n", m_cameraid);
		msocket->socket_SendStr(tmpsendstr);
		SDL_Delay(100);
		while (flag == 0){
			//printf("ready to receive buff\n");
			int rc = msocket->socket_ReceiveDataLn2(buf, BUFF_COUNT, "Content_Length: ");
			if (rc > 0) {
				put((unsigned char*) buf, rc);
			}else{
				printf("start to reconnect\n");
				//msocket->Reconnect(m_ip,m_port);
				delete msocket;
				SDL_Delay(1000);
				msocket = PEOPLE::CreateNew(m_ip.c_str(), m_port);
				msocket->socket_SendStr(tmpsendstr);
				printf("reconnecting\n");
			}
			//SDL_PollEvent(NULL);
			SDL_Delay(1);
		}
		msocket->socket_CloseSocket();
	}
	delete [] buf;
	delete msocket;
	msocket = NULL;
	//printf("ziya decoder delete! : %d\n", m_cameraid);
	return 0;
}

int mythStreamDecoder::GetFrameAsync(PacketQueue* packet){
	int rc = msocket->socket_ReceiveDataLn2(buf, BUFF_COUNT, "Content_Length: ");
	if (rc > 4) {
		if (packet){
			packet->h264Packet = (unsigned char*) buf;
			packet->h264PacketLength = rc;
			return 0;
		}
		else{
			return 1;
		}
	}
	else{
		return 1;
	}
}

int mythStreamDecoder::GetFrameBlock(PacketQueue* packet){
	puts("stream!");
	for (;;){
		if (GetFrameAsync(packet) == 0)break;	
		SDL_Delay(1);
	}
	return 0;
}
mythStreamDecoder::~mythStreamDecoder(void){
	if (msocket){
		delete msocket;
	}
}

int mythStreamDecoder::StartAsync()
{
	msocket = PEOPLE::CreateNew(m_ip.c_str(), m_port);
	if (msocket){
		char tmpsendstr[100];
		SDL_snprintf(tmpsendstr, 100, "GET /CameraID=%d&Type=zyh264 HTTP/1.0\r\n\r\n", m_cameraid);
		msocket->socket_SendStr(tmpsendstr);
	}
	return 0;
}

