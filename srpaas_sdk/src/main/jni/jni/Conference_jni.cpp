#define TAG "COnference_jni"
#include <jni.h>
#include <android/log.h>
#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include<iostream>
#include <signal.h>
#include "Conference_jni.h"
#include "DataProcess.h"
#include "srengine_api.h"
#include "Log.h"
#define LOG_TAG "COnference_jni----->"
DataProcess *api = 0;
JavaVM *gs_jvm = 0;
using namespace std;

jclass Callback_class = NULL;
jclass stringClass = NULL;
jclass info_class = NULL;
jclass class_ArrayList = NULL;
jclass VoiceActiveInfo_class = NULL;

int w = 0;
int h = 0;
jbyteArray yByte = NULL;
jbyteArray uByte = NULL;
jbyteArray vByte = NULL;

struct sigaction* old_sa;
void InitCrashReport() {
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "异常捕获。。。");
	struct sigaction handler;
	memset(&handler, 0, sizeof(struct sigaction));
	handler.sa_sigaction = android_sigaction;
	handler.sa_flags = SA_RESETHAND;
#define CATCHSIG(X) sigaction(X, &handler, &old_sa[X])
	CATCHSIG(SIGTRAP);
	CATCHSIG(SIGKILL);
	CATCHSIG(SIGKILL);
	CATCHSIG(SIGILL);
	CATCHSIG(SIGABRT);
	CATCHSIG(SIGBUS);
	CATCHSIG(SIGFPE);
	CATCHSIG(SIGSEGV);
	CATCHSIG(SIGSTKFLT);
	CATCHSIG(SIGPIPE);
}
void android_sigaction(int signal, siginfo_t *info, void *reserved) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (!env) {
		return;
	}
	if (Callback_class != NULL) {
		jmethodID qttCallback_method = env->GetMethodID(Callback_class,
				"<init>", "()V");
		jobject obj_qtt = env->NewObject(Callback_class, qttCallback_method,
				"");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"getJNIExcaption", "()V");
		env->CallVoidMethod(obj_qtt, gJinMethod);
		env->DeleteLocalRef(obj_qtt);
	}
	old_sa[signal].sa_handler(signal);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *ajvm, void *reserved) {
	gs_jvm = ajvm;
//	InitCrashReport();
	JNIEnv* env = NULL;
	if ((gs_jvm)->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
		Log("COnference_jni:JNI_OnLoad..not..JNI_VERSION_1_4.");
		return -1;
	}
	Log("COnference_jni:JNI_OnLoad....");
	return JNI_VERSION_1_4;;
}
class Conference_jni {
public:
	Conference_jni(JNIEnv *env) {
		stringClass = (jclass) env->NewGlobalRef(
				env->FindClass("java/lang/String"));
		class_ArrayList = (jclass) env->NewGlobalRef(
				env->FindClass("java/util/ArrayList"));
		Callback_class = (jclass) env->NewGlobalRef(
				env->FindClass("org/suirui/srpaas/jni/CallBack"));
		info_class = (jclass) env->NewGlobalRef(
				env->FindClass("org/suirui/srpaas/entry/TermInfo"));

		VoiceActiveInfo_class = (jclass) env->NewGlobalRef(
				env->FindClass("org/suirui/srpaas/entry/VoiceActiveInfo"));

	}
	~Conference_jni() {
	}

};
extern "C" {

void ThrowJNI(JNIEnv *env, const char * str) {
	jthrowable exc = env->ExceptionOccurred();
	if (exc) {
		jclass newExcCls;
		env->ExceptionDescribe();
		env->ExceptionClear();
		newExcCls = env->FindClass("org/suirui/splansdk/jni/ThrowJNIException");
		if (newExcCls == NULL) {
			return;
		}
		env->ThrowNew(newExcCls, str);
	}
}

//jstring to string
string jstringTostring(JNIEnv* env, jstring jstr) {
	char* rtn = NULL;
	if (stringClass != NULL && stringClass != 0) {
		jstring strencode = env->NewStringUTF("utf-8");
		jmethodID mid = env->GetMethodID(stringClass, "getBytes",
				"(Ljava/lang/String;)[B");
		jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid,
				strencode);
		env->DeleteLocalRef(strencode);
		jsize alen = env->GetArrayLength(barr);
		jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
		if (alen > 0) {
			rtn = (char*) malloc(alen + 1); //new   char[alen+1];
			memcpy(rtn, ba, alen);
			rtn[alen] = 0;
		} else {
			return "";
		}
		env->ReleaseByteArrayElements(barr, ba, 0);
		string stemp(rtn);
		free(rtn);
		return stemp;
	}
}

//jstring to char*
char* jstringTochar(JNIEnv* env, jstring jstr) {
	char* rtn = NULL;
	if (stringClass != NULL && stringClass != 0) {
		jstring strencode = env->NewStringUTF("utf-8");
		jmethodID mid = env->GetMethodID(stringClass, "getBytes",
				"(Ljava/lang/String;)[B");
		jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid,
				strencode);
		env->DeleteLocalRef(strencode);
		jsize alen = env->GetArrayLength(barr);
		jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
		if (alen > 0) {
			rtn = (char*) malloc(alen + 1);
			memcpy(rtn, ba, alen);
			rtn[alen] = 0;
		}
		env->ReleaseByteArrayElements(barr, ba, 0);
		return rtn;
	}
}
//const char* to jstring
jstring chartoJstring(JNIEnv* env, const char* pat) {
	if (stringClass != NULL && stringClass != 0) {
		jmethodID ctorID = env->GetMethodID(stringClass, "<init>",
				"([BLjava/lang/String;)V");
		if (pat != NULL) {
			jbyteArray bytes = env->NewByteArray(strlen(pat));
			env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*) pat);
			jstring encoding = env->NewStringUTF("utf-8");
			return (jstring) env->NewObject(stringClass, ctorID, bytes,
					encoding);
		} else {
			return NULL;
		}
	}

}
int mystrlen(unsigned char* str) {
	int i = -1;
	while (i++, '\0' != str[i])
		;
	return i;
}

