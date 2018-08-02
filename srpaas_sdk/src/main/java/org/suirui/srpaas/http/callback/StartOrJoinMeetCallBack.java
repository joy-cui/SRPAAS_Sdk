package org.suirui.srpaas.http.callback;

import org.suirui.srpaas.entry.MeetingInfo;

import okhttp3.Call;

/**
 * Created by cui.li on 2017/4/6.
 */

public abstract class StartOrJoinMeetCallBack {
    public void onStartOrJoinMeetSuccess(MeetingInfo meetingInfo) {

    }

    public void onError(int errorCode, String msg) {

    }

    public void  onError(Call call, Exception e, int i){

    }
}
