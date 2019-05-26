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
		public:
			virtual void ProcessData(const pair<size_t, const char*>) = 0;
		public:
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

			void DumpData(const pair<size_t, const char * > data)
			{
				string output = "output" + GetExtension();
				if (!m_file)
					// TODO need to check if opened 
					m_file = fopen(output.c_str(), "wb");
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
			void ProcessData(const pair<size_t, const char*> data) { DumpData(data); };
			string GetExtension() { return ".aac"; }
			static bool is_registered;
		};



		class VideoProcessor :public DataDumper<VideoProcessor>
		{
		public:
			void ProcessData(const pair<size_t, const char*> data) { DumpData(data); };
			string GetExtension() { return ".mp4"; }
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
			shared_ptr<BaseProcessor> GetProcessor(PAYLOAD_TYPE type)  const throw(exception);
			static PayloadProcessorsFactory * GetInstance();
			static bool Register(PAYLOAD_TYPE type, function<shared_ptr<BaseProcessor>()> func);
		};

	}

}

