package org.suirui.srpaas.sdk;

import com.suirui.srpaas.base.util.log.SRLog;
import com.suirui.srpaas.common.http.okhttp.OkHttpUtils;
import com.suirui.srpaas.common.http.okhttp.https.HttpsUtils;
import com.suirui.srpaas.common.http.okhttp.log.LoggerInterceptor;

import org.suirui.srpaas.contant.SRPaaSdkConfigure;
import org.suirui.srpaas.entry.SpaasInfo;
import org.suirui.srpaas.jni.JniNative;
import org.suirui.srpaas.util.StringUtil;

import java.util.concurrent.TimeUnit;

import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.SSLSession;

import okhttp3.OkHttpClient;

public class SRPaasSDK {

    private static final SRLog log = new SRLog(SRPaasSDK.class.getName());
    static SRPaasSDK instance = null;
    private MeetingService mMeetingService;
    private MeetingControlService mMeetingControlService;
    private AuthServer mAuthServer;
    private String pass_url_root = "";
    private boolean isInitSdk = false;//sdk是否初始化成功
    private int intSdk = -1;
    private SpaasInfo spaasInfo;// 第三方用户信息
    private String paasToken = "";// token
    private int paasUid = 0;// pass平台登录的账号信息
    private int term_id = 0;// pass平台对应的sid(pass平台退出会议的时候用的)
    private String userName = "";// 账号名称(登录时候的帐号),登录成功后赋值的格式：uid:nickName:pic
    private String DO_MAIN_URL = "";//域名
    private String inviteUrl = "";


    private SRPaasSDK() {
    }

    public static synchronized SRPaasSDK getInstance() {
        if (instance == null) {
            log.E("new SRPaasSDK...initSdk");
            instance = new SRPaasSDK();
        }
        return instance;
    }

    public String getPassUrl() {
        return pass_url_root;
    }

    public void setPassUrl(String pass_http_url) {
        if (!StringUtil.isEmptyOrNull(pass_http_url)) {
            pass_url_root = pass_http_url;
        }
    }

    public String getDoMain() {
        return DO_MAIN_URL;
    }

    public void setDoMain(String domain) {
        if (!StringUtil.isEmptyOrNull(domain)) {
            DO_MAIN_URL = domain;
        }
    }

    public String getInviteUrl() {
        return inviteUrl;
    }

    public void setInviteUrl(String invite_URL) {
        if (!StringUtil.isEmptyOrNull(invite_URL)) {
            inviteUrl = invite_URL;
        }
    }

    public void initialize(boolean isOpenSDKLog,boolean isH264Decode,int platformType) {
        init(isOpenSDKLog,isH264Decode,platformType);
    }

    public boolean isInitialized() {
        return isInitSdk;
    }

    public int initSdk() {
        return intSdk;
    }

    public SpaasInfo getSpaasInfo() {
        return this.spaasInfo;
    }

    public String getPaasToken() {
        return this.paasToken;
    }

    public void setPaasToken(String paasToken) {
        this.paasToken = paasToken;
    }

    public int getPaasUid() {
        return this.paasUid;
    }

    public void setPaasUid(int paasUid) {
        this.paasUid = paasUid;
    }

    private synchronized void init(boolean isOpenSDKLog,boolean isH264Decode,int platformType) {
        log.E("initSdk.....加载库....isOpenSDKLog:" + isOpenSDKLog + " isH264Decode:" + isH264Decode);
        if (platformType== SRPaaSdkConfigure.SREnginePlatFormType.SR_PLATFORM_TYPE_ANDROID_BOX) {
            JniNative.loadlibraryhBox();
        } else {
            JniNative.loadlibrary();
        }
       //	String logPath = Environment.getExternalStorageDirectory() + "/";
//		int result = JniNative.InitSDK(true, logPath);
        int result = JniNative.InitSDK(isOpenSDKLog,isH264Decode,platformType);
        log.E("initSdk........." + result + "  url: " + pass_url_root);
        intSdk = result;
        isInitSdk = result == 0 ? true : false;
    }

    public void unInit() {
        JniNative.UnInitSDK();
    }

    public MeetingService getMeetingService() {
        if (!this.isInitialized()) {
            return null;
        } else {
            if (this.mMeetingService == null) {
                this.mMeetingService = new MeetingServiceImpl();
            }
            return this.mMeetingService;
        }

    }

    public MeetingControlService getMeetingControlService() {
        if (!this.isInitialized()) {
            return null;
        } else {
            if (this.mMeetingControlService == null) {
                this.mMeetingControlService = new MeetingControlServiceImpl();
            }
            return this.mMeetingControlService;
        }
    }

    public AuthServer getAuthServer() {
        if (this.mAuthServer == null) {
            this.mAuthServer = new AuthServerImpl();
        }
        return this.mAuthServer;
    }

    /**
     * @param appId     （必填）
     * @param secretKey （必填）
     * @param uid       第三方用户唯一标识（必填）
     * @param phone
     * @param email
     * @param nickName
     */
    public void setAppKey(String appId, String secretKey, String uid,
                          String serverId, String phone, String email, String nickName, int userType) {
        SpaasInfo spaasInfo = new SpaasInfo();
        if (appId != null)
            spaasInfo.setAppId(appId);
        if (secretKey != null)
            spaasInfo.setSecretKey(secretKey);
        if (uid != null && !uid.equals("")) {
            spaasInfo.setUid(uid);
        }
        if (email != null)
            spaasInfo.setEmail(email);
        if (phone != null)
            spaasInfo.setPhone(phone);
        if (nickName != null) {
            this.userName = nickName;
            String[] term = nickName.split(":");
            if (term != null && term.length > 1) {
                spaasInfo.setNickName(term[1]);
            } else {
                spaasInfo.setNickName(nickName);
            }
        }
        if (serverId != null)
            spaasInfo.setServerId(serverId);
        spaasInfo.setUserType(userType);
        log.E("setAppKey...............uid:" + uid);
        this.spaasInfo = spaasInfo;

    }

    /**
     * https获取证书
     */
    public void initOkHttpSSL() {
        HttpsUtils.SSLParams sslParams = HttpsUtils.getSslSocketFactory(null, null, null);
        OkHttpClient okHttpClient = new OkHttpClient.Builder()
                .connectTimeout(10000L, TimeUnit.MILLISECONDS)
                .readTimeout(10000L, TimeUnit.MILLISECONDS)
                .addInterceptor(new LoggerInterceptor("TAG"))
                .hostnameVerifier(new HostnameVerifier() {
                    @Override
                    public boolean verify(String hostname, SSLSession session) {
                        return true;
                    }
                })
                .sslSocketFactory(sslParams.sSLSocketFactory, sslParams.trustManager)
                .build();
        OkHttpUtils.initClient(okHttpClient);
    }
}
