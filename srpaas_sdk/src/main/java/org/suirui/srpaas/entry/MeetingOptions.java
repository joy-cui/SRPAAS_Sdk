package org.suirui.srpaas.entry;

/**
 * 会议的类型(提供第三方使用)
 * 
 * @author cui.li
 * 
 */
public class MeetingOptions {
	private String m_confType;// 会议类型（1：传统会议 2：直播会议)
	private String m_startType;// 开启方式（1:定点开启 2:有人进入开启 3: 管理员进入开启）



	public String getM_confType() {
		return m_confType;
	}

	public void setM_confType(String m_confType) {
		this.m_confType = m_confType;
	}

	public String getM_startType() {
		return m_startType;
	}

	public void setM_startType(String m_startType) {
		this.m_startType = m_startType;
	}
}
