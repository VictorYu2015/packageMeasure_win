#include "dialog.h"
#include <QApplication>
#include <QTextCodec>


bool use_trigger_mode = false;
char recv_buffer[1024*1024];

// class ServerThread : public QThread {
// protected:
//     virtual void run() {
//         _pm_main();
//     }
// };

void printUsage()
{
    qDebug() << "Usage: PMPackedGUI [options]";
    qDebug() << "options:   --help              show this help";
    qDebug() << "           --trigger-mode      use trigger mode, some cameras may not support";
}

bool checkArgs(int argc, char* argv[])
{

    for(int i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")){
            return false;
        }
        if(!strcmp(argv[i], "--trigger-mode")){
            use_trigger_mode = true;
        }
    }

    if(use_trigger_mode){
        qDebug() << "Set to use trigger mode";
    } else {
        qDebug() << "Set to use continuous mode";
    }

    return true;
}

int main(int argc, char *argv[])
{
    if(!checkArgs(argc, argv)){
        printUsage();
        return 0;
    }

    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    Dialog w;
    w.show();

// #ifdef BUILD_STATIC
//     // Create a new thread to run server
//     ServerThread thread;
//     thread.start();
// #endif

    return a.exec();
}
