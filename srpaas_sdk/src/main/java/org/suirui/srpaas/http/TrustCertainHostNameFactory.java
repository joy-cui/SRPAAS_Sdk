package org.suirui.srpaas.http;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.security.KeyManagementException;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.UnrecoverableKeyException;
import java.security.cert.Certificate;
import java.security.cert.CertificateFactory;

import org.apache.http.conn.ssl.SSLSocketFactory;

import android.content.Context;

public class TrustCertainHostNameFactory extends SSLSocketFactory {

	private static TrustCertainHostNameFactory mInstance;

	public TrustCertainHostNameFactory(KeyStore truststore)
			throws NoSuchAlgorithmException, KeyManagementException,
			KeyStoreException, UnrecoverableKeyException {
		super(truststore);
	}

	public static TrustCertainHostNameFactory getDefault(Context context) {
		KeyStore keystore = null;
		try {
			CertificateFactory cf = CertificateFactory.getInstance("X.509");
			Certificate ca = null;
			if (context != null) {
				InputStream in;
				in = context.getAssets().open("load-der.crt"); // 打开证书
				ca = cf.generateCertificate(in);
			}

			keystore = KeyStore.getInstance(KeyStore.getDefaultType());
			keystore.load(null, null);
			if (ca != null)
				keystore.setCertificateEntry("ca", ca);

			if (null == mInstance) {
				mInstance = new TrustCertainHostNameFactory(keystore);
			}
		} catch (Exception e) {

		}
		return mInstance;
	}

	@Override
	public Socket createSocket() throws IOException {
		return super.createSocket();
	}

	@Override
	public Socket createSocket(Socket socket, String host, int port,
			boolean autoClose) throws IOException, UnknownHostException {
		return super.createSocket(socket, host, port, autoClose);
	}

}
