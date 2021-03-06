#include "JniCommon.h"
#include <string.h>
#include <malloc.h>

JavaVM *jvm_ = NULL;
JNIEnv *env_ = NULL;
uint32_t thrd_id_ = 0;

/*
 * Class:     com_yeguang_paramprotocol_ParamSocket
 * Method:    Create
 * Signature: ()V
 */
jmethodID GetMethod(JNIEnv *env, 
					const char* clsname,
					const char* method, 
					const char* args)
{	
	jclass cls = env->FindClass(clsname);

	if(cls == NULL)
	{
		return NULL;
	}

	return env->GetMethodID(cls, method, args);
}

jmethodID GetMethod2(JNIEnv *env, 
					jclass cls,
					const char* method, 
					const char* args)
{
	if(cls == NULL)
	{
		return NULL;
	}

	return env->GetMethodID(cls, method, args);
}

//jstring to char*
char* jstringTostring(JNIEnv* env, jstring jstr)
{        
	char* rtn = NULL;
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("utf-8");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0)
	{
		rtn = (char*)malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	env->ReleaseByteArrayElements(barr, ba, 0);
	return rtn;
}

//char* to jstring
jstring stoJstring(JNIEnv* env, const char* pat)
{
	jclass strClass = env->FindClass("java/lang/String");
	jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	jbyteArray bytes = env->NewByteArray(strlen(pat));
	env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
	jstring encoding = env->NewStringUTF("utf-8");
	return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}

uint32_t PthreadSelf()
{
#ifdef WIN32
	return::GetCurrentThreadId();
#else
	return pthread_self();
#endif
}

bool GetJniEnv(void **env)
{
	int status = 0;
	status = jvm_->GetEnv(env,JNI_VERSION_1_4);
	if(status < 0){
#ifdef ANDROID
		jint res = jvm_->AttachCurrentThread((JNIEnv**)env, NULL);
#else
		jint res = jvm_->AttachCurrentThread(env, NULL);
#endif	
		return true;
	}
	return false;
}

void ReleaseJniEnv()
{
	jvm_->DetachCurrentThread();
}
