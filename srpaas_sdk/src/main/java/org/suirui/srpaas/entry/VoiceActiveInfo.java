package org.suirui.srpaas.entry;

import java.io.Serializable;

public class VoiceActiveInfo implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int talk_id;
	private int energy;

	public int getTalk_id() {
		return talk_id;
	}

	public void setTalk_id(int talk_id) {
		this.talk_id = talk_id;
	}

	public int getEnergy() {
		return energy;
	}

	public void setEnergy(int energy) {
		this.energy = energy;
	}

}
