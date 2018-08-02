package org.suirui.srpaas.sdk;

import com.suirui.srpaas.base.util.log.SRLog;

import org.suirui.srpaas.entry.BufData;
import org.suirui.srpaas.entry.ConfInfoStatus;
import org.suirui.srpaas.entry.InviteInfo;
import org.suirui.srpaas.entry.MeeingListParams;
import org.suirui.srpaas.entry.MeetInfo;
import org.suirui.srpaas.entry.MeetingInfo;
import org.suirui.srpaas.entry.NetWorkStatus;
import org.suirui.srpaas.entry.OnliveInfo;
import org.suirui.srpaas.entry.RvideoParam;
import org.suirui.srpaas.entry.SRError;
import org.suirui.srpaas.entry.SRMediaPInfo;
import org.suirui.srpaas.entry.SRRecvStreamInfo;
import org.suirui.srpaas.entry.SRSdkConferenceInfo;
import org.suirui.srpaas.entry.SRSendStreamInfo;
import org.suirui.srpaas.entry.SRUserInfo;
import org.suirui.srpaas.entry.ScreenLableAttr;
import org.suirui.srpaas.entry.SpaasInfo;
import org.suirui.srpaas.entry.TermInfo;
import org.suirui.srpaas.entry.VoiceActiveInfo;
import org.suirui.srpaas.http.HttpService;
import org.suirui.srpaas.http.HttpServiceImpl;
import org.suirui.srpaas.http.callback.InviteCallBack;
import org.suirui.srpaas.http.callback.OnHasPwdCallBack;
import org.suirui.srpaas.http.callback.OnMeetingDetailInfoCallBack;
import org.suirui.srpaas.http.callback.OnMeetingListCallBack;
import org.suirui.srpaas.http.callback.StartOrJoinMeetCallBack;
import org.suirui.srpaas.jni.JniNative;
import org.suirui.srpaas.sdk.SRPaas.eMeetingError;
import org.suirui.srpaas.sdk.inter.OnExitConferenceListener;
import org.suirui.srpaas.sdk.inter.OnJoinMeetingListener;
import org.suirui.srpaas.sdk.inter.OnRenderListener;
import org.suirui.srpaas.util.StringUtil;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

import okhttp3.Call;

/**
 * 会议相关的接口实现
 *
 * @author cui.li
 */
public class MeetingServiceImpl implements MeetingService, OnJoinMeetingListener, OnRenderListener, OnExitConferenceListener {

    private static final SRLog log = new SRLog(MeetingServiceImpl.class.getName());
    private MeetingServiceListener mListener;

    private String confid = "";// 会议号(缓存)
    private String confPwd = "";// 会议密码
    private String joinNickName = "";// 加入会议显示的昵称,格式：uid:nickName:pic
    private SRPaasSDK srPaasSDK;

    public MeetingServiceImpl() {
        SdkCallBack.getInstance().addJoinListener(this);
        SdkCallBack.getInstance().addOnRenderListener(this);
        SdkCallBack.getInstance().addExitListener(this);
    }

    @Override
    public void addMeetingServiceListener(MeetingServiceListener listener) {
        this.mListener = listener;
    }

    @Override
    public void removeMeetingServiceListener(MeetingServiceListener listener) {
        this.mListener = null;
    }

    @Override
    public String getDoMain() {
        if (srPaasSDK == null) srPaasSDK = SRPaasSDK.getInstance();
        return srPaasSDK.getDoMain();
    }

    @Override
    public int getSuid() {
        if (srPaasSDK == null) srPaasSDK = SRPaasSDK.getInstance();
        return srPaasSDK.getPaasUid();
    }


    @Override
    public String getInviteUrl() {
        if (srPaasSDK == null) srPaasSDK = SRPaasSDK.getInstance();
        return srPaasSDK.getInviteUrl();
    }

