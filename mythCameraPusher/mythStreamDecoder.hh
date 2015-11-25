#pragma once
#include "MythConfig.hh"
#include "mythVirtualDecoder.hh"
#include <string>
#include "PEOPLE.hh"
using namespace std;
#define BUFF_COUNT 1024*1024	
class mythStreamDecoder :
	public mythVirtualDecoder
{
public:
	static mythStreamDecoder* CreateNew(char* ip, int port, int CameraID);
	static mythStreamDecoder* CreateNew(char* ip, int CameraID);
	void start();
	void stop();
	~mythStreamDecoder(void);
	static Uint32 TimerCallbackStatic(Uint32 interval, void *param);
protected:
	Uint32 TimerCallback(Uint32 interval);
	int decodethread();
	static int decodethreadstatic(void* data);
	mythStreamDecoder(char* ip, int port, int CameraID);
	int GetFrameAsync(PacketQueue* packet);
	int StartAsync();
	int GetFrameBlock(PacketQueue* packet);
#ifdef MYTHPEOLE
	PEOPLE* msocket;
#else
	PEOPLE *msocket;
#endif
	SDL_Thread* startthread;
private:
	string m_ip;
	int m_port;
	int m_cameraid;
	char* buf;
};

