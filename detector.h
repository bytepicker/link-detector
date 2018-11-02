#ifndef DETECTOR_H
#define DETECTOR_H

#include <QNetworkInterface>

class Detector : public QObject
{
    Q_OBJECT
public:
    Detector();

public slots:
    void watch();
    void getMacs();

signals:
    void sendMacs(const QStringList &macs);
    void up(const QString &mac);
    void down(const QString &mac);

private:
    QStringList macs;
};

#endif // DETECTOR_H