int strlens(unsigned char* str) {

}
jbyteArray byteToArray(JNIEnv *env, unsigned char* buf) {
	int len = mystrlen(buf);
	jbyteArray array = env->NewByteArray(len);
	env->SetByteArrayRegion(array, 0, len, reinterpret_cast<jbyte*>(buf));
//	jbyte *by = (jbyte*)pData;
//	jbyteArray jarray = env->NewByteArray(nOutSize);
//	env->SetByteArrayRegin(jarray, 0, nOutSize, by);

	return array;
}
//jbyteArray getByteToArray(JNIEnv *env, unsigned char* ybuf, int len,
//		jbyteArray array) {
//	env->SetByteArrayRegion(array, 0, len, reinterpret_cast<jbyte*>(ybuf));
//	return array;
//}

jbyteArray getByteToArray(JNIEnv *env, unsigned char* ybuf, int len) {
	jbyteArray array = env->NewByteArray(len);
	env->SetByteArrayRegion(array, 0, len, reinterpret_cast<jbyte*>(ybuf));
	return array;
}

unsigned char* arrayToChar(JNIEnv *env, jbyteArray array) {
	int len = env->GetArrayLength(array);
	unsigned char* buf = new unsigned char[len];
	env->GetByteArrayRegion(array, 0, len, reinterpret_cast<jbyte*>(buf));

	return buf;
}
/************************
 * 初始化sdk,启动程序时候调用
 * 作    者:licui
 * **********************/

JNIEXPORT jobject JNICALL Java_org_suirui_srpaas_jni_JniNative_allocNativeBuffer(
		JNIEnv *env, jclass jcls, jlong size) {
	void* buffer = malloc(size);
	jobject directBuffer = env->NewDirectByteBuffer(buffer, size);
	jobject globalRef = env->NewGlobalRef(directBuffer);
	return globalRef;

}
JNIEXPORT void JNICALL Java_org_suirui_srpaas_jni_JniNative_freeNativeBuffer(
		JNIEnv *env, jclass jcls, jobject globalRef) {
	void *buffer = env->GetDirectBufferAddress(globalRef);
	env->DeleteLocalRef(globalRef);
	free(buffer);
}

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_InitSDK(JNIEnv *env,
		jclass jcls, jboolean debug_en, jstring pLogPath) {
	env->GetJavaVM(&gs_jvm);
#if defined(LOG_JNI)
	Log("COnference_jni:InitSDK.....");
#endif
	Conference_jni* ldata = new Conference_jni(env);
	api = new DataProcess();
	char* logPathChar = NULL;
	if (pLogPath != NULL)
		logPathChar = jstringTochar(env, pLogPath);
	return api->initSdk(debug_en, logPathChar);
}
/************************
 * 退出应用时候调用
 * 作    者:licui
 * **********************/
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_UnInitSDK(
		JNIEnv *env, jclass jcls) {
	env->DeleteGlobalRef(Callback_class);
	env->DeleteGlobalRef(stringClass);
	env->DeleteGlobalRef(info_class);
	env->DeleteGlobalRef(class_ArrayList);
	env->DeleteGlobalRef(VoiceActiveInfo_class);
	return api->UnInitSDK();
}

/************************
 * 	函数功能：初始化MC
 输入参数：const char	*mc_ip  mc地址  const  int	mc_port 端口号    listenport: 本地监听(填0)
 返回值: 0 成功  非0 失败
 * 作    者:licui
 * **********************/
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestInitMC(
		JNIEnv *env, jclass jcls, jstring mc_adress, jint relaymc_nsize,
		jint termUId, jlong mcuport) {
#if defined(LOG_JNI)
	Log("COnference_jni:requestInitMC..mcuport:%llu",mcuport);
#endif
	char* mc_adress_c = NULL;
	if (mc_adress != NULL)
		mc_adress_c = jstringTochar(env, mc_adress);
	UINT64 mcuPorts = (UINT64) mcuport;
	return api->requestInitMC(mc_adress_c, relaymc_nsize, termUId, mcuPorts);
}

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestInitMCArray(
		JNIEnv *env, jclass jcls, jobject mcAdressList, jint relaymc_nsize,
		jint termUId, jlong mcuport) {
#if defined(LOG_JNI)
	Log("COnference_jni:requestInitMC..mcuport:%llu",mcuport);
#endif

	int i;
	jclass cls_arraylist = env->GetObjectClass(mcAdressList);
	jmethodID arraylist_get = env->GetMethodID(cls_arraylist, "get",
			"(I)Ljava/lang/Object;");
	jmethodID arraylist_size = env->GetMethodID(cls_arraylist, "size", "()I");
	jint len = env->CallIntMethod(mcAdressList, arraylist_size);
	char *prelayInfo[len];
	for (i = 0; i < len; i++) {
		jobject obj_videoParam = env->CallObjectMethod(mcAdressList,
				arraylist_get, i);
		jclass videoParam = env->GetObjectClass(obj_videoParam);
		jmethodID get_Address = env->GetMethodID(videoParam, "getAddress",
				"()Ljava/lang/String;");
		jstring address = (jstring) env->CallObjectMethod(obj_videoParam,
				get_Address);
		if (address != NULL) {
			char* address_c = jstringTochar(env, address);
			prelayInfo[i] = address_c;
		}
	}
	UINT64 mcuPorts = (UINT64) mcuport;
	return api->requestInitMCArray((const char **) prelayInfo, len, termUId,
			mcuPorts);
}

/**
 * 注销mcu初始化
 */
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestUnInitMC(
		JNIEnv *env, jclass jcls) {
#if defined(LOG_JNI)
	Log("COnference_jni:requestUnInitMC");
#endif
	return api->requestUnInitMC();
}
/**
 * 加入会议
 */
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestJoinConference(
		JNIEnv *env, jclass jcls, jlong conf_id, jstring password,
		jstring term_name, jint term_id, jobject local_wnd, jboolean isMuted,
		jboolean isCameraOn) {
#if defined(LOG_JNI)
	Log("COnference_jni:requestJoinConference..conf_id:%llu",conf_id);
#endif
	void *local = (void *) (&local_wnd);
	char* password_c = NULL;
	if (password != NULL)
		password_c = jstringTochar(env, password);
	char* term_name_c = NULL;
	if (term_name != NULL)
		term_name_c = jstringTochar(env, term_name);
	UINT64 confId = (UINT64) conf_id;
	return api->requestJoinConference(confId, password_c, term_name_c, term_id,
			local, isMuted, isCameraOn);

}
/**
 * 退出会议
 */
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestExitConference(
		JNIEnv *env, jclass jcls, jlong conf_id, jint term_id,
		jstring exit_reason, jboolean isEnd) {
#if defined(LOG_JNI)
	Log("COnference_jni:requestExitConference..");
#endif
	char* exit_reason_c = NULL;
	if (exit_reason != NULL)
		exit_reason_c = jstringTochar(env, exit_reason);
	jint end = api->requestExitConference(conf_id, term_id, exit_reason_c,
			isEnd);

//	//释放
//	if (yByte != NULL)
//		env->DeleteGlobalRef(yByte);
//	if (uByte != NULL)
//		env->DeleteGlobalRef(uByte);
//	if (vByte != NULL)
//		env->DeleteGlobalRef(vByte);
//	w = 0;
//	h = 0;

	return end;
}
/**
 * 获取会议中的终端信息,客户端需要根据终端信息开启接受视频(需要等待ACK)
 */
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestTerminalmList(
		JNIEnv *env, jclass jcls) {
#if defined(LOG_JNI)
	Log("COnference_jni:requestTerminalmList..");
#endif
	return api->requestTerminalmList();
}
/**
 * 开始发送双流(需要等ACK)
 */
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestStartSendDualVideo(
		JNIEnv *env, jclass jcls, jobject wnd_) {
#if defined(LOG_JNI)
	Log("COnference_jni:requestStartSendDualVideo..");
#endif
	void *wnd = (void *) (&wnd_);
	return api->requestStartSendDualVideo(wnd);
}
/**
 * 停止发送双流(不需要等ACK)
 */
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestStopSendDualVideo(
		JNIEnv *env, jclass jcls) {
#if defined(LOG_JNI)
	Log("COnference_jni:requestStopSendDualVideo..");
#endif
	return api->requestStopSendDualVideo();
}
/**
 * 打开本地相机
 */
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_openCamera(
		JNIEnv *env, jclass jcls) {
#if defined(LOG_JNI)
	Log("COnference_jni:openCamera..");
#endif
	return api->SREngineOpenCamera();
}

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_closeCamera(
		JNIEnv *env, jclass jcls) {
#if defined(LOG_JNI)
	Log("COnference_jni:closeCamera..");
#endif
	return api->SREngineCloseCamera();
}

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestSelectRemoteVideo(
		JNIEnv *env, jclass jcls, jobject videoparamList) {
#if defined(LOG_JNI)
	Log("COnference_jni:requestSelectRemoteVideo..");
#endif
	int i;
	jclass cls_arraylist = env->GetObjectClass(videoparamList);
	jmethodID arraylist_get = env->GetMethodID(cls_arraylist, "get",
			"(I)Ljava/lang/Object;");
	jmethodID arraylist_size = env->GetMethodID(cls_arraylist, "size", "()I");
	jint len = env->CallIntMethod(videoparamList, arraylist_size);
	RVIDEO_PARAM *params = new RVIDEO_PARAM[len];
	for (i = 0; i < len; i++) {
		jobject obj_videoParam = env->CallObjectMethod(videoparamList,
				arraylist_get, i);
		jclass videoParam = env->GetObjectClass(obj_videoParam);
		jmethodID getterm_id = env->GetMethodID(videoParam, "getTermId", "()I");
		jmethodID getVideo_type = env->GetMethodID(videoParam, "getVideoType",
				"()I");
		jint termId = env->CallIntMethod(obj_videoParam, getterm_id);
		jint videoType = env->CallIntMethod(obj_videoParam, getVideo_type);
		Log(
				"COnference_jni:.....requestSelectRemoteVideo....termId__%d-----videoType:%d...len:%d",
				termId, videoType, len);

//		int 					term_id;					//选看终端的id
//		HWND 					wnd;						//大窗体句柄,调用端传空
//		HWND 					low_wnd;					//小窗体句柄,调用端传空
//		SR_CFG_VIDEO_TYPE		video_type;

		RVIDEO_PARAM param;
//		param.wnd = (void *) (&wnd_);
		param.term_id = termId;
		param.video_type = SR_CFG_VIDEO_TYPE(videoType);
//		param.low_wnd = (void *) (&wnd_);
		params[i] = param;
	}
	return api->requestSelectRemoteVideo(params, len);
}
/************************************************************************************************
 函数功能:  本地终端举手(不需要等ACK)
 输入参数： hand_up 举手:true 放手:false
 返回值: 0 成功  非0 失败
 *************************************************************************************************/
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestHandUp(
		JNIEnv *env, jclass jcls, jboolean handUp) {
#if defined(LOG_JNI)
	Log("COnference_jni:requestHandUp..");
#endif
	return api->requestHandUp(handUp);
}
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestRemoveTerminal(
		JNIEnv *env, jclass jcls, jint drop_id) {
#if defined(LOG_JNI)
	Log("COnference_jni:requestRemoveTerminal..");
#endif
	return api->requestRemoveTerminal(drop_id);
}
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_setMasterId(
		JNIEnv *env, jclass jcls, jint masterId) {
#if defined(LOG_JNI)
	Log("COnference_jni:masterId..");
#endif
	return api->setMasterId(masterId);
}

