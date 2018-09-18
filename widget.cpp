#include "ui_widget.h"
#include "const.h"

#include <QTime>
#include <QTcpSocket>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QMap>
#include <QList>

Widget::Widget(const QString &strHost, int nPort, QWidget *parent) :
    QWidget(parent),
     m_nNextBlockSize(0),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(strHost, static_cast<quint16>(nPort));
    createScene();
    timers(startGame);
    createNameLineEdit();
    startGame = false;
    createMenu();
    hideMenu();
    connections();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::connections()
{
    connect(animationTimer, SIGNAL(timeout()), scene, SLOT(advance()));
    connect(generatorTimerAsteroid, SIGNAL(timeout()), this, SLOT(onGenerateAsteroid()));
    connect(generatorTimerEnemySpaceship, SIGNAL(timeout()), this, SLOT(onGenerateEnemySpaceship()));
    connect(sceneHideTimer, SIGNAL(timeout()), this, SLOT(stopGame()));
    connect(&LinkSignal::Instance(), SIGNAL(signalEndGameMessage()), this, SLOT(endGameMessage()));
    connect(&LinkSignal::Instance(), SIGNAL(signalDestroy()), this, SLOT(sumScore()));
    connect(&LinkSignal::Instance(), SIGNAL(signalDestroyEnemySpaceship()), this, SLOT(lifeChangerEnemySpaceship()));
    connect(buttonNewGame, SIGNAL(clicked()), this, SLOT(newGame()));
    connect(buttonLeaders, SIGNAL(clicked()), this, SLOT(showLeaders()));
    connect(buttonQuitGame, SIGNAL(clicked()), this, SLOT(close()));
    connect(buttonBack, SIGNAL(clicked()), this, SLOT(showMenu()));
    connect(lineEditName, SIGNAL(returnPressed()), this, SLOT(checkNickName()));
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
}

void Widget::createSpaceship()
{
    this->_spaceship = new Spaceship();
    scene->addItem(_spaceship);
}

