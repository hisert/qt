#include <QCoreApplication>
#include <QThread>
#include <iostream>
#include <functional>
#include <QHostInfo>
#include <QTcpSocket>

class MyThread : public QThread
{
public:
#define THREAD_ENABLE_DEBUG true
#define THREAD_DISABLE_DEBUG false
#define THREAD_ENABLE_LOOP true
#define THREAD_DISABLE_LOOP false
    using FunctionType = std::function<void()>;
    MyThread(FunctionType func, int sleepTime, const std::string& threadName, bool initialIsEnabled, bool initialDebugFlag, bool shouldStartThread)
        : functionToRun(func), sleepTime(sleepTime), isEnabled(initialIsEnabled), THREAD_NAME(threadName), isDebugOn(initialDebugFlag)
    {
        if (shouldStartThread) start();
    }

    void run() override
    {
        if (isDebugOn) std::cout << THREAD_NAME << " START!" << std::endl;
        while (1)
        {
            functionToRun();
            if (isDebugOn) std::cout << THREAD_NAME << " WORKING!" << std::endl;
            if (!isEnabled) break;
            QThread::msleep(sleepTime);
        }
        if (isDebugOn) std::cout << THREAD_NAME << " STOP!" << std::endl;
    }

    void disable()
    {
        isEnabled = false;
    }

    void enable()
    {
        isEnabled = true;
    }

    void debug_enable()
    {
        isDebugOn = true;
    }

    void debug_disable()
    {
        isDebugOn = false;
    }

private:
    FunctionType functionToRun;
    int sleepTime;
    bool isEnabled;
    std::string THREAD_NAME;
    bool isDebugOn;
};

void helloFunction();
MyThread myThread1(helloFunction, 100, "HELLO THREAD", THREAD_ENABLE_LOOP, THREAD_ENABLE_DEBUG,false);
MyThread myThread2(helloFunction, 300, "LED THREAD", THREAD_ENABLE_LOOP, THREAD_ENABLE_DEBUG,false);

QString SYSTEM_GET_IP()
{
    QHostInfo hostInfo = QHostInfo::fromName(QHostInfo::localHostName());
    foreach (const QHostAddress &address, hostInfo.addresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol) return address.toString();
    }
    return "";
}

void SYSTEM_PRINT(QString data)
{
    std::cout << data.toStdString() << std::endl;
}

void helloFunction()
{

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    while(1) std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return a.exec();
}