/**************************************
 入参数：函数功能：4.1.38	获取下行网络估计带宽
 输      media_type: 0-audio, 1-video low, 2-video-high
 ************/
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_getDownLoadBitrate(
		JNIEnv *env, jclass jcls, jint stream_id, jint media_type) {
#if defined(LOG_JNI)
	Log("COnference_jni:getDownLoadBitrate..");
#endif
	return api->getDownLoadBitrate(stream_id, media_type);
}

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_openOrCloseCamera(
		JNIEnv *env, jclass jcls, jboolean isOpen) {
	return api->openOrCloseCamera(isOpen);
}

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_setMute(JNIEnv *env,
		jclass jcls, jboolean isMute, jint mute_term_id) {
	return api->setMute(mute_term_id, isMute);
}

//VideoRawStreamType type, int width, int height, char *buf[3], int buf_size[3]
//unsigned char *ybuf,unsigned char *ubuf, unsigned char *vbuf
//发送视频接口
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineInVideoRawStreamYUV(
		JNIEnv *env, jclass jcls, jint videoStreamType, jint type, jint width,
		jint height, jbyteArray byteArray, jint size) {
#if defined(LOG_JNI)
	Log("COnference_jni:SREngineInVideoRawStream....");
#endif
	char *buf[3];
	jbyte *yuv420sp = env->GetByteArrayElements(byteArray, 0);
	char* byBuf = (char*) yuv420sp;
	//byBuf
	buf[0] = byBuf;
	int buf_size[3];
	buf_size[0] = (int) size;
	buf_size[1] = 0;
	buf_size[2] = 0;
	int value = api->SREngineInVideoRawStream(videoStreamType, type, width,
			height, buf, buf_size);
	env->ReleaseByteArrayElements(byteArray, yuv420sp, 0);
	return value;
}

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineInVideoRawStreamRGB(
		JNIEnv *env, jclass jcls, jint videoStreamType, jint type, jint width,
		jint height, jintArray rgbArray, jint size) {
//#if defined(LOG_JNI)
//	Log("COnference_jni:SREngineInVideoRawStreamRGB....");
//#endif
	char *buf[3];

	jint *rgb = env->GetIntArrayElements(rgbArray, 0);
	char* byBuf = (char*) rgb;

	//byBuf
	buf[0] = byBuf;
	int buf_size[3];
	buf_size[0] = (int) size;
	buf_size[1] = 0;
	buf_size[2] = 0;
	api->SREngineInVideoRawStream(videoStreamType, type, width, height, buf,
			buf_size);
	env->ReleaseIntArrayElements(rgbArray, rgb, 0);
	return 0;
}

////发送视频接口
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_RequestInVideoRawStream(
		JNIEnv *env, jclass jcls, jint type, jint width, jint height) {

}

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineSetRelayServer(
		JNIEnv *env, jclass jcls, jstring address) {
#if defined(LOG_JNI)
	Log("COnference_jni:SREngineSetRelayServer......");
#endif
	char* address_c = NULL;
	if (address != NULL)
		address_c = jstringTochar(env, address);
	Log("COnference_jni:SREngineSetRelayServer......:");
	return api->SREngineSetRelayServer(address_c);
}

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineMuteAudio(
		JNIEnv *env, jclass jcls, jint term_id) {
#if defined(LOG_JNI)
	Log("COnference_jni:SREngineMuteAudio.......");
#endif
	return api->SREngineMuteAudio(term_id);
}
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineUnMuteAudio(
		JNIEnv *env, jclass jcls, jint unterm_id) {
#if defined(LOG_JNI)
	Log("COnference_jni:SREngineUnMuteAudio.......");
#endif
	return api->SREngineUnMuteAudio(unterm_id);
}
JNIEXPORT jstring JNICALL Java_org_suirui_srpaas_jni_JniNative_getExtAudioProcessVersion(
		JNIEnv *env, jclass jcls) {
#if defined(LOG_JNI)
	Log("COnference_jni:GetExtAudioProcessVersion.......");
#endif
	char *versionss = api->SREngineGetExtAudioProcessVersion();
//	const char *version=(const char *)versionss;
//	Log("COnference_jni:GetExtAudioProcessVersion...version....%s", version);
//	jstring version_str = NULL;
//	if (version != NULL)
//		version_str = chartoJstring(env, version);
	jstring version_str = env->NewStringUTF(versionss);
	return version_str;

}

