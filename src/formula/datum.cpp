#include "datum.h"

Datum::Datum()
{
}

Datum::~Datum()
{
}

Datum::Datum(uint64_t data)
{
	setUInt(data);
}

Datum::Datum(const std::string& data)
{
	setString(data);
}

void Datum::setUInt(uint64_t data)
{
	m_data = data;
}

uint64_t Datum::getUInt() const
{
	if (const uint64_t *data = std::get_if<uint64_t>(&m_data))
	{
		return *data;
	}
	return 0;
}

void Datum::setString(const std::string& data)
{
	m_data = data;
}

std::string Datum::getString() const
{
	if (const std::string *data = std::get_if<std::string>(&m_data))
	{
		return *data;
	}
	return "";
}
