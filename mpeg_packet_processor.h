#pragma once

#include "payload_processors.h"


namespace MPEGParser
{
	using namespace PayloadProcessors;

	template <typename packet>
	class MPEG_PacketProcessor
	{
        std::map<int, std::shared_ptr<BaseProcessor>> m_processors;
	public:
		void ProcessPacket(packet & pack);
	};

	template <typename packet>
	void MPEG_PacketProcessor<packet>::ProcessPacket(packet & pack)
	{
        std::shared_ptr<BaseProcessor> processor;
		if (m_processors.end() != m_processors.find(pack.GetPayloadType()))
			processor = m_processors[pack.GetPayloadType()];
		else
		{
			processor = PayloadProcessorsFactory::GetInstance()->GetProcessor(pack.GetPayloadType());
			m_processors[pack.GetPayloadType()] = processor;
		}
			
		if (!processor)
            throw std::runtime_error("Unknown packet type");
		processor->ProcessData(pack.GetPayloadData());
	}

}
