#include "const.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include <QTcpSocket>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

Client::Client(const QString &strHost, int nPort, QWidget *parent) : QWidget (parent), m_nNextBlockSize(0)
{
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(strHost, static_cast<quint16>(nPort));
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
    connect(&LinkSignal::Instance(), SIGNAL(signalGetScore(int)), this, SLOT(slotGetScore(int)));
    connect(&LinkSignal::Instance(), SIGNAL(signalLineEditText(QString)), this, SLOT(slotLineEditText(QString)));
    connect(&LinkSignal::Instance(), SIGNAL(signalEndGameCheck(bool)), this, SLOT(slotEndGameCheck(bool)));
    connect(&LinkSignal::Instance(), SIGNAL(signalSendToServerGet()), this, SLOT(slotSendToServerGet()));
    connect(&LinkSignal::Instance(), SIGNAL(signalSendToServerSet()), this, SLOT(slotSendToServerSet()));
}

QString Client::addToJson(QString str)
{
    QJsonDocument document;
    QJsonObject root = document.object();
    root.insert(_lineEditText, QJsonValue::fromVariant(str));
    document.setObject(root);
    QString strJson(document.toJson(QJsonDocument::Compact));
    return strJson;
}

void Client::slotLineEditText(QString lineEditText)
{
    _lineEditText = lineEditText;
    qDebug() << "NICKNAME:" << _lineEditText;
}

void Client::slotEndGameCheck(bool endGame)
{
    _endGame = endGame;
}

void Client::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_5_8);
    if (!m_nNextBlockSize)
    {
        in >> m_nNextBlockSize;
    }
    QString str;
    in >> str;
    m_nNextBlockSize = 0;
    if(_endGame)
    {
        insertDataReadyRead(str);
    }
}

void Client::insertDataReadyRead(QString str)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject jsObj = jsonDoc.object();
    QMap<int, QString> map;
    foreach(const QString& key, jsObj.keys())
    {
        QJsonValue value = jsObj.value(key);
        int valueInt = value.toString().toInt();
        map.insert(valueInt, key);
        if (lastMapValue < valueInt)
        {
            lastMapValue = valueInt;
        }
    }
    QMap<int, QString>::const_iterator i = map.constEnd();
    do {
        --i;
        QString textLine = i.value() + " : " + QString::number(i.key());
        LinkSignal::Instance().descriptionEndGame(textLine);
    } while (i != map.constBegin());
}

void Client::slotGetScore(int score)
{
    _score = score;
}

void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                         "The host was not found." :
                         err == QAbstractSocket::RemoteHostClosedError ?
                         "The remote host is closed." :
                         err == QAbstractSocket::ConnectionRefusedError ?
                         "The connection was refused." :
                         QString(m_pTcpSocket->errorString())
                        );
    QMessageBox::critical(nullptr, "Server Error", "Unable to start the server:" + strError);
}

void Client::slotSendToServerGet()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << quint16(0) << addToJson("onlyRead");
    out.device()->seek(0);
    out << quint16(static_cast<quint16>(arrBlock.size()) - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}

void Client::slotSendToServerSet()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << quint16(0) << addToJson(QString::number(_score));
    out.device()->seek(0);
    out << quint16(static_cast<quint16>(arrBlock.size()) - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}

void Client::slotConnected()
{
    qDebug() << "CONNECTED!";
}
