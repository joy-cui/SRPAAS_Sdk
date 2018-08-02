#define TAG "SRSdkJni"

#include <jni.h>
#include <android/log.h>
#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <signal.h>
#include "SRSdkJni.h"
#include "SRRtcEngineConferenceSdk.h"
#include "ISRRtcEngine.h"
#include "ISRRtcType.h"
#include "Log.h"
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <stdarg.h>

#define FILE_BUF_SIZE    1024


#define LOG_TAG "SRSdkJni----->"


bool isWriteLog = false;
ofstream ofile;

JavaVM *gs_jvm = 0;
using namespace std;

jclass Callback_class = NULL;
jclass stringClass = NULL;
jclass info_class = NULL;
jclass class_ArrayList = NULL;
jclass VoiceActiveInfo_class = NULL;
jclass screenLabel_class = NULL;
jclass SRError_class = NULL;
jclass SRSendStreamInfo_class = NULL;
jclass SRRecvStreamInfo_class = NULL;
jclass RecvAudioStreamInfo_class = NULL;
jclass RecvVideoStreamInfo_class = NULL;
jclass ConfInfoStatus_class = NULL;
jclass SubtitleInfo_class = NULL;
jclass WhiteListInfo_class = NULL;
jclass srMediaInfo_class = NULL;
jclass srMediaInfoPScreenInfo_class = NULL;
jclass srNetWorkstate_class = NULL;
jclass srOnliveInfo_class = NULL;

int w = 0;
int h = 0;
jbyteArray yByte = NULL;
jbyteArray uByte = NULL;
jbyteArray vByte = NULL;


char *yBufData=NULL;
char *uBufData=NULL;
char *vBufData=NULL;

struct sigaction *old_sa;

jobject network_obj = NULL;

