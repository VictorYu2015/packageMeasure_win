#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#ifdef WIN32
#include <winsock2.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma comment(lib,"Ws2_32")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <string.h>
#include "PMDefines.h"

#include <QDebug>

#define  Q_FLAG_WAITALL   MSG_WAITALL

#ifdef __GNUC__
#include <sys/types.h>
#include <sys/socket.h>
#endif

#define LOGPRE          "Client: "
#ifdef WIN32
#define LOGI(fmt, ...)    qDebug(LOGPRE fmt)
#define LOGE(fmt, ...)    qDebug(LOGPRE "ERROR: " fmt)
#define CHECK(v, fmt, ...)    if((v)<0){LOGE(fmt);break;}
#ifdef QGC_DEBUG
#  define LOGD(fmt, ...)    qDebug(LOGPRE fmt)
#else
#  define LOGD(fmt, ...)
#endif
#else
#define LOGI(fmt...)    qDebug(LOGPRE fmt)
#define LOGE(fmt...)    qDebug(LOGPRE "ERROR: " fmt)
#define CHECK(v, fmt...)    if((v)<0){LOGE(fmt);break;}
#ifdef QGC_DEBUG
#  define LOGD(fmt...)    qDebug(LOGPRE fmt)
#else
#  define LOGD(fmt...)
#endif
#endif

extern bool use_trigger_mode;
extern char recv_buffer[1024*1024];

static inline int send_cmd(int cfd, int16_t action, int16_t target
                           , int len = 0, void* buffer = 0)
{
    XData xdata;
    xdata.action_id = action;
    xdata.target_id = target;
    xdata.error_id  = -1;
    xdata.uid       = 0;
    xdata.length    = len;

    // send header
    int trans_len = sizeof(xdata);
#ifdef WIN32
	if(send(cfd, (char*)&xdata, sizeof(xdata), 0) != trans_len) {
#else
	if(::write(cfd, (char*)&xdata, sizeof(xdata)) != trans_len){
#endif
		LOGE("Send %d %d failed.\n", action, target);
        return -1;
    }

    // send body
#ifdef WIN32
	if(len && send(cfd, (char*)buffer, len, 0) != len)
#else
    if(len && ::write(cfd, buffer, len) != len)
#endif
	{
        LOGE("Send action %d data failed.", action);
        return -1;
    }

    return 0;
}

static inline int recieve_data(int cfd, XData &xdata, void* buffer, bool has_body = 0)
{
    // receive header
    int trans_len = sizeof(xdata);
	int k = 0;
#ifdef WIN32
	k = recv(cfd, (char*)&xdata, trans_len,Q_FLAG_WAITALL);  
#else
    k = ::recv(cfd, &xdata, trans_len, Q_FLAG_WAITALL);
#endif
	if( k != trans_len)
    {
        LOGE("Receive answer header failed. recv(%d)", k);
        return -1;
    }

    // handle error
    if(xdata.error_id != I_ERR_NO_ERROR)
    {
#ifdef WIN32
		recv(cfd, (char*)buffer, xdata.length, Q_FLAG_WAITALL);
#else
		::recv(cfd, buffer, xdata.length, Q_FLAG_WAITALL);
#endif  
        LOGE("Error message: %s", (char*)buffer);
        return 1;
    }

    // check data complementation
    if(has_body && !xdata.length)
    {
        LOGE("Received should have body but got none.");
        return -1;
    }

    // no body to receive
    if(xdata.length == 0)
    {
        return 0;
    }

    // receive body
    trans_len = xdata.length;
#ifdef WIN32
	k = recv(cfd, (char*)buffer, trans_len, Q_FLAG_WAITALL);
#else
	k = ::recv(cfd, buffer, trans_len, Q_FLAG_WAITALL);
#endif
    if(k != trans_len)
    {
        LOGE("Receive answer body failed.(%d -> %d)", trans_len, k);
        return -1;
    }

    return 0;
}

#endif // COMMON_H
