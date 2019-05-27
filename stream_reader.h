#pragma once

#include "pch.h"
#include "mpeg_ts_packet.h"

using namespace std;

namespace MPEGParser
{
	/*!
	\fn bool FindSyncByte(ifstream & fs)
	\brief Static helper function: search first entrance of synchrobyte for MPEG-TS package
	for a case if something brocken in the stream.
	\param [in] file input stream
	\param [out] return true if synchrobyte found or false if end of file reached but synchrobyte not found
	*/
	static bool FindSyncByte(const ifstream && fs);

	template<typename container, typename processor>
	class TSReader
	{
	public:
		TSReader() = default;
		void Process(ifstream && fs);
	};

	template<typename container, typename processor>
	void TSReader<container, processor>::Process(ifstream && fs)
	{
		processor proc;
		char c = 0;
		for (;;)
		{
			while (fs.read(&c, 1) && c != SYNCBYTE);
			if (c != SYNCBYTE || fs.peek() == EOF)
			{
				std::cout << "end of file" << endl;
				return;
			}
			fs.putback(c);
			container packet;
			try
			{
				packet.Read(fs);
				packet.Validate();
				proc.ProcessPacket(packet);
			}
			catch (exception & e)
			{
				std::cout << e.what() << endl;
			}

		}

	}
}

