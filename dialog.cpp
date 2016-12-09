#include <QDebug>
#include <QMessageBox>
#include "dialog.h"
#include "ui_dialog.h"
#include "PMDefines.h"
#include "MeasureThread.h"


namespace {

void ErrDlg(const QString& msg)
{
    QMessageBox::critical(NULL, "Error", msg);
}

} // namespace {}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_socket(-1),
    m_tcpPort(0),
    m_isInstalling(false),
    m_installThread(&m_socket),
    m_isMeasuring(false),
    m_measureThread(&m_socket)
{
    ui->setupUi(this);

    connect(&m_installThread, SIGNAL(finished()), this, SLOT(slot_install_thread_finished()));
    connect(&m_installThread, SIGNAL(signal_frameCountUpdated(int)), this, SLOT(slot_handle_frame_cnt(int)));
    connect(&m_installThread, SIGNAL(signal_frameImageUpdated(QImage*)), this, SLOT(slot_handle_new_depth_image(QImage*)));

    connect(&m_measureThread, SIGNAL(finished()), this, SLOT(slot_measure_thread_finished()));
    connect(&m_measureThread, SIGNAL(signal_frameCountUpdated(int)), this, SLOT(slot_handle_frame_cnt(int)));
    connect(&m_measureThread, SIGNAL(signal_frameImageUpdated(QImage*)), this, SLOT(slot_handle_new_depth_image(QImage*)));

    connect(ui->pushButton_UpdateBg, SIGNAL(clicked()), &m_measureThread, SLOT(slot_reset_bg()));

    connect(&m_measureThread, SIGNAL(signal_updatePackageInfo(PackageInfo*)), this, SLOT(slot_handle_package_info(PackageInfo*)));
    connect(ui->pushButton_Measure, SIGNAL(clicked()), &m_measureThread, SLOT(slot_measure_once()));

    setWindowTitle(QObject::tr("图漾科技"));

#ifdef WIN32
	WSADATA wsaData;

	if ( WSAStartup(MAKEWORD(2,2), &wsaData) != 0 )
	{
		QMessageBox::critical(NULL, "Error", "WSAStartup返回错误");
		return;
    }
#else

#endif
}

Dialog::~Dialog()
{
    delete ui;
#ifdef WIN32
	WSACleanup();
#else

#endif
}

void Dialog::on_pushButton_Exit_clicked()
{
    if(m_isMeasuring){
        connect(&m_installThread, SIGNAL(finished()), this, SLOT(close()));
        m_measureThread.slot_thread_exit();

    } else if(m_isInstalling){
        connect(&m_installThread, SIGNAL(finished()), this, SLOT(close()));
        m_installThread.slot_thread_exit();

    }

    close();
}

int Dialog::connectDevice()
{
    struct sockaddr_in s_add;

    m_tcpPort = ui->lineEdit_Port->text().toInt();
    m_hostAddress = ui->lineEdit_IP->text();
//    m_tcpPort = 7000;
//    m_hostAddress = "127.0.0.1";

    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(m_socket < 0){
        QMessageBox::critical(this, "Error", "Open socket failed!", QObject::tr("OK"));
        return -1;
    }
#ifdef WIN32
	memset(&s_add, 0, sizeof(struct sockaddr_in));
#else
    bzero(&s_add,sizeof(struct sockaddr_in));
#endif
    s_add.sin_family=AF_INET;
    s_add.sin_addr.s_addr= inet_addr(m_hostAddress.toStdString().c_str());
    s_add.sin_port=htons(m_tcpPort);

	int on = 1;
	::setsockopt( m_socket, IPPROTO_TCP, TCP_NODELAY, (char *)(void *)&on, sizeof(on));

    if(-1 == ::connect(m_socket,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
    {
        LOGE("Connect fail!");
        QMessageBox::critical(this, "Error", "Connect failed! Please check the IP and Port.", QObject::tr("quit"));
#ifdef WIN32
		closesocket(m_socket);
#else
		::close(m_socket);
#endif
        return -1;
    }
    LOGI("Connect to server ok!");

    return 0;
}

void Dialog::disconnectDevice()
{
#ifdef WIN32
		closesocket(m_socket);
#else
		::close(m_socket);
#endif
    m_socket = -1;
}

void Dialog::on_pushButton_Start_clicked()
{
    if(!m_isMeasuring)
    {
        if(!connectDevice())
        {
            m_measureThread.start();
            m_isMeasuring = true;

            ui->pushButton_Start->setText(QObject::tr("Stop"));
            ui->pushButton_Install->setEnabled(false);
        }
    } else {
        m_measureThread.slot_thread_exit();
    }
}

void Dialog::slot_measure_thread_finished()
{
    disconnectDevice();
    m_isMeasuring = false;

    ui->pushButton_Start->setText(tr("Start"));
    // Disable other buttons
    ui->pushButton_Install->setEnabled(true);
    qDebug() << "slot_measure_thread_finished() OK";
}

void Dialog::on_pushButton_Install_clicked()
{
    if(!m_isInstalling)
    {
        if(!connectDevice())
        {
            m_installThread.start();
            m_isInstalling = true;

            ui->pushButton_Install->setText(tr("停止安装"));
            // Disable other buttons
            ui->pushButton_Start->setEnabled(false);
            ui->pushButton_UpdateBg->setEnabled(false);
            ui->pushButton_Measure->setEnabled(false);
            ui->lineEdit_X->clear();
            ui->lineEdit_Y->clear();
            ui->lineEdit_Z->clear();
        }
    } else {
        m_installThread.slot_thread_exit();
    }
}

void Dialog::slot_install_thread_finished()
{
    disconnectDevice();
    m_isInstalling = false;

    ui->pushButton_Install->setText(tr("Start Install"));
    // Disable other buttons
    ui->pushButton_Start->setEnabled(true);
    ui->pushButton_UpdateBg->setEnabled(true);
    ui->pushButton_Measure->setEnabled(true);
    qDebug() << "slot_install_thread_finished() OK";
}

void Dialog::slot_handle_frame_cnt(int n)
{
    ui->lineEdit_Frames->setText(QString::number(n));
}

void Dialog::slot_handle_new_depth_image(QImage* image)
{
    m_scene.clear();
    m_scene.addPixmap(QPixmap::fromImage(*image));
    ui->graphicsView_Depth->setScene(&m_scene);
    ui->graphicsView_Depth->show();
}

void Dialog::slot_handle_package_info(PackageInfo *info)
{
    qDebug() << "slot_handle_package_info set x y z";
    ui->lineEdit_Timestamp->setText(QString::number(info->timestamp));
    switch(info->type){
        case I_PACKAGE_TYPE_NONE:
            ui->lineEdit_Type->setText("None");
            break;
        case I_PACKAGE_TYPE_BOX:
            ui->lineEdit_Type->setText("Box");
            break;
        case I_PACKAGE_TYPE_IRREGULAR:
            ui->lineEdit_Type->setText("Irregular");
            break;
    }
    ui->lineEdit_X->setText(QString::number(info->x));
    ui->lineEdit_Y->setText(QString::number(info->y));
    ui->lineEdit_Z->setText(QString::number(info->z));
    ui->lineEdit_Boundingvol->setText(QString::number(info->boundingVolume));
    ui->lineEdit_IntegeralVol->setText(QString::number(info->integeralVolume));
}
