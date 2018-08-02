package org.suirui.srpaas.sdk;

import org.suirui.srpaas.entry.DelParticipant;
import org.suirui.srpaas.entry.OnliveInfo;
import org.suirui.srpaas.entry.SRMediaPScreenInfo;
import org.suirui.srpaas.entry.SendMessageTerm;

import java.util.List;

/**
 * 会议控制相关的接口 (会议控制服务类，提供比如举手，主持人权限转移，静音等)
 *
 * @author cui.li
 */
public interface MeetingControlService {
    public void addMeetingControlServiceListener(
            MeetingControlServiceListener listener);

    // 静音
    int muteAudio(int term_id);

    // 取消静音
    int unMuteAudio(int unterm_id);

    /**
     * 静音/解除静音除主持人以外的参会人
     *
     * @param isMute
     * @return
     */
    int muteAllAudio(boolean isMute);

    /**
     * 举手
     *
     * @param isHandUp false 放下 true 举手
     * @return
     */
    int handUp(boolean isHandUp);

    /**
     * 主持人踢人
     *
     * @param dropId
     * @return
     */
    int removeTerminal(int dropId);

    /**
     * 支持人权限转移(只有支持人有这个权限)
     *
     * @param newMasterId
     * @return
     */
    int setMasterId(int newMasterId);

    /**
     * 改名
     *
     * @param name
     * @return
     */
    int changeName(String name);

    /**
     * 设置焦点视频
     *
     * @param lockId
     * @param isLock
     * @return
     */
    int lockOrUnLock(int lockId, boolean isLock);

    /**
     * 获取发送数据统计信息
     */
    int getSendStreamInfo(int interval);

    /**
     * 获取接收数据统计信息
     */
    int getRecvStreamInfo(int interval);

    /**
     * 测试按钮，写文件
     *
     * @param cmdMsg
     * @return
     */
    int SetUserCmdToEngine(String[] cmdMsg);

    /*
    * 设置当前扬声器的音量
     */
    int SetOutputDeviceVolume(int volume);

    /**
     * 主持人设置强制静音
     *
     * @param isforcemute
     * @return
     */
    int setForceMuteAudio(boolean isforcemute);

    /**
     * 设置锁定会议
     *
     * @param islock
     * @return
     */
    int setLockOrUnLockConf(boolean islock);

    /**
     * 锁定会议后，删除与会人
     *
     * @param participantList
     * @return
     */
    int delParticipants(List<DelParticipant> participantList);

    /**
     * 重启音频设备
     *
     * @return
     */
    int resetAudioDevice();

    /**
     * 开始会议录制
     *
     * @return
     */
    int startMeetingRecord(int channelid, List<SRMediaPScreenInfo> srMediaPScreenInfoList);

    /**
     * 停止会议录制
     *
     * @return
     */
    int stopMeetingRecord(int channelid, List<SRMediaPScreenInfo> srMediaPScreenInfoList);

    /**
     * 开始直播
     *
     * @param onliveInfo
     * @param srMediaPScreenInfoList
     * @return
     */
    int startMeetingLive(OnliveInfo onliveInfo, int channelid,List<SRMediaPScreenInfo> srMediaPScreenInfoList);

    /**
     * 停止直播
     *
     * @param srMediaPScreenInfoList
     * @return
     */
    int stopMeetingLive(int channelid,List<SRMediaPScreenInfo> srMediaPScreenInfoList);

    /**
     * 聊天发送消息
     *
     * @param termIdList
     * @param message
     * @return
     */
    int sendConfMessage(List<SendMessageTerm> termIdList, String message);
}