void InitCrashReport() {
//    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "异常捕获....");
    file_write_log("SRSdkJni...InitCrashReport....");
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
//    CATCHSIG(SIGSTKFLT);
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

JNIEXPORT jint

JNICALL JNI_OnLoad(JavaVM *ajvm, void *reserved) {
    gs_jvm = ajvm;
//    InitCrashReport();
    JNIEnv *env = NULL;
    if ((gs_jvm)->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        Log("SRSdkJni:JNI_OnLoad..not..JNI_VERSION_1_4.");
        return -1;
    }
    Log("SRSdkJni:JNI_OnLoad....");
    return JNI_VERSION_1_4;;
}

class SRSdkJni {
public:
    SRSdkJni(JNIEnv *env) {
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

        screenLabel_class = (jclass) env->NewGlobalRef(
                env->FindClass("org/suirui/srpaas/entry/SRScreenLable"));

        SRError_class = (jclass) env->NewGlobalRef(
                env->FindClass("org/suirui/srpaas/entry/SRError"));

        SRSendStreamInfo_class = (jclass) env->NewGlobalRef(
                env->FindClass("org/suirui/srpaas/entry/SRSendStreamInfo"));

        SRRecvStreamInfo_class = (jclass) env->NewGlobalRef(
                env->FindClass("org/suirui/srpaas/entry/SRRecvStreamInfo"));

        RecvAudioStreamInfo_class = (jclass) env->NewGlobalRef(
                env->FindClass("org/suirui/srpaas/entry/RecvAudioStreamInfo"));

        RecvVideoStreamInfo_class = (jclass) env->NewGlobalRef(
                env->FindClass("org/suirui/srpaas/entry/RecvVideoStreamInfo"));

        ConfInfoStatus_class = (jclass) env->NewGlobalRef(
                env->FindClass("org/suirui/srpaas/entry/ConfInfoStatus"));

        SubtitleInfo_class = (jclass) env->NewGlobalRef(
                env->FindClass("org/suirui/srpaas/entry/SubtitleInfo"));

        WhiteListInfo_class = (jclass) env->NewGlobalRef(
                env->FindClass("org/suirui/srpaas/entry/WhiteListInfo"));

        srMediaInfo_class = (jclass) env->NewGlobalRef(
                env->FindClass("org/suirui/srpaas/entry/SRMediaPInfo"));

        srMediaInfoPScreenInfo_class = (jclass) env->NewGlobalRef(
                env->FindClass("org/suirui/srpaas/entry/SRMediaPScreenInfo"));

        srNetWorkstate_class = (jclass) env->NewGlobalRef(
                env->FindClass("org/suirui/srpaas/entry/NetWorkStatus"));

        srOnliveInfo_class = (jclass) env->NewGlobalRef(
                env->FindClass("org/suirui/srpaas/entry/OnliveInfo"));
    }

    ~SRSdkJni() {
    }

};

extern "C" {

void ThrowJNI(JNIEnv *env, const char *str) {
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
string jstringTostring(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    if (stringClass != NULL && stringClass != 0) {
        jstring strencode = env->NewStringUTF("utf-8");
        jmethodID mid = env->GetMethodID(stringClass, "getBytes",
                                         "(Ljava/lang/String;)[B");
        jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid,
                                                             strencode);
        env->DeleteLocalRef(strencode);
        jsize alen = env->GetArrayLength(barr);
        jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
        if (alen > 0) {
            rtn = (char *) malloc(alen + 1); //new   char[alen+1];
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
    return "";
}


//jstring to char*
char *jstringTochar(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    if (stringClass != NULL && stringClass != 0) {
        jstring strencode = env->NewStringUTF("utf-8");
        jmethodID mid = env->GetMethodID(stringClass, "getBytes",
                                         "(Ljava/lang/String;)[B");
        jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid,
                                                             strencode);
        env->DeleteLocalRef(strencode);
        jsize alen = env->GetArrayLength(barr);
        jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
        if (alen > 0) {
            rtn = (char *) malloc(alen + 1);
            memcpy(rtn, ba, alen);
            rtn[alen] = 0;
        }
        env->ReleaseByteArrayElements(barr, ba, 0);
        return rtn;
    }
    return rtn;
}
//const char* to jstring
jstring chartoJstring(JNIEnv *env, const char *pat) {
    if (stringClass != NULL && stringClass != 0) {
        jmethodID ctorID = env->GetMethodID(stringClass, "<init>",
                                            "([BLjava/lang/String;)V");
        if (pat != NULL) {
            jbyteArray bytes = env->NewByteArray(strlen(pat));
            env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte *) pat);
            jstring encoding = env->NewStringUTF("utf-8");
            jstring retJString = (jstring)env->NewObject(stringClass, ctorID, bytes, encoding);
            env->DeleteLocalRef(bytes);
            env->DeleteLocalRef(encoding);
            //return (jstring)env->NewObject(stringClass, ctorID, bytes, encoding);
            return retJString;
        } else {
            return NULL;
        }
    }
    return NULL;
}


//string to jstring
jstring stringToJstring(JNIEnv *env, string str) {


    const char *chardata = str.c_str();
    // char* 转 string
    jstring jstr = chartoJstring(env, chardata);
    return jstr;

}

int mystrlen(unsigned char *str) {
    int i = -1;
    while (i++, '\0' != str[i]);
    return i;
}

int strlens(unsigned char *str) {
    return 0;
}
jbyteArray byteToArray(JNIEnv *env, unsigned char *buf) {
    int len = mystrlen(buf);
    jbyteArray array = env->NewByteArray(len);
    env->SetByteArrayRegion(array, 0, len, reinterpret_cast<jbyte *>(buf));
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

jbyteArray getByteToArray(JNIEnv *env, unsigned char *ybuf, int len) {
    jbyteArray array = env->NewByteArray(len);
    env->SetByteArrayRegion(array, 0, len, reinterpret_cast<jbyte *>(ybuf));
    return array;
}

unsigned char *arrayToChar(JNIEnv *env, jbyteArray array) {
    int len = env->GetArrayLength(array);
    unsigned char *buf = new unsigned char[len];
    env->GetByteArrayRegion(array, 0, len, reinterpret_cast<jbyte *>(buf));

    return buf;
}
/************************
 * 初始化sdk,启动程序时候调用
 * 作    者:licui
 * **********************/

JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_InitSDK(JNIEnv *env, jclass jcls,
                                                     jboolean isopensdklog,jboolean isH264Decode,jint platformType) {
    env->GetJavaVM(&gs_jvm);
#if defined(LOG_JNI)
    Log("COnference_jni:InitSDK.....");
#endif
    SRSdkJni *ldata = new SRSdkJni(env);
//	api = SRRtcEngineConferenceSdk::instance();
    return gSdk->initSrEnginConferenceSdk(isopensdklog,isH264Decode,platformType);
}
/************************
 * 退出应用时候调用
 * 作    者:licui
 * **********************/
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_UnInitSDK(
        JNIEnv *env, jclass jcls) {
#if defined(LOG_JNI)
    Log("SRSdkJni........UnInitSDK");
#endif
    env->DeleteGlobalRef(Callback_class);
    env->DeleteGlobalRef(stringClass);
    env->DeleteGlobalRef(info_class);
    env->DeleteGlobalRef(class_ArrayList);
    env->DeleteGlobalRef(VoiceActiveInfo_class);
    env->DeleteGlobalRef(screenLabel_class);
    env->DeleteGlobalRef(SRError_class);
    env->DeleteGlobalRef(SRSendStreamInfo_class);
    env->DeleteGlobalRef(SRRecvStreamInfo_class);
    env->DeleteGlobalRef(RecvAudioStreamInfo_class);
    env->DeleteGlobalRef(RecvVideoStreamInfo_class);
    env->DeleteGlobalRef(ConfInfoStatus_class);
    env->DeleteGlobalRef(SubtitleInfo_class);
    env->DeleteGlobalRef(WhiteListInfo_class);
    env->DeleteGlobalRef(srMediaInfoPScreenInfo_class);
    env->DeleteGlobalRef(srMediaInfo_class);
    env->DeleteGlobalRef(srNetWorkstate_class);
    env->DeleteGlobalRef(srOnliveInfo_class);
    return gSdk->UnInitSDK();
}

/*****************结构体******start**********************************************************************************************/
void SceenLabelInfoStruct(JNIEnv *env, jobject screenLabelObject, SRScreenLableAttr sceenlabel) {
    jclass userCls = (env)->GetObjectClass(screenLabelObject);
    jmethodID getLabelterid = env->GetMethodID(userCls, "getLabelterid", "()I");
    jmethodID getOperatetype = env->GetMethodID(userCls, "getOperatetype", "()I");
    jmethodID getLableid = env->GetMethodID(userCls, "getLableid", "()I");
    jmethodID getLabletype = env->GetMethodID(userCls, "getLabletype", "()I");
    jmethodID getLablesize = env->GetMethodID(userCls, "getLablesize", "()I");
    jmethodID getLablecolor = env->GetMethodID(userCls, "getLablecolor", "()I");
    jmethodID getLinetype = env->GetMethodID(userCls, "getLinetype", "()I");
    jmethodID getLeftuppoints_x = env->GetMethodID(userCls, "getLeftuppoints_x", "()I");
    jmethodID getLeftuppoints_y = env->GetMethodID(userCls, "getLeftuppoints_y", "()I");
    jmethodID getRightdownpoints_x = env->GetMethodID(userCls, "getRightdownpoints_x", "()I");
    jmethodID getRightdownpoints_y = env->GetMethodID(userCls, "getRightdownpoints_y", "()I");
    jmethodID getResolution_x = env->GetMethodID(userCls, "getResolution_x", "()I");
    jmethodID getResolution_y = env->GetMethodID(userCls, "getResolution_y", "()I");

    jint Labelterid = env->CallIntMethod(screenLabelObject, getLabelterid);
    jint Operatetype = env->CallIntMethod(screenLabelObject, getOperatetype);
    jint Lableid = env->CallIntMethod(screenLabelObject, getLableid);
    jint Labletype = env->CallIntMethod(screenLabelObject, getLabletype);
    jint Lablesize = env->CallIntMethod(screenLabelObject, getLablesize);
    jint Lablecolor = env->CallIntMethod(screenLabelObject, getLablecolor);
    jint Linetype = env->CallIntMethod(screenLabelObject, getLinetype);

    jint Leftuppoints_x = env->CallIntMethod(screenLabelObject, getLeftuppoints_x);
    jint Leftuppoints_y = env->CallIntMethod(screenLabelObject, getLeftuppoints_y);

    jint Rightdownpoints_x = env->CallIntMethod(screenLabelObject, getRightdownpoints_x);
    jint Rightdownpoints_y = env->CallIntMethod(screenLabelObject, getRightdownpoints_y);

    jint Resolution_x = env->CallIntMethod(screenLabelObject, getResolution_x);
    jint Resolution_y = env->CallIntMethod(screenLabelObject, getResolution_y);


    sceenlabel.labelterid = Labelterid;
    sceenlabel.operatetype = Operatetype;
    sceenlabel.lableid = Lableid;
    sceenlabel.labletype = Labletype;
    sceenlabel.lablesize = Lablesize;
    sceenlabel.lablecolor = Lablecolor;
    sceenlabel.linetype = Linetype;
    sceenlabel.leftuppoints_x = Leftuppoints_x;
    sceenlabel.leftuppoints_y = Leftuppoints_y;
    sceenlabel.rightdownpoints_x = Rightdownpoints_x;
    sceenlabel.rightdownpoints_y = Rightdownpoints_y;
    sceenlabel.resolution_x = Resolution_x;
    sceenlabel.resolution_y = Resolution_y;
}


SRRtcEngineJoinConfContext makeJoinConfContext(JNIEnv *env, jclass jcls,
                                               jobject joinConfObject, jobject userInfoObject,
                                               McInfo &mcInfo,
                                               UserInfo &userInfo, ConfInfo &confInfo,
                                               bool isCameraOn,
                                               bool isMute, bool needRelayServer) {
    //用户信息
    jclass userCls = (env)->GetObjectClass(userInfoObject);
    jmethodID getTermUId = env->GetMethodID(userCls, "getTermUId", "()I");
    jmethodID getTermUname = env->GetMethodID(userCls, "getTermUname",
                                              "()Ljava/lang/String;");
    jmethodID getMediagroupid = env->GetMethodID(userCls, "getMediagroupid", "()I");
    jmethodID getUserType=env->GetMethodID(userCls, "getUserType", "()I");
    jint termUId = env->CallIntMethod(userInfoObject, getTermUId);
    jstring
            str_termUName = (jstring)
    env->CallObjectMethod(userInfoObject, getTermUname);
    jint mediagroupid = env->CallIntMethod(userInfoObject, getMediagroupid);
    jint userType = env->CallIntMethod(userInfoObject, getUserType);
    //会议相关
    jclass configCls = (env)->GetObjectClass(joinConfObject);
    jmethodID getConferenceId = env->GetMethodID(configCls, "getConferenceId", "()J");
    jmethodID getPassword = env->GetMethodID(configCls, "getPassword", "()Ljava/lang/String;");
    jmethodID getPandPort = env->GetMethodID(configCls, "getPandPort", "()J");
    jmethodID getOCI = env->GetMethodID(configCls, "getOCI", "()Ljava/lang/String;");
    jmethodID getRelay_server = env->GetMethodID(configCls, "getRelay_server",
                                                 "()Ljava/lang/String;");
    jstring  str_passWord = (jstring)env->CallObjectMethod(joinConfObject, getPassword);
    jlong confid = env->CallLongMethod(joinConfObject, getConferenceId);
    jlong panPort = env->CallLongMethod(joinConfObject, getPandPort);
    jstring
            str_oci = (jstring)
    env->CallObjectMethod(joinConfObject, getOCI);
    jstring
            str_relay_server = (jstring)
    env->CallObjectMethod(joinConfObject, getRelay_server);
//relay_mc_address(列表)

    jfieldID relaymcInfoID = env->GetFieldID(configCls, "relaymcInfo", "Ljava/util/ArrayList;");
    jobject codeobj = env->GetObjectField(joinConfObject, relaymcInfoID);
    list <std::string> relaymc_info;
    if (codeobj != NULL) {
        int i;
        jclass cls_arraylist = env->GetObjectClass(codeobj);
        //method in class ArrayList
        jmethodID arraylist_get = env->GetMethodID(cls_arraylist, "get", "(I)Ljava/lang/Object;");
        jmethodID arraylist_size = env->GetMethodID(cls_arraylist, "size", "()I");
        jint len = env->CallIntMethod(codeobj, arraylist_size);
        for (i = 0; i < len; i++) {
            jobject obj_user = env->CallObjectMethod(codeobj, arraylist_get, i);
            jclass cls_user = env->GetObjectClass(obj_user);
            jfieldID idFieldID = env->GetFieldID(cls_user, "address",
                                                 "Ljava/lang/String;"); // 获得属性ID
            jstring
                    address = (jstring)
            env->GetObjectField(obj_user, idFieldID);//获得属性值

            std::string address_s = jstringTostring(env, address);
            relaymc_info.push_back(address_s);
        }
    }
    mcInfo.ipandport = panPort;
    mcInfo.relaymc_info = relaymc_info;
    confInfo.conf_id = confid;
    if (str_passWord != NULL) {
        confInfo.password = jstringTostring(env, str_passWord);
    }


    userInfo.termUId = termUId;
    userInfo.mediagroupid = mediagroupid;
    if (str_termUName != NULL) {
        userInfo.termUName = jstringTostring(env, str_termUName);
    }
    userInfo.usertype=SREngineUserType(userType);
    SRRtcEngineJoinConfContext context;
    context.mcinfo = &mcInfo;
    context.userinfo = &userInfo;
    context.confinfo = &confInfo;
    if (needRelayServer) {
        if (str_relay_server != NULL) {
            context.relay_server_addrs = jstringTostring(env, str_relay_server);
        }
    }
    context.iscameraon = isCameraOn;
    context.ismuted = isMute;
    if (str_oci != NULL) {
        context.systemload = jstringTostring(env, str_oci);
        Log("SRSdkJni:makeJoinConfContext.......OCI:%s", (jstringTostring(env, str_oci)).c_str());
    }
#if defined(LOG_JNI)
    Log("SRSdkJni:makeJoinConfContext........panPort:%llu======confid:%llu======termUId:%d======termUName:%s",
        panPort, confid, userInfo.termUId,(userInfo.termUName).c_str());
#endif
    return context;
}


std::list <SRMediaPScreenInfo> getMediaPScreenInfoList(JNIEnv *env,jobject screensList){
    jclass cls_arraylist = env->GetObjectClass(screensList);
    jmethodID arraylist_get = env->GetMethodID(cls_arraylist, "get",
                                               "(I)Ljava/lang/Object;");
    jmethodID arraylist_size = env->GetMethodID(cls_arraylist, "size", "()I");
    jint len = env->CallIntMethod(screensList, arraylist_size);
    std::list <SRMediaPScreenInfo> screens_List;
    int i;
    for (i = 0; i < len; i++) {
        jobject obj_screenInfo = env->CallObjectMethod(screensList, arraylist_get, i);
        jclass screenInfo = env->GetObjectClass(obj_screenInfo);
        jmethodID getScreenid = env->GetMethodID(screenInfo, "getScreenid", "()I");
        jmethodID getScreentype = env->GetMethodID(screenInfo, "getScreentype", "()I");
        jint screenid = env->CallIntMethod(obj_screenInfo, getScreenid);
        jint screentype = env->CallIntMethod(obj_screenInfo, getScreentype);
        Log("SRSdkJni...getMediaPScreenInfoList...screenid__=%d_____screentype=%d", screenid, screentype);
        SRMediaPScreenInfo srMediaPScreenInfo;
        srMediaPScreenInfo.screenid = screenid;
        srMediaPScreenInfo.screentype = screentype;
        screens_List.push_back(srMediaPScreenInfo);
    }
    return screens_List;
}
/*************************************************结构体 end*********************************************************************/

//加入会议
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_reqestJoinConf(JNIEnv *env, jclass jcls,
                                                            jobject joinConfObject,
                                                            jobject userInfoObject,
                                                            jboolean isCameraOn,
                                                            jboolean isMute) {
#if defined(LOG_JNI)
    Log("SRSdkJni...reqestJoinConf..");
#endif

    McInfo mcInfo;
    UserInfo userInfo;
    ConfInfo confInfo;
    SRRtcEngineJoinConfContext context = makeJoinConfContext(env, jcls, joinConfObject,
                                                             userInfoObject, mcInfo,
                                                             userInfo, confInfo, isCameraOn,
                                                             isMute, true);
    return gSdk->ReqJoinConf(context);
}

//退出会议
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestExitConf(JNIEnv *env, jclass jcls,
                                                             jstring exit_reason) {
#if defined(LOG_JNI)
    Log("SRSdkJni...requestExitConf..");
#endif
    char *exit_reason_c = NULL;
    if (exit_reason != NULL)
        exit_reason_c = jstringTochar(env, exit_reason);
    jint end = gSdk->ExitConf(exit_reason_c);
    return end;
}

//主持人结束会议
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestChairEndConf(JNIEnv *env, jclass jcls) {
#if defined(LOG_JNI)
    Log("SRSdkJni...requestChairEndConf..");
#endif
    jint end = gSdk->ChairEndConf();
    return end;
}

//  向SREngine发送数据帧
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineInVideoRawStreamRGB(JNIEnv *env, jclass jcls,
                                                                         jint streamType,
                                                                         jint formatType,
                                                                         jint width, jint height,
                                                                         jintArray rgbArray,
                                                                         jint size) {
#if defined(LOG_JNI)
    Log("SRSdkJni...SREngineInVideoRawStreamRGB..");
#endif

    SR_VIDEO_STREAM_TYPE type = (SR_VIDEO_STREAM_TYPE) streamType;
    SR_VIDEO_RAW_FORMAT_TYPE format = (SR_VIDEO_RAW_FORMAT_TYPE) formatType;


    char *buf[3];
    jint * rgb = env->GetIntArrayElements(rgbArray, 0);
    char *byBuf = (char *) rgb;
    //byBuf
    buf[0] = byBuf;
    int buf_size[3];
    buf_size[0] = (int) size;
    buf_size[1] = 0;
    buf_size[2] = 0;


    VideoFrame frame;
    frame.format = format;
    frame.width = width;
    frame.height = height;
    frame.yBuffer = buf[0];
    frame.ySize = buf_size[0];
    frame.uBuffer = buf[1];
    frame.uSize = buf_size[1];
    frame.vBuffer = buf[2];
    frame.vSize = buf_size[2];
    int ret = gSdk->InPutVideoRawStream(type, frame);
    env->ReleaseIntArrayElements(rgbArray, rgb, 0);
    return ret;
}


//  向SREngine发送数据帧(发送流 )
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineInVideoRawStreamYUV(JNIEnv *env, jclass jcls,
                                                                         jint streamType,
                                                                         jint formatType,
                                                                         jint width, jint height,
                                                                         jbyteArray byteArray,
                                                                         jint size) {

    SR_VIDEO_STREAM_TYPE type = (SR_VIDEO_STREAM_TYPE) streamType;
    SR_VIDEO_RAW_FORMAT_TYPE format = (SR_VIDEO_RAW_FORMAT_TYPE) formatType;

    char *buf[3];
    jbyte *yuv420sp = env->GetByteArrayElements(byteArray, 0);
    char *byBuf = (char *) yuv420sp;
    int len = strlen(byBuf) + 1;


#if defined(LOG_JNI)
    Log("SRSdkJni...SREngineInVideoRawStreamYUV..___size:%d___len:%d",size,len);
#endif
    //byBuf
    buf[0] = byBuf;
    int buf_size[3];
    buf_size[0] = (int) size;
    buf_size[1] = 0;
    buf_size[2] = 0;


    VideoFrame frame(width, height);

    buf[1] = byBuf + frame.ySize;
    buf[2] = byBuf + frame.ySize + frame.uSize;

    frame.format = format;
    frame.width = width;
    frame.height = height;
    frame.yBuffer = buf[0];
    frame.uBuffer = buf[1];
    frame.vBuffer = buf[2];
    int ret = gSdk->InPutVideoRawStream(type, frame);
#if defined(LOG_JNI)
    Log("SRSdkJni...SREngineInVideoRawStreamYUV..__end");
#endif
    env->ReleaseByteArrayElements(byteArray, yuv420sp, 0);
    return ret;
}


//获取参会人列表
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestTerminalmList(
        JNIEnv *env, jclass jcls) {
#if defined(LOG_JNI)
    Log("SRSdkJni...requestTerminalmList..");
#endif
    int ret = gSdk->EnableReqConfTermList();
    return ret;
}

//选看视频
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestSelectRemoteVideo(JNIEnv *env, jclass jcls,
                                                                      jobject videoparamList) {
    int i;
    jclass cls_arraylist = env->GetObjectClass(videoparamList);
    jmethodID arraylist_get = env->GetMethodID(cls_arraylist, "get",
                                               "(I)Ljava/lang/Object;");
    jmethodID arraylist_size = env->GetMethodID(cls_arraylist, "size", "()I");
    jint len = env->CallIntMethod(videoparamList, arraylist_size);
    list <RequestVideoParam> paramList;
    for (i = 0; i < len; i++) {
        jobject obj_videoParam = env->CallObjectMethod(videoparamList,
                                                       arraylist_get, i);
        jclass videoParam = env->GetObjectClass(obj_videoParam);
        jmethodID getterm_id = env->GetMethodID(videoParam, "getTermId", "()I");
        jmethodID getVideo_type = env->GetMethodID(videoParam, "getVideoType",
                                                   "()I");

        jmethodID getDelayflag = env->GetMethodID(videoParam, "getDelayflag",
                                                  "()I");
        jmethodID getReplaceterid = env->GetMethodID(videoParam, "getReplaceterid",
                                                     "()I");
        jmethodID getExpectfps = env->GetMethodID(videoParam, "getExpectfps",
                                                  "()I");

        jint termId = env->CallIntMethod(obj_videoParam, getterm_id);
        jint videoType = env->CallIntMethod(obj_videoParam, getVideo_type);

        jint delayFlag_ = env->CallIntMethod(obj_videoParam, getDelayflag);
        jint replaceId_ = env->CallIntMethod(obj_videoParam, getReplaceterid);
        jint expectFps_ = env->CallIntMethod(obj_videoParam, getExpectfps);


        RequestVideoParam param;
        param.sterm_id = termId;
        param.video_type = SR_CFG_SELECT_VIDEO_STREAM(videoType);
        param.delayflag = delayFlag_;
        param.replaceterid = replaceId_;
//        param.expectfps = expectFps_;
        paramList.push_back(param);
        file_write_log("SRSdkJni...requestSelectRemoteVideo....___%d,___%d", termId, videoType);
    }
    int ret = gSdk->SelectVideo(paramList);
    return ret;
}
/**
 * 开启共享
 */
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestStartSendDualVideo(
        JNIEnv *env, jclass jcls, jobject wnd_) {
#if defined(LOG_JNI)
    Log("SRSdkJni:requestStartSendDualVideo..");
#endif
    void *view_t = (void *) (&wnd_);
    int ret = gSdk->StartSendDualVideo(view_t);
    return ret;

}
//   停止共享
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestStopSendDualVideo(JNIEnv *env, jclass jcls) {
    int ret = gSdk->StopSendDualVideo();
    return ret;
}


// 暂停共享
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestPauseSendDualVideo(JNIEnv *env, jclass jcls) {
    int ret = gSdk->PauseSendDualVideo();
    return ret;
}

// 恢复共享
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestResumeSendDualVideo(JNIEnv *env, jclass jcls) {
    int ret = gSdk->ResumeSendDualVideo();
    return ret;
}
//恢复共享申请者
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_resposeSendDualVideoProxy(
        JNIEnv *env, jclass jcls, jint avterid, jboolean isok, jstring rejectreason) {
#if defined(LOG_JNI)
    Log("SRSdkJni:resposeSendDualVideoProxy.......");
#endif
    char *rejectreason_c = NULL;
    if (rejectreason != NULL)
        rejectreason_c = jstringTochar(env, rejectreason);
    return gSdk->RspSendDualVideoProxy(avterid, isok, rejectreason_c);
}


// 桌面共享其他客户端添加备注
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestAddScreenLabel(JNIEnv *env, jclass jcls,
                                                                   jobject addLabelObject) {
#if defined(LOG_JNI)
    Log("SRSdkJni:requestAddScreenLabel.......");
#endif
    SRScreenLableAttr sceenlabel;
    SceenLabelInfoStruct(env, addLabelObject, sceenlabel);
    return gSdk->AddScreenLabel(sceenlabel);
}

//打开本地摄像头指示
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_openCamera(JNIEnv *env, jclass jcls,
                                                        jint unmute_stermid) {
#if defined(LOG_JNI)
    Log("SRSdkJni...openCamera..");
#endif
    return gSdk->SetCameraOn(unmute_stermid, true);
}

//关闭本地相机
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_closeCamera(JNIEnv *env, jclass jcls,
                                                         jint mute_stermid) {
#if defined(LOG_JNI)
    Log("SRSdkJni...closeCamera..");
#endif
    return gSdk->SetCameraOn(mute_stermid, false);
}

//静音
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_muteAudio(JNIEnv *env, jclass jcls,
                                                       jint mute_stermid) {
#if defined(LOG_JNI)
    Log("SRSdkJni...muteAudio..");
#endif
    return gSdk->SetAudioMute(mute_stermid, true);
}

//取消静音
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_unMuteAudio(JNIEnv *env, jclass jcls,
                                                         jint unmute_stermid) {
#if defined(LOG_JNI)
    Log("SRSdkJni...unMuteAudio..");
#endif
    return gSdk->SetAudioMute(unmute_stermid, false);
}

//全部静音/取消全部静音
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_MuteAudioAllTerm(JNIEnv *env, jclass jcls,
                                                              jboolean isMute) {
#if defined(LOG_JNI)
    Log("SRSdkJni...MuteAudioAllTerm..");
#endif
    return gSdk->MuteAudioAllTerm(isMute);
}


//举手
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestHandUp(JNIEnv *env, jclass jcls,
                                                           jboolean handUp) {
#if defined(LOG_JNI)
    Log("SRSdkJni...requestHandUp..");
#endif
    return gSdk->HandUp(handUp);
}

//改名
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_changeName(JNIEnv *env, jclass jcls,
                                                        jstring changename) {
#if defined(LOG_JNI)
    Log("SRSdkJni...changeName..");
#endif
    char *changename_c = NULL;
    if (changename != NULL)
        changename_c = jstringTochar(env, changename);
    return gSdk->ChangeTermName(changename_c);
}

//设置焦点视频
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_lockOrUnLockVideo(JNIEnv *env, jclass jcls,
                                                               jint lock_id, jboolean isLock) {
#if defined(LOG_JNI)
    Log("SRSdkJni...lockOrUnLockVideo..");
#endif
    if (isLock)
        return gSdk->LockVideo(lock_id);
    else
        return gSdk->UnLockVideo(lock_id);

}

//主持人踢人
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestRemoveTerminal(JNIEnv *env, jclass jcls,
                                                                   jint termid) {
#if defined(LOG_JNI)
    Log("SRSdkJni...dropTerm..");
#endif
    return gSdk->DropTerm(termid);
}

//会中有共享，主持人可结束
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_chairEndDataShare(JNIEnv *env, jclass jcls) {
#if defined(LOG_JNI)
    Log("SRSdkJni...chairEndDataShare..");
#endif
    return gSdk->ChairEndDataShare();
}

//主持人权限转移
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_setMasterId(JNIEnv *env, jclass jcls,
                                                         jint newMasterId) {
#if defined(LOG_JNI)
    Log("SRSdkJni...setMasterId..");
#endif
    file_write_log("SRSdkJni..setMasterId......setMasterId:%d", newMasterId);
    return gSdk->MasterTransfer(newMasterId);
}

//使能获取当前收到流统计信息状态, 传0 代表停止统计
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_getSendStreamInfoIndication(JNIEnv *env, jclass jcls,
                                                                         jint interval) {
#if defined(LOG_JNI)
    Log("SRSdkJni...onSendStreamInfoIndication");
#endif
    return gSdk->EnableSendStreamInfoIndication(interval);
}

//使能获取当前发送统计信息状态, 传0 代表停止统计
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_getRecvStreamInfoIndication(JNIEnv *env, jclass jcls,
                                                                         jint interval) {
#if defined(LOG_JNI)
    Log("SRSdkJni...onRecvStreamInfoIndication");
#endif
    return gSdk->EnableRecvStreamInfoIndication(interval);
}

//共享内存



JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineInVideoRawStreamDataBuf(JNIEnv *env, jclass jcls, jint streamType, jint formatType, jobject obj, jint width, jint height, jint rotationType, jboolean isMirror, jint size) {
//#if defined(LOG_JNI)
//    Log("SRSdkJni...SREngineInVideoRawStreamDataTest....demo");
//#endif
    SR_VIDEO_STREAM_TYPE type = (SR_VIDEO_STREAM_TYPE) streamType;
    SR_VIDEO_RAW_FORMAT_TYPE format = (SR_VIDEO_RAW_FORMAT_TYPE) formatType;
    SR_VIDEO_RAW_ROTATION_MODE rotation = (SR_VIDEO_RAW_ROTATION_MODE) rotationType;

    char *buf[3];
    jlong length=  env->GetDirectBufferCapacity(obj);
    char *byBuf=(char *)env->GetDirectBufferAddress(obj);

//byBuf
    buf[0] = byBuf;
    int buf_size[3];
    buf_size[0] = (int) size;
    buf_size[1] = 0;
    buf_size[2] = 0;

    VideoFrame frame(width, height);

    frame.format = format;
    frame.rotation = rotation;
    frame.isMirror = isMirror;
    frame.width = width;
    frame.height = height;
    frame.yBuffer = buf[0];
    frame.ySize = buf_size[0];
    frame.uBuffer = buf[1];
    frame.uSize = buf_size[1];
    frame.vBuffer = buf[2];
    frame.vSize = buf_size[2];
    int ret = gSdk->InPutVideoRawStream(type, frame);
    return ret;
}





//相机采集的数据
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineInVideoRawStreamData(JNIEnv *env, jclass jcls,
                                                                          jint streamType,
                                                                          jint formatType,
                                                                          jbyteArray byteArray,
                                                                          jint width,
                                                                          jint height,
                                                                          jint rotationType,
                                                                          jboolean isMirror,
                                                                          jint size) {
//#if defined(LOG_JNI)
//    Log("SRSdkJni...SREngineInVideoRawStreamData");
//#endif
    SR_VIDEO_STREAM_TYPE type = (SR_VIDEO_STREAM_TYPE) streamType;
    SR_VIDEO_RAW_FORMAT_TYPE format = (SR_VIDEO_RAW_FORMAT_TYPE) formatType;
    SR_VIDEO_RAW_ROTATION_MODE rotation = (SR_VIDEO_RAW_ROTATION_MODE) rotationType;

    char *buf[3];
    jbyte *yuv420sp = env->GetByteArrayElements(byteArray, 0);
    char *byBuf = (char *) yuv420sp;
    //byBuf
    buf[0] = byBuf;
    int buf_size[3];
    buf_size[0] = (int) size;
    buf_size[1] = 0;
    buf_size[2] = 0;

    VideoFrame frame(width, height);

    frame.format = format;
    frame.rotation = rotation;
    frame.isMirror = isMirror;
    frame.width = width;
    frame.height = height;
    frame.yBuffer = buf[0];
    frame.ySize = buf_size[0];
    frame.uBuffer = buf[1];
    frame.uSize = buf_size[1];
    frame.vBuffer = buf[2];
    frame.vSize = buf_size[2];
    int ret = gSdk->InPutVideoRawStream(type, frame);
    env->ReleaseByteArrayElements(byteArray, yuv420sp, 0);
    return ret;
}

//测试按钮写文件
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRSetUserCmdToEngine(JNIEnv *env, jclass jcls,
                                                                  jobjectArray strArray) {
#if defined(LOG_JNI)
    Log("SRSdkJni...SRSetUserCmdToEngine");
#endif
    jobject jobj;
    jsize len = env->GetArrayLength(strArray);
    char *pstr[len];
    int i = 0;
    for (i = 0; i < len; i++) {
        jobj = env->GetObjectArrayElement(strArray, i);
        pstr[i] = (char *) env->GetStringUTFChars((jstring)
        jobj, 0);
        Log("SRSdkJni...SRSetUserCmdToEngine...__%d,__%s", len, pstr[i]);
    }
    return gSdk->SetUserCmdToEngine(len, pstr);
}


//网络监听
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineNetworkChanged(JNIEnv *env, jclass jcls) {
#if defined(LOG_JNI)
    Log("SRSdkJni...SREngine_NetworkChanged");
#endif
    return gSdk->NotifyNetworkChanged();
}

//设置扬声器的模式
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineSetSpeakerMode(JNIEnv *env, jclass jcls,
                                                                    jint mode) {
#if defined(LOG_JNI)
    Log("SRSdkJni...SREngineSetSpeakerMode");
#endif
    return gSdk->SetSpeakerMode(mode);
}

//设置终端状态
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineRunningStatusNotify(JNIEnv *env, jclass jcls,
                                                                         jint sta_class,
                                                                         jint sta_sub_class,
                                                                         jstring status_str) {
#if defined(LOG_JNI)
    Log("SRSdkJni...SREngineRunningStatusNotify");
#endif
    char *status_str_c = NULL;
    if (status_str != NULL)
        status_str_c = jstringTochar(env, status_str);
    return gSdk->RunningStatusNotify(sta_class, sta_sub_class, status_str_c);
}


//获取apm认证mac信息
JNIEXPORT jstring
JNICALL Java_org_suirui_srpaas_jni_JniNative_getApmInfo(JNIEnv *env, jclass jcls) {
#if defined(LOG_JNI)
    Log("SRSdkJni...getApmInfo...");
#endif

    string info_c = gSdk->GetApmInfoSDK();
#if defined(LOG_JNI)
    Log("SRSdkJni...getApmInfo...__%s",info_c.c_str());
#endif
    jstring infoStr = stringToJstring(env, info_c);
    return infoStr;
}

//设置APM认证key
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_setApmKeyContent(JNIEnv *env, jclass jcls,
                                                              jstring key) {
#if defined(LOG_JNI)
    Log("SRSdkJni...setApmKeyContent");
#endif
    string key_c = jstringTostring(env, key);
    return gSdk->SetApmKeyContentSDK(key_c);
}

//设置当前扬声器的音量
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRSetOutputDeviceVolume(JNIEnv *env, jclass jcls,
                                                                     jint volume) {
#if defined(LOG_JNI)
    Log("SRSdkJni...SRSetOutputDeviceVolume");
#endif
    return gSdk->SetOutputDeviceVolume(volume);
}


//设置强制静音
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRSetForceMuteAudio(JNIEnv *env, jclass jcls,
                                                                 jint sorttype,
                                                                 jboolean isforcemute) {
#if defined(LOG_JNI)
    Log("SRSdkJni...SRSetForceMute");
#endif
    SRConferenceCtrlForceMute ctrlForceMute;
    ctrlForceMute.sponsortype = sorttype;
    ctrlForceMute.isforcemute = isforcemute;
    return gSdk->ForceMuteAudio(ctrlForceMute);
}


//获取会议信息
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRReqSRConfStatus(JNIEnv *env, jclass jcls,
                                                               jint sorttype) {
#if defined(LOG_JNI)
    Log("SRSdkJni...SRReqSRConfStatus");
#endif
    SRConferenceCtrlReqConfStatus ctrlReqConfStatus;
    ctrlReqConfStatus.sponsortype = sorttype;
    return gSdk->ReqSRConfStatus(ctrlReqConfStatus);
}

//锁定会议
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRLockConf(JNIEnv *env, jclass jcls,
                                                        jboolean islockconf) {
#if defined(LOG_JNI)
    Log("SRSdkJni...SRLockConf");
#endif
    return gSdk->LockConf(islockconf);
}

//锁定会议时，主持人踢除参会人
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRDelParticipants(JNIEnv *env, jclass jcls,
                                                               jobject delparlist) {
#if defined(LOG_JNI)
    Log("SRSdkJni...SRDelParticipants");
#endif
    int i;
    SRConferenceCtrlDelParticipants ctrlDelParticipants;
    jclass cls_arraylist = env->GetObjectClass(delparlist);
    jmethodID arraylist_get = env->GetMethodID(cls_arraylist, "get",
                                               "(I)Ljava/lang/Object;");
    jmethodID arraylist_size = env->GetMethodID(cls_arraylist, "size", "()I");
    jint len = env->CallIntMethod(delparlist, arraylist_size);
    list <UINT32> participantlist;
    for (i = 0; i < len; i++) {
        jobject obj_suidParam = env->CallObjectMethod(delparlist, arraylist_get, i);
        jclass suidParam = env->GetObjectClass(obj_suidParam);
        jmethodID getsuid = env->GetMethodID(suidParam, "getSuid", "()I");
        jint suid = env->CallIntMethod(obj_suidParam, getsuid);
        Log("SRSdkJni...SRDelParticipants...suid__%d", suid);
        participantlist.push_back(suid);
    }
    ctrlDelParticipants.participants = participantlist;
    return gSdk->DelParticipants(ctrlDelParticipants);
}


//重启音频设备
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRresetAudioDevice(JNIEnv *env, jclass jcls) {
#if defined(LOG_JNI)
    Log("SRSdkJni...SRresetAudioDevice");
#endif
    return gSdk->ResetAudioDevice();
}

//设置用户需要设置的信息给sdk
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRSetUsrNotify(JNIEnv *env, jclass jcls,
                                                            jint netType) {
#if defined(LOG_JNI)
    Log("SRSdkJni...SRSetUsrNotify");
#endif
    SRUserSetParam netParam;
    netParam.has_network_param = true;
    netParam.network_param.network_type = SREngineNetworkType(netType);
    netParam.network_param.platform_type = SREnginePlatFormType(2);
    return gSdk->SetUsrNotify(netParam);
}


//开始会议的录制
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_StartMeetingRecord(JNIEnv *env, jclass jcls,
                                                                jint channelid,
                                                                jobject screensList) {
#if defined(LOG_JNI)
    Log("SRSdkJni...StartMeetingRecord");
#endif
    SRConferenceCtrlStartMeetingRecord ctrlStartMeetingRecord;
    ctrlStartMeetingRecord.is_record_mp = true;
    ctrlStartMeetingRecord.mp_info.channelid = channelid;
    if (screensList != NULL) {
        std::list <SRMediaPScreenInfo> screens_List = getMediaPScreenInfoList(env, screensList);
        ctrlStartMeetingRecord.mp_info.screens = screens_List;
    }
    return gSdk->StartMeetingRecord(ctrlStartMeetingRecord);
}


//停止会议录制
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_StopMeetingRecord(JNIEnv *env, jclass jcls,
                                                               jint channelid,
                                                               jobject screensList) {
#if defined(LOG_JNI)
    Log("SRSdkJni...StopMeetingRecord");
#endif
    SRConferenceCtrlStopMeetingRecord ctrlStopMeetingRecord;
    ctrlStopMeetingRecord.is_record_mp = true;
    ctrlStopMeetingRecord.mp_info.channelid = channelid;
    if (screensList != NULL) {
        std::list <SRMediaPScreenInfo> screens_List = getMediaPScreenInfoList(env, screensList);
        ctrlStopMeetingRecord.mp_info.screens = screens_List;
    }
    return gSdk->StopMeetingRecord(ctrlStopMeetingRecord);
}


//获取当前的网络状态
JNIEXPORT jobject
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRGetNetWorkStatus(JNIEnv *env, jclass jcls) {
//#if defined(LOG_JNI)
//    Log("SRSdkJni...SRGetNetWorkStatus");
//#endif
    NetWorkStatus status;
    gSdk->GetNetWorkStatusNotify(status);
//    Log("SRSdkJni...SRGetNetWorkStatus...upload__=%d_____download=%d",
//        status.network_upload_status, status.network_download_status);
    jmethodID m_mid = env->GetMethodID(srNetWorkstate_class, "<init>", "(II)V");
    network_obj = env->NewObject(srNetWorkstate_class, m_mid, status.network_upload_status,
                                 status.network_download_status);
    return network_obj;
}


//开启直播
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_StartMeetingLive(JNIEnv *env, jclass jcls,
                                                              jobject onliveInfo,
                                                              jint channelid,
                                                              jobject screensList) {
    Log("SRSdkJni...StartMeetingLive");
    SRConferenceCtrlStartMeetingLive startMeetingLive;
    startMeetingLive.is_live_mp = true;
    //直播的参数设置
    jclass onliveCls = (env)->GetObjectClass(onliveInfo);
    jmethodID getPulladdrprefix = env->GetMethodID(onliveCls, "getPulladdrprefix", "()Ljava/lang/String;");
    jmethodID getPlayaddrprefix = env->GetMethodID(onliveCls, "getPlayaddrprefix", "()Ljava/lang/String;");
    jmethodID getChairman = env->GetMethodID(onliveCls, "getChairman", "()Ljava/lang/String;");
    jmethodID getSubject = env->GetMethodID(onliveCls, "getSubject", "()Ljava/lang/String;");
    jmethodID getDigest = env->GetMethodID(onliveCls, "getDigest", "()Ljava/lang/String;");
    jmethodID getIspublic = env->GetMethodID(onliveCls, "getIspublic", "()I");
    jmethodID getLivepwd = env->GetMethodID(onliveCls, "getLivepwd", "()Ljava/lang/String;");
    jstring  str_pulladdrprefix = (jstring)env->CallObjectMethod(onliveInfo, getPulladdrprefix);
    jstring  str_playaddrprefix = (jstring)env->CallObjectMethod(onliveInfo, getPlayaddrprefix);
    jstring  str_chairman = (jstring)env->CallObjectMethod(onliveInfo, getChairman);
    jstring  str_subject = (jstring)env->CallObjectMethod(onliveInfo, getSubject);
    jstring  str_digest = (jstring)env->CallObjectMethod(onliveInfo, getDigest);
    jint ispublic = env->CallIntMethod(onliveInfo, getIspublic);
    jstring  str_livepwd = (jstring)env->CallObjectMethod(onliveInfo, getLivepwd);
    if(str_pulladdrprefix!=NULL)
        startMeetingLive.pulladdrprefix=jstringTostring(env, str_pulladdrprefix);
    if(str_playaddrprefix!=NULL)
        startMeetingLive.playaddrprefix=jstringTostring(env,str_playaddrprefix);
    if(str_chairman!=NULL)
        startMeetingLive.livesetinfo.chairman=jstringTostring(env,str_chairman);
    if(str_subject!=NULL)
        startMeetingLive.livesetinfo.subject=jstringTostring(env,str_subject);
    if(str_digest!= NULL)
        startMeetingLive.livesetinfo.digest=jstringTostring(env,str_digest);
    startMeetingLive.livesetinfo.ispublic=ispublic;
    if(str_livepwd!= NULL)
        startMeetingLive.livesetinfo.livepwd=jstringTostring(env,str_livepwd);

    //SRMediaPInfo信息
    startMeetingLive.mp_info.channelid=channelid;
    if (screensList != NULL) {
        std::list <SRMediaPScreenInfo> screens_List = getMediaPScreenInfoList(env, screensList);
        startMeetingLive.mp_info.screens = screens_List;
    }
    Log("SRSdkJni...StartMeetingLive(sdk)");
    return gSdk->StartMeetingLive(startMeetingLive);
}


//停止直播
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_StopMeetingLive(JNIEnv *env, jclass jcls,
                                                             jint channelid,
                                                             jobject screensList) {
    Log("SRSdkJni...StopMeetingLive");
    SRConferenceCtrlStopMeetingLive stopMeetingLive;
    stopMeetingLive.is_live_mp= true;

    //SRMediaPInfo信息
    stopMeetingLive.mp_info.channelid=channelid;
    if (screensList != NULL) {
        std::list <SRMediaPScreenInfo> screens_List = getMediaPScreenInfoList(env, screensList);
        stopMeetingLive.mp_info.screens = screens_List;
    }
    return gSdk->StopMeetingLive(stopMeetingLive);
}


//修改直播的参数
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_ChangeLiveSetting(JNIEnv *env, jclass jcls,
                                                               jobject onliveInfo){
    Log("SRSdkJni...ChangeLiveSetting");
    SRConferenceCtrlChangeLiveSetting changeLiveSetting;
    //直播的参数设置
    jclass onliveCls = (env)->GetObjectClass(onliveInfo);
    jmethodID getChairman = env->GetMethodID(onliveCls, "getChairman", "()Ljava/lang/String;");
    jmethodID getSubject = env->GetMethodID(onliveCls, "getSubject", "()Ljava/lang/String;");
    jmethodID getDigest = env->GetMethodID(onliveCls, "getDigest", "()Ljava/lang/String;");
    jmethodID getIspublic = env->GetMethodID(onliveCls, "getIspublic", "()I");
    jmethodID getLivepwd = env->GetMethodID(onliveCls, "getLivepwd", "()Ljava/lang/String;");
    jstring  str_chairman = (jstring)env->CallObjectMethod(onliveInfo, getChairman);
    jstring  str_subject = (jstring)env->CallObjectMethod(onliveInfo, getSubject);
    jstring  str_digest = (jstring)env->CallObjectMethod(onliveInfo, getDigest);
    jint ispublic = env->CallIntMethod(onliveInfo, getIspublic);
    jstring  str_livepwd = (jstring)env->CallObjectMethod(onliveInfo, getLivepwd);
    if(str_chairman!=NULL)
        changeLiveSetting.new_setting.chairman=jstringTostring(env,str_chairman);
    if(str_subject!=NULL)
        changeLiveSetting.new_setting.subject=jstringTostring(env,str_subject);
    if(str_digest!= NULL)
        changeLiveSetting.new_setting.digest=jstringTostring(env,str_digest);
    changeLiveSetting.new_setting.ispublic=ispublic;
    if(str_livepwd!= NULL)
        changeLiveSetting.new_setting.livepwd=jstringTostring(env,str_livepwd);
    return gSdk->ChangeLiveSetting(changeLiveSetting);
}



//聊天发送消息
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_sendConfMessage(JNIEnv *env, jclass jcls,
                                                             jobject termIdList, jstring message){
    Log("SRSdkJni...sendConfMessage");
    int i;
    jclass cls_arraylist = env->GetObjectClass(termIdList);
    jmethodID arraylist_get = env->GetMethodID(cls_arraylist, "get",
                                               "(I)Ljava/lang/Object;");
    jmethodID arraylist_size = env->GetMethodID(cls_arraylist, "size", "()I");
    jint len = env->CallIntMethod(termIdList, arraylist_size);
    std::list<int> participantlist;
    for (i = 0; i < len; i++) {
        jobject obj_termIdParam = env->CallObjectMethod(termIdList, arraylist_get, i);
        jclass termIdParam = env->GetObjectClass(obj_termIdParam);
        jmethodID getTermId = env->GetMethodID(termIdParam, "getTermId", "()I");
        jint termId = env->CallIntMethod(obj_termIdParam, getTermId);
        Log("SRSdkJni...sendConfMessage...termId__%d", termId);
        participantlist.push_back(termId);
    }
    return gSdk->SendIMMessage(participantlist, jstringTostring(env, message));
}
//****************************文件操作*************

//JNIEnv *getJNIEnv(int *needsDetach) {
//    JNIEnv *env = NULL;
//    jint result = -1;
//    int status = gs_jvm->AttachCurrentThread(&env, NULL);
//    if (status < 0) {
//        return NULL;
//    }
//    *needsDetach = 1;
//    return env;
//}

JNIEnv *getJNIEnv(int *needsDetach) {
    JNIEnv *env = NULL;
    *needsDetach = -1;
    if ((gs_jvm)->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        int status = gs_jvm->AttachCurrentThread(&env, 0);
        if (status < 0) {
            return NULL;
        }
        *needsDetach = 1;
    }
    return env;
}


jboolean file_open(const char *filename) {
    if (!isWriteLog) {
        ofile.open(filename);
        isWriteLog = true;
    }
    return isWriteLog;

}


void file_write_log(const char *strFormat, ...) {
    if (isWriteLog) {
        if (NULL == strFormat)

            return;

        char strInfo[FILE_BUF_SIZE];

        va_list arg_ptr;

        va_start(arg_ptr, strFormat);

        vsprintf(strInfo, strFormat, arg_ptr);

        va_end(arg_ptr);

        ofile << strInfo << "\n";
        //释放
    }

}


JNIEXPORT jboolean
JNICALL Java_org_suirui_srpaas_jni_JniNative_openFile(JNIEnv *env, jclass jcls, jstring filename) {
    const char *filename_char = env->GetStringUTFChars(filename, NULL);
    return file_open(filename_char);
}
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_closeFile(JNIEnv *env, jclass jcls) {
    if (ofile) {
        ofile.close();
    }
    return 0;
}

//****************************文件操作end*************
/****主调结束****************************************************************************************************/
/***************************************************************************************************************/
//终端列表结构体
jobject TermInfoStruct(JNIEnv *env, int termId, unsigned int suid, string tername, bool ismuted,
                       bool iscamera_on, bool ishandup, bool isonline, int usertype,
                       int specialtype,int devicetype,string ip,int protocoltype,int bandwidth,string calloption,
                       jobject info_obj) {
    jfieldID term_id = env->GetFieldID(info_class, "termid", "I");
    jfieldID suid_id = env->GetFieldID(info_class, "suid", "I");
    jfieldID term_name = env->GetFieldID(info_class, "tername",
                                         "Ljava/lang/String;");
    jfieldID is_muted = env->GetFieldID(info_class, "ismuted", "Z");
    jfieldID is_camera_on = env->GetFieldID(info_class, "iscamera_on", "Z");
    jfieldID is_handup = env->GetFieldID(info_class, "ishandup", "Z");
    jfieldID is_online = env->GetFieldID(info_class, "isonline", "Z");
    jfieldID user_type = env->GetFieldID(info_class, "usertype", "I");
    jfieldID special_type = env->GetFieldID(info_class, "specialtype", "I");
    jfieldID device_type = env->GetFieldID(info_class, "devicetype", "I");
    jfieldID ip_ = env->GetFieldID(info_class, "ip", "Ljava/lang/String;");
    jfieldID protocol_type = env->GetFieldID(info_class, "protocoltype", "I");
    jfieldID band_width = env->GetFieldID(info_class, "bandwidth", "I");
    jfieldID calloption_ = env->GetFieldID(info_class, "calloption", "Ljava/lang/String;");

    env->SetIntField(info_obj, term_id, termId);
    env->SetIntField(info_obj, suid_id, suid);
    jstring term_nameStr;
    term_nameStr = stringToJstring(env, tername);
    env->SetObjectField(info_obj, term_name, term_nameStr);
    env->DeleteLocalRef(term_nameStr);
    env->SetBooleanField(info_obj, is_muted, ismuted);
    env->SetBooleanField(info_obj, is_camera_on, iscamera_on);
    env->SetBooleanField(info_obj, is_handup, ishandup);
    env->SetBooleanField(info_obj, is_online, isonline);
    env->SetIntField(info_obj, user_type, usertype);
    env->SetIntField(info_obj, special_type, specialtype);
    env->SetIntField(info_obj, device_type, devicetype);
    jstring ip_str;
    ip_str = stringToJstring(env,ip);
    env->SetObjectField(info_obj, ip_, ip_str);
    env->DeleteLocalRef(ip_str);
    env->SetIntField(info_obj, protocol_type, protocoltype);
    env->SetIntField(info_obj, band_width, bandwidth);
    jstring calloption_str;
    calloption_str = stringToJstring(env,calloption);
    env->SetObjectField(info_obj, calloption_, calloption_str);
    env->DeleteLocalRef(calloption_str);
    return info_obj;
}


jobject ScreenLabelStruct(JNIEnv *env, SRScreenLableAttr *sceenlabel, jobject info_obj) {
    int Labelterid = sceenlabel->labelterid;
    int Operatetype = sceenlabel->operatetype;
    int Lableid = sceenlabel->lableid;
    int Labletype = sceenlabel->labletype;
    int Lablesize = sceenlabel->lablesize;
    int Lablecolor = sceenlabel->lablecolor;
    int Linetype = sceenlabel->linetype;
    int Leftuppoints_x = sceenlabel->leftuppoints_x;
    int Leftuppoints_y = sceenlabel->leftuppoints_y;
    int Rightdownpoints_x = sceenlabel->rightdownpoints_x;
    int Rightdownpoints_y = sceenlabel->rightdownpoints_y;
    int Resolution_x = sceenlabel->resolution_x;
    int Resolution_y = sceenlabel->resolution_y;


    jfieldID labelterid_ = env->GetFieldID(screenLabel_class, "labelterid", "I");
    jfieldID operatetype_ = env->GetFieldID(screenLabel_class, "operatetype", "I");
    jfieldID lableid_ = env->GetFieldID(screenLabel_class, "lableid", "I");
    jfieldID labletype_ = env->GetFieldID(screenLabel_class, "labletype", "I");
    jfieldID lablesize_ = env->GetFieldID(screenLabel_class, "lablesize", "I");
    jfieldID lablecolor_ = env->GetFieldID(screenLabel_class, "lablecolor", "I");
    jfieldID linetype_ = env->GetFieldID(screenLabel_class, "linetype", "I");

    jfieldID leftuppoints_x_ = env->GetFieldID(screenLabel_class, "leftuppoints_x", "I");
    jfieldID leftuppoints_y_ = env->GetFieldID(screenLabel_class, "leftuppoints_y", "I");
    jfieldID rightdownpoints_x_ = env->GetFieldID(screenLabel_class, "rightdownpoints_x", "I");
    jfieldID rightdownpoints_y_ = env->GetFieldID(screenLabel_class, "rightdownpoints_y", "I");
    jfieldID resolution_x_ = env->GetFieldID(screenLabel_class, "resolution_x", "I");
    jfieldID resolution_y_ = env->GetFieldID(screenLabel_class, "resolution_y", "I");


    env->SetIntField(info_obj, labelterid_, Labelterid);
    env->SetIntField(info_obj, operatetype_, Operatetype);
    env->SetIntField(info_obj, lableid_, Lableid);
    env->SetIntField(info_obj, labletype_, Labletype);
    env->SetIntField(info_obj, lablesize_, Lablesize);
    env->SetIntField(info_obj, lablecolor_, Lablecolor);
    env->SetIntField(info_obj, linetype_, Labletype);

    env->SetIntField(info_obj, leftuppoints_x_, Leftuppoints_x);
    env->SetIntField(info_obj, leftuppoints_y_, Leftuppoints_y);
    env->SetIntField(info_obj, rightdownpoints_x_, Rightdownpoints_x);
    env->SetIntField(info_obj, rightdownpoints_y_, Rightdownpoints_y);
    env->SetIntField(info_obj, resolution_x_, Resolution_x);
    env->SetIntField(info_obj, resolution_y_, Resolution_y);

    return info_obj;
}


jobject errorStruct(JNIEnv *env, int errorCode, std::string brief_reason, std::string detail_reason,
                    jobject info_obj) {
    jfieldID cur_error_field = env->GetFieldID(SRError_class, "cur_error", "I");
    jfieldID brief_reason_field = env->GetFieldID(SRError_class, "brief_reason",
                                                  "Ljava/lang/String;");
    jfieldID detail_reason_field = env->GetFieldID(SRError_class, "detail_reason",
                                                   "Ljava/lang/String;");
    env->SetIntField(info_obj, cur_error_field, errorCode);
    jstring brief_reasonStr;
    brief_reasonStr = stringToJstring(env, brief_reason);
    jstring detail_reasonStr;
    detail_reasonStr = stringToJstring(env, detail_reason);

    env->SetObjectField(info_obj, brief_reason_field, brief_reasonStr);

    env->DeleteLocalRef(brief_reasonStr);

    env->SetObjectField(info_obj, detail_reason_field, detail_reasonStr);

    env->DeleteLocalRef(detail_reasonStr);


    return info_obj;
}


jobject VoiceActiveInfoStruct(JNIEnv *env, int talkId, int energy,
                              jobject info_obj) {
    jfieldID talk_id_ = env->GetFieldID(VoiceActiveInfo_class, "talk_id", "I");
    jfieldID energy_ = env->GetFieldID(VoiceActiveInfo_class, "energy", "I");
    env->SetIntField(info_obj, talk_id_, talkId);
    env->SetIntField(info_obj, energy_, energy);
    return info_obj;
}

jobject SRMediaPScreenInfoStruct(JNIEnv *env, int screenid, int screentype,
                                 jobject mediaPScreenInfoObj) {
    jfieldID screen_id_ = env->GetFieldID(srMediaInfoPScreenInfo_class, "screenid", "I");
    jfieldID screen_type_ = env->GetFieldID(srMediaInfoPScreenInfo_class, "screentype", "I");
    env->SetIntField(mediaPScreenInfoObj, screen_id_, screenid);
    env->SetIntField(mediaPScreenInfoObj, screen_type_, screentype);
    return mediaPScreenInfoObj;
}


jobject getConfInfoState(JNIEnv *env, ConfStatus &confstatus, jobject info_obj) {
    string _confname = confstatus.confname;
    int _confmode = confstatus.confmode;
    unsigned int _chairmansuid = confstatus.chairmansuid;
    int _duovideoterid = confstatus.duovideoterid;
    int _stdterseeingstyle = confstatus.stdterseeingstyle;
    bool _isduovideostart = confstatus.isduovideostart;
    bool _isconflocked = confstatus.isconflocked;
    bool _isforcemute = confstatus.isforcemute;
    bool _isdisplaytername = confstatus.isdisplaytername;
    bool _issubtitlestart = confstatus.issubtitlestart;
    string _subtitlemsg = confstatus.subtitlemsg;
    int _recstate = confstatus.recordinfo.recstate;
    string _failreason = confstatus.recordinfo.failreason;
    int _livestate=confstatus.liveinfo.livestate;
    string _livefailreason=confstatus.liveinfo.failreason;
    string _liveplayurl = confstatus.liveinfo.liveplayurl;

    jfieldID conf_name = env->GetFieldID(ConfInfoStatus_class, "confname", "Ljava/lang/String;");
    jfieldID conf_mode = env->GetFieldID(ConfInfoStatus_class, "confmode", "I");
    jfieldID chairman_suid = env->GetFieldID(ConfInfoStatus_class, "chairmansuid", "I");
    jfieldID duovideo_terid = env->GetFieldID(ConfInfoStatus_class, "duovideoterid", "I");
    jfieldID stdterseeing_style = env->GetFieldID(ConfInfoStatus_class, "stdterseeingstyle", "I");
    jfieldID is_duovideostart = env->GetFieldID(ConfInfoStatus_class, "isduovideostart", "Z");
    jfieldID is_conflocked = env->GetFieldID(ConfInfoStatus_class, "isconflocked", "Z");
    jfieldID is_forcemute = env->GetFieldID(ConfInfoStatus_class, "isforcemute", "Z");
    jfieldID is_displaytername = env->GetFieldID(ConfInfoStatus_class, "isdisplaytername", "Z");
    jfieldID is_subtitlestart = env->GetFieldID(ConfInfoStatus_class, "issubtitlestart", "Z");
    jfieldID subtitle_msg = env->GetFieldID(ConfInfoStatus_class, "subtitlemsg",
                                            "Ljava/lang/String;");
    jfieldID rec_state = env->GetFieldID(ConfInfoStatus_class, "recstate", "I");
    jfieldID fail_reason = env->GetFieldID(ConfInfoStatus_class, "recfailreason",
                                           "Ljava/lang/String;");
    jfieldID live_state = env->GetFieldID(ConfInfoStatus_class, "livestate", "I");
    jfieldID live_fail_reason = env->GetFieldID(ConfInfoStatus_class, "livefailreason",
                                           "Ljava/lang/String;");
    jfieldID live_play_url = env->GetFieldID(ConfInfoStatus_class, "liveplayurl",
                                             "Ljava/lang/String;");
    jstring confnameStr = stringToJstring(env, _confname);
    env->SetObjectField(info_obj, conf_name, confnameStr);
    env->DeleteLocalRef(confnameStr);
    env->SetIntField(info_obj, conf_mode, _confmode);
    env->SetIntField(info_obj, chairman_suid, _chairmansuid);
    env->SetIntField(info_obj, duovideo_terid, _duovideoterid);
    env->SetIntField(info_obj, stdterseeing_style, _stdterseeingstyle);
    env->SetBooleanField(info_obj, is_duovideostart, _isduovideostart);
    env->SetBooleanField(info_obj, is_conflocked, _isconflocked);
    env->SetBooleanField(info_obj, is_forcemute, _isforcemute);
    env->SetBooleanField(info_obj, is_displaytername, _isdisplaytername);
    env->SetBooleanField(info_obj, is_subtitlestart, _issubtitlestart);
    jstring subtitleMsgStr = stringToJstring(env, _subtitlemsg);
    env->SetObjectField(info_obj, subtitle_msg, subtitleMsgStr);
    env->DeleteLocalRef(subtitleMsgStr);
    env->SetIntField(info_obj, rec_state, _recstate);
    jstring failreasonStr = stringToJstring(env, _failreason);
    env->SetObjectField(info_obj, fail_reason, failreasonStr);
    env->SetIntField(info_obj, live_state, _livestate);
    jstring livefailreasonStr = stringToJstring(env, _livefailreason);
    env->SetObjectField(info_obj, live_fail_reason, livefailreasonStr);
    jstring liveplayurlStr = stringToJstring(env, _liveplayurl);
    env->SetObjectField(info_obj, live_play_url, liveplayurlStr);
    return info_obj;
}


jobject SendStreamInfoStruct(JNIEnv *env, const SendStreamInfo &stats, jobject info_obj) {
    char *audio_CodecName = (char *) stats.audioCodecName;
    int audio_SampleRate = stats.audioSampleRate;
    int audio_Bitrate = stats.audioBitrate;
    char *video_CodecName = (char *) stats.videoCodecName;
    int video_LFps = stats.videoLFps;
    int video_LBitrate = stats.videoLBitrate;
    int video_LWidth = stats.videoLWidth;
    int video_LHeight = stats.videoLHeight;
    int video_MFps = stats.videoMFps;
    int video_MBitrate = stats.videoMBitrate;
    int video_MWidth = stats.videoMWidth;
    int video_MHeight = stats.videoMHeight;
    int video_HFps = stats.videoHFps;
    int video_HBitrate = stats.videoHBitrate;
    int video_HWidth = stats.videoHWidth;
    int video_HHeight = stats.videoHHeight;
    char *h239_CodecName = (char *) stats.h239CodecName;
    int h239_Fps = stats.h239Fps;
    int h239_Bitrate = stats.h239Bitrate;
    int h239_Width = stats.h239Width;
    int h239_Height = stats.h239Height;
    int up_qos_kbps = stats.up_qos_kbps;
    int upload_network_status = stats.network_upload_status;

    jfieldID audioCodecName_ = env->GetFieldID(SRSendStreamInfo_class, "audioCodecName",
                                               "Ljava/lang/String;");
    jfieldID audioSampleRate_ = env->GetFieldID(SRSendStreamInfo_class, "audioSampleRate", "I");
    jfieldID audioBitrate_ = env->GetFieldID(SRSendStreamInfo_class, "audioBitrate", "I");
    jfieldID videoCodecName_ = env->GetFieldID(SRSendStreamInfo_class, "videoCodecName",
                                               "Ljava/lang/String;");
    jfieldID videoLFps_ = env->GetFieldID(SRSendStreamInfo_class, "videoLFps", "I");
    jfieldID videoLBitrate_ = env->GetFieldID(SRSendStreamInfo_class, "videoLBitrate", "I");
    jfieldID videoLWidth_ = env->GetFieldID(SRSendStreamInfo_class, "videoLWidth", "I");
    jfieldID videoLHeight_ = env->GetFieldID(SRSendStreamInfo_class, "videoLHeight", "I");
    jfieldID videoMFps_ = env->GetFieldID(SRSendStreamInfo_class, "videoMFps", "I");
    jfieldID videoMBitrate_ = env->GetFieldID(SRSendStreamInfo_class, "videoMBitrate", "I");
    jfieldID videoMWidth_ = env->GetFieldID(SRSendStreamInfo_class, "videoMWidth", "I");
    jfieldID videoMHeight_ = env->GetFieldID(SRSendStreamInfo_class, "videoMHeight", "I");
    jfieldID videoHFps_ = env->GetFieldID(SRSendStreamInfo_class, "videoHFps", "I");
    jfieldID videoHBitrate_ = env->GetFieldID(SRSendStreamInfo_class, "videoHBitrate", "I");
    jfieldID videoHWidth_ = env->GetFieldID(SRSendStreamInfo_class, "videoHWidth", "I");
    jfieldID videoHHeight_ = env->GetFieldID(SRSendStreamInfo_class, "videoHHeight", "I");
    jfieldID h239CodecName_ = env->GetFieldID(SRSendStreamInfo_class, "h239CodecName",
                                              "Ljava/lang/String;");
    jfieldID h239Fps_ = env->GetFieldID(SRSendStreamInfo_class, "h239Fps", "I");
    jfieldID h239Bitrate_ = env->GetFieldID(SRSendStreamInfo_class, "h239Bitrate", "I");
    jfieldID h239Width_ = env->GetFieldID(SRSendStreamInfo_class, "h239Width", "I");
    jfieldID h239Height_ = env->GetFieldID(SRSendStreamInfo_class, "h239Height", "I");
    jfieldID up_qos_kbps_ = env->GetFieldID(SRSendStreamInfo_class, "up_qos_kbps", "I");
    jfieldID network_state_ = env->GetFieldID(SRSendStreamInfo_class, "network_state", "I");


    jstring audioCN = chartoJstring(env, audio_CodecName);
    env->SetObjectField(info_obj, audioCodecName_, audioCN);
    env->DeleteLocalRef(audioCN);
    env->SetIntField(info_obj, audioSampleRate_, audio_SampleRate);
    env->SetIntField(info_obj, audioBitrate_, audio_Bitrate);
    jstring videoCN = chartoJstring(env, video_CodecName);
    env->SetObjectField(info_obj, videoCodecName_, videoCN);
    env->DeleteLocalRef(videoCN);
    env->SetIntField(info_obj, videoLFps_, video_LFps);
    env->SetIntField(info_obj, videoLBitrate_, video_LBitrate);
    env->SetIntField(info_obj, videoLWidth_, video_LWidth);
    env->SetIntField(info_obj, videoLHeight_, video_LHeight);
    env->SetIntField(info_obj, videoMFps_, video_MFps);
    env->SetIntField(info_obj, videoMBitrate_, video_MBitrate);
    env->SetIntField(info_obj, videoMWidth_, video_MWidth);
    env->SetIntField(info_obj, videoMHeight_, video_MHeight);
    env->SetIntField(info_obj, videoHFps_, video_HFps);
    env->SetIntField(info_obj, videoHBitrate_, video_HBitrate);
    env->SetIntField(info_obj, videoHWidth_, video_HWidth);
    env->SetIntField(info_obj, videoHHeight_, video_HHeight);
    jstring h239CN = chartoJstring(env, h239_CodecName);
    env->SetObjectField(info_obj, h239CodecName_, h239CN);
    env->DeleteLocalRef(h239CN);
    env->SetIntField(info_obj, h239Fps_, h239_Fps);
    env->SetIntField(info_obj, h239Bitrate_, h239_Bitrate);
    env->SetIntField(info_obj, h239Width_, h239_Width);
    env->SetIntField(info_obj, h239Height_, h239_Height);
    env->SetIntField(info_obj, up_qos_kbps_, up_qos_kbps);
    env->SetIntField(info_obj, network_state_, upload_network_status);
    return info_obj;
}

jobject RecvStreamInfoStruct(JNIEnv *env, const RecvStreamInfo &stats, jobject info_obj) {
    std::deque <RecvAudioStream> recvAudioStream = stats.audioStreams;
    std::deque <RecvVideoStream> recvVideoStream = stats.videoStreams;
    RecvVideoStream recvh239Stream = stats.h239Stream;
    int downQos = stats.down_qos_kbps;
    int download_network_status = stats.network_download_status;

    jfieldID audio_stream_list_ = env->GetFieldID(SRRecvStreamInfo_class, "recvAudioStreamInfoList",
                                                  "Ljava/util/ArrayList;");
    jfieldID video_stream_list_ = env->GetFieldID(SRRecvStreamInfo_class, "recvVideoStreamInfoList",
                                                  "Ljava/util/ArrayList;");
    jfieldID h239_stream_ = env->GetFieldID(SRRecvStreamInfo_class, "recvH239StreamInfo",
                                            "Lorg/suirui/srpaas/entry/RecvVideoStreamInfo;");
    jfieldID down_qos_kbps_ = env->GetFieldID(SRRecvStreamInfo_class, "down_qos_kbps", "I");
    jfieldID network_state_ = env->GetFieldID(SRRecvStreamInfo_class, "network_status", "I");
    //add audio list
    jmethodID audio_construct = env->GetMethodID(class_ArrayList, "<init>", "()V");
    jobject audio_obj_List = env->NewObject(class_ArrayList, audio_construct, "");
    jmethodID audio_list_add = env->GetMethodID(class_ArrayList, "add",
                                                "(Ljava/lang/Object;)Z");
    jmethodID audio_info_method = env->GetMethodID(RecvAudioStreamInfo_class, "<init>", "()V");

    int audioNum = recvAudioStream.size();
//#if defined(LOG_JNI)
//    Log("SRSdkJni:........onRecvStreamInfoStatsCallBack_JNI.audioNum.___%d:",audioNum);
//#endif
    for (int i = 0; i < audioNum; i++) {
        RecvAudioStream &audioInfo = recvAudioStream.at(i);
        int audio_id = audioInfo.id;
        char *audio_codecName = (char *) audioInfo.codecName;
        jstring audio_codecName_str = chartoJstring(env, audio_codecName);
        int audio_sampleRate = audioInfo.sampleRate;
        int audio_bitRate = audioInfo.bitRate;
        int audio_recCodecChs = audioInfo.recCodecChs;
        float audio_loseRate = audioInfo.loseRate;
        jobject audioStreamInfo_obj = env->NewObject(RecvAudioStreamInfo_class, audio_info_method,
                                                     "");
        jobject audio_info = RecvAudioStreamStruct(env, audio_id, audio_codecName_str,
                                                   audio_sampleRate,
                                                   audio_bitRate, audio_recCodecChs, audio_loseRate,
                                                   audioStreamInfo_obj);
        env->CallBooleanMethod(audio_obj_List, audio_list_add, audio_info);
        env->DeleteLocalRef(audioStreamInfo_obj);
    }


    //add video list
    jmethodID video_construct = env->GetMethodID(class_ArrayList, "<init>", "()V");
    jobject video_obj_List = env->NewObject(class_ArrayList, video_construct, "");
    jmethodID video_list_add = env->GetMethodID(class_ArrayList, "add",
                                                "(Ljava/lang/Object;)Z");
    jmethodID video_info_method = env->GetMethodID(RecvVideoStreamInfo_class, "<init>", "()V");
    int videoNum = recvVideoStream.size();
//#if defined(LOG_JNI)
//    Log("SRSdkJni:........onRecvStreamInfoStatsCallBack_JNI.videoNum.___%d:",videoNum);
//#endif
    for (int i = 0; i < videoNum; i++) {
        RecvVideoStream &videoInfo = recvVideoStream.at(i);
        int video_id = videoInfo.id;
        char *video_codecName = (char *) videoInfo.codecName;
        jstring video_codecName_str = chartoJstring(env, video_codecName);
        int video_fps = videoInfo.fps;
        int video_bitRate = videoInfo.bitRate;
        float video_loseRate = videoInfo.loseRate;
        int video_width = videoInfo.width;
        int video_height = videoInfo.height;
        jobject videoStreamInfo_obj = env->NewObject(RecvVideoStreamInfo_class, video_info_method,
                                                     "");
        jobject video_info = RecvVideoStreamStruct(env, video_id, video_codecName_str, video_fps,
                                                   video_bitRate, video_loseRate, video_width,
                                                   video_height, videoStreamInfo_obj);
        env->CallBooleanMethod(video_obj_List, video_list_add, video_info);
        env->DeleteLocalRef(videoStreamInfo_obj);
    }

    jmethodID h239_info_method = env->GetMethodID(RecvVideoStreamInfo_class, "<init>", "()V");
    int h239_id = recvh239Stream.id;
    char *h239_codecName = (char *) recvh239Stream.codecName;
    jstring h239_codecName_str = chartoJstring(env, h239_codecName);
    int h239_fps = recvh239Stream.fps;
    int h239_bitRate = recvh239Stream.bitRate;
    float h239_loseRate = recvh239Stream.loseRate;
    int h239_width = recvh239Stream.width;
    int h239_height = recvh239Stream.height;
    jobject h239StreamInfo_obj = env->NewObject(RecvVideoStreamInfo_class, h239_info_method,
                                                "");
    jobject h239_info = RecvH239StreamStruct(env, h239_id, h239_codecName_str, h239_fps,
                                             h239_bitRate, h239_loseRate, h239_width,
                                             h239_height, h239StreamInfo_obj);

    env->SetObjectField(info_obj, audio_stream_list_, audio_obj_List);
    env->SetObjectField(info_obj, video_stream_list_, video_obj_List);
    env->SetObjectField(info_obj, h239_stream_, h239_info);
    env->SetIntField(info_obj, down_qos_kbps_, downQos);
    env->SetIntField(info_obj, network_state_, download_network_status);
    env->DeleteLocalRef(h239StreamInfo_obj);
    return info_obj;
}

jobject RecvAudioStreamStruct(JNIEnv *env, int id, jstring codecName,
                              int sampleRate, int bitRate, int recCodecChs,
                              float loseRate, jobject info_obj) {
    jfieldID audio_id_ = env->GetFieldID(RecvAudioStreamInfo_class, "id", "I");
    jfieldID audio_codecName_ = env->GetFieldID(RecvAudioStreamInfo_class, "codecName",
                                                "Ljava/lang/String;");
    jfieldID audio_sampleRate_ = env->GetFieldID(RecvAudioStreamInfo_class, "sampleRate", "I");
    jfieldID audio_bitRate_ = env->GetFieldID(RecvAudioStreamInfo_class, "bitRate", "I");
    jfieldID audio_recCodecChs_ = env->GetFieldID(RecvAudioStreamInfo_class, "recCodecChs", "I");
    jfieldID audio_loseRate_ = env->GetFieldID(RecvAudioStreamInfo_class, "loseRate", "F");
    env->SetIntField(info_obj, audio_id_, id);
    env->SetObjectField(info_obj, audio_codecName_, codecName);
    env->SetIntField(info_obj, audio_sampleRate_, sampleRate);
    env->SetIntField(info_obj, audio_bitRate_, bitRate);
    env->SetIntField(info_obj, audio_recCodecChs_, recCodecChs);
    env->SetFloatField(info_obj, audio_loseRate_, loseRate);
    return info_obj;
}

jobject RecvVideoStreamStruct(JNIEnv *env, int id, jstring codecName,
                              int fps, int bitRate, float loseRate,
                              int width, int height, jobject info_obj) {
    jfieldID video_id_ = env->GetFieldID(RecvVideoStreamInfo_class, "id", "I");
    jfieldID video_codecName_ = env->GetFieldID(RecvVideoStreamInfo_class, "codecName",
                                                "Ljava/lang/String;");
    jfieldID video_fps_ = env->GetFieldID(RecvVideoStreamInfo_class, "fps", "I");
    jfieldID video_bitRate_ = env->GetFieldID(RecvVideoStreamInfo_class, "bitRate", "I");
    jfieldID video_loseRate_ = env->GetFieldID(RecvVideoStreamInfo_class, "loseRate", "F");
    jfieldID video_width_ = env->GetFieldID(RecvVideoStreamInfo_class, "width", "I");
    jfieldID video_height_ = env->GetFieldID(RecvVideoStreamInfo_class, "height", "I");

    env->SetIntField(info_obj, video_id_, id);
    env->SetObjectField(info_obj, video_codecName_, codecName);
    env->SetIntField(info_obj, video_fps_, fps);
    env->SetIntField(info_obj, video_bitRate_, bitRate);
    env->SetFloatField(info_obj, video_loseRate_, loseRate);
    env->SetIntField(info_obj, video_width_, width);
    env->SetIntField(info_obj, video_height_, height);
    return info_obj;
}

jobject RecvH239StreamStruct(JNIEnv *env, int id, jstring codecName,
                             int fps, int bitRate, float loseRate,
                             int width, int height, jobject info_obj) {
    jfieldID h239_id_ = env->GetFieldID(RecvVideoStreamInfo_class, "id", "I");
    jfieldID h239_codecName_ = env->GetFieldID(RecvVideoStreamInfo_class, "codecName",
                                               "Ljava/lang/String;");
    jfieldID h239_fps_ = env->GetFieldID(RecvVideoStreamInfo_class, "fps", "I");
    jfieldID h239_bitRate_ = env->GetFieldID(RecvVideoStreamInfo_class, "bitRate", "I");
    jfieldID h239_loseRate_ = env->GetFieldID(RecvVideoStreamInfo_class, "loseRate", "F");
    jfieldID h239_width_ = env->GetFieldID(RecvVideoStreamInfo_class, "width", "I");
    jfieldID h239_height_ = env->GetFieldID(RecvVideoStreamInfo_class, "height", "I");
    env->SetIntField(info_obj, h239_id_, id);
    env->SetObjectField(info_obj, h239_codecName_, codecName);
    env->SetIntField(info_obj, h239_fps_, fps);
    env->SetIntField(info_obj, h239_bitRate_, bitRate);
    env->SetFloatField(info_obj, h239_loseRate_, loseRate);
    env->SetIntField(info_obj, h239_width_, width);
    env->SetIntField(info_obj, h239_height_, height);
    return info_obj;
}


jobject LiveSettingInfo(JNIEnv *env, std::string chairman, std::string subject, std::string digest,int ispublic,std::string livepwd,jobject liveInfo){
    jfieldID str_chairman = env->GetFieldID(srOnliveInfo_class, "chairman", "Ljava/lang/String;");
    jfieldID str_subject = env->GetFieldID(srOnliveInfo_class, "subject","Ljava/lang/String;");
    jfieldID str_digest = env->GetFieldID(srOnliveInfo_class, "digest","Ljava/lang/String;");
    jfieldID str_ispublic = env->GetFieldID(srOnliveInfo_class, "ispublic","I");
    jfieldID str_livepwd = env->GetFieldID(srOnliveInfo_class, "livepwd","Ljava/lang/String;");
    jstring  chairman_ = stringToJstring(env, chairman);
    env->SetObjectField(liveInfo, str_chairman, chairman_);
    env->DeleteLocalRef(chairman_);

    jstring  subject_ = stringToJstring(env, subject);
    env->SetObjectField(liveInfo, str_subject, subject_);
    env->DeleteLocalRef(subject_);

    jstring  digest_ = stringToJstring(env, digest);
    env->SetObjectField(liveInfo, str_digest, digest_);
    env->DeleteLocalRef(digest_);

    env->SetIntField(liveInfo, str_ispublic, ispublic);

    jstring  livepwd_ = stringToJstring(env, livepwd);
    env->SetObjectField(liveInfo, str_livepwd, livepwd_);
    env->DeleteLocalRef(livepwd_);
    return liveInfo;
}

/*****回调********************************************************************************************************************************/




//加入会议回调
void OnRspJoinConfCallBack_JNI(const bool isok, const SRConferenceAbnormal &error,
                               const int stermid) {

#if defined(LOG_JNI)
    Log("SRSdkJni:...OnRspJoinConfCallBack_JNI......__%d______%d",isok,stermid);
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jmethodID info_method = env->GetMethodID(SRError_class, "<init>", "()V");
    jobject error_obj = env->NewObject(SRError_class, info_method, "");

    int errorCode = (int) error.cur_error;
    string brief_reason = error.brief_reason;
    string detail_reason = error.detail_reason;
    jobject info = errorStruct(env, errorCode, brief_reason, detail_reason, error_obj);

    jboolean
            isStatus = (jboolean)
    isok;
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "OnRspJoinConfCallBack",
                                                "(ZLorg/suirui/srpaas/entry/SRError;I)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, isok, info,
                            stermid);
        env->DeleteLocalRef(error_obj);
        env->DeleteLocalRef(obj_qtt);
    }
    Log("SRSdkJni:...OnRspJoinConfCallBack_JNI...11...__%d______%d", isok, stermid);
    gs_jvm->DetachCurrentThread();
}

