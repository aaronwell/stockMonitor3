#include <QQmlContext>
#include "stockModel.h"
#include "stock.h"
#include <QTranslator>
#if defined(Q_OS_ANDROID)
#include <QtGui/QGuiApplication>
#include "notifyAndroid.h"
#elif defined(Q_OS_IOS)
#else
#include <QApplication>
#endif
#include <QDebug>
#include <QQuickView>

#include "Python.h"


int main(int argc, char *argv[])
{
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
    QGuiApplication app(argc, argv);
#else
    QApplication app(argc, argv);
#endif



    //初始化python模块
        Py_Initialize();
        if ( !Py_IsInitialized() )
        {
            return -1 ;
        }
        //导入test.py模块
        PyObject* pModule = PyImport_ImportModule("getData");
        if (!pModule)
        {
            qDebug()<<"Cant open python file!\n";
            return -1 ;
        }
        //获取test模块中的函数
        PyObject* pFun= PyObject_GetAttrString(pModule,"getData");

        if(!pFun)
        {
            qDebug()<<"Get function hello failed";
            return -1 ;
        }
        qDebug()<<"haha1";
        //调用hello函数
        PyObject_CallFunction(pFun,NULL);
        qDebug()<<"haha2";
        //结束，释放python
        Py_Finalize();


    //installLogcatMessageHandler("stockMonitor");
    //QTranslator t;//翻译包
    //t.load(":/stockMonitor_zh.qm");
    //app.installTranslator(&t);

    StockModel *model = new StockModel;
    QQuickView viewer;
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    QQmlContext *ctx = viewer.rootContext();
    ctx->setContextProperty("stockModel", model);
    ctx->setContextProperty("currentStock", model->currentStock());
    viewer.setSource(QUrl("qrc:/qml/main.qml"));


    viewer.show();

    return app.exec();
}
