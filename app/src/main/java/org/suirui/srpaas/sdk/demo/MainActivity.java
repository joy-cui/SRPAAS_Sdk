package org.suirui.srpaas.sdk.demo;

import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.media.AudioManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.srpaas.capture.service.VideoService;
import com.srpaas.capture.service.VideoServiceImpl;
import com.srpaas.capture.service.VideoServiceListener;
import com.suirui.srpaas.base.NetBean;
import com.suirui.srpaas.base.ui.activity.BaseAppCompatActivity;
import com.suirui.srpaas.base.util.log.SRLog;
import com.suirui.srpaas.base.util.receiver.NetStateReceiver;

import org.suirui.srpaas.contant.SRPaaSdkConfigure;
import org.suirui.srpaas.entry.AuthInfo;
import org.suirui.srpaas.entry.ConfInfoStatus;
import org.suirui.srpaas.entry.ConferenceInfo;
import org.suirui.srpaas.entry.MeeingListParams;
import org.suirui.srpaas.entry.MeetDetailInfo;
import org.suirui.srpaas.entry.MeetInfo;
import org.suirui.srpaas.entry.MeetingInfo;
import org.suirui.srpaas.entry.MeetingOptions;
import org.suirui.srpaas.entry.OnliveInfo;
import org.suirui.srpaas.entry.SRError;
import org.suirui.srpaas.entry.SRMediaPInfo;
import org.suirui.srpaas.entry.SRRecvStreamInfo;
import org.suirui.srpaas.entry.SRSendStreamInfo;
import org.suirui.srpaas.entry.ScreenLableAttr;
import org.suirui.srpaas.entry.TermInfo;
import org.suirui.srpaas.entry.UserInfo;
import org.suirui.srpaas.entry.VoiceActiveInfo;
import org.suirui.srpaas.http.HttpServiceImpl;
import org.suirui.srpaas.http.callback.OnHasPwdCallBack;
import org.suirui.srpaas.http.callback.OnMeetingDetailInfoCallBack;
import org.suirui.srpaas.http.callback.OnMeetingListCallBack;
import org.suirui.srpaas.sdk.AuthLoginListener;
import org.suirui.srpaas.sdk.AuthRegisterListener;
import org.suirui.srpaas.sdk.AuthServer;
import org.suirui.srpaas.sdk.AuthServerImpl;
import org.suirui.srpaas.sdk.MeetingControlService;
import org.suirui.srpaas.sdk.MeetingControlServiceImpl;
import org.suirui.srpaas.sdk.MeetingControlServiceListener;
import org.suirui.srpaas.sdk.MeetingService;
import org.suirui.srpaas.sdk.MeetingServiceImpl;
import org.suirui.srpaas.sdk.MeetingServiceListener;
import org.suirui.srpaas.sdk.SRPaas;
import org.suirui.srpaas.sdk.SRPaasSDK;
import org.suirui.srpaas.util.StringUtil;

import java.util.ArrayList;
import java.util.List;

import okhttp3.Call;

public class MainActivity extends BaseAppCompatActivity implements MeetingServiceListener, VideoServiceListener, MeetingControlServiceListener, AuthLoginListener, AuthRegisterListener, View.OnClickListener {
    static SRLog log = new SRLog(MainActivity.class.getSimpleName());
    public AudioManager audioManager = null;
    TextView test_sdk_lib;
    SRPaasSDK srPassSdk;
    Handler mHandler = new Handler();
    int[] RGB = null;
    private MeetingService meetingService;
    private AuthServer authServer;
    private Bitmap mBitmap = null;// 共享发送图片
    private boolean isSendData = false;
    private FrameLayout sharePic;
    private VideoService videoService;
    private boolean isSuccess = false;
    private int currentTermId = 0;
    private boolean isSharing = false;
    private boolean isOpenCamera = false;
    private boolean isMute = false;
    private boolean isAllMute = false;
    private boolean isHand = false;
    private boolean isLock = false;
    private boolean isSpeak = false;
    private MeetingControlService meetingControlService;
    private Button openCamera, btnMute, btnAllMute, btnHand, btnSpeak, btnLogin, btnRegister,btnGetMeetingList,
            btnHasPwd,meetDetailInfo;
    private int masterid = 0;
    private ListView termList;
    private TermInfoAdapter mAdapter;
    private List<TermInfo> term_List = new ArrayList<>();
    private EditText editConfig;
    private String currentConfid = "";//28671622260
    private String phone = "13700000003";
    private String token="9F5E3103F394EFD6F2D421F83B3E3C5757CA4555F774BD42";

    public static String appId = "beb7da4ced7c42a085c3c99697f9aa42";
    public static String secretKey = "beb7da4ced7c42a085c3c99697f9aa42";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        log.E("MainActivity..onCreate....");
        setContentView(R.layout.activity_sdk_demo);
        NetStateReceiver.registerNetworkStateReceiver(this);//注册网络状态
        sharePic = (FrameLayout) findViewById(R.id.sharePic);
        termList = (ListView) findViewById(R.id.termList);
        editConfig = (EditText) findViewById(R.id.editConfig);
        test_sdk_lib = (TextView) this.findViewById(R.id.test_sdk_lib);
        test_sdk_lib.setText("import srpass_sdk_v0.1.0.jar success");
        meetingService = new MeetingServiceImpl();
        meetingService.addMeetingServiceListener(this);
        authServer = new AuthServerImpl();
        authServer.addAuthLoginListener(this);
        authServer.addAuthRegisterListener(this);

