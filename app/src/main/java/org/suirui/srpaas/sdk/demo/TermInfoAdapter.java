package org.suirui.srpaas.sdk.demo;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.suirui.srpaas.base.util.log.SRLog;

import org.suirui.srpaas.entry.TermInfo;
import org.suirui.srpaas.sdk.MeetingControlService;
import org.suirui.srpaas.sdk.MeetingService;
import org.suirui.srpaas.sdk.SRPaas;

import java.util.ArrayList;
import java.util.List;

/**
 * @authordingna
 * @date2017-01-06
 **/
public class TermInfoAdapter extends BaseAdapter {
    static SRLog log = new SRLog(TermInfoAdapter.class.getName());
    private Context context;
    private List<TermInfo> termInfoList;
    private MeetingService meetingService;
    private TextView test_sdk_lib;
    private int masterid = 0;
    private boolean isLock = false;
    private MeetingControlService meetingControlService;
    private int currentTermId = 0;

    public TermInfoAdapter(Context context, List<TermInfo> term_list, MeetingService meetingService, MeetingControlService meetingControlService, TextView test_sdk_lib, int masterid, int currentTermId) {
        this.context = context;
        this.termInfoList = term_list;
        this.meetingService = meetingService;
        this.test_sdk_lib = test_sdk_lib;
        this.masterid = masterid;
        this.meetingControlService = meetingControlService;
        this.currentTermId = currentTermId;
    }

    @Override
    public int getCount() {
        if (termInfoList == null || termInfoList.size() <= 0)
            return 0;
        return termInfoList.size();
    }

    @Override
    public Object getItem(int position) {
        return termInfoList.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    public void setMasterId(int masterId) {
        this.masterid = masterId;
    }

    @Override
    public View getView(final int position, View view, ViewGroup parent) {
        ViewHolder holder;
        if (view == null) {
            view = LayoutInflater.from(context).inflate(R.layout.activity_main, null);
            holder = new ViewHolder();
            holder.termName = (TextView) view.findViewById(R.id.termName);
            holder.termID = (TextView) view.findViewById(R.id.termid);
            holder.termItem = (LinearLayout) view.findViewById(R.id.termItem);
            view.setTag(holder);
        } else {
            holder = (ViewHolder) view.getTag();
        }
        if (termInfoList != null) {
            TermInfo termInfo = termInfoList.get(position);
            holder.termName.setText(String.valueOf(termInfo.getTername()));
            holder.termID.setText(String.valueOf(termInfo.getTermid()));
        }
        holder.termItem.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                TermInfo termInfo = termInfoList.get(position);
                selectVideoRemote(termInfo);

                //设置焦点视屏（ok）
//                if (currentTermId == masterid) {
//                    if (!isLock) {
//                        meetingControlService.lockOrUnLock(termInfo.getTermid(), true);
//                        isLock = true;
//                    } else {
//                        meetingControlService.lockOrUnLock(termInfo.getTermid(), false);
//                        isLock = false;
//                    }
//                } else {
//                    test_sdk_lib.setText("只有主持人才能锁定或取消锁定视频");
//                }

                //主持人权限转移
//                if (currentTermId == masterid) {
//                    meetingControlService.setMasterId(termInfo.getTermid());
//                } else {
//                    test_sdk_lib.setText("只有主持人才能转移主持人权限");
//                }
            }
        });
        return view;
    }

    private void selectVideoRemote(TermInfo termInfos) {
        test_sdk_lib.setText("正在接收" + termInfos.getTername() + "的视频流....");
        List<TermInfo> termList = new ArrayList<TermInfo>();
        TermInfo termInfo = new TermInfo();
        termInfo.setTermid(termInfos.getTermid());
        termInfo
                .setVideoType(SRPaas.VideoType.SR_CFG_VIDEO_SIZE_720P
                        .getValue());
        termList.add(termInfo);
        meetingService.requestSelectRemoteVideo(termList);
    }

    class ViewHolder {
        TextView termName;
        TextView termID;
        LinearLayout termItem;
    }
}
