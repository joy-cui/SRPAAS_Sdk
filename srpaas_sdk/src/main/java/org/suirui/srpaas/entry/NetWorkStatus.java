package org.suirui.srpaas.entry;

/**
 * @authordingna
 * @date2018-04-02
 **/
public class NetWorkStatus {
    private int network_upload_status;//网络上行方向的状况
    private int network_download_status;//网络下行方向的状况

    public NetWorkStatus() {
    }

    public NetWorkStatus(int upload_state, int download_state) {
        this.network_upload_status = upload_state;
        this.network_download_status = download_state;
    }

    public int getNetwork_upload_status() {
        return network_upload_status;
    }

    public void setNetwork_upload_status(int network_upload_status) {
        this.network_upload_status = network_upload_status;
    }

    public int getNetwork_download_status() {
        return network_download_status;
    }

    public void setNetwork_download_status(int network_download_status) {
        this.network_download_status = network_download_status;
    }
}
