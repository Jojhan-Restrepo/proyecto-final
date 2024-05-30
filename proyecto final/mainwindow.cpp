#include "mainwindow.h"
#include "qevent.h"
#include "ui_mainwindow.h"
#include "Particula.h"
#include "Jugador.h"
#include <qdebug.h>
#include <QLabel>
#include <QPixmap>
#include "PropQGraphicsView.h"
#include "enemigos.h"
#include "Bala.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) //La interfaz diseñada en Qt Designer
{

    ui->setupUi(this); //This hace referencia a la clase MainWindow, configura la interfaz de usuario definida en el Qt designer
    //bool clic = true; //No hay necesidad de declararla de nuevo
    //PropQGraphicsView *perView = new PropQGraphicsView(this);
    //ui->graphicsView = perView;
    scene = new QGraphicsScene(this); // se debe crear una escena para manejar elementos gráficos
    scene->setSceneRect(0, 0, 3880, 500);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(800 + 2 * ui->graphicsView->frameWidth(), 500 + 2 * ui->graphicsView->frameWidth());
    //perView->setScene(scene);
    //perView->setFixedSize(800 + 2 * perView->frameWidth(), 500 + 2 * perView->frameWidth());//manejar la relación de aspecto
    //ui->centralwidget->layout()->addWidget(perView);

    tiempoTrans = 0;

    QPixmap backgroundImage("C:/Users/JojhanSebastian/Downloads/Soldier_1/back1.png");
    QGraphicsPixmapItem *background = scene->addPixmap(backgroundImage);

    /*QTimer *bgTimer = new QTimer(this);
    connect(bgTimer, &QTimer::timeout, [=]() {
        // Update background position
        QPointF newPos = background->pos() - QPointF(1, 0); // Adjust the movement speed as needed
        background->setPos(newPos);
        qDebug() << newPos << " " << scene->width() << background->pos().x() + background->pixmap().width();

        // Wrap around when reaching the end of the scene
        if (background->pos().x() + background->pixmap().width() <= scene->width())
            background->setPos(QPointF(0, 0)); // Reset to the beginning
    });
    bgTimer->start(50); // Update every 50 milliseconds*/

    Particula *bola = new Particula(ui->graphicsView, 50.0, 100.0, 100.0, 75);
    scene->addItem(bola);
    bola->setPos(100,100);

    jug1 = new Jugador(ui->graphicsView);
    scene -> addItem(jug1);
    jug1->setPos(100,0);
    qDebug() << ui->graphicsView->size()<<" "<<scene->sceneRect();

    enem1= new Enemigos(ui->graphicsView);
    scene -> addItem(enem1);
    enem1->setPos(100,0);

    timer = new QTimer;
    //connect(timer,SIGNAL(timeout()),this,SLOT(hmov(*bola)));
    connect(timer, &QTimer::timeout, [=]() {
        hmov(bola);
        movjug(jug1);
        enemigomov(enem1);
        if (bola->collidesWithItem(jug1)) {
            // Handle collision logic here
            qDebug() << "Collision detected between Particula and Jugador";
        }
    });
    timer->stop();
    for(int i=0;i<3; i++){
        obst.append(scene->addRect(200+(i*100),100,40,40,QPen(Qt::black), QBrush(Qt::black)));
    }
    if (bola->collidesWithItem(jug1)) {
        // Handle collision logic here
        qDebug() << "Collision detected between Particula and Jugador";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if (clic){
        ui->pushButton->setText("Hizo click");
        clic = false;
    }
    else{
        ui->pushButton->setText("Haga clic");
        clic = true;
    }
    if (timer->isActive()) timer->stop();
    else timer->start(60);

}
void MainWindow::movjug(Jugador *jug1)
{
    tiempoTrans+=0.5;
    jug1->setFocus();
    bool bandera = false;
    for(int i=0;i<obst.length();i++){
        if(jug1->collidesWithItem(obst.at(i))){
            bool bandera=true;
            break;
        }
    }
}
void MainWindow::hmov(Particula *bola)
{
    bola->movParabolico(&this->tiempoTrans);
    tiempoTrans+=0.01;

}
void MainWindow::enemigomov(Enemigos *enem1) {
    if (enem1) {
        enem1->movimiento(5, 0);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    QPointF mousePos = ui->graphicsView->mapToScene(event->pos());
    qDebug()<<mousePos;
    animacionTiro(mousePos);
    jug1->cambiarSprite(":/images/new_sprite.png",18);
    jug1->setFocus();
}
static int contadormuerte = 0;
static int totalenemigos=1;
void MainWindow::animacionTiro(const QPointF &posTiro){
    new Bala(scene, jug1->pos(), posTiro, enem1, obst);
}



