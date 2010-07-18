#pragma once

#include <boost/array.hpp>
#include <boost/cstdint.hpp>
#include <boost/tuple/tuple.hpp>

#include <util/buffer.h>

#include <exception>
#include <string>

namespace cockpit {
namespace detail {

// The exception we throw if there are any shenanigans in the input.
struct ParseFailed : public std::exception
{
	ParseFailed();
	const char* what() throw();
	virtual ~ParseFailed() throw();
};

boost::int32_t extract_int32(const boost::uint8_t* paramStart, const boost::uint8_t** currentParam, boost::uint16_t packetLength);
boost::uint32_t extract_uint32(const boost::uint8_t* paramStart, const boost::uint8_t** currentParam, boost::uint16_t packetLength);
float extract_float(const boost::uint8_t* paramStart, const boost::uint8_t** currentParam, boost::uint16_t packetLength);
bool extract_bool(const boost::uint8_t* paramStart, const boost::uint8_t** currentParam, boost::uint16_t packetLength);
std::string extract_string(const boost::uint8_t* paramStart, const boost::uint8_t** currentParam, boost::uint16_t packetLength);
boost::array<float, 3> extract_position(const boost::uint8_t* paramStart, const boost::uint8_t** currentParam, boost::uint16_t packetLength);
boost::array<float, 3> extract_direction(const boost::uint8_t* paramStart, const boost::uint8_t** currentParam, boost::uint16_t packetLength);
boost::uint32_t extract_color(const boost::uint8_t* paramStart, const boost::uint8_t** currentParam, boost::uint16_t packetLength);
boost::uint64_t extract_MUID(const boost::uint8_t* paramStart, const boost::uint8_t** currentParam, boost::uint16_t packetLength);
boost::tuple<Buffer /* data */, size_t /* count */, size_t /* size */>
extract_blob(const boost::uint8_t* paramStart, const boost::uint8_t** currentParam, boost::uint16_t packetLength);
boost::int8_t extract_int8(const boost::uint8_t* paramStart, const boost::uint8_t** currentParam, boost::uint16_t packetLength);
boost::uint8_t extract_uint8(const boost::uint8_t* paramStart, const boost::uint8_t** currentParam, boost::uint16_t packetLength);
boost::int16_t extract_int16(const boost::uint8_t* paramStart, const boost::uint8_t** currentParam, boost::uint16_t packetLength);
boost::uint16_t extract_uint16(const boost::uint8_t* paramStart, const boost::uint8_t**currentParam, boost::uint16_t packetLength);

}
}
