/* DO NOT EDIT THIS FILE - it is machine generated */
#define DLLEXPORT
#include "com_yeguang_paramprotocol_ParamSocket.h"
#include "ParamSocket.h"
#include "JniCommon.h"
#include "ValueObject.h"
#include "ParamExecutor.h"

//////////////////////////////////////////////////////////////////////////
static jobject param_socket_ = NULL;

yeguang::ParamSocket *GetSocket(JNIEnv *env, jobject obj)
{
	// call Lcom/yeguang/paramprotocol/ParamSocket; getSock
	jmethodID mid = GetMethod(env, "com/yeguang/paramprotocol/ParamSocket",
		"getSock", "()J");

	yeguang::ParamSocket *sock = (yeguang::ParamSocket *)env->CallLongMethod(obj, mid);

	return sock;
}

int GetArgsCount(JNIEnv *env, jobject args)
{
	jmethodID mid = GetMethod(env, "com/yeguang/paramprotocol/ParamArgs",
		"getCount", "()I");

	return env->CallIntMethod(args, mid);
}

void AddArg(JNIEnv *env, jobject args, yeguang::ValueObject& valueobj)
{
	jclass clazz_arg = env->FindClass("Lcom/yeguang/paramprotocol/ParamArg;");
	jmethodID mid_arg = NULL;
	jobject argobj = NULL;

	yeguang::emValueType type = valueobj.GetType();

	switch(type)
	{
	case yeguang::BOOLVALUE:
		{
			mid_arg = env->GetMethodID(clazz_arg, "<init>", "(Z)V");
			argobj = env->NewObject(clazz_arg, mid_arg, (jboolean)valueobj.GetBoolean());
		}break;
	case yeguang::CHARVALUE:
		{
			mid_arg = env->GetMethodID(clazz_arg, "<init>", "(C)V");
			argobj = env->NewObject(clazz_arg, mid_arg, (jchar)valueobj.GetChar());
		}break;
	case yeguang::SHORTVALUE:
		{
			mid_arg = env->GetMethodID(clazz_arg, "<init>", "(S)V");
			argobj = env->NewObject(clazz_arg, mid_arg, (jshort)valueobj.GetShort());
		}break;
	case yeguang::INTVALUE:
		{
			mid_arg = env->GetMethodID(clazz_arg, "<init>", "(I)V");
			argobj = env->NewObject(clazz_arg, mid_arg, (jint)valueobj.GetInt());
		}break;
	case yeguang::LONGVALUE:
		{
			mid_arg = env->GetMethodID(clazz_arg, "<init>", "(J)V");
			argobj = env->NewObject(clazz_arg, mid_arg, (jlong)valueobj.GetLong());
		}break;
	case yeguang::FLOATVALUE:
		{
			mid_arg = env->GetMethodID(clazz_arg, "<init>", "(F)V");
			argobj = env->NewObject(clazz_arg, mid_arg, (jfloat)valueobj.GetFloat());
		}break;
	case yeguang::DOUBLEVALUE:
		{
			mid_arg = env->GetMethodID(clazz_arg, "<init>", "(D)V");
			argobj = env->NewObject(clazz_arg, mid_arg, (jfloat)valueobj.GetDouble());
		}break;
	case yeguang::STRINGVALUE:
		{
			mid_arg = env->GetMethodID(clazz_arg, "<init>", "(Ljava/lang/String;)V");
			jstring strtmp = stoJstring(env, valueobj.GetString().c_str());
			argobj = env->NewObject(clazz_arg, mid_arg, strtmp);
		}break;
	case yeguang::BYTEARRAY:
		{
			mid_arg = env->GetMethodID(clazz_arg, "<init>", "([B)V");
			jbyteArray byte_array = env->NewByteArray(valueobj.GetByteLength());
			env->SetByteArrayRegion(byte_array, 0, valueobj.GetByteLength(), 
				(jbyte *)valueobj.GetByteArray().get());
			argobj = env->NewObject(clazz_arg, mid_arg, byte_array);
		}break;
	default:
		break;
	}

	if(argobj != NULL)
	{
		jmethodID mid = GetMethod(env, "com/yeguang/paramprotocol/ParamArgs",
			"AddArgs", "(Lcom/yeguang/paramprotocol/ParamArg;)V");

		env->CallVoidMethod(args, mid, argobj);
	}
}

