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
	Datum(const std::string& data);

	void setUInt(uint64_t data);
	uint64_t getUInt() const;

	void setReal(real data);
	real getReal() const;

	void setString(const std::string& data);
	std::string getString() const;

	operator uint64_t() const
	{
		return getUInt();
	}

	operator std::string() const
	{
		return getString();
	}

	Datum operator +(const Datum& other) const
	{
		Datum result;
		if (const std::string *lhs = std::get_if<std::string>(&m_data))
		{
			if (const std::string *rhs = std::get_if<std::string>(&other.m_data))
			{
				result.setString(*lhs + *rhs);
			}
			else if (const uint64_t *rhs = std::get_if<uint64_t>(&other.m_data))
			{
				result.setString(*lhs + std::to_string(*rhs));
			}
			else if (const real *rhs = std::get_if<real>(&other.m_data))
			{
				result.setString(*lhs + std::to_string(*rhs));
			}
		}
		else if (const uint64_t *lhs = std::get_if<uint64_t>(&m_data))
		{
			if (const std::string *rhs = std::get_if<std::string>(&other.m_data))
			{
				result.setString(std::to_string(*lhs) + *rhs);
			}
			else if (const real *rhs = std::get_if<real>(&other.m_data))
			{
				result.setReal(*lhs + *rhs);
			}
			else if (const uint64_t *rhs = std::get_if<uint64_t>(&other.m_data))
			{
				result.setUInt(*lhs + *rhs);
			}
		}
		else if (const real *lhs = std::get_if<real>(&m_data))
		{
			if (const real *rhs = std::get_if<real>(&other.m_data))
			{
				result.setReal(*lhs + *rhs);
			}
			else if (const uint64_t *rhs = std::get_if<uint64_t>(&other.m_data))
			{
				result.setUInt(*lhs + *rhs);
			}
			else if (const std::string *rhs = std::get_if<std::string>(&other.m_data))
			{
				result.setString(std::to_string(*lhs) + *rhs);
			}
		}
		return result;
	}

	operator bool() const
	{
		return m_data.index() != 0;
	}

	bool operator ==(uint64_t other) const
	{
		return other == getUInt();
	}

	bool operator ==(const std::string& other) const
	{
		return other == getString();
	}

	bool operator !=(uint64_t other) const
	{
		return other != getUInt();
	}

	bool operator !=(const std::string& other) const
	{
		return other != getString();
	}

	bool operator <(uint64_t other) const
	{
		return other < getUInt();
	}

	bool operator <(const std::string& other) const
	{
		return other < getString();
	}

	bool operator <=(uint64_t other) const
	{
		return other <= getUInt();
	}

	bool operator <=(const std::string& other) const
	{
		return other <= getString();
	}

private:
	std::variant<std::monostate, std::string, uint64_t, real> m_data;
};

#endif // !DATUM
