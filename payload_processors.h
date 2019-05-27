#pragma once
#include "pch.h"
#include "mpeg_ts_packet.h"

using namespace std;

namespace MPEGParser
{
	namespace PayloadProcessors
	{
		class BaseProcessor
		{
            // make it noncopyable
            BaseProcessor(const BaseProcessor&) = delete;
            BaseProcessor& operator=(const BaseProcessor&) = delete;
		public:
            BaseProcessor() = default;
			virtual void ProcessData(const pair<size_t, const uint8_t*>) = 0;
			template<class T>
			static shared_ptr<BaseProcessor> Create()
			{
				return make_shared<T>();
			}
		};

		/* Classic curiously recurring template pattern implementation
			just to avoid code duplication*/
		template<typename T>
		class DataDumper :public BaseProcessor
		{
		protected:
			string m_extension;
			FILE * m_file;
			virtual string GetExtension() = 0;

			void DumpData(const pair<size_t, const uint8_t * > data)
			{
				string output = "output" + GetExtension();
                if (!m_file)
                {
                    try
                    { 
                        m_file = fopen(output.c_str(), "wb");
                    }
                    catch (...)
                    {
                        throw runtime_error("Cannot create output file");
                    }
                }
					
				fwrite(data.second, data.first, 1, m_file);
			}

		public:
			DataDumper() :m_file(nullptr) {}
			~DataDumper()
			{
				if (m_file)
					fclose(m_file);
			}
		};

		class AudioProcessor :public DataDumper<AudioProcessor>
		{
		public:
			void ProcessData(const pair<size_t, const uint8_t*> data) { DumpData(data); };
			string GetExtension() { return ".aac"; }
			static bool is_registered;
		};



		class VideoProcessor :public DataDumper<VideoProcessor>
		{
		public:
			void ProcessData(const pair<size_t, const uint8_t*> data) { DumpData(data); };
			string GetExtension() { return ".h264"; }
			static bool is_registered;
		};

	
		/* Implement singleton pattern for processors factory*/
		class PayloadProcessorsFactory 
		{
		private:
			static map<PAYLOAD_TYPE, function<shared_ptr<BaseProcessor>()>>    m_registered_processors;
			/* make it private to prohibit external creation */
			PayloadProcessorsFactory() = default;
		public:
			/* in c++ 17 we can use optional to return empty value */
			shared_ptr<BaseProcessor> GetProcessor(PAYLOAD_TYPE type)  const;
			static PayloadProcessorsFactory * GetInstance();
			static bool Register(PAYLOAD_TYPE type, function<shared_ptr<BaseProcessor>()> func);
		};

	}

}