JNIEXPORT jstring JNICALL Java_org_suirui_srpaas_jni_JniNative_getExtAudioProcessId(
		JNIEnv *env, jclass jcls) {
#if defined(LOG_JNI)
	Log("COnference_jni:getExtAudioProcessId.......");
#endif
	char *versionss = api->SREngineGetExtAudioProcessId();
	jstring version_str = env->NewStringUTF(versionss);
	return version_str;

}

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_registerExtAudioProcessLicence(
		JNIEnv *env, jclass jcls, jstring licence, jint len) {
#if defined(LOG_JNI)
	Log("COnference_jni:registerExtAudioProcessLicence......");
#endif
	char* licence_c = NULL;
	if (licence != NULL)
		licence_c = jstringTochar(env, licence);
	return api->SREngineRegisterExtAudioProcessLicence(licence_c, len);
}
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_resposeSendDualVideoProxy(
		JNIEnv *env, jclass jcls, jlong conf_id, jint termid, jint avterid,
		jboolean isok, jstring rejectreason) {
#if defined(LOG_JNI)
	Log("COnference_jni:SREngineRspSendDualVideoProxy.......");
#endif
	char* rejectreason_c = NULL;
	if (rejectreason != NULL)
		rejectreason_c = jstringTochar(env, rejectreason);
	return api->SREngineRspSendDualVideoProxy(conf_id, termid, avterid, isok,
			rejectreason_c);
}

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_MuteAudioAllTerm(
		JNIEnv *env, jclass jcls, jlong confid, jint termid, jboolean ismute) {
#if defined(LOG_JNI)
	Log("COnference_jni:.......MuteAudioAllTerm..111");
#endif
	int re = api->SREngineMuteAudioAllTerm(confid, termid, ismute);
	Log("COnference_jni:.......MuteAudioAllTerm........22222");
	return re;
}
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineSetSpeakerMode(
		JNIEnv *env, jclass jcls, jint mode) {
	return api->SREngineSetSpeakerMode(mode);

}
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineRunningStatusNotify(
		JNIEnv *env, jclass jcls, jlong confid, jint termid, jint sta_class,
		jint sta_sub_class, jstring status_str) {
	char* status_c = NULL;
	if (status_str != NULL)
		status_c = jstringTochar(env, status_str);

	return api->SREngineRunningStatusNotify(confid, termid, sta_class,
			sta_sub_class, status_c);

}

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_getAudioActiveInf(
		JNIEnv *env, jclass jcls) {
#if defined(LOG_JNI)
	Log("COnference_jni:getAudioActiveInf.......");
#endif
	api->SRRegisterGetAudioActiveInfo();
	return 0;
}

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineNetworkChanged(
		JNIEnv *env, jclass jcls) {
	return api->SREngineNetworkChanged();
}

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_lockOrUnLockVideo(JNIEnv *env, jclass jcls,jlong  confi_id, jint term_id, jint lock_id,jboolean isLock ){
return api->lockOrUnLockVideo(confi_id,term_id,  lock_id, isLock);
}


JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_changeName(
		JNIEnv *env, jclass jcls,  jstring change_name) {
	char* change_name_c = NULL;
	if (change_name != NULL)
		change_name_c = jstringTochar(env, change_name);

	return api->changeName(change_name_c);

}

/************回调************************/
/**
 * 初始化mcu返回状态
 */
void onInitMCStatusCallBack_JNI(bool status) {
#if defined(LOG_JNI)
	Log("Conference_jni:mcu.........__%d",status);
#endif
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onInitMCStatusCallBack", "(Z)V");
		env->CallVoidMethod(obj_qtt, gJinMethod, status);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}
/**
 * 注销mcu返回的状态
 */
void OnUnInitMCStatusCallBack_JNI(bool status) {
#if defined(LOG_JNI)
	Log("Conference_jni:注销mcu返回的状态.........__%d",status);
#endif
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"OnUnInitMCStatusCallBack", "(Z)V");
		env->CallVoidMethod(obj_qtt, gJinMethod, status);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}
//入会状态返回
void OnRspJoinConfCallBack_JNI(const bool isOk, const char *fail_reason,
		const int sTermId) {
#if defined(LOG_JNI)
	Log("Conference_jni:.........__%d______%d",isOk,sTermId);
#endif
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	jstring fail_reason_str = NULL;
	if (fail_reason != NULL)
		fail_reason_str = chartoJstring(env, fail_reason);
	jboolean isStatus = (jboolean) isOk;
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"OnRspJoinConfCallBack", "(ZLjava/lang/String;I)V");
		env->CallVoidMethod(obj_qtt, gJinMethod, isOk, fail_reason_str,
				sTermId);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}
/**
 * 退出会议回调
 */
void OnExitConfCallBack_JNI(const char *exit_reason) {
#if defined(LOG_JNI)
	Log("Conference_jni:OnExitConfCallBack_JNI.........");
#endif
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	jstring exit_reason_str = NULL;
	if (exit_reason != NULL)
		exit_reason_str = chartoJstring(env, exit_reason);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"OnExitConfCallBack", "(Ljava/lang/String;)V");
		env->CallVoidMethod(obj_qtt, gJinMethod, exit_reason_str);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}

