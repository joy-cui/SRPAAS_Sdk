package org.suirui.srpaas.util;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.telephony.TelephonyManager;
import android.text.TextUtils;

public class NetworkUtil {

	public static final int NETWORK_TYPE_NONE = 0;
	public static final int NETWORK_TYPE_WIFI = 1;
	public static final int NETWORK_TYPE_MOBILE = 2;
	public static final int NETWORK_TYPE_WiMAX = 3;
	public static final int NETWORK_TYPE_ETHERNET = 4;
	public static final int NETWORK_TYPE_UNKNOWN = 5;

	public NetworkUtil() {
	}

	public static boolean hasDataNetwork(Context context) {
		if (context == null) {
			return false;
		} else {
			ConnectivityManager manager = (ConnectivityManager) context
					.getSystemService(Context.CONNECTIVITY_SERVICE);
			if (manager == null) {
				return false;
			} else {
				NetworkInfo netInf = null;

				try {
					netInf = manager.getActiveNetworkInfo();
				} catch (Exception e) {
					e.printStackTrace();
					return false;
				}

				if (netInf == null) {
					return false;
				} else {
					boolean connected = netInf.isConnected();
					if (connected
							&& netInf.getType() == ConnectivityManager.TYPE_MOBILE) {
						TelephonyManager telMgr = (TelephonyManager) context
								.getSystemService("phone");
						if (telMgr == null) {
							return false;
						}

						connected = telMgr.getDataState() == TelephonyManager.DATA_CONNECTED;
					}

					return connected;
				}
			}
		}
	}

	// public static final int TYPE_NONE = -1;
	// public static final int TYPE_MOBILE = 0;
	// public static final int TYPE_WIFI = 1;
	// public static final int TYPE_MOBILE_MMS = 2;
	// public static final int TYPE_MOBILE_SUPL = 3;
	// public static final int TYPE_MOBILE_DUN = 4;
	// public static final int TYPE_MOBILE_HIPRI = 5;
	// public static final int TYPE_WIMAX = 6;
	// public static final int TYPE_BLUETOOTH = 7;
	// public static final int TYPE_DUMMY = 8;
	// public static final int TYPE_ETHERNET = 9;
	// public static final int TYPE_MOBILE_FOTA = 10;
	// public static final int TYPE_MOBILE_IMS = 11;
	// public static final int TYPE_MOBILE_CBS = 12;
	// public static final int TYPE_WIFI_P2P = 13;
	// public static final int TYPE_MOBILE_IA = 14;
	// public static final int TYPE_PROXY = 16;
	public static int getDataNetworkType(Context context) {
		if (context == null) {
			return NETWORK_TYPE_UNKNOWN;
		} else {
			ConnectivityManager cm = (ConnectivityManager) context
					.getSystemService("connectivity");
			if (cm == null) {
				return NETWORK_TYPE_UNKNOWN;
			} else {
				NetworkInfo netInf = cm.getActiveNetworkInfo();
				if (netInf == null) {
					return NETWORK_TYPE_NONE;
				} else if (!netInf.isConnected()) {
					return NETWORK_TYPE_NONE;
				} else {
					switch (netInf.getType()) {
					case 0:
					case 2:
					case 3:
					case 4:
					case 5:
						TelephonyManager telMgr = (TelephonyManager) context
								.getSystemService("phone");
						if (telMgr.getDataState() != 2) {
							return NETWORK_TYPE_NONE;
						}

						return NETWORK_TYPE_MOBILE;
					case 1:
						return NETWORK_TYPE_WIFI;
					case 6:
						return NETWORK_TYPE_WiMAX;
					case 7:
					case 8:
					default:
						return NETWORK_TYPE_UNKNOWN;
					case 9:
						return NETWORK_TYPE_ETHERNET;
					}
				}
			}
		}
	}

}
