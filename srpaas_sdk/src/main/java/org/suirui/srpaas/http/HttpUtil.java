package org.suirui.srpaas.http;

import com.suirui.srpaas.base.util.log.SRLog;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.suirui.srpaas.entry.ConferenceInfo;
import org.suirui.srpaas.entry.MeetDetailInfo;
import org.suirui.srpaas.http.bean.MeetDetailInfoBean;
import org.suirui.srpaas.http.bean.MeetingListBean;

import java.util.ArrayList;
import java.util.List;

/**
 * 网络连接
 *
 * @author cui.li
 */
public class HttpUtil {
    public static String  HTTP_SUCCESS_CODE="200";
    public static class HttpError{
        public static final String http_meet_error="入会失败";
        public static final String http_no_meet_error="会议不存在";
        public static final String http_server_error="连接服务器失败";
        public static final String http_login_error="登录失败";
        public static final String http_no_login_error="账号不存在";
        public static final String http_register_error="注册失败";
        public static final String http_no_register_error="注册账号非法";
        public static final String http_server_field_error="服务器字段错误";
        public static final String http_invite_error = "邀请失败";
        public static final String http_get_meetinglist_error = "获取会议列表失败";
    }

    private static final SRLog log = new SRLog(HttpUtil.class.getSimpleName());

