package org.suirui.srpaas.sdk;

public class AppSDKNotInitializedException extends RuntimeException {
    private static final long serialVersionUID = 1L;

    public AppSDKNotInitializedException() {
    }

    public AppSDKNotInitializedException(String detailMessage, Throwable throwable) {
        super(detailMessage, throwable);
    }

    public AppSDKNotInitializedException(String detailMessage) {
        super(detailMessage);
    }

    public AppSDKNotInitializedException(Throwable throwable) {
        super(throwable);
    }
}