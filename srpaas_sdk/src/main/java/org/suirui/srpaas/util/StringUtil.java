package org.suirui.srpaas.util;

import android.text.TextPaint;
import android.util.Log;

import org.suirui.srpaas.entry.McAdress;

import java.io.UnsupportedEncodingException;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

public class StringUtil {
	private static final String TAG = StringUtil.class.getSimpleName();
	public static final int MID_FORMAT_TYPE_DEFAULT = 0;
	public static final int MID_FORMAT_TYPE_34X = 1;
	public static final int MID_FORMAT_TYPE_43X = 2;

	public StringUtil() {
	}

	// 将adrees转数组
	public static String[] stringToArray(String value) {
		String[] array = new String[2];
		if (!isEmptyOrNull(value)) {
			String[] replay = value.split(":");
			if (replay != null && replay.length > 1) {
				array[0] = replay[0];
				array[1] = replay[1];
			}
		}
		return array;
	}

	public static List<McAdress> stringToList(String value, String split) {
		List<McAdress> mcAdressList = null;
		McAdress mcAdress = null;
		if (!isEmptyOrNull(value)) {
			String[] replay = value.split(split);
			if (replay != null) {
				int lenght = replay.length;
				for (int i = 0; i < lenght; i++) {
					if (mcAdressList == null)
						mcAdressList = new ArrayList<McAdress>();
					mcAdress = new McAdress();
					mcAdress.setAddress(replay[i]);
					mcAdressList.add(mcAdress);
				}
			}

		}
		return mcAdressList;
	}

	public static boolean isEmptyOrNull(String str) {
		// return str == null || str.length() == 0;
		if (str == null || str.equals("") || str == "NULL" || str.length() == 0 || str == "null") {
			return true;
		} else {
			return false;
		}

	}

	public static boolean isSameString(String str1, String str2) {
		return str1 == null && str2 == null ? true : (str1 != null
				&& str2 == null ? false : (str1 == null && str2 != null ? false
				: (str1 != null && str2 != null ? str1.equals(str2) : false)));
	}

	public static Map<String, String> parseNameValues(String str) {
		if (str == null) {
			return null;
		} else {
			HashMap map = new HashMap();
			String[] pairs = str.split("\\s*;\\s*");
			String[] var6 = pairs;
			int var5 = pairs.length;

			for (int var4 = 0; var4 < var5; ++var4) {
				String pair = var6[var4];
				String[] parts = pair.split("=");
				if (parts.length == 2) {
					map.put(parts[0], parts[1]);
				}
			}

			return map;
		}
	}

	public static Object bytes2String(byte[] data) {
		String str = null;

		try {
			str = new String(data, "UTF-8");
		} catch (UnsupportedEncodingException var3) {
			Log.w(TAG, "bytes2String failed!", var3);
		}

		return str;
	}

	public static String formatConfNumber(String confNumber) {
		return formatConfNumber(confNumber, (int) 0);
	}

	public static String formatConfNumber(String confNumber, int formatType) {
		return formatConfNumber(confNumber, '-', formatType);
	}

	public static String formatConfNumber(String confNumber, char sectionChar) {
		return formatConfNumber(confNumber, sectionChar, 0);
	}

	public static String formatConfNumber(String confNumber, char sectionChar,
			int formatType) {
		StringBuilder str = new StringBuilder(confNumber);

		while (str.length() < 9) {
			str.insert(0, '0');
		}

		switch (formatType) {
		case 0:
		default:
			if (str.length() <= 10) {
				str.insert(6, sectionChar);
				str.insert(3, sectionChar);
			} else {
				str.insert(7, sectionChar);
				str.insert(3, sectionChar);
			}
			break;
		case 1:
			str.insert(7, sectionChar);
			str.insert(3, sectionChar);
			break;
		case 2:
			str.insert(7, sectionChar);
			str.insert(4, sectionChar);
		}

		return str.toString();
	}

	public static String formatConfNumber(long confNumber) {
		return formatConfNumber(confNumber, (int) 0);
	}

	public static String formatConfNumber(long confNumber, int formatType) {
		return formatConfNumber(confNumber, '-', formatType);
	}

