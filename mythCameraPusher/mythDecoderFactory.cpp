#include "mythDecoderFactory.hh"
/*
	hlsclient -i	rtsp://username:password@ip:port/args
 			or		stream://ip:port/cameraid
					outputpath
*/
mythVirtualDecoder* mythDecoderFactory::CreateNew(const char* url)
{
	string strurl = url;
	vector<string> spstr;
	split(url, ":\/\/", spstr);
	if (spstr.size() > 1){
		if (spstr[0] == "rtsp"){
			string username = "", password = "";
			string rtsplink = "";
			//username:password@ip:port/args
			cout << "RTSP Stream:" << endl;
			vector<string> hasusername;
			split(spstr[1], "@", hasusername);
			if (hasusername.size() > 1){
				// has username and password
				vector<string> spusernamepassword;
				split(hasusername[0], ":", spusernamepassword);
				if (spusernamepassword.size() > 1){
					username = spusernamepassword[0];
					password = spusernamepassword[1];
				}
				else{
					username = spusernamepassword[0];
					password = "";
				}
				cout << "username:" << username << endl;
				cout << "password:" << password << endl;
				rtsplink = "rtsp://" + hasusername[1];
				cout << "rtsplink:" << rtsplink << endl;
			}
			else{
				rtsplink = url;
				cout << "rtsplink:" << rtsplink << endl;
			}
			if (rtsplink != ""){
				return NULL;
				//return mythLive555Decoder::CreateNew((char*) rtsplink.c_str(), (char*) username.c_str(), (char*) password.c_str());
			}
			else{
				return NULL;
			}
		}
		else if (spstr[0] == "stream"){
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
					return mythStreamDecoder::CreateNew((char*)ip.c_str(), port, cameraid);
				}
				else{
					return NULL;
				}
			}
			else{
				return NULL;
			}
		}
		else if (spstr[0] == "camera"){
			mythCamera* camera = mythCamera::CreateNew();
			return mythCameraDecoder::CreateNew();
		}
		else{
			return NULL;
		}
	}
	else{
		return NULL;
	}
}

mythDecoderFactory::mythDecoderFactory()
{
}
void mythDecoderFactory::split(const std::string& s, const std::string& c, std::vector<std::string>& v)
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
/*
void mythDecoderFactory::split(const string& src, const string& separator, vector<string>& dest)
{
	string str = src;
	string substring;
	string::size_type start = 0, index;

	do
	{
		index = str.find_first_of(separator, start);
		if (index != string::npos)
		{
			substring = str.substr(start, index - start);
			dest.push_back(substring);
			start = str.find_first_not_of(separator, index);
			if (start == string::npos) return;
		}
	} while (index != string::npos);

	//the last token
	substring = str.substr(start);
	dest.push_back(substring);
}
*/
mythDecoderFactory::~mythDecoderFactory()
{
}
