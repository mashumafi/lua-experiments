#ifndef DATUM
#define DATUM

#include <string>
#include <variant>

class Datum
{
public:
	Datum();
	virtual ~Datum();

	Datum(uint64_t);
	Datum(const std::string& data);

	void setUInt(uint64_t data);
	uint64_t getUInt() const;

	void setString(const std::string& data);
	std::string getString() const;

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
		}
		else if (const uint64_t *lhs = std::get_if<uint64_t>(&m_data))
		{
			if (const std::string *rhs = std::get_if<std::string>(&other.m_data))
			{
				result.setString(std::to_string(*lhs) + *rhs);
			}
			else if (const uint64_t *rhs = std::get_if<uint64_t>(&other.m_data))
			{
				result.setUInt(*lhs + *rhs);
			}
		}
		return result;
	}

	bool operator ==(const std::string& other) const
	{
		return other == getString();
	}

private:
	std::variant<std::string, uint64_t> m_data;
};

#endif // !DATUM
