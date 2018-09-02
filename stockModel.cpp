#include "stockModel.h"
#include <QXmlStreamReader>
#include <QVector>
#include <QHash>
#include <QFile>
#include <QDebug>
#include "stockProvider.h"

/*
enum {
    stock_name = 0,
    today_open,
    yesterday_close,
    current_price,
    today_highest_price,
    today_lowest_price,
    buy_1_price_0,
    sale_1_price_0,
    transaction_stocks,
    transaction_money,
    buy_1_amount,
    buy_1_price,
    buy_2_amount,
    buy_2_price,
    buy_3_amount,
    buy_3_price,
    buy_4_amount,
    buy_4_price,
    buy_5_amount,
    buy_5_price,
    sale_1_amount,
    sale_1_price,
    sale_2_amount,
    sale_2_price,
    sale_3_amount,
    sale_3_price,
    sale_4_amount,
    sale_4_price,
    sale_5_amount,
    sale_5_price,
    stock_date,
    stock_time//31
};
//*/
class StockModelPrivate
{
public:
    StockModelPrivate(StockModel *m)
        : m_model(m)
    {qDebug()<<__FUNCTION__;
        int role = Qt::UserRole;
        m_roleNames.insert(role++, "code");
        m_roleNames.insert(role++, "name");
        m_roleNames.insert(role++, "current");
        m_roleNames.insert(role++, "offset");
        m_roleNames.insert(role++, "percent");
        m_roleNames.insert(role++, "handover");
        m_roleNames.insert(role++, "gainAndLose");
        m_roleNames.insert(role++, "upDown");
        m_roleNames.insert(role++, "turnover");
        m_currentStock.setProvider(&m_stocks);
    }

    StockModel * m_model;
    QHash<int, QByteArray> m_roleNames;
    StockProvider m_stocks;
    StockState m_currentStock;
};

StockModel::StockModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_dptr(new StockModelPrivate(this))
{qDebug()<<__FUNCTION__;
    connect( &(m_dptr->m_stocks), SIGNAL(refreshed()),
             this, SLOT(onStockDataRefreshed()) );
    connect( &(m_dptr->m_stocks), SIGNAL(beginRefresh()),
             this, SLOT(onStockDataBeginRefresh()) );
}

StockModel::~StockModel()
{qDebug()<<__FUNCTION__;
    delete m_dptr;
}

int StockModel::rowCount(const QModelIndex &parent) const
{qDebug()<<__FUNCTION__;
    return m_dptr->m_stocks.stockCount();
}

QVariant StockModel::data(const QModelIndex &index, int role) const
{qDebug()<<__FUNCTION__;
    StockDetail *stock = m_dptr->m_stocks.stockAt(index.row());
    switch(role - Qt::UserRole)
    {
    case 0: // code
        return stock->code();
    case 1: // name
        //return stock->name();
        return stock->content(stock_name);
    case 2: // current
        //return stock->currentPrice();
        return stock->content(current_price);
    case 3: // offset
        return stock->rise();
    case 4: // percent
        return stock->risePercent();
    case 5: // handover
        return stock->handoverRate();
    case 6: // stopLose
        return QString("%1/%2")
                .arg(stock->stopWinPrice(), 0, 'f', 2)
                .arg(stock->stopLosePrice(), 0, 'f', 2);
    case 7: // upDown
        return QString("%1/%2").arg(stock->content(today_highest_price).data())
                .arg(stock->content(today_lowest_price).data());
    case 8: // turnover
        //return stock->transactionMoney();
        return stock->content(transaction_money);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> StockModel::roleNames() const
{qDebug()<<__FUNCTION__;
    return m_dptr->m_roleNames;
}

int StockModel::updateInterval()
{qDebug()<<__FUNCTION__;
    return m_dptr->m_stocks.updateInterval();
}

void StockModel::setUpdateInterval(int seconds)
{qDebug()<<__FUNCTION__;
    m_dptr->m_stocks.setUpdateInterval(seconds);
}

int StockModel::stateOf(int row)
{qDebug()<<__FUNCTION__;
    StockDetail *stock = m_dptr->m_stocks.stockAt(row);
    return stock->riseMode();
}

void StockModel::addStock(QString code)
{qDebug()<<__FUNCTION__;
    int count = m_dptr->m_stocks.stockCount();
    if(m_dptr->m_stocks.addStock(code.toLatin1()))
    {
        QModelIndex parent;
        beginInsertRows(parent, count, count);
        endInsertRows();
    }
}

void StockModel::remove(int row)
{qDebug()<<__FUNCTION__;
    beginRemoveRows(QModelIndex(), row, row);
    m_dptr->m_stocks.removeStock(row);
    endRemoveRows();
}

void StockModel::updateCurrentStock(int row)
{qDebug()<<__FUNCTION__;
    m_dptr->m_currentStock.setIndex(row);
}

void StockModel::saveState()
{qDebug()<<__FUNCTION__;
    m_dptr->m_stocks.saveState();
    int row = m_dptr->m_currentStock.index();
    QModelIndex topLeft = createIndex(row, 2);
    QModelIndex bottomRight = createIndex(row, 8);
    emit dataChanged(topLeft, bottomRight);
}

StockState *StockModel::currentStock()
{qDebug()<<__FUNCTION__;
    return &m_dptr->m_currentStock;
}

void StockModel::connectToReminder(QObject *receiver, const char *method)
{qDebug()<<__FUNCTION__;
    QObject::connect(&m_dptr->m_stocks, SIGNAL(remind(QString)),
                     receiver, method);
}

void StockModel::onStockDataBeginRefresh()
{qDebug()<<__FUNCTION__;
    //beginResetModel();
}

void StockModel::onStockDataRefreshed()
{qDebug()<<__FUNCTION__;
    //qDebug() << "onStockDataChange";
    QModelIndex topLeft = createIndex(0, 0);
    QModelIndex bottomRight = createIndex(m_dptr->m_stocks.stockCount() - 1, 8);
    emit dataChanged(topLeft, bottomRight);
}
