#ifndef DIALOG_H
#define DIALOG_H

#include "common.h"
#include "./InstallThread.h"
#include "./MeasureThread.h"
#include <QGraphicsScene>
#include <QImage>
#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>
#include <QThread>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_Exit_clicked();
    void on_pushButton_Start_clicked();
    void slot_measure_thread_finished();
    void slot_install_thread_finished();

    void slot_handle_frame_cnt(int);
    void slot_handle_new_depth_image(QImage*);
    void slot_handle_package_info(PackageInfo*);

    void on_pushButton_Install_clicked();

public:
    Ui::Dialog *ui;
    QGraphicsScene m_scene;
    int         m_socket;
    QString     m_hostAddress;
    qint16      m_tcpPort;

    bool        m_isInstalling;
    InstallThread m_installThread;

    bool        m_isMeasuring;
    MeasureThread   m_measureThread;

private:
    int     connectDevice();
    void    disconnectDevice();
};

#endif // DIALOG_H
