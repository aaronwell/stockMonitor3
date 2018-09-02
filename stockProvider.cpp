﻿#include "stockProvider.h"
#include <QTimerEvent>
#include <QNetworkRequest>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QXmlStreamReader>
#include <QDebug>
#include <QObjectCleanupHandler>
#include <QMutexLocker>
#include <QCoreApplication>
#include <QNetworkReply>
#include <QDateTime>

#define REFRESH_PERIOD  1000
#define STOCK_START_STRING "var hq_str_"
#define STOCK_START_STRING_LEN  11


StockDetail::StockDetail(const QByteArray &stockCode) : m_strCode(stockCode)
  , m_stopWinPrice(-1), m_stopLosePrice(-1), m_totalTransactStocks(-1)
{qDebug()<<__FUNCTION__<<stock_time<<stockCode;
    QByteArray dummy("-");
    for(int i = 0; i <= stock_time; i++)
    {
        m_details.append(dummy);
    }
}

StockDetail::~StockDetail()
{qDebug()<<__FUNCTION__;
}

//bool StockDetail::detailAvailable() const
//{qDebug()<<__FUNCTION__;
//    return m_details.size() > stock_time;
//}

const QByteArray & StockDetail::code() const
{qDebug()<<__FUNCTION__;
    return m_strCode;
}


const QByteArray & StockDetail::content(quint8 value) const
{qDebug()<<__FUNCTION__;
    return m_details.at(value);
}




const QString StockDetail::rise() const
{qDebug()<<__FUNCTION__;
    //const QByteArray & baCurrent = currentPrice();
    const QByteArray & baCurrent = content(current_price);
    if(baCurrent != "-")
    {
        //float yesterday = yesterdayClosePrice().toFloat();
        float yesterday = content(yesterday_close).toFloat();
        float current = baCurrent.toFloat();
        if(current < 0.001)
        {
            return "-";
        }
        float rise = current - yesterday;
        return QString("%1").arg(rise, 0, 'f', 2);
    }
    return "-";
}

const QString StockDetail::risePercent() const
{qDebug()<<__FUNCTION__;
    //const QByteArray & baCurrent = currentPrice();
    const QByteArray & baCurrent = content(current_price);
    if(baCurrent != "-")
    {
//        float yesterday = yesterdayClosePrice().toFloat();
//        float current = currentPrice().toFloat();
        float yesterday = content(yesterday_close).toFloat();
        float current = content(current_price).toFloat();
        if(current < 0.001)
        {
            return "-";
        }
        float risePercent = (current - yesterday)*100 / yesterday;
        return QString("%1%").arg(risePercent, 0, 'f', 2);
    }

    return "-";
}

int StockDetail::riseMode() const
{qDebug()<<__FUNCTION__;
    //const QByteArray & baCurrent = currentPrice();
    const QByteArray & baCurrent = content(current_price);
    if(baCurrent != "-")
    {
        //float yesterday = yesterdayClosePrice().toFloat();
        float yesterday = content(yesterday_close).toFloat();
        float current = baCurrent.toFloat();
        if(current < 0.001)
        {
            return 0;
        }
        float rise = current - yesterday;
        if(rise < -0.001) return -1;
        if(rise > 0.001) return 1;
    }
    return 0;
}

bool StockDetail::arriveStopWin() const
{qDebug()<<__FUNCTION__;
    if(m_details.size() > 0 && m_stopWinPrice > 0.001)
    {
        double currentPrice = m_details.at(current_price).toDouble();
        if(currentPrice < 0.001)
        {
            return false;
        }
        return currentPrice >= m_stopWinPrice;
    }

    return false;
}

bool StockDetail::arriveStopLose() const
{qDebug()<<__FUNCTION__;
    if(m_details.size() > 0 && m_stopLosePrice > 0.001)
    {
        double currentPrice = m_details.at(current_price).toDouble();
        if(currentPrice < 0.001)
        {
            return false;
        }
        return currentPrice <= m_stopLosePrice;
    }

    return false;
}

void StockDetail::setStopWinPrice(double price)
{qDebug()<<__FUNCTION__;
    m_stopWinPrice = price;
}

double StockDetail::stopWinPrice() const
{
    return m_stopWinPrice;
}

void StockDetail::setStopLosePrice(double price)
{qDebug()<<__FUNCTION__;
    m_stopLosePrice = price;
}

double StockDetail::stopLosePrice() const
{
    return m_stopLosePrice;
}

