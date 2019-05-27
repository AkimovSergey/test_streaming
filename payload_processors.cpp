#include "payload_processors.h"
#include "pch.h"

namespace MPEGParser
{
	namespace PayloadProcessors
	{

		map < PAYLOAD_TYPE, function<shared_ptr<BaseProcessor>()>> PayloadProcessorsFactory::m_registered_processors;
		bool AudioProcessor::is_registered = PayloadProcessorsFactory::Register(PAYLOAD_TYPE::AUDIO_TYPE, BaseProcessor::Create<AudioProcessor>);
		bool VideoProcessor::is_registered = PayloadProcessorsFactory::Register(PAYLOAD_TYPE::VIDEO_TYPE, BaseProcessor::Create<VideoProcessor>);

		/* classic implementation, no thread safety */
		PayloadProcessorsFactory * PayloadProcessorsFactory::GetInstance()
		{
			/* dont need to worry about memory - it will be freed at end of program execution*/
			static PayloadProcessorsFactory * m_instance;
			if (m_instance == 0)
			{
				m_instance = new PayloadProcessorsFactory();
			}

			return m_instance;
		}

		shared_ptr<BaseProcessor> PayloadProcessorsFactory::GetProcessor(PAYLOAD_TYPE type) const
		{
			if (m_registered_processors.end() == m_registered_processors.find(type))
				throw ("There is no processor for type: " + std::to_string((int)type));
			return m_registered_processors[type]();
		}

		bool PayloadProcessorsFactory::Register(PAYLOAD_TYPE type, function<shared_ptr<BaseProcessor>()> func)
		{
			m_registered_processors[type] = func;
			return true;
		}

		
	}
}
