package org.suirui.srpaas.sdk.demo;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.text.TextUtils;

import com.suirui.srpaas.base.util.log.SRLog;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;

/**
 * Created by hh on 2018/4/21.
 */

public class NetworkUtil {
    private static final SRLog log = new SRLog(NetworkUtil.class.getName(), SRLog.DebugType.V);
    private static NetworkUtil instance = null;
    private Context mContext;

    public NetworkUtil(Context context) {
        mContext = context;
    }

    public static synchronized NetworkUtil getInstance(Context context) {
        if (instance == null) {
            instance = new NetworkUtil(context);
        }
        return instance;
    }

    public static boolean hasDataNetwork(Context context) {
        if(context == null) {
            return false;
        } else {
            ConnectivityManager manager = (ConnectivityManager) context
                    .getSystemService(Context.CONNECTIVITY_SERVICE);
            if(manager == null) {
                return false;
            } else {
                NetworkInfo netInf = null;

                try {
                    netInf = manager.getActiveNetworkInfo();
                } catch (Exception e) {
                    e.printStackTrace();
                    return false;
                }

                if(netInf == null) {
                    return false;
                } else {
                    boolean connected = netInf.isConnected();
                    return connected;
                }
            }
        }
    }

    /**
     * 判断以太网网络是否可用
     *
     * @param context
     * @return
     */
    public static boolean isEthernetConnected(Context context) {
        if (context != null) {
            ConnectivityManager mConnectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
            NetworkInfo mInternetNetWorkInfo = mConnectivityManager.getNetworkInfo(ConnectivityManager.TYPE_ETHERNET);
            boolean hasInternet = mInternetNetWorkInfo != null && mInternetNetWorkInfo.isConnected() && mInternetNetWorkInfo.isAvailable();
            return hasInternet;
        }
        return false;
    }
//
//    public void net(Context context){
//        // 获取以太网连接状态(DHCP IP)
//        EthernetManager mEthernetManager = (EthernetManager) context.getSystemService(Context.ET.ETHERNET_SERVICE);
//        EthernetDevInfo mEthernetDevInfo = mEthernetManager.getSavedEthConfig();
//        String etho_mode = mEthernetDevInfo.getConnectMode();  //得到连接模式  手动  DHCP
//        String IpAddress = mEthernetDevInfo.getIpAddress();  //得到ip地址
//        String NetMask = mEthernetDevInfo.getNetMask();  //得到掩码
//        String DNS = mEthernetDevInfo.getDnsAddr();  //得到DNS
//        String GateWay = mEthernetDevInfo.getRouteAddr();  //得到网关
////		Toast.makeText(this, etho_mode + IpAddress + NetMask + DNS + GateWay, Toast.LENGTH_LONG).show();
//        if(etho_mode.equals("manual")){
//            Log.i(TAG, "manual");
//        }else if(etho_mode.equals("dhcp")){
//            Log.i(TAG, "dhcp");
//            Toast.makeText(this, etho_mode + IpAddress + NetMask + DNS + GateWay, Toast.LENGTH_LONG).show();
//        }
//    }

