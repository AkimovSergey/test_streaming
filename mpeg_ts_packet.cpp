#include "mpeg_ts_packet.h"


namespace MPEGParser
{

	void MPEG_TSPacket::Validate()
	{
        //TODO: add some checking
	}

    void MPEG_TSPacket::Read(std::ifstream & fs)
	{
		fs.read((char*)m_data, MPEG_PACKAGE_SIZE);
	}

	size_t MPEG_TSPacket::AdaptationFieldLength() const
	{
		// check if there is adaptation field
		if ((m_data[3] & ADAPTATION_FIELD_MASK)  >= 0x20)
			return m_data[4] + AF_FIELD_LENGTH;
		return 0;
	}

    size_t MPEG_TSPacket::PesHeaderLength(size_t pes_offset) const
    {
        return PES_OPT_HEADER_LENGTH;
        /* Should work but doesn't for first audio packet
        investigation required */
        return PES_LENGTH_OFFSET + m_data[pes_offset + PES_LENGTH_OFFSET];
    }

    const std::pair<size_t, const uint8_t*> MPEG_TSPacket::GetPayloadData() const
	{
		if (!HasPayload())
			return { 0, nullptr };
		auto offset = MPEG_HEADER_SIZE + AdaptationFieldLength();
        if (PayloadStart())
            offset += PesHeaderLength(offset);

		return {MPEG_PACKAGE_SIZE - offset, &m_data[offset]};
	}

    int MPEG_TSPacket::GetPayloadType() const
	{
        return ((m_data[1] & 0x1f) << 8) + m_data[2];
	}

	bool MPEG_TSPacket::HasPayload() const
	{
		// check AF bit for payload
		return ((m_data[3] & ADAPTATION_FIELD_MASK) & 0x10);
	}
	bool MPEG_TSPacket::PayloadStart() const
	{
		return m_data[1] & PAYLOAD_START_MASK;
	}

}
