package org.suirui.srpaas.jni;

import com.suirui.srpaas.base.util.log.SRLog;

import org.suirui.srpaas.entry.BufData;
import org.suirui.srpaas.entry.DelParticipant;
import org.suirui.srpaas.entry.NetWorkStatus;
import org.suirui.srpaas.entry.OnliveInfo;
import org.suirui.srpaas.entry.RvideoParam;
import org.suirui.srpaas.entry.SRMediaPScreenInfo;
import org.suirui.srpaas.entry.SRScreenLable;
import org.suirui.srpaas.entry.SRSdkConferenceInfo;
import org.suirui.srpaas.entry.SRUserInfo;
import org.suirui.srpaas.entry.SendMessageTerm;

import java.nio.ByteBuffer;
import java.util.List;

/**
 * sdk接口
 *
 * @author cui.li
 */
public class JniNative {
    private static final SRLog log = new SRLog(JniNative.class.getName());
    public static void loadlibrary() {

        String[] LIBS = new String[]{"apm", "callserver", "mediacore",
                "SRRtcEngine", "SRSdkJNI"};
        for (int i = 0; i < LIBS.length; i++) {
            try {
                log.E("加载库...mobie..." + LIBS[i] + "...start");
                System.loadLibrary(LIBS[i]);
                log.E("加载库......" + LIBS[i] + "...end");
            } catch (Exception e) {
                e.printStackTrace();

            }
        }
    }

    public static void loadlibraryhBox() {

        String[] LIBS = new String[]{"apm", "callserver", "hwcodec_3288", "mediacore",
                "SRRtcEngine", "SRSdkJNI"};
        for (int i = 0; i < LIBS.length; i++) {
            try {
                log.E("加载库......" + LIBS[i] + "...start");
                System.loadLibrary(LIBS[i]);
                log.E("加载库......" + LIBS[i] + "...end");
            } catch (Exception e) {
                e.printStackTrace();

            }
        }
    }




    /******* native方法 接口  new*******************/
    /**
     * 设置h264的内存缓存
     * @param bufData
     * @return
     */
    public native static int  setReceiveByteBufferData(BufData bufData);

    public native static int SREngineInVideoRawStreamDataBuf(int videoStreamType,
                                                              int formatType, ByteBuffer data, int width, int height, int rotation, boolean isMirror, int size);




    /**
     * *****
     * 客户端在启动时调用(只调用一次,初始化) *返回值: 0 成功 非0 失败（ok）
     * isH264Decode true硬解  false 软解
     * platformType  平台类型
     */
    public native static int InitSDK(boolean isOpenSDKLog,boolean isH264Decode,int platformType);

    /*
    客户端退出时调用 return 0 success 其他 failer（ok）
    */
    public native static int UnInitSDK();

    /**
     * 加入会议（ok）
     *
     * @param joinConfObject
     * @param userInfoObject
     * @param isCameraOn
     * @param isMute
     * @return OnRspJoinConfCallBack
     */
    public native static int reqestJoinConf(SRSdkConferenceInfo joinConfObject,
                                            SRUserInfo userInfoObject,
                                            boolean isCameraOn,
                                            boolean isMute);

    /**
     * 结束会议（ok）
     *
     * @param exit_reason
     * @return OnExitConfCallBack
     */
    public native static int requestExitConf(String exit_reason);

    /**
     * 发送流 ******传递RGB（ok）
     *
     * @param videoStreamType (数据共享0 视频 1)
     * @param formatType      （YUV 0 ，RGB 1 ，ARGB 2）
     * @param width
     * @param height
     * @param rgb
     * @param size
     * @return onRenderCallBackCallBack
     */
    public native static int SREngineInVideoRawStreamRGB(int videoStreamType,
                                                         int formatType, int width, int height, int[] rgb, int size);


    /**
     * 发送流 传递YUV（ok）
     *
     * @param videoStreamType(数据共享0 视频 1)
     * @param formatType（YUV        0 ，RGB 1 ，ARGB 2）
     * @param width
     * @param height
     * @param yuv
     * @param size
     * @return onRenderCallBackCallBack
     */
    public native static int SREngineInVideoRawStreamYUV(int videoStreamType,
                                                         int formatType, int width, int height, byte[] yuv, int size);

