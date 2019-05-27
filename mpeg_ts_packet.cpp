#include "mpeg_ts_packet.h"


namespace MPEGParser
{

	void MPEG_TSPacket::Validate()
	{

	}

	void MPEG_TSPacket::Read(ifstream & fs)
	{
		fs.read(m_data, MPEG_PACKAGE_SIZE);
	}

	size_t MPEG_TSPacket::AdaptationFieldLength() const
	{
		// check if there is adaptation field
		if ((m_data[3] & ADAPTATION_FIELD_MASK)  >= 0x20)
			return m_data[3];
		return 0;
	}

	const pair<size_t, const char*> MPEG_TSPacket::GetPayloadData() const
	{
		if (!HasPayload())
			return { 0, nullptr };
		auto offset = MPEG_HEADER_SIZE +  1 + AdaptationFieldLength();
		if (PayloadStart())
			offset += PES_HEADER_SIZE;
		return {MPEG_PACKAGE_SIZE - offset, &m_data[offset]};
	}

	PAYLOAD_TYPE MPEG_TSPacket::GetPayloadType() const
	{
		return (PAYLOAD_TYPE)(((m_data[1] & 0x1f) << 8) + m_data[2]);
	}

	bool MPEG_TSPacket::HasPayload() const
	{
		// check if bit for payload
		return ((m_data[3] & ADAPTATION_FIELD_MASK) & 0x10);
	}
	bool MPEG_TSPacket::PayloadStart() const
	{
		return m_data[1] & PAYLOAD_START_MASK;
	}

}
