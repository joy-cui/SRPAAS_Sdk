package org.suirui.srpaas.jni;

import android.util.Log;

/**
 * 调用so崩溃
 * 
 * @author cui.li
 * 
 */
public class ThrowJNIException extends Exception {
	private static final long serialVersionUID = 1L;

	ThrowJNIException() {
		super();
		Log.i("", "ThrowJNIException................");
	}

	ThrowJNIException(String reason) {
		super(reason);
		Log.i("", "ThrowJNIException.............reason..." + reason);
	}

}
