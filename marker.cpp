#include "marker.h"

void Marker::setLowBattery(bool val)
{
    if (m_lowBattery != val)
    {
        m_lowBattery = val;
        emit lowBatteryChanged();
    }
}
