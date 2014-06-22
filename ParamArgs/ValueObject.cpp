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
		value.bvalue = CBooleanValue::ParseBoolean(data);

		return value;
	}

	static TValueVar& ParseChar(const char* const data)
	{
		static TValueVar value;

		value.valuetype = CHARVALUE;
		value.cvalue = CCharValue::ParseChar(data);

		return value;
	}

	static TValueVar& ParseShort(const char* const data)
	{
		static TValueVar value;

		value.valuetype = SHORTVALUE;
		value.svalue = CShortValue::ParseShort(data);

		return value;
	}

	static TValueVar& ParseInt(const char* const data)
	{
		static TValueVar value;

		value.valuetype = INTVALUE;
		value.ivalue = CIntValue::ParseInt(data);

		return value;
	}

	static TValueVar& ParseLong(const char* const data)
	{
		static TValueVar value;

		value.valuetype = LONGVALUE;
		value.lvalue = CLongValue::ParseLong(data);

		return value;
	}

	static TValueVar& ParseFloat(const char* const data)
	{
		static TValueVar value;

		value.valuetype = FLOATVALUE;
		value.fvalue = CFloatValue::ParseFloat(data);

		return value;
	}

	static TValueVar& ParseDouble(const char* const data)
	{
		static TValueVar value;

		value.valuetype = DOUBLEVALUE;
		value.dvalue = CDoubleValue::ParseDouble(data);

		return value;
	}

	static TValueVar& ParseString(const char* const data)
	{
		static TValueVar value;

		value.valuetype = STRINGVALUE;
		value.strvalue = CStringValue::ParseString(data);

		return value;
	}

    static TValueVar& ParseByteArray(const char* const data)
    {
        static TValueVar value;

        value.valuetype = BYTEARRAY;
        value.bytearray = CByteArray::ParseByteArray(data);

        return value;
    }

	CValueObject::CValueObject(const char *const data, int datalen)
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

	CValueObject::~CValueObject()
	{

	}

	CValueObject::CValueObject(bool value)
	{
		m_value.valuetype = BOOLVALUE;
		m_value.bvalue = value;
	}

	CValueObject::CValueObject(char value)
	{
		m_value.valuetype = CHARVALUE;
		m_value.cvalue = value;
	}

	CValueObject::CValueObject(int16_t value)
	{
		m_value.valuetype = SHORTVALUE;
		m_value.svalue = value;
	}

	CValueObject::CValueObject(int value)
	{
		m_value.valuetype = INTVALUE;
		m_value.ivalue = value;
	}

	CValueObject::CValueObject(int64_t value)
	{
		m_value.valuetype = LONGVALUE;
		m_value.lvalue = value;
	}

	CValueObject::CValueObject(float value)
	{
		m_value.valuetype = FLOATVALUE;
		m_value.fvalue = value;
	}

	CValueObject::CValueObject(double value)
	{
		m_value.valuetype = DOUBLEVALUE;
		m_value.dvalue = value;
	}

	CValueObject::CValueObject(const char * const value)
	{
		m_value.valuetype = STRINGVALUE;
		m_value.strvalue = value;
	}

	CValueObject::CValueObject(const uint8_t * const value, int valuelen)
	{
		m_value.valuetype = BYTEARRAY;

		m_value.bytearray.datasize = valuelen;
		m_value.bytearray.data = std::tr1::shared_ptr<uint8_t>(new uint8_t[valuelen]);
		memcpy(m_value.bytearray.data.get(), value, valuelen);
	}

	emValueType CValueObject::GetType()
	{
		return m_value.valuetype;
	}

	bool CValueObject::GetBoolean()
	{
		return m_value.bvalue;
	}

	char CValueObject::GetChar()
	{
		return m_value.cvalue;
	}

	int16_t CValueObject::GetShort()
	{
		return m_value.svalue;
	}

	int32_t CValueObject::GetInt()
	{
		return m_value.ivalue;
	}

	int64_t CValueObject::GetLong()
	{
		return m_value.lvalue;
	}

	float CValueObject::GetFloat() 
	{
		return m_value.fvalue;
	}

	double CValueObject::GetDouble()
	{
		return m_value.dvalue;
	}

	std::string CValueObject::GetString()
	{
		return m_value.strvalue;
	}

	int CValueObject::GetByteLength()
	{
		return m_value.bytearray.datasize;
	}

    std::tr1::shared_ptr<uint8_t>& CValueObject::GetByteArray()
	{
        return m_value.bytearray.data;
	}

	void CValueObject::GetData(char* const data, int& datalen)
	{
		switch (m_value.valuetype)
		{
		case BOOLVALUE:
			{
				CBooleanValue::PackageBoolean(m_value.bvalue, data, datalen);
			}break;
		case CHARVALUE:
			{
				CCharValue::PackageChar(m_value.cvalue, data, datalen);
			}break;
		case SHORTVALUE:
			{
				CShortValue::PackageShort(m_value.svalue, data, datalen);
			}break;
		case INTVALUE:
			{
				CIntValue::PackageInt(m_value.ivalue, data, datalen);
			}break;
		case LONGVALUE:
			{
				CLongValue::PackageLong(m_value.lvalue, data, datalen);
			}break;
		case FLOATVALUE:
			{
				CFloatValue::PackageFloat(m_value.fvalue, data, datalen);
			}break;
		case DOUBLEVALUE:
			{
				CDoubleValue::PackageDouble(m_value.dvalue, data, datalen);
			}break;
		case STRINGVALUE:
			{
				CStringValue::PackageString(m_value.strvalue, data, datalen);
			}break;
		case BYTEARRAY:
			{
				CByteArray::PackageByteArray(m_value.bytearray, data, datalen);
			}
		default:
			break;
		}
	}

}