bool StockDetail::isDetailsValid() const
{qDebug()<<__FUNCTION__;
    //return currentPrice() != "-";
    return content(current_price) != "-";
}

const QString StockDetail::handoverRate() const
{qDebug()<<__FUNCTION__;
    if(m_totalTransactStocks > 0)
    {
        const QByteArray & transact = m_details.at(transaction_stocks);
        if(transact != "-")
        {
            double dbRate = transact.toDouble()/m_totalTransactStocks;
            return QString("%1%").arg(dbRate, 0, 'f',2);
        }
    }
    return "-";
}

//
// class StockProvider
//
StockProvider::StockProvider(QObject *parent)
    : QObject(parent)
    , m_iRefreshTimer(0)
    , m_iRefreshTimeoutTimer(0)
    , m_nam(this)
    , m_iRemindMode(0)
    , m_refreshInterval(3000)
    , m_reply(0)
    , m_bShouldSave(false)
    , m_bNoRefreshAfterLaunch(true)
    , m_refreshingCount(0)
{qDebug()<<__FUNCTION__;
    readFromFile();
    if(m_stocks.size() > 0)
    {
        m_iRefreshTimer = startTimer(m_refreshInterval);
    }
}

StockProvider::~StockProvider()
{qDebug()<<__FUNCTION__;
    int count = m_stocks.count();
    if(count > 0)
    {
        saveToFile();
        for(int i = 0; i < count; i++)
        {
            delete m_stocks.at(i);
        }
        m_stocks.clear();
    }
}

bool StockProvider::addStock(const QByteArray &stockCode)
{qDebug()<<__FUNCTION__;
    QByteArray code(stockCode);
    if(code.startsWith('6'))
    {
        code.prepend("sh");
    }
    else
    {
        code.prepend("sz");
    }
    int count = m_stocks.count();
    int i = 0;
    for(; i < count; i++)
    {
        if( m_stocks.at(i)->code() == code )
        {
            break;
        }
    }

    if(i == count)
    {
        m_stocks.append(new StockDetail(code));
        saveToFile();
        m_bNoRefreshAfterLaunch = true;
        //新增了股票，如当前未在更新，立即启动更新流程
        if(m_reply == 0)
        {
            startUpdateImmediately();
        }
    }

    return i == count;
}

void StockProvider::removeStock(const QByteArray &stockCode)
{qDebug()<<__FUNCTION__;
    int count = m_stocks.count();
    int i = 0;
    for(; i < count; i++)
    {
        if( m_stocks.at(i)->code() == stockCode )
        {
            break;
        }
    }

    if(i < count)
    {
        delete m_stocks.takeAt(i);
        saveToFile();
    }
}

void StockProvider::removeStock(int index)
{qDebug()<<__FUNCTION__;
    if(index >=0 && index < m_stocks.size())
    {
        delete m_stocks.takeAt(index);
        saveToFile();
    }
}

StockDetail * StockProvider::stock(const QByteArray &stockCode)
{qDebug()<<__FUNCTION__;
    int count = m_stocks.count();
    int i = 0;
    StockDetail * detail = 0;
    for(; i < count; i++)
    {
        detail = m_stocks[i];
        if( detail->code() == stockCode )
        {
            return detail;
        }
    }

    return 0;
}

int StockProvider::stockCount()
{qDebug()<<__FUNCTION__;
    return m_stocks.count();
}

StockDetail * StockProvider::stockAt(int index)
{
    return m_stocks[index];
}

int StockProvider::remindMode()
{qDebug()<<__FUNCTION__;
    return m_iRemindMode;
}

void StockProvider::setRemindMode(int mode)
{qDebug()<<__FUNCTION__;
    m_iRemindMode = mode;
}

void StockProvider::saveState()
{qDebug()<<__FUNCTION__;
    saveToFile();
}

void StockProvider::setUpdateInterval(int seconds)
{qDebug()<<__FUNCTION__;
    m_refreshInterval = seconds;
    //TODO: update
}

void StockProvider::onRefreshError(QNetworkReply::NetworkError code)
{qDebug()<<__FUNCTION__;
    m_reply->disconnect(this);
    m_reply->deleteLater();
    m_reply = 0;
    m_iRefreshTimer = startTimer(0);
}

