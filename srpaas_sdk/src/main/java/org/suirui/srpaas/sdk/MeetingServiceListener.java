package org.suirui.srpaas.sdk;

import org.suirui.srpaas.entry.ConfInfoStatus;
import org.suirui.srpaas.entry.MeetingInfo;
import org.suirui.srpaas.entry.OnliveInfo;
import org.suirui.srpaas.entry.SRError;
import org.suirui.srpaas.entry.SRMediaPInfo;
import org.suirui.srpaas.entry.SRRecvStreamInfo;
import org.suirui.srpaas.entry.SRSendStreamInfo;
import org.suirui.srpaas.entry.ScreenLableAttr;
import org.suirui.srpaas.entry.TermInfo;
import org.suirui.srpaas.entry.VoiceActiveInfo;
import org.suirui.srpaas.sdk.SRPaas.eMeetingError;

import java.util.List;

import okhttp3.Call;

/**
 * 会议相关接口的错误监听
 *
 * @author cui.li
 */
public interface MeetingServiceListener {
    /**
     * 第三方是否需要上报
     *
     * @param meetingInfo
     */
    void OnMeetPort(MeetingInfo meetingInfo);


    /**
     * 会议失败相关状态
     *
     * @param srError
     */
    void onMeetingError(SRError srError);

    /**
     * 接口返回的相关状态
     *
     * @param emeetingnoerror
     */
    void onMeetingError(eMeetingError emeetingnoerror);

    /**
     * 服务器相关操作返回的错误
     */
    void onHttpMeetingError(int errorCode, String msg);

    void onHttpError(Call call, Exception e, int i);

    /**
     * 加入会议成功回调
     *
     * @param sTermId
     */
    void OnRspJoinConfSuccess(int sTermId, String confId);

    /**
     * 返回终端列表
     *
     * @param master_id    主席id
     * @param duo_term_id
     * @param termInfoList
     */
    void onRspConfTermList(boolean status, int master_id, int duo_term_id, List<TermInfo> termInfoList, SRError srError);

    /**
     * 视频渲染
     *
     * @param y
     * @param u
     * @param v
     * @param width
     * @param height
     */
    void onRenderCallBackCallBack(int id, int flag,int format, byte[] y, byte[] u, byte[] v, int width, int height,int lenght);

    /**
     * 新终端加入会议
     *
     * @param termInfo
     */
    void onNewTermJoinCallBack(TermInfo termInfo);

    /**
     * 其他终端离开当前会议
     *
     * @param srError
     * @param leaveterid
     */
    void onTermLeaveCallBack(int leaveterid, SRError srError);

    /**
     * 其他终端关闭共享
     *
     * @param close_term_id
     */
    void OnRecvDualVideoCloseCallBack(int close_term_id);

    //暂停共享
    void OnRecvDualVideoPauseCallBack(int pause_term_id);

    //恢复共享
    void OnRecvDualVideoResumeCallBack(int resumeTermId);

    //共享人收到其他终端申请共享
    void OnReqAssistVideoProxyCallBack(int termId);

    // 桌面共享其他客户端添加备注
    void OnScreenDrawLabelCallBack(ScreenLableAttr screenLableAttr);

    /**
     * 收到数据共享
     *
     * @param send_id
     */
    void OnRecvDualVideoOpenCallBack(int send_id);

    /**
     * 请求开启共享回调
     *
     * @param isOk    true，可以发送共享，false 不允许发送共享
     * @param srError
     */
    void onRspSendDualVideoCallBack(boolean isOk, SRError srError);

    /**
     * 其它客户端静音/取消静音回调
     *
     * @param muteterid
     * @param isMute    true为静音 false 为取消静音
     */
    void onTermAudioRecUnOrMuteCallBack(int muteterid, boolean isMute);

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
     * 主持人身份切换
     *
     * @param chair_stermid
     */
    void onMasterTransferCallBack(int chair_stermid);

    /**
     * 设置或取消焦点视频
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
    void onTermHandUpCallBack(int handupterid, boolean isHandUp);

    /**
     * 语音激励
     *
     * @param voiceActiveInfoList
     */

    public void onActiveVoiceCallBack(List<VoiceActiveInfo> voiceActiveInfoList);

    /**
     * 全部靜音、取消全部靜音
     *
     * @param isMute
     */
    public void onMuteAudioAllTermNotifyCallBack(boolean isMute);

    /**
     * 主持人結束會議
     */
    public void onChairEndConfCallBack(int endTermid, String endName);

    /**
     * 退出会议
     *
     * @param exit_reason
     */
    public void OnExitConfCallBack(String exit_reason);

    /**
     * 异常，退出会议
     */
    public void OnStackConnErrorCallBack(int type);

    /**
     * 网络切换
     *
     * @param status
     */
    public void OnNetwrokNotify(int status);

    /**
     * 返回参会人或者会议中的状态
     *
     * @param stautsTermid
     * @param staClass     参会人或者会议中的状态
     * @param staSubCls    具体的参会人状态或者会议状态
     */
    public void SREngineRunningStatusNotifyCallBack(int stautsTermid, int staClass, int staSubCls, String staStr);

    /**
     * 改名(其它客户端修改名称)
     *
     * @param changeterid
     * @param term_name
     */
    public void onTermChangeNameCallBack(int changeterid, String term_name);

    /**
     * 其他端停止共享
     */
    void OnStopSendVideoCallBack();

    /**
     * 共享中主持人结束会议
     *
     * @param chair_stermid
     * @param chair_name
     */
    void onIndChairEndDataShareCallBack(int chair_stermid, String chair_name);

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
     * JNI异常
     */
    void getJNIExcaption();

    /**
     * 强制静音
     *
     * @param isforcemute
     */
    void onConfForceMuteAllTermCallBack(boolean isforcemute);

    /**
     * 获取会议信息
     *
     * @param isok
     * @param confInfoStatus
     * @param srError
     */
    void onRspConfInfoStatusCallBack(boolean isok, ConfInfoStatus confInfoStatus, SRError srError);

    /**
     * 主持人开始/结束会议的录制
     *
     * @param recordstate
     */
    void onIndTerCRSRecStateCallBack(int recordstate, SRError error);

    //入会收到的MP消息
    void onAllMPInfoCallBack(List<SRMediaPInfo> srMediaPInfoList);

    //入会收到的MPScreen消息
    void onMPScreenInfoCallback(int channelid, int screenid, int screentype, int addordel);

    //参会人列表更新（增加）
    void onUpdateAddPaticipantsCallback(List<TermInfo> addTermInfoList);

    //参会人列表更新（删除）
    void onUpdateDelPaticipantsCallback(List<TermInfo> delTermInfoList);

    //邀请成功
    void onInviteSuccess();

    //邀请失败
    void onHttpInviteError(int errorCode, String msg);

    //投频终端的回调
    void OnIndTerSpecialtypeTransferCallBack(int nspclterid, int nspcltype);

    //直播状态回调
    void OnIndTerCRSLiveStateCallBack(int livestate, String liveplayurl, SRError srError);

    //直播变更状态回调
    void OnIndLiveSettingChangedCallBack(OnliveInfo info);

    //聊天接收到的消息
    void OnRecvConfMessageCallBack(int termId, String message);

    //网络异常后，又重新链接成功
    void onServerOkCallBack(int okCode);
}