    public static String getJsonStr(JSONObject obj, String objValue) {
        JSONArray personList = null;
        String str = "";
        try {
            personList = obj.getJSONArray(objValue);
            if (personList != null) {
                for (int i = 0; i < personList.length(); i++) {
                    if (i == 0) {
                        str = personList.getString(i);
                    } else {
                        str = str + "/" + personList.getString(i);
                    }
                }
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return str;
    }

    public static String getArrayStr(String[] objValue) {
        String str = "";
        try {

            if (objValue != null) {
                for (int i = 0; i < objValue.length; i++) {
                    if (i == 0) {
                        str = objValue[i];
                    } else {
                        str = str + "/" + objValue[i];
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return str;
    }

    public static List<ConferenceInfo> setMeetingList(MeetingListBean meetingListBean){
        List<ConferenceInfo> list=null;
        ConferenceInfo conferenceInfo=null;

        if(meetingListBean!=null){
            if(meetingListBean.data.list!=null){
                for (MeetingListBean.Conference conference:meetingListBean.data.list) {
                    conferenceInfo=new ConferenceInfo();
//                    log.E("setMeetingList :"+conference.confId+"  : "+conference.subject+"  : "+conference.confName);

                   if(conference.confId!=null) conferenceInfo.setConfId(conference.confId);
                    if(conference.confName!=null)conferenceInfo.setConfName(conference.confName);

                    if(conference.subject!=null)conferenceInfo.setSubject(conference.subject) ;

                    if(conference.confPwd!=null)conferenceInfo.setConfPwd(conference.confPwd) ;

                    if(conference.suid!=null)conferenceInfo.setSuid(conference.suid);

                    if(conference.nickname!=null)conferenceInfo.setNickname(conference.nickname) ;
                    if(conference.startTime!=null)conferenceInfo.setStartTime(conference.startTime) ;

                    if(conference.endTime!=null)conferenceInfo.setEndTime(conference.endTime) ;

                    if(conference.confType!=null)conferenceInfo.setConfType(conference.confType) ;

                    if(conference.startType!=null) conferenceInfo.setStartType(conference.startType);

                    if(conference.anonymous!=null)conferenceInfo.setAnonymous(conference.anonymous) ;

                    if(conference.maxterm!=null)conferenceInfo.setMaxterm(conference.maxterm) ;

                    if(conference.videoenable!=null)conferenceInfo.setVideoenable(conference.videoenable) ;
                    if(conference.audioenable!=null)conferenceInfo.setAudioenable(conference.audioenable) ;

                    if(conference.permanentenable!=null)conferenceInfo.setPermanentenable(conference.permanentenable) ;

                    if(conference.ctrluserid!=null)conferenceInfo.setCtrluserid(conference.ctrluserid);

                    if(conference.ctrlpwd!=null)conferenceInfo.setCtrlpwd(conference.ctrlpwd);
                    if(conference.hasStarted!=null){
                        conferenceInfo.setHasStarted(conference.hasStarted);
                    }

                    if(list==null){
                        list=new ArrayList<ConferenceInfo>();
                    }
                    list.add(conferenceInfo);

                }


            }

        }

        return list;

    }

    /*
     * 会议详情
     * @param MeetDetailInfoBean
     */
    public static MeetDetailInfo setMeetDetailInfo(MeetDetailInfoBean meetDetailInfoBean){
        MeetDetailInfo meetDetailInfo=null;
        if(meetDetailInfoBean!=null && meetDetailInfoBean.data!=null){
            meetDetailInfo=new MeetDetailInfo();
//            log.E("MeetDetailInfo confId:"+meetDetailInfoBean.data.toString());
            meetDetailInfo.setChairman(meetDetailInfoBean.data.chairman);
            meetDetailInfo.setVideoenable(meetDetailInfoBean.data.videoenable);
            meetDetailInfo.setSubject(meetDetailInfoBean.data.subject);
            meetDetailInfo.setEncryptalg(meetDetailInfoBean.data.encryptalg);
            meetDetailInfo.setEndTime(meetDetailInfoBean.data.endTime);
            meetDetailInfo.setConfType(meetDetailInfoBean.data.confType);
            meetDetailInfo.setCreatetime(meetDetailInfoBean.data.createtime);
            meetDetailInfo.setStartTime(meetDetailInfoBean.data.startTime);
            meetDetailInfo.setAnonymous(meetDetailInfoBean.data.anonymous);
            meetDetailInfo.setChairman(meetDetailInfoBean.data.chairman);
            meetDetailInfo.setPermanentenable(meetDetailInfoBean.data.permanentenable);
            meetDetailInfo.setSuid(meetDetailInfoBean.data.suid);
            meetDetailInfo.setCtrlpwd(meetDetailInfoBean.data.ctrlpwd);
            meetDetailInfo.setMsgtype(meetDetailInfoBean.data.msgtype);
            meetDetailInfo.setAudioenable(meetDetailInfoBean.data.audioenable);
            meetDetailInfo.setNickname(meetDetailInfoBean.data.nickname);
            meetDetailInfo.setConfPwd(meetDetailInfoBean.data.confPwd);
            meetDetailInfo.setCameraautoenable(meetDetailInfoBean.data.camaraautoenable);
            meetDetailInfo.setHasStarted(meetDetailInfoBean.data.hasStarted);
            meetDetailInfo.setStartType(meetDetailInfoBean.data.startType);
            meetDetailInfo.setConfId(meetDetailInfoBean.data.confId);
            meetDetailInfo.setCtrluserid(meetDetailInfoBean.data.ctrluserid);
            meetDetailInfo.setConfName(meetDetailInfoBean.data.confName);
            meetDetailInfo.setMicautoenable(meetDetailInfoBean.data.micautoenable);
           List<MeetDetailInfo.Participantes> rooms=getParticipantList(meetDetailInfoBean.data.rooms);
            List<MeetDetailInfo.Participantes> participantes=getParticipantList(meetDetailInfoBean.data.participates);
          if(rooms!=null){
              meetDetailInfo.setRooms(rooms);
          }
          if(participantes!=null){
              meetDetailInfo.setParticipates(participantes);
          }


        }else{
            log.E("MeetDetailInfo....null");
        }
        return meetDetailInfo;

    }

    private static List<MeetDetailInfo.Participantes> getParticipantList(List<MeetDetailInfoBean.Participantes> participantes){
            List<MeetDetailInfo.Participantes> list=null;
             MeetDetailInfo.Participantes participanteInfo=null;
            if(participantes!=null){
            for(MeetDetailInfoBean.Participantes rooms:participantes) {
                if (rooms != null) {
                    participanteInfo=new MeetDetailInfo.Participantes();
                    participanteInfo.setSuid(rooms.suid);
                    participanteInfo.setNickname(rooms.nickname);
                    participanteInfo.setThirduid(rooms.thirduid);
                    participanteInfo.setType(rooms.type);
                    if(list==null){
                        list=new ArrayList<MeetDetailInfo.Participantes>();
                    }
                    if(participanteInfo!=null){
                        list.add(participanteInfo);

                    }


                }
            }
          }
            return list;
    }

}


