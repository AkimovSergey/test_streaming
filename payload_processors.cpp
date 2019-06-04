#include "payload_processors.h"
#include "pch.h"

namespace MPEGParser
{

using namespace std;

	namespace PayloadProcessors
	{

        map < int , function<shared_ptr<BaseProcessor>()>> PayloadProcessorsFactory::m_registered_processors;
        bool AudioProcessor::is_registered = PayloadProcessorsFactory::Register(AudioProcessor::m_type, BaseProcessor::Create<AudioProcessor>);
        bool VideoProcessor::is_registered = PayloadProcessorsFactory::Register(VideoProcessor::m_type, BaseProcessor::Create<VideoProcessor>);

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

        shared_ptr<BaseProcessor> PayloadProcessorsFactory::GetProcessor(int type) const
		{
			if (m_registered_processors.end() == m_registered_processors.find(type))
				throw runtime_error("There is no processor for type: " + std::to_string((int)type));
			return m_registered_processors[type]();
		}

        bool PayloadProcessorsFactory::Register(int type, function<shared_ptr<BaseProcessor>()> func)
		{
			m_registered_processors[type] = func;
			return true;
		}

		
	}
}
