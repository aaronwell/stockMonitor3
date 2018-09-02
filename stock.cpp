#include "stock.h"
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
StockState::StockState()
    : m_detail(0), m_provider(0)
    , m_indexInProvider(0)
{
    qDebug()<<__FUNCTION__;
}
StockState::StockState(const StockState &rhs)
    : m_detail(rhs.m_detail),
      m_provider(rhs.m_provider),
      m_indexInProvider(rhs.m_indexInProvider)
{
    qDebug()<<__FUNCTION__;
}

StockState::~StockState()
{
    qDebug()<<__FUNCTION__;
}

QString StockState::loss()
{
    qDebug()<<__FUNCTION__;
    return QString::number(m_detail->stopLosePrice(), 'f', 2);
}

void StockState::setLoss(QString loss)
{
    qDebug()<<__FUNCTION__;
    m_detail->setStopLosePrice(loss.toDouble());
}

QString StockState::gain()
{
    qDebug()<<__FUNCTION__;
    return QString::number(m_detail->stopWinPrice(), 'f', 2);
}

void StockState::setGain(QString gain)
{
    qDebug()<<__FUNCTION__;
    m_detail->setStopWinPrice(gain.toDouble());
}

QString StockState::code()
{
    qDebug()<<__FUNCTION__;
    return m_detail->code();
    //return m_detail->content();
}

QString StockState::name()
{
    qDebug()<<__FUNCTION__;
    //return m_detail->name();
    return m_detail->content(stock_name);
}

QString StockState::price()
{
    qDebug()<<__FUNCTION__;
    //return m_detail->currentPrice();
    return m_detail->content(current_price);
}

int StockState::index()
{
    qDebug()<<__FUNCTION__;
    return m_indexInProvider;
}

void StockState::setIndex(int index)
{
    qDebug()<<__FUNCTION__;
    m_indexInProvider = index;
    m_detail = m_provider->stockAt(index);
}
