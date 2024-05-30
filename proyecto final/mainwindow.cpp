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
#include <cstdlib> // Necesario para la función rand()
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

    background->setPos(
        (scene->width() - background->pixmap().width()) / 2,
        (scene->height() - background->pixmap().height()) / 2
        );

    Particula *bola = new Particula(ui->graphicsView, 50.0, 100.0, 100.0, 75);
    scene->addItem(bola);
    bola->setPos(100,100);

    jug1 = new Jugador(ui->graphicsView);
    scene -> addItem(jug1);
    jug1->setPos(100,0);
    qDebug() << ui->graphicsView->size()<<" "<<scene->sceneRect();

    int numEnemigos = 2; // Puedes ajustar el número de enemigos según lo desees
    for (int i = 0; i < numEnemigos; ++i) {
        Enemigos *enemigo = new Enemigos(ui->graphicsView);
        enemigos.append(enemigo);
        scene->addItem(enemigo);

        // Generar una posición aleatoria en el eje x entre 100 y 700 unidades
        int xPos = rand() % 3780 + 100; // 100 es el valor mínimo, 3880 es el valor máximo

        // Utiliza la posición aleatoria generada para la coordenada x
        enemigo->setPos(xPos, 250); // 250 es la posición en el eje y
    }

    timer = new QTimer;
    //connect(timer,SIGNAL(timeout()),this,SLOT(hmov(*bola)));
    connect(timer, &QTimer::timeout, [=]() {
        hmov(bola);
        movjug(jug1);
        for (auto enem : enemigos) {
            enemigomov(enem);}
        if (bola->collidesWithItem(jug1)) {
            // Handle collision logic here
            qDebug() << "Collision detected between Particula and Jugador";
        }
    });
    timer->stop();
    /*for(int i=0;i<3; i++){
        obst.append(scene->addRect(200+(i*100),250,40,40,QPen(Qt::black), QBrush(Qt::black)));
    }*/
    obst.append(scene->addRect(300,250,40,40,QPen(Qt::black), QBrush(Qt::black)));
    obst.append(scene->addRect(600,250,40,40,QPen(Qt::black), QBrush(Qt::black)));
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

    // Llama a la función para mover los enemigos cuando se inicia el temporizador
    if (timer->isActive()) {
        for (auto enem : enemigos) {
            enem->movimiento(10,0); // Aquí llamas a la función movimiento para cada enemigo
        }
    }
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
        // Llama al método movimiento de la clase Enemigos
        enem1->movimiento(10,0); // Cambia esto para llamar a movimiento con los parámetros adecuados
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    QPointF mousePos = ui->graphicsView->mapToScene(event->pos());
    qDebug()<<mousePos;
    animacionTiro(mousePos);
    incrementarContador();
    //jug1->cambiarSprite(":/images/new_sprite.png",0);
    jug1->setFocus();
}
static int contadormuerte = 0;
static int totalenemigos=1;
void MainWindow::animacionTiro(const QPointF &posTiro) {
    new Bala(scene, jug1->pos(), posTiro, enemigos, obst);
}

void MainWindow::incrementarContador()
{
    jug1->cambiarSprite("C:/Users/JojhanSebastian/Downloads/Soldier_1/Shot_1.png",0);
}

