#include "detector.h"

Detector::Detector()
{
    foreach (QNetworkInterface nic, QNetworkInterface::allInterfaces()) {
        if(!nic.hardwareAddress().contains("00:00:00:00:00:00") && !nic.flags().testFlag(QNetworkInterface::IsLoopBack)){
            if(!macs.contains(nic.hardwareAddress())){
                macs.append(nic.hardwareAddress());
            }
        }
    }
    emit sendMacs(macs);
}

void Detector::getMacs()
{
    if(macs.size()){
        emit sendMacs(macs);
    }
}

void Detector::watch()
{
    while(true){
        foreach (QNetworkInterface nic, QNetworkInterface::allInterfaces()) {
            foreach (QString mac, macs) {
                if(nic.hardwareAddress() == mac){
                    if(!nic.flags().testFlag(QNetworkInterface::IsUp)){
                        emit down(mac);
                    } else {
                        emit up(mac);
                    }
                }
            }
        }
    }
}
