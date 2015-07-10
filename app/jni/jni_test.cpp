#include <jni.h>
#include <stdio.h>
#include "ann_lib.h"
#include "com_example_annteng_myapplicationonmac_DisplayMessageActivity.h"

JNIEXPORT jstring JNICALL Java_com_example_annteng_myapplicationonmac_DisplayMessageActivity_helloString(
		JNIEnv* env, jobject obj, jstring str){
	const char* toWhat = env->GetStringUTFChars(str, JNI_FALSE);
	char hello[80];
	sprintf(hello,"Hello, aasdb %s!", toWhat);
	//AnnTestClass aa(hello);
	/*const char* outfilename = env->GetStringUTFChars(p_outfilename, JNI_FALSE);
	const char* infilename = env->GetStringUTFChars(p_infilename, JNI_FALSE);

	aa.DecodeVideo(outfilename, infilename);*/
	return env->NewStringUTF(hello);
}

JNIEXPORT jstring JNICALL Java_com_example_annteng_myapplicationonmac_DisplayMessageActivity_decodeVideoFF
                            (JNIEnv *env, jobject obj, jstring p_outfilename, jstring p_infilename){
	//const char* toWhat = env->GetStringUTFChars(str, JNI_FALSE);
	//char hello[80];
	//sprintf(hello,"Hello, aasdb %s!", toWhat);

	const char* outfilename = env->GetStringUTFChars(p_outfilename, JNI_FALSE);
	const char* infilename = env->GetStringUTFChars(p_infilename, JNI_FALSE);

    AnnTestClass aa;
	aa.DecodeVideo(outfilename, infilename);
	return env->NewStringUTF("ok");
}

