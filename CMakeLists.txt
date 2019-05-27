cmake_minimum_required(VERSION 3.0)

project(MPEG-TS_splitter VERSION ${VERSION_PREFIX})


set(SOURCES  mpeg_packet_processor.h 
				mpeg_ts_packet.cpp
				mpeg_ts_packet.h
				payload_processors.cpp
				payload_processors.h
				pch.h
				stream_reader.h
				test_unified_streaming.cpp)
				
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	add_executable(${PROJECT_NAME} ${SOURCES})
else()
	add_executable(${PROJECT_NAME} ${SOURCES})
endif()
