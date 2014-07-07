#include <stdio.h>
#include "ParamSocket.h"
#include "ParamExecutor.h"
#include "TcpServer.h"
#include <string>
#include "public.h"
#include "vjoyinterface.h"

#define ROBUST

using namespace yeguang;

#define LEFT     0
#define RIGHT    1
#define UP       2
#define DOWN     3
#define SELECT   4
#define START    5
#define AKEY     6
#define BKEY     7
#define XKEY     8
#define YKEY     9

//UTF-8 GBK  
int UTF82GBK(char *szUtf8,char *szGbk,int Len)  
{  
	int n = MultiByteToWideChar(CP_UTF8, 0, szUtf8, -1, NULL, 0);  
	WCHAR * wszGBK = new WCHAR[sizeof(WCHAR) * n];  
	memset(wszGBK, 0, sizeof(WCHAR) * n);  
	MultiByteToWideChar(CP_UTF8, 0,szUtf8,-1, wszGBK, n);  

	n = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);  
	if (n > Len)  
	{  
		delete[]wszGBK;  
		return -1;  
	}  

	WideCharToMultiByte(CP_ACP,0, wszGBK, -1, szGbk, n, NULL, NULL);  

	delete[]wszGBK;  
	wszGBK = NULL;  

	return 0;  
} 

int Execute(uint32_t function_id, ParamArgs& args, void* context)
{
	//*
	int i = 0;

	for (i = 0; i < args.GetArgCount(); i++)
	{
		ValueObject vobj = args.GetArg(i);

		switch (vobj.GetType())
		{
		case yeguang::BOOLVALUE:
			{
				printf("boolean:%d\n", vobj.GetBoolean());
			}break;
		case yeguang::CHARVALUE:
			{
				printf("char:%d\n", vobj.GetChar());
			}break;
		case yeguang::SHORTVALUE:
			{
				printf("short:%d\n", vobj.GetShort());
			}break;
		case yeguang::INTVALUE:
			{
				printf("int:%d\n", vobj.GetInt());
			}break;
		case yeguang::LONGVALUE:
			{
				printf("long:%ld\n", vobj.GetLong());
			}break;
		case yeguang::FLOATVALUE:
			{
				printf("float:%f\n", vobj.GetFloat());
			}break;
		case yeguang::DOUBLEVALUE:
			{
				printf("double:%f\n", vobj.GetDouble());
			}break;
		case yeguang::STRINGVALUE:
			{
				char buffer[4096] = {0};
				UTF82GBK((char *)vobj.GetString().c_str(), buffer, sizeof(buffer));
				printf("string:%s\n", buffer);
			}break;
		case yeguang::BYTEARRAY:
			{
				int cnt = vobj.GetByteLength();
				for (int i = 0; i < cnt; i++)
				{
					printf("bytearray:%d\n", vobj.GetByteArray().get()[i]);
				}
			}break;
		default:
			break;
		}
	}
	//*/

	/*
	int keyvalue = args.GetArg(0).GetInt();
	int status = args.GetArg(1).GetInt();
	std::string strkey = "";

	switch (keyvalue)
	{
	case LEFT:
		strkey = "左";
		if (status == 0)
		{
			SetAxis(1, 1, HID_USAGE_X);
			SetAxis(0x4000, 1, HID_USAGE_Y);
		}
		else
		{
			SetAxis(0x4000, 1, HID_USAGE_X);
			SetAxis(0x4000, 1, HID_USAGE_Y);
		}
		break;
	case RIGHT:
		strkey = "右";
		if (status == 0)
		{
			SetAxis(0x8000, 1, HID_USAGE_X);
			SetAxis(0x4000, 1, HID_USAGE_Y);
		}
		else
		{
			SetAxis(0x4000, 1, HID_USAGE_X);
			SetAxis(0x4000, 1, HID_USAGE_Y);
		}
		break;
	case UP:
		strkey = "上";
		if (status == 0)
		{
			SetAxis(0x4000, 1, HID_USAGE_X);
			SetAxis(1, 1, HID_USAGE_Y);
		}
		else
		{
			SetAxis(0x4000, 1, HID_USAGE_X);
			SetAxis(0x4000, 1, HID_USAGE_Y);
		}
		break;
	case DOWN:
		strkey = "下";
		if (status == 0)
		{
			SetAxis(0x4000, 1, HID_USAGE_X);
			SetAxis(0x8000, 1, HID_USAGE_Y);
		}
		else
		{
			SetAxis(0x4000, 1, HID_USAGE_X);
			SetAxis(0x4000, 1, HID_USAGE_Y);
		}
		break;
	case SELECT:
		strkey = "选择";
		break;
	case START:
		strkey = "开始";
		break;
	case AKEY:
		strkey = "A";
		break;
	case BKEY:
		strkey = "B";
		break;
	case XKEY:
		strkey = "X";
		break;
	case YKEY:
		strkey = "Y";
		break;
	default:
		break;
	}

	int res = 0;

	if (strkey != "")
	{
		if (status == 0)
		{
		    printf("%s 按下\n", strkey.c_str());
			if (keyvalue > 3)
			{
				res = SetBtn(TRUE, 1, keyvalue - 3);
			}

			//Sleep(1);
		}
		else
		{
			printf("%s 放开\n", strkey.c_str());
			if (keyvalue > 3)
			{
			    res = SetBtn(FALSE, 1, keyvalue - 3);
			}
		}
	}

	//*/

	return 0;
}

