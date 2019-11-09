#ifndef DATUM
#define DATUM

#include <string>
#include <variant>

using real = double;

class Datum
{
public:
	Datum();
	virtual ~Datum();

	Datum(uint64_t);
	Datum(real);
	Datum(const std::string &data);

	void setUInt(uint64_t data);
	uint64_t getUInt() const;

	void setReal(real data);
	real getReal() const;

	void setString(const std::string &data);
	std::string getString() const;

	operator uint64_t() const
	{
		return getUInt();
	}

	operator std::string() const
	{
		return getString();
	}

	Datum operator+(const Datum &other) const
	{
		Datum result;
		if (const std::string *slhs = std::get_if<std::string>(&m_data))
		{
			if (const std::string *srhs = std::get_if<std::string>(&other.m_data))
			{
				result.setString(*slhs + *srhs);
			}
			else if (const uint64_t *irhs = std::get_if<uint64_t>(&other.m_data))
			{
				result.setString(*slhs + std::to_string(*irhs));
			}
			else if (const real *rrhs = std::get_if<real>(&other.m_data))
			{
				result.setString(*slhs + std::to_string(*rrhs));
			}
		}
		else if (const uint64_t *ilhs = std::get_if<uint64_t>(&m_data))
		{
			if (const std::string *srhs = std::get_if<std::string>(&other.m_data))
			{
				result.setString(std::to_string(*ilhs) + *srhs);
			}
			else if (const real *rrhs = std::get_if<real>(&other.m_data))
			{
				result.setReal(*ilhs + *rrhs);
			}
			else if (const uint64_t *irhs = std::get_if<uint64_t>(&other.m_data))
			{
				result.setUInt(*ilhs + *irhs);
			}
		}
		else if (const real *rlhs = std::get_if<real>(&m_data))
		{
			if (const real *rrhs = std::get_if<real>(&other.m_data))
			{
				result.setReal(*rlhs + *rrhs);
			}
			else if (const uint64_t *irhs = std::get_if<uint64_t>(&other.m_data))
			{
				result.setUInt(static_cast<uint64_t>(*rlhs + *irhs));
			}
			else if (const std::string *srhs = std::get_if<std::string>(&other.m_data))
			{
				result.setString(std::to_string(*rlhs) + *srhs);
			}
		}
		return result;
	}

	operator bool() const
	{
		return m_data.index() != 0;
	}

	bool operator==(uint64_t other) const
	{
		return other == getUInt();
	}

	bool operator==(const std::string &other) const
	{
		return other == getString();
	}

	bool operator!=(uint64_t other) const
	{
		return other != getUInt();
	}

	bool operator!=(const std::string &other) const
	{
		return other != getString();
	}

	bool operator<(uint64_t other) const
	{
		return other < getUInt();
	}

	bool operator<(const std::string &other) const
	{
		return other < getString();
	}

	bool operator<=(uint64_t other) const
	{
		return other <= getUInt();
	}

	bool operator<=(const std::string &other) const
	{
		return other <= getString();
	}

private:
	std::variant<std::monostate, std::string, uint64_t, real> m_data;
};

#endif // !DATUM