    /**
     * 发送视频流
     *
     * @param data     相机采集的原始数据
     * @param width    预览的宽
     * @param height   预览的高
     * @param rotation 旋转的角度
     * @param isMirror 是否镜像
     * @return
     */
    public native static int SREngineInVideoRawStreamData(int videoStreamType,
                                                          int formatType, byte[] data, int width, int height, int rotation, boolean isMirror, int size);


    /**
     * 获取会议中参会者列表（ok）
     *
     * @return onRspConfTermListCallBack
     */
    public native static int requestTerminalmList();


    /**
     * 函数功能: 选看远端视频 输入参数： mul_stream:选看视频id和窗口（ok）
     *
     * @param videoParamList
     * @return onRenderCallBackCallBack(显示视频)  OnStartSendVideoCallBack(对方收到回调发送数据)
     */
    public native static int requestSelectRemoteVideo(
            List<RvideoParam> videoParamList);


    /**
     * 函数功能: 请求开启共享（ok）
     *
     * @return onRspSendDualVideoCallBack
     */
    public native static int requestStartSendDualVideo();


    /**
     * 停止共享（ok）
     *
     * @return
     */
    public native static int requestStopSendDualVideo();

    /**
     * 回复桌面共享申请(ok)
     *
     * @param avterid      申请共享Id
     * @param isok         是否同意
     * @param rejectreason 同意传空，拒绝传理由
     * @return
     */
    public native static int resposeSendDualVideoProxy(int avterid, boolean isok, String rejectreason);

    /**
     * (ok)
     * 函数功能: 打开本地摄像头指示(不需要等ack) 输入参数： conf_id 会议ID term_id 终端id(终端注册时的id) 返回值: 0
     * 成功 非0 失败
     */
    public native static int openCamera(int unmute_stermid);


    /**
     * (ok)
     * 函数功能: 关闭本地摄像头指示(不需要等ack) 输入参数： conf_id 会议ID term_id 终端id(终端注册时的id) 返回值: 0
     * 成功 非0 失败
     */
    public native static int closeCamera(int mute_stermid);


    /**
     * 静音(ok)
     *
     * @param term_id
     * @return
     */
    public native static int muteAudio(int term_id);

    /**
     * 取消静音(ok)
     *
     * @param unterm_id
     * @return
     */
    public native static int unMuteAudio(int unterm_id);

    /**
     * 全部静音/取消全部静音(ok)
     *
     * @param isMute
     * @return
     */
    public native static int MuteAudioAllTerm(boolean isMute);


    /**
     * 主持人结束会议(ok)
     *
     * @return
     */
    public native static void requestChairEndConf();

    /**
     * 本地终端举手(ok)
     *
     * @param handUp 举手:true 放手:false
     * @return 返回值: 0 成功 非0 失败
     */
    public native static int requestHandUp(boolean handUp);

    /**
     * 改名(ok)
     *
     * @param name
     * @return
     */
    public native static int changeName(String name);


    /**
     * 设置焦点视频(ok)
     *
     * @param lock_id
     * @param isLock
     * @return
     */
    public native static int lockOrUnLockVideo(int lock_id, boolean isLock);


    /**
     * 转让主持人权限，只有主持人才能做该操作（ok）
     *
     * @param newMasterId 要转让的id
     * @return
     */

    public native static int setMasterId(int newMasterId);

    /**
     * 主持人将其他终端踢出会议命令,只有主持人可以发出去（ok）
     *
     * @param dropId
     */
    public native static int requestRemoveTerminal(int dropId);

    /**
     * 会中有共享，主持人可结束(暂时不用)
     */
    public native static void chairEndDataShare();

    /**
     * mode: 0:听筒模式 1:外音模式(未调试)
     *
     * @param mode
     * @return
     */
    public native static int SREngineSetSpeakerMode(int mode);

    /**
     * 桌面共享其他客户端添加备注(ok)
     *
     * @param screenLabel
     * @return
     */
    public native static int requestAddScreenLabel(SRScreenLable screenLabel);


    /**
     * 暂停共享(暂时不用)
     *
     * @return
     */
    public native static int requestPauseSendDualVideo();

