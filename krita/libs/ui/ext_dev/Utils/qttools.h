#ifndef QTTOOLS_H
#define QTTOOLS_H

#include <QObject>
#include <QStyle>
#include <QJsonObject>
#include <QJsonArray>

//隐式连接信号
#ifndef Q_CONNECT
#define Q_CONNECT(obj, objtype, signal, lambda) \
    connect(obj, &objtype::signal, this, lambda)
#endif //Q_CONNECT

#ifndef Q_CONNECT_PARAM
#define Q_CONNECT_PARAM(obj, objtype, signal, lambda, ...) \
    connect(obj, static_cast<void(objtype::*)(__VA_ARGS__)>(&objtype::signal), this, lambda)
#endif //Q_CONNECT_PARAM

//直接连接信号
#ifndef Q_CONNECT_SLOT
#define Q_CONNECT_SLOT(sigObj, signal, slotObj, slot) \
    connect(sigObj, SIGNAL(signal), slotObj, SLOT(slot))
#endif //Q_CONNECT_SLOT

//断开全部连接信号
#ifndef Q_DISCONNECT_ALL
#define Q_DISCONNECT_ALL(obj) \
    disconnect(obj, 0, 0, 0)
#endif //Q_DISCONNECT_ALL
//断开指定连接信号
#ifndef Q_DISCONNECT
#define Q_DISCONNECT(obj, signal) \
    disconnect(obj, SIGNAL(signal), 0, 0)
#endif //Q_DISCONNECT
//断开与指定对象的所有连接
#ifndef Q_DISCONNECT_OBJ
#define Q_DISCONNECT_OBJ(sigObj, slotObj) \
    disconnect(sigObj, 0, slotObj, 0)
#endif //Q_DISCONNECT_OBJ

namespace QtTools
{
    //生成uuid
    extern QString createUuid();
    extern QString createId();
    //生成随机数
    extern quint32 random();
    extern quint32 random(quint32 maxValue);
    extern quint32 random(quint32 minValue, quint32 maxValue);
    extern double randomDouble(double maxValue = 1.0);
    //获得内置图标
    QPixmap getStdPixmap(QStyle::StandardPixmap pixmap);
    //生成随机颜色
    extern QColor randomColor();
    //json转文本
    extern QString jsonToText(const QJsonObject& obj);
    extern QString jsonToText(const QJsonArray& arr);
    //文本转json
    extern QJsonObject textToJsonObject(const QString& text);
    extern QJsonArray textToJsonArray(const QString& text);
    //选择文件对话框，mode：0.打开文件1.保存文件2.选择目录3.打开多个文件
    extern QStringList selectFilesDialog(int mode = 0,
        QWidget* parent = nullptr, const QString &caption = QString(),
        const QString &defaultFile = QString(), const QString &defaultExt = QString(),
        const QString &dir = QString(), const QStringList &filters = QStringList(), int filterIndex = 0);
#ifdef QT_USE_NETWORK
    //同步下载网络文件至本地(返回值为QNetworkReply::NetworkError,其它负数如-1.请求出错-2.无法创建本地文件)
    extern int syncDownloadFile(const QString& pathFileName,
        const QString& downloadUrl, qint64 timeoutMS = 5000);
    extern int syncDownloadData(QByteArray& data,
        const QString& downloadUrl, qint64 timeoutMS = 5000);
#endif

    //创建非对称圆角矩形
    extern QPainterPath CreateRoundRectPath(int w, int h,
        int radiusTopLeft, int radiusTopRight,
        int radiusBottomLeft, int radiusBottomRight);
    /**
     * 功能       创建气泡路径
     * @参数      rectW, rectH                            主体矩形区域宽高
     * @参数      radius                                  圆角边框
     * @参数      arrowDir                                箭头方向(None无箭头)
     * @参数      arrowOffset                             箭头尖角位置坐标(顶点)
     * @参数      arrowHeight                             箭头尖角高度
     * @参数      arrowMinPos                             最小偏移坐标(起点)
     * @参数      arrowMaxPos                             最大偏移坐标(终点)
     * @参数      retRealSize                             返回生成路径最终尺寸
     * @返回值    生成的气泡路径
     */
    //箭头方向
    enum class PopArrowDir
    {
        None = -1,
        Left,
        Top,
        Right,
        Bottom
    };
    extern QPainterPath CreateBubblePath(
        int rectW, int rectH, int radius,
        PopArrowDir arrowDir, int arrowOffset, int arrowHeight,
        int arrowMinPos, int arrowMaxPos,
        QSize* retRealSize = nullptr);
    extern QPainterPath CreateBubblePath(int rectW, int rectH,
        int radiusTopLeft, int radiusTopRight,
        int radiusBottomLeft, int radiusBottomRight,
        PopArrowDir arrowDir, int arrowOffset, int arrowHeight,
        int arrowMinPos, int arrowMaxPos,
        QSize* retRealSize = nullptr);
}

#endif // QTTOOLS_H