//退出会议回调
void OnExitConfCallBack_JNI(const char *exit_reason) {
#if defined(LOG_JNI)
    Log("SRSdkJni...OnExitConfCallBack_JNI.........");
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

//新终端加入会议
void onNewTermJoinCallBack_JNI(const TermInfo &join_info) {
//#if defined(LOG_JNI)
//    Log("SRSdkJni..onNewTermJoinCallBack_JNI.........___%d____%s",join_info.termid,join_info.tername.c_str());
//#endif
//    JNIEnv *env;
//    gs_jvm->AttachCurrentThread(&env, NULL);
    int needsDetach;
    JNIEnv *env = getJNIEnv(&needsDetach);
    file_write_log("SRSdkJni..onNewTermJoinCallBack_JNI......start");

    jmethodID construct = env->GetMethodID(class_ArrayList, "<init>", "()V");
    jobject obj_List = env->NewObject(class_ArrayList, construct, "");
    jmethodID list_add = env->GetMethodID(class_ArrayList, "add",
                                          "(Ljava/lang/Object;)Z");
    jmethodID info_method = env->GetMethodID(info_class, "<init>", "()V");
    int termId = join_info.termid;
    unsigned int suid = join_info.suid;
    string tername = join_info.tername;
    bool ismuted = join_info.ismuted;
    bool iscamera_on = join_info.iscamera_on;
    bool ishandup = join_info.ishandup;
    bool isonline = join_info.isonline;
    int usertype = join_info.usertype;
    int specialtype = join_info.specialtype;
    int devicetype = join_info.devicetype;
    string ip = join_info.ip;
    int protocoltype = join_info.protocoltype;
    int bandwidth = join_info.bandwidth;
    string calloption = join_info.calloption;
    file_write_log("SRSdkJni..onNewTermJoinCallBack_JNI......start.....termId:%d", termId);

    if (Callback_class != NULL) {
        jobject info_obj = env->NewObject(info_class, info_method, "");
        jobject info = TermInfoStruct(env, termId, suid, tername, ismuted, iscamera_on,
                                      ishandup, isonline, usertype, specialtype,devicetype,
                                      ip,protocoltype,bandwidth,calloption,info_obj);
        env->CallBooleanMethod(obj_List, list_add, info);
        env->DeleteLocalRef(info_obj);
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onNewTermJoinCallBack",
                                                "(Ljava/util/ArrayList;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, obj_List);
        env->DeleteLocalRef(obj_qtt);
        env->DeleteLocalRef(obj_List);
    }

    if (needsDetach) {
        gs_jvm->DetachCurrentThread();
        file_write_log("SRSdkJni..onNewTermJoinCallBack_JNI.......end");
    }
}

//终端离开会议
void OnTermLeaveCallBack_JNI(const int leave_stermid, const SRConferenceAbnormal &error) {
#if defined(LOG_JNI)
    Log("SRSdkJni..OnTermLeaveCallBack_JNI.........___%d",leave_stermid);
#endif
//    JNIEnv *env;
//    gs_jvm->AttachCurrentThread(&env, NULL);
    int needsDetach;
    JNIEnv *env = getJNIEnv(&needsDetach);
    file_write_log("SRSdkJni..OnTermLeaveCallBack_JNI......start...leave_stermid:%d",
                   leave_stermid);

    jmethodID infos_method = env->GetMethodID(SRError_class, "<init>", "()V");
    jobject error_obj = env->NewObject(SRError_class, infos_method, "");

    int errorCode = (int) error.cur_error;
    string brief_reason = error.brief_reason;
    string detail_reason = error.detail_reason;
    jobject info = errorStruct(env, errorCode, brief_reason, detail_reason, error_obj);


    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onTermLeaveCallBack",
                                                "(ILorg/suirui/srpaas/entry/SRError;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, leave_stermid, info);
        env->DeleteLocalRef(error_obj);
        env->DeleteLocalRef(obj_qtt);
    }
    if (needsDetach) {
        gs_jvm->DetachCurrentThread();
        file_write_log("SRSdkJni.....OnTermLeaveCallBack_JNI......end....leave_stermid:%d",
                       leave_stermid);
    }
}


