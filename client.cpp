//#include "const.h"

//#include <QPushButton>
//#include <QVBoxLayout>
//#include <QLabel>
//#include <QTime>
//#include <QTcpSocket>
//#include <QJsonArray>
//#include <QJsonObject>
//#include <QJsonDocument>

//client::client(const QString &strHost, int nPort, QWidget *parent) : QWidget (parent), m_nNextBlockSize(0)
//{
//    m_pTcpSocket = new QTcpSocket(this);
//    m_pTcpSocket->connectToHost("localhost", static_cast<quint16>(8080));

//    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
//    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
//    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

//    //connect(m_ptxtInput, SIGNAL(returnPressed()), this, SLOT(slotSendToServer()));

//    //connect(pcmd, SIGNAL(clicked()), SLOT(slotSendToServer()));
//}

//QString client::addToJson(QString m_ptxtInput)
//{
//    QJsonDocument document;
//    QJsonObject root = document.object();
//    root.insert(QTime::currentTime().toString(), QJsonValue::fromVariant(m_ptxtInput));
//    document.setObject(root);
//    QString strJson(document.toJson(QJsonDocument::Compact));
//    return strJson;
//}

//void client::slotReadyRead()
//{
//    QDataStream in(m_pTcpSocket);
//    in.setVersion(QDataStream::Qt_5_8);
//    for (;;)
//    {
//        if (!m_nNextBlockSize)
//        {
//            if (static_cast<quint16>(m_pTcpSocket->bytesAvailable()) < sizeof(quint16))
//            {
//                   break;
//            }
//            in >> m_nNextBlockSize;
//        }

//        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize)
//        {
//            break;
//        }

//        QString str;
//        in >> str;

//        m_nNextBlockSize = 0;
//    }
//}

//void client::slotError(QAbstractSocket::SocketError err)
//{
//    QString strError =
//            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
//                         "The host was not found." :
//                         err == QAbstractSocket::RemoteHostClosedError ?
//                         "The remote host is closed." :
//                         err == QAbstractSocket::ConnectionRefusedError ?
//                         "The connection was refused." :
//                         QString(m_pTcpSocket->errorString())
//                        );
//    //m_ptxtInfo->append(strError);
//}

//void client::slotSendToServer()
//{
//    QByteArray  arrBlock;
//    QDataStream out(&arrBlock, QIODevice::WriteOnly);

//    out.setVersion(QDataStream::Qt_5_8);
//    //out << quint16(0) << QTime::currentTime() << addToJson(m_ptxtInput->text());

//    out.device()->seek(0);
//    out << quint16(static_cast<quint16>(arrBlock.size()) - sizeof(quint16));

//    m_pTcpSocket->write(arrBlock);
//    //m_ptxtInput->setText("");
//}

//void client::slotConnected()
//{
//    qDebug() << "CONNECTED!";
//}
