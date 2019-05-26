#pragma once

#include "payload_processors.h"


namespace MPEGParser
{
	using namespace PayloadProcessors;

	template <typename packet>
	class MPEG_PacketProcessor
	{
	public:
		void ProcessPacket(packet & packet);
	};

	template <typename packet>
	void MPEG_PacketProcessor<packet>::ProcessPacket(packet & pack)
	{
		auto processor = PayloadProcessorsFactory::GetInstance()->GetProcessor(pack.GetPayloadType());
		if (!processor)
			throw exception("Unknown packet type");
		processor->ProcessData(pack.GetPayloadData());
	}

}
