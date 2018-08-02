package org.suirui.srpaas.sdk;

import com.suirui.srpaas.base.util.log.SRLog;

import org.suirui.srpaas.entry.ConfInfoStatus;
import org.suirui.srpaas.entry.OnliveInfo;
import org.suirui.srpaas.entry.SRError;
import org.suirui.srpaas.entry.SRMediaPInfo;
import org.suirui.srpaas.entry.SRRecvStreamInfo;
import org.suirui.srpaas.entry.SRSendStreamInfo;
import org.suirui.srpaas.entry.ScreenLableAttr;
import org.suirui.srpaas.entry.TermInfo;
import org.suirui.srpaas.entry.VoiceActiveInfo;
import org.suirui.srpaas.sdk.inter.OnExitConferenceListener;
import org.suirui.srpaas.sdk.inter.OnJoinMeetingListener;
import org.suirui.srpaas.sdk.inter.OnRenderListener;
import org.suirui.srpaas.sdk.inter.OnSendVideoListener;

import java.util.List;

public class SdkCallBack {
    private static final SRLog log = new SRLog(SdkCallBack.class.getName());
    private static SdkCallBack callBack = null;
    OnJoinMeetingListener joinListener = null;// 加入会议
    OnExitConferenceListener exitListener = null;// 退出会议
    OnRenderListener renderListener = null;// 渲染
    OnSendVideoListener sendVideoLister = null;// 发送视频

    public synchronized static SdkCallBack getInstance() {

        if (callBack == null) {
            callBack = new SdkCallBack();
        }
        return callBack;

    }

    public OnSendVideoListener getSendVideoLister() {
        return sendVideoLister;
    }

    public void addOnSendVideoLister(OnSendVideoListener sendVideoLister) {
        this.sendVideoLister = sendVideoLister;
    }

    public OnRenderListener getRenderListener() {
        return renderListener;
    }

    public void addOnRenderListener(OnRenderListener renderListener) {
        this.renderListener = renderListener;
    }

    public OnExitConferenceListener getExitListener() {
        return exitListener;
    }

    public void addExitListener(OnExitConferenceListener exitListener) {
        this.exitListener = exitListener;
    }

    public OnJoinMeetingListener getJoinListener() {
        return joinListener;
    }

    public void addJoinListener(OnJoinMeetingListener joinListener) {
        this.joinListener = joinListener;
    }

    public void OnRspJoinConfCallBack(boolean status, SRError srError,
                                      int sTermId) {
        if (joinListener != null) {
            joinListener.OnRspJoinConfCallBack(status, srError, sTermId);
        }
    }

    /**
     * 获取会议中所有终端信息回调
     *
     * @param status       成功 true 失败false
     * @param master_id    主席id
     * @param duo_term_id
     * @param termInfoList 终端信息
     * @param srError      失败原因
     */
    public void onRspConfTermListCallBack(boolean status, int master_id, int duo_term_id,
                                          List<TermInfo> termInfoList, SRError srError) {
        if (joinListener != null) {
            joinListener.onRspConfTermListCallBack(status,
                    master_id, duo_term_id, termInfoList, srError);
        }
    }

    //请求发送视频流回调(被请求方收到)
    public void OnStartSendVideoCallBack(int videoSize) {
        if (joinListener != null) {
            joinListener.OnStartSendVideoCallBack(videoSize);
        }
    }

    //请求停止发送视频流回调
    public void OnStopSendVideoCallBack() {
        if (joinListener != null) {
            joinListener.OnStopSendVideoCallBack();
        }
    }

    /**
     * 渲染
     *
     * @param id
     * @param flag
     * @param ybuf
     * @param ubuf
     * @param vbuf
     * @param width
     * @param height
     */
    public void onRenderCallBackCallBack(int id, int flag,int format, byte[] ybuf,
                                         byte[] ubuf, byte[] vbuf, int width, int height,int length) {
        // 视频显示
        if (renderListener != null) {
            renderListener.onRenderCallBackCallBack(id, flag,format, ybuf, ubuf, vbuf,
                    width, height, length);
        }
    }

    /**
     * 退出会议
     *
     * @param exitResion
     */
    public void OnExitConfCallBack(String exitResion) {
        if (exitListener != null)
            exitListener.OnExitConfCallBack(exitResion);
    }

