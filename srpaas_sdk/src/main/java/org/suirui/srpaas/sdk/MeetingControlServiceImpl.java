package org.suirui.srpaas.sdk;

import com.suirui.srpaas.base.util.log.SRLog;

import org.suirui.srpaas.entry.DelParticipant;
import org.suirui.srpaas.entry.OnliveInfo;
import org.suirui.srpaas.entry.SRMediaPScreenInfo;
import org.suirui.srpaas.entry.SendMessageTerm;
import org.suirui.srpaas.jni.JniNative;

import java.util.List;

/**
 * 会议控制相关的接口实现(会议控制服务类，提供比如举手，主持人权限转移，静音等)
 *
 * @author cui.li
 */
public class MeetingControlServiceImpl implements MeetingControlService {
    private static final SRLog log = new SRLog(MeetingControlServiceImpl.class.getName());
    private MeetingControlServiceListener mListener;

    public MeetingControlServiceImpl() {
    }

    @Override
    public void addMeetingControlServiceListener(MeetingControlServiceListener listener) {
        this.mListener = listener;
    }

    @Override
    public int muteAudio(int term_id) {
        return JniNative.muteAudio(term_id);
    }

    @Override
    public int unMuteAudio(int unterm_id) {
        return JniNative.unMuteAudio(unterm_id);
    }

    @Override
    public int muteAllAudio(boolean isMute) {
        return JniNative.MuteAudioAllTerm(isMute);
    }

    @Override
    public int handUp(boolean isHandUp) {
        return JniNative.requestHandUp(isHandUp);
    }

    @Override
    public int removeTerminal(int dropId) {
        return JniNative.requestRemoveTerminal(dropId);
    }

    @Override
    public int setMasterId(int newMasterId) {
        return JniNative.setMasterId(newMasterId);
    }

    @Override
    public int changeName(String name) {
        return JniNative.changeName(name);
    }

    @Override
    public int lockOrUnLock(int lockId, boolean isLock) {
        return JniNative.lockOrUnLockVideo(lockId, isLock);
    }

    @Override
    public int getSendStreamInfo(int interval) {
        return JniNative.getSendStreamInfoIndication(interval);
    }

    @Override
    public int getRecvStreamInfo(int interval) {
        return JniNative.getRecvStreamInfoIndication(interval);
    }

    @Override
    public int SetUserCmdToEngine(String[] cmdMsg) {
        return JniNative.SRSetUserCmdToEngine(cmdMsg);
    }

    @Override
    public int SetOutputDeviceVolume(int volume) {
        return JniNative.SRSetOutputDeviceVolume(volume);
    }

    @Override
    public int setForceMuteAudio(boolean isforcemute) {
        return JniNative.SRSetForceMuteAudio(1, isforcemute);
    }

    @Override
    public int setLockOrUnLockConf(boolean islock) {
        return JniNative.SRLockConf(islock);
    }

    @Override
    public int delParticipants(List<DelParticipant> participantList) {
        return JniNative.SRDelParticipants(participantList);
    }

    @Override
    public int resetAudioDevice() {
        return JniNative.SRresetAudioDevice();
    }

    @Override
    public int startMeetingRecord(int channelid, List<SRMediaPScreenInfo> srMediaPScreenInfoList) {
        return JniNative.StartMeetingRecord(channelid,srMediaPScreenInfoList);
    }

    @Override
    public int stopMeetingRecord(int channelid, List<SRMediaPScreenInfo> srMediaPScreenInfoList) {
        return JniNative.StopMeetingRecord(channelid,srMediaPScreenInfoList);
    }

    @Override
    public int startMeetingLive(OnliveInfo onliveInfo, int channelid,List<SRMediaPScreenInfo> srMediaPScreenInfoList) {
        return JniNative.StartMeetingLive(onliveInfo,channelid, srMediaPScreenInfoList);
    }

    @Override
    public int stopMeetingLive(int channelid,List<SRMediaPScreenInfo> srMediaPScreenInfoList) {
        return JniNative.StopMeetingLive(channelid,srMediaPScreenInfoList);
    }

    @Override
    public int sendConfMessage(List<SendMessageTerm> termIdList, String message) {
        return JniNative.sendConfMessage(termIdList, message);
    }
}
