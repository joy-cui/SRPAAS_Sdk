package org.suirui.srpaas.http;


import com.suirui.srpaas.base.util.log.SRLog;
import com.suirui.srpaas.common.http.okhttp.OkHttpUtils;
import com.suirui.srpaas.common.http.okhttp.callback.GenericsCallback;
import com.suirui.srpaas.common.http.okhttp.callback.JsonGenericsSerializator;

import org.suirui.srpaas.contant.SRPaaSdkConfigure;
import org.suirui.srpaas.contant.UserType;
import org.suirui.srpaas.entry.AuthInfo;
import org.suirui.srpaas.entry.ConferenceInfo;
import org.suirui.srpaas.entry.InviteInfo;
import org.suirui.srpaas.entry.MeeingListParams;
import org.suirui.srpaas.entry.MeetDetailInfo;
import org.suirui.srpaas.entry.MeetInfo;
import org.suirui.srpaas.entry.MeetingInfo;
import org.suirui.srpaas.entry.MeetingOptions;
import org.suirui.srpaas.entry.SpaasInfo;
import org.suirui.srpaas.entry.UserInfo;
import org.suirui.srpaas.http.bean.HasPwdBean;
import org.suirui.srpaas.http.bean.InviteBean;
import org.suirui.srpaas.http.bean.LoginBean;
import org.suirui.srpaas.http.bean.MeetDetailInfoBean;
import org.suirui.srpaas.http.bean.MeetingBean;
import org.suirui.srpaas.http.bean.MeetingListBean;
import org.suirui.srpaas.http.bean.RegisterBean;
import org.suirui.srpaas.http.callback.InviteCallBack;
import org.suirui.srpaas.http.callback.LoginCallBack;
import org.suirui.srpaas.http.callback.OnHasPwdCallBack;
import org.suirui.srpaas.http.callback.OnMeetingDetailInfoCallBack;
import org.suirui.srpaas.http.callback.OnMeetingListCallBack;
import org.suirui.srpaas.http.callback.RegisterCallBack;
import org.suirui.srpaas.http.callback.StartOrJoinMeetCallBack;
import org.suirui.srpaas.sdk.SRPaas;
import org.suirui.srpaas.sdk.SRPaasSDK;
import org.suirui.srpaas.util.MD5;
import org.suirui.srpaas.util.StringUtil;

import java.util.HashMap;
import java.util.List;

import okhttp3.Call;

import static com.suirui.srpaas.common.http.okhttp.OkHttpUtils.post;

/**
 * pass平台服务器端接口
 *
 * @author cui.li
 */
public class HttpServiceImpl implements HttpService, PaasHttpURL {
    private static final SRLog log = new SRLog(HttpServiceImpl.class.getSimpleName());
    private static HttpServiceImpl instance = null;
    private final int COUNT = 3;
    /**
     * 开始会议
     */
    int startCount = 0;
    /**
     * 加入会议
     */
    int joinConut = 0;
    private MeetingInfo cancelMeetInfo = null;


    private HttpServiceImpl() {
        cancelMeetInfo = null;
//        HttpsUtils.SSLParams sslParams = HttpsUtils.getSslSocketFactory(null, null, null);
//        int cacheSize = 10 * 1024 * 1024; // 10 MiB
//        Cache cache = new Cache(App.getContext().getCacheDir(), cacheSize);
//        builder.cache(cache);
//        OkHttpClient okHttpClient = new OkHttpClient.Builder().connectTimeout(10000L, TimeUnit.MILLISECONDS).readTimeout(10000L, TimeUnit.MILLISECONDS).addInterceptor(new LoggerInterceptor("TAG"))
////                .cache(cache)
//                .hostnameVerifier(new HostnameVerifier() {
//                    @Override
//                    public boolean verify(String hostname, SSLSession session) {
//                        return true;
//                    }
//                }).sslSocketFactory(sslParams.sSLSocketFactory, sslParams.trustManager).build();
//
//
//        OkHttpUtils.initClient(okHttpClient);

    }

    public static synchronized HttpServiceImpl getInstance() {
        if (instance == null) {
            instance = new HttpServiceImpl();
        }
        return instance;
    }