    /**
     * 会议邀请
     *
     * @param inviteInfo
     * @return
     */
    @Override
    public void meetingInvite(InviteInfo inviteInfo) {
        HttpService h = HttpServiceImpl.getInstance();
        h.meetingInvite(inviteInfo, new InviteCallBack() {
            @Override
            public void onInviteSuccess() {
                if (mListener != null) {
                    mListener.onInviteSuccess();
                }
            }

            @Override
            public void onError(int errorCode, String msg) {
                if (mListener != null) {
                    mListener.onHttpInviteError(errorCode, msg);
                }
            }

            @Override
            public void onError(Call call, Exception e, int i) {
                if (mListener != null) {
                    mListener.onHttpInviteError(-1, (String) e.toString() + " ..." + i + "\n" + call.toString());
                }
            }
        });
    }

    @Override
    public void getMeetingList(MeeingListParams meetListingParams, OnMeetingListCallBack callBack) {
        HttpService h = HttpServiceImpl.getInstance();
         h.getMeetingList(meetListingParams,callBack);
    }

    @Override
    public void getMeetingPwd(String token, String confId, OnHasPwdCallBack onHasPwdCallBack) {
        HttpService h = HttpServiceImpl.getInstance();
        h.getMeetingPwd(token,confId,onHasPwdCallBack);
    }

