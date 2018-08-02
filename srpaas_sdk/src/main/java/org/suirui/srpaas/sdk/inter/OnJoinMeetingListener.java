package org.suirui.srpaas.sdk.inter;

import org.suirui.srpaas.entry.ConfInfoStatus;
import org.suirui.srpaas.entry.OnliveInfo;
import org.suirui.srpaas.entry.SRError;
import org.suirui.srpaas.entry.SRMediaPInfo;
import org.suirui.srpaas.entry.SRRecvStreamInfo;
import org.suirui.srpaas.entry.SRSendStreamInfo;
import org.suirui.srpaas.entry.ScreenLableAttr;
import org.suirui.srpaas.entry.TermInfo;
import org.suirui.srpaas.entry.VoiceActiveInfo;

import java.util.List;

public interface OnJoinMeetingListener {
    /**
     * 入会状态回调
     *
     * @param status
     * @param srError status=false失败原因
     * @param sTermId 入会状态回调
     */
    void OnRspJoinConfCallBack(boolean status, SRError srError, int sTermId);

    /**
     * 获取会议中所有终端信息回调
     *
     * @param status       成功 true 失败false
     * @param master_id    主席id
     * @param duo_term_id
     * @param termInfoList 终端信息
     * @param srError      失败原因
     */
    void onRspConfTermListCallBack(boolean status,
                                   int master_id, int duo_term_id, List<TermInfo> termInfoList,
                                   SRError srError);

    //请求发送视频流回调(被请求方收到)
    void OnStartSendVideoCallBack(int videoSize);

    //请求停止发送视频流回调
    void OnStopSendVideoCallBack();

    /**
     * 收到数据共享
     *
     * @param send_id
     */
    public void OnRecvDualVideoOpenCallBack(int send_id);

    /**
     * 收到关闭数据共享的
     *
     * @param close_term_id
     */
    public void OnRecvDualVideoCloseCallBack(int close_term_id);

    //暂停共享
    public void OnRecvDualVideoPauseCallBack(int pause_term_id);

    //恢复共享
    public void OnRecvDualVideoResumeCallBack(int resumeTermId);

    //共享人收到其他终端申请共享
    public void OnReqAssistVideoProxyCallBack(int termId);

    //桌面共享其他客户端添加备注
    void OnScreenDrawLabelCallBack(ScreenLableAttr screenLableAttr);

    /**
     * 有新的终端加入会议
     *
     * @param termInfo
     */
    public void onNewTermJoinCallBack(
            TermInfo termInfo);

    /**
     * 开始发送视频
     *
     * @param isOk
     * @param srError
     */
    public void onRspSendDualVideoCallBack(boolean isOk, SRError srError);

    /**
     * 其他终端离开当前会议
     *
     * @param srError
     * @param leaveterid
     */
    public void onTermLeaveCallBack(int leaveterid, SRError srError);

    /**
     * 其它客户端静音/取消静音回调
     *
     * @param muteterid
     * @param isMute    true为静音 false 为取消静音
     */
    public void onTermAudioRecUnOrMuteCallBack(int muteterid, boolean isMute);

    /**
     * 主持人身份切换回调
     *
     * @param chair_stermid
     */
    public void onMasterTransferCallBack(int chair_stermid);

    /**
     * 设置或者取消焦点视频
     *
     * @param unOrLockId
     * @param isLock
     */
    void onLockOrUnLockVideoCallBack(int unOrLockId, boolean isLock);

    /**
     * 举手、放下 回调
     *
     * @param handupterid
     * @param isHandUp
     */
    public void onTermHandUpCallBack(int handupterid, boolean isHandUp);


    /**
     * 收到其他端视频流（选看视频）
     *
     * @param open_id
     */
    public void onOpenCameraCallBack(int open_id);

    /**
     * 其他端关闭视频流（关闭选看视频）
     *
     * @param close_id
     */
    public void onCloseCameraCallBack(int close_id);

    /**
     * 语音激励
     *
     * @param voiceActiveInfoList
     */
    public void onActiveVoiceCallBack(List<VoiceActiveInfo> voiceActiveInfoList);

    /**
     * 全部 静音、取消全部静音
     *
     * @param isMute
     */
    public void onMuteAudioAllTermNotifyCallBack(boolean isMute);

    /**
     * 主持人结束会议
     */
    public void onChairEndConfCallBack(int endTermid, String endName);

    /**
     * 会议中异常，退出会议
     */
    public void OnStackConnErrorCallBack(int type);

    //网络切换回调
    public void OnNetwrokNotify(int status);

    /**
     * pc设备回调
     *
     * @param stautsTermid
     * @param staClass
     * @param staSubCls
     * @param staStr
     */
    public void SREngineRunningStatusNotifyCallBack(int stautsTermid,
                                                    int staClass, int staSubCls, String staStr);

    /**
     * 主持人改名
     *
     * @param changeterid
     * @param term_name
     */
    public void onTermChangeNameCallBack(int changeterid, String term_name);

    /**
     * 会中共享，结束会议
     *
     * @param chair_stermid
     * @param chair_name
     */
    void onIndChairEndDataShareCallBack(int chair_stermid, String chair_name);

    /**
     * 清除标注
     *
     * @param cleard_stermid
     */
    void onScreenClearLabelCallBack(int cleard_stermid);

    /**
     * 发送数据统计信息回调
     *
     * @param sendStreamInfoList
     */
    void onSendStreamInfoStatsCallBack(List<SRSendStreamInfo> sendStreamInfoList);

    /**
     * 接收数据统计信息回调
     *
     * @param recvStreamInfoList
     */
    void onRecvStreamInfoStatsCallBack(List<SRRecvStreamInfo> recvStreamInfoList);

    /**
     * 服务器返回错误码
     *
     * @param errorCode
     */
    void onServerErrorCallBack(int errorCode);

    /**
     * JNI异常处理
     */
    void getJNIExcaption();

    //强制静音
    void onConfForceMuteAllTermCallBack(boolean isforcemute);

    //获取会议的信息
    void onRspConfInfoStatusCallBack(boolean isok, ConfInfoStatus confInfoStatus, SRError srError);

    //主持人开始/结束会议的录制
    void onIndTerCRSRecStateCallBack(int recordstate, SRError error);

    //新加入的终端可能会出收到该消息
    void onAllMPInfoCallBack(List<SRMediaPInfo> srMediaPInfoList);

    //新加入的终端可能会出收到该消息
    void onMPScreenInfoCallback(int channelid, int screenid, int screentype, int addordel);

    //参会人列表更新（增加）
    void onUpdateAddPaticipantsCallback(List<TermInfo> addTermInfoList);

    //参会人列表更新（删除）
    void onUpdateDelPaticipantsCallback(List<TermInfo> delTermInfoList);

    //投频终端的回调
    void OnIndTerSpecialtypeTransferCallBack(int nspclterid, int nspcltype);

    //直播的状态回调
    void OnIndTerCRSLiveStateCallBack(int livestate, String liveplayurl, SRError srError);

    //直播更改状态回调
    void OnIndLiveSettingChangedCallBack(OnliveInfo info);

    //聊天中收到的消息
    void OnRecvConfMessageCallBack(int termId, String message);

    //网络异常后，又重新链接成功
    void onServerOkCallBack(int okCode);
}