    @Override
    public void startMeeting(final MeetInfo meetInfo, final StartOrJoinMeetCallBack callback) {
        if (meetInfo == null) return;
        String confid = meetInfo.getM_confId();
        String pwd = meetInfo.getM_confPwd();
        String m_livePwd = meetInfo.getM_livePwd();
        String subject = meetInfo.getM_subject();
        String startTime = meetInfo.getM_startTime();
        String endTime = meetInfo.getM_endTime();
        String thirdAudioId = meetInfo.getThirdAudioId();
        String thirdAudioVersion = meetInfo.getThirdAudioVersion();
        String nickName = meetInfo.getNickName();
        MeetingOptions option = meetInfo.getM_options();
        String confType = "";
        String startType = "";
        if (option != null) {
            confType = option.getM_confType();
            startType = option.getM_startType();
        }
        String token = meetInfo.getToken();
        String audioenable = meetInfo.getAudioenable();
        String videoenable = meetInfo.getVideoenable();
        HashMap<String, String> paramsMap = new HashMap<String, String>();
        setMapBaseEntry(paramsMap, nickName);
        setMeetMap(paramsMap, confid, subject, pwd, m_livePwd, thirdAudioId, thirdAudioVersion);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetingInfo.m_startTime, startTime);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetingInfo.m_endTime, endTime);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetingInfo.m_confType, confType);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetingInfo.m_startType, startType);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetingInfo.m_token, token);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetingInfo.m_audioenable, audioenable);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetingInfo.m_videoenable, videoenable);
        log.E("startMeeting confid:" + confid + "  subject:" + subject + "  url_start_meeting: " + SRPaasSDK.getInstance().getPassUrl() + url_start_meeting + "  token:" + token + "  audioenable:" + audioenable + "  videoenable:" + videoenable);
        String domain = SRPaasSDK.getInstance().getPassUrl();
        if (StringUtil.isEmptyOrNull(domain)) {
            callback.onError(100, HttpUtil.HttpError.http_meet_error);
            return;
        }
        try {
            OkHttpUtils.post().url(domain + url_start_meeting).params(paramsMap).build().execute(new GenericsCallback<MeetingBean>(new JsonGenericsSerializator()) {
                @Override
                public void onError(Call call, Exception e, int i) {
//                    startCount++;
//                    log.E("HttpServiceImpl...startMeetingThird...onError:" + e.toString() + " i:" + i + " startCount:" + startCount);
//                    if (startCount < 3) {
//                        startMeeting(meetInfo, callback);
//                    } else {
//                        callback.onError(-1, HttpUtil.HttpError.http_server_error);
//                        callback.onError(call, e, i);
//                        startCount = 0;
//                    }
//                    callback.onError(-1, HttpUtil.HttpError.http_server_error);
                    callback.onError(call, e, i);
                }

                @Override
                public void onResponse(final MeetingBean jsonBean, int id) {
                    log.E("HttpServiceImpl: " + jsonBean.toString());
                    onSuccess(jsonBean, callback);
                }
            });

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void joinMeeting(final MeetInfo meetInfo, final StartOrJoinMeetCallBack callback) {
        if (meetInfo == null) return;

        String confid = meetInfo.getM_confId();
        String pwd = meetInfo.getM_confPwd();
        String m_livePwd = meetInfo.getM_livePwd();
        String thirdAudioId = meetInfo.getThirdAudioId();
        String thirdAudioVersion = meetInfo.getThirdAudioVersion();
        String nickName = meetInfo.getNickName();
        String subject = meetInfo.getM_subject();
        String token = meetInfo.getToken();
        HashMap<String, String> paramsMap = new HashMap<String, String>();
        setMapBaseEntry(paramsMap, nickName);
        setMeetMap(paramsMap, confid, subject, pwd, m_livePwd, thirdAudioId, thirdAudioVersion);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetingInfo.m_token, token);
        log.E("joinMeeting confid:" + confid + "  subject:" + subject + "  url_join_meeting: " + SRPaasSDK.getInstance().getPassUrl() + url_join_meeting + "  token:" + token);
        String domain = SRPaasSDK.getInstance().getPassUrl();
        if (StringUtil.isEmptyOrNull(domain)) {
            callback.onError(100, HttpUtil.HttpError.http_meet_error);
            return;
        }
        try {
            post().url(SRPaasSDK.getInstance().getPassUrl() + url_join_meeting).params(paramsMap).build().execute(new GenericsCallback<MeetingBean>(new JsonGenericsSerializator()) {
                @Override
                public void onError(Call call, Exception e, int i) {
                    log.E("HttpServiceImpl...joinMeetingThird...onError:" + e.toString() + " i:" + i);


//                    joinConut++;
//                    log.E("HttpServiceImpl...startMeetingThird...onError:" + e.toString() + " i:" + i + " startCount:" + startCount);
//                    if (joinConut < 3) {
//                        joinMeeting(meetInfo, callback);
//                    } else {
//                        callback.onError(-1, HttpUtil.HttpError.http_server_error);
//                        callback.onError(call, e, i);
//                        joinConut = 0;
//                    }
                    if (cancelMeetInfo != null && cancelMeetInfo.getM_subject() == meetInfo.getM_subject()) {
                        callback.onStartOrJoinMeetSuccess(cancelMeetInfo);
                    } else {
                        callback.onError(-1, HttpUtil.HttpError.http_server_error);
                        callback.onError(call, e, i);
                    }

                }

                @Override
                public void onResponse(final MeetingBean jsonBean, int id) {
                    log.E("HttpServiceImpl: " + jsonBean.toString());
                    onSuccess(jsonBean, callback);

                }
            });

        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    @Override
    public void login(AuthInfo info, final LoginCallBack callback) {
        if (info == null) {
            return;
        }
        String account = info.getAccount();
        String pwd = MD5.getMD5Str(info.getPwd());
        String appid = info.getAppid();
        String secretKey = info.getSecretKey();
        String type = info.getType();
        String uuid = info.getUuid();
        String macAddr = info.getMacAddr();
        String cpuNo = info.getCpuNo();
        String diskNo = info.getDiskNo();
        HashMap<String, String> paramsMap = new HashMap<String, String>();

        if(!StringUtil.isEmptyOrNull(type) && StringUtil.isSameString(type,""+UserType.USER_NEW_UBOX)){
            setKeyValue(paramsMap, "appId", appid);
            setKeyValue(paramsMap, "secretKey", secretKey);
            setKeyValue(paramsMap, "type", type);
            setKeyValue(paramsMap, "option.cpuNo", cpuNo);
            setKeyValue(paramsMap, "option.diskNo", diskNo);
            setKeyValue(paramsMap, "option.macAddr", macAddr);
            setKeyValue(paramsMap, "option.uuid", uuid);
        }else {
            setKeyValue(paramsMap, SRPaaSdkConfigure.AccountInfo.m_login_account, account);
            setKeyValue(paramsMap, SRPaaSdkConfigure.AccountInfo.m_pwd, pwd);
            setKeyValue(paramsMap, SRPaaSdkConfigure.AccountInfo.m_appid, appid);
            setKeyValue(paramsMap, SRPaaSdkConfigure.AccountInfo.m_type, type);
        }

        log.E("login....account:" + account + "  pwd:" + pwd + "  appid:" + appid + " type:" + type + " url:" + SRPaasSDK.getInstance().getPassUrl() + url_user_login);
        try {
            OkHttpUtils.post().url(SRPaasSDK.getInstance().getPassUrl() + url_user_login).params(paramsMap).build().execute(new GenericsCallback<LoginBean>(new JsonGenericsSerializator()) {
                @Override
                public void onError(Call call, Exception e, int i) {
                    log.E("HttpServiceImpl...login...onError:" + e.toString() + " i:" + i);
                    callback.onError(call, e, i);
                }

                @Override
                public void onResponse(LoginBean loginBean, int i) {
                    log.E("HttpServiceImpl...login...onResponse:" + loginBean.toString());
                    onSuccess(loginBean, callback);
                }
            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void Register(AuthInfo info, final RegisterCallBack callback) {
        if (info == null)
            return;
        String phone = info.getPhone();
        String appid = info.getAppid();
        String secretKey = info.getSecretKey();
        String nikename = info.getNickname();
        String pwd = MD5.getMD5Str(info.getPwd());//密码必须用MD5加密
        int useIM = info.getUseIM();

        String type = info.getType();
        String uuid = info.getUuid();
        String macAddr = info.getMacAddr();
        String cpuNo = info.getCpuNo();
        String diskNo = info.getDiskNo();
        String url = "";
        log.E("Register....phone:" + phone + "    pwd:" + info.getPwd() + "  appid:" + appid + "  nikename:" + nikename + "  useIM:" + useIM);
        HashMap<String, String> paramsMap = new HashMap<String, String>();

        if(!StringUtil.isEmptyOrNull(type) && StringUtil.isSameString(type, ""+UserType.USER_NEW_UBOX)){
            url = url_terminal_register;
            setKeyValue(paramsMap, "appId", appid);
            setKeyValue(paramsMap, "secretKey", secretKey);
            setKeyValue(paramsMap, "cpuNo", cpuNo);
            setKeyValue(paramsMap, "diskNo", diskNo);
            setKeyValue(paramsMap, "macAddr", macAddr);
            setKeyValue(paramsMap, "uuid", uuid);
            setKeyValue(paramsMap, "nickName", nikename);
        }else {
            url = url_user_register;
            setKeyValue(paramsMap, SRPaaSdkConfigure.AccountInfo.m_register_phone, phone);
            setKeyValue(paramsMap, SRPaaSdkConfigure.AccountInfo.m_appid, appid);
            setKeyValue(paramsMap, SRPaaSdkConfigure.AccountInfo.m_register_nikename, nikename);
            setKeyValue(paramsMap, SRPaaSdkConfigure.AccountInfo.m_pwd, pwd);
            setKeyValue(paramsMap, SRPaaSdkConfigure.AccountInfo.m_register_useim, String.valueOf(useIM));
        }

        try {
            OkHttpUtils.post().url(SRPaasSDK.getInstance().getPassUrl() + url).params(paramsMap).build().execute(new GenericsCallback<RegisterBean>(new JsonGenericsSerializator()) {
                @Override
                public void onError(Call call, Exception e, int i) {
//                    log.E("HttpServiceImpl...login...onError:" + e.toString() + " i:" + i);
                    callback.onError(call, e, i);
                }

                @Override
                public void onResponse(RegisterBean bean, int i) {
                    onSuccess(bean, callback);
                }
            });

        }catch (IllegalArgumentException e){
            callback.onError(SRPaas.eRegisterError.eRegisterError_Url.ordinal(),HttpUtil.HttpError.http_server_error);
        } catch (Exception e) {
            log.E("HttpServiceImpl...register...onError:" + e.getMessage());
            callback.onError(SRPaas.eRegisterError.eRegisterError_UNknow.ordinal(),e.getMessage());
            e.printStackTrace();
        }

    }

    @Override
    public void updateUser(AuthInfo info,final LoginCallBack callback){
        if (info == null)
            return;
        String phone = info.getPhone();
        String appid = info.getAppid();
        String secretKey = info.getSecretKey();
        String nikename = info.getNickname();
        String token = info.getToken();
        String type = info.getType();
        log.E("HttpServiceImpl...login...authinfo::" + info.getAuthInfoString());
        String url = "";
        HashMap<String, String> paramsMap = new HashMap<String, String>();

        if(!StringUtil.isEmptyOrNull(type) && StringUtil.isSameString(type, ""+UserType.USER_NEW_UBOX)){
            url = url_user_update;
            log.E("HttpServiceImpl...login...authinfo::"+SRPaasSDK.getInstance().getPassUrl() + url+"  :" + info.getAuthInfoString());
            setKeyValue(paramsMap, "appId", appid);
            setKeyValue(paramsMap, "secretKey", secretKey);
            setKeyValue(paramsMap, "token", token);
            setKeyValue(paramsMap, "nickname", nikename);
        }else {

        }

        try {
            OkHttpUtils.post().url(SRPaasSDK.getInstance().getPassUrl() + url).params(paramsMap).build().execute(new GenericsCallback<LoginBean>(new JsonGenericsSerializator()) {
                @Override
                public void onError(Call call, Exception e, int i) {
//                    log.E("HttpServiceImpl...login...onError:" + e.toString() + " i:" + i);
                    callback.onError(call, e, i);
                }

                @Override
                public void onResponse(LoginBean bean, int i) {
                    onSuccess(bean, callback);
                }
            });

        }catch (IllegalArgumentException e){
            callback.onError(SRPaas.eRegisterError.eRegisterError_Url.ordinal(),HttpUtil.HttpError.http_server_error);
        } catch (Exception e) {
            log.E("HttpServiceImpl...register...onError:" + e.getMessage());
            callback.onError(SRPaas.eRegisterError.eRegisterError_UNknow.ordinal(),e.getMessage());
            e.printStackTrace();
        }
    }

    @Override
    public void meetingInvite(InviteInfo inviteInfo, final InviteCallBack callback) {
        if (inviteInfo == null) return;
        String token = inviteInfo.getToken();
        String secretKey = inviteInfo.getSecretKey();
        String participants = inviteInfo.getParticipants();
        int termId = inviteInfo.getTermId();
        String termName = inviteInfo.getTermName();
        String msgType = inviteInfo.getMsgType();
        String confId = inviteInfo.getConfId();
        String rooms = inviteInfo.getRooms();
        String callOption = inviteInfo.getCallOption();
        HashMap<String, String> paramsMap = new HashMap<String, String>();
        SpaasInfo spaasInfo = SRPaasSDK.getInstance().getSpaasInfo();
        if (spaasInfo != null) {
            log.E("meetingInvite....appid:" + spaasInfo.getAppId());
            setKeyValue(paramsMap, SRPaaSdkConfigure.Invite.appId, spaasInfo.getAppId());
            spaasInfo = null;
        }
        setKeyValue(paramsMap, SRPaaSdkConfigure.Invite.confId, confId);
        setKeyValue(paramsMap, SRPaaSdkConfigure.Invite.participants, participants);
        setKeyValue(paramsMap, SRPaaSdkConfigure.Invite.msgType, msgType);
        setKeyValue(paramsMap, SRPaaSdkConfigure.Invite.terid, String.valueOf(termId));
        setKeyValue(paramsMap, SRPaaSdkConfigure.Invite.terName, termName);
        setKeyValue(paramsMap, SRPaaSdkConfigure.Invite.rooms, rooms);
        setKeyValue(paramsMap, SRPaaSdkConfigure.Invite.secretKey, secretKey);
        setKeyValue(paramsMap, SRPaaSdkConfigure.Invite.token, token);
        setKeyValue(paramsMap, SRPaaSdkConfigure.Invite.callOption, callOption);
        log.E("meetingInvite...confId:" + confId + " participants:" + participants + " msgType:" + msgType + " termId:" + termId + " termName:" + termName + " token:" + token + "callOption:" + callOption);
        try {
            OkHttpUtils.post().url(SRPaasSDK.getInstance().getPassUrl() + url_user_invite).params(paramsMap).build().execute(new GenericsCallback<InviteBean>(new JsonGenericsSerializator()) {
                @Override
                public void onError(Call call, Exception e, int i) {
                    callback.onError(call, e, i);
                }

                @Override
                public void onResponse(InviteBean bean, int i) {
                    onSuccess(bean, callback);
                }
            });

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 获取会议列表
     * @param meeingListParams
     * @param meetingListCallBack
     */
    @Override
    public void getMeetingList(MeeingListParams meeingListParams, final OnMeetingListCallBack meetingListCallBack) {
        if (meeingListParams == null)
            return;
        String appid = meeingListParams.getAppId();
        String secretKey = meeingListParams.getSecretKey();
        String token=meeingListParams.getToken();
        String timeTamp=meeingListParams.getTimestamp();
        int start=meeingListParams.getStart();
        int number=meeingListParams.getNumber();


        HashMap<String, String> paramsMap = new HashMap<String, String>();
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetListingParams.m_appId, appid);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetListingParams.m_secretKey, secretKey);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetListingParams.m_token, token);
        setKeyValue(paramsMap,SRPaaSdkConfigure.MeetListingParams.m_timestamp,timeTamp);
        if(start>0) {
            setKeyValue(paramsMap, SRPaaSdkConfigure.MeetListingParams.m_start, String.valueOf(start));
        }
        if(number>0) {
            setKeyValue(paramsMap, SRPaaSdkConfigure.MeetListingParams.m_itemNumPerPage, String.valueOf(number));
        }
//        log.E("getMeetingList.... url: "+SRPaasSDK.getInstance().getPassUrl() + url_meetinglist_url+"?appId="+paramsMap.get(SRPaaSdkConfigure.MeetListingParams.m_appId)+"&secretKey="+paramsMap.get(SRPaaSdkConfigure.MeetListingParams.m_secretKey)+"&token="+paramsMap.get(SRPaaSdkConfigure.MeetListingParams.m_token)+"&itemNumPerPage="+paramsMap.get("itemNumPerPage"));
        try {

            OkHttpUtils.post().url(SRPaasSDK.getInstance().getPassUrl() + url_meetinglist_url).params(paramsMap).build().execute(new GenericsCallback<MeetingListBean>(new JsonGenericsSerializator()) {
                @Override
                public void onError(Call call, Exception e, int i) {
                    log.E(e.getMessage());
                    meetingListCallBack.onError(i,e.getMessage());
                }

                @Override
                public void onResponse(MeetingListBean bean, int i) {
                    if(bean==null){
                        meetingListCallBack.onError(-1,HttpUtil.HttpError.http_server_error);
                    }else {
//                        log.E("code :"+bean.code+" token: "+bean.token+" isCode: "+bean.code.equals(HttpUtil.HTTP_SUCCESS_CODE));
                        if (bean.code.equals(HttpUtil.HTTP_SUCCESS_CODE) ) {
                            List<ConferenceInfo > conferenceInfoList=HttpUtil.setMeetingList(bean);
                            meetingListCallBack.onSuccess(conferenceInfoList);
                        } else {
                            meetingListCallBack.onError(Integer.valueOf(bean.code),HttpUtil.HttpError.http_get_meetinglist_error);
                        }
                    }
                }
            });

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void getMeetingPwd(String token, String confId, final OnHasPwdCallBack onHasPwdCallBack) {

        HashMap<String, String> paramsMap = new HashMap<String, String>();
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetListingParams.m_token, token);
        setKeyValue(paramsMap, SRPaaSdkConfigure.Invite.SUBJECT, confId);

        try {

//            log.E(SRPaasSDK.getInstance().getPassUrl() + HASPWD_url+"?token="+paramsMap.get(SRPaaSdkConfigure.MeetListingParams.m_token)+"&subject="+paramsMap.get(SRPaaSdkConfigure.Invite.SUBJECT));
            OkHttpUtils.post().url(SRPaasSDK.getInstance().getPassUrl() + HASPWD_url).params(paramsMap).build().execute(new GenericsCallback<HasPwdBean>(new JsonGenericsSerializator()) {

                @Override
                public void onError(Call call, Exception e, int i) {
                    log.E(e.getMessage());
                    if(onHasPwdCallBack!=null) {
                        onHasPwdCallBack.onError(i, e.getMessage());
                    }
                }

                @Override
                public void onResponse(HasPwdBean hasPwdBean, int i) {
                    if(hasPwdBean==null ){
                        onHasPwdCallBack.onError(i, HttpUtil.HttpError.http_server_error);
                        return;
                    }
                    if(onHasPwdCallBack!=null){
                        if( hasPwdBean.code.equals(HttpUtil.HTTP_SUCCESS_CODE)){
                            boolean isHasPwd=false;
                            if(Integer.valueOf(hasPwdBean.hasPwd)==1){
                                isHasPwd=true;
                            }
                            onHasPwdCallBack.onSuccess(hasPwdBean.confId,isHasPwd);
                        }else{
                            onHasPwdCallBack.onError(Integer.valueOf(hasPwdBean.code),"");
                        }

                    }

                }
            });

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void getMeetingInfo(String appId, String secretKey, String token, String confId, final OnMeetingDetailInfoCallBack onMeetingDetailInfoCallBack) {
        HashMap<String, String> paramsMap = new HashMap<String, String>();
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetListingParams.m_appId, appId);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetListingParams.m_secretKey, secretKey);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetListingParams.m_token, token);
        setKeyValue(paramsMap,SRPaaSdkConfigure.MeetDetailInfo.confId,confId);

        try {

            log.E(SRPaasSDK.getInstance().getPassUrl() + getMeetDetail_url+"?token="+paramsMap.get(SRPaaSdkConfigure.MeetListingParams.m_token)+"&confId="+paramsMap.get(SRPaaSdkConfigure.MeetDetailInfo.confId)+"&appId="+paramsMap.get(SRPaaSdkConfigure.MeetListingParams.m_appId)+"&secretKey="+paramsMap.get(SRPaaSdkConfigure.MeetListingParams.m_secretKey));
            OkHttpUtils.post().url(SRPaasSDK.getInstance().getPassUrl() + getMeetDetail_url).params(paramsMap).build().execute(new GenericsCallback<MeetDetailInfoBean>(new JsonGenericsSerializator()) {

                @Override
                public void onError(Call call, Exception e, int i) {
                    log.E(e.getMessage());
                    if(onMeetingDetailInfoCallBack!=null) {
                        onMeetingDetailInfoCallBack.onError(i, e.getMessage());
                    }
                }

                @Override
                public void onResponse(MeetDetailInfoBean meetDetailInfoBean, int i) {
                    if(meetDetailInfoBean==null ){
                        onMeetingDetailInfoCallBack.onError(i, HttpUtil.HttpError.http_server_error);
                        return;
                    }
//                    log.E("onResponse: "+meetDetailInfoBean.toString()+" : "+meetDetailInfoBean.data.toString());
                    MeetDetailInfo meetDetailInfo=HttpUtil.setMeetDetailInfo(meetDetailInfoBean);
                    onMeetingDetailInfoCallBack.onSuccess(meetDetailInfo);
                }


            });

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void onSuccess(InviteBean bean, InviteCallBack callback) {
        try {
            if (bean == null) {
                callback.onError(100, HttpUtil.HttpError.http_invite_error);
            } else {
                String code = bean.code;
                log.E("meetingInvite.....onSuccess....code:" + code);
                if (code != null) {
                    if (!code.equals("200")) {
                        callback.onError(Integer.valueOf(code), HttpUtil.HttpError.http_invite_error);
                    } else {
                        callback.onInviteSuccess();
                    }
                }
            }
        } catch (NumberFormatException e) {
            callback.onError(0, HttpUtil.HttpError.http_server_field_error);
            e.printStackTrace();
        }
    }

    private void onSuccess(RegisterBean registerBean, RegisterCallBack callback) {
//        log.E("HttpServiceImpl...RegisterBean:" + registerBean);
        try {
            if (registerBean == null) {
                callback.onError(100, HttpUtil.HttpError.http_register_error);
            } else {
                String code = registerBean.code;
                if (code != null && !code.equals("200")) {
                    callback.onError(Integer.valueOf(code), HttpUtil.HttpError.http_no_register_error);
                } else {
                    if (registerBean.data == null) {
                        callback.onError(100, HttpUtil.HttpError.http_register_error);
                    } else {
                        UserInfo info  = getRegisterInfo(registerBean);
                        callback.onRegisterSuccess(info);
                    }
                }
            }
        } catch (NumberFormatException e) {
            callback.onError(0, HttpUtil.HttpError.http_server_field_error);
            e.printStackTrace();
        }
    }

    private UserInfo getRegisterInfo(RegisterBean registerBean) {
        UserInfo info = new UserInfo();
        if (registerBean != null) {
            info.setNickname(registerBean.data.nickName);
            info.setSuid(registerBean.data.suid);
        }
        log.E("HttpServiceImpl....getRegisterInfo()....suid:" + info.toString());
        return info;
    }


    private void onSuccess(LoginBean loginBean, LoginCallBack callback) {
        try {
            if (loginBean == null) {
                callback.onError(100, HttpUtil.HttpError.http_login_error);
            } else {
                String code = loginBean.code;
                if (code != null) {
                    if (code.equals("200")) {
                        if (loginBean.data != null) {
                            UserInfo userInfo = getLoginInfo(loginBean);
                            callback.onLoginSuccess(userInfo);
                        } else {
                            callback.onError(100, HttpUtil.HttpError.http_login_error);
                        }
                    } else {
                        callback.onError(Integer.valueOf(code), HttpUtil.HttpError.http_no_login_error);
                    }
                } else {
                    callback.onError(100, HttpUtil.HttpError.http_login_error);
                }
            }
        } catch (NumberFormatException e) {
            callback.onError(0, HttpUtil.HttpError.http_server_field_error);
            e.printStackTrace();
        }
    }

    private UserInfo getLoginInfo(LoginBean loginBean) {
        UserInfo userInfo = null;
        if (loginBean != null) {
            userInfo = new UserInfo();
            String suid = loginBean.data.suid;
            String email = loginBean.data.email;
            String phone = loginBean.data.phone;
            String nickname = loginBean.data.nickname;
            String token = loginBean.data.token;
            String timestamp = loginBean.data.timestamp;
            log.E("HttpServiceImpl....getLoginInfo()....suid:" + suid
                    + " email:" + email + "  phone:" + phone
                    + "  nickname:" + nickname + "  token:" + token
                    + " timestamp:" + timestamp);
            if (suid != null) userInfo.setSuid(suid);
            if (email != null) userInfo.setEmail(email);
            if (phone != null) userInfo.setPhone(phone);
            if (nickname != null) userInfo.setNickname(nickname);
            if (token != null) userInfo.setToken(token);
            if (timestamp != null) userInfo.setTimestamp(timestamp);
        }
        return userInfo;
    }


    //
//        "timestamp":"2017-04-06 09:58:13",
//            "paasUid":"19910326",
//            "paasToken":"beb7da4ced7c42a085c3c99697f9aa42-1491445693003",
//            "code":"200",
//            "conference":{
//        "startTime":"",
//                "hasStarted":"0",
//                "confId":"38058379646",
//                "confStartType":"3",
//                "subject":"38058379646",
//                "relayServer":[],
//        "TAK":"S0S5-32CF-E2E0-C0EB-0EFE-C9F3",
//                "endTime":"",
//                "relaymcAddr":[
//        "103.249.255.252:4000",
//                "103.249.255.252:4001"
//        ],
//        "mcAddr":"4395805749356277818",
//                "confType":"1"
//    }
    private void onSuccess(MeetingBean jsonBean, StartOrJoinMeetCallBack callback) {
        try {
            if (jsonBean == null) {
                callback.onError(100, HttpUtil.HttpError.http_meet_error);
            } else {
                String code = jsonBean.code;
                if (code != null && !code.equals("200")) {
                    callback.onError(Integer.valueOf(code), HttpUtil.HttpError.http_no_meet_error);
                } else {
                    if (jsonBean.conference == null) {
                        callback.onError(100, HttpUtil.HttpError.http_meet_error);
                    } else {
                        MeetingInfo meetInfo = getMeetingInfo(jsonBean);
                        if (meetInfo != null) {
                            cancelMeetInfo = meetInfo;
                        }
                        callback.onStartOrJoinMeetSuccess(meetInfo);
                    }
                }
            }
        } catch (NumberFormatException e) {
            callback.onError(0, HttpUtil.HttpError.http_server_field_error);
            e.printStackTrace();
        }
    }

    private MeetingInfo getMeetingInfo(MeetingBean jsonBean) {
        MeetingInfo meetInfo = null;
        if (jsonBean != null) {
            SRPaasSDK srpaasSdk = SRPaasSDK.getInstance();
            String paasTokens = jsonBean.paasToken;
            String passUid_str = jsonBean.paasUid;
            if (paasTokens != null && !paasTokens.equals("")) {
                srpaasSdk.setPaasToken(paasTokens);
            }
            srpaasSdk.setPaasUid(StringUtil.StringToInt(passUid_str));

            meetInfo = new MeetingInfo();
            String confid_ = jsonBean.conference.confId;
            String subject = jsonBean.conference.subject;
            String m_startTime = jsonBean.conference.startTime;
            String m_endTime = jsonBean.conference.endTime;
            String m_confType = jsonBean.conference.confType;
            String m_startType = jsonBean.conference.confStartType;
            String mcaddr = jsonBean.conference.mcAddr;
            String relaymcaddr = HttpUtil.getArrayStr(jsonBean.conference.relaymcAddr);
            String m_relayServer = HttpUtil.getArrayStr(jsonBean.conference.relayServer);
            String thirdAudioKey = jsonBean.conference.TAK;
            String hasStarted = jsonBean.conference.hasStarted;
            String videoenable = jsonBean.conference.videoenable;
            String audioenable = jsonBean.conference.audioenable;
            String confPwd = jsonBean.conference.confPwd;
            String micautoenable = jsonBean.conference.micautoenable;
            String camaraautoenable = jsonBean.conference.camaraautoenable;
            String confName = jsonBean.conference.confName;
            String mediaGroupId = jsonBean.conference.mediaGroupId;
            String OCI = jsonBean.conference.OCI;
            String relaymcInfo = HttpUtil.getArrayStr(jsonBean.conference.relayMcInfo);
            String playAddrPrefix = jsonBean.conference.playAddrPrefix;
            String pullAddrPrefix = jsonBean.conference.pullAddrPrefix;
            log.E("HttpServiceImpl...getMeetingInfo...confid_: " + confid_ + "  subject:" + subject
                    + "  m_startTime:" + m_startTime + " m_endTime:" + m_endTime + "  m_confType:" + m_confType
                    + " m_startType:" + m_startType + "  mcaddr:" + mcaddr + "  relaymcaddr:" + relaymcaddr
                    + "  m_relayServer:" + m_relayServer + "  thirdAudioKey:" + thirdAudioKey
                    + "  hasStarted:" + hasStarted + "  videoenable:" + videoenable + "  audioenable:" + audioenable
                    + "  confPwd:" + confPwd + "  micautoenable:" + micautoenable + " camaraautoenable:" + camaraautoenable
                    + "   confName:" + confName + " mediaGroupId:" + mediaGroupId + " OCI:" + OCI + " relaymcInfo:" + relaymcInfo
                    + "   playAddrPrefix:" + playAddrPrefix + "  pullAddrPrefix:" + pullAddrPrefix);

            if (thirdAudioKey != null) meetInfo.setThirdAudioKey(thirdAudioKey);
            if (confid_ != null) meetInfo.setM_confId(confid_);
            if (mcaddr != null) meetInfo.setM_mcAddr(mcaddr);
            if (relaymcaddr != null) meetInfo.setM_relaymcAddr(relaymcaddr);
            if (subject != null) meetInfo.setM_subject(subject);
            if (m_relayServer != null) meetInfo.setM_relayServer(m_relayServer);
            if (m_startTime != null) meetInfo.setM_startTime(m_startTime);
            if (m_endTime != null) meetInfo.setM_endTime(m_endTime);
            if (hasStarted != null) meetInfo.setHasStarted(hasStarted);
            MeetingOptions m_options = new MeetingOptions();
            m_options.setM_confType(m_confType);
            m_options.setM_startType(m_startType);
            if (m_options != null) meetInfo.setM_options(m_options);
            if (videoenable != null) meetInfo.setVideoenable(videoenable);
            if (audioenable != null) meetInfo.setAudioenable(audioenable);
            if (confPwd != null) meetInfo.setConfPwd(confPwd);
            if (micautoenable != null) meetInfo.setMicautoenable(micautoenable);
            if (camaraautoenable != null) meetInfo.setCamaraautoenable(camaraautoenable);
            if (confName != null) meetInfo.setConfName(confName);
            if (mediaGroupId != null) meetInfo.setMediaGroupId(mediaGroupId);
            else meetInfo.setMediaGroupId("0");
            if (OCI != null) meetInfo.setOCI(OCI);
            if (relaymcInfo != null) meetInfo.setM_relaymcInfo(relaymcInfo);
            if (playAddrPrefix != null) meetInfo.setPlayAddrPrefix(playAddrPrefix);
            if (pullAddrPrefix != null) meetInfo.setPullAddrPrefix(pullAddrPrefix);
        }
        return meetInfo;
    }

    private void setMeetMap(HashMap<String, String> paramsMap, String confid, String subject, String pwd, String m_livePwd, String thirdAudioId, String thirdAudioVersion) {

        if (pwd == null || pwd.equals("")) pwd = "";
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetingInfo.m_confId, confid);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetingInfo.m_subject, subject);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetingInfo.m_confPwd, pwd);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetingInfo.m_livePwd, m_livePwd);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetingInfo.m_thirdAudioId, thirdAudioId);
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetingInfo.m_thirdAudioVersion, thirdAudioVersion);
        String serverId = "";
        SpaasInfo spaasInfo = SRPaasSDK.getInstance().getSpaasInfo();
        if (spaasInfo != null) serverId = spaasInfo.getServerId();
        setKeyValue(paramsMap, SRPaaSdkConfigure.MeetingInfo.m_serviceId, serverId);
//        log.E("setMeetMap...." + confid + " subject: " + subject + " pwd:" + pwd + " m_livePwd:" + m_livePwd + " thirdAudioId: " + thirdAudioId + " thirdAudioVersion:" + thirdAudioVersion+" serverId: "+serverId);
    }

    private void setMapBaseEntry(HashMap<String, String> paramsMap, String nickName) {

        SpaasInfo spaasInfo = SRPaasSDK.getInstance().getSpaasInfo();
        if (spaasInfo != null) {
            setKeyValue(paramsMap, SRPaaSdkConfigure.SECRET_KEY, spaasInfo.getSecretKey());
            setKeyValue(paramsMap, SRPaaSdkConfigure.APP_ID, spaasInfo.getAppId());
            setKeyValue(paramsMap, SRPaaSdkConfigure.U_ID, spaasInfo.getUid());
            setKeyValue(paramsMap, SRPaaSdkConfigure.PHONE, spaasInfo.getPhone());
            setKeyValue(paramsMap, SRPaaSdkConfigure.EMAIL, spaasInfo.getEmail());
            if (nickName == null || nickName.equals("")) {
                setKeyValue(paramsMap, SRPaaSdkConfigure.NICK_NAME, spaasInfo.getNickName());
            } else {
                setKeyValue(paramsMap, SRPaaSdkConfigure.NICK_NAME, nickName);
            }
//            log.E("setMapBaseEntry...getSecretKey: " + spaasInfo.getSecretKey() + " getAppId:" + spaasInfo.getAppId() + " getUid:" + spaasInfo.getUid() + " getNickName:" + spaasInfo.getNickName());
        }

    }

    private void setKeyValue(HashMap<String, String> paramsMap, String key, String value) {
        if (paramsMap != null) {
            if (key != null && value != null) {
                paramsMap.put(key, value);
            }
        }
    }

}
