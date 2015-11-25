#pragma once
#include "MythConfig.hh"
#include "mythVirtualDecoder.hh"
#include "PEOPLE.hh"
#include "mythBaseClient.hh"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class mythDecoderPusher
{
public:
	static void split(const std::string& s, const std::string& c, std::vector<std::string>& v)
	{
		std::string::size_type pos1, pos2;
		pos2 = s.find(c);
		pos1 = 0;
		while (std::string::npos != pos2)
		{
			v.push_back(s.substr(pos1, pos2 - pos1));

			pos1 = pos2 + c.size();
			pos2 = s.find(c, pos1);
		}
		if (pos1 != s.length())
			v.push_back(s.substr(pos1));
	}
	static mythDecoderPusher* CreateNew(mythVirtualDecoder* decoder, const char* url){
		string strurl = url;
		vector<string> spstr;
		split(url, ":\/\/", spstr);
		if (spstr.size() > 1){
			if (spstr[0] == "stream"){
				//ip:port/cameraid
				string ip = "";
				int port = 5834, cameraid = -1;
				cout << "Stream:" << endl;
				vector<string> spid;
				split(spstr[1], "\/", spid);
				if (spid.size() > 1){
					cameraid = atoi(spid[1].c_str());
					vector<string> spip;
					split(spid[0], ":", spip);
					if (spip.size() > 1){
						ip = spip[0];
						port = atoi(spip[1].c_str());
					}
					else{
						ip = spip[0];
					}
					cout << "ip:" << ip << endl;
					cout << "port:" << port << endl;
					cout << "cameraid:" << cameraid << endl;
					if (cameraid > 0){
						return CreateNew(decoder,(const char*) ip.c_str(), port, cameraid);
					}
					else{
						return NULL;
					}
				}
				else{
					return NULL;
				}
			}
			else{
				return NULL;
			}
		}
		else{
			return NULL;
		}
	}
	static mythDecoderPusher* CreateNew(mythVirtualDecoder* decoder, const char* ip, int port, int cameraid){
		return new mythDecoderPusher(decoder,ip, port, cameraid);
	}
	mythDecoderPusher(mythVirtualDecoder* decoder, const char* ip, int port, int cameraid);
	~mythDecoderPusher();
	void start();
	void stop();
private:
	mythVirtualDecoder* mdecoder;
	const char* mip;
	int mport;
	int mcameraid;
	PEOPLE* people;
	mythBaseClient* baseclient;
};

