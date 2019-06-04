#pragma once

#include "pch.h"
#include "mpeg_ts_packet.h"


namespace MPEGParser
{
	/*!
	\fn bool FindSyncByte(ifstream & fs)
	\brief Static helper function: search first entrance of synchrobyte for MPEG-TS package
	for a case if something brocken in the stream.
	\param [in] file input stream
	\param [out] return true if synchrobyte found or false if end of file reached but synchrobyte not found
	*/
    static bool FindSyncByte(const std::ifstream & fs);


	template<typename container, typename processor>
    class TSReader final
	{
        // make it noncopyable
        TSReader(const TSReader&) = delete;
        TSReader& operator=(const TSReader&) = delete;
	public:
		TSReader() = default;
        void Process(std::ifstream & fs);
	};

	template<typename container, typename processor>
    void TSReader<container, processor>::Process(std::ifstream & fs)
	{
		processor proc;
		char c = 0;
		for (;;)
		{
            // looking for start of TS packet
			while (fs.read(&c, 1) && c != SYNCBYTE);

			if (c != SYNCBYTE || fs.peek() == EOF)
			{
                std::cout << "end of file" << std::endl;
				return;
			}
            std::streampos oldpos = fs.tellg();
            // we found syncbyte but need full package for parsing  ... so lets move one byte back
			fs.putback(c);
			container packet;
			try
			{
				packet.Read(fs);
				packet.Validate();
				proc.ProcessPacket(packet);
			}
            catch (std::exception & e)
			{
                std::cout << e.what() << std::endl;
                // step back to continue looking syncbyte
                fs.seekg(oldpos);
			}
		}
	}
}

