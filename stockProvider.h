#ifndef STOCKPROVIDER_H
#define STOCKPROVIDER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QList>
#include <QTime>
#include <QByteArray>

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

//StockProvider
class StockProvider;

class StockDetail
{
    friend class StockProvider;
public:
    StockDetail(const QByteArray & stockCode);
    ~StockDetail();

    //bool detailAvailable() const;

    const QByteArray & code() const;


    const QByteArray & content(quint8 value) const;


    const QString rise() const;
    const QString risePercent() const ;
    int riseMode() const;
    bool arriveStopWin() const;
    bool arriveStopLose() const;
    void setStopWinPrice(double price);
    double stopWinPrice() const;
    void setStopLosePrice(double price);
    double stopLosePrice() const;
    bool isDetailsValid() const;
    const QString handoverRate() const;

protected:
    QByteArray m_strCode;
    QList<QByteArray> m_details;
    double m_stopWinPrice;
    double m_stopLosePrice;
    double m_totalTransactStocks;
};

class StockProvider : public QObject
{
    Q_OBJECT
public:
    StockProvider(QObject * parent = 0);
    ~StockProvider();

    bool addStock(const QByteArray & stockCode);
    void removeStock(const QByteArray & stockCode);
    void removeStock(int index);
    StockDetail * stock(const QByteArray & stockCode);
    int stockCount();
    StockDetail * stockAt(int index);

    int remindMode();
    void setRemindMode(int mode);

    void saveState();

    int updateInterval() { return m_refreshInterval; }
    void setUpdateInterval(int seconds);

signals:
    void beginRefresh();
    void refreshed();
    void remind(const QString & contents);

protected slots:
    void onRefreshFinished();
    void onRefreshError(QNetworkReply::NetworkError code);

protected:
    void timerEvent(QTimerEvent *);
    void saveToFile();
    void readFromFile();
    void startUpdate();
    void parseData(const QByteArray & data);
    void updateStockDetail(const QByteArray & stockCode, const QByteArray & data);
    void updateRemindContents(StockDetail * stock);
    bool isTransactTime();
    void startUpdateImmediately();

protected:
    QList<StockDetail*> m_stocks;
    int m_iRefreshTimer;
    int m_iRefreshTimeoutTimer;
    QNetworkAccessManager m_nam;
    QTime m_updateElapsed;
    int m_iRemindMode;
    int m_refreshInterval;
    QNetworkReply *m_reply;
    bool m_bShouldSave;
    QString m_strRemind;
    bool m_bNoRefreshAfterLaunch;
    int m_refreshingCount;
};
#endif // STOCKPROVIDER_H
