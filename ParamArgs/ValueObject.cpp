#include "ValueObject.h"
#include "ValueCommon.h"
#include "BooleanValue.h"
#include "CharValue.h"
#include "ShortValue.h"
#include "IntValue.h"
#include "LongValue.h"
#include "FloatValue.h"
#include "DoubleValue.h"
#include "StringValue.h"
#include "ByteArray.h"

namespace yeguang
{
	static TValueVar& ParseBoolean(const char* const data)
	{
		static TValueVar value;

		value.valuetype = BOOLVALUE;
		value.bvalue = BooleanValue::ParseBoolean(data);

		return value;
	}

	static TValueVar& ParseChar(const char* const data)
	{
		static TValueVar value;

		value.valuetype = CHARVALUE;
		value.cvalue = CharValue::ParseChar(data);

		return value;
	}

	static TValueVar& ParseShort(const char* const data)
	{
		static TValueVar value;

		value.valuetype = SHORTVALUE;
		value.svalue = ShortValue::ParseShort(data);

		return value;
	}

	static TValueVar& ParseInt(const char* const data)
	{
		static TValueVar value;

		value.valuetype = INTVALUE;
		value.ivalue = IntValue::ParseInt(data);

		return value;
	}

	static TValueVar& ParseLong(const char* const data)
	{
		static TValueVar value;

		value.valuetype = LONGVALUE;
		value.lvalue = LongValue::ParseLong(data);

		return value;
	}

	static TValueVar& ParseFloat(const char* const data)
	{
		static TValueVar value;

		value.valuetype = FLOATVALUE;
		value.fvalue = FloatValue::ParseFloat(data);

		return value;
	}

	static TValueVar& ParseDouble(const char* const data)
	{
		static TValueVar value;

		value.valuetype = DOUBLEVALUE;
		value.dvalue = DoubleValue::ParseDouble(data);

		return value;
	}

	static TValueVar& ParseString(const char* const data)
	{
		static TValueVar value;

		value.valuetype = STRINGVALUE;
		value.strvalue = StringValue::ParseString(data);

		return value;
	}

    static TValueVar& ParseByteArray(const char* const data)
    {
        static TValueVar value;

        value.valuetype = BYTEARRAY;
        value.bytearray = ByteArray::ParseByteArray(data);

        return value;
    }

	ValueObject::ValueObject(const char *const data, int datalen)
	{
		if (data[2] == 1)
		{
			switch (data[3])
			{
			case 'Z':
				{					
					m_value = ParseBoolean(data);
				}break;
			case 'C':
				{
					m_value = ParseChar(data);
				}break;
			case 'S':
				{
					m_value = ParseShort(data);
				}break;
			case 'I':
				{
					m_value = ParseInt(data);
				}break;
			case 'J':
				{
					m_value = ParseLong(data);
				}break;
			case 'F':
				{
					m_value = ParseFloat(data);
				}break;
			case 'D':
				{
					m_value = ParseDouble(data);
				}break;
			default:
				break;
			}
		}
        else if (data[2] == 2)
        {
            if (!memcmp(data + 3, "[B", 2))
            {
                m_value = ParseByteArray(data);
            }
        }
		else if (data[2] == 8)
		{
			if (!memcmp(data + 3, "LString;", 8))
			{
				m_value = ParseString(data);
			}
		}
		else
		{
			throw std::invalid_argument("param is error!");
		}
	}

	ValueObject::~ValueObject()
	{

	}

	ValueObject::ValueObject(bool value)
	{
		m_value.valuetype = BOOLVALUE;
		m_value.bvalue = value;
	}

	ValueObject::ValueObject(char value)
	{
		m_value.valuetype = CHARVALUE;
		m_value.cvalue = value;
	}

	ValueObject::ValueObject(int16_t value)
	{
		m_value.valuetype = SHORTVALUE;
		m_value.svalue = value;
	}

	ValueObject::ValueObject(int value)
	{
		m_value.valuetype = INTVALUE;
		m_value.ivalue = value;
	}

	ValueObject::ValueObject(int64_t value)
	{
		m_value.valuetype = LONGVALUE;
		m_value.lvalue = value;
	}

	ValueObject::ValueObject(float value)
	{
		m_value.valuetype = FLOATVALUE;
		m_value.fvalue = value;
	}

	ValueObject::ValueObject(double value)
	{
		m_value.valuetype = DOUBLEVALUE;
		m_value.dvalue = value;
	}

	ValueObject::ValueObject(const char * const value)
	{
		m_value.valuetype = STRINGVALUE;
		m_value.strvalue = value;
	}

	ValueObject::ValueObject(const uint8_t * const value, int valuelen)
	{
		m_value.valuetype = BYTEARRAY;

		m_value.bytearray.datasize = valuelen;
		m_value.bytearray.data = std::tr1::shared_ptr<uint8_t>(new uint8_t[valuelen]);
		memcpy(m_value.bytearray.data.get(), value, valuelen);
	}

	emValueType ValueObject::GetType()
	{
		return m_value.valuetype;
	}

	bool ValueObject::GetBoolean()
	{
		return m_value.bvalue;
	}

	char ValueObject::GetChar()
	{
		return m_value.cvalue;
	}

	int16_t ValueObject::GetShort()
	{
		return m_value.svalue;
	}

	int32_t ValueObject::GetInt()
	{
		return m_value.ivalue;
	}

	int64_t ValueObject::GetLong()
	{
		return m_value.lvalue;
	}

	float ValueObject::GetFloat() 
	{
		return m_value.fvalue;
	}

	double ValueObject::GetDouble()
	{
		return m_value.dvalue;
	}

	std::string ValueObject::GetString()
	{
		return m_value.strvalue;
	}

	int ValueObject::GetByteLength()
	{
		return m_value.bytearray.datasize;
	}

    std::tr1::shared_ptr<uint8_t>& ValueObject::GetByteArray()
	{
        return m_value.bytearray.data;
	}

	void ValueObject::GetData(char* const data, int& datalen)
	{
		switch (m_value.valuetype)
		{
		case BOOLVALUE:
			{
				BooleanValue::PackageBoolean(m_value.bvalue, data, datalen);
			}break;
		case CHARVALUE:
			{
				CharValue::PackageChar(m_value.cvalue, data, datalen);
			}break;
		case SHORTVALUE:
			{
				ShortValue::PackageShort(m_value.svalue, data, datalen);
			}break;
		case INTVALUE:
			{
				IntValue::PackageInt(m_value.ivalue, data, datalen);
			}break;
		case LONGVALUE:
			{
				LongValue::PackageLong(m_value.lvalue, data, datalen);
			}break;
		case FLOATVALUE:
			{
				FloatValue::PackageFloat(m_value.fvalue, data, datalen);
			}break;
		case DOUBLEVALUE:
			{
				DoubleValue::PackageDouble(m_value.dvalue, data, datalen);
			}break;
		case STRINGVALUE:
			{
				StringValue::PackageString(m_value.strvalue, data, datalen);
			}break;
		case BYTEARRAY:
			{
				ByteArray::PackageByteArray(m_value.bytearray, data, datalen);
			}
		default:
			break;
		}
	}

}