//共享内存

JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_setReceiveByteBufferData(
        JNIEnv *env, jclass jcls,jobject bufObj){
    Log("SRSdkJni..setReceiveByteBufferData.dd...bufData...create...");

    jclass cls = env->GetObjectClass(bufObj);
    jfieldID yfid = env->GetFieldID(cls, "yData","Ljava/nio/ByteBuffer;");
    jobject yobj = env->GetObjectField(bufObj, yfid);
    yBufData= (char*)env->GetDirectBufferAddress(yobj);
    jlong yLength=  env->GetDirectBufferCapacity(yobj);
    env->DeleteLocalRef(yobj);

    jfieldID ufid = env->GetFieldID(cls, "uData","Ljava/nio/ByteBuffer;");
    jobject uobj = env->GetObjectField(bufObj, ufid);
    uBufData= (char*)env->GetDirectBufferAddress(uobj);
    jlong uLength=  env->GetDirectBufferCapacity(uobj);
    env->DeleteLocalRef(uobj);

    jfieldID vfid = env->GetFieldID(cls, "vData","Ljava/nio/ByteBuffer;");
    jobject vobj = env->GetObjectField(bufObj, vfid);
    vBufData= (char*)env->GetDirectBufferAddress(vobj);
    jlong vLength=  env->GetDirectBufferCapacity(vobj);
    env->DeleteLocalRef(vobj);
//    env->DeleteGlobalRef(cls);




    Log("SRSdkJni..setReceiveByteBufferData.eee.end..y:%d,u:%d,v%d",(int)yLength,(int)uLength,(int)vLength);
    return 1;
}

