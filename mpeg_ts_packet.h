#pragma once

#include "pch.h"

using namespace std;

namespace MPEGParser
{

	const static char SYNCBYTE = 0x47;
	const static int MPEG_PACKAGE_SIZE = 188;
	const static int ADAPTATION_FIELD_MASK = 0x30;
	const static int PAYLOAD_START_MASK = 0x40;
	const static int MPEG_HEADER_SIZE = 0x3;
	const static int PES_HEADER_SIZE = 0x6;

	enum class PAYLOAD_TYPE
	{
		AUDIO_TYPE = 34,
		VIDEO_TYPE = 33
		/* .... etc */
	};

	class MPEG_TSPacket
	{

	private:
		char      m_data[MPEG_PACKAGE_SIZE];
	public:
		/*!
		\fn void Validate
		\brief Validate package consistency
		\ implement later check if fields have valid values
		*/
		void Validate();
		void Read(ifstream & fs);
		const const pair<size_t, const char*> GetPayloadData() const;
		PAYLOAD_TYPE GetPayloadType() const;
		size_t AdaptationFieldLength() const;
		bool HasPayload() const;
		bool PayloadStart() const;
	};

};