//终端列表结构体
jobject TermInfoStruct(JNIEnv *env, int termId, char* tername, bool ismuted,
		bool iscamera_on, bool ishandup, jobject info_obj) {
	jfieldID term_id = env->GetFieldID(info_class, "termid", "I");
	jfieldID term_name = env->GetFieldID(info_class, "tername",
			"Ljava/lang/String;");
	jfieldID is_muted = env->GetFieldID(info_class, "ismuted", "Z");
	jfieldID is_camera_on = env->GetFieldID(info_class, "iscamera_on", "Z");
	jfieldID is_handup = env->GetFieldID(info_class, "ishandup", "Z");
	env->SetIntField(info_obj, term_id, termId);
	jstring term_nameStr;
	term_nameStr = env->NewStringUTF(tername);
	env->SetObjectField(info_obj, term_name, term_nameStr);
	env->DeleteLocalRef(term_nameStr);
	env->SetBooleanField(info_obj, is_muted, ismuted);
	env->SetBooleanField(info_obj, is_camera_on, iscamera_on);
	env->SetBooleanField(info_obj, is_handup, ishandup);
	return info_obj;
}
//获取会议终端列表回调
void onRspConfTermListCallBack_JNI(const bool isOk, const UINT64 conf_id,
		const int term_id, const int master_id, const int duo_term_id,
		const int totalnums, TermInfo **termInfoList, const int nSize,
		const char *fail_reason) {
#if defined(LOG_JNI)
	Log("Conference_jni:onRspConfTermListCallBack_JNI...list.....___isOk:%d____conf_id:%llu____term_id:%d____totalnums:%d_____nSize:%d",isOk,conf_id,term_id,totalnums,nSize);
#endif
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	jstring fail_reason_str = NULL;
	if (fail_reason != NULL)
		fail_reason_str = chartoJstring(env, fail_reason);
	jmethodID construct = env->GetMethodID(class_ArrayList, "<init>", "()V");
	jobject obj_List = env->NewObject(class_ArrayList, construct, "");
	jmethodID list_add = env->GetMethodID(class_ArrayList, "add",
			"(Ljava/lang/Object;)Z");
	jmethodID info_method = env->GetMethodID(info_class, "<init>", "()V");

	int i = 0;
	for (i = 0; i < nSize; i++) {
		TermInfo *termInfo = termInfoList[i];
		int termId = termInfo->termid;
		char* tername = termInfo->tername;
		bool ismuted = termInfo->ismuted;
		bool iscamera_on = termInfo->iscamera_on;
		bool ishandup = termInfo->ishandup;
		jobject info_obj = env->NewObject(info_class, info_method, "");
		jobject info = TermInfoStruct(env, termId, tername, ismuted,
				iscamera_on, ishandup, info_obj);
		env->CallBooleanMethod(obj_List, list_add, info);
		env->DeleteLocalRef(info_obj);
	}
	jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
			"()V");
	jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
	jmethodID gJinMethod = env->GetMethodID(Callback_class,
			"onRspConfTermListCallBack",
			"(ZJIIILjava/util/ArrayList;Ljava/lang/String;)V");
	jlong confId = (jlong) conf_id;
	env->CallVoidMethod(obj_qtt, gJinMethod, isOk, confId, term_id, master_id,
			duo_term_id, obj_List, fail_reason_str);
	env->DeleteLocalRef(obj_qtt);
	env->DeleteLocalRef(obj_List);
	gs_jvm->DetachCurrentThread();
}
//新终端加入会议
void onNewTermJoinCallBack_JNI(const UINT64 conf_id, const int term_id,
		const TermInfo *termInfos) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);

	jmethodID construct = env->GetMethodID(class_ArrayList, "<init>", "()V");
	jobject obj_List = env->NewObject(class_ArrayList, construct, "");
	jmethodID list_add = env->GetMethodID(class_ArrayList, "add",
			"(Ljava/lang/Object;)Z");
	jmethodID info_method = env->GetMethodID(info_class, "<init>", "()V");
	TermInfo *termInfo = (TermInfo *) termInfos;
	int termId = termInfo->termid;
	char* tername = termInfo->tername;
	bool ismuted = termInfo->ismuted;
	bool iscamera_on = termInfo->iscamera_on;
	bool ishandup = termInfo->ishandup;
	jobject info_obj = env->NewObject(info_class, info_method, "");
	jobject info = TermInfoStruct(env, termId, tername, ismuted, iscamera_on,
			ishandup, info_obj);
	env->CallBooleanMethod(obj_List, list_add, info);
	env->DeleteLocalRef(info_obj);
	jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
			"()V");
	jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
	Log("Conference_.........j");
	jmethodID gJinMethod = env->GetMethodID(Callback_class,
			"onNewTermJoinCallBack", "(JILjava/util/ArrayList;)V");
	jlong confId = (jlong) conf_id;
	env->CallVoidMethod(obj_qtt, gJinMethod, confId, term_id, obj_List);
	env->DeleteLocalRef(obj_qtt);
	env->DeleteLocalRef(obj_List);
	gs_jvm->DetachCurrentThread();

//	jmethodID info_method = env->GetMethodID(info_class, "<init>", "()V");
//	TermInfo *termInfo = (TermInfo *) termInfos;
//	int termId = termInfo->termid;
//	char* tername = (char*) termInfo->tername;
//	bool ismuted = termInfo->ismuted;
//	bool iscamera_on = termInfo->iscamera_on;
//	bool ishandup = termInfo->ishandup;
//	jobject info_obj = env->NewObject(info_class, info_method, "");
//	jobject info = TermInfoStruct(env, termId, tername, ismuted, iscamera_on,
//			ishandup, info_obj);
//	env->DeleteLocalRef(info_obj);
//	if (Callback_class != NULL) {
//		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
//				"()V");
//		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
//		jmethodID gJinMethod = env->GetMethodID(Callback_class,
//				"onNewTermJoinCallBack", "(JILjava/lang/Object;)V");
//		jlong confId = (jlong) conf_id;
//		int termId = (int) term_id;
//		env->CallVoidMethod(obj_qtt, gJinMethod, confId, termId, info);
//		env->DeleteLocalRef(obj_qtt);
//		env->DeleteLocalRef(info);
//	}
//	gs_jvm->DetachCurrentThread();
}

void onTermLeaveCallBack_JNI(const UINT64 conf_id, const int term_id,
		const char *leave_reason, const int leaveterid) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	jstring leave_reason_str;
	if (leave_reason != NULL)
		leave_reason_str = chartoJstring(env, leave_reason);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onTermLeaveCallBack", "(JILjava/lang/String;I)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, confId, term_id,
				leave_reason_str, leaveterid);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}

//新终端进入时,告知双流进行的指示
void onDualVideoOnCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int dual_id) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onDualVideoOnCallBack", "(JII)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, confId, term_id, dual_id);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}



void onTermChangeNameCallBack_JNI(const UINT64 conf_id, const int term_id,
     		const int changeterid, const char *term_name) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);

		jstring term_name_str;
    	if (term_name != NULL)
    		term_name_str = chartoJstring(env, term_name);

	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onTermChangeNameCallBack", "(JIILjava/lang/String;)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, confId, term_id, changeterid,term_name_str);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}



