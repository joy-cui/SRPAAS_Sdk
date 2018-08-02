package org.suirui.srpaas.entry;

/**
 * 登录注册时的认证信息
 *
 * @authordingna
 * @date2017-05-23
 **/
public class AuthInfo {
    private String account;//账号(手机号)
    private String appid;//密码（appid）
    private String secretKey;//
    private String nickname;//昵称
    private String pwd;//密码
    private int useIM;//若为1则同时在平台IM创建用户，0不创建
    private String type;//用户类型 1：注册用户2：ubox 用户3：标准终端4：监控点用户5：非本级用户6：新版本 ubox 账号

    private String phone;//账号(手机号)

    //tv
    private String uuid;//设备的 Uuid用户类型为 6 时必填
    private String macAddr;//地址用户类型为 6 时使用
    private String cpuNo;//Cpu 序列号用户类型为 6 时传入
    private String diskNo;//硬盘序列号 用户类型为 6 时传入
    private String token;
    private String doMain;

    public String getDoMain() {
        return doMain;
    }

    public void setDoMain(String doMain) {
        this.doMain = doMain;
    }

    public String getAccount() {
        return account;
    }

    public void setAccount(String account) {
        this.account = account;
    }

    public String getAppid() {
        return appid;
    }

    public void setAppid(String appid) {
        this.appid = appid;
    }

    public String getSecretKey() {
        return secretKey;
    }

    public void setSecretKey(String secretKey) {
        this.secretKey = secretKey;
    }

    public String getNickname() {
        return nickname;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }

    public String getPwd() {
        return pwd;
    }

    public void setPwd(String pwd) {
        this.pwd = pwd;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    public int getUseIM() {
        return useIM;
    }

    public void setUseIM(int useIM) {
        this.useIM = useIM;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getUuid() {
        return uuid;
    }
    public void setUuid(String uuid) {
        this.uuid = uuid;
    }

    public String getMacAddr() {
        return macAddr;
    }
    public void setMacAddr(String macAddr) {
        this.macAddr = macAddr;
    }

    public String getCpuNo() {
        return cpuNo;
    }

    public void setCpuNo(String cpuNo) {
        this.cpuNo = cpuNo;
    }

    public String getDiskNo() {
        return this.diskNo;
    }

    public void setDiskNo(String diskNo) {
        this.diskNo = diskNo;
    }

    public String getToken() {
        return token;
    }

    public void setToken(String token) {
        this.token = token;
    }

    public String getAuthInfoString(){
        return "AuthInfo:"
                +" account:"+this.account
                +" appid:"+this.appid
                +" secretKey:"+this.secretKey
                +" nickname:"+this.nickname
                +" pwd:"+this.pwd
                +" useIM:"+this.useIM
                +" type:"+this.type
                +" phone:"+this.phone
                +" uuid:"+this.uuid
                +" macAddr:"+this.macAddr
                +" cpuNo:"+this.cpuNo
                +" diskNo:"+this.diskNo
                +" token:"+this.token;
    }
}