        meetingControlService = new MeetingControlServiceImpl();
        meetingControlService.addMeetingControlServiceListener(this);

        videoService = new VideoServiceImpl();
        videoService.addVideoServiceListener(this);
        videoService.startCapture(this, 1);

        findview();
    }

    private void findview() {
        openCamera = (Button) findViewById(R.id.openCamera);
        btnMute = (Button) findViewById(R.id.btnMute);
        btnAllMute = (Button) findViewById(R.id.btnAllMute);
        btnHand = (Button) findViewById(R.id.onHand);
        btnSpeak = (Button) findViewById(R.id.btnSpeak);
        btnRegister = (Button) findViewById(R.id.btnRegister);
        btnLogin = (Button) findViewById(R.id.btnLogin);
        btnGetMeetingList=(Button)findViewById(R.id.btnGetMeetingList);
        btnHasPwd=(Button)findViewById(R.id.btnHasPwd);
        meetDetailInfo=(Button)findViewById(R.id.meetDetailInfo);
        openCamera.setOnClickListener(this);
        btnMute.setOnClickListener(this);
        btnAllMute.setOnClickListener(this);
        btnHand.setOnClickListener(this);
        btnSpeak.setOnClickListener(this);
        btnRegister.setOnClickListener(this);
        btnLogin.setOnClickListener(this);
        btnGetMeetingList.setOnClickListener(this);
        btnHasPwd.setOnClickListener(this);
        meetDetailInfo.setOnClickListener(this);
    }

    @Override
    public void onStart() {
        super.onStart();
    }

    @Override
    protected void onSensorEventChange(boolean b) {

    }

    @Override
    protected void onHeadsetStatus(boolean b) {

    }

    @Override
    protected void onBluetooth(int i, BluetoothAdapter bluetoothAdapter) {

    }

    public void unInitSdk(View v) {
//        if (/*SRPAASApplication.isInitSdk*/) {
//            srPassSdk.unInit();
//            test_sdk_lib.setText("注销sdk");
//        }
    }

    public void initSdk(View v) {
        test_sdk_lib.setText("开始初始化");
        srPassSdk = SRPaasSDK.getInstance();
        srPassSdk.initOkHttpSSL();
        srPassSdk.setPassUrl("http://192.168.61.39/api/v2");
        if (!srPassSdk.isInitialized())
            srPassSdk.initialize(false,false,SRPaaSdkConfigure.SREnginePlatFormType.SR_PLATFORM_TYPE_ANDROID_BOX);
//        if (SRPAASApplication.intSdk == 0) {
//            test_sdk_lib.setText("开始初始化...成功");
//        } else {
//            test_sdk_lib.setText("开始初始化...失败");
//        }
    }

    public void onClickBtnRegister(View v){
        SRPaasSDK srPaasSDK = SRPaasSDK.getInstance();
        srPaasSDK.setPassUrl("http://192.168.61.39/api/v2");
        AuthInfo accountInfo = new AuthInfo();
        String mac = NetworkUtil.getInstance(this).getMac();
        accountInfo.setAppid("beb7da4ced7c42a085c3c99697f9aa42");
        accountInfo.setSecretKey("beb7da4ced7c42a085c3c99697f9aa42");
        accountInfo.setType("6");
        accountInfo.setCpuNo("");
        accountInfo.setDiskNo("");
        accountInfo.setMacAddr(mac);
        accountInfo.setUuid(mac);
        accountInfo.setNickname("TVAPP");
        log.E(accountInfo.getAuthInfoString());
        authServer.Register(accountInfo);
    }

    public void onClickBtnLogin(View v){
        String mac = NetworkUtil.getInstance(this).getMac();
        SRPaasSDK srPaasSDK = SRPaasSDK.getInstance();
        srPaasSDK.setPassUrl("http://192.168.61.39/api/v2");
        AuthInfo accountInfo = new AuthInfo();
        accountInfo.setAppid("beb7da4ced7c42a085c3c99697f9aa42");
        accountInfo.setSecretKey("beb7da4ced7c42a085c3c99697f9aa42");
        accountInfo.setPwd("");
        accountInfo.setType("6");
        accountInfo.setCpuNo("");
        accountInfo.setDiskNo("");
        accountInfo.setMacAddr(mac);
        accountInfo.setUuid(mac);
        authServer.Login(accountInfo);
        log.E(" serverAdress:"+" login :" +accountInfo.getAuthInfoString());

    }

    public void onClickBtnModifyNick(View v){
        String mac = NetworkUtil.getInstance(this).getMac();
        SRPaasSDK srPaasSDK = SRPaasSDK.getInstance();
        srPaasSDK.setPassUrl("http://192.168.61.39/api/v2");
        AuthInfo accountInfo = new AuthInfo();
        accountInfo.setAppid("beb7da4ced7c42a085c3c99697f9aa42");
        accountInfo.setSecretKey("beb7da4ced7c42a085c3c99697f9aa42");
        accountInfo.setPwd("");
        accountInfo.setType("6");
        accountInfo.setCpuNo("");
        accountInfo.setDiskNo("");
        accountInfo.setMacAddr(mac);
        accountInfo.setUuid(mac);
        accountInfo.setToken("8F7A196F6489DD03D600456FEFA65F8944E6231952E32D0A");
        accountInfo.setNickname("TVAPP1111");
        authServer.updateUser(accountInfo);
        //http://192.168.61.39/api/v2/user/update?appid=beb7da4ced7c42a085c3c99697f9aa42&secretKey=beb7da4ced7c42a085c3c99697f9aa42&token=8F7A196F6489DD03D600456FEFA65F8944E6231952E32D0A&nickname=TVAAA
        log.E(" serverAdress:"+" updateUser :" +accountInfo.getAuthInfoString());
    }

    public void startMeet(View v) {
//        if (SRPAASApplication.intSdk != 0) {
//            test_sdk_lib.setText("初始化失败");
//            return;
//        }
        if (!isSuccess) {
            final int termId = (int) (Math.random() * 10000000);
            final String nikeName = "test" + termId;
            setSRPassSdk(String.valueOf(termId), nikeName);
            new Thread(new Runnable() {
                @Override
                public void run() {
                    MeetInfo meetInfo = new MeetInfo();
                    meetInfo.setNickName(nikeName);
                    MeetingOptions m_options = new MeetingOptions();
                    m_options
                            .setM_startType("2");
                    meetInfo.setM_options(m_options);
                    meetingService.StartMeeting(meetInfo);
                }
            }).start();
        }
    }

    public void joinMeet(View v) {
//        log.E("joinMeet.....isSuccess:" + isSuccess + "  :" + SRPAASApplication.intSdk);
//        if (SRPAASApplication.intSdk != 0) {
//            test_sdk_lib.setText("初始化失败");
//            return;
//        }
        final String confid = editConfig.getText().toString();
        if (!StringUtil.isEmptyOrNull(confid)) {
            if (!isSuccess) {
                final int termId = (int) (Math.random() * 10000000);
                final String nikeName = "test" + termId;
                setSRPassSdk(String.valueOf(termId), nikeName);
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        MeetInfo meetInfo = new MeetInfo();
                        meetInfo.setM_confId(confid);
                        meetInfo.setNickName(nikeName);
                        meetingService.joinMeeting(meetInfo);
                    }
                }).start();
            }
        } else {
            test_sdk_lib.setText("请输入会议号");
        }
    }

    public void startShareRGB(View v) {
        if (/*SRPAASApplication.isInitSdk && */isSuccess) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    meetingService.requestStartSendDualVideo();
                }
            }).start();
        } else {
            mHandler.post(new Runnable() {
                @Override
                public void run() {
                    test_sdk_lib.setText("请先入会");
                }
            });
        }
    }

    public void stopShareRGB(View v) {
        if (/*SRPAASApplication.isInitSdk && */isSuccess) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    meetingService.requestStopSendDualVideo();
                }
            }).start();
        } else {
            mHandler.post(new Runnable() {
                @Override
                public void run() {
                    test_sdk_lib.setText("请先入会");
                }
            });
        }
    }

    public void leaveMeet(View v) {
        if (/*SRPAASApplication.isInitSdk&&*/  isSuccess) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    if (isSharing) {//关闭共享
                        meetingService.requestStopSendDualVideo();
                    }
                    MeetingInfo meetingInfo = new MeetingInfo();
                    meetingInfo.setM_confId(currentConfid);
                    meetingService.leaveMeetingWithCmd(SRPaas.eLeaveMeetingCmd.eLeaveDefault, "正常退出");
                }
            }).start();

            mHandler.post(new Runnable() {
                @Override
                public void run() {
                    //关闭自己选看的视屏流
                    if (term_List == null)
                        return;
                    for (TermInfo termInfo : term_List) {
                        if (termInfo.getTermid() != currentTermId)
                            closeVideoRemote(termInfo.getTermid());
                    }
                }
            });
        } else {
            mHandler.post(new Runnable() {
                @Override
                public void run() {
                    test_sdk_lib.setText("请先入会");
                }
            });
        }
    }

    public void endMeet(View v) {
        if (/*SRPAASApplication.isInitSdk&&*/  isSuccess) {
            if (masterid == currentTermId) {
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        if (isSharing) {//关闭共享
                            meetingService.requestStopSendDualVideo();
                        }
                        MeetingInfo meetingInfo = new MeetingInfo();
                        meetingInfo.setM_confId("16592274987");
                        meetingService.leaveMeetingWithCmd(SRPaas.eLeaveMeetingCmd.eLeaveEndMeeting, "正常退出");
                    }
                }).start();

                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        //关闭自己选看的视屏流
                        if (term_List == null)
                            return;
                        for (TermInfo termInfo : term_List) {
                            if (termInfo.getTermid() != currentTermId)
                                closeVideoRemote(termInfo.getTermid());
                        }
                    }
                });
            } else {
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        test_sdk_lib.setText("只有主持人才能结束会议");
                    }
                });
            }
        } else {
            mHandler.post(new Runnable() {
                @Override
                public void run() {
                    test_sdk_lib.setText("请先入会");
                }
            });
        }
    }

    public void changeName(View v) {
        if (/*SRPAASApplication.isInitSdk&&*/  isSuccess) {
            if (masterid == currentTermId) {
                meetingControlService.changeName("success");
            } else {
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        test_sdk_lib.setText("主持人才能改名");
                    }
                });
            }
        } else {
            mHandler.post(new Runnable() {
                @Override
                public void run() {
                    test_sdk_lib.setText("请先入会");
                }
            });
        }
    }

    private void setSRPassSdk(String uid, String nickName) {
        srPassSdk.setAppKey("65220ea5c26d45099408f3c0044f727c", "65220ea5c26d45099408f3c0044f727c", uid, uid, "", "", nickName,1);
    }

    @Override
    public void OnMeetPort(final MeetingInfo meetingInfo) {
        if (meetingInfo == null)
            return;
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("会议信息....confId:" + meetingInfo.getM_confId()
                        + "  UserName:" + meetingInfo.getUserName()
                        + "  startTime:" + meetingInfo.getM_startTime()
                        + "  endTime:" + meetingInfo.getM_endTime()
                        + "  mcAddr:" + meetingInfo.getM_mcAddr()
                        + "  relaymcAddr:" + meetingInfo.getM_relaymcAddr()
                        + "  relayServer:" + meetingInfo.getM_relayServer()
                        + "  subject:" + meetingInfo.getM_subject()
                        + "  ThirdAudioKey:" + meetingInfo.getThirdAudioKey()
                        + "  HasStarted:" + meetingInfo.getHasStarted());
            }
        });

    }

    @Override
    public void onMeetingError(final SRError srError) {
        if (srError == null)
            return;
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("入会失败!!!...errorCode:" + srError.getCur_error());
            }
        });
    }

    @Override
    public void onMeetingError(SRPaas.eMeetingError errorMsg) {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("入会失败!!!");
            }
        });
    }

    @Override
    public void onLoginError(SRPaas.eLoginError error) {
        Toast.makeText(this, "登录失败了!!!", Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onLoginSuccess(UserInfo userInfo) {
        Toast.makeText(this, "登录成功了!!!", Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onRegisterError(SRPaas.eRegisterError error) {
        Toast.makeText(this, "注册失败了!!!", Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onRegisterSuccess(UserInfo info) {
        Toast.makeText(this, "注册成功了!!!", Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onHttpAuthError(int errorCode, String msg) {
        log.E("MainActivity....onHttpAuthError..." + errorCode);
    }

    @Override
    public void onHttpMeetingError(int errorCode, String msg) {
        log.E("MainActivity....onHttpMeetingError..." + errorCode);
    }

    @Override
    public void onHttpError(Call call, Exception e, int i) {
        log.E("MainActivity....onHttpError..."+i + "\n Exception:"+ e.getMessage());
    }

    @Override
    public void OnRspJoinConfSuccess(int sTermId, final String confId) {
        initAudio();
        currentTermId = sTermId;
        currentConfid = confId;
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("加入会议成功!!!...confId:" + confId);
            }
        });
        isSuccess = true;
        meetingService.getRequestTerminalmList();
    }

    @Override
    public void onRspConfTermList(final boolean status, final int master_id, final int duo_term_id, final List<TermInfo> termInfoList, final SRError srError) {
        this.masterid = master_id;
        mHandler.post(new Runnable() {
            @Override
            public void run() {

                if (!status) {
                    if (srError != null)
                        test_sdk_lib.setText("获取参会人列表失败：" + srError.getCur_error());
                    return;
                }
                if (termInfoList != null) {
                    for (TermInfo termInfo : termInfoList) {
                        test_sdk_lib.setText("获取参会人列表成功......master_id:" + master_id
                                + "  duo_term_id:" + duo_term_id
                                + "  Tername:" + termInfo.getTername()
                                + "  Termid:" + termInfo.getTermid()
                                + "  size:" + termInfoList.size());
                        if (currentTermId != termInfo.getTermid()) {
                            term_List.add(termInfo);
                        }
                    }
                    if (duo_term_id != 0) {
                        selectShareRemote(duo_term_id);
                    }

                } else {
                    test_sdk_lib.setText("获取参会人列表成功......master_id:" + master_id + "  duo_term_id:" + duo_term_id);
                }
                initData(term_List);

                meetingControlService.getSendStreamInfo(1000);
                meetingControlService.getRecvStreamInfo(1000);
            }
        });
    }

    @Override
    public void onRenderCallBackCallBack(int id, int flag, int format, byte[] y, byte[] u, byte[] v, int width, int height, int lenght) {

    }

//    private void selectVideoRemote(TermInfo termInfos) {
//        test_sdk_lib.setText("正在接收视频流....");
//        List<TermInfo> termList = new ArrayList<TermInfo>();
//        TermInfo termInfo = new TermInfo();
//        termInfo.setTermid(termInfos.getTermid());
//        termInfo
//                .setVideoType(SRPaas.VideoType.CFG_VIDEO_LOW_TYPE
//                        .getValue());
//        termList.add(termInfo);
//        meetingService.requestSelectRemoteVideo(termList);
//    }

    private void initData(List<TermInfo> term_list) {
        mAdapter = new TermInfoAdapter(this, term_list, meetingService, meetingControlService, test_sdk_lib, masterid, currentTermId);
        termList.setAdapter(mAdapter);
    }

    private void closeVideoRemote(int leaveId) {
        test_sdk_lib.setText("关闭视频流.....leaveId:" + leaveId);
        List<TermInfo> termList = new ArrayList<TermInfo>();
        TermInfo termInfo = new TermInfo();
        termInfo.setTermid(leaveId);
        termInfo
                .setVideoType(SRPaas.VideoType.SR_CFG_VIDEO_CLOSE
                        .getValue());
        termList.add(termInfo);
        meetingService.requestSelectRemoteVideo(termList);
    }

    private void selectShareRemote(int duo_term_id) {
        test_sdk_lib.setText("有人正在共享，接受共享数据....");
        List<TermInfo> shareTermList = new ArrayList<TermInfo>();
        TermInfo shareTermInfo = new TermInfo();
        shareTermInfo.setTermid(duo_term_id);
        shareTermInfo
                .setVideoType(SRPaas.VideoType.SR_CFG_DESKTOP_OPEN
                        .getValue());
        shareTermList.add(shareTermInfo);
        meetingService.requestSelectRemoteVideo(shareTermList);
    }

    private void closeShareRemote(int duo_term_id) {
        List<TermInfo> shareTermList = new ArrayList<TermInfo>();
        TermInfo shareTermInfo = new TermInfo();
        shareTermInfo.setTermid(duo_term_id);
        shareTermInfo
                .setVideoType(SRPaas.VideoType.SR_CFG_DESKTOP_CLOSE
                        .getValue());
        shareTermList.add(shareTermInfo);
        meetingService.requestSelectRemoteVideo(shareTermList);
    }

//    @Override
//    public void onRenderCallBackCallBack(final int id, final int flag, byte[] y, byte[] u, byte[] v, int width, int height,int length) {
//        mHandler.post(new Runnable() {
//            @Override
//            public void run() {
//                if (flag == 4) {
//                    test_sdk_lib.setText("收到终端" + id + "  的共享了....");
//                } else {
//                    test_sdk_lib.setText("收到终端" + id + "  的视频了....");
//                }
//            }
//        });
//    }

    @Override
    public void onNewTermJoinCallBack(final TermInfo termInfo) {
        if (termInfo == null)
            return;
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("有新终端加入....Termid:" + termInfo.getTermid()
                        + "  Tername:" + termInfo.getTername()
                        + "  VideoType:" + termInfo.getVideoType()
                        + "  TermState:" + termInfo.getTermState()
                        + "  AudioDeviceState:" + termInfo.getAudioDeviceState());
                term_List.add(termInfo);
                initData(term_List);
            }
        });
    }

    @Override
    public void onTermLeaveCallBack(final int leaveterid, final SRError srError) {
        if (currentTermId == leaveterid) {
            this.isSuccess = false;
        }
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                if (srError != null) {
                    test_sdk_lib.setText("有终端离开会议失败:" + srError.getCur_error());
                } else {
                    test_sdk_lib.setText("有终端离开会议.....leaveterid:" + leaveterid);
                    closeVideoRemote(leaveterid);
                }
                if (term_List != null) {
                    for (TermInfo term : term_List) {
                        if (term.getTermid() == leaveterid) {
                            term_List.remove(term);
                            break;
                        }
                    }
                }
                initData(term_List);
            }
        });
    }

    @Override
    public void OnRecvDualVideoCloseCallBack(int close_term_id) {
        closeShareRemote(close_term_id);
        isSharing = false;
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("停止共享了!!!");
            }
        });
    }

    @Override
    public void OnRecvDualVideoPauseCallBack(int pause_term_id) {

    }

    @Override
    public void OnRecvDualVideoResumeCallBack(int resumeTermId) {

    }

    @Override
    public void OnReqAssistVideoProxyCallBack(final int termId) {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("收到" + termId + " 的共享申请了。");
                dialog1(termId);
            }
        });
    }

    @Override
    public void OnScreenDrawLabelCallBack(ScreenLableAttr screenLableAttr) {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("收到共享标注了");
            }
        });
    }

    @Override
    public void OnRecvDualVideoOpenCallBack(final int send_id) {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("收到终端" + send_id + " 的共享了");
            }
        });
    }

    @Override
    public void onRspSendDualVideoCallBack(final boolean isOk, SRError srError) {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                if (isOk) {
                    isSharing = true;
                    test_sdk_lib.setText("可以开始共享图片了....");
                    getShareImage();
                } else {
                    test_sdk_lib.setText("不能共享....");
                }
            }
        });
    }

    @Override
    public void onTermAudioRecUnOrMuteCallBack(final int muteterid, final boolean isMute) {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                if (isMute)
                    test_sdk_lib.setText("终端id：" + muteterid + " 静音了");
                else
                    test_sdk_lib.setText("终端id：" + muteterid + " 取消静音了");
            }
        });
    }

    @Override
    public void onOpenCameraCallBack(final int open_id) {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("终端id：" + open_id + " 打开相机了");
            }
        });
    }

    @Override
    public void onCloseCameraCallBack(final int close_id) {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("终端id：" + close_id + " 关闭相机了");
            }
        });
    }

    @Override
    public void onMasterTransferCallBack(final int chair_stermid) {
        this.masterid = chair_stermid;
        if (mAdapter != null)
            mAdapter.setMasterId(chair_stermid);
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("收到主持人转移权限了，终端" + chair_stermid + " 成为新的主持人了");
            }
        });
    }

    @Override
    public void onLockOrUnLockVideoCallBack(final int unOrLockId, final boolean isLock) {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                if (isLock)
                    test_sdk_lib.setText("将终端" + unOrLockId + " 设置为焦点视屏了");
                else
                    test_sdk_lib.setText("取消终端" + unOrLockId + " 为焦点视屏");
            }
        });
    }

    @Override
    public void onTermHandUpCallBack(final int handupterid, final boolean isHandUp) {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                if (isHandUp)
                    test_sdk_lib.setText("终端" + handupterid + " 举手了..");
                else
                    test_sdk_lib.setText("终端" + handupterid + " 放下举手了..");
            }
        });
    }

    @Override
    public void onActiveVoiceCallBack(List<VoiceActiveInfo> voiceActiveInfoList) {

    }

    @Override
    public void onMuteAudioAllTermNotifyCallBack(final boolean isMute) {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                if (isMute)
                    test_sdk_lib.setText("主持人全部静音了...");
                else
                    test_sdk_lib.setText("主持人取消全部静音了...");
            }
        });
    }

    @Override
    public void onChairEndConfCallBack(final int endTermid, String endName) {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("主持人结束会议了...");
                MeetingInfo meetingInfo = new MeetingInfo();
                meetingInfo.setM_confId(currentConfid);
                meetingService.leaveMeetingWithCmd(SRPaas.eLeaveMeetingCmd.eLeaveDefault, "正常退出");
            }
        });
    }

    @Override
    public void OnExitConfCallBack(final String exit_reason) {
        this.isSuccess = false;
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("退出会议成功!!!....:" + exit_reason);
            }
        });
        videoService.stopCapture();
    }

    @Override
    public void OnStackConnErrorCallBack(int type) {

    }

    @Override
    public void OnNetwrokNotify(int status) {

    }

    @Override
    public void SREngineRunningStatusNotifyCallBack(int stautsTermid,
                                                    int staClass, int staSubCls, String staStr) {

    }

    @Override
    public void onTermChangeNameCallBack(final int changeterid, final String term_name) {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("终端" + changeterid + "  将昵称改为:" + term_name);
            }
        });
    }

    @Override
    public void OnStopSendVideoCallBack() {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("终端停止发送视频流了");
            }
        });
    }

    @Override
    public void onIndChairEndDataShareCallBack(final int chair_stermid, final String chair_name) {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                test_sdk_lib.setText("会中共享时，主持人结束会议了，终端为：" + chair_name + "  :" + chair_stermid);
            }
        });
    }

    @Override
    public void onScreenClearLabelCallBack(int cleard_stermid) {

    }

    @Override
    public void onSendStreamInfoStatsCallBack(List<SRSendStreamInfo> sendStreamInfoList) {
        
    }

    @Override
    public void onRecvStreamInfoStatsCallBack(List<SRRecvStreamInfo> recvStreamInfoList) {

    }

    @Override
    public void onServerErrorCallBack(int errorCode) {

    }

    @Override
    public void getJNIExcaption() {

    }

    @Override
    public void onConfForceMuteAllTermCallBack(boolean isforcemute) {

    }

    @Override
    public void onRspConfInfoStatusCallBack(boolean isok, ConfInfoStatus confInfoStatus, SRError srError) {

    }

    @Override
    public void onIndTerCRSRecStateCallBack(int recordstate, SRError error) {

    }

    @Override
    public void onAllMPInfoCallBack(List<SRMediaPInfo> srMediaPInfoList) {
        
    }

    @Override
    public void onMPScreenInfoCallback(int channelid, int screenid, int screentype, int addordel) {

    }

    @Override
    public void onUpdateAddPaticipantsCallback(List<TermInfo> addTermInfoList) {

    }

    @Override
    public void onUpdateDelPaticipantsCallback(List<TermInfo> delTermInfoList) {

    }

    @Override
    public void onInviteSuccess() {

    }

    @Override
    public void onHttpInviteError(int errorCode, String msg) {
        
    }

    @Override
    public void OnIndTerSpecialtypeTransferCallBack(int nspclterid, int nspcltype) {

    }

    @Override
    public void OnIndTerCRSLiveStateCallBack(int livestate, String liveplayurl, SRError srError) {

    }

