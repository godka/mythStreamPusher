#pragma once
#include "mythCamera.hh"
#include "mythVirtualDecoder.hh"
#include "mythStreamDecoder.hh"
#include "mythCameraDecoder.hh"
//#include "mythLive555Decoder.hh"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class mythDecoderFactory
{
public:
	static mythVirtualDecoder* CreateNew(const char* url);
	static void split(const string& src, const string& separator, vector<string>& dest);
protected:
	mythDecoderFactory();
	~mythDecoderFactory();
};

