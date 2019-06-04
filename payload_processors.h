#pragma once
#include "pch.h"
#include "mpeg_ts_packet.h"

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
            virtual void ProcessData(const std::pair<size_t, const uint8_t*>) = 0;
			template<class T>
            static std::shared_ptr<BaseProcessor> Create()
			{
                return std::make_shared<T>();
			}
		};

		/* Classic curiously recurring template pattern implementation
			just to avoid code duplication*/
		template<typename T>
		class DataDumper :public BaseProcessor
		{
		protected:
            std::string    m_extension;
            std::ofstream  m_file;
            virtual std::string GetExtension() = 0;

            void DumpData(std::pair<size_t, const uint8_t * > data)
			{
                std::string output = "output" + GetExtension();
                if (!m_file)
                {
                    try
                    { 
                        m_file.open(output.c_str(), std::ofstream::out | std::ofstream::binary);
                        if(!m_file.is_open())
                            throw "Cannot create output file";
                    }
                    catch (std::string & s)
                    {
                        std::cout<<s<<std::endl;
                        throw std::system_error(EIO, std::iostream_category(), s.c_str());
                    }
                }
                if(m_file.bad())
                    throw std::system_error(EIO, std::iostream_category(), "Something wrong with output file");
                m_file.write((const char* )data.second, data.first);
			}

		public:
			DataDumper() :m_file(nullptr) {}
			~DataDumper()
			{
				if (m_file)
                    m_file.close();
			}
		};

        class AudioProcessor final :public DataDumper<AudioProcessor>
		{
		public:
            void ProcessData(const std::pair<size_t, const uint8_t*> data) { DumpData(data); };
            std::string GetExtension() { return ".aac"; }
			static bool is_registered;
            static const int m_type = 33;
		};



        class VideoProcessor final :public DataDumper<VideoProcessor>
		{
		public:
            void ProcessData(const std::pair<size_t, const uint8_t*> data) { DumpData(data); };
            std::string GetExtension() { return ".h264"; }
			static bool is_registered;
            static const int m_type = 34;
		};

	
		/* Implement singleton pattern for processors factory*/
		class PayloadProcessorsFactory 
		{
		private:
            static std::map<int, std::function<std::shared_ptr<BaseProcessor>()>>    m_registered_processors;
			/* make it private to prohibit external creation */
			PayloadProcessorsFactory() = default;
		public:
			/* in c++ 17 we can use optional to return empty value */
            std::shared_ptr<BaseProcessor> GetProcessor(int type)  const;
			static PayloadProcessorsFactory * GetInstance();
            static bool Register(int type, std::function<std::shared_ptr<BaseProcessor>()> func);
		};

	}

}