int main()
{
	/*
	USHORT X, Y, Z, ZR, XR;							// Position of several axes
	JOYSTICK_POSITION	iReport;					// The structure that holds the full position data
	BYTE id=1;										// ID of the target vjoy device (Default is 1)
	UINT iInterface=1;								// Default target vJoy device
	BOOL ContinuousPOV=FALSE;						// Continuous POV hat (or 4-direction POV Hat)
	int count=0;

	// Get the driver attributes (Vendor ID, Product ID, Version Number)
	if (!vJoyEnabled())
	{
		printf("vJoy driver not enabled: Failed Getting vJoy attributes.\n");
		return -2;
	}
	else
	{
		printf("Vendor: %S\nProduct :%S\nVersion Number:%S\n", TEXT(GetvJoyManufacturerString()),  TEXT(GetvJoyProductString()), TEXT(GetvJoySerialNumberString()));
	}

	VjdStat status = GetVJDStatus(1);
	switch (status)
	{
	case VJD_STAT_OWN:
		printf("vJoy Device %d is already owned by this feeder\n", 1);
		break;
	case VJD_STAT_FREE:
		printf("vJoy Device %d is free\n", 1);
		break;
	case VJD_STAT_BUSY:
		printf("vJoy Device %d is already owned by another feeder\nCannot continue\n", 1);
		return -3;
	case VJD_STAT_MISS:
		printf("vJoy Device %d is not installed or disabled\nCannot continue\n", 1);
		return -4;
	default:
		printf("vJoy Device %d general error\nCannot continue\n", 1);
		return -1;
	};

	// Check which axes are supported
	int AxisX  = GetVJDAxisExist(1, HID_USAGE_X);
	int AxisY  = GetVJDAxisExist(1, HID_USAGE_Y);
	int AxisZ  = GetVJDAxisExist(1, HID_USAGE_Z);
	int AxisRX = GetVJDAxisExist(1, HID_USAGE_RX);
	int AxisRZ = GetVJDAxisExist(1, HID_USAGE_RZ);
	// Get the number of buttons and POV Hat switchessupported by this vJoy device
	int nButtons  = GetVJDButtonNumber(1);
	int ContPovNumber = GetVJDContPovNumber(1);
	int DiscPovNumber = GetVJDDiscPovNumber(1);

	// Print results
	printf("\nvJoy Device %d capabilities:\n", 1);
	printf("Numner of buttons\t\t%d\n", nButtons);
	printf("Numner of Continuous POVs\t%d\n", ContPovNumber);
	printf("Numner of Descrete POVs\t\t%d\n", DiscPovNumber);
	printf("Axis X\t\t%s\n", AxisX?"Yes":"No");
	printf("Axis Y\t\t%s\n", AxisX?"Yes":"No");
	printf("Axis Z\t\t%s\n", AxisX?"Yes":"No");
	printf("Axis Rx\t\t%s\n", AxisRX?"Yes":"No");
	printf("Axis Rz\t\t%s\n", AxisRZ?"Yes":"No");



	// Acquire the target
	if ((status == VJD_STAT_OWN) || ((status == VJD_STAT_FREE) && (!AcquireVJD(1))))
	{
		printf("Failed to acquire vJoy device number %d.\n", 1);
		return -1;
	}
	else
	{
		printf("Acquired: vJoy device number %d.\n", 1);
	}



	printf("\npress enter to stat feeding");
	//getchar();

	X = 20;
	Y = 30;
	Z = 40;
	XR = 60;
	ZR = 80;

	long value = 0;

	ResetVJD(1);

	int res = 0;

	while(1)
	{
		// Set position of 4 axes
		//res = SetAxis(X, 1, HID_USAGE_X);
		//res = SetAxis(Y, 1, HID_USAGE_Y);
		//res = SetAxis(Z, 1, HID_USAGE_Z);
		//res = SetAxis(XR, 1, HID_USAGE_RX);
		//res = SetAxis(ZR, 1, HID_USAGE_RZ);

		// Press/Release Buttons
		res = SetBtn(TRUE, iInterface, count%9);
		res = SetBtn(FALSE, iInterface, 1+count%9);

		// If Continuous POV hat switches installed - make them go round
		// For high values - put the switches in neutral state
		if (ContPovNumber)
		{
			if ((count*70) < 30000)
			{
				res = SetContPov((DWORD)(count*70)		, iInterface, 1);
				res = SetContPov((DWORD)(count*70)+2000	, iInterface, 2);
				res = SetContPov((DWORD)(count*70)+4000	, iInterface, 3);
				res = SetContPov((DWORD)(count*70)+6000	, iInterface, 4);
			}
			else
			{
				res = SetContPov(-1 , iInterface, 1);
				res = SetContPov(-1 , iInterface, 2);
				res = SetContPov(-1 , iInterface, 3);
				res = SetContPov(-1 , iInterface, 4);
			};
		};

		// If Discrete POV hat switches installed - make them go round
		// From time to time - put the switches in neutral state
		if (DiscPovNumber)
		{
			if (count < 550)
			{
				SetDiscPov(((count/20) + 0)%4, iInterface, 1);
				SetDiscPov(((count/20) + 1)%4, iInterface, 2);
				SetDiscPov(((count/20) + 2)%4, iInterface, 3);
				SetDiscPov(((count/20) + 3)%4, iInterface, 4);
			}
			else
			{
				SetDiscPov(-1, iInterface, 1);
				SetDiscPov(-1, iInterface, 2);
				SetDiscPov(-1, iInterface, 3);
				SetDiscPov(-1, iInterface, 4);
			};
		};

		Sleep(300);
		X+=150;
		Y+=250;
		Z+=350;
		ZR-=200;
		count++;
		if (count > 640) count=0;
	} // While
	*/

	ParamExecutor::Instance()->AddRecvCB("ime", Execute, NULL);

	TcpServer server;

	server.CreateServer(50000);

    getchar();

	server.DestroyServer();
	return 0;
}