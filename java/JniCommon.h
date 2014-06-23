#ifndef _JNICOMMON_
#define _JNICOMMON_
#include <jni.h>

extern jmethodID GetMethod(JNIEnv *env, 
					const char* clsname,
					const char* method, 
					const char* args);

extern jmethodID GetMethod2(JNIEnv *env, 
					 jclass cls,
					 const char* method, 
					 const char* args);

extern char* jstringTostring(JNIEnv* env, jstring jstr);
extern jstring stoJstring(JNIEnv* env, const char* pat);
extern uint32_t PthreadSelf();
extern uint32_t PthreadSelf();
extern void GetJniEnv(void **env);

extern JavaVM *jvm_;
extern JNIEnv *env_;
extern uint32_t thrd_id_;

#endif