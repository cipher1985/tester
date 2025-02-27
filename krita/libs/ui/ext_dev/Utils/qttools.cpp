#include "qttools.h"

#include <QColor>
#include <QUuid>
#include <QRandomGenerator>
#include <QJsonDocument>

#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QApplication>

#include <QTimer>
#include <QStandardPaths>
#include <QPainterPath>

#ifdef QT_USE_NETWORK
#include <QNetworkAccessManager>
#include <QNetworkReply>
#endif

namespace QtTools
{
QString createUuid()
{
    QString uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
    return uuid;
}

QString createId()
{
    QString id = QUuid::createUuid().toString(QUuid::Id128);
    return id;
}

quint32 random()
{
    return QRandomGenerator::global()->generate();
}

quint32 random(quint32 maxValue)
{
    return QRandomGenerator::global()->bounded(maxValue);
}

quint32 random(quint32 minValue, quint32 maxValue)
{
    return QRandomGenerator::global()->bounded(minValue, maxValue);
}

double randomDouble(double maxValue)
{
    return QRandomGenerator::global()->bounded(maxValue);
}

QColor randomColor()
{
    return QColor::fromRgb(QRandomGenerator::global()->generate());
}

QPixmap getStdPixmap(QStyle::StandardPixmap pixmap)
{
    return QApplication::style()->standardPixmap(pixmap);
}

QString jsonToText(const QJsonObject &obj)
{
    QJsonDocument jsonDoc(obj);
    return jsonDoc.toJson(QJsonDocument::Compact);
}

QString jsonToText(const QJsonArray &arr)
{
    QJsonDocument jsonDoc(arr);
    return jsonDoc.toJson(QJsonDocument::Compact);
}

QJsonObject textToJsonObject(const QString &text)
{
    QJsonObject obj;
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8(), &error);
    if (error.error == QJsonParseError::NoError)
        obj = doc.object();
    return obj;
}

QJsonArray textToJsonArray(const QString &text)
{
    QJsonArray arr;
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8(), &error);
    if (error.error == QJsonParseError::NoError)
        arr = doc.array();
    return arr;
}