//    @Override
//    public void OnIndTerCRSLiveStateCallBack(int livestate, SRError srError) {
//
//    }

    @Override
    public void OnIndLiveSettingChangedCallBack(OnliveInfo info) {

    }

    @Override
    public void OnRecvConfMessageCallBack(int termId, String message) {
        
    }

    @Override
    public void onServerOkCallBack(int okCode) {

    }

    @Override
    protected void onDestroy() {
        log.E("onDestroy......");
        super.onDestroy();
//        if (/*SRPAASApplication.isInitSdk*/)
//            srPassSdk.unInit();
        videoService.stopCapture();
        videoService.removeVideoServiceListener();
//        SRPAASApplication.paasUid = 0;
//        SRPAASApplication.joinNickName = "";
    }

    @Override
    protected void onNetworkConnected(NetBean netBean) {

    }

    @Override
    protected void onNetworkDisConnected() {
        Toast.makeText(this, "Network disConnected", Toast.LENGTH_SHORT).show();
    }

    @Override
    protected boolean isSupportActionBar() {
        return false;
    }

    private void getShareImage() {
        Drawable drawable = getResources().getDrawable(R.drawable.no_avatar);
        BitmapDrawable bd = (BitmapDrawable) drawable;
        mBitmap = bd.getBitmap();
        try {
        } catch (OutOfMemoryError e) {
            e.printStackTrace();
            if (mBitmap != null)
                mBitmap.recycle();
            mBitmap = null;
        }

        if (mBitmap != null) {
            int width = mBitmap.getWidth();
            int height = mBitmap.getHeight();
            isSendData = true;
            log.E("onRspSendDualVideoCallBack...display_screen....width:" + width
                    + "  height: " + height);
            sendDataStream(mBitmap, width, height);
        }
    }

    private void sendDataStream(final Bitmap mBitmap, final int width, final int height) {
        if (mBitmap != null) {
            try {
                RGB = new int[width * height];
                mBitmap.getPixels(RGB, 0, width, 0, 0, width, height);
                if (mBitmap != null && !mBitmap.isRecycled()) {
                    mBitmap.recycle();
                }
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        // 要做的事情
                        if (isSharing) {
                            if (/*SRPAASApplication.isInitSdk&&*/  isSuccess) {//会议成功中
                                if (RGB != null && RGB.length > 0 && RGB.length == width * height) {
                                    log.E("onRspSendDualVideoCallBack.发送。。。。");
                                    meetingService.sendDataStreamRGB(SRPaas.SRVideoStreamType.kSRScreenStream.getValue(), width, height, RGB);
                                }
                                mHandler.postDelayed(this, 1000);
                            }
                        }
                    }
                });
            } catch (RuntimeException e) {
                e.printStackTrace();
            } catch (OutOfMemoryError e) {
                e.printStackTrace();
            }
        }
    }

    private void initAudio() {
        if (audioManager == null) {
            audioManager = (AudioManager) this
                    .getSystemService(Context.AUDIO_SERVICE);
            this.setVolumeControlStream(AudioManager.STREAM_MUSIC);
        }
        try {
//            meetingService.setSpeakerMode(1);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void onstartCaptureFailListener() {

    }

    @Override
    public void onstopCaptureFailListener() {

    }

    @Override
    public void onPreviewCallback(byte[] data, int width, int height, boolean isRotation, int rotation, boolean isMirror) {
        if (/*SRPAASApplication.isInitSdk&&*/  isSuccess) {
            meetingService.sendDataStreamVideo(SRPaas.SRVideoStreamType.kSRVideoStream.getValue(), data, width, height, rotation, isMirror, data.length);
        }
    }

    @Override
    public void onPreviewCallback(byte[] des, int width, int height, int rotation) {
//        if (/*SRPAASApplication.isInitSdk&& */ isSuccess) {
//            meetingService.sendDataStreamYUV(SRPaas.SRVideoStreamType.kSRVideoStream.getValue(), width, height, des);
//        }
    }

    private void dialog1(final int termId) {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);  //先得到构造器
        builder.setTitle("提示"); //设置标题
        builder.setMessage("收到共享申请了?"); //设置内容
        builder.setIcon(R.mipmap.ic_launcher);//设置图标，图片id即可
        builder.setPositiveButton("确定", new DialogInterface.OnClickListener() { //设置确定按钮
            @Override
            public void onClick(DialogInterface dialog, int which) {
                meetingService.requestStopSendDualVideo();
                meetingService.resposeSendDualVideoProxy(termId, true, "");
                dialog.dismiss(); //关闭dialog
            }
        });
        builder.setNegativeButton("取消", new DialogInterface.OnClickListener() { //设置取消按钮
            @Override
            public void onClick(DialogInterface dialog, int which) {
                meetingService.resposeSendDualVideoProxy(termId, false, "拒绝");
                dialog.dismiss();
            }
        });
        //参数都设置完成了，创建并显示出来
        builder.create().show();
    }

    @Override
    public void onMeetingControlError(int errorCode) {

    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.openCamera:
                if (/*SRPAASApplication.isInitSdk&& */ isSuccess) {
                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            if (!isOpenCamera) {
                                meetingService.openCamera(currentTermId);
                                isOpenCamera = true;
                                openCamera.setText("关闭相机");
                            } else {
                                meetingService.closeCamera(currentTermId);
                                isOpenCamera = false;
                                openCamera.setText("打开相机");
                            }
                        }
                    }).start();
                } else {
                    mHandler.post(new Runnable() {
                        @Override
                        public void run() {
                            test_sdk_lib.setText("请先入会");
                        }
                    });
                }
                break;

            case R.id.btnMute:
                if (/*SRPAASApplication.isInitSdk&& */ isSuccess) {
                    if (!isMute) {
                        meetingControlService.muteAudio(currentTermId);
                        isMute = true;
                        mHandler.post(new Runnable() {
                            @Override
                            public void run() {
                                btnMute.setText("取消静音");
                            }
                        });
                    } else {
                        meetingControlService.unMuteAudio(currentTermId);
                        isMute = false;
                        mHandler.post(new Runnable() {
                            @Override
                            public void run() {
                                btnMute.setText("静音");
                            }
                        });
                    }
                } else {
                    mHandler.post(new Runnable() {
                        @Override
                        public void run() {
                            test_sdk_lib.setText("请先入会");
                        }
                    });
                }
                break;

            case R.id.btnAllMute://调试有问题（MuteAudioAllTerm）
                if (/*SRPAASApplication.isInitSdk&& */ isSuccess) {
                    if (!isAllMute) {
                        meetingControlService.muteAllAudio(true);
                        isAllMute = true;
                        mHandler.post(new Runnable() {
                            @Override
                            public void run() {
                                btnAllMute.setText("取消全部静音");
                            }
                        });
                    } else {
                        meetingControlService.muteAllAudio(false);
                        isAllMute = false;
                        mHandler.post(new Runnable() {
                            @Override
                            public void run() {
                                btnAllMute.setText("全部静音");
                            }
                        });
                    }
                } else {
                    mHandler.post(new Runnable() {
                        @Override
                        public void run() {
                            test_sdk_lib.setText("请先入会");
                        }
                    });
                }

                break;

            case R.id.onHand:
                if (/*SRPAASApplication.isInitSdk&& */ isSuccess) {
                    if (currentTermId != masterid) {
                        if (!isHand) {
                            meetingControlService.handUp(true);
                            isHand = true;
                            mHandler.post(new Runnable() {
                                @Override
                                public void run() {
                                    btnHand.setText("放下");
                                }
                            });
                        } else {
                            meetingControlService.handUp(false);
                            isHand = false;
                            mHandler.post(new Runnable() {
                                @Override
                                public void run() {
                                    btnHand.setText("举手");
                                }
                            });
                        }
                    } else {
                        mHandler.post(new Runnable() {
                            @Override
                            public void run() {
                                test_sdk_lib.setText("主持人不能举手");
                            }
                        });
                    }
                } else {
                    mHandler.post(new Runnable() {
                        @Override
                        public void run() {
                            test_sdk_lib.setText("请先入会");
                        }
                    });
                }
                break;

            case R.id.btnSpeak:
                if (/*SRPAASApplication.isInitSdk&& */ isSuccess) {
                    if (!isSpeak) {
                        openOrCloseSpeaker(true);
                        isSpeak = true;
                        mHandler.post(new Runnable() {
                            @Override
                            public void run() {
                                btnSpeak.setText("取消外放模式");
                            }
                        });
                    } else {
                        openOrCloseSpeaker(false);
                        isSpeak = false;
                        mHandler.post(new Runnable() {
                            @Override
                            public void run() {
                                btnSpeak.setText("外放模式");
                            }
                        });
                    }

                } else {
                    mHandler.post(new Runnable() {
                        @Override
                        public void run() {
                            test_sdk_lib.setText("请先入会");
                        }
                    });
                }
                break;

            case R.id.btnRegister:
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        SRPaasSDK srPaasSDK = SRPaasSDK.getInstance();
                        srPaasSDK.setPassUrl("http://192.168.61.39/api");
                        AuthInfo accountInfo = new AuthInfo();
                        accountInfo.setPhone(phone);
                        accountInfo.setAppid("65220ea5c26d45099408f3c0044f727c");
                        accountInfo.setPwd("123456");
                        accountInfo.setUseIM(1);
                        authServer.Register(accountInfo);
                    }
                });
                break;

            case R.id.btnLogin:
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        SRPaasSDK srPaasSDK = SRPaasSDK.getInstance();
                        srPaasSDK.setPassUrl("http://192.168.61.39/api");
                        AuthInfo accountInfo = new AuthInfo();
                        accountInfo.setAccount(phone);
                        accountInfo.setPwd("12345678");
                        accountInfo.setAppid(appId);
                        authServer.Login(accountInfo);
                    }
                });

                break;
            case R.id.btnGetMeetingList:
                SRPaasSDK srPaasSDK = SRPaasSDK.getInstance();
                srPaasSDK.setPassUrl("http://192.168.61.39/api/v2");
                MeeingListParams params=new MeeingListParams();
                params.setAppId(appId);
                params.setSecretKey(appId);
                params.setNumber(10);
                params.setStart(0);
                params.setTimestamp("");
                params.setToken(token);
                meetingService.getMeetingList(params, new OnMeetingListCallBack() {
                    @Override
                    public void onError(int code, String msg) {
                        log.E("getMeetingList  error: "+msg);
                        super.onError(code, msg);
                    }

                    @Override
                    public void onSuccess(List<ConferenceInfo> conferenceInfoList) {
                        for(ConferenceInfo conferenceInfo:conferenceInfoList) {
                            log.E("getMeetingList  : " + conferenceInfoList.size()+"  : "+conferenceInfo.getConfId()+" : "+conferenceInfo.getSubject()+"  : "+conferenceInfo.getSuid());

                        }
                        super.onSuccess(conferenceInfoList);
                    }
                });

                break;
            case R.id.btnHasPwd:
                SRPaasSDK.getInstance().setPassUrl("http://192.168.61.39/api/v2");
                meetingService.getMeetingPwd(token,"532327", new OnHasPwdCallBack() {

                    @Override
                    public void onError(int code, String msg) {
                     log.E("getMeetingPwd....onError:"+code+"  msg :"+msg);
                    }

                    @Override
                    public void onSuccess(String confId, boolean hasPwd) {
                        log.E("getMeetingPwd...hasPwd: "+hasPwd+" confId: "+confId);
                    }
                });

                break;
            case R.id.meetDetailInfo:
                SRPaasSDK.getInstance().setPassUrl("http://192.168.61.39/api/v2");
                HttpServiceImpl.getInstance().getMeetingInfo(appId, secretKey, token, "598158", new OnMeetingDetailInfoCallBack() {
                    @Override
                    public void onError(int code, String msg) {
                        log.E("meetDetailInfo....onError:"+code+"  msg :"+msg);
                    }

                    @Override
                    public void onSuccess(MeetDetailInfo meetDetailInfo) {
                        if(meetDetailInfo!=null) {
                            log.E("meetDetailInfo....onSuccess......getConfId:" + meetDetailInfo.getConfId() + "  getConfName :" + meetDetailInfo.getConfName());
                        }
                    }
                });
                break;
        }
    }

    private void openOrCloseSpeaker(boolean isOpen) {
        if (audioManager == null)
            return;
        try {
            if (isOpen) {//外放模式
                audioManager.setMode(AudioManager.STREAM_MUSIC);
                audioManager.setSpeakerphoneOn(true);
            } else {//听筒模式
                if (audioManager.isSpeakerphoneOn()) {
                    audioManager.setSpeakerphoneOn(false);
                    OpenTelephoneStream();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void OpenTelephoneStream() {
        this.setVolumeControlStream(AudioManager.STREAM_VOICE_CALL); // 设置电话流控
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            audioManager.setMode(AudioManager.MODE_IN_COMMUNICATION);
        } else {
            audioManager.setMode(AudioManager.MODE_IN_CALL);
        }
    }
}