    /**
     * 接受到数据共享
     *
     * @param send_id
     */
    public void OnRecvDualVideoOpenCallBack(
            int send_id) {
        if (joinListener != null) {
            joinListener.OnRecvDualVideoOpenCallBack(send_id);
        }
    }

    /**
     * 关闭双流的回调
     *
     * @param close_term_id 终端id
     */
    public void OnRecvDualVideoCloseCallBack(int close_term_id) {
        if (joinListener != null) {
            joinListener.OnRecvDualVideoCloseCallBack(close_term_id);
        }
    }

    //暂停共享
    public void OnRecvDualVideoPauseCallBack(int pause_term_id) {
        if (joinListener != null) {
            joinListener.OnRecvDualVideoPauseCallBack(pause_term_id);
        }
    }

    //恢复共享
    public void OnRecvDualVideoResumeCallBack(int resumeTermId) {
        if (joinListener != null) {
            joinListener.OnRecvDualVideoResumeCallBack(resumeTermId);
        }
    }

    //共享人收到其他终端申请共享
    public void OnReqAssistVideoProxyCallBack(int termId) {
        if (joinListener != null) {
            joinListener.OnReqAssistVideoProxyCallBack(termId);
        }
    }

    //桌面共享其他客户端添加备注
    public void OnScreenDrawLabelCallBack(ScreenLableAttr screenLableAttr) {
        if (joinListener != null) {
            joinListener.OnScreenDrawLabelCallBack(screenLableAttr);
        }
    }


    public void onRspSendDualVideoCallBack(boolean isOk, SRError srError) {
        if (joinListener != null) {
            joinListener.onRspSendDualVideoCallBack(isOk, srError);
        }

    }

    /**
     * 有新的终端加入会议
     *
     * @param termInfo
     */
    public void onNewTermJoinCallBack(
            TermInfo termInfo) {
        if (joinListener != null) {
            joinListener.onNewTermJoinCallBack(termInfo);
        }
    }

    /**
     * 其他终端离开会议
     *
     * @param srError
     * @param leaveterid
     */
    public void onTermLeaveCallBack(int leaveterid, SRError srError) {
        if (joinListener != null) {
            joinListener.onTermLeaveCallBack(leaveterid, srError);
        }
    }

    /**
     * 其它客户端静音/取消静音回调
     *
     * @param muteterid
     * @param isMute    true为静音 false 为取消静音
     */
    public void onTermAudioRecUnOrMuteCallBack(int muteterid, boolean isMute) {
        if (joinListener != null) {
            joinListener.onTermAudioRecUnOrMuteCallBack(muteterid, isMute);
        }

    }

    public void onMasterTransferCallBack(int chair_stermid) {
        if (joinListener != null) {
            joinListener.onMasterTransferCallBack(chair_stermid);
        }
    }

    public void onLockOrUnLockVideoCallBack(int unOrLockId, boolean isLock) {
        if (joinListener != null) {
            joinListener.onLockOrUnLockVideoCallBack(unOrLockId, isLock);
        }
    }

    public void onTermHandUpCallBack(int handupterid, boolean isHandUp) {
        if (joinListener != null) {
            joinListener.onTermHandUpCallBack(handupterid, isHandUp);
        }
    }


    public void onOpenCameraCallBack(int open_id) {
        if (joinListener != null) {
            joinListener.onOpenCameraCallBack(open_id);
        }
    }

    public void onCloseCameraCallBack(int close_id) {
        if (joinListener != null) {
            joinListener.onCloseCameraCallBack(close_id);
        }
    }

    public void onActiveVoiceCallBack(List<VoiceActiveInfo> voiceActiveInfoList) {
        if (joinListener != null) {
            joinListener.onActiveVoiceCallBack(voiceActiveInfoList);
        }
    }

    public void onMuteAudioAllTermNotifyCallBack(boolean isMute) {
        if (joinListener != null) {
            joinListener.onMuteAudioAllTermNotifyCallBack(isMute);
        }
    }

    public void onChairEndConfCallBack(int endTermid, String endName) {
        if (joinListener != null) {
            joinListener.onChairEndConfCallBack(endTermid, endName);
        }
    }

    public void OnStackConnErrorCallBack(int type) {
        if (joinListener != null) {
            joinListener.OnStackConnErrorCallBack(type);
        }
    }

    //网络切换回调
    public void OnNetwrokNotify(int status) {
        if (joinListener != null) {
            joinListener.OnNetwrokNotify(status);
        }
    }

