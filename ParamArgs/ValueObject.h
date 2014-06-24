#ifndef _VALUE_OBJECT_
#define _VALUE_OBJECT_
#include <stdint.h>
#include <string>
#include <stdexcept>
#include <stdint.h>
#ifdef WIN32
#include <memory.h>
#else
#include <tr1/memory>
#endif
#include<memory>
#include "ProtocolCommon.h"

namespace yeguang
{
	typedef enum 
	{
		BOOLVALUE = 0,
		CHARVALUE,
		SHORTVALUE,
		INTVALUE,
		LONGVALUE,
		FLOATVALUE,
		DOUBLEVALUE,
		STRINGVALUE,
		BYTEARRAY,
		MAXVALUETYPE
	}emValueType;

	typedef struct tagByteArray
	{
		std::tr1::shared_ptr<uint8_t> data;
		int datasize;
	}TByteArray;

	typedef struct tagValueVar
	{
		emValueType valuetype;
		union 
		{
			bool    bvalue;
			char    cvalue;
			int16_t svalue;
			int32_t ivalue;
			int64_t lvalue;
			float   fvalue;
			double  dvalue;		
		};

        TByteArray bytearray;
		std::string  strvalue;
	}TValueVar;

	class PARAMPROTOCOL_API ValueObject
	{
	public:
		ValueObject()
		{

		}
		ValueObject(const char *const data, int datalen);

		ValueObject(bool value);
		ValueObject(char value);
		ValueObject(int16_t value);
		ValueObject(int value);
		ValueObject(int64_t value);
		ValueObject(float value);
		ValueObject(double value);
		ValueObject(const char * const value);
		ValueObject(const uint8_t * const value, int valuelen);

		~ValueObject();

		emValueType GetType();

		// 获取参数
		bool    GetBoolean();
		char    GetChar();
		int16_t GetShort();
		int32_t GetInt();
		int64_t GetLong();
		float   GetFloat();
		double  GetDouble();
		std::string  GetString();

		// 获取数组数据
		int GetByteLength();
        std::tr1::shared_ptr<uint8_t>& GetByteArray();

		// 获取数据
		void GetData(char* const data, int& datalen);

	private:
		TValueVar m_value;
	};
}

#endif