QStringList selectFilesDialog(int mode, QWidget *parent, const QString &caption, const QString &defaultFile, const QString &defaultExt, const QString &dir, const QStringList &filters, int filterIndex)
{
    QFileDialog dialog(parent, caption, dir);
    dialog.setStyleSheet(
        "QWidget{ background:#F9F9F9; color:black; }"
        "QComboBox, QPushButton{ min-height: 24px; }"
        "QPushButton:disabled{ color:gray; }"
        "QLineEdit{ min-height: 23px; }");
    dialog.setMinimumSize(600, 400);
    dialog.setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    dialog.setWindowFlag(Qt::WindowStaysOnTopHint);
    dialog.setOption(QFileDialog::DontUseNativeDialog);
    dialog.setNameFilters(filters);
    if(filterIndex >= 0 && filterIndex < filters.count())
        dialog.selectNameFilter(filters[filterIndex]);
    //设置侧边路径
    QList<QUrl> urls;
    //主路径
    QUrl homeUrl = QUrl::fromLocalFile(QDir::homePath());
    urls.append(homeUrl);
    //文档路径
    QUrl app_url = QUrl::fromLocalFile(
        QStandardPaths::writableLocation(
            QStandardPaths::DocumentsLocation));
    urls.append(app_url);
    //桌面路径
    QUrl desktopUrl = QUrl::fromLocalFile(
        QStandardPaths::writableLocation(
            QStandardPaths::DesktopLocation));
    urls.append(desktopUrl);
    //程序位置路径
    //QUrl appUrl = QUrl::fromLocalFile(QCoreApplication::applicationDirPath());
    //urls.append(appUrl);
    //运行路径
    //QUrl curUrl = QUrl::fromLocalFile(QDir::currentPath());
    //urls.append(curUrl);
    //磁盘路径
    QFileInfoList drivelist = QDir::drives();
    for(QFileInfo& si : drivelist) {
        urls.append(QUrl::fromLocalFile(si.absolutePath()));
    }
    dialog.setSidebarUrls(urls);
    //设置文件选择模式
    switch (mode) {
    case 0://打开文件
        dialog.setAcceptMode(QFileDialog::AcceptOpen);
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setLabelText(QFileDialog::Accept, u8"打开");
        break;
    case 1://保存文件
        dialog.setAcceptMode(QFileDialog::AcceptSave);
        dialog.setFileMode(QFileDialog::AnyFile);
        dialog.setOption(QFileDialog::DontConfirmOverwrite);
        dialog.setLabelText(QFileDialog::Accept, u8"保存");
        break;
    case 2://选择文件夹
        dialog.setAcceptMode(QFileDialog::AcceptOpen);
        dialog.setFileMode(QFileDialog::Directory);
        dialog.setOption(QFileDialog::ShowDirsOnly);
        dialog.setLabelText(QFileDialog::Accept, u8"选择");
        break;
    case 3://选择多文件
    default:
        dialog.setAcceptMode(QFileDialog::AcceptOpen);
        dialog.setFileMode(QFileDialog::ExistingFiles);
        dialog.setLabelText(QFileDialog::Accept, u8"选择");
        break;
    }
    //设置标签文本
    dialog.setLabelText(QFileDialog::LookIn, u8"当前路径:");
    dialog.setLabelText(QFileDialog::FileName, u8"文件名:");
    dialog.setLabelText(QFileDialog::FileType, u8"文件类型:");
    dialog.setLabelText(QFileDialog::Reject, u8"取消");
    dialog.selectFile(defaultFile);
    dialog.setDefaultSuffix(defaultExt);
    QStringList fileList;
    while(1) {
        int ret = dialog.exec();
        if(ret != QFileDialog::Accepted)
            return QStringList();
        fileList = dialog.selectedFiles();
        // 保存框检查文件是否已存在
        if (mode == 1 && QFile::exists(fileList[0])) {
            // 弹出中文提示
            QMessageBox messageBox(parent);
            messageBox.setWindowFlag(Qt::WindowStaysOnTopHint);
            messageBox.setWindowTitle(caption.isEmpty() ? u8"保存提示" : caption);
            messageBox.setText(QString(u8"%1 文件已存在，是否覆盖？").arg(
                QFileInfo(fileList[0]).fileName()));
            messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            messageBox.setDefaultButton(QMessageBox::No);
            messageBox.setButtonText(QMessageBox::Yes, u8"确定");
            messageBox.setButtonText(QMessageBox::No, u8"取消");
            if (messageBox.exec() != QMessageBox::Yes) {
                continue;
            }
        }
        break;
    }
    return fileList;
}
#ifdef QT_USE_NETWORK
int syncDownloadFile(const QString &pathFileName,
    const QString &downloadUrl, qint64 timeoutMS)
{
    QByteArray data;
    int ret = syncDownloadData(data, downloadUrl, timeoutMS);
    if(ret != QNetworkReply::NoError)
        return ret;
    QFile saveFile(pathFileName);
    if(!saveFile.open(QFile::WriteOnly))
        return -2;
    saveFile.write(data);
    saveFile.close();
    return QNetworkReply::NoError;
}

