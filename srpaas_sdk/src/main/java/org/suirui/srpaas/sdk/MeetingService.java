package org.suirui.srpaas.sdk;

import org.suirui.srpaas.entry.BufData;
import org.suirui.srpaas.entry.InviteInfo;
import org.suirui.srpaas.entry.MeeingListParams;
import org.suirui.srpaas.entry.MeetInfo;
import org.suirui.srpaas.entry.NetWorkStatus;
import org.suirui.srpaas.entry.TermInfo;
import org.suirui.srpaas.http.callback.OnHasPwdCallBack;
import org.suirui.srpaas.http.callback.OnMeetingDetailInfoCallBack;
import org.suirui.srpaas.http.callback.OnMeetingListCallBack;

import java.nio.ByteBuffer;
import java.util.List;

/**
 * 会议相关的接口
 *
 * @author cui.li
 */
public interface MeetingService {

    public void addMeetingServiceListener(MeetingServiceListener listener);

    public void removeMeetingServiceListener(MeetingServiceListener listener);

    /**
     * 获取域名
     *
     * @return
     */
    String getDoMain();

    /**
     * 获取inviteUrl
     *
     * @return
     */
    String getInviteUrl();

    /**
     * 开始会议（立即会议）
     *
     * @return
     */
    public void StartMeeting(MeetInfo meetInfo);


    /**
     * 加入会议(成功后调用投影平台的reportMeet)
     *
     * @return
     */
    public void joinMeeting(MeetInfo meetInfo);

    /**
     * 获取参会人列表
     *
     * @return
     */
    int getRequestTerminalmList();

    /**
     * 退出会议
     *
     * @param eLeave
     */
    public boolean leaveMeetingWithCmd(SRPaas.eLeaveMeetingCmd eLeave, String exitReason);

    /**
     * 函数功能: 选看远端视频 输入参数： mul_stream:选看视频id和窗口 显示视频
     *
     * @param termInfoList
     * @return onRenderCallBackCallBack
     */
    public void requestSelectRemoteVideo(List<TermInfo> termInfoList);

    /**
     * 发送双流(SRPaas.SRVideoStreamType.kSRScreenStream.getValue())
     *
     * @param streamType
     * @param width
     * @param height
     * @param rgb
     */

    public void sendDataStreamRGB(int streamType, int width, int height, int[] rgb);

    /**
     * 发送yuv
     *
     * @param width
     * @param height
     * @param yuv
     */
    public void sendDataStreamYUV(int streamType, int width, int height, byte[] yuv);





    // 开始发送双流
    public int requestStartSendDualVideo();

    // 关闭发送双流
    public int requestStopSendDualVideo();

    /**
     * 函数功能: 打开本地摄像头指示(不需要等ack) 输入参数： conf_id 会议ID term_id 终端id(终端注册时的id) 返回值: 0
     * 成功 非0 失败
     */
    public int openCamera(int unmute_stermid);

    /**
     * 函数功能: 关闭本地摄像头指示(不需要等ack) 输入参数： conf_id 会议ID term_id 终端id(终端注册时的id) 返回值: 0
     * 成功 非0 失败
     */
    public int closeCamera(int mute_stermid);

    /**
     * 回复桌面共享申请
     *
     * @param avterid      申请共享Id
     * @param isok         是否同意
     * @param rejectreason 同意传空，拒绝传理由
     * @return
     */
    public int resposeSendDualVideoProxy(int avterid,
                                         boolean isok, String rejectreason);


    /**
     * mode: 0:听筒模式 1:外音模式
     *
     * @param mode
     */
    public void setSpeakerMode(int mode);

    /**
     * 设置终端状态
     *
     * @param sta_class
     * @param sta_sub_class
     * @param status_str
     */
    public void setRunningStatusNotify(int sta_class,
                                       int sta_sub_class, String status_str);


    /**
     * 会中有共享，主持人可结束
     */
    void chairEndDataShare();

    /**
     * 发送视频
     *
     * @param streamType
     * @param data
     * @param width
     * @param height
     * @param rotation
     * @param isMirror
     */
    void sendDataStreamVideo(int streamType, byte[] data, int width, int height, int rotation, boolean isMirror, int size);

    /**
     * 切换网络
     */
    void onNetworkChanged();

    /**
     * 设置APM认证key
     *
     * @param key
     */
    void setApmKeyContent(String key);

    /**
     * 获取apm认证mac信息
     */
    String getApmInfo();

    /**
     * 获取会议信息
     */
    void getConfInfoState();

    /**
     * 获取当前的suid
     *
     * @return
     */
    int getSuid();

    /**
     * 会议邀请
     *
     * @param inviteInfo
     * @return
     */
    void meetingInvite(InviteInfo inviteInfo);

    /**
     * 获取会议列表
     * @param meetListingParams
     * @param callBack
     */
    void getMeetingList(MeeingListParams meetListingParams, OnMeetingListCallBack callBack);
    /**
     * 获取会议是否与密码
     * @param token
     * @param confId
     */
    void getMeetingPwd(String token, String confId, OnHasPwdCallBack onHasPwdCallBack);

    /**
     * 获取会议详情
     * @param appId
     * @param secretKey
     * @param token
     * @param confId
     * @param onMeetingDetailInfoCallBack
     */
    void getMeetingInfo(String appId,String secretKey,String token,String confId ,OnMeetingDetailInfoCallBack onMeetingDetailInfoCallBack );


    /**
     * 获取当前的网络状态
     *
     * @return
     */
    NetWorkStatus getNetWorkState();

    //共享内存

    /**
     * 设置 y u v 内存
     * @param bufData
     */
    void setReceiveByteBufferData(BufData bufData);

    /**
     * 发送采集的数据
     * @param streamType
     * @param data
     * @param width
     * @param height
     * @param rotation
     * @param isMirror
     * @param size
     */
    void sendDataStreamVideoBuf(int streamType,ByteBuffer data, int width, int height, int rotation, boolean isMirror, int size) ;
    /**
     * 发送采集的数据
     * @param streamType
     * @param data
     * @param dataType 视频格式
     * @param width
     * @param height
     */
    void sendDataStreamVideoBufType(int streamType, int dataType, ByteBuffer data, int width, int height, int rotation, boolean isMirror, int size) ;

}
