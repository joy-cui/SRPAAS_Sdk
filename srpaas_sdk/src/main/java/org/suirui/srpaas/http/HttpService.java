package org.suirui.srpaas.http;

import org.suirui.srpaas.entry.AuthInfo;
import org.suirui.srpaas.entry.InviteInfo;
import org.suirui.srpaas.entry.MeeingListParams;
import org.suirui.srpaas.entry.MeetInfo;
import org.suirui.srpaas.http.callback.InviteCallBack;
import org.suirui.srpaas.http.callback.LoginCallBack;
import org.suirui.srpaas.http.callback.OnHasPwdCallBack;
import org.suirui.srpaas.http.callback.OnMeetingDetailInfoCallBack;
import org.suirui.srpaas.http.callback.OnMeetingListCallBack;
import org.suirui.srpaas.http.callback.RegisterCallBack;
import org.suirui.srpaas.http.callback.StartOrJoinMeetCallBack;
import org.suirui.srpaas.http.callback.UpdateUserCallBack;

/**
 * 平台接口
 *
 * @author cui.li
 */
public interface HttpService {


    /**
     * 创建会议(开始会议)
     */
    void startMeeting(MeetInfo meetInfo, StartOrJoinMeetCallBack callback);

    /**
     * 加入会议
     *
     * @param meetInfo
     * @return
     */
    void joinMeeting(MeetInfo meetInfo, StartOrJoinMeetCallBack callback);


    /**
     * 登录
     *
     * @param info
     * @return
     */
    void login(AuthInfo info, LoginCallBack callBack);

    /**
     * 注册
     *
     * @param info
     * @param callBack
     */
    void Register(AuthInfo info, RegisterCallBack callBack);

    /**
     * 更新用户信息
     */

    void updateUser(AuthInfo info,LoginCallBack callBack);

    /**
     * 邀请
     *
     * @param inviteInfo
     * @param inviteCallBack
     */
    void meetingInvite(InviteInfo inviteInfo, InviteCallBack inviteCallBack);

    /**
     * 获取会议列表接口
     * @param meeingListParams
     * @param meetingCallBack
     */
    void getMeetingList(MeeingListParams meeingListParams, OnMeetingListCallBack meetingCallBack);

    /**
     * 获取会议是否与密码
     * @param token
     * @param confId 对应的subject
     */
    void getMeetingPwd(String token, String confId, OnHasPwdCallBack onHasPwdCallBack);

    void getMeetingInfo(String appId,String secretKey,String token,String confId ,OnMeetingDetailInfoCallBack onMeetingDetailInfoCallBack );


}
