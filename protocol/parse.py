#!/usr/bin/python3.1
# To the poor soul reading through this file to make changes:
# I'm sorry, and good luck. I hope you manage to make this file suck less.
#    - Clark

class Command:
	def __init__(self):
		self.id = ''
		self.name = ''
		self.docstring = ''
		self.parameters = list()

class Parameter:
	def __init__(self):
		self.id = ''
		self.type = ''
		self.name = ''

def clean(commands):
	def get_type(paramID):
		if paramID == 0x00:
			return "boost::int32_t"
		elif paramID == 0x01:
			return "boost::uint32_t"
		elif paramID == 0x02:
			return "float"
		elif paramID == 0x03:
			return "bool"
		elif paramID == 0x04:
			return "const std::string&"
		elif paramID == 0x06:
			return "const boost::array<float, 3>&"
		elif paramID == 0x07:
			return "const boost::array<float, 3>&"
		elif paramID == 0x08:
			return "boost::uint32_t"
		elif paramID == 0x09:
			return "boost::uint64_t"
		elif paramID == 0x0A:
			return "boost::tuple<boost::shared_array<boost::uint8_t> /* data */, size_t /* count */, size_t /* size */>"
		elif paramID == 0x0B:
			return "const boost::array<boost::uint16_t, 3>&"
		elif paramID == 0x0C:
			return "boost::uint8_t"
		elif paramID == 0x0D:
			return "boost::int16_t"
		elif paramID == 0x0E:
			return "boost::uint16_t"
		else:
			return None
	
	to_drop = list()

	for c in commands:
		savedID = c.id
		c.id = int(c.id, 16)
		c.name = ''.join([x for x in c.name if x != ' ']).replace('.', '_')
		# No docstring changes necessary.
		for p in c.parameters:
			p.type = get_type(p.id)
			if p.type == None:
				to_drop.append(c)
			p.name = ''.join([x for x in p.name if x != ' ' if x != ')']).replace('.', '_').replace('(', '_').replace(' ', '_')

		if c.name in [x.name for x in commands if x != c]:
			print("Warning: Conflict found ->", c.name, 'ID:', savedID)

	commands = [c for c in commands if c not in to_drop]

	print("Commands:\n", '\n'.join([''.join([c.name, '(', ' '.join([p.name for p in c.parameters]), ')']) for c in commands]), sep='')

	return commands

def parse(p):
	c = list()
	for x in p:
		if x.find('Command ID = ') == 0:
			c.append(Command())
			c[-1].id = x[x.find(' = ') + 3:]
		elif x.find('Command = ') == 0:
			c[-1].name = x[x.find('"') + 1:-1]
		elif x.find('Command Help = ') == 0:
			c[-1].docstring = x[x.find('"') + 1:-1]
		elif x.find('    Parameter Type = ') == 0:
			c[-1].parameters.append(Parameter())
			c[-1].parameters[-1].id = int(x[x.find(' = ') + 3:], 16)
		elif x.find('    Parameter = ') == 0:
			c[-1].parameters[-1].name = x[x.find('"') + 1:-1]

	return clean(c)

def make_packet_registry_header_header():
	return """/*
 * NOTICE: Do not manually edit this file. It has been autogenerated by
 * protocol/parse.py. Any changes should me made there, instead of here.
 */
#pragma once
#include <string>
#include <cstddef>
#include <boost/signals2.hpp>
#include <boost/cstdint.hpp>
#include <boost/array.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/shared_array.hpp>

namespace packet {

// Handles the registration and dispatch to the various packet handlers
// around the nation.
class Registry
{
public:
	Registry();

	void dispatch(boost::uint16_t packetID,
	              const boost::uint8_t* parameters,
		      boost::uint16_t length);

	~Registry();

	// This signal is called when the parsing of a packet has failed. Do whatever you want in here.
	boost::signals2::signal<void (boost::uint16_t /* packetID */,
	                              const boost::uint8_t* /* rawParameters */,
	                              boost::uint16_t /* length */)> OnFailedParse;"""

