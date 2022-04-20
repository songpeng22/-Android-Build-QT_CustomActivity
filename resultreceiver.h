#ifndef RESULTRECEIVER_H
#define RESULTRECEIVER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QAndroidActivityResultReceiver>

#include <QtAndroid>
#include <QAndroidIntent>

#include "global_define.h"

class ResultReceiver : public QAndroidActivityResultReceiver
{
public:
    ResultReceiver()
    {

    }

    void handleActivityResult(
            int receiverRequestCode,
            int resultCode,
            const QAndroidJniObject & data)
    {
        qDebug() << "handleActivityResult, requestCode - " << receiverRequestCode
                 << " resultCode - " << resultCode;

        const jint RESULT_OK = QAndroidJniObject::getStaticField<jint>("android/app/Activity", "RESULT_OK");

        if (receiverRequestCode == REQUEST_CODE) {
            if (resultCode == RESULT_OK) {
                const QAndroidJniObject key = QAndroidJniObject::fromString("message");
                const QAndroidJniObject message = data.callObjectMethod(
                        "getStringExtra", "(Ljava/lang/String;)Ljava/lang/String;", key.object());
                if (message.isValid())
                    qDebug() << "message:" << message.toString();
            } else {
                qDebug() << "Rejected!";
            }
        }
    }

private:

};

#endif // RESULTRECEIVER_H