void OnRenderFrameCallBack_JNI(int stermid, int flag,
                               VideoFrame &frame) {
//    Log("SRSdkJni..OnRenderFrameCallBack_JNI...");
    int needsDetach;
    JNIEnv *env = getJNIEnv(&needsDetach);
    if (!env) {
        return;
    }
    int format=(int)frame.format;
    int width = frame.width;
    int height = frame.height;
    int length=frame.ySize;
    if(yBufData!=NULL ){//共享内存
//           yBufData = (char *)frame.yBuffer;
            memcpy(yBufData,(char *)frame.yBuffer,frame.ySize);
        if(uBufData!=NULL && frame.uBuffer!=NULL) {
//            uBufData = (char *) frame.uBuffer;
            memcpy(uBufData,(char *)frame.uBuffer,frame.uSize);
        }
        if(vBufData!=NULL && frame.vBuffer!=NULL){
//            vBufData=( char *) frame.vBuffer;
            memcpy(vBufData,(char *)frame.vBuffer,frame.vSize);
        }

        Log("SRSdkJni..OnRenderFrameCallBack_JNI...y:%d,u:%d,v:%d",frame.ySize,frame.uSize,frame.vSize);

        if (Callback_class != NULL) {
            jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                         "()V");
            jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");

            jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                    "onRenderCallBackCallBack", "(IIIIII)V");
            env->CallVoidMethod(obj_qtt, gJinMethod, stermid, flag, format, width, height,length);
            env->DeleteLocalRef(obj_qtt);
        }
    }else{
        jbyteArray yByte = getByteToArray(env, (unsigned char *) frame.yBuffer, frame.ySize);
        jbyteArray uByte = getByteToArray(env, (unsigned char *) frame.uBuffer, frame.uSize);
        jbyteArray vByte = getByteToArray(env, (unsigned char *) frame.vBuffer, frame.vSize);
        if (yByte == NULL || uByte == NULL || vByte == NULL) {
            gs_jvm->DetachCurrentThread();
            return;
        }
        if (Callback_class != NULL) {
            jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                         "()V");
            jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");

            jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                    "onRenderCallBackCallBack", "(III[B[B[BIII)V");
            env->CallVoidMethod(obj_qtt, gJinMethod, stermid, flag, format,yByte, uByte, vByte,
                                width, height,length);

            env->DeleteLocalRef(obj_qtt);
        }
        env->DeleteLocalRef(yByte);
        env->DeleteLocalRef(uByte);
        env->DeleteLocalRef(vByte);
    }
    if (needsDetach == 1) {
        gs_jvm->DetachCurrentThread();
    }

}