bool GetArg(JNIEnv *env, jobject args, int index, yeguang::ValueObject& valueobj)
{
	bool res = false;

	jmethodID mid = GetMethod(env, "com/yeguang/paramprotocol/ParamArgs",
		"getArg", "(I)Lcom/yeguang/paramprotocol/ParamArg;");

	jobject arg = env->CallObjectMethod(args, mid, index);

	mid = GetMethod(env, "com/yeguang/paramprotocol/ParamArg",
		"getType", "()I");

	int type = env->CallIntMethod(arg, mid);

	switch(type)
	{
	case yeguang::BOOLVALUE:
		{
			mid = GetMethod(env, "com/yeguang/paramprotocol/ParamArg",
				"getBoolean", "()Z");

			jboolean tmpvalue = env->CallBooleanMethod(arg, mid);

			valueobj = yeguang::ValueObject((bool)tmpvalue);
			res = true;
		}break;
	case yeguang::CHARVALUE:
		{
			mid = GetMethod(env, "com/yeguang/paramprotocol/ParamArg",
				"getChar", "()C");

			jchar tmpvalue = env->CallCharMethod(arg, mid);

			valueobj = yeguang::ValueObject((char)tmpvalue);
			res = true;
		}break;
	case yeguang::SHORTVALUE:
		{
			mid = GetMethod(env, "com/yeguang/paramprotocol/ParamArg",
				"getShort", "()S");

			jshort tmpvalue = env->CallShortMethod(arg, mid);

			valueobj = yeguang::ValueObject(tmpvalue);
			res = true;
		}break;
	case yeguang::INTVALUE:
		{
			mid = GetMethod(env, "com/yeguang/paramprotocol/ParamArg",
				"getInt", "()I");

			jint tmpvalue = env->CallIntMethod(arg, mid);

			valueobj = yeguang::ValueObject(tmpvalue);
			res = true;
		}break;
	case yeguang::LONGVALUE:
		{
			mid = GetMethod(env, "com/yeguang/paramprotocol/ParamArg",
				"getLong", "()J");

			jlong tmpvalue = env->CallLongMethod(arg, mid);

			valueobj = yeguang::ValueObject(tmpvalue);
			res = true;
		}break;
	case yeguang::FLOATVALUE:
		{
			mid = GetMethod(env, "com/yeguang/paramprotocol/ParamArg",
				"getFloat", "()F");

			jfloat tmpvalue = env->CallFloatMethod(arg, mid);

			valueobj = yeguang::ValueObject(tmpvalue);
			res = true;
		}break;
	case yeguang::DOUBLEVALUE:
		{
			mid = GetMethod(env, "com/yeguang/paramprotocol/ParamArg",
				"getDouble", "()D");

			jdouble tmpvalue = env->CallDoubleMethod(arg, mid);

			valueobj = yeguang::ValueObject(tmpvalue);
			res = true;
		}break;
	case yeguang::STRINGVALUE:
		{
			mid = GetMethod(env, "com/yeguang/paramprotocol/ParamArg",
				"getString", "()Ljava/lang/String;");

			jstring tmpvalue = (jstring)env->CallObjectMethod(arg, mid);

			char *name = jstringTostring(env, tmpvalue);
			valueobj = yeguang::ValueObject(name);
			free(name);

			res = true;
		}break;
	case yeguang::BYTEARRAY:
		{
			mid = GetMethod(env, "com/yeguang/paramprotocol/ParamArg",
				"getByteArray", "()[B");

			jbyteArray tmpvalue = (jbyteArray)env->CallObjectMethod(arg, mid);

			jbyte *data = (jbyte*)env->GetByteArrayElements(tmpvalue, 0);
			jsize len = env->GetArrayLength(tmpvalue);
			valueobj = yeguang::ValueObject((uint8_t*)data, len);
			env->ReleaseByteArrayElements(tmpvalue, data, 0);

			res = true;
		}break;
	default:
		break;
	}

	return res;
}

