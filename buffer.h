#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <iostream>
#include <vector>
#include <string>

class buffer {
	public:
		buffer();
		void writeByte(const uint8_t& data);
		void writeInt16(const int16_t& data);
		void writeInt32(const int32_t& data);
		void writeInt64(const int64_t& data);
		void writeSByte(const int8_t& data);
		void writeUInt16(const uint16_t& data);
		void writeUInt32(const uint32_t& data);
		void writeUInt64(const uint64_t& data);
		void writeFloat(const float& data);
		void writeDouble(const double& data);
		void write7BitInt(const int32_t& data);
		void writeString(const std::string& data);
		void writeChar(const char& data);
		
		size_t size();
		int setStreamPosition(const int& pos);
		int getStreamPosition();
		int seekPosition(const int& pos);
		void clear();
		
		uint8_t readByte();
		int8_t readSByte();
		int16_t readInt16();
		uint16_t readUInt16();
		int32_t readInt32();
		uint32_t readUInt32();
		int64_t readInt64();
		uint64_t readUInt64();
		std::string readString();
		int32_t read7BitInt();
		double readDouble();
		float readFloat();
	private:
		int streamPosition;
	protected:
		std::vector<uint8_t> dynamicData;
};

#endif // BUFFER_H