#include "markerlist.h"
#include "marker.h"
#include <iostream>

MarkerList::MarkerList(QObject *parent)
    : QAbstractListModel(parent)
{
}

void MarkerList::add(std::shared_ptr<Marker> marker)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_markers << marker;
    endInsertRows();
}

int MarkerList::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_markers.count();
}

QVariant MarkerList::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_markers.count())
        return QVariant();

    std::shared_ptr<Marker> marker = m_markers[index.row()];
    if (role == NameRole)
    {
        return marker->name();
    }
    else if (role == LowBatteryRole)
    {
        return marker->lowBattery();
    }
    return QVariant();
}

QHash<int, QByteArray> MarkerList::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[LowBatteryRole] = "lowBattery";
    return roles;
}

LowBatteryMarkerList::LowBatteryMarkerList(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool LowBatteryMarkerList::filterAcceptsRow(int sourceRow,
                                            const QModelIndex &sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    return sourceModel()->data(index0, MarkerList::LowBatteryRole).toBool();
}