void Widget::createScene()
{
    scene = new QGraphicsScene(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, this);
    scene->setStickyFocus(true);
    QPixmap pim(":/images/space.jpg");
    scene->setBackgroundBrush(pim.scaled(SCREEN_WIDTH, SCREEN_HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->graphicsView->setScene(scene);
}

void Widget::timers(bool startGame)
{
    animationTimer = new QTimer(this);
    generatorTimerAsteroid = new QTimer(this);
    generatorTimerEnemySpaceship = new QTimer(this);
    sceneHideTimer = new QTimer(this);
    if (startGame)
    {
        return;
    }
    timersStart();
}

void Widget::timersStart()
{
    animationTimer->start(TIME_ANIMATION/60);
    generatorTimerAsteroid->start(TIME_GENERATION_ASTEROID);
    generatorTimerEnemySpaceship->start(TIME_GENERATION_ENEMY_SPACESHIP);
}

void Widget::timersStop()
{
    sceneHideTimer->stop();
    animationTimer->stop();
    generatorTimerAsteroid->stop();
    generatorTimerEnemySpaceship->stop();
}
void Widget::descriptionScore(int size, QString fontType, QString textData, QColor textColor, int setPosX, int setPosY)
{
    QFont fontScore;
    fontScore.setPointSize(size);
    fontScore.setFamily(fontType);
    score = new QGraphicsTextItem;
    score = scene->addText(textData);
    score->setPos(setPosX, setPosY);
    score->setDefaultTextColor(textColor);
    score->setFont(fontScore);
}

void Widget::descriptionEndGame(int size, QString fontType, QString textData, QColor textColor, int setPosX, int setPosY)
{
    QFont fontLose;
    fontLose.setPointSize(size);
    fontLose.setFamily(fontType);
    lose = new QGraphicsTextItem;
    lose = scene->addText(textData);
    lose->setPos(setPosX, setPosY);
    lose->setDefaultTextColor(textColor);
    lose->setFont(fontLose);
}

void Widget::endGameMessage()
{
    if (!endGame) {
        return;
    }
    descriptionEndGame(80, "Unispace", "YOU LOSE!", Qt::yellow, 110, 210);
    endGame = false;
    sceneHideTimer->start(TIME_HIDE_SCENE);
}

void Widget::onGenerateAsteroid()
{
    this->_asteroid = new Asteroid(scene->sceneRect().width());
    scene->addItem(_asteroid);
}

void Widget::onGenerateEnemySpaceship()
{
    this->_enemySpaceship = new EnemySpaceship(scene->sceneRect().width());
    scene->addItem(_enemySpaceship);
}

void Widget::sumScore()
{
    _score++;
    score->setPlainText(QString::number(_score));
}

void Widget::checkNickName()
{
    if (lineEditName->text() == "")
    {
        return;
    }
    showMenu();
}

void Widget::createNameLineEdit()
{
    lineEditName = new QLineEdit("", this);
    lineEditName->setMaxLength(15);
    lineEditName->setPlaceholderText("Insert your nickname...");
    lineEditName->setStyleSheet("font: 25px");
    lineEditName->setGeometry(QRect(QPoint(250, 275), QSize(300, 50)));
}

void Widget::createMenu()
{
    buttonNewGame = new QPushButton("New Game", this);
    buttonNewGame->setGeometry(QRect(QPoint(350, 100), QSize(200, 50)));
    buttonLeaders = new QPushButton("Leaders", this);
    buttonLeaders->setGeometry(QRect(QPoint(350, 200), QSize(200, 50)));
    buttonQuitGame = new QPushButton("Quit", this);
    buttonQuitGame->setGeometry(QRect(QPoint(350, 300), QSize(200, 50)));
    buttonBack = new QPushButton("Back", this);
    buttonBack->setGeometry(QRect(QPoint(350, 50), QSize(200, 50)));
}

void Widget::showLeaders()
{
    endGame = true;
    hideMenu();
    buttonBack->show();
    slotSendToServerGet();
}

void Widget::showMenu()
{
    lineEditName->hide();
    buttonNewGame->show();
    buttonLeaders->show();
    buttonQuitGame->show();
    buttonBack->hide();
    clearScene();
    descriptionEndGame(25, "Unispace", "Hello, " + lineEditName->text(), Qt::cyan, 250, 10);
    yLeadersLineStep = 100;
}

void Widget::hideMenu()
{
    buttonNewGame->hide();
    buttonLeaders->hide();
    buttonQuitGame->hide();
    buttonBack->hide();
    clearScene();
}

void Widget::stopGame()
{
    buttonBack->hide();
    slotSendToServerSet();
    timersStop();
    clearScene();
    showMenu();
}

void Widget::newGame()
{
    blockSignals(false);
    endGame = true;
    _score = 0;
    hideMenu();
    timersStart();
    createSpaceship();
    scene->addRect(scene->sceneRect());
    descriptionScore(30, "Unispace", QString::number(0), Qt::darkCyan, 0, -5);
}

void Widget::clearScene()
{
    QList<QGraphicsItem*> list = scene->items();
    qDebug() << list;
    for(int i = 0; i < list.length(); i++)
    {
        scene->removeItem(list[i]);
    }
    blockSignals(true);
}

void Widget::lifeChangerEnemySpaceship()
{
    if (!life)
    {
        life = 3;
        delete this->_enemySpaceship;
        sumScore();
        return;
    }
    reinicializateEnemySpaceship();
}

void Widget::reinicializateEnemySpaceship()
{
    qreal x = this->_enemySpaceship->x();
    qreal y = this->_enemySpaceship->y();
    delete this->_enemySpaceship;
    onGenerateEnemySpaceship();
    this->_enemySpaceship->setPos(x, y);
    life--;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
QString Widget::addToJson(QString str)
{
    QJsonDocument document;
    QJsonObject root = document.object();
    root.insert(lineEditName->text(), QJsonValue::fromVariant(str));
    document.setObject(root);
    QString strJson(document.toJson(QJsonDocument::Compact));
    return strJson;
}

void Widget::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_5_8);
    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (static_cast<quint16>(m_pTcpSocket->bytesAvailable()) < sizeof(quint16))
            {
                break;
            }
            in >> m_nNextBlockSize;
        }
        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize)
        {
            break;
        }
        QString str;
        in >> str;
        m_nNextBlockSize = 0;
        if(endGame)
        {
            insertDataReadyRead(str);
        }
    }
}

void Widget::insertDataReadyRead(QString str)
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
        descriptionEndGame(25, "Unispace", i.value() + " : " + QString::number(i.key()), Qt::yellow, 280, yLeadersLineStep += 30);
    } while (i != map.constBegin());
}

void Widget::slotError(QAbstractSocket::SocketError err)
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

void Widget::slotSendToServerGet()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << quint16(0) << addToJson("onlyRead");
    out.device()->seek(0);
    out << quint16(static_cast<quint16>(arrBlock.size()) - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}

void Widget::slotSendToServerSet()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << quint16(0) << addToJson(QString::number(_score));
    out.device()->seek(0);
    out << quint16(static_cast<quint16>(arrBlock.size()) - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}

void Widget::slotConnected()
{
    qDebug() << "CONNECTED!";
}
