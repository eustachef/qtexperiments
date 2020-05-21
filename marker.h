#ifndef MARKER_H
#define MARKER_H
#include <QObject>
#include <QString>

class Marker : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name() NOTIFY nameChanged())
    Q_PROPERTY(bool lowBattery READ lowBattery() NOTIFY lowBatteryChanged)

public:
    Marker(QString name) : m_name(name) {}
    QString name() const {return m_name;}
    void setLowBattery(bool);
    bool lowBattery() const {return m_lowBattery;}

signals:
    void nameChanged();
    void lowBatteryChanged();

private:
    QString m_name = "";
    bool m_lowBattery = false;
};

#endif // MARKER_H
