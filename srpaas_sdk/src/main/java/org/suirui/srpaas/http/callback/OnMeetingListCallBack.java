package org.suirui.srpaas.http.callback;

import org.suirui.srpaas.entry.ConferenceInfo;
import org.suirui.srpaas.http.bean.MeetingListBean;

import java.util.List;

import okhttp3.Call;

/**
 * Created by cui on 2018/4/8.
 */

public abstract class OnMeetingListCallBack {
    public void onError(int code,String msg) {

    }
    public void onSuccess(List<ConferenceInfo> conferenceInfoList){

    }
}