    public boolean isWifiApOpen() {
        try {
            WifiManager manager = (WifiManager) mContext.getSystemService(Context.WIFI_SERVICE);
            //通过放射获取 getWifiApState()方法
            Method method = manager.getClass().getDeclaredMethod("getWifiApState");
            //调用getWifiApState() ，获取返回值
            int state = (int) method.invoke(manager);
            //通过放射获取 WIFI_AP的开启状态属性
            Field field = manager.getClass().getDeclaredField("WIFI_AP_STATE_ENABLED");
            //获取属性值
            int value = (int) field.get(manager);
            //判断是否开启
            if (state == value) {
                return true;
            } else {
                return false;
            }
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (NoSuchFieldException e) {
            e.printStackTrace();
        }
        return false;
    }



    public String getSSID() {
        boolean isOPen = isWifiApOpen();
        log.E("getSSID--:isOPen:"+isOPen);
        String ssid = "";
        try {
            WifiManager manager = (WifiManager) mContext.getSystemService(Context.WIFI_SERVICE);
            //拿到getWifiApConfiguration()方法
            Method method = manager.getClass().getDeclaredMethod("getWifiApConfiguration");
            //调用getWifiApConfiguration()方法，获取到 热点的WifiConfiguration
            WifiConfiguration configuration = (WifiConfiguration) method.invoke(manager);
            ssid = configuration.SSID;
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }
        return ssid;
    }

    public String getIpAddress(){
        NetworkInfo info = ((ConnectivityManager) mContext
                .getSystemService(Context.CONNECTIVITY_SERVICE)).getActiveNetworkInfo();
        if (info != null && info.isConnected()) {
            // 3/4g网络
            if (info.getType() == ConnectivityManager.TYPE_MOBILE) {
                try {
                    for (Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements(); ) {
                        NetworkInterface intf = en.nextElement();
                        for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements(); ) {
                            InetAddress inetAddress = enumIpAddr.nextElement();
                            if (!inetAddress.isLoopbackAddress() && inetAddress instanceof Inet4Address) {
                                return inetAddress.getHostAddress();
                            }
                        }
                    }
                } catch (SocketException e) {
                    e.printStackTrace();
                }

            } else if (info.getType() == ConnectivityManager.TYPE_WIFI) {
                //  wifi网络
                WifiManager wifiManager = (WifiManager) mContext.getSystemService(Context.WIFI_SERVICE);
                WifiInfo wifiInfo = wifiManager.getConnectionInfo();
                String ipAddress = intIP2StringIP(wifiInfo.getIpAddress());
                return ipAddress;
            }  else if (info.getType() == ConnectivityManager.TYPE_ETHERNET){
                // 有限网络
                return getLocalIp();
            }
        }
        return null;
    }


    public String getMac() {

        String strMac = "";

        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.M) {
            log.E("=====6.0以下");
//            strMac = MacUtil.getLocalMacAddressFromWifiInfo(context);
            strMac = MacUtil.getMacAddressFromIp(getIpAddress());
        } else if (Build.VERSION.SDK_INT < Build.VERSION_CODES.N
                && Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            log.E("=====6.0以上7.0以下");
            strMac = MacUtil.getMacAddress(mContext);
        } else if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
            log.E("=====7.0以上");
            if (!TextUtils.isEmpty(MacUtil.getMacAddress())) {
                log.E("=====7.0以上1");
                strMac = MacUtil.getMacAddress();
            } else if (!TextUtils.isEmpty(MacUtil.getMachineHardwareAddress())) {
                log.E("=====7.0以上2");
                strMac = MacUtil.getMachineHardwareAddress();
            } else {
                log.E("=====7.0以上3");
                strMac = MacUtil.getLocalMacAddressFromBusybox();
            }
        }
        log.E("====：strMac：" + strMac);
        return strMac;
    }


    private String intIP2StringIP(int ip) {
        return (ip & 0xFF) + "." +
                ((ip >> 8) & 0xFF) + "." +
                ((ip >> 16) & 0xFF) + "." +
                (ip >> 24 & 0xFF);
    }


    // 获取有限网IP
    private String getLocalIp() {
        try {
            for (Enumeration<NetworkInterface> en = NetworkInterface
                    .getNetworkInterfaces(); en.hasMoreElements(); ) {
                NetworkInterface intf = en.nextElement();
                for (Enumeration<InetAddress> enumIpAddr = intf
                        .getInetAddresses(); enumIpAddr.hasMoreElements(); ) {
                    InetAddress inetAddress = enumIpAddr.nextElement();
                    if (!inetAddress.isLoopbackAddress()
                            && inetAddress instanceof Inet4Address) {
                        return inetAddress.getHostAddress();
                    }
                }
            }
        } catch (SocketException ex) {

        }
        return "0.0.0.0";

    }
}
