#include "mainwindow.h"
#include "qevent.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "PropQGraphicsView.h"
#include <cstdlib>
#include "Particula.h"
#include "Jugador.h"
#include "enemigos.h"
#include "Bala.h"
#include "trampas.h"
#include <QGraphicsProxyWidget>
#include "balaenemigo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , clic(true)
{
    ui->setupUi(this);

    menuScene = new QGraphicsScene(this);
    menuScene->setSceneRect(0, 0, 400, 300);

    QPixmap menuBackground("C:/Users/JojhanSebastian/Downloads/Soldier_1/fondodeinicio.jpg");
    QGraphicsPixmapItem *backgroundItem = new QGraphicsPixmapItem(menuBackground);
    menuScene->addItem(backgroundItem);
    backgroundItem->setPos(0, 0);

    QPushButton *startButton = new QPushButton("Start");
    QPushButton *scoresButton = new QPushButton("Puntajes");

    QGraphicsProxyWidget *startButtonItem = menuScene->addWidget(startButton);
    QGraphicsProxyWidget *scoresButtonItem = menuScene->addWidget(scoresButton);

    startButtonItem->setPos(350, 200);
    scoresButtonItem->setPos(350, 300);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(scoresButton, &QPushButton::clicked, this, &MainWindow::showScores);

    ui->graphicsView->setScene(menuScene);

    initGameScene();

    tiempoTrans = 0;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateGame);
    timer->stop();
    QTimer *timerDisparoEnemigos = new QTimer(this);
    connect(timerDisparoEnemigos, &QTimer::timeout, this, &MainWindow::animacionTiroDesdeEnemigo);
    timerDisparoEnemigos->start(2000);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initGameScene() {
    gameScene = new QGraphicsScene(this);
    gameScene->setSceneRect(0, 0, 3880, 500);
    ui->graphicsView->setFixedSize(800 + 2 * ui->graphicsView->frameWidth(), 500 + 2 * ui->graphicsView->frameWidth());

    QPixmap backgroundImage("C:/Users/JojhanSebastian/Downloads/Soldier_1/back1.png");
    QGraphicsPixmapItem *background = gameScene->addPixmap(backgroundImage);
    background->setPos((gameScene->width() - background->pixmap().width()) / 2, (gameScene->height() - background->pixmap().height()) / 2);

    int numTrampas = 5;
    for (int i = 0; i < numTrampas; ++i) {
        qreal xPos = rand() % 3880;
        Trampas *trampa = new Trampas(xPos, 275, 56.07, 87, "C:/Users/JojhanSebastian/Downloads/Soldier_2/trampa.png");
        trampas.append(trampa);
        gameScene->addItem(trampa);
    }

    bola = new Particula(ui->graphicsView, 50.0, 100.0, 100.0, 75);
    gameScene->addItem(bola);
    bola->setPos(100,100);

    jug1 = new Jugador(ui->graphicsView);
    gameScene->addItem(jug1);
    jugador.append(jug1);
    int numEnemigos = 5;
    for (int i = 0; i < numEnemigos; ++i) {
        qreal yPos = 270;
        Enemigos *enemigo = new Enemigos(ui->graphicsView, 200 + (i * 300), yPos);
        enemigos.append(enemigo);
        gameScene->addItem(enemigo);
    }

    QImage caja("C:/Users/JojhanSebastian/Downloads/Soldier_1/caja1.jpg");
    QBrush brocha(caja);
    for (int i = 0; i < 9; i++) {
        obst.append(gameScene->addRect(300 + (i * 300), 280, 40, 40, QPen(Qt::black), brocha));
    }
}

void MainWindow::startGame() {
    ui->graphicsView->setScene(gameScene);
    timer->start(60);
}

void MainWindow::showScores() {
    QFile file("scores.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo de puntajes");
        return;
    }

    QTextStream in(&file);
    QString scoresText = in.readAll();
    file.close();

    QMessageBox::information(this, "Puntajes", scoresText);
}

void MainWindow::updateGame() {
    hmov(bola);
    movjug(jug1);
    for (auto enem : enemigos) {
        enemigomov(enem);
    }
    if (bola->collidesWithItem(jug1)) {
        qDebug() << "Collision detected between Particula and Jugador";
    }
}

void MainWindow::on_pushButton_clicked() {
    if (clic) {
        ui->pushButton->setText("Hizo click");
        clic = false;
    } else {
        ui->pushButton->setText("Haga clic");
        clic = true;
    }
    if (timer->isActive()) timer->stop();
    else timer->start(60);

    if (timer->isActive()) {
        for (auto enem : enemigos) {
            enem->movimiento(4, 0);
        }
    }
}

void MainWindow::movjug(Jugador *jug1) {
    tiempoTrans += 0.5;
    jug1->setFocus();
    for (int i = 0; i < obst.length(); i++) {
        if (jug1->collidesWithItem(obst.at(i))) {
            break;
        }
    }
}

void MainWindow::hmov(Particula *bola) {
    float tiempoTransFloat = static_cast<float>(this->tiempoTrans);
    bola->movParabolico(&tiempoTransFloat);
    tiempoTrans += 0.01;
}

void MainWindow::enemigomov(Enemigos *enem1) {
    if (enem1) {
        enem1->movimiento(4, 0);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    QPointF mousePos = ui->graphicsView->mapToScene(event->pos());
    qDebug() << mousePos;
    animacionTiro(mousePos);
    incrementarContador();
    jug1->setFocus();
}

void MainWindow::animacionTiro(const QPointF &posTiro) {
    new Bala(gameScene, jug1->pos(), posTiro, enemigos, obst);
}

void MainWindow::incrementarContador() {
    jug1->cambiarSprite("C:/Users/JojhanSebastian/Downloads/Soldier_1/Shot_1.png", 0);
}

void MainWindow::Trampa(Trampas *trampa) {
    trampa->setSprite(0);
}

void MainWindow::animacionTiroDesdeEnemigo() {
    for (Enemigos* enemigo : enemigos) {
        if (enemigo) {
            QPointF posInicio = enemigo->pos();
            QPointF posObjetivo = jug1->pos();
            BalaEnemigo* bala = new BalaEnemigo(gameScene, posInicio, posObjetivo, jugador, obst);
        }
    }
}