int syncDownloadData(QByteArray &data,
    const QString &downloadUrl, qint64 timeoutMS)
{
    //创建网络访问器
    QNetworkAccessManager manager;
    //网络回复对象
    QNetworkReply *reply = manager.get(QNetworkRequest(downloadUrl));
    if (!reply)
        return -1;
    reply->setParent(&manager);
    //开启子事件循环
    QEventLoop loop;
    //请求结束并下载完成后，退出子事件循环
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    //超时控制
    QTimer* timer = new QTimer(&manager);
    if(timeoutMS > 0) {
        QObject::connect(timer, &QTimer::timeout, [=] {
            timer->stop();
            if(!reply->isFinished())
                reply->abort();
        });
        timer->start(timeoutMS);
    }
    //循环事件
    loop.exec();
    //关闭计时器
    if(timer->isActive())
        timer->stop();
    //获得数据
    QNetworkReply::NetworkError error = reply->error();
    if (error == QNetworkReply::NoError)
        data = reply->readAll();
    reply->deleteLater();
    return error;
}
#endif
QPainterPath CreateRoundRectPath(int w, int h, int radiusTopLeft, int radiusTopRight, int radiusBottomLeft, int radiusBottomRight)
{
    QPainterPath path;
    path.moveTo(radiusTopLeft, 0);
    path.lineTo(w - radiusTopRight, 0);
    path.arcTo(w - radiusTopRight * 2, 0, radiusTopRight * 2, radiusTopRight * 2, 90, -90);
    path.lineTo(w, h - radiusBottomRight);
    path.arcTo(w - radiusBottomRight * 2, h - radiusBottomRight * 2, radiusBottomRight * 2, radiusBottomRight * 2, 0, -90);
    path.lineTo(radiusBottomLeft, h);
    path.arcTo(0, h - radiusBottomLeft * 2, radiusBottomLeft * 2, radiusBottomLeft * 2, 270, -90);
    path.lineTo(0, radiusTopLeft);
    path.arcTo(0, 0, radiusTopLeft * 2, radiusTopLeft * 2, 180, -90);
    return path;
}

QPainterPath CreateBubblePath(int rectW, int rectH, int radius,
    PopArrowDir arrowDir, int arrowOffset, int arrowHeight,
    int arrowMinPos, int arrowMaxPos, QSize* retRealSize)
{
    return CreateBubblePath(rectW, rectH,
        radius, radius, radius, radius,
        arrowDir, arrowOffset, arrowHeight,
        arrowMinPos, arrowMaxPos, retRealSize);
}

QPainterPath CreateBubblePath(int rectW, int rectH,
    int radiusTopLeft, int radiusTopRight,
    int radiusBottomLeft, int radiusBottomRight,
    PopArrowDir arrowDir, int arrowOffset, int arrowHeight,
    int arrowMinPos, int arrowMaxPos, QSize* retRealSize)
{
    QPainterPath path = CreateRoundRectPath(rectW, rectH,
        radiusTopLeft, radiusTopRight, radiusBottomLeft, radiusBottomRight);
    int finalWidth = rectW;
    int finalHeight = rectH;
    //箭头顶点
    QPointF tipPoint;
    //三角边线
    QLineF edgeLine;

    switch (arrowDir) {
    case PopArrowDir::Left:
        tipPoint = QPoint(-arrowHeight, arrowOffset);
        edgeLine = {QPoint(0, arrowMinPos), QPoint(0, arrowMaxPos)};
        finalWidth += arrowHeight;
        break;
    case PopArrowDir::Right:
        tipPoint = QPoint(rectW + arrowHeight, arrowOffset);
        edgeLine = {QPoint(rectW, arrowMinPos), QPoint(rectW, arrowMaxPos)};
        finalWidth += arrowHeight;
        break;

    case PopArrowDir::Top:
        tipPoint = QPoint(arrowOffset, -arrowHeight);
        edgeLine = {QPoint(arrowMinPos, 0), QPoint(arrowMaxPos, 0)};
        finalHeight += arrowHeight;
    break;

    case PopArrowDir::Bottom:
        tipPoint = QPoint(arrowOffset, rectH + arrowHeight);
        edgeLine = {QPoint(arrowMinPos, rectH), QPoint(arrowMaxPos, rectH)};
        finalHeight += arrowHeight;
    break;

    default:  // PopArrowDir::None
        if (retRealSize)
            *retRealSize = {finalWidth, finalHeight};
        return path;
    }

    QPainterPath arrow;
    arrow.moveTo(edgeLine.p1());
    arrow.lineTo(tipPoint);
    arrow.lineTo(edgeLine.p2());
    path = path.united(arrow);

    if (retRealSize)
        *retRealSize = {finalWidth, finalHeight};

    switch (arrowDir) {
    case PopArrowDir::Left:
        path.translate(arrowHeight, 0);
        break;
    case PopArrowDir::Top:
        path.translate(0, arrowHeight);
        break;
    }
    return path;
}
}
