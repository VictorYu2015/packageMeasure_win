#ifndef INSTALLTHREAD_H
#define INSTALLTHREAD_H

#include <QImage>
#include <QThread>
#include <QDateTime>
#include "common.h"

class InstallThread : public QThread {
    Q_OBJECT

private:
    int    *m_socket;
    bool    m_thread_exit;
    int     m_frameCnt;
    QImage  m_image;

public:
    InstallThread(int* socket) : QThread(), m_socket(socket), m_thread_exit(false), m_frameCnt(0) {}
    virtual ~InstallThread() {}

signals:
    void signal_frameCountUpdated(int);
    void signal_frameImageUpdated(QImage*);

public slots:
    void slot_thread_exit() {m_thread_exit = true;}

protected:
    void run() {
        m_thread_exit = false;
        m_frameCnt = 0;
        XData xdata;

        LOGI("Set work mode to SETUP ...");
        int32_t workmode = I_VAL_WORK_MODE_SETUP;
        send_cmd(*m_socket, I_ACTION_WRITE_PROPERTY
                 , I_PROPERTY_int32_WORK_MODE, sizeof(workmode), &workmode);
        recieve_data(*m_socket, xdata, &recv_buffer);
        if(xdata.error_id != I_ERR_NO_ERROR)
        {
            LOGE("Set workmode to SETUP failed");
            return;
        }

        if(use_trigger_mode)
        {
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
        } else {
            LOGI("Set trigger mode to CONTINUOUS ...");
            int32_t triggermode = I_VAL_TRIGGER_MODE_CONTINUOUS;
            send_cmd(*m_socket, I_ACTION_WRITE_PROPERTY
                     , I_PROPERTY_int32_TRIGGER_MODE, sizeof(triggermode), &triggermode);
            recieve_data(*m_socket, xdata, &recv_buffer);
            if(xdata.error_id != I_ERR_NO_ERROR)
            {
                LOGE("Set trigger mode to INTERNAL failed");
                return;
            }
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
        send_cmd(*m_socket, I_ACTION_CMD, I_CMD_START_FETCH_DEPTH);
        recieve_data(*m_socket, xdata, &recv_buffer);
        if(xdata.error_id != I_ERR_NO_ERROR)
        {
            LOGE("Start fetching failed");
            return;
        }

        LOGI("Run into loop ...");
        qint64 t_old = 0;
        while(!m_thread_exit)
        {
            qint64 t0 = QDateTime::currentMSecsSinceEpoch();
            if(use_trigger_mode)
            {
                send_cmd(*m_socket, I_ACTION_CMD, I_CMD_TRIGGER);
                recieve_data(*m_socket, xdata, &recv_buffer);
                if(xdata.error_id != I_ERR_NO_ERROR)
                {
                    LOGE("Trigger failed!");
                    continue;
                }
            }
            int err = recieve_data(*m_socket, xdata, &recv_buffer, 1);
            if(err != 0)
            {
                continue;
            }
            qint64 t1 = QDateTime::currentMSecsSinceEpoch();
            LOGD("t_old->t0 %lld, t0->t1 fetch image time %lld", t0 - t_old, t1 - t0);
            t_old = t1;

            m_frameCnt++;
            m_image.loadFromData((uchar*)(&recv_buffer), xdata.length);

            emit signal_frameImageUpdated(&m_image);
            emit signal_frameCountUpdated(m_frameCnt);
        }

        LOGI("Stop fetching ...");
        send_cmd(*m_socket, I_ACTION_CMD, I_CMD_STOP_FETCH_DEPTH);
        recieve_data(*m_socket, xdata, &recv_buffer);
        if(xdata.error_id != I_ERR_NO_ERROR)
        {
            LOGE("Stop fetching failed");
            return;
        }

        LOGI("Stop running ...");
        send_cmd(*m_socket, I_ACTION_CMD, I_CMD_STOP_CAPTURE);
        recieve_data(*m_socket, xdata, &recv_buffer);
        if(xdata.error_id != I_ERR_NO_ERROR)
        {
            LOGE("Stop running failed");
            return;
        }

        LOGI("InstallThread exit!");
    }
};

#endif // INSTALLTHREAD_H
