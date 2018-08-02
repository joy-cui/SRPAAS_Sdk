package org.suirui.srpaas.jni;

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
import org.suirui.srpaas.sdk.SdkCallBack;

import java.util.ArrayList;

/**
 * jni接口回调用
 *
 * @author cui.li
 */
public class CallBack {
    private static final SRLog log = new SRLog(CallBack.class.getName());
    private static CallBack callBack = null;

    public CallBack() {
//		super();
    }

    public synchronized static CallBack getInstance() {

        if (callBack == null) {
            callBack = new CallBack();
        }
        return callBack;

    }

    /**
     * 入会状态回调（new）
     *
     * @param status  1:success   0:fail
     * @param srError status=false失败原因
     * @param sTermId 入会状态回调
     */
    void OnRspJoinConfCallBack(boolean status, SRError srError, int sTermId) {
        log.E("OnRspJoinConfCallBack..入会状态回调...." + status + " sTermId:" + sTermId);
        SdkCallBack.getInstance().OnRspJoinConfCallBack(status, srError, sTermId);
    }

    /**
     * 退出会议回调(本人退出会议)
     *
     * @param exitResion
     */
    void OnExitConfCallBack(String exitResion) {
        log.E("OnExitConfCallBack..退出会议回调...." + exitResion);
        SdkCallBack.getInstance().OnExitConfCallBack(exitResion);
    }

    /**
     * 新终端加入会议
     *
     * @param termInfoList
     */
    void onNewTermJoinCallBack(
            ArrayList<TermInfo> termInfoList) {
        if (termInfoList != null) {
            TermInfo termInfo = termInfoList.get(0);
            log.E("onNewTermJoinCallBack...." + termInfo.getTermid()
                    + " Tername: " + termInfo.getTername() + " VideoType: "
                    + termInfo.getVideoType());
            SdkCallBack.getInstance().onNewTermJoinCallBack(
                    termInfo);
        }

    }

    /**
     * 其他终端离开会议
     *
     * @param srError
     * @param leaveterid
     */
    void onTermLeaveCallBack(int leaveterid, SRError srError) {
        log.E("onTermLeaveCallBack...... leaveterid:" + leaveterid);
        SdkCallBack.getInstance().onTermLeaveCallBack(leaveterid, srError);

    }


