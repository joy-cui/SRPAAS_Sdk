package org.suirui.srpaas.http.callback;

import org.suirui.srpaas.entry.MeetDetailInfo;

/**
 * Created by cui on 2018/4/13.
 */

public interface OnMeetingDetailInfoCallBack {
    void onError(int code,String msg);

    /**
     * 会议详情
     * @param meetDetailInfo
     */
    void onSuccess(MeetDetailInfo meetDetailInfo);
}
