#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>

class Client : public QWidget
{
    Q_OBJECT
public:
    Client(const QString& strHost ,int nPort, QWidget *parent = nullptr);
private:
    QString addToJson(QString str);
    QTcpSocket* m_pTcpSocket;
    quint16 m_nNextBlockSize;
    bool _endGame = false;
    int _score = 0;
    int lastMapValue = 0;
    int yLeadersLineStep = 30;
    QString _lineEditText;
    void insertDataReadyRead(QString str);
    void bubbleSortScore(QMultiMap<int, QString> map1, QMultiMap<int, QString> map2, int sumLine);
private slots:
    void slotGetScore(int score);
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError err);
    void slotSendToServerGet();
    void slotSendToServerSet();
    void slotConnected();
    void slotLineEditText(QString lineEditText);
    void slotEndGameCheck(bool endGame);
};

#endif // CLIENT_H
