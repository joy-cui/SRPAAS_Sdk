package org.suirui.srpaas.sdk;

import com.suirui.srpaas.base.util.log.SRLog;

import org.suirui.srpaas.contant.UserType;
import org.suirui.srpaas.entry.AuthInfo;
import org.suirui.srpaas.entry.UserInfo;
import org.suirui.srpaas.http.HttpService;
import org.suirui.srpaas.http.HttpServiceImpl;
import org.suirui.srpaas.http.callback.LoginCallBack;
import org.suirui.srpaas.http.callback.RegisterCallBack;
import org.suirui.srpaas.util.StringUtil;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import okhttp3.Call;

/**
 * @authordingna
 * @date2017-05-24
 **/
public class AuthServerImpl implements AuthServer {
    private static final SRLog log = new SRLog(AuthServerImpl.class.getSimpleName());
    private AuthRegisterListener registerListener;
    private AuthLoginListener loginListener;
    private UpdateUserListener updateUserListener;

    @Override
    public void addAuthLoginListener(AuthLoginListener listener) {
        this.loginListener = listener;
    }

    @Override
    public void addAuthRegisterListener(AuthRegisterListener listener){
        registerListener = listener;
    }

    @Override
    public void addUpdateListener(UpdateUserListener listener) {
        this.updateUserListener = listener;
    }


    @Override
    public void Register(AuthInfo info) {
        if (info == null) {
            onRegisterError(SRPaas.eRegisterError.eRegisterError_ACCOUNT);
            return;
        } else {
            if(StringUtil.isSameString(info.getType(),""+ UserType.USER_NEW_UBOX)){

            }else {
                if (info.getPhone() == null || info.getPhone().equals("")) {
                    onRegisterError(SRPaas.eRegisterError.eRegisterError_ACCOUNT);
                    return;
                }
                if (info.getPwd() == null || info.getPwd().equals("")) {
                    onRegisterError(SRPaas.eRegisterError.eRegisterError_Pwd);
                    return;
                }
                if (info.getAppid() == null || info.getAppid().equals("")) {
                    onRegisterError(SRPaas.eRegisterError.eRegisterError_Appid);
                    return;
                }
            }

        }
        HttpService h = HttpServiceImpl.getInstance();
        h.Register(info, new RegisterCallBack() {
            @Override
            public void onRegisterSuccess(final UserInfo info) {
                if (info == null || info.getSuid() == null || info.getSuid().equals("")) {
                    onRegisterError(SRPaas.eRegisterError.eRegisterError_InvalidAccount);
                } else {
                    if (registerListener != null) {
                        registerListener.onRegisterSuccess(info);
                    }
                }
            }

            @Override
            public void onError(int errorCode, String msg) {
                if (registerListener != null) {
                    registerListener.onHttpAuthError(errorCode, msg);
                }
            }

            @Override
            public void onError(Call call, Exception e, int i) {
                if (registerListener != null) {
                    registerListener.onHttpError(call, e, i);
                }
            }
        });
    }

    private void onRegisterError(SRPaas.eRegisterError error) {
        if (registerListener != null) {
            registerListener.onRegisterError(error);
        }
    }

    @Override
    public void Login(AuthInfo info) {
        if (info == null) {
            onLoginError(SRPaas.eLoginError.eLoginError_InvalidAccount);
            return;
        } else {
            if(StringUtil.isSameString(info.getType(),""+ UserType.USER_NEW_UBOX)){

            }else {
                if (info.getAccount() == null || info.getAccount().equals("")) {
                    onLoginError(SRPaas.eLoginError.eLoginError_ACCOUNT);
                    return;
                }
                if (info.getPwd() == null || info.getPwd().equals("")) {
                    onLoginError(SRPaas.eLoginError.eLoginError_Pwd);
                    return;
                }
            }
        }
        HttpService h = HttpServiceImpl.getInstance();
        h.login(info, new LoginCallBack() {
            @Override
            public void onLoginSuccess(UserInfo userInfo) {
                if (userInfo == null) {
                    onLoginError(SRPaas.eLoginError.eLoginError_InvalidAccount);
                } else {
                    if (loginListener != null) {
                        loginListener.onLoginSuccess(userInfo);
                    }
                }
            }

            @Override
            public void onError(int errorCode, String msg) {
                if (loginListener != null) {
                    loginListener.onHttpAuthError(errorCode, msg);
                }
            }

            @Override
            public void onError(Call call, Exception e, int i) {
                if (loginListener != null) {
                    loginListener.onHttpError(call, e, i);
                }
            }
        });
    }

    @Override
    public void updateUser(AuthInfo info){
        if (info == null) {
            onUpdateError(SRPaas.eError.eError_Parm_Null);
            return;
        } else {
            if(StringUtil.isSameString(info.getType(),""+ UserType.USER_NEW_UBOX)){
                if (info.getNickname() == null || info.getNickname().equals("")) {
                    onUpdateError(SRPaas.eError.eError_Parm_Null);
                    return;
                }
            }else {

            }
        }
        HttpService h = HttpServiceImpl.getInstance();
        h.updateUser(info, new LoginCallBack() {
            @Override
            public void onLoginSuccess(UserInfo userInfo) {
                if (userInfo == null) {
                    onUpdateError(SRPaas.eError.eError_Error);
                } else {
                    if (updateUserListener != null) {
                        updateUserListener.onUpdateSuccess(userInfo);
                    }
                }
            }

            @Override
            public void onError(int errorCode, String msg) {
                if (updateUserListener != null) {
                    updateUserListener.onHttpAuthError(errorCode, msg);
                }
            }

            @Override
            public void onError(Call call, Exception e, int i) {
                if (updateUserListener != null) {
                    updateUserListener.onHttpError(call, e, i);
                }
            }
        });
    }

    @Override
    public void tempLogin() {
        return;
    }

    /**
     * 登录接口错误处理
     *
     * @param error
     */
    private void onLoginError(SRPaas.eLoginError error) {
        if (loginListener != null) {
            loginListener.onLoginError(error);
        }
    }

    private void onUpdateError(SRPaas.eError error) {
        if (updateUserListener != null) {
            updateUserListener.onUpdateError(error);
        }
    }
}