    /**
     * 渲染视频
     *
     * @param id
     * @param flag   0-low resolution video, 1-high resolution video, 2-datashare
     * @param y
     * @param u
     * @param v
     * @param width
     * @param height
     */
    void onRenderCallBackCallBack(int id, int flag,int format, byte[] y, byte[] u,
                                  byte[] v, int width, int height,int length) {
//        log.E("onRenderCallBackCallBack...... id:" + id + "  flag:" + flag + "  width:" + width + " height:" + height);
        SdkCallBack.getInstance().onRenderCallBackCallBack(id, flag, format,y, u, v,
                width, height,length);

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
    void onRspConfTermListCallBack(boolean status,
                                   int master_id, int duo_term_id, ArrayList<TermInfo> termInfoList,
                                   SRError srError) {
//        log.E("获取会议终端列表回调...." + status + "...master_id:" + master_id + "  duo_term_id：" + duo_term_id);
//        if (termInfoList != null) {
//            for (TermInfo terminfo : termInfoList) {
//                log.E("getTermid: " + terminfo.getTermid() + " getTername: "
//                        + terminfo.getTername() + " isIsmuted: "
//                        + terminfo.isIsmuted());
//            }
//        }
        SdkCallBack.getInstance().onRspConfTermListCallBack(status, master_id, duo_term_id, termInfoList, srError);
    }

    //请求发送视频流回调(被请求方收到)
    void OnStartSendVideoCallBack(int videoSize) {
        log.E("有人请求发送视频，大小是:" + videoSize);
        SdkCallBack.getInstance().OnStartSendVideoCallBack(videoSize);
    }

    //请求停止发送视频流回调
    void OnStopSendVideoCallBack() {
        log.E("有人请求停止发送视频流");
        SdkCallBack.getInstance().OnStopSendVideoCallBack();
    }

    /**
     * 请求开启共享回调，是否可以开启共享
     */
    void onRspSendDualVideoCallBack(boolean isOk, SRError srError) {
        log.E("开启双流calback........isOk:" + isOk);
        SdkCallBack.getInstance().onRspSendDualVideoCallBack(isOk, srError);
    }


    /**
     * 接收端收到接收双流 回调
     *
     * @param send_id 发送双流终端id
     */
    void OnRecvDualVideoOpenCallBack(int send_id) {
        log.E("接收端收到接收双流 回调......OnRecvDualVideoOpenCallBack....send_id：" + send_id);
        SdkCallBack.getInstance().OnRecvDualVideoOpenCallBack(send_id);
    }

    /**
     * 关闭双流的回调
     *
     * @param close_term_id 终端id
     */
    void OnRecvDualVideoCloseCallBack(int close_term_id) {
        log.E("收到关闭收双流 回调........");
        SdkCallBack.getInstance()
                .OnRecvDualVideoCloseCallBack(close_term_id);
    }

    //暂停共享
    void OnRecvDualVideoPauseCallBack(int pause_term_id) {
        SdkCallBack.getInstance()
                .OnRecvDualVideoPauseCallBack(pause_term_id);
    }

    //恢复共享
    void OnRecvDualVideoResumeCallBack(int resumeTermId) {
        SdkCallBack.getInstance()
                .OnRecvDualVideoResumeCallBack(resumeTermId);
    }

    //共享人收到其他终端申请共享
    void OnReqAssistVideoProxyCallBack(int termId) {
        log.E("收到其他端的共享申请....OnReqAssistVideoProxyCallBack..termId:" + termId);
        SdkCallBack.getInstance()
                .OnReqAssistVideoProxyCallBack(termId);
    }

    //桌面共享其他客户端添加备注
    void OnScreenDrawLabelCallBack(ArrayList<ScreenLableAttr> screenLableAttrsList) {
        if (screenLableAttrsList != null) {
            ScreenLableAttr screenLableAttr = screenLableAttrsList.get(0);
            SdkCallBack.getInstance().OnScreenDrawLabelCallBack(screenLableAttr);
        }

    }

    void onScreenClearLabelCallBack(int cleard_stermid) {
        log.E("onScreenClearLabelCallBack。。。cleard_stermid:" + cleard_stermid);
        SdkCallBack.getInstance().onScreenClearLabelCallBack(cleard_stermid);
    }

    // 主持人退出会议（接口未测试）
    void onChairEndConfCallBack(int endTermid, String endName) {
        log.E("主持人退出会议__onChairEndConfCallBack。。。endTermid:" + endTermid + "  endName:" + endName);
        SdkCallBack.getInstance().onChairEndConfCallBack(endTermid, endName);
    }


    /**
     * 设置或者取消焦点视频
     *
     * @param unOrLockId
     * @param isLock
     */
    void onLockOrUnLockVideoCallBack(int unOrLockId, boolean isLock) {
        log.E("设置/取消锁定视频...onLockOrUnLockVideoCallBack.... unOrLockId:" + unOrLockId + "  isLock:" + isLock);
        SdkCallBack.getInstance().onLockOrUnLockVideoCallBack(unOrLockId, isLock);
    }


    /**
     * 其它客户端静音/取消静音回调
     *
     * @param muteterid true为静音 false 为取消静音
     */
    void onTermAudioRecUnOrMuteCallBack(int muteterid, boolean isMute) {
        log.E("其它客户端静音/取消静音回调。。。。.  muteterid:" + muteterid + "  isMute：" + isMute);
        SdkCallBack.getInstance().onTermAudioRecUnOrMuteCallBack(muteterid, isMute);

    }


    /**
     * 主持人身份切换回调(设置主持人)投影项目没有使用
     *
     * @param chair_stermid
     */
    void onMasterTransferCallBack(int chair_stermid) {
        log.E("主持人身份切换回调。。。。.chair_stermid:" + chair_stermid);
        SdkCallBack.getInstance().onMasterTransferCallBack(chair_stermid);
    }


    /**
     * 举手回调
     *
     * @param handupterid
     * @param isHandUp
     */
    void onTermHandUpCallBack(int handupterid, boolean isHandUp) {
        log.E("举手...onTermHandUpCallBack.... handupterid:" + handupterid + "  isHandUp:" + isHandUp);
        SdkCallBack.getInstance().onTermHandUpCallBack(handupterid, isHandUp);
    }

    /**
     * 全部静音或取消全部静音回调
     *
     * @param isMute
     */
    void onMuteAudioAllTermNotifyCallBack(boolean isMute) {
        log.E("onMuteAudioAllTermNotifyCallBack.........isMute:" + isMute);
        SdkCallBack.getInstance().onMuteAudioAllTermNotifyCallBack(isMute);
    }

    /**
     * 收到视频回调(选看视频流)
     *
     * @param open_id
     */
    void onOpenCameraCallBack(int open_id) {
        log.E("onOpenCameraCallBack.........open_id:" + open_id);
        SdkCallBack.getInstance().onOpenCameraCallBack(open_id);
    }


    /**
     * 关闭视频回调（关闭选看视频流）
     *
     * @param close_id
     */
    void onCloseCameraCallBack(int close_id) {
        log.E("onCloseCameraCallBack.........close_id:" + close_id);
        SdkCallBack.getInstance().onCloseCameraCallBack(close_id);
    }

    /**
     * 共享中主持人结束会议
     *
     * @param chair_stermid
     * @param chair_name
     */
    void onIndChairEndDataShareCallBack(int chair_stermid, String chair_name) {
        log.E("onIndChairEndDataShareCallBack.........chair_stermid:" + chair_stermid + "  chair_name:" + chair_name);
        SdkCallBack.getInstance().onIndChairEndDataShareCallBack(chair_stermid, chair_name);
    }

    /**
     * 终端修改名称
     *
     * @param changeterid
     * @param term_name
     */
    void onTermChangeNameCallBack(int changeterid, String term_name) {
        log.E("onTermChangeNameCallBack.........changeterid:" + changeterid + "  term_name:" + term_name);
        SdkCallBack.getInstance().onTermChangeNameCallBack(changeterid, term_name);
    }


    /**
     * 语音激励回调
     *
     * @param voiceActiveInfoList
     */
    void onActiveVoiceCallBack(ArrayList<VoiceActiveInfo> voiceActiveInfoList) {
//        log.E("onActiveVoiceCallBack.........:");
        SdkCallBack.getInstance().onActiveVoiceCallBack(voiceActiveInfoList);
    }

    /**
     * 接收数据统计信息回调
     *
     * @param sendStreamInfoList
     */
    void onSendStreamInfoStatsCallBack(ArrayList<SRSendStreamInfo> sendStreamInfoList) {
//        if (sendStreamInfoList != null)
//            log.E("CallBack。。onSendStreamInfoStatsCallBack.........size:" + sendStreamInfoList.size());
        SdkCallBack.getInstance().onSendStreamInfoStatsCallBack(sendStreamInfoList);
    }

    /**
     * 发送数据统计信息回调
     *
     * @param recvStreamInfoList
     */
    void onRecvStreamInfoStatsCallBack(ArrayList<SRRecvStreamInfo> recvStreamInfoList) {
//        if (recvStreamInfoList != null)
//            log.E("CallBack..onRecvStreamInfoStatsCallBack.........size:" + recvStreamInfoList.size());
        SdkCallBack.getInstance().onRecvStreamInfoStatsCallBack(recvStreamInfoList);
    }


    void onServerErrorCallBack(int errorCode) {
        log.E("onServerErrorCallBack.........:");
        SdkCallBack.getInstance().onServerErrorCallBack(errorCode);
    }

    /**
     * 通知其它客户端状态，自定义结构
     *
     * @param stautsTermid
     * @param staClass
     * @param staSubCls
     * @param staStr
     */
    void SREngineRunningStatusNotifyCallBack(int stautsTermid,
                                             int staClass, int staSubCls, String staStr) {
        SdkCallBack.getInstance().SREngineRunningStatusNotifyCallBack(stautsTermid, staClass, staSubCls, staStr);
    }

    void onConfForceMuteAllTermCallBack(boolean isforcemute) {
        SdkCallBack.getInstance().onConfForceMuteAllTermCallBack(isforcemute);
    }

    void onRspConfInfoStatusCallBack(boolean isok, ConfInfoStatus confInfoStatus, SRError srError) {
        SdkCallBack.getInstance().onRspConfInfoStatusCallBack(isok, confInfoStatus, srError);
    }

    void onIndTerCRSRecStateCallBack(int recordstate, SRError error) {
        SdkCallBack.getInstance().onIndTerCRSRecStateCallBack(recordstate, error);
    }

    void OnAllMPInfoCallBack(ArrayList<SRMediaPInfo> srMediaPInfoList) {
        SdkCallBack.getInstance().onAllMPInfoCallBack(srMediaPInfoList);
    }

    void onMPScreenInfoCallback(int channelid, int screenid, int screentype, int addordel) {
        SdkCallBack.getInstance().onMPScreenInfoCallback(channelid, screenid, screentype, addordel);
    }

    void onUpdateAddPaticipantsCallback(ArrayList<TermInfo> addTermInfoList) {
        SdkCallBack.getInstance().onUpdateAddPaticipantsCallback(addTermInfoList);
    }

    void onUpdateDelPaticipantsCallback(ArrayList<TermInfo> delTermInfoList) {
        SdkCallBack.getInstance().onUpdateDelPaticipantsCallback(delTermInfoList);
    }

    void OnIndTerSpecialtypeTransferCallBack(int nspclterid, int nspcltype) {
        SdkCallBack.getInstance().OnIndTerSpecialtypeTransferCallBack(nspclterid, nspcltype);
    }

    void OnIndTerCRSLiveStateCallBack(int livestate, String liveplayurl,SRError srError) {
        SdkCallBack.getInstance().OnIndTerCRSLiveStateCallBack(livestate,liveplayurl, srError);
    }

    void OnIndLiveSettingChangedCallBack(OnliveInfo info) {
        SdkCallBack.getInstance().OnIndLiveSettingChangedCallBack(info);
    }

    void OnRecvConfMessageCallBack(int termId, String message) {
        SdkCallBack.getInstance().OnRecvConfMessageCallBack(termId,message);
    }

    void onServerOkCallBack(int okCode) {
        SdkCallBack.getInstance().onServerOkCallBack(okCode);
    }
//************new sdk end***********************************************************************************


    void OnStackConnErrorCallBack(int type) {
        SdkCallBack.getInstance().OnStackConnErrorCallBack(type);
    }

    //网络切换回调
    void OnNetwrokNotify(int status) {
        SdkCallBack.getInstance().OnNetwrokNotify(status);
    }

    /**
     * JNI异常
     */
    void getJNIExcaption() {
        SdkCallBack.getInstance().getJNIExcaption();
    }




    //共享内存

    /**
     * 渲染，回传视频
     * @param id
     * @param flag
     * @param format
     * @param width
     * @param height
     * @param length
     */
    void onRenderCallBackCallBack(int id, int flag,int format, int width, int height,int length) {
        SdkCallBack.getInstance().onRenderCallBackCallBack(id, flag, format,null, null, null,
                width, height,length);
    }

}