/**
 * @brief OnRenderFrame     收到视频数据 回调
 * @param stermid           视频所属终端termid
 * @param flag              视屏类型
 * @param frame             视频数据
 */
//void OnRenderFrameCallBack_JNI(int stermid, int flag,
//                               VideoFrame &frame) {
//    int needsDetach;
//    JNIEnv *env = getJNIEnv(&needsDetach);
////    file_write_log(
////            "SRSdkJni..OnRenderFrameCallBack_JNI.........start...stermid:%d...needsDetach:%d",
////            stermid, needsDetach);
//
//    if (!env) {
//        return;
//    }
////    Log("SRSdkJni:........OnRenderFrameCallBack_JNI.......flag:%d",flag);
//    int format=(int)frame.format;
////    Log("SRSdkJni:........OnRenderFrameCallBack_JNI.......flag:%d ; format:%d",flag,format);
//    int width = frame.width;
//    int height = frame.height;
//    int length=frame.ySize;
////    Log("SRSdkJni:...OnRenderFrameCallBack_JNI......_width:%d______length:%d_____uSize:%d",width,length,frame.uSize);
//    jbyteArray yByte = getByteToArray(env, (unsigned char *) frame.yBuffer, frame.ySize);
//    jbyteArray uByte = getByteToArray(env, (unsigned char *) frame.uBuffer, frame.uSize);
//    jbyteArray vByte = getByteToArray(env, (unsigned char *) frame.vBuffer, frame.vSize);
//    if (yByte == NULL || uByte == NULL || vByte == NULL) {
//        gs_jvm->DetachCurrentThread();
//        return;
//    }
//    if (Callback_class != NULL) {
//        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
//                                                     "()V");
//        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
//
//        jmethodID gJinMethod = env->GetMethodID(Callback_class,
//                                                "onRenderCallBackCallBack", "(III[B[B[BIII)V");
//        env->CallVoidMethod(obj_qtt, gJinMethod, stermid, flag, format,yByte, uByte, vByte,
//                            width, height,length);
//
//        env->DeleteLocalRef(obj_qtt);
//    }
//    env->DeleteLocalRef(yByte);
//    env->DeleteLocalRef(uByte);
//    env->DeleteLocalRef(vByte);
//    if (needsDetach == 1) {
//        gs_jvm->DetachCurrentThread();
//        file_write_log(
//                "SRSdkJni..OnRenderFrameCallBack_JNI............end...stermid:%d", stermid);
//    }
//
//}


//参会人列表回调
void OnRspConfTermListCallBack_JNI(const bool isOk, const SRConferenceAbnormal &error,
                                   const int master_id,
                                   const int duo_term_id,
                                   std::deque <TermInfo> termInfos) {
#if defined(LOG_JNI)
    Log("SRSdkJni..OnRspConfTermListCallBack_JNI...list.....___isOk:%d",isOk);
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jmethodID infos_method = env->GetMethodID(SRError_class, "<init>", "()V");
    jobject error_obj = env->NewObject(SRError_class, infos_method, "");

    int errorCode = (int) error.cur_error;
    string brief_reason = error.brief_reason;
    string detail_reason = error.detail_reason;
    jobject error_info = errorStruct(env, errorCode, brief_reason, detail_reason, error_obj);

    jmethodID construct = env->GetMethodID(class_ArrayList, "<init>", "()V");
    jobject obj_List = env->NewObject(class_ArrayList, construct, "");
    jmethodID list_add = env->GetMethodID(class_ArrayList, "add",
                                          "(Ljava/lang/Object;)Z");
    jmethodID info_method = env->GetMethodID(info_class, "<init>", "()V");
    int nSize = termInfos.size();
    int i = 0;
    for (i = 0; i < nSize; i++) {
        TermInfo &termInfo = termInfos.at(i);
        int termId = termInfo.termid;
        unsigned int suid = termInfo.suid;
        string tername = termInfo.tername;
        bool ismuted = termInfo.ismuted;
        bool iscamera_on = termInfo.iscamera_on;
        bool ishandup = termInfo.ishandup;
        bool isonline = termInfo.isonline;
        int usertype = termInfo.usertype;
        int specialtype = termInfo.specialtype;
        int devicetype = termInfo.devicetype;
        string ip = termInfo.ip;
        int protocoltype = termInfo.protocoltype;
        int bandwidth = termInfo.bandwidth;
        string calloption = termInfo.calloption;
        jobject info_obj = env->NewObject(info_class, info_method, "");
        jobject info = TermInfoStruct(env, termId, suid, tername, ismuted,
                                      iscamera_on, ishandup, isonline, usertype, specialtype,
                                      devicetype,ip,protocoltype,bandwidth,calloption,info_obj);
        env->CallBooleanMethod(obj_List, list_add, info);
        env->DeleteLocalRef(info_obj);
    }
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onRspConfTermListCallBack",
                                                "(ZIILjava/util/ArrayList;Lorg/suirui/srpaas/entry/SRError;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, isOk, master_id,
                            duo_term_id, obj_List, error_info);
        env->DeleteLocalRef(error_obj);
        env->DeleteLocalRef(obj_qtt);
        env->DeleteLocalRef(obj_List);
    }
    gs_jvm->DetachCurrentThread();
}

