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

Datum::Datum(real data)
{
	setReal(data);
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
	else if (const real *data = std::get_if<real>(&m_data))
	{
		return static_cast<uint64_t>(*data);
	}
	else if (const std::string *data = std::get_if<std::string>(&m_data))
	{
		return std::stoul(*data);
	}
	return 0;
}

void Datum::setReal(real data)
{
	m_data = data;
}

real Datum::getReal() const
{
	if (const real *data = std::get_if<real>(&m_data))
	{
		return *data;
	}
	else if (const uint64_t *data = std::get_if<uint64_t>(&m_data))
	{
		return static_cast<real>(*data);
	}
	else if (const std::string *data = std::get_if<std::string>(&m_data))
	{
		return std::stof(*data);
	}
	return 0.f;
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
	else if (const real *data = std::get_if<real>(&m_data))
	{
		return std::to_string(*data);
	}
	else if (const uint64_t *data = std::get_if<uint64_t>(&m_data))
	{
		return std::to_string(*data);
	}
	return "";
}