def make_packet_registry_header_footer():
	return "\n};\n\n}"

def build_packet_registry_header(commands):
	f = open('include/net/PacketRegistry.h', 'w')

	print(make_packet_registry_header_header(), end='', file=f)
	
	for c in commands:
		print('\n\n\t// ', c.docstring, '\n', sep='', end='', file=f)
		print('\tboost::signals2::signal<void (', sep='',end='', file=f)
		for p in c.parameters:
			seperator = ''
			if p == c.parameters[0]:
				seperator = ''
			else:
				seperator = ', '

			print(seperator, p.type, ' /* ', p.name, ' */', sep='', end='', file=f)

		print(')> ', c.name, ';', sep='', end='', file=f)

	print(make_packet_registry_header_footer(), end='', file=f)

def make_packet_registry_cpp_header():
	return """/*
 * NOTICE: Do not manually edit this file. It has been autogenerated by
 * protocol/parse.py. Any changes should me made there, instead of here.
 */
#include <boost/format.hpp>
#include <boost/shared_array.hpp>
#include <net/PacketRegistry.h>
#include <net/protocol/all>

using namespace std;
using namespace boost;

// The following are implemented in security.cpp
// If they throw ANY exception, the packet's parsing will be broken,
// the packet will be dropped, and OnFailedParse will be signaled.
// The extraction method MUST modify *currentParam to point to the
// next element in the parameter string.
int32_t extract_int32(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength);
uint32_t extract_uint32(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength);
float extract_float(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength);
bool extract_bool(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength);
string extract_string(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength);
array<float, 3> extract_position(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength);
array<float, 3> extract_direction(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength);
uint32_t extract_color(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength);
uint64_t extract_MUID(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength);
tuple<shared_array<uint8_t> /* data */, size_t /* count */, size_t /* size */>
extract_blob(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength);
array<uint16_t, 3> extract_vector(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength);
uint8_t extract_uint8(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength);
int16_t extract_int16(const uint8_t* paramStart, const uint8_t** currentParam, uint16_t packetLength);
uint16_t extract_uint16(const uint8_t* paramStart, const uint8_t**currentParam, uint16_t packetLength);

namespace packet {

Registry::Registry()
{
}

Registry::~Registry()
{
}

void Registry::dispatch(uint16_t packetID,
                              const uint8_t* parameters,
                              uint16_t length)
{
	const uint8_t* paramPtr = parameters;

	try {
		switch(packetID)
		{
"""

# Just accept it. LOL.
def make_packet_registry_cpp_footer():
	return "\t\t}\n\t} catch(...) {\n\t\t\tthis->OnFailedParse(packetID, parameters, length);\n\t}\n}\n\n}"

def make_case(command):
	extractorMap = {
		0x00 : ("int32_t", "extract_int32"),
		0x01 : ("uint32_t", "extract_uint32"),
		0x02 : ("float", "extract_float"),
		0x03 : ("bool", "extract_bool"),
		0x04 : ("std::string", "extract_string"),
		0x06 : ("array<float, 3>", "extract_position"),
		0x07 : ("array<float, 3>", "extract_direction"),
		0x08 : ("uint32_t", "extract_color"),
		0x09 : ("uint64_t", "extract_MUID"),
		0x0A : ("tuple<shared_array<uint8_t>, size_t, size_t>", "extract_blob"),
		0x0B : ("array<uint16_t, 3>", "extract_vector"),
		0x0C : ("uint8_t", "extract_uint8"),
		0x0D : ("int16_t", "extract_int16"),
		0x0E : ("uint16_t", "extract_uint16")
	}

	ret = ''.join(['\t\tcase protocol::', command.name, '::packetID:\n\t\t\t{\n'])

	for (p, i) in zip(command.parameters, range(9999999)):
		(type, func) = extractorMap[p.id]
		ret = ''.join([ret, '\t\t\t\t', type, ' p', str(i), ' = ', func, '(parameters, &paramPtr, length);\n'])

	ret = ''.join([ret, '\t\t\t\tthis->', command.name, '('])

	for (p, i) in zip(command.parameters, range(9999999)):
		sep = ''
		if i == 0:
			sep = ''
		else:
			sep = ', '

		ret = ''.join([ret, sep, 'p', str(i)])

	ret = ''.join([ret, ');\n\t\t\t\tbreak;\n\t\t\t}'])

	return ret