void onMuteAudioAllTermNotifyCallBack_JNI(const UINT64 conf_id,
		const int term_id, const bool is_mute) {
#if defined(LOG_JNI)
	Log("COnference_jni:.......onMuteAudioAllTermNotifyCallBack_JNI...%d",term_id);
#endif
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onMuteAudioAllTermNotifyCallBack", "(JIZ)V");
		jlong confId = (jlong) conf_id;
		jboolean ismute = (jboolean) is_mute;
		env->CallVoidMethod(obj_qtt, gJinMethod, confId, term_id, ismute);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}

void onReqDualVideoProxyCallBack_JNI(const UINT64 conf_id, const int termid,
		const int avtermid) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onReqDualVideoProxyCallBack", "(JII)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, confId, termid, avtermid);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}

void onOpenCameraCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int open_id) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onOpenCameraCallBack", "(JII)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, conf_id, term_id, open_id);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}
void onCloseCameraCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int close_id) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onCloseCameraCallBack", "(JII)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, conf_id, term_id, close_id);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}
//主持人退出会议
void onChairEndConfCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int chairid, const char* chairname) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	jstring chairname_str;
	if (chairname != NULL)
		chairname_str = chartoJstring(env, chairname);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onChairEndConfCallBack", "(JIILjava/lang/String;)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, confId, term_id, chairid,
				chairname_str);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}
/**
 * 其它客户端取消禁音回调
 */
void onTermAudioRecUnMuteCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int sponsorid, const int cancelterid) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onTermAudioRecUnOrMuteCallBack", "(JIIIZ)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, confId, term_id, sponsorid,
				cancelterid, false);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}
/**
 * 其它客户端禁音回调
 */
void onTermAudioRecMuteCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int sponsorid, const int muteterid) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onTermAudioRecUnOrMuteCallBack", "(JIIIZ)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, confId, term_id, sponsorid,
				muteterid, true);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}

/**
 * 主持人身份切换回调
 */
void onMasterTransferCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int new_id) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onMasterTransferCallBack", "(JII)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, confId, term_id, new_id);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}


/**
 * 举手
 */
void onTermHandUpCallBack_JNI(const UINT64 conf_id, const int term_id,
                              		const int handupterid, const bool isHandUp){
JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onTermHandUpCallBack", "(JIIZ)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, confId, term_id, handupterid,isHandUp);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}

/**
 *设置演讲人
 */
void onLockVideoCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int unlock_id) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onLockOrUnLockVideoCallBack", "(JIIZ)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, confId, term_id, unlock_id,
				true);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}
/**
 * 取消演讲人回调
 */
void onUnLockVideoCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int unlock_id) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onLockOrUnLockVideoCallBack", "(JIIZ)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, confId, term_id, unlock_id,
				false);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}

/**
 * 开始发送双流 回调
 */
void onRspSendDualVideoCallBack_JNI(const bool isOk, const UINT64 conf_id,
		const int term_id, const char *fail_reason) {
#if defined(LOG_JNI)
	Log("Conference_jni:开始发送双流 回调.........isOk:%d____conf_id:%llu____term_id:%d",
			isOk,conf_id,term_id);
#endif
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	jstring fail_reason_str;
	if (fail_reason != NULL)
		fail_reason_str = chartoJstring(env, fail_reason);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onRspSendDualVideoCallBack", "(ZJILjava/lang/String;)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, isOk, confId, term_id,
				fail_reason_str);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}
/**
 * 接受端收到双流回调
 */
void OnRecvDualVideoOpenCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int send_id) {
#if defined(LOG_JNI)
	Log("Conference_jni:接受端收到双流回调.........conf_id:%llu____term_id:%d____send_id:%d",conf_id,term_id,send_id);
#endif
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"OnRecvDualVideoOpenCallBack", "(JII)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, confId, term_id, send_id);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();

}
/**
 * 接收端收到关闭双流 回调
 * conf_id 会议id
 * term_id 终端id
 */
