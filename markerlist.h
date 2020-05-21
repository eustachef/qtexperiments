#ifndef MARKERLIST_H
#define MARKERLIST_H
#include <QAbstractListModel>
#include <QList>
#include <QObject>
#include <QSortFilterProxyModel>
#include <memory>
#include "marker.h"

class MarkerList : public QAbstractListModel
{
public:
    enum MarkerRoles {
        NameRole = Qt::UserRole + 1,
        LowBatteryRole
    };

    MarkerList(QObject * parent = nullptr);

    void add(std::shared_ptr<Marker> marker);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<std::shared_ptr<Marker>> m_markers;

};

class LowBatteryMarkerList : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    LowBatteryMarkerList(QObject *parent = 0);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

};

#endif // MARKERLIST_H