def build_packet_registry_cpp(commands):
	f = open('net/src/PacketRegistry.cpp', 'w')

	print(make_packet_registry_cpp_header(), end='', file=f)

	for c in commands:
		end = ''
		if c == commands[-1]:
			end = ''
		else:
			end = '\n'
		print(make_case(c), end=end, file=f);
	
	print(make_packet_registry_cpp_footer(), end='', file=f)

def make_all_packet_types_header_header():
	return """/*
 * NOTICE: Do not manually edit this file. It has been autogenerated by
 * protocol/parse.py. Any changes should me made there, instead of here.
 */
#pragma once"""


def build_all_packet_types_header(commands):
	f = open('include/net/protocol/all', 'w')

	print(make_all_packet_types_header_header(), end='', file=f)

	for c in commands:
		print('\n#include "', c.name, '.h"', sep='', end='', file=f)

def make_root_packet_header():
	return """/*
 * NOTICE: Do not manually edit this file. It has been autogenerated by
 * protocol/parse.py. Any changes should me made there, instead of here.
 */
#pragma once
#include <boost/cstdint.hpp>
#include <util/buffer.h>

namespace packet {
namespace protocol {
	class Packet
	{
	public:
		virtual const char* name() const = 0;
		virtual const char* docstring() const = 0;
		virtual boost::uint16_t id() const = 0;
		virtual Buffer serialize() const = 0;
	};
}
}"""

def build_root_packet_header():
	f = open('include/net/packet.h', 'w')

	print(make_root_packet_header(), end='', file=f)

def make_command_header(name, docstring):
	return ''.join(["""/*
 * NOTICE: Do not manually edit this file. It has been autogenerated by
 * protocol/parse.py. Any changes should me made there, instead of here.
 */
#pragma once
#include <net/packet.h>
#include <boost/cstdint.hpp>
#include <net/PacketParameters.h>

namespace packet {
namespace protocol {

// """, docstring, """
class """, name, """ : public Packet
{
"""])

def make_local_vars(params):
	retVal = ""

	if len(params) != 0:
		retVal = 'private:\n'

	for p in params:
		retVal = ''.join([retVal, '\t', typeMap[p.id], ' ', p.name, ';\n'])

	return retVal

def make_constructor(command):
	retVal = ''.join(["""\npublic:
	enum { packetID = """, str(command.id), """ };\n\n"""])

	retVal = ''.join([retVal, '\t', command.name, '('])

	for p in command.parameters:
		sep = ', '
		if p == command.parameters[0]:
			sep = ''
		retVal = ''.join([retVal, sep, typeMap[p.id], ' ', p.name])

	retVal = ''.join([retVal, ');\n'])

	return retVal

def make_command_header_footer():
	return """
	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}"""

typeMap = {
	0x00 : "packet::int32",
	0x01 : "packet::uint32",
	0x02 : "packet::floating_point",
	0x03 : "packet::boolean",
	0x04 : "packet::string",
	0x06 : "packet::position",
	0x07 : "packet::direction",
	0x08 : "packet::color",
	0x09 : "packet::MUID",
	0x0A : "packet::blob",
	0x0B : "packet::vector",
	0x0C : "packet::uint8",
	0x0D : "packet::int16",
	0x0E : "packet::uint16"
}