//请求客服端发送视频流(selectvideo触发)
void OnStartSendVideoCallBack_JNI(const int video_size) {
#if defined(LOG_JNI)
    Log("SRSdkJni...OnStartSendVideoCallBack_JNI.........");
#endif
//    JNIEnv *env;
//    gs_jvm->AttachCurrentThread(&env, NULL);
    int needsDetach;
    JNIEnv *env = getJNIEnv(&needsDetach);
    file_write_log("SRSdkJni..OnStartSendVideoCallBack_JNI.....start");
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "OnStartSendVideoCallBack", "(I)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, video_size);
        env->DeleteLocalRef(obj_qtt);
    }
    if (needsDetach) {
        gs_jvm->DetachCurrentThread();
        file_write_log("SRSdkJni..OnStartSendVideoCallBack_JNI.....end");
    }
}

/**
  *  请求客户端关闭视频流
  */
void OnStopSendVideoCallBack_JNI() {
#if defined(LOG_JNI)
    Log("SRSdkJni..OnStopSendVideo.........");
#endif
//    JNIEnv *env;
//    gs_jvm->AttachCurrentThread(&env, NULL);
    int needsDetach;
    JNIEnv *env = getJNIEnv(&needsDetach);
    file_write_log("SRSdkJni..OnStopSendVideoCallBack_JNI.....start");
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "OnStopSendVideoCallBack", "()V");
        env->CallVoidMethod(obj_qtt, gJinMethod);
        env->DeleteLocalRef(obj_qtt);
    }
    if (needsDetach) {
        gs_jvm->DetachCurrentThread();
        file_write_log("SRSdkJni..OnStopSendVideoCallBack_JNI.....end");
    }
}


//请求开启共享 回调
void onRspSendDualVideoCallBack_JNI(const bool isOk, const SRConferenceAbnormal &error) {
#if defined(LOG_JNI)
    Log("SRSdkJni:开启 回调onRspSendDualVideoCallBack_JNI.........isOk:%d",
            isOk);
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jmethodID infos_method = env->GetMethodID(SRError_class, "<init>", "()V");
    jobject error_obj = env->NewObject(SRError_class, infos_method, "");

    int errorCode = (int) error.cur_error;
    string brief_reason = error.brief_reason;
    string detail_reason = error.detail_reason;
    jobject error_info = errorStruct(env, errorCode, brief_reason, detail_reason, error_obj);

    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onRspSendDualVideoCallBack",
                                                "(ZLorg/suirui/srpaas/entry/SRError;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, isOk, error_info);
        env->DeleteLocalRef(error_obj);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//其他终端收到有人共享的回调
void OnRecvDualVideoOpenCallBack_JNI(const int dualvideo_send_stermid) {
#if defined(LOG_JNI)
    Log("SRSdkJni:接受端收到双流回调.........send_id:%d",dualvideo_send_stermid);
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "OnRecvDualVideoOpenCallBack", "(I)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, dualvideo_send_stermid);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//其他终端结束共享的回调
void OnRecvDualVideoCloseCallBack_JNI(const int dualvideo_close_stermid) {
#if defined(LOG_JNI)
    Log("SRSdkJni:关闭双流的回调........close_termId:%d",dualvideo_close_stermid);
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "OnRecvDualVideoCloseCallBack", "(I)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, dualvideo_close_stermid);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//其他终端暂停共享(已处理)
void OnRecvDualVideoPauseCallBack_JNI(const int dualvideo_pause_stermid) {
#if defined(LOG_JNI)
    Log("SRSdkJni:暂停共享回调........OnRecvDualVideoPauseCallBack_JNI");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "OnRecvDualVideoPauseCallBack", "(I)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, dualvideo_pause_stermid);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//其他终端恢复共享
void OnRecvDualVideoResumeCallBack_JNI(const int dualvideo_resume_stermid) {
#if defined(LOG_JNI)
    Log("SRSdkJni:恢复共享的回调........OnRecvDualVideoResumeCallBack_JNI");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "OnRecvDualVideoResumeCallBack", "(I)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, dualvideo_resume_stermid);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//共享人收到其他终端申请共享
void OnReqAssistVideoProxyCallBack_JNI(const int who_want_send_dualvideo_stermid) {
#if defined(LOG_JNI)
    Log("SRSdkJni:........OnReqAssistVideoProxyCallBack_JNI");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "OnReqAssistVideoProxyCallBack", "(I)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, who_want_send_dualvideo_stermid);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//参会人标注回调
void OnScreenDrawLabelCallBack_JNI(SRScreenLableAttr *attr) {
#if defined(LOG_JNI)
    Log("SRSdkJni:........OnScreenDrawLabelCallBack_JNI");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jmethodID construct = env->GetMethodID(class_ArrayList, "<init>", "()V");
    jobject obj_List = env->NewObject(class_ArrayList, construct, "");
    jmethodID list_add = env->GetMethodID(class_ArrayList, "add",
                                          "(Ljava/lang/Object;)Z");
    jmethodID info_method = env->GetMethodID(screenLabel_class, "<init>", "()V");
    SRScreenLableAttr *screenLableAttr = (SRScreenLableAttr *) attr;
    int labelterid = screenLableAttr->labelterid;

    jobject info_obj = env->NewObject(screenLabel_class, info_method, "");
    jobject info = ScreenLabelStruct(env, screenLableAttr, info_obj);

    env->CallBooleanMethod(obj_List, list_add, info);
    env->DeleteLocalRef(info_obj);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "OnScreenDrawLabelCallBack",
                                                "(Ljava/util/ArrayList;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, obj_List);
        env->DeleteLocalRef(obj_qtt);
        env->DeleteLocalRef(obj_List);
    }
    gs_jvm->DetachCurrentThread();
}

void OnScreenClearLabelCallBack_JNI(const int cleard_stermid) {
#if defined(LOG_JNI)
    Log("SRSdkJni:........OnScreenClearLabelCallBack_JNI");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onScreenClearLabelCallBack", "(I)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, cleard_stermid);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

/**
 * 打开相机的回调
 */
void onOpenCameraCallBack_JNI(const int open_stermid) {
#if defined(LOG_JNI)
    Log("SRSdkJni:........onOpenCameraCallBack_JNI");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onOpenCameraCallBack", "(I)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, open_stermid);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

/**
 * 关闭相机的回调
 */
void onCloseCameraCallBack_JNI(const int close_stermid) {
#if defined(LOG_JNI)
    Log("SRSdkJni:........onCloseCameraCallBack_JNI");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onCloseCameraCallBack", "(I)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, close_stermid);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}


/**
 * 静音
 */
void onTermAudioRecMuteCallBack_JNI(const int mute_stermid) {
#if defined(LOG_JNI)
    Log("SRSdkJni:........onTermAudioRecMuteCallBack_JNI");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onTermAudioRecUnOrMuteCallBack", "(IZ)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, mute_stermid, true);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}


/**
 * 取消静音
 */
void onTermAudioRecUnMuteCallBack_JNI(const int cancel_stermid) {
#if defined(LOG_JNI)
    Log("SRSdkJni:........onTermAudioRecUnMuteCallBack_JNI");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onTermAudioRecUnOrMuteCallBack", "(IZ)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, cancel_stermid, false);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//全部静音/取消全部静音
void onMuteAudioAllTermNotifyCallBack_JNI(const bool is_mute) {
#if defined(LOG_JNI)
    Log("SRSdkJni:........onMuteAudioAllTermNotifyCallBack_JNI");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onMuteAudioAllTermNotifyCallBack", "(Z)V");
        jboolean
                ismute = (jboolean)
        is_mute;
        env->CallVoidMethod(obj_qtt, gJinMethod, ismute);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();

}

//主持人结束会议
void OnIndChairEndConfCallBack_JNI(const int chair_stermid,
                                   const char *chair_name) {
#if defined(LOG_JNI)
    Log("SRSdkJni:........OnIndChairEndConfCallBack_JNI...__%d__%s",chair_stermid,chair_name);
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jstring exit_chair_name = NULL;
    if (chair_name != NULL)
        exit_chair_name = chartoJstring(env, chair_name);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onChairEndConfCallBack", "(ILjava/lang/String;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, chair_stermid, exit_chair_name);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}


//某个终端举手回调
void OnTermHandUpCallBack_JNI(const int handup_stermid,
                              const bool is_handup) {
#if defined(LOG_JNI)
    Log("SRSdkJni:........OnTermHandUpCallBack_JNI...__%d__%d",handup_stermid,is_handup);
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onTermHandUpCallBack", "(IZ)V");
        jboolean
                ishandup = (jboolean)
        is_handup;
        env->CallVoidMethod(obj_qtt, gJinMethod, handup_stermid, ishandup);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//新主持人收到回调
void OnMasterTransferCallBack_JNI(const int chair_stermid) {
#if defined(LOG_JNI)
    Log("SRSdkJni:........OnMasterTransferCallBack_JNI...__%d",chair_stermid);
#endif
    file_write_log("SRSdkJni..OnMasterTransferCallBack_JNI......chair_stermid:%d", chair_stermid);
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onMasterTransferCallBack", "(I)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, chair_stermid);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//主持人指定会议室内其它人看某一个客户端的视频回调
void onLockOrUnLockVideoCallBack_JNI(const int lock_stermid, const bool islock) {
#if defined(LOG_JNI)
    Log("SRSdkJni:........onLockOrUnLockVideoCallBack_JNI...__%d__%d",lock_stermid,islock);
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onLockOrUnLockVideoCallBack", "(IZ)V");
        jboolean
                is_lock = (jboolean)
        islock;
        env->CallVoidMethod(obj_qtt, gJinMethod, lock_stermid, is_lock);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//主持人结束共享回调
void OnIndChairEndDataShareCallBack_JNI(const int chair_stermid,
                                        const char *chair_name) {
#if defined(LOG_JNI)
    Log("SRSdkJni:........OnIndChairEndDataShareCallBack_JNI...__%d",chair_stermid);
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jstring end_chair_name = NULL;
    if (chair_name != NULL)
        end_chair_name = chartoJstring(env, chair_name);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onIndChairEndDataShareCallBack",
                                                "(ILjava/lang/String;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, chair_stermid, end_chair_name);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//修改终端的名称
void OnTermChangeNameCallBack_JNI(const int change_stermid, const char *term_name) {
#if defined(LOG_JNI)
    Log("SRSdkJni:........OnTermChangeNameCallBack_JNI...__%d",change_stermid);
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jstring change_term_name = NULL;
    if (term_name != NULL)
        change_term_name = chartoJstring(env, term_name);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onTermChangeNameCallBack",
                                                "(ILjava/lang/String;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, change_stermid, change_term_name);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//语音激励
void OnActiveVoiceCallBack_JNI(std::deque <SRVoiceActiveInfo> voice_acives) {
//#if defined(LOG_JNI)
//    Log("SRSdkJni:........OnActiveVoiceCallBack_JNI..");
//#endif
//    JNIEnv *env;
//    gs_jvm->AttachCurrentThread(&env, NULL);
    int needsDetach;
    JNIEnv *env = getJNIEnv(&needsDetach);
    file_write_log("SRSdkJni..OnActiveVoiceCallBack_JNI......start");
    if (!env) {
        file_write_log("SRSdkJni..OnActiveVoiceCallBack_JNI.....NULL");
        return;
    }
    jmethodID construct = env->GetMethodID(class_ArrayList, "<init>", "()V");
    jobject obj_List = env->NewObject(class_ArrayList, construct, "");
    jmethodID list_add = env->GetMethodID(class_ArrayList, "add",
                                          "(Ljava/lang/Object;)Z");
    jmethodID info_method = env->GetMethodID(VoiceActiveInfo_class, "<init>",
                                             "()V");
    int num = voice_acives.size();
    for (int i = 0; i < num; i++) {
        SRVoiceActiveInfo &activeInfo = voice_acives.at(i);
        int talkId = activeInfo.talk_id;
        unsigned int ergy = activeInfo.energy;
        int ergyen = (int) ergy;
        jobject VoiceActiveInfo_obj = env->NewObject(VoiceActiveInfo_class,
                                                     info_method, "");
        jobject info = VoiceActiveInfoStruct(env, talkId, ergyen,
                                             VoiceActiveInfo_obj);
        env->CallBooleanMethod(obj_List, list_add, info);
        env->DeleteLocalRef(VoiceActiveInfo_obj);
        file_write_log("SRSdkJni..OnActiveVoiceCallBack_JNI......start.....talkId:%d", talkId);
    }
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onActiveVoiceCallBack",
                                                "(Ljava/util/ArrayList;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, obj_List);
        env->DeleteLocalRef(obj_qtt);
        env->DeleteLocalRef(obj_List);
    }
    if (needsDetach) {
        file_write_log("SRSdkJni..OnActiveVoiceCallBack_JNI......end");
        gs_jvm->DetachCurrentThread();
    }
}

//发送数据统计信息回调
void onSendStreamInfoStatsCallBack_JNI(const SendStreamInfo &stats) {
//#if defined(LOG_JNI)
//    Log("SRSdkJni:........onSendStreamInfoStatsCallBack_JNI..");
//#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jmethodID construct = env->GetMethodID(class_ArrayList, "<init>", "()V");
    jobject obj_List = env->NewObject(class_ArrayList, construct, "");
    jmethodID list_add = env->GetMethodID(class_ArrayList, "add",
                                          "(Ljava/lang/Object;)Z");
    jmethodID info_method = env->GetMethodID(SRSendStreamInfo_class, "<init>", "()V");
    jobject info_obj = env->NewObject(SRSendStreamInfo_class, info_method, "");
    jobject info = SendStreamInfoStruct(env, stats, info_obj);
    env->CallBooleanMethod(obj_List, list_add, info);
    env->DeleteLocalRef(info_obj);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onSendStreamInfoStatsCallBack",
                                                "(Ljava/util/ArrayList;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, obj_List);
        env->DeleteLocalRef(obj_qtt);
        env->DeleteLocalRef(obj_List);
    }
    gs_jvm->DetachCurrentThread();
}

//接收数据统计信息回调
void onRecvStreamInfoStatsCallBack_JNI(const RecvStreamInfo &stats) {
//#if defined(LOG_JNI)
//    Log("SRSdkJni:........onRecvStreamInfoStatsCallBack_JNI..");
//#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jmethodID construct = env->GetMethodID(class_ArrayList, "<init>", "()V");
    jobject obj_List = env->NewObject(class_ArrayList, construct, "");
    jmethodID list_add = env->GetMethodID(class_ArrayList, "add",
                                          "(Ljava/lang/Object;)Z");
    jmethodID info_method = env->GetMethodID(SRRecvStreamInfo_class, "<init>", "()V");
    jobject info_obj = env->NewObject(SRRecvStreamInfo_class, info_method, "");
    jobject info = RecvStreamInfoStruct(env, stats, info_obj);
    env->CallBooleanMethod(obj_List, list_add, info);
    env->DeleteLocalRef(info_obj);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onRecvStreamInfoStatsCallBack",
                                                "(Ljava/util/ArrayList;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, obj_List);
        env->DeleteLocalRef(obj_qtt);
        env->DeleteLocalRef(obj_List);
    }
    gs_jvm->DetachCurrentThread();
}

//服务器错误回调
void onServerErrorCallBack_JNI(SR_ERROR_CODE_TYPE err) {
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    int error_code = (int) err;
#if defined(LOG_JNI)
    Log("SRSdkJni:........onServerErrorCallBack_JNI..__%d",error_code);
#endif
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onServerErrorCallBack",
                                                "(I)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, error_code);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}


//检测其他终端的状态回调
void OnOtherTermRunningStatusCallBack_JNI(const int stautsTermid,
                                          const int staClass, const int staSubCls,
                                          const std::string staStr) {
#if defined(LOG_JNI)
    Log("SRSdkJni:OnOtherTermRunningStatusCallBack_JNI:..........");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jstring sta_Str = stringToJstring(env, staStr);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "SREngineRunningStatusNotifyCallBack",
                                                "(IIILjava/lang/String;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, stautsTermid, staClass, staSubCls,
                            sta_Str);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//网络该表回调
void OnNetwrokNotify_JNI(int stauts) {
#if defined(LOG_JNI)
    Log("SRSdkJni:OnNetwrokNotify_JNI:..........");
#endif
//    JNIEnv *env;
//    gs_jvm->AttachCurrentThread(&env, NULL);
    int needsDetach;
    JNIEnv *env = getJNIEnv(&needsDetach);
    file_write_log("SRSdkJni..OnNetwrokNotify_JNI.....start");
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "OnNetwrokNotify",
                                                "(I)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, stauts);
        env->DeleteLocalRef(obj_qtt);
    }
    if (needsDetach) {
        gs_jvm->DetachCurrentThread();
    }
}


//主持人设置强制静音其他参会人收到的回调
void OnConfForceMuteCallBack_JNI(const bool isforcemute) {
#if defined(LOG_JNI)
    Log("SRSdkJni:OnConfForceMuteCallBack_JNI:..........");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onConfForceMuteAllTermCallBack", "(Z)V");
        jboolean
                isforceMute = (jboolean)
        isforcemute;
        env->CallVoidMethod(obj_qtt, gJinMethod, isforceMute);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}


//获取会议信息的回调
void OnRspConfStatusCallBack_JNI(const bool isok, ConfStatus &confstatus,
                                 const SRConferenceAbnormal &error) {
#if defined(LOG_JNI)
    Log("SRSdkJni:OnRspConfStatusCallBack_JNI:..........");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jmethodID infos_method = env->GetMethodID(SRError_class, "<init>", "()V");
    jobject error_obj = env->NewObject(SRError_class, infos_method, "");

    int errorCode = (int) error.cur_error;
    string brief_reason = error.brief_reason;
    string detail_reason = error.detail_reason;
    jobject error_info = errorStruct(env, errorCode, brief_reason, detail_reason, error_obj);

    jmethodID info_method = env->GetMethodID(ConfInfoStatus_class, "<init>", "()V");
    jobject confInfo_obj = env->NewObject(ConfInfoStatus_class, info_method, "");
    jobject conf_info = getConfInfoState(env, confstatus, confInfo_obj);

    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onRspConfInfoStatusCallBack",
                                                "(ZLorg/suirui/srpaas/entry/ConfInfoStatus;Lorg/suirui/srpaas/entry/SRError;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, isok, conf_info, error_info);
        env->DeleteLocalRef(error_obj);
        env->DeleteLocalRef(confInfo_obj);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//主持人开始/结束会议录制的回调
void OnIndTerCRSRecStateCallBack_JNI(const int recstate, const SRConferenceAbnormal &error) {
#if defined(LOG_JNI)
    Log("SRSdkJni:OnIndTerCRSRecStateCallBack_JNI:..........");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);

    jmethodID infos_method = env->GetMethodID(SRError_class, "<init>", "()V");
    jobject error_obj = env->NewObject(SRError_class, infos_method, "");
    int errorCode = (int) error.cur_error;
    string brief_reason = error.brief_reason;
    string detail_reason = error.detail_reason;
    jobject info = errorStruct(env, errorCode, brief_reason, detail_reason, error_obj);


    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onIndTerCRSRecStateCallBack",
                                                "(ILorg/suirui/srpaas/entry/SRError;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, recstate, info);
        env->DeleteLocalRef(obj_qtt);
        env->DeleteLocalRef(error_obj);
    }
    gs_jvm->DetachCurrentThread();
}

//新加入的终端可能会出收到该消息，与GetTermList类似
void OnAllMPInfoCallBack_JNI(std::list <SRMediaPInfo> &mpis) {
#if defined(LOG_JNI)
    Log("SRSdkJni..OnAllMPInfoCallBack_JNI.......");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jmethodID construct = env->GetMethodID(class_ArrayList, "<init>", "()V");
    jobject mediaInfo_List = env->NewObject(class_ArrayList, construct, "");
    jmethodID list_add = env->GetMethodID(class_ArrayList, "add",
                                          "(Ljava/lang/Object;)Z");
    jmethodID info_method = env->GetMethodID(srMediaInfo_class, "<init>", "()V");


    jmethodID screen_construct = env->GetMethodID(class_ArrayList, "<init>", "()V");
    jobject screenInfo_List = env->NewObject(class_ArrayList, screen_construct, "");
    jmethodID screen_list_add = env->GetMethodID(class_ArrayList, "add",
                                                 "(Ljava/lang/Object;)Z");
    jmethodID screen_info_method = env->GetMethodID(srMediaInfoPScreenInfo_class, "<init>", "()V");

    for (list<SRMediaPInfo>::iterator itor = mpis.begin(); itor != mpis.end(); itor++) {
        int channelid = (*itor).channelid;
        Log("SRSdkJni..OnAllMPInfoCallBack_JNI.......channelid==%d", channelid);
        jobject mediaInfo_obj = env->NewObject(srMediaInfo_class, info_method, "");
        jfieldID channelid_ = env->GetFieldID(srMediaInfo_class, "channelid", "I");
        env->SetIntField(mediaInfo_obj, channelid_, channelid);
        jfieldID screen_list_ = env->GetFieldID(srMediaInfo_class, "screens",
                                                "Ljava/util/ArrayList;");
        //screen list
        std::list <SRMediaPScreenInfo> screensList = (*itor).screens;
        for (list<SRMediaPScreenInfo>::iterator itor2 = screensList.begin();
             itor2 != screensList.end(); itor2++) {
            int screenid = (*itor2).screenid;
            int screentype = (*itor2).screentype;
            jobject screenInfo_obj = env->NewObject(srMediaInfoPScreenInfo_class,
                                                    screen_info_method, "");
            jfieldID screenid_ = env->GetFieldID(srMediaInfoPScreenInfo_class, "screenid", "I");
            jfieldID screentype_ = env->GetFieldID(srMediaInfoPScreenInfo_class, "screentype", "I");
            env->SetIntField(screenInfo_obj, screenid_, screenid);
            env->SetIntField(screenInfo_obj, screentype_, screentype);
            env->CallBooleanMethod(screenInfo_List, screen_list_add, screenInfo_obj);
            env->DeleteLocalRef(screenInfo_obj);
        }
        env->SetObjectField(mediaInfo_obj, screen_list_, screenInfo_List);
        env->CallBooleanMethod(mediaInfo_List, list_add, mediaInfo_obj);
        env->DeleteLocalRef(mediaInfo_obj);
    }
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "OnAllMPInfoCallBack",
                                                "(Ljava/util/ArrayList;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, mediaInfo_List);
        env->DeleteLocalRef(obj_qtt);
        env->DeleteLocalRef(mediaInfo_List);
        env->DeleteLocalRef(screenInfo_List);
    }
    gs_jvm->DetachCurrentThread();
}

//channelid 对应的那个mp
//screenid 混屏布局对应屏幕id
//screentype 屏幕类型，1-会议屏幕/网关(标准终端)屏幕、2-终端屏幕、3-双流屏幕
//addordel 屏幕的是否增加删除 1:add  2:del
void OnMPScreenInfoCallback_JNI(const int channelid, const int screenid,
                                const int screentype, const int addordel) {
#if defined(LOG_JNI)
    Log("SRSdkJni:OnMPScreenInfoCallback_JNI:..........");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onMPScreenInfoCallback", "(IIII)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, channelid, screenid, screentype, addordel);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//参会人变化同步更新到终端 增加（参会人列表）
void OnUpdateAddPaticipantsCallBack_JNI(std::list <TermInfo> &paticipants) {
    Log("SRSdkJni:OnUpdateAddPaticipantsCallBack_JNI:..........");
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jmethodID construct = env->GetMethodID(class_ArrayList, "<init>", "()V");
    jobject obj_List = env->NewObject(class_ArrayList, construct, "");
    jmethodID list_add = env->GetMethodID(class_ArrayList, "add",
                                          "(Ljava/lang/Object;)Z");
    jmethodID info_method = env->GetMethodID(info_class, "<init>", "()V");
    for (list<TermInfo>::iterator itor = paticipants.begin(); itor != paticipants.end(); itor++) {
        int termId = (*itor).termid;
        unsigned int suid = (*itor).suid;
        string tername = (*itor).tername;
        bool ismuted = (*itor).ismuted;
        bool iscamera_on = (*itor).iscamera_on;
        bool ishandup = (*itor).ishandup;
        bool isonline = (*itor).isonline;
        int usertype = (*itor).usertype;
        int specialtype = (*itor).specialtype;
        int devicetype = (*itor).devicetype;
        string ip = (*itor).ip;
        int protocoltype = (*itor).protocoltype;
        int bandwidth = (*itor).bandwidth;
        string calloption = (*itor).calloption;
        jobject info_obj = env->NewObject(info_class, info_method, "");
        jobject info = TermInfoStruct(env, termId, suid, tername, ismuted,
                                      iscamera_on, ishandup, isonline, usertype, specialtype,
                                      devicetype,ip,protocoltype,bandwidth,calloption,info_obj);
        env->CallBooleanMethod(obj_List, list_add, info);
        env->DeleteLocalRef(info_obj);
    }
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onUpdateAddPaticipantsCallback",
                                                "(Ljava/util/ArrayList;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, obj_List);
        env->DeleteLocalRef(obj_qtt);
        env->DeleteLocalRef(obj_List);
    }
    gs_jvm->DetachCurrentThread();
}

//参会人变化同步更新到终端 删除（参会人列表）
void OnUpdateDelPaticipantsCallBack_JNI(std::list <TermInfo> &paticipants) {
#if defined(LOG_JNI)
    Log("SRSdkJni:OnUpdateDelPaticipantsCallBack_JNI:..........");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jmethodID construct = env->GetMethodID(class_ArrayList, "<init>", "()V");
    jobject obj_List = env->NewObject(class_ArrayList, construct, "");
    jmethodID list_add = env->GetMethodID(class_ArrayList, "add",
                                          "(Ljava/lang/Object;)Z");
    jmethodID info_method = env->GetMethodID(info_class, "<init>", "()V");
    for (list<TermInfo>::iterator itor = paticipants.begin(); itor != paticipants.end(); itor++) {
        int termId = (*itor).termid;
        unsigned int suid = (*itor).suid;
        string tername = (*itor).tername;
        bool ismuted = (*itor).ismuted;
        bool iscamera_on = (*itor).iscamera_on;
        bool ishandup = (*itor).ishandup;
        bool isonline = (*itor).isonline;
        int usertype = (*itor).usertype;
        int specialtype = (*itor).specialtype;
        int devicetype = (*itor).devicetype;
        string ip = (*itor).ip;
        int protocoltype = (*itor).protocoltype;
        int bandwidth = (*itor).bandwidth;
        string calloption = (*itor).calloption;
        jobject info_obj = env->NewObject(info_class, info_method, "");
        jobject info = TermInfoStruct(env, termId, suid, tername, ismuted,
                                      iscamera_on, ishandup, isonline, usertype, specialtype,
                                      devicetype,ip,protocoltype,bandwidth,calloption,info_obj);
        env->CallBooleanMethod(obj_List, list_add, info);
        env->DeleteLocalRef(info_obj);
    }
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "onUpdateDelPaticipantsCallback",
                                                "(Ljava/util/ArrayList;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, obj_List);
        env->DeleteLocalRef(obj_qtt);
        env->DeleteLocalRef(obj_List);
    }
    gs_jvm->DetachCurrentThread();
}

