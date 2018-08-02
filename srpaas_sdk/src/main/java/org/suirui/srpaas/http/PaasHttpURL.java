package org.suirui.srpaas.http;

/**
 * @author cui.li
 */
public interface PaasHttpURL {

    // public static final String url_root = "http://api.suirui.com/v1";
    public static int http_overtime = 5000;// http请求超时
    // 192.168.62.37


    public static final String url_start_meeting = "/conference/startmeeting";
    public static final String url_join_meeting = "/conference/joinmeeting";// 加入会议
    public static final String url_user_login = "/user/login";//登录//
    public static final String url_user_register = "/user/register";//注册
    public static final String url_user_update = "/user/update";
    public static final String url_terminal_register = "/terminal/register";//ubox终端
    public static final String url_user_invite = "/conference/inviteOnline";//邀请上线
    public static final String url_meetinglist_url="/conference/list";//获取会议列表
    public static final String HASPWD_url="/conference/haspwd";//是否有密码
    public static final String getMeetDetail_url="/conference/get";//获取会议详情

}
