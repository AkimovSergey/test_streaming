// test_unified_streaming.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "mpeg_ts_packet.h"
#include "stream_reader.h"
#include "mpeg_packet_processor.h"

using namespace std;
using namespace MPEGParser;

int main(int argc, char* argv[])
{
 	if (argc < 2)
	{
		std::cout << "File path as first argument required";
        return 1;
	}
	string file_path = argv[1];

	ifstream fs;
	try
	{
		fs.open(file_path.c_str(), ifstream::in | ifstream::binary);
        if(!fs.is_open())
            throw "Cannot open file" + file_path;
        TSReader<MPEG_TSPacket, MPEG_PacketProcessor<MPEG_TSPacket>> reader;
        reader.Process(fs);
	}
    catch (string & s)
	{
        cout << s;
        return 1;
	}
    catch (system_error & e)
    {
        cout << e.what();
        return 1;
    }


	return 0;
}