    /**
     * 恢复共享(暂时不用)
     *
     * @return
     */
    public native static int requestResumeSendDualVideo();


    /**
     * 使能获取当前收到流统计信息状态, 传0 代表停止统计(ok)
     *
     * @param interval
     * @return
     */
    public native static int getSendStreamInfoIndication(int interval);

    /**
     * 使能获取当前发送统计信息状态, 传0 代表停止统计(ok)
     *
     * @param interval
     * @return
     */
    public native static int getRecvStreamInfoIndication(int interval);

    /**
     * 测试按钮，写文件
     */
    public native static int SRSetUserCmdToEngine(String cmdMsg[]);

    /**
     * 切换网络
     *
     * @return
     */
    public native static int SREngineNetworkChanged();


    /**
     * 设置终端状态
     *
     * @param sta_class
     * @param sta_sub_class
     * @param status_str
     * @return
     */
    public native static int SREngineRunningStatusNotify(int sta_class, int sta_sub_class, String status_str);


    /**
     * 设置APM认证key
     *
     * @param key
     * @return
     */
    public native static int setApmKeyContent(String key);

    /**
     * 获取apm认证mac信息
     *
     * @return
     */
    public native static String getApmInfo();

    /**
     * 设置当前扬声器的音量
     *
     * @param volume
     * @return
     */
    public native static int SRSetOutputDeviceVolume(int volume);

    /**
     * 设置强制静音
     *
     * @return
     */
    public native static int SRSetForceMuteAudio(int type, boolean isforcemute);

    /**
     * 获取会议的会议信息
     *
     * @return
     */
    public native static int SRReqSRConfStatus(int type);

    /**
     * 锁定会议true: 锁定   false:取消锁定
     *
     * @param
     * @return
     */
    public native static int SRLockConf(boolean isLock);

    /**
     * 锁定会议时，主持人踢除参会人
     *
     * @param delParticipants
     * @return
     */
    public native static int SRDelParticipants(List<DelParticipant> delParticipants);

    /**
     * 重启音频设备
     *
     * @return
     */
    public native static int SRresetAudioDevice();

    /**
     * 设置用户需要设置的信息给sdk
     *
     * @return
     */
    public native static int SRSetUsrNotify(int netType);

    /**
     * 开始会议录制
     *
     * @param
     * @return
     */
    public native static int StartMeetingRecord(int channelid, List<SRMediaPScreenInfo> srMediaPScreenInfoList);

    /**
     * 停止会议录制
     *
     * @return
     */
    public native static int StopMeetingRecord(int channelid, List<SRMediaPScreenInfo> srMediaPScreenInfoList);

    /**
     * 获取当前的网络状态
     *
     * @return
     */
    public native static NetWorkStatus SRGetNetWorkStatus();

    /**
     * 开启直播
     *
     * @return
     */
    public native static int StartMeetingLive(OnliveInfo onliveInfo, int channelid, List<SRMediaPScreenInfo> srMediaPScreenInfoList);

    /**
     * 停止直播
     *
     * @return
     */
    public native static int StopMeetingLive(int channelid, List<SRMediaPScreenInfo> srMediaPScreenInfoList);

    /**
     * 修改直播设置
     *
     * @return
     */
    public native static int ChangeLiveSetting(OnliveInfo onliveInfo);

    /**
     * 聊天发送的消息
     *
     * @param termIdList
     * @param message
     * @return
     */
    public native static int sendConfMessage(List<SendMessageTerm> termIdList, String message);
    //*********************newSDK end***********************************************************************************************/


    //*********************oldSDK************************************************************************************************************/
    public native static ByteBuffer allocNativeBuffer(long bufferSize);

    public native static void freeNativeBuffer(ByteBuffer buffer);


    /**
     * 获取第三方音频库版本
     *
     * @return
     */
    public native static String getExtAudioProcessVersion();

    /**
     * 第三方音频库lisence注册
     *
     * @param licence
     * @param len
     * @return
     */
    public native static int registerExtAudioProcessLicence(String licence,
                                                            int len);


    //写文件 跟踪bug
    public native static boolean openFile(String fileName);

    public native static int closeFile();
}
