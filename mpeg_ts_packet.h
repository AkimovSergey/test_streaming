#pragma once

#include "pch.h"

using namespace std;

namespace MPEGParser
{

	const static uint8_t SYNCBYTE =          0x47;
	const static int MPEG_PACKAGE_SIZE =     0xBC;
	const static int ADAPTATION_FIELD_MASK = 0x30;
	const static int PAYLOAD_START_MASK =    0x40;
	const static int MPEG_HEADER_SIZE =      0x04;
	const static int PES_LENGTH_OFFSET =     0x08;
    const static int AF_FIELD_LENGTH =       0x01;

	enum class PAYLOAD_TYPE
	{
		AUDIO_TYPE = 34,
		VIDEO_TYPE = 33
		/* .... etc */
	};

	class MPEG_TSPacket
	{

	private:
		uint8_t      m_data[MPEG_PACKAGE_SIZE];
	public:
		/*!
		\fn void Validate
		\brief Validate package consistency
		\ implement later check if fields have valid values
		*/
		void Validate();
		void Read(ifstream & fs);
		const pair<size_t, const uint8_t*> GetPayloadData() const;
		PAYLOAD_TYPE GetPayloadType() const;
		size_t AdaptationFieldLength() const;
        size_t PesHeaderLength(size_t pes_offset) const;
		bool HasPayload() const;
		bool PayloadStart() const;
	};

};