    public void SREngineRunningStatusNotifyCallBack(int stautsTermid,
                                                    int staClass, int staSubCls, String staStr) {
        if (joinListener != null) {
            joinListener.SREngineRunningStatusNotifyCallBack(stautsTermid, staClass, staSubCls, staStr);
        }
    }

    public void onTermChangeNameCallBack(int changeterid, String term_name) {
        if (joinListener != null) {
            joinListener.onTermChangeNameCallBack(changeterid, term_name);
        }
    }

    public void onIndChairEndDataShareCallBack(int chair_stermid, String chair_name) {
        if (joinListener != null) {
            joinListener.onIndChairEndDataShareCallBack(chair_stermid, chair_name);
        }
    }

    public void onScreenClearLabelCallBack(int cleard_stermid) {
        if (joinListener != null) {
            joinListener.onScreenClearLabelCallBack(cleard_stermid);
        }
    }

    public void onSendStreamInfoStatsCallBack(List<SRSendStreamInfo> sendStreamInfoList) {
        if (joinListener != null) {
            joinListener.onSendStreamInfoStatsCallBack(sendStreamInfoList);
        }
    }

    public void onRecvStreamInfoStatsCallBack(List<SRRecvStreamInfo> recvStreamInfoList) {
        if (joinListener != null) {
            joinListener.onRecvStreamInfoStatsCallBack(recvStreamInfoList);
        }
    }

    public void onServerErrorCallBack(int errorCode) {
        if (joinListener != null) {
            joinListener.onServerErrorCallBack(errorCode);
        }
    }

    public void getJNIExcaption(){
        if (joinListener != null) {
            joinListener.getJNIExcaption();
        }
    }

    public void onConfForceMuteAllTermCallBack(boolean isforcemute) {
        if (joinListener != null) {
            joinListener.onConfForceMuteAllTermCallBack(isforcemute);
        }
    }

    public void onRspConfInfoStatusCallBack(boolean isok, ConfInfoStatus confInfoStatus, SRError srError) {
        if (joinListener != null) {
            joinListener.onRspConfInfoStatusCallBack(isok, confInfoStatus, srError);
        }
    }

    public void onIndTerCRSRecStateCallBack(int recordstate, SRError error) {
        if (joinListener != null) {
            joinListener.onIndTerCRSRecStateCallBack(recordstate, error);
        }
    }

    public void onAllMPInfoCallBack(List<SRMediaPInfo> srMediaPInfoList) {
        if (joinListener != null) {
            joinListener.onAllMPInfoCallBack(srMediaPInfoList);
        }
    }

    public void onMPScreenInfoCallback(int channelid, int screenid, int screentype, int addordel) {
        if (joinListener != null) {
            joinListener.onMPScreenInfoCallback(channelid, screenid, screentype, addordel);
        }
    }

    public void onUpdateAddPaticipantsCallback(List<TermInfo> addTermInfoList) {
        if (joinListener != null) {
            joinListener.onUpdateAddPaticipantsCallback(addTermInfoList);
        }
    }

    public void onUpdateDelPaticipantsCallback(List<TermInfo> delTermInfoList) {
        if (joinListener != null) {
            joinListener.onUpdateDelPaticipantsCallback(delTermInfoList);
        }
    }

    public void OnIndTerSpecialtypeTransferCallBack(int nspclterid, int nspcltype) {
        if (joinListener != null) {
            joinListener.OnIndTerSpecialtypeTransferCallBack(nspclterid, nspcltype);
        }
    }

    public void OnIndTerCRSLiveStateCallBack(int livestate, String liveplayurl, SRError srError) {
        if (joinListener != null) {
            joinListener.OnIndTerCRSLiveStateCallBack(livestate, liveplayurl, srError);
        }
    }

    public void OnIndLiveSettingChangedCallBack(OnliveInfo info) {
        if (joinListener != null) {
            joinListener.OnIndLiveSettingChangedCallBack(info);
        }
    }

    public void OnRecvConfMessageCallBack(int termId, String message) {
        if (joinListener != null) {
            joinListener.OnRecvConfMessageCallBack(termId, message);
        }
    }

    public void onServerOkCallBack(int okCode) {
        if (joinListener != null) {
            joinListener.onServerOkCallBack(okCode);
        }
    }
}