void StockProvider::onRefreshFinished()
{qDebug()<<__FUNCTION__;
    m_reply->disconnect(this);
    if(m_reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "StockProvider::refreshFinished, error - " << m_reply->errorString();
        return;
    }
    else if(m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200)
    {
        qDebug() << "StockProvider::refreshFinished, but server return - " << m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        return;
    }
    //qDebug() << "onRefreshFinished";

    parseData(m_reply->readAll());
    m_reply->deleteLater();
    m_reply = 0;
    //刷新过程中没有添加新的股票才设置 m_bNoRefreshAfterLaunch
    if(m_bNoRefreshAfterLaunch &&
            m_refreshingCount >= m_stocks.size())
    {
        m_bNoRefreshAfterLaunch = false;
    }

    int elapsed = m_updateElapsed.elapsed();

    m_iRefreshTimer = startTimer(m_refreshInterval > elapsed ? m_refreshInterval - elapsed : 0);
}

void StockProvider::timerEvent(QTimerEvent *e)
{//qDebug()<<__FUNCTION__;
    int id = e->timerId();
    if(id == m_iRefreshTimer)
    {
        startUpdateImmediately();
    }
    else if(id == m_iRefreshTimeoutTimer)
    {
        killTimer(m_iRefreshTimeoutTimer);
        m_iRefreshTimeoutTimer = 0;

        if(m_iRefreshTimer > 0)
        {
            killTimer(m_iRefreshTimer);
            m_iRefreshTimer = 0;
        }
        if(m_reply)
        {
            m_reply->disconnect(this);
            m_reply->abort();
            m_reply->deleteLater();
            m_reply = 0;
        }

        startUpdate();
    }
}
//此函数是保存到文件的，
void StockProvider::saveToFile()
{qDebug()<<__FUNCTION__;
    m_bShouldSave = false;
    int count = m_stocks.size();
    if(count == 0)
    {
        return;
    }

    QFile file("stocks");
    if(!file.open(QFile::WriteOnly | QFile::Truncate))
    {
        qDebug() << "open stocks for write failed";
        return;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    out << "<stocks>\n";

    out << "  <remindMode>" << m_iRemindMode << "</remindMode>\n";

    StockDetail * detail = 0;
    for(int i = 0; i < count; i++)
    {
        detail = m_stocks.at(i);
        out << "  <stock>\n";
        out << "    <code>" << detail->code() << "</code>\n";

        //QString strName = detail->name().data();
        QString strName = detail->content(stock_name).data();
        if(strName != "-")
        {
            out << "    <name>" << strName << "</name>\n";
        }

        if(detail->m_stopWinPrice >= 0)
        {
            out << "    <stopwin>" << detail->m_stopWinPrice << "</stopwin>\n";
        }
        if(detail->m_stopLosePrice >= 0)
        {
            out << "    <stoplose>" << detail->m_stopLosePrice << "</stoplose>\n";
        }
        out << "  </stock>\n";
    }

    out << "</stocks>";
    file.close();
}

void StockProvider::readFromFile()
{qDebug()<<__FUNCTION__;
    QFile file("stocks");
    if(!file.open(QFile::ReadOnly))
    {
        qDebug() << "open stocks for read failed";
        return;
    }

    QXmlStreamReader reader;
    reader.setDevice(&file);
    QStringRef elementName;
    StockDetail * stockinfo = 0;

    while(!reader.atEnd())
    {
        reader.readNext();
        if(reader.isStartElement())
        {
            elementName = reader.name();
            if( elementName == "code")
            {
                stockinfo = new StockDetail(reader.readElementText().toLatin1());
            }
            else if( elementName == "name")
            {
                stockinfo->m_details[stock_name] = reader.readElementText().toUtf8();
            }
            else if( elementName == "stopwin")
            {
                stockinfo->setStopWinPrice(reader.readElementText().toDouble());
            }
            else if( elementName == "stoplose" )
            {
                stockinfo->setStopLosePrice(reader.readElementText().toDouble());
            }
            else if( elementName == "remindMode")
            {
                m_iRemindMode = reader.readElementText().toInt();
            }
        }
        else if(reader.isEndElement())
        {
            elementName = reader.name();
            if( elementName == "stock")
            {
                m_stocks.append(stockinfo);
                stockinfo = 0;
            }
        }
    }
    file.close();
}

void StockProvider::startUpdate()
{//qDebug()<<__FUNCTION__;
    if(m_stocks.size() == 0 ) return;
    if(!isTransactTime() && !m_bNoRefreshAfterLaunch)
    {
        //schedule later
        m_iRefreshTimer = startTimer(m_refreshInterval);
        return;
    }

    QString strUrl("http://hq.sinajs.cn/list=");
    m_refreshingCount = m_stocks.size();
    StockDetail * detail = 0;
    for(int i = 0; i < m_refreshingCount; i++)
    {
        detail = m_stocks.at(i);
        strUrl.append(detail->code());
        //qDebug()<<detail->handoverRate();
        //qDebug()<<detail->yesterdayClosePrice();
        strUrl.append(',');
    }
    if(strUrl.endsWith(','))
    {
        strUrl.chop(1);
    }

    //qDebug() << "start get - " << strUrl;
    QUrl qurl(strUrl);
    QNetworkRequest req(qurl);
    m_reply = m_nam.get(req);
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(onRefreshError(QNetworkReply::NetworkError)));
    connect(m_reply, SIGNAL(finished()), this, SLOT(onRefreshFinished()));

    m_iRefreshTimeoutTimer = startTimer(20000);
    m_updateElapsed.restart();
    emit beginRefresh();
}