int JniSendCallback(const char * const data, int data_len, void* context)
{
	//printf("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

	JNIEnv *env = NULL;
	GetJniEnv((void **)&env);

	//printf("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

	jobject obj = (jobject)context;

	//printf("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

	jmethodID mid = GetMethod(env, "com/yeguang/paramprotocol/ParamSocket",
		"SendCallback", "([B)V");

	//printf("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

	jbyteArray byte_array = env->NewByteArray(data_len);

	//printf("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

	env->SetByteArrayRegion(byte_array, 0, data_len, (jbyte *)data);

	//printf("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

	//printf("env:%p, obj:%p, mid:%p\n", env, obj, mid);

	env->CallVoidMethod(obj, mid, byte_array);

	//printf("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);
	
	ReleaseJniEnv();
	return 0;
}

int JniRecvCallback(uint32_t function_id, yeguang::ParamArgs& args, void* context)
{
	dprint("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);
	JNIEnv *env;
	GetJniEnv((void **)&env);

	const yeguang::TParamInfo *info = yeguang::ParamExecutor::Instance()->GetParamInfo(function_id);

	dprint("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

	if(info != NULL)
	{
		jobject execobj = (jobject)context;

		jclass clazz_args = env->FindClass("Lcom/yeguang/paramprotocol/ParamArgs;");
		jmethodID mid_args = env->GetMethodID(clazz_args, "<init>", "()V");
		jobject argsobj = env->NewObject(clazz_args, mid_args);

		dprint("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

		int cnt = args.GetArgCount();

		for (int i = 0; i < cnt; i++)
		{
			AddArg(env, argsobj, args[i]);
		}

		jmethodID mid = GetMethod(env, "com/yeguang/paramprotocol/ParamSocket",
			"Execute", "(ILcom/yeguang/paramprotocol/ParamArgs;)V");   

		dprint("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

		dprint("env:%p execobj:%p mid:%p function_id:%X argsobj:%p\n", env, execobj, mid, function_id, argsobj);

		dprint("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

		env->CallVoidMethod(execobj, mid, function_id, argsobj);

		dprint("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);
	}

	dprint("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

	ReleaseJniEnv();
	return 0;
}

int JniCheckCallback(void* context)
{
	JNIEnv *env = NULL;
	GetJniEnv((void **)&env);

	jobject obj = (jobject)context;

	jmethodID mid = GetMethod(env, "com/yeguang/paramprotocol/ParamSocket",
		"CheckCallback", "()V");

	env->CallLongMethod(obj, mid);

	ReleaseJniEnv();
	return 0;
}


//////////////////////////////////////////////////////////////////////////


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void *reserved) //这是JNI_OnLoad的声明，必须按照这样的方式声明
{
	jvm_ = vm;

	thrd_id_ = PthreadSelf();

	if(vm->GetEnv((void**)&env_, JNI_VERSION_1_4) != JNI_OK) //从JavaVM获取JNIEnv，一般使用1.4的版本
	    return -1;	

	//printf("env:%p\n", env_);

	return JNI_VERSION_1_4; //这里很重要，必须返回版本，否则加载会失败。
}

/*
 * Class:     com_yeguang_paramprotocol_ParamSocket
 * Method:    Create
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_yeguang_paramprotocol_ParamSocket_Create
  (JNIEnv *env, jobject obj)
{
	if(param_socket_)
	{
		return;
	}

	yeguang::ParamSocket *sock = yeguang::ParamSocket::Create();

	param_socket_ = env->NewGlobalRef(obj);  

	sock->SetSendCB(JniSendCallback, param_socket_);
	sock->SetCheckCB(JniCheckCallback, param_socket_);
	sock->SetRecvCB(JniRecvCallback, param_socket_);

	// call Lcom/yeguang/paramprotocol/ParamSocket; setSock
	jmethodID mid = GetMethod(env, "com/yeguang/paramprotocol/ParamSocket",
		"setSock", "(J)V");

	if(mid == NULL)
	{
	    return;
	}

	env->CallVoidMethod(obj, mid, (jlong)sock);
}

/*
 * Class:     com_yeguang_paramprotocol_ParamSocket
 * Method:    Destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_yeguang_paramprotocol_ParamSocket_Destroy
	(JNIEnv *env, jobject obj)
{
	if (param_socket_ == NULL)
	{
		return;
	}

	yeguang::ParamSocket *sock = GetSocket(env, obj);

	if (sock != NULL)
	{
		delete sock;
		sock = NULL;
	}
}


/*
 * Class:     com_yeguang_paramprotocol_ParamSocket
 * Method:    CheckConn
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_yeguang_paramprotocol_ParamSocket_CheckConn
  (JNIEnv *env, jobject obj)
{
	if (param_socket_ == NULL)
	{
		return;
	}

	yeguang::ParamSocket *sock = GetSocket(env, obj);

	if (sock == NULL)
	{
		return;
	}

	sock->CheckConn();
}


/*
 * Class:     com_yeguang_paramprotocol_ParamSocket
 * Method:    InputData
 * Signature: ([BI)V
 */
JNIEXPORT void JNICALL Java_com_yeguang_paramprotocol_ParamSocket_InputData
    (JNIEnv *env, jclass cls, jbyteArray dataarry, jint len)
{
	dprint("-datalen:%d, %d---\n", len, env->GetArrayLength(dataarry));
	if (param_socket_ == NULL)
	{
		return;
	}

	yeguang::ParamSocket *sock = GetSocket(env, param_socket_);

	if (sock == NULL)
	{
		return;
	}

	jbyte *data = (jbyte*)env->GetByteArrayElements(dataarry, NULL);
	sock->InputData((char *)data, len);
	env->ReleaseByteArrayElements(dataarry, data, 0);
}

/*
 * Class:     com_yeguang_paramprotocol_ParamSocket
 * Method:    CallFunction
 * Signature: (Ljava/lang/String;Lcom/yeguang/paramprotocol/ParamArgs;)V
 */
JNIEXPORT void JNICALL Java_com_yeguang_paramprotocol_ParamSocket_CallFunction
  (JNIEnv *env, jobject obj, jstring funname, jobject args)
{
	if (param_socket_ == NULL)
	{
		return;
	}

	//printf("-%s---%p\n", __FUNCTION__, obj);

	//printf("%s %d\n", __FILE__, __LINE__);

	yeguang::ParamSocket *sock = GetSocket(env, obj);

	//printf("%s %d\n", __FILE__, __LINE__);

	if (sock == NULL)
	{
		return;
	}

	//printf("%s %d\n", __FILE__, __LINE__);

	char *name = jstringTostring(env, funname);
	std::string strname = name;
	free(name);

	//printf("%s %d\n", __FILE__, __LINE__);

	int count = GetArgsCount(env, args);

	int i = 0;
	yeguang::ParamArgs params;	

	for (i = 0; i < count; i++)
	{
		yeguang::ValueObject tmpvalue;
	    if(GetArg(env, args, i, tmpvalue))
		{
			params.AddArg(tmpvalue);
		}
	}

	//printf("%s %d\n", __FILE__, __LINE__);
	sock->CallFunction(strname, params);
}

/*
 * Class:     com_yeguang_paramprotocol_ParamSocket
 * Method:    SaveFunction
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_yeguang_paramprotocol_ParamSocket_SaveFunction
  (JNIEnv *env, jobject obj, jstring funname)
{
	if (param_socket_ == NULL)
	{
		return -1;
	}

	//printf("-%s---%p\n", __FUNCTION__, obj);

	char *name = jstringTostring(env, funname);
	int res = yeguang::ParamExecutor::Instance()->AddRecvCB(name, JniRecvCallback, param_socket_);
	free(name);

	//printf("----%p, function:%X\n", obj, res);

	return res;
}
