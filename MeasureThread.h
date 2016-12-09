#ifndef MEASURETHREAD_H
#define MEASURETHREAD_H

#include <QDateTime>
#include <QImage>
#include <QThread>
#include "common.h"

class MeasureThread : public QThread {
    Q_OBJECT

private:
    int    *m_socket;
    int     m_frameCnt;
    QImage  m_image;
    bool    m_thread_exit;
    bool    m_need_bg;
    bool    m_measure;
    PackageInfo m_packageInfo;

public:
    MeasureThread(int* sock) : QThread()
        , m_socket(sock)
        , m_frameCnt(0)
        , m_thread_exit(false)
        , m_need_bg(true)
        , m_measure(false)
    {}
    virtual ~MeasureThread() {}

signals:
    void signal_frameCountUpdated(int);
    void signal_frameImageUpdated(QImage*);
    void signal_updatePackageInfo(PackageInfo*);

public slots:
    void slot_thread_exit() {m_thread_exit = true;}
    void slot_reset_bg() {m_need_bg = true;}
    void slot_measure_once() {m_measure = true;}

protected:
    void run() {
        m_thread_exit = false;
        m_frameCnt = 0;
        XData xdata;

        LOGI("Set work mode to MEASURE ...");
        int32_t workmode = I_VAL_WORK_MODE_NORMAL_RUN;
        send_cmd(*m_socket, I_ACTION_WRITE_PROPERTY
                 , I_PROPERTY_int32_WORK_MODE, sizeof(workmode), &workmode);
        recieve_data(*m_socket, xdata, &recv_buffer);
        if(xdata.error_id != I_ERR_NO_ERROR)
        {
            LOGE("Set workmode failed");
            return;
        }

        LOGI("Set trigger mode to INTERNAL ...");
        int32_t triggermode = I_VAL_TRIGGER_MODE_INTERNAL;
        send_cmd(*m_socket, I_ACTION_WRITE_PROPERTY
                 , I_PROPERTY_int32_TRIGGER_MODE, sizeof(triggermode), &triggermode);
        recieve_data(*m_socket, xdata, &recv_buffer);
        if(xdata.error_id != I_ERR_NO_ERROR)
        {
            LOGE("Set trigger mode to INTERNAL failed");
            return;
        }

        LOGI("Start running ...");
        send_cmd(*m_socket, I_ACTION_CMD, I_CMD_START_CAPTURE);
        recieve_data(*m_socket, xdata, &recv_buffer);
        if(xdata.error_id != I_ERR_NO_ERROR)
        {
            LOGE("Start running failed");
            return;
        }

        LOGI("Start fetching ...");
        send_cmd(*m_socket, I_ACTION_CMD, I_CMD_START_FETCH_PACKAGE_INFO_IMAGE);
        recieve_data(*m_socket, xdata, &recv_buffer);
        if(xdata.error_id != I_ERR_NO_ERROR)
        {
            LOGE("Start running failed");
            return;
        }

        LOGI("Run into loop ...");
        qint64 t_old = 0;
        while(!m_thread_exit)
        {
            if(m_need_bg)
            {
                LOGI("Reset bg image.");
                send_cmd(*m_socket, I_ACTION_CMD, I_CMD_RESET_BG_IMAGE);
                recieve_data(*m_socket, xdata, &recv_buffer);
                if(xdata.error_id != I_ERR_NO_ERROR)
                {
                    LOGE("Reset bg image failed");
                    return;
                }
                m_need_bg = false;
            }

            qint64 t0 = QDateTime::currentMSecsSinceEpoch();

            // Trigger
            send_cmd(*m_socket, I_ACTION_CMD, I_CMD_TRIGGER);
            recieve_data(*m_socket, xdata, &recv_buffer);
            if(xdata.error_id != I_ERR_NO_ERROR)
            {
                LOGE("Trigger failed!");
                continue;
            }

            if(recieve_data(*m_socket, xdata, &recv_buffer, 1) != 0)
            {
                LOGE("Receive data failed!");
                continue;
            }

                m_packageInfo = *(PackageInfo*)&recv_buffer;
                m_image.loadFromData((uchar*)(&recv_buffer) + sizeof(PackageInfo), xdata.length - sizeof(PackageInfo));

                LOGD("emit package info ...");
                emit signal_updatePackageInfo(&m_packageInfo);
/*
            if(m_measure)
            {
                LOGD("Do measure ...");
                send_cmd(*m_socket, I_ACTION_READ_PROPERTY, I_PROPERTY_struct_PACKAGE_INFO_IMAGE);
                recieve_data(*m_socket, xdata, &recv_buffer);
                if(xdata.error_id != I_ERR_NO_ERROR)
                {
                    LOGE("Do measure failed. Err(%d:%s)", xdata.error_id, (char*)xdata.data);
                    return;
                }
                m_measure = false;

            } else { // only reveive depth image
                send_cmd(*m_socket, I_ACTION_READ_PROPERTY, I_PROPERTY_struct_DEPTH_IMAGE);
                recieve_data(*m_socket, xdata, &recv_buffer);
                if(xdata.error_id != I_ERR_NO_ERROR)
                {
                    LOGE("Receive depth image failed");
                    return;
                }
                m_image.loadFromData((uchar*)(&recv_buffer), xdata.length);
            }
*/
            qint64 t1 = QDateTime::currentMSecsSinceEpoch();
            LOGD("t_old->t0 %lld, t0->t1 fetch image time %lld", t0 - t_old, t1 - t0);
            t_old = t1;

            m_frameCnt++;

            emit signal_frameImageUpdated(&m_image);
            emit signal_frameCountUpdated(m_frameCnt);
        }

        LOGI("Stop fetching ...");
        send_cmd(*m_socket, I_ACTION_CMD, I_CMD_STOP_FETCH_PACKAGE_INFO_IMAGE);
        recieve_data(*m_socket, xdata, &recv_buffer);
        if(xdata.error_id != I_ERR_NO_ERROR)
        {
            LOGE("Stop fetching failed");
            return;
        }

        LOGI("Stop measure thread ...");
        send_cmd(*m_socket, I_ACTION_CMD, I_CMD_STOP_CAPTURE);
        recieve_data(*m_socket, xdata, &recv_buffer);
        if(xdata.error_id != I_ERR_NO_ERROR)
        {
            LOGE("Stop running failed");
            return;
        }

        LOGI("MeasureThread exit!");
    }

};

#endif // THREAD_H
