#ifndef MODBUS_H
#define MODBUS_H

#include <QObject>
#include <QModbusTcpClient>
#include <QVariant>
#include <QDebug>

class Modbus : public QObject
{
    Q_OBJECT
public:
    explicit Modbus(QObject *parent = nullptr);
    void connectIP(const QString &ipaddress);
    void sendmessage(const int &ynum,const quint32 &xnum1,const quint32 &xnum2);
    QVector<quint16> u32Tou16(quint32 &u32num);
    int readflag();
    void discon();

private:
    QModbusTcpClient *client;
    QString tcpipaddress;

signals:
};

#endif // MODBUS_H
