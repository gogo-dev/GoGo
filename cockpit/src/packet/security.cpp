#include <boost/cstdint.hpp>
#include <boost/array.hpp>
#include <boost/tuple/tuple.hpp>
#include <string>
#include <util/buffer.h>

using namespace std;
using namespace boost;

namespace {

// The exception we throw if there are any shenanigans in the input.
struct ParseFailed
{
};

}

// Ensures there's enough room to remove "request", starting at "currentParam",
// bytes from the "paramStart" -> "paramStart + len" array.
static void overflow_check(const void* paramStart, size_t len, const void* currentParam, size_t request)
{
	const uintptr_t requestedEnd = reinterpret_cast<uintptr_t>(currentParam);
	const uintptr_t realEnd = reinterpret_cast<uintptr_t>(paramStart) + len - request;

	if(requestedEnd > realEnd)
		throw ParseFailed();
}

template <typename IntType>
static IntType extract_arbitrary_integer(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength)
{
	overflow_check(paramStart, packetLength, *currentParam, sizeof(IntType));

	IntType ret = *reinterpret_cast<const IntType*>(*currentParam);
	*currentParam += sizeof(IntType);

	return ret;
}

int32_t extract_int32(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength)
{
	return extract_arbitrary_integer<int32_t>(paramStart, currentParam, packetLength);
}

uint32_t extract_uint32(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength)
{
	return extract_arbitrary_integer<uint32_t>(paramStart, currentParam, packetLength);
}

float extract_float(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength)
{
	// Because floats aren't very comparable, we just treat it like any other integer.
	return extract_arbitrary_integer<float>(paramStart, currentParam, packetLength);
}

bool extract_bool(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength)
{
	// Each bool is really a byte in disguise.
	return static_cast<bool>(extract_arbitrary_integer<uint8_t>(paramStart, currentParam, packetLength));
}

// Checks for null-terminators. If all goes well, the pointer will move to the
// next character. However, if it ISN'T null, ParseFailed() will be thrown.
static void check_for_null(const uint8_t*& c)
{
	if(*c++ != NULL)
		throw ParseFailed();
}

string extract_string(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength)
{
	uint16_t len = extract_arbitrary_integer<uint16_t>(paramStart, currentParam, packetLength);
	overflow_check(paramStart, packetLength, *currentParam, len);

	string ret;
	ret.reserve(len - 1); // We only need room for ONE null-terminator.

	for(uint16_t i = 0; i < (len - 2); ++i)
		ret += *(*currentParam)++;

	check_for_null(*currentParam);
	(*currentParam)++;	// Gunz is weird. This is necessary to handle one
	                    // garbage byte at the end of the string.

	return ret;
}

array<float, 3> extract_position(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength)
{
	array<float, 3> ret = { {
		extract_arbitrary_integer<float>(paramStart, currentParam, packetLength),
		extract_arbitrary_integer<float>(paramStart, currentParam, packetLength),
		extract_arbitrary_integer<float>(paramStart, currentParam, packetLength)
	} };

	return ret;
}

array<float, 3> extract_direction(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength)
{
	array<float, 3> ret = { {
		extract_arbitrary_integer<float>(paramStart, currentParam, packetLength),
		extract_arbitrary_integer<float>(paramStart, currentParam, packetLength),
		extract_arbitrary_integer<float>(paramStart, currentParam, packetLength)
	} };

	return ret;
}

uint32_t extract_color(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength)
{
	return extract_arbitrary_integer<uint32_t>(paramStart, currentParam, packetLength);
}

uint64_t extract_MUID(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength)
{
	return extract_arbitrary_integer<uint64_t>(paramStart, currentParam, packetLength);
}

tuple<Buffer /* data */, size_t /* count */, size_t /* size */>
extract_blob(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength)
{
	uint32_t totalSize = extract_arbitrary_integer<uint32_t>(paramStart, currentParam, packetLength);
	uint32_t elementSize = extract_arbitrary_integer<uint32_t>(paramStart, currentParam, packetLength);
	uint32_t elementCount = extract_arbitrary_integer<uint32_t>(paramStart, currentParam, packetLength);
	const uint8_t* blobStart = *currentParam;

	// I agree, it's an entirely redundant parameter. Deal with it.
	if(totalSize != (elementSize*elementCount + sizeof(elementSize) + sizeof(elementCount)))
		throw ParseFailed();

	overflow_check(paramStart, packetLength, blobStart, elementSize*elementCount);
	*currentParam += elementSize * elementCount;

	return make_tuple(
		Buffer(blobStart, elementSize*elementCount),
		elementCount,
		elementSize
	);
}

int8_t extract_int8(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength)
{
	return extract_arbitrary_integer<int8_t>(paramStart, currentParam, packetLength);
}

uint8_t extract_uint8(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength)
{
	return extract_arbitrary_integer<uint8_t>(paramStart, currentParam, packetLength);
}

int16_t extract_int16(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength)
{
	return extract_arbitrary_integer<int16_t>(paramStart, currentParam, packetLength);
}

uint16_t extract_uint16(const uint8_t* paramStart, const uint8_t**currentParam, uint16_t packetLength)
{
	return extract_arbitrary_integer<uint16_t>(paramStart, currentParam, packetLength);
}