def build_command_header(command):
	f = open(''.join(['include/net/protocol/', command.name, '.h']), 'w')

	print(make_command_header(command.name, command.docstring), end='', sep='', file=f)
	print(make_local_vars(command.parameters), end='', sep='', file=f)
	print(make_constructor(command), end='', sep='', file=f)
	print(make_command_header_footer(), end='', sep='', file=f)

def make_all_packets_cpp_header():
	return """/*
 * NOTICE: Do not manually edit this file. It has been autogenerated by
 * protocol/parse.py. Any changes should me made there, instead of here.
 */
#include <net/protocol/all>
#include <util/memory.h>

using namespace boost;

#define countof(array) \
	(sizeof(array)/sizeof((array)[0]))

static Buffer merge_parameters(Buffer* serializedParameters, size_t numberOfParameters)
{
	size_t packetLength = 0;

	for(size_t i = 0; i < numberOfParameters; ++i)
		packetLength += serializedParameters[i].length();

	assert(packetLength <= 0xFFFF);

	Buffer out(packetLength);
	uint8_t* outPtr = out.data();
	Buffer* param = serializedParameters;

	for(size_t i = 0; i < numberOfParameters; ++i, ++param)
		outPtr = memory::pcopy(outPtr, param->data(), param->length());

	return out;
}

namespace packet {
namespace protocol {"""

def flesh_out_command(command):
	ret = '\n\n'

	ret = ''.join([ret, command.name, '::', command.name, '('])

	if len(command.parameters) != 0:
		for p in command.parameters:
			sep = ', '
			if p == command.parameters[0]:
				sep = ''
			ret = ''.join([ret, sep, typeMap[p.id], ' _', p.name])

		ret = ''.join([ret, ')\n\t: '])
	
		for p in command.parameters:
			sep = ', '
			if p == command.parameters[0]:
				sep = ''
			ret = ''.join([ret, sep, p.name, '(_', p.name, ')'])
	else:
		ret = ''.join([ret, ')'])

	ret = ''.join([
		ret,
		'\n{\n}\n\nconst char* ', command.name, '::name() const\n{\n\treturn "',
		command.name, '";\n}\n\nconst char* ', command.name, '::doc() const\n{\n\treturn "',
		command.docstring, '";\n}\n\nuint16_t ', command.name, '::id() const\n{\n\treturn ',
		'packetID', ';\n}\n\nBuffer ', command.name, '::serialize() const\n{\n'])

	if len(command.parameters) != 0:
		ret = ''.join([ret, '\tBuffer serializedParameters[] = {\n'])
		for p in command.parameters:
			sep = ','
			if p == command.parameters[-1]:
				sep = ''
			ret = ''.join([ret, '\t\t', p.name, '.serialize()', sep, '\n'])

		return ''.join([ret, '\t};\n\n', '\treturn merge_parameters(serializedParameters, countof(serializedParameters));\n}'])
	else:
		return ''.join([ret, '\treturn Buffer(0);\n}'])

def make_all_packets_cpp_footer():
	return """

}
}"""

def build_all_packets_cpp(commands):
	f = open('net/src/all_packets.cpp', 'w')

	print(make_all_packets_cpp_header(), end='', file=f)
	for c in commands:
		print(flesh_out_command(c), end='', file=f)

	print(make_all_packets_cpp_footer(), end='', file=f)

commands = list()

from sys import argv

if len(argv) == 2:
	commands = parse([x[:-1] for x in open(argv[1]).readlines()])
	build_packet_registry_header(commands)
	build_packet_registry_cpp(commands)
	build_all_packet_types_header(commands)
	build_root_packet_header()
	for c in commands:
		build_command_header(c)
	build_all_packets_cpp(commands)
else:
	print('Usage: "./parse.py [protocol file]"')
	print("Please note that the build files will be generated in subdirectories of parse.py.")
