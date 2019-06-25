#include "buffer.h"
#include <iostream>
#include <cmath>

#include <string>

buffer::buffer()
{
	streamPosition = 0;
	std::cout << "Stream Created" << std::endl;  	
}

#pragma region writing
void buffer::writeByte(const uint8_t& data) 
{
	dynamicData.push_back(data);
}

void buffer::writeSByte(const int8_t& data)
{
	dynamicData.push_back(data);
}

void buffer::writeInt16(const int16_t& data) 
{
	dynamicData.push_back((uint8_t)data);
	dynamicData.push_back((uint8_t)(data >> 8));
}

void buffer::writeUInt16(const uint16_t& data) 
{
	dynamicData.push_back((uint8_t)data);
	dynamicData.push_back((uint8_t)(data >> 8));
}

void buffer::writeInt32(const int32_t& data)
{
	dynamicData.resize(dynamicData.size() + 4);
	*(int32_t*)&dynamicData[dynamicData.size() - 4] = data;
}

void buffer::writeUInt32(const uint32_t& data)
{
	dynamicData.resize(dynamicData.size() + 4);
	*(uint32_t*)&dynamicData[dynamicData.size() - 4] = data;
}

void buffer::writeInt64(const int64_t& data)
{
	dynamicData.resize(dynamicData.size() + 8);
	*(int64_t*)&dynamicData[dynamicData.size() - 8] = data;
}

void buffer::writeUInt64(const uint64_t& data)
{
	dynamicData.resize(dynamicData.size() + 8);
	*(uint64_t*)&dynamicData[dynamicData.size() - 8] = data;
}

void buffer::writeFloat(const float& data)
{
	uint32_t TmpValue = *(uint32_t*)&data;
    writeUInt32(TmpValue);
}

void buffer::writeDouble(const double& data)
{
	uint64_t TmpValue = *(uint64_t*)&data;
	writeUInt64(TmpValue);
}

void buffer::write7BitInt(const int32_t& data)
{
	uint32_t v = (uint32_t)data;
    while (v >= 0x80)
    {
        writeByte((uint8_t)(v | 0x80));
        v >>= 7;
    }
    writeByte((uint8_t)v);
}

void buffer::writeChar(const char& data) 
{
	writeByte(data);
}

void buffer::writeString(const std::string& data) 
{
	write7BitInt(data.length());
	for(int i = 0; i < data.length(); i++) writeChar(data[i]);
}

#pragma endregion

#pragma region operations
size_t buffer::size()
{
	return dynamicData.size();
}

int buffer::setStreamPosition(const int& pos)
{
	streamPosition = pos;
	return streamPosition;
}

int buffer::getStreamPosition() 
{
	return streamPosition;
}

int buffer::seekPosition(const int& pos) 
{
	return (int)dynamicData[pos];
}

uint8_t buffer::readByte()
{
	return dynamicData[streamPosition++];
}

void buffer::clear()
{
	dynamicData.clear();
}
#pragma endregion operations

#pragma region readers
int8_t buffer::readSByte()
{
	return (int8_t)dynamicData[streamPosition++];
}

int16_t buffer::readInt16()
{
	uint8_t byte1 = readByte();
	uint8_t byte2 = readByte();
	return (int16_t)(byte2 * 256 + byte1);
}

uint16_t buffer::readUInt16()
{
	uint8_t byte1 = readByte();
	uint8_t byte2 = readByte();
	return (uint16_t)(byte2 * 256 + byte1);
}

int32_t buffer::readInt32() 
{
	int X [4] = { readByte(), readByte(), readByte(), readByte() };
	return (int32_t)(X[3] << 24) + (X[2] << 16) + (X[1] << 8) + (X[0] << 0);
}

uint32_t buffer::readUInt32()
{
	int X [4] = { readByte(), readByte(), readByte(), readByte() };
	return (uint32_t)(X[3] << 24) + (X[2] << 16) + (X[1] << 8) + (X[0] << 0);
}

int64_t buffer::readInt64()
{
	int X [8] = { readByte(), readByte(), readByte(), readByte(), readByte(), readByte(), readByte(), readByte() };
	return (int64_t)((int64_t)X[7] << 56) + ((int64_t)X[6] << 48) + ((int64_t)X[5] << 40) + ((int64_t)X[4] << 32) + ((int64_t)X[3] << 24) + ((int64_t)X[2] << 16) + ((int64_t)X[1] << 8) + ((int64_t)X[0] << 0);
}

uint64_t buffer::readUInt64()
{
	int X [8] = { readByte(), readByte(), readByte(), readByte(), readByte(), readByte(), readByte(), readByte() };
	return (uint64_t)((int64_t)X[7] << 56) + ((int64_t)X[6] << 48) + ((int64_t)X[5] << 40) + ((int64_t)X[4] << 32) + ((int64_t)X[3] << 24) + ((int64_t)X[2] << 16) + ((int64_t)X[1] << 8) + ((int64_t)X[0] << 0);
}

float buffer::readFloat() 
{
	int32_t val = readInt32();
	return *(float*)&val;
}

double buffer::readDouble()
{
	int64_t val = readInt64();
	return *(double*)&val;
}

int32_t buffer::read7BitInt()
{
    int count = 0;
    int shift = 0;
    uint8_t b;
    do
    {
        b = readByte();
        count |= (b & 0x7F) << shift;
        shift += 7;
    } while ((b & 0x80) != 0);
    return count;
}

std::string buffer::readString()
{
	int32_t len = read7BitInt();
	std::string str;
	for (int i = 0; i < len; i++) str.push_back(readByte());
	return str;
}
#pragma endregion
