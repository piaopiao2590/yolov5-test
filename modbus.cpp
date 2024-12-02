#include "modbus.h"

Modbus::Modbus(QObject *parent)
    : QObject{parent}
{
    client = new QModbusTcpClient;
    client->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
}

void Modbus::connectIP(const QString &ipaddress){
    tcpipaddress = ipaddress;
}

void Modbus::sendmessage(const int &ynum,const quint32 &xnum1,const quint32 &xnum2){
    QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters, 500 ,2);
    QVector<uint16_t> values;
    qDebug() << "y_num:" << ynum << "x_num1:" << xnum1 << "x_num2" << xnum2;

    if (client->connectDevice() == false){
        qDebug() << tcpipaddress;
        client->setConnectionParameter(QModbusDevice::NetworkAddressParameter, tcpipaddress);
        if (client->connectDevice() == true){
            qDebug() << "确定连接成功";
        }
        else{
            qDebug() << "未连接成功";
        }
    }

    //纵坐标处理
    quint32 value32 = static_cast<quint32>(ynum);
    QVector<quint16> value_u16 = u32Tou16(value32);
    values.append(value_u16[0]);
    values.append(value_u16[1]);
    while (values.size() < 30){
        values.append(0xFFFF);
    }

    value32 = static_cast<quint32>(xnum1);
    value_u16 = u32Tou16(value32);
    values.append(value_u16[0]);
    values.append(value_u16[1]);
    while (values.size() < 60){
        values.append(0xFFFF);
    }

    value32 = static_cast<quint32>(xnum2);
    value_u16 = u32Tou16(value32);
    values.append(value_u16[0]);
    values.append(value_u16[1]);
    while (values.size() < 90){
        values.append(0xFFFF);
    }
    unit.setValues(values);
    QModbusReply *reply = client->sendWriteRequest(unit, 1);

}

QVector<quint16> Modbus::u32Tou16(quint32 &u32num){
    QVector<quint16> retu;
    quint16 u16_1 = (u32num >> 16)| 0xFFFF;
    quint16 u16_2 = u32num | 0xFFFF;
    retu.append(u16_1);
    retu.append(u16_2);
    return retu;
}

int Modbus::readflag(){
    QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters, 700 ,2);
    QModbusReply *reply = client->sendReadRequest(unit, 2);
    int receivefla = reply->result().value(0);
    return receivefla;
}

void Modbus::discon(){
    if(client){
        client->disconnect();
    }
}