	public static String formatConfNumber(long confNumber, char sectionChar) {
		return formatConfNumber(confNumber, sectionChar, 0);
	}

	public static String formatConfNumber(long confNumber, char sectionChar,
			int formatType) {
		return formatConfNumber(String.valueOf(confNumber), sectionChar,
				formatType);
	}

	public static String ellipseString(String str, int maxWidth, TextPaint paint) {
		while (paint.measureText(str) > (float) maxWidth) {
			if (str.length() <= 3) {
				return str;
			}

			str = str.substring(0, str.length() - 4);
			str = str + "...";
		}

		return str;
	}

	public static boolean isValidEmailAddress(String email) {
		return email == null ? false
				: email.matches("([a-zA-Z0-9_]|\\-|\\.|\\+)+@(([a-zA-Z0-9_]|\\-)+\\.)+[a-zA-Z]{2,}");
	}

	public static boolean containsAsianCharacter(String str) {
		if (str == null) {
			return false;
		} else {
			try {
				if (str.length() != str.getBytes("UTF-8").length) {
					return true;
				}
			} catch (UnsupportedEncodingException var2) {
				var2.printStackTrace();
			}

			return false;
		}
	}

	public static boolean endsWithAsianCharacter(String str) {
		return containsAsianCharacter(str.substring(str.length() - 1));
	}

	public static boolean startsWithAsianCharacter(String str) {
		return containsAsianCharacter(str.substring(0, 1));
	}

	public static String formatPersonName(String firstName, String lastName) {
		return formatPersonName(firstName, lastName, (String) null);
	}

	public static String formatPersonName(String firstName, String lastName,
			String regionCode) {
		String first = firstName == null ? "" : firstName;
		String last = lastName == null ? "" : lastName;
		first = first.trim();
		last = last.trim();
		return last.length() == 0 ? first
				: (first.length() == 0 ? last
						: (Locale.CHINA.getCountry().equalsIgnoreCase(
								regionCode) ? (!containsAsianCharacter(first)
								&& !containsAsianCharacter(last) ? first + " "
								+ last : (!endsWithAsianCharacter(lastName)
								&& !startsWithAsianCharacter(firstName) ? last
								+ " " + first : last + first)) : first + " "
								+ last));
	}

	public static String safeString(String str) {
		return str == null ? "" : str;
	}

	public static boolean isAllAssii(String s) {
		char[] array = s.toCharArray();
		char[] var5 = array;
		int var4 = array.length;

		for (int var3 = 0; var3 < var4; ++var3) {
			char c = var5[var3];
			if (c < 0 || c > 255) {
				return false;
			}
		}

		return true;
	}

	/**
	 * string 转byte
	 * 
	 * @param value
	 * @return
	 */
	public static byte[] getStringToByte(String value) {
		if (value != null && !value.equals("")) {
			byte[] responseBufferP = null;
			responseBufferP = value.trim().getBytes();
			return responseBufferP;
		} else {
			return null;
		}
	}

	/**
	 * 有符号转无符号
	 * 
	 * @param mcaddr
	 * @return
	 */
	public static final String readUnsignedLong(String mcaddr) {
		if (mcaddr != null && !mcaddr.equals("")) {
			long value = Long.parseLong(mcaddr);
			BigDecimal toValue;
			if (value >= 0) {
				toValue = new BigDecimal(value);
			} else {
				long lowValue = value & 0x7fffffffffffffffL;
				toValue = BigDecimal.valueOf(lowValue)
						.add(BigDecimal.valueOf(Long.MAX_VALUE))
						.add(BigDecimal.valueOf(1));
			}
			if (toValue == null)
				return "";
			return toValue.toString();
		} else {
			return "";
		}

	}

	public static final long readLong(String value) {
		if (!isEmptyOrNull(value)) {
			long longValue = Long.parseLong(value);
			return longValue;
		}
		return 0;
	}

	public static int StringToInt(String str) {
		int value = 0;
		if (str != null && !str.equals("")) {
			try {
				value = Integer.valueOf(str);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		return value;
	}

	public static boolean StringToBoolean(String str) {
		int _value = StringToInt(str);
		return (_value == 1) ? true : false;
	}
}