void StockProvider::parseData(const QByteArray &data)
{qDebug()<<__FUNCTION__;
    QList<QByteArray> stocksData = data.split(';');
    int size = stocksData.size();
    if(size == 0) return;

    m_strRemind.clear();

    for(int i = 0; i < size; i++)
    {
        QByteArray  d = stocksData.at(i).trimmed();
        if(d.startsWith(STOCK_START_STRING))
        {
            int start = STOCK_START_STRING_LEN;
            int index = d.indexOf('=');
            if(index > 0)
            {
                QByteArray stockCode = d.mid(start, index - start);
                QByteArray perData = d.mid(index+2);
                if(perData.endsWith('\"'))
                {
                    perData.chop(1);
                }
                updateStockDetail(stockCode, perData);
            }
        }
    }
    if(m_bShouldSave) saveToFile();

    emit refreshed();

    if(m_strRemind.length() > 0) emit remind(m_strRemind);
}

void StockProvider::updateStockDetail(const QByteArray &stockCode, const QByteArray &data)
{qDebug()<<__FUNCTION__;
    if(data.length() < 64) return;

    int count = m_stocks.count();
    int i = 0;
    for(; i < count; i++)
    {
        if( m_stocks.at(i)->code() == stockCode )
        {
            break;
        }
    }

    if(i < count)
    {
        StockDetail * detail = m_stocks.at(i);
        QByteArray stockName = detail->m_details[stock_name];
        if(stockName == "-")
        {
            m_bShouldSave = true;
        }
        qDebug()<<__FUNCTION__<<data;
        detail->m_details = data.split(',');
        detail->m_details[transaction_stocks].chop(2);
        double money = detail->m_details.at(transaction_money).toDouble() / 10000;
        detail->m_details[transaction_money] = QByteArray::number(money,'f',0);
        if(stockName != "-")
        {
            detail->m_details[stock_name] = stockName;
        }
        else
        {
            QTextCodec * gbkCodec = QTextCodec::codecForName("GBK");
            if(gbkCodec)
            {
                detail->m_details[stock_name] = gbkCodec->toUnicode(detail->m_details.at(stock_name).data()).toUtf8();
            }
        }
        updateRemindContents(detail);
    }
}

void StockProvider::updateRemindContents(StockDetail *stock)
{qDebug()<<__FUNCTION__;
    if(stock->arriveStopLose())
    {
        m_strRemind += QString("%1 : %2\n")
                .arg(stock->code().data())
                .arg(stock->content(current_price).data());
                //.arg(stock->currentPrice().data());
    }
    else if(stock->arriveStopWin())
    {
        m_strRemind += QString("%1: %2\n")
                .arg(stock->code().data())
                .arg(stock->content(current_price).data());
                //.arg(stock->currentPrice().data());
    }
}

bool StockProvider::isTransactTime()
{//qDebug()<<__FUNCTION__;
    static QTime amStartTime(9, 9, 50);
    static QTime amStopTime(11, 31);
    static QTime pmStartTime(12, 59, 50);
    static QTime pmStopTime(15, 2);
    QTime t = QTime::currentTime();
    return ((t >= amStartTime && t <= amStopTime) ||
            (t >= pmStartTime && t <= pmStopTime));
}

void StockProvider::startUpdateImmediately()
{//qDebug()<<__FUNCTION__;
    if(m_iRefreshTimer > 0)
    {
        killTimer(m_iRefreshTimer);
        m_iRefreshTimer = 0;
    }
    if(m_iRefreshTimeoutTimer > 0)
    {
        killTimer(m_iRefreshTimeoutTimer);
        m_iRefreshTimeoutTimer = 0;
    }

    startUpdate();
}