void OnRecvDualVideoCloseCallBack_JNI(const UINT64 conf_id, const int term_id) {
#if defined(LOG_JNI)
	Log("Conference_jni:关闭双流的回调.........conf_id:%llu____term_id:%d",conf_id,term_id);
#endif
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"OnRecvDualVideoCloseCallBack", "(JI)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, confId, term_id);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}
/**
 * 渲染unsigned char* buf
 */

//void onRenderCallBackCallBack_JNI(int id, int flag, unsigned char *ybuf,
//		unsigned char *ubuf, unsigned char *vbuf, int width, int height) {
//
//	JNIEnv *env;
//	gs_jvm->AttachCurrentThread(&env, NULL);
////	jbyteArray yByte = env->NewByteArray(ysize);
////	jbyteArray uByte = env->NewByteArray(usize);
////	jbyteArray vByte = env->NewByteArray(usize);
////
////	yByte = getByteToArray(env, ybuf, ysize, yByte);
////	uByte = getByteToArray(env, ubuf, usize, uByte);
////	vByte = getByteToArray(env, vbuf, usize, vByte);
//	int ysize = width * height;
//	int usize = ((width + 1) / 2) * ((height + 1) / 2);
//	if (w != width && height != h) {
//		yByte = env->NewByteArray(ysize);
//		uByte = env->NewByteArray(usize);
//		vByte = env->NewByteArray(usize);
//		w = width;
//		h = height;
//	}
//
////	jboolean isCopy;
////	void *data = env->GetPrimitiveArrayCritical((jarray) yByte, &isCopy);
////	memcpy(data, ybuf, bytecount);
//	if (yByte != NULL)
//		env->SetByteArrayRegion(yByte, 0, ysize, reinterpret_cast<jbyte*>(ybuf));
//	if (uByte != NULL)
//		env->SetByteArrayRegion(uByte, 0, usize, reinterpret_cast<jbyte*>(ybuf));
//	if (vByte != NULL)
//		env->SetByteArrayRegion(vByte, 0, usize, reinterpret_cast<jbyte*>(ybuf));
//	Log("Conference_jni:onRenderCallBackCallBack_JNI....3333");
//	if (Callback_class != NULL) {
//		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
//				"()V");
//		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
//		jmethodID gJinMethod = env->GetMethodID(Callback_class,
//				"onRenderCallBackCallBack", "(II[B[B[BII)V");
//		Log("Conference_jni:onRenderCallBackCallBack_JNI....4444");
//		env->CallVoidMethod(obj_qtt, gJinMethod, id, flag, yByte, uByte, vByte,
//				width, height);
//		Log("Conference_jni:onRenderCallBackCallBack_JNI....555");
//		env->DeleteLocalRef(obj_qtt);
//		Log("Conference_jni:onRenderCallBackCallBack_JNI...666");
//	}
//	gs_jvm->DetachCurrentThread();
//}
/**
 * 渲染unsigned char* buf
 */
void onRenderCallBackCallBack_JNI(int id, int flag, unsigned char *ybuf,
		unsigned char *ubuf, unsigned char *vbuf, int width, int height) {
//#if defined(LOG_JNI)
//	Log("Conference_jni:onRenderCallBackCallBack_JNI.........id:%d____flag:%d___width:%d___height:%d",id,flag,width,height);
//#endif
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	int ysize = width * height;
	int usize = ((width + 1) / 2) * ((height + 1) / 2);
	jbyteArray yByte = getByteToArray(env, ybuf, ysize);
	jbyteArray uByte = getByteToArray(env, ubuf, usize);
	jbyteArray vByte = getByteToArray(env, vbuf, usize);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"onRenderCallBackCallBack", "(II[B[B[BII)V");
		env->CallVoidMethod(obj_qtt, gJinMethod, id, flag, yByte, uByte, vByte,
				width, height);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}

//*******************end
JNIEXPORT void JNICALL Java_org_suirui_srpaas_jni_JniNative_SetDisplayZoom(float zoom_factor, float *zoom_cx, float *zoom_cy) {

}

jobject VoiceActiveInfoStruct(JNIEnv *env, int talkId, int energy,
		jobject info_obj) {
	jfieldID talk_id_ = env->GetFieldID(VoiceActiveInfo_class, "talk_id", "I");
	jfieldID energy_ = env->GetFieldID(VoiceActiveInfo_class, "energy", "I");
	env->SetIntField(info_obj, talk_id_, talkId);
	env->SetIntField(info_obj, energy_, energy);
	return info_obj;
}

void onActiveVoiceCallBack_JNI(SRVoiceActiveInfo *voice_acives, int num) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	jmethodID construct = env->GetMethodID(class_ArrayList, "<init>", "()V");
	jobject obj_List = env->NewObject(class_ArrayList, construct, "");
	jmethodID list_add = env->GetMethodID(class_ArrayList, "add",
			"(Ljava/lang/Object;)Z");
	jmethodID info_method = env->GetMethodID(VoiceActiveInfo_class, "<init>",
			"()V");
	SRVoiceActiveInfo *voice_acive = (SRVoiceActiveInfo *) voice_acives;
	for (int i = 0; i < num; i++) {

		int talkId = voice_acive[i].talk_id;
		unsigned int ergy = voice_acive[i].energy;
		int ergyen = (int) ergy;
		jobject VoiceActiveInfo_obj = env->NewObject(VoiceActiveInfo_class,
				info_method, "");
		jobject info = VoiceActiveInfoStruct(env, talkId, ergyen,
				VoiceActiveInfo_obj);
		env->CallBooleanMethod(obj_List, list_add, info);
		env->DeleteLocalRef(VoiceActiveInfo_obj);
	}
	jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
			"()V");
	jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
	jmethodID gJinMethod = env->GetMethodID(Callback_class,
			"onActiveVoiceCallBack", "(Ljava/util/ArrayList;)V");
	env->CallVoidMethod(obj_qtt, gJinMethod, obj_List);
	env->DeleteLocalRef(obj_qtt);
	env->DeleteLocalRef(obj_List);
	gs_jvm->DetachCurrentThread();
}
void OnScreenDrawLabelCallBack_JNI(UINT64 conf_id, int term_id,
		ScreenLableAttr attr) {

}
void OnScreenClearLabelCallBack_JNI(UINT64 conf_id, int term_id, int cleardid) {

}
void OnRecvConfMessageCallBack_JNI(UINT64 conf_id, int from_id, char *message,
		int message_len) {

}
void SREngineRunningStatusNotifyCallBack_JNI(const UINT64 conf_id,
		const int termid, const int stautsTermid, const int staClass,
		const int staSubCls, const char* staStr) {
#if defined(LOG_JNI)
	Log("Conference_jni:SREngineRunningStatusNotifyCallBack_JNI:..........");
#endif
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"SREngineRunningStatusNotifyCallBack", "(JIIII)V");
		jlong confId = (jlong) conf_id;
		env->CallVoidMethod(obj_qtt, gJinMethod, confId, termid, stautsTermid,
				staClass, staSubCls);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}
void OnStackConnErrorCallBack_JNI(int type) {
	JNIEnv *env;
	gs_jvm->AttachCurrentThread(&env, NULL);
	if (Callback_class != NULL) {
		jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
				"()V");
		jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
		jmethodID gJinMethod = env->GetMethodID(Callback_class,
				"OnStackConnErrorCallBack", "(I)V");
		env->CallVoidMethod(obj_qtt, gJinMethod, type);
		env->DeleteLocalRef(obj_qtt);
	}
	gs_jvm->DetachCurrentThread();
}
}