    @Override
    public void getMeetingInfo(String appId, String secretKey, String token, String confId, OnMeetingDetailInfoCallBack onMeetingDetailInfoCallBack) {
        try{
            HttpService h = HttpServiceImpl.getInstance();
            h.getMeetingInfo(appId,secretKey,token,confId,onMeetingDetailInfoCallBack);
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    @Override
    public NetWorkStatus getNetWorkState() {
        return JniNative.SRGetNetWorkStatus();
    }

    @Override
    public void setReceiveByteBufferData(BufData bufData) {
        if(bufData!=null) {
            JniNative.setReceiveByteBufferData(bufData);
        }
    }

    /**
     * 开始会议（立即会议）
     *
     * @return
     */
    @Override
    public void StartMeeting(MeetInfo meetInfo) {
        log.E("StartMeeting....点击开始会议了");
        getNextStartMeetInfo(meetInfo, 0);
    }

    public void getNextStartMeetInfo(MeetInfo meetInfo, final int setKeyCunt) {
        if (meetInfo == null) meetInfo = new MeetInfo();
        HttpService h = HttpServiceImpl.getInstance();
        String apmStatus = JniNative.getApmInfo();
        if (!StringUtil.isEmptyOrNull(apmStatus)) {
            meetInfo.setThirdAudioId(String.valueOf(apmStatus));
        }
        if (!StringUtil.isEmptyOrNull(meetInfo.getM_confPwd())) confPwd = meetInfo.getM_confPwd();
        else confPwd = "";
        if (meetInfo.getNickName() != null && !meetInfo.getNickName().equals("")) {
            joinNickName = meetInfo.getNickName();
        } else {
            joinNickName = "";
        }
        final MeetInfo finalMeetInfo = meetInfo;
        h.startMeeting(meetInfo, new StartOrJoinMeetCallBack() {
            @Override
            public void onStartOrJoinMeetSuccess(MeetingInfo meet) {
                log.E("startMeeting.....onStartOrJoinMeetSuccess...meet:" + meet + "  setKeyCunt:" + setKeyCunt);
                if (meet == null) {
                    onMeetError(eMeetingError.eMeetingError_InvalidMeetingNumber);
                } else {
                    sdkJoinMeetInfo(meet, false, finalMeetInfo, setKeyCunt);
                }
            }

            @Override
            public void onError(int errorCode, String msg) {
                if (mListener != null) {
                    mListener.onHttpMeetingError(errorCode, msg);
                }
            }

            @Override
            public void onError(Call call, Exception e, int i) {
                if (mListener != null) {
                    mListener.onHttpError(call, e, i);
                }
            }
        });
    }


    /**
     * 加入会议
     *
     * @param meetInfo
     */
    @Override
    public void joinMeeting(MeetInfo meetInfo) {
        if (meetInfo == null) {// 非法会议号
            log.E("joinMeeting....非法错误号码");
            onMeetError(eMeetingError.eMeetingError_InvalidMeetingNumber);
        }
        log.E("joinMeeting...." + meetInfo.getM_subject());
        getNextJoinMeetInfo(meetInfo, 0);

    }

    private void getNextJoinMeetInfo(MeetInfo meetInfo, final int setKeyCunt) {
        HttpService h = HttpServiceImpl.getInstance();
        String apmStatus = JniNative.getApmInfo();
        if (!StringUtil.isEmptyOrNull(apmStatus)) {
            meetInfo.setThirdAudioId(String.valueOf(apmStatus));
        }
        if (!StringUtil.isEmptyOrNull(meetInfo.getM_confPwd())) confPwd = meetInfo.getM_confPwd();
        else confPwd = "";


        if (meetInfo.getNickName() != null && !meetInfo.getNickName().equals("")) {
            joinNickName = meetInfo.getNickName();
        } else {
            joinNickName = "";
        }
        final MeetInfo finalMeetInfo = meetInfo;
        h.joinMeeting(meetInfo, new StartOrJoinMeetCallBack() {
            @Override
            public void onStartOrJoinMeetSuccess(MeetingInfo meet) {
                if (meet == null) {
                    onMeetError(eMeetingError.eMeetingError_InvalidMeetingNumber);
                } else {
                    sdkJoinMeetInfo(meet, true, finalMeetInfo, setKeyCunt);
                }
            }

            @Override
            public void onError(int errorCode, String msg) {
                if (mListener != null) {
                    mListener.onHttpMeetingError(errorCode, msg);
                }
            }
        });
    }

    /**
     * 加入会议
     *
     * @param meetingInfo isJoinMeeting true 加入会议,否则 开始会议
     */

    public synchronized boolean sdkJoinMeetInfo(MeetingInfo meetingInfo, boolean isJoinMeeting, MeetInfo info, int setKeyCunt) {
        try {
            log.E("joinMeeting...." + meetingInfo.getM_subject() + " : " + meetingInfo.getM_confId());
            if (srPaasSDK == null) srPaasSDK = SRPaasSDK.getInstance();
            MeetingInfo meetInfo = meetingInfo;
            if (meetInfo != null) {
                if (mListener != null) {
                    if (StringUtil.isEmptyOrNull(meetInfo.getUserName()))
                        meetInfo.setUserName(joinNickName);
                    mListener.OnMeetPort(meetInfo);
                }
                // getM_mcAddr
                String mc_addr = meetInfo.getM_mcAddr();
                String relay_addr = meetInfo.getM_relaymcAddr();
                String relayServer = meetInfo.getM_relayServer();
                String relay_mcInfo = meetInfo.getM_relaymcInfo();
                log.E("joinMeeting.sdkJoinMeetInfo.........relay_addr:" + relay_addr + " ...relayServer:" + relayServer + " getM_confId: " + meetingInfo.getM_confId() + "  getM_subject: " + meetingInfo.getM_subject() + "  mc_addr:" + mc_addr + " relay_mcInfo:" + relay_mcInfo);
                String password = meetInfo.getConfPwd();
                //meetinginfo
                SRSdkConferenceInfo sdkConferenceInfo = new SRSdkConferenceInfo();
                sdkConferenceInfo.setConferenceId(StringUtil.readLong(meetInfo.getM_confId()));
                sdkConferenceInfo.setRelay_server(relayServer);
                if (!StringUtil.isEmptyOrNull(mc_addr))
                    sdkConferenceInfo.setPandPort(StringUtil.readLong(mc_addr));

                if (!StringUtil.isEmptyOrNull(relay_mcInfo)) {
                    log.E("joinMeeting.sdkJoinMeetInfo....有relaymcInfo....:" + relay_mcInfo);
                    sdkConferenceInfo.setRelaymcInfo((ArrayList) StringUtil.stringToList(relay_mcInfo, "/"));
                } else {
                    if (!StringUtil.isEmptyOrNull(relay_addr)) {
                        log.E("joinMeeting.sdkJoinMeetInfo....有relaymcAddr....:" + relay_addr);
                        sdkConferenceInfo.setRelaymcInfo((ArrayList) StringUtil.stringToList(relay_addr, "/"));
                    }
                }

                if (!StringUtil.isEmptyOrNull(password))
                    sdkConferenceInfo.setPassword(password);
                if (!StringUtil.isEmptyOrNull(meetInfo.getOCI()))
                    sdkConferenceInfo.setOCI(meetInfo.getOCI());

                //userinfo
                SRUserInfo userInfo = new SRUserInfo();
                userInfo.setTermUId(srPaasSDK.getPaasUid());
                userInfo.setTermUname(joinNickName);
                userInfo.setMediagroupid(Integer.parseInt(meetInfo.getMediaGroupId()));
                SpaasInfo spaasInfo = SRPaasSDK.getInstance().getSpaasInfo();
                if (spaasInfo != null) {
                    userInfo.setUserType(spaasInfo.getUserType());
                }

                log.E("joinMeeting。。sdkJoinMeetInfo。会议号：" + meetInfo.getM_confId() + " mcu_adress地址: " + meetInfo.getM_mcAddr() + " relay_adress端口号: " + meetInfo.getM_relaymcAddr() + "  relayServer:" + meetInfo.getM_relayServer() + " : " + StringUtil.readLong(mc_addr) + " paasUid:" + srPaasSDK.getPaasUid() + "  NickName:" + joinNickName + " thirdAudioKey:" + meetingInfo.getThirdAudioKey() + "  sdk初始化：" + SRPaasSDK.getInstance().isInitialized());
                boolean isCameraOn = StringUtil.StringToBoolean(meetingInfo.getCamaraautoenable());
                boolean isMute = StringUtil.StringToBoolean(meetingInfo.getMicautoenable());
                log.E("joinMeeting。。sdkJoinMeetInfo...isCameraOn:" + isCameraOn + "   isMute:" + isMute);
                if (!StringUtil.isEmptyOrNull(meetInfo.getM_confId()))
                    confid = meetInfo.getM_confId();
                else {
                    confid = "";
                }
                int returnJoin = -1;
//                if (!StringUtil.isEmptyOrNull(meetingInfo.getThirdAudioKey())) {
//                    log.E("joinMeeting..sdkJoinMeetInfo...getThirdAudioKey:" + meetingInfo.getThirdAudioKey());
//                    if (setKeyCunt < 3) {//三次循环
//                        int value = JniNative.setApmKeyContent(meetingInfo.getThirdAudioKey());
//                        log.E("joinMeeting..sdkJoinMeetInfo...value:" + value);
//                        if (value == 0) {
//                            returnJoin = JniNative.reqestJoinConf(sdkConferenceInfo, userInfo, isCameraOn, isMute);
//                        } else {
//                            setKeyCunt++;
//                            log.E("joinMeeting..sdkJoinMeetInfo...isJoinMeeting:" + isJoinMeeting);
//                            if (isJoinMeeting) {
//                                getNextJoinMeetInfo(info, setKeyCunt);
//                            } else {
//                                getNextStartMeetInfo(info, setKeyCunt);
//                            }
//                        }
//
//                    } else {
//                        log.E("joinMeeting..sdkJoinMeetInfo... 获取apm认证mac信息失败");
//                        onMeetError(eMeetingError.eMeetingError_GETAPM_MAC_ERROR);
//                        return false;
//
//                    }
//                } else {//直接入会
                    log.E("joinMeeting..sdkJoinMeetInfo...直接入会");
                    returnJoin = JniNative.reqestJoinConf(sdkConferenceInfo, userInfo, isCameraOn, isMute);
//                }
                if (returnJoin == 0) {
                    return true;
                } else {
//                    onMeetError(eMeetingError.eMeetingError_GETAPM_MAC_ERROR);
                    onMeetError(eMeetingError.eMeetingError_JoinMeetingFailer);
                    return false;
                }


            } else {
                log.E("joinMeeting..sdkJoinMeetInfo.服务器连接失败");
                onMeetError(eMeetingError.eMeetingError_ServerConnetError);
            }
        } catch (NumberFormatException e) {
            e.printStackTrace();
        }
        return false;
    }

    /**
     * 会议成功后，获取参会人列表
     *
     * @return
     */
    @Override
    public int getRequestTerminalmList() {
        return JniNative.requestTerminalmList();
    }

    @Override
    public boolean leaveMeetingWithCmd(SRPaas.eLeaveMeetingCmd eLeave, String exitReason) {
        log.E("leaveMeetingWithCmd..." + eLeave.getValue() + " 退出理由:" + exitReason);
        if (!eLeave.getValue()) {
            JniNative.requestExitConf(exitReason);
        } else {
            JniNative.requestChairEndConf();
        }
        return true;
    }

    @Override
    public void requestSelectRemoteVideo(List<TermInfo> termInfoList) {
        List<RvideoParam> videoParamList = new ArrayList<RvideoParam>();
        if (termInfoList != null) {
            for (TermInfo termInfo : termInfoList) {
                if (termInfo != null) {
                    RvideoParam param = new RvideoParam();
                    param.setTermId(termInfo.getTermid());
                    param.setVideoType(termInfo.getVideoType());
                    param.setDelayflag(termInfo.getDelayflag());
                    if (termInfo.getReplaceterid() != 0) {
                        param.setReplaceterid(termInfo.getReplaceterid());
                    }
                    videoParamList.add(param);
                }
            }
        }
        JniNative.requestSelectRemoteVideo(videoParamList);
    }

    @Override
    public void chairEndDataShare() {
        JniNative.chairEndDataShare();
    }

    // 发送共享
    @Override
    public void sendDataStreamRGB(int streamType, int width, int height, int[] rgb) {
        JniNative.SREngineInVideoRawStreamRGB(streamType, SRPaas.SRVideoRawFormat.SR_FORMAT_RAW_TYPE_ARGB.getValue(), width, height, rgb, rgb.length);
    }

    // 发送视频流
    public void sendDataStreamYUV(int streamType, int width, int height, byte[] yuv) {
        JniNative.SREngineInVideoRawStreamYUV(streamType, SRPaas.SRVideoRawFormat.SR_FORMAT_RAW_TYPE_YUV420.getValue(), width, height, yuv, yuv.length);
    }
    //发送视频流
    @Override
    public void sendDataStreamVideo(int streamType, byte[] data, int width, int height, int rotation, boolean isMirror, int size) {
        JniNative.SREngineInVideoRawStreamData(streamType, SRPaas.SRVideoRawFormat.SR_FORMAT_RAW_TYPE_NV21.getValue(), data, width, height, rotation, isMirror, size);


    }
    //发送视频流
    @Override
    public void sendDataStreamVideoBuf(int streamType, ByteBuffer data, int width, int height, int rotation, boolean isMirror, int size) {
        JniNative.SREngineInVideoRawStreamDataBuf(streamType, SRPaas.SRVideoRawFormat.SR_FORMAT_RAW_TYPE_NV21.getValue(), data, width, height, rotation, isMirror, size);

    }

    @Override
    public void sendDataStreamVideoBufType(int streamType, int dataType, ByteBuffer data, int width, int height, int rotation, boolean isMirror, int size) {
        JniNative.SREngineInVideoRawStreamDataBuf(streamType, dataType, data, width, height, rotation, isMirror, size);
    }

    @Override
    public void onNetworkChanged() {
        JniNative.SREngineNetworkChanged();
    }

    @Override
    public void setApmKeyContent(String key) {
        JniNative.setApmKeyContent(key);
    }

    @Override
    public String getApmInfo() {
        return JniNative.getApmInfo();
    }

    @Override
    public void getConfInfoState() {
        JniNative.SRReqSRConfStatus(1);
    }

    // 开始发送双流共享
    @Override
    public int requestStartSendDualVideo() {
        return JniNative.requestStartSendDualVideo();
    }

    @Override
    public int requestStopSendDualVideo() {
        return JniNative.requestStopSendDualVideo();
    }

    @Override
    public int openCamera(int unmute_stermid) {
        return JniNative.openCamera(unmute_stermid);
    }

    @Override
    public int closeCamera(int mute_stermid) {
        return JniNative.closeCamera(mute_stermid);
    }

    @Override
    public int resposeSendDualVideoProxy(int avterid, boolean isok, String rejectreason) {
        return JniNative.resposeSendDualVideoProxy(avterid, isok, rejectreason);
    }


    @Override
    public void setSpeakerMode(int mode) {
        JniNative.SREngineSetSpeakerMode(mode);
    }

    @Override
    public void setRunningStatusNotify(int sta_class, int sta_sub_class, String status_str) {
        JniNative.SREngineRunningStatusNotify(sta_class, sta_sub_class, status_str);

    }


    // ============回调接口CallBack==============================================================

    /**
     * @param status
     * @param srError status=false失败原因
     * @param sTermId 入会状态回调
     */
    @Override
    public void OnRspJoinConfCallBack(boolean status, SRError srError, int sTermId) {
        log.E("OnRspJoinConfCallBack...sdkJoinMeetInfo...status:" + status + "...sTermId:" + sTermId + "  confid:" + confid);
        if (status) {// 加入会议成功,获取会议终端信息
            if (mListener != null) {
                mListener.OnRspJoinConfSuccess(sTermId, confid);
            } else {
                log.E("OnRspJoinConfCallBack......mListener is null");
            }
        } else {
            // 加入会议失败
            if (srError != null) {
                log.E("OnRspJoinConfCallBack......srError:" + srError.getCur_error());
                onMeetError(srError);
            }
        }
    }

    @Override
    public void onRspConfTermListCallBack(boolean status, int master_id, int duo_term_id, List<TermInfo> termInfoList, SRError srError) {
        log.E("onRspConfTermListCallBack...终端列表回调，....status:" + status);
        if (mListener != null) {
            mListener.onRspConfTermList(status, master_id, duo_term_id, termInfoList, srError);
        }

    }

    @Override
    public void OnStartSendVideoCallBack(int videoSize) {
        log.E("请求发送视频流回调(被请求方收到)，开始发送....");
    }

    @Override
    public void OnStopSendVideoCallBack() {
        log.E("请求停止发送视频流回调(被请求方收到,停止发送)，....");
        if (mListener != null) mListener.OnStopSendVideoCallBack();
    }

    // 收到发送双流回调
    @Override
    public void OnRecvDualVideoOpenCallBack(int send_id) {
        log.E("接受到双流共享，显示。。。。send_id:" + send_id);
        if (mListener != null) mListener.OnRecvDualVideoOpenCallBack(send_id);

    }

    // 收到关闭双流的回调
    @Override
    public void OnRecvDualVideoCloseCallBack(int close_term_id) {
        log.E("关闭到双流共享，显示。。。。。close_term_id:" + close_term_id);
        // 发送关闭数据共享提示
        if (mListener != null) mListener.OnRecvDualVideoCloseCallBack(close_term_id);

    }

    //暂停共享
    @Override
    public void OnRecvDualVideoPauseCallBack(int pause_term_id) {
        if (mListener != null) mListener.OnRecvDualVideoPauseCallBack(pause_term_id);
    }

    //恢复共享
    @Override
    public void OnRecvDualVideoResumeCallBack(int resumeTermId) {
        if (mListener != null) mListener.OnRecvDualVideoResumeCallBack(resumeTermId);
    }

    //共享人收到其他终端申请共享
    @Override
    public void OnReqAssistVideoProxyCallBack(int termId) {
        if (mListener != null) mListener.OnReqAssistVideoProxyCallBack(termId);
    }

    // 桌面共享其他客户端添加备注
    @Override
    public void OnScreenDrawLabelCallBack(ScreenLableAttr screenLableAttr) {
        if (mListener != null) mListener.OnScreenDrawLabelCallBack(screenLableAttr);
    }

    // 渲染视频界面
    @Override
    public void onRenderCallBackCallBack(int id, int flag,int format, byte[] ybuf, byte[] ubuf, byte[] vbuf, int width, int height,int length) {
        if (mListener != null) {
            mListener.onRenderCallBackCallBack(id, flag,format, ybuf, ubuf, vbuf, width, height,length);
        }
    }


    /**
     * 接口错误处理
     *
     * @param error
     */
    public void onMeetError(eMeetingError error) {
        if (mListener != null) {
            mListener.onMeetingError(error);
        }
    }

    public void onMeetError(SRError srError) {
        if (mListener == null) return;
        mListener.onMeetingError(srError);
    }

    // 退出会议
    @Override
    public void OnExitConfCallBack(String OnExitConfCallBack) {
        log.E("退出会议回调....OnExitConfCallBack");
        if (mListener != null) {
            mListener.OnExitConfCallBack(OnExitConfCallBack);
        }
        log.E("退出会议回调....OnExitConfCallBack.....222");
    }

    // 新终端加入会议
    @Override
    public void onNewTermJoinCallBack(TermInfo termInfo) {
        if (mListener != null) {
            mListener.onNewTermJoinCallBack(termInfo);
        }
    }

    @Override
    public void onTermLeaveCallBack(int leaveterid, SRError srError) {
        if (mListener != null) {
            mListener.onTermLeaveCallBack(leaveterid, srError);
        }

    }


    @Override
    public void onRspSendDualVideoCallBack(boolean isOk, SRError srError) {
        if (mListener != null) {
            mListener.onRspSendDualVideoCallBack(isOk, srError);
        }

    }


    @Override
    public void onTermAudioRecUnOrMuteCallBack(int muteterid, boolean isMute) {
        if (mListener != null) {
            mListener.onTermAudioRecUnOrMuteCallBack(muteterid, isMute);
        }
    }


    @Override
    public void onOpenCameraCallBack(int open_id) {
        if (mListener != null) {
            mListener.onOpenCameraCallBack(open_id);
        }

    }

    @Override
    public void onCloseCameraCallBack(int close_id) {
        if (mListener != null) {
            mListener.onCloseCameraCallBack(close_id);
        }
    }


    @Override
    public void onMasterTransferCallBack(int chair_stermid) {
        if (mListener != null) {
            mListener.onMasterTransferCallBack(chair_stermid);
        }
    }

    @Override
    public void onLockOrUnLockVideoCallBack(int unOrLockId, boolean isLock) {
        if (mListener != null) {
            mListener.onLockOrUnLockVideoCallBack(unOrLockId, isLock);
        }
    }

    @Override
    public void onTermHandUpCallBack(int handupterid, boolean isHandUp) {
        if (mListener != null) {
            mListener.onTermHandUpCallBack(handupterid, isHandUp);
        }
    }

    @Override
    public void onActiveVoiceCallBack(List<VoiceActiveInfo> voiceActiveInfoList) {
        if (mListener != null) {
            mListener.onActiveVoiceCallBack(voiceActiveInfoList);
        }

    }

    @Override
    public void onMuteAudioAllTermNotifyCallBack(boolean isMute) {
        if (mListener != null) {
            mListener.onMuteAudioAllTermNotifyCallBack(isMute);
        }

    }

    @Override
    public void onChairEndConfCallBack(int endTermid, String endName) {
        if (mListener != null) {
            mListener.onChairEndConfCallBack(endTermid, endName);
        }
    }

    @Override
    public void OnStackConnErrorCallBack(int type) {
        if (mListener != null) {
            mListener.OnStackConnErrorCallBack(type);
        }

    }

    @Override
    public void OnNetwrokNotify(int status) {
        if (mListener != null) {
            mListener.OnNetwrokNotify(status);
        }
    }

    @Override
    public void SREngineRunningStatusNotifyCallBack(int stautsTermid, int staClass, int staSubCls, String staStr) {
        if (mListener != null) {
            mListener.SREngineRunningStatusNotifyCallBack(stautsTermid, staClass, staSubCls, staStr);
        }

    }

    @Override
    public void onTermChangeNameCallBack(int changeterid, String term_name) {
        if (mListener != null) {
            mListener.onTermChangeNameCallBack(changeterid, term_name);
        }
    }

    @Override
    public void onIndChairEndDataShareCallBack(int chair_stermid, String chair_name) {
        if (mListener != null) {
            mListener.onIndChairEndDataShareCallBack(chair_stermid, chair_name);
        }
    }

    @Override
    public void onScreenClearLabelCallBack(int cleard_stermid) {
        if (mListener != null) {
            mListener.onScreenClearLabelCallBack(cleard_stermid);
        }
    }

    @Override
    public void onSendStreamInfoStatsCallBack(List<SRSendStreamInfo> sendStreamInfoList) {
        if (mListener != null) {
            mListener.onSendStreamInfoStatsCallBack(sendStreamInfoList);
        }
    }

    @Override
    public void onRecvStreamInfoStatsCallBack(List<SRRecvStreamInfo> recvStreamInfoList) {
        if (mListener != null) {
            mListener.onRecvStreamInfoStatsCallBack(recvStreamInfoList);
        }
    }

    @Override
    public void onServerErrorCallBack(int errorCode) {
        if (mListener != null) {
            mListener.onServerErrorCallBack(errorCode);
        }
    }

    @Override
    public void getJNIExcaption() {
        if (mListener != null) {
            mListener.getJNIExcaption();
        }
    }

    @Override
    public void onConfForceMuteAllTermCallBack(boolean isforcemute) {
        if (mListener != null) {
            mListener.onConfForceMuteAllTermCallBack(isforcemute);
        }
    }

    @Override
    public void onRspConfInfoStatusCallBack(boolean isok, ConfInfoStatus confInfoStatus, SRError srError) {
        if (mListener != null) {
            mListener.onRspConfInfoStatusCallBack(isok, confInfoStatus, srError);
        }
    }

    @Override
    public void onIndTerCRSRecStateCallBack(int recordstate, SRError error) {
        if (mListener != null) {
            mListener.onIndTerCRSRecStateCallBack(recordstate, error);
        }
    }

    @Override
    public void onAllMPInfoCallBack(List<SRMediaPInfo> srMediaPInfoList) {
        if (mListener != null) {
            mListener.onAllMPInfoCallBack(srMediaPInfoList);
        }
    }

    @Override
    public void onMPScreenInfoCallback(int channelid, int screenid, int screentype, int addordel) {
        if (mListener != null) {
            mListener.onMPScreenInfoCallback(channelid, screenid, screentype, addordel);
        }
    }

    @Override
    public void onUpdateAddPaticipantsCallback(List<TermInfo> addTermInfoList) {
        if (mListener != null) {
            mListener.onUpdateAddPaticipantsCallback(addTermInfoList);
        }
    }

    @Override
    public void onUpdateDelPaticipantsCallback(List<TermInfo> delTermInfoList) {
        if (mListener != null) {
            mListener.onUpdateDelPaticipantsCallback(delTermInfoList);
        }
    }

    @Override
    public void OnIndTerSpecialtypeTransferCallBack(int nspclterid, int nspcltype) {
        if (mListener != null) {
            mListener.OnIndTerSpecialtypeTransferCallBack(nspclterid, nspcltype);
        }
    }

    @Override
    public void OnIndTerCRSLiveStateCallBack(int livestate, String liveplayurl, SRError srError) {
        if (mListener != null) {
            mListener.OnIndTerCRSLiveStateCallBack(livestate, liveplayurl, srError);
        }
    }

    @Override
    public void OnIndLiveSettingChangedCallBack(OnliveInfo info) {
        if (mListener != null) {
            mListener.OnIndLiveSettingChangedCallBack(info);
        }
    }

    @Override
    public void OnRecvConfMessageCallBack(int termId, String message) {
        if (mListener != null) {
            mListener.OnRecvConfMessageCallBack(termId, message);
        }
    }

    @Override
    public void onServerOkCallBack(int okCode) {
        if (mListener != null) {
            mListener.onServerOkCallBack(okCode);
        }
    }
}