/**
  * MC将该消息群发到其他所有在会终端(包含主持人) 哪个终端类型转变
  * @param [in] nspclterid
  *          特殊类型变化的终端stermid
  * @param [in] nspcltype
  *          终端要转变的类型,变化后的特殊类型,	0-普通终端类型,1-投屏终端类型
  */
void OnIndTerSpecialtypeTransferCallBack_JNI(const int nspclterid,
                                             const int nspcltype) {
#if defined(LOG_JNI)
    Log("SRSdkJni:OnIndTerSpecialtypeTransferCallBack_JNI:..........");
#endif
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "OnIndTerSpecialtypeTransferCallBack", "(II)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, nspclterid, nspcltype);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//直播状态回调
void OnIndTerCRSLiveStateCallBack_JNI(const int livestate, const std::string &liveplayurl,
                                      const SRConferenceAbnormal &error) {
    Log("SRSdkJni:OnIndTerCRSLiveStateCallBack_JNI:..........");
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);

    jmethodID infos_method = env->GetMethodID(SRError_class, "<init>", "()V");
    jobject error_obj = env->NewObject(SRError_class, infos_method, "");
    int errorCode = (int) error.cur_error;
    string brief_reason = error.brief_reason;
    string detail_reason = error.detail_reason;
    jobject info = errorStruct(env, errorCode, brief_reason, detail_reason, error_obj);

    jstring liveplayurlStr = stringToJstring(env, liveplayurl);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "OnIndTerCRSLiveStateCallBack",
                                                "(ILjava/lang/String;Lorg/suirui/srpaas/entry/SRError;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, livestate, liveplayurlStr, info);
        env->DeleteLocalRef(obj_qtt);
        env->DeleteLocalRef(error_obj);
    }
    gs_jvm->DetachCurrentThread();
}

//直播设置变更回调
void OnIndLiveSettingChangedCallBack_JNI(const LiveSetting &new_setting){
    Log("SRSdkJni:OnIndLiveSettingChangedCallBack_JNI:..........");
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jmethodID infos_method = env->GetMethodID(srOnliveInfo_class, "<init>", "()V");
    jobject liveInfo = env->NewObject(srOnliveInfo_class, infos_method, "");
    string chairman=new_setting.chairman;
    string subject=new_setting.subject;
    string digest=new_setting.digest;
    int ispublic=(int)new_setting.ispublic;
    string livepwd=new_setting.livepwd;
    jobject info = LiveSettingInfo(env, chairman, subject, digest,ispublic,livepwd, liveInfo);

    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "OnIndLiveSettingChangedCallBack",
                                                "(Lorg/suirui/srpaas/entry/OnliveInfo;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, info);
        env->DeleteLocalRef(obj_qtt);
        env->DeleteLocalRef(liveInfo);
    }
    gs_jvm->DetachCurrentThread();
}

//聊天中接收到信息
void OnRecvIMMessageCallBack_JNI(const int from_stermid, const std::string &message) {
    Log("SRSdkJni:OnRecvIMMessageCallBack_JNI:..........");
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    jstring msg = stringToJstring(env, message);
    if (Callback_class != NULL) {
        jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                     "()V");
        jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
        jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                "OnRecvConfMessageCallBack",
                                                "(ILjava/lang/String;)V");
        env->CallVoidMethod(obj_qtt, gJinMethod, from_stermid,msg);
        env->DeleteLocalRef(obj_qtt);
    }
    gs_jvm->DetachCurrentThread();
}

//网络异常后，又重新链接成功
void onServerOkCallBack_JNI(const SR_OK_CODE_TYPE ok){
        JNIEnv *env;
        gs_jvm->AttachCurrentThread(&env, NULL);
        int ok_code = (int) ok;
    #if defined(LOG_JNI)
        Log("SRSdkJni:........onServerOkCallBack_JNI..__%d",ok_code);
    #endif
        if (Callback_class != NULL) {
            jmethodID Callback_method = env->GetMethodID(Callback_class, "<init>",
                                                         "()V");
            jobject obj_qtt = env->NewObject(Callback_class, Callback_method, "");
            jmethodID gJinMethod = env->GetMethodID(Callback_class,
                                                    "onServerOkCallBack",
                                                    "(I)V");
            env->CallVoidMethod(obj_qtt, gJinMethod, ok_code);
            env->DeleteLocalRef(obj_qtt);
        }
        gs_jvm->DetachCurrentThread();
}
//*********************end*******************************************************************
}
