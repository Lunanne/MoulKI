#ifndef QTSDLTREEMODEL_H
#define QTSDLTREEMODEL_H

#include <QVector>
#include <QAbstractItemModel>

class plStateDataRecord;
class plStateVariable;

class qtSDLTreeModel : public QAbstractItemModel
{
    Q_OBJECT
private:
    plStateDataRecord* sdl;
    enum ItemType { kSDR, kVar, kVal };
    struct SDLModelIndex {
        QModelIndex parent;
        ItemType type;
        int row, column;
        union {
            plStateDataRecord* sdr;
            plStateVariable* sv;
            void* raw;
        } ptr;

        bool operator==(const SDLModelIndex& other) {
            return parent == other.parent && type == other.type && row == other.row && column == other.column && ptr.raw == other.ptr.raw;
        }
    };
    mutable QVector<SDLModelIndex> indices;

    QModelIndex ICreateIndex(int row, int column, const QModelIndex& parent, void* ptr, ItemType type) const;

public:
    explicit qtSDLTreeModel(plStateDataRecord* sdl);
    ~qtSDLTreeModel();
    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

signals:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void sdlChanged(plStateDataRecord* sdl);

public slots:

};

#endif // QTSDLTREEMODEL_H
