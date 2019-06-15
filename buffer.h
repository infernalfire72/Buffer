#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <iostream>
#include <vector>
#include <string>

class buffer {
	public:
		buffer();
		void writeByte(uint8_t data);
		void writeInt16(int16_t data);
		void writeInt32(int32_t data);
		void writeInt64(int64_t data);
		void writeSByte(int8_t data);
		void writeUInt16(uint16_t data);
		void writeUInt32(uint32_t data);
		void writeUInt64(uint64_t data);
		void writeFloat(float data);
		void writeDouble(double data);
		void write7BitInt(int32_t data);
		void writeString(std::string data);
		void writeChar(char data);
		
		size_t size();
		int setStreamPosition(int pos);
		int getStreamPosition();
		int seekPosition(int pos);
		
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
		std::vector<uint8_t> dynamicData;
};

#endif // BUFFER_H
