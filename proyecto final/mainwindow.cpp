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
#include "trampas.h"
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
    Trampas *trampa = new Trampas(100, 275, 56.07, 87, "C:/Users/JojhanSebastian/Downloads/Soldier_2/trampa.png");
    scene->addItem(trampa);
    trampas.append(trampa);
    Particula *bola = new Particula(ui->graphicsView, 50.0, 100.0, 100.0, 75);
    scene->addItem(bola);
    bola->setPos(100,100);

    jug1 = new Jugador(ui->graphicsView);
    scene -> addItem(jug1);
    jug1->setPos(100,0);
    qDebug() << ui->graphicsView->size()<<" "<<scene->sceneRect();

    int numEnemigos = 5; // Puedes ajustar el número de enemigos según lo desees
    for (int i = 0; i < numEnemigos; ++i) {
        //qreal xPos = rand() % 3780 + 100; // 100 es el valor mínimo, 3880 es el valor máximo
        qreal yPos = 270; // Utiliza la posición fija para la coordenada y
        Enemigos *enemigo = new Enemigos(ui->graphicsView, 200+(i*300), yPos);
        enemigos.append(enemigo);
        scene->addItem(enemigo);

        // Llama al método disparar para cada enemigo
        //enemigo->disparar();
    }

    timer = new QTimer;
    //connect(timer,SIGNAL(timeout()),this,SLOT(hmov(*bola)));
    connect(timer, &QTimer::timeout, [=]() {
        hmov(bola);
        movjug(jug1);
        //Trampa(trampa);
        for (auto enem : enemigos) {
            enemigomov(enem);
            //enem->disparar();
        }
        if (bola->collidesWithItem(jug1)) {
            // Handle collision logic here
            qDebug() << "Collision detected between Particula and Jugador";
        }
    });
    timer->stop();
    QImage caja("C:/Users/JojhanSebastian/Downloads/Soldier_1/caja1.jpg");
    QBrush brocha(caja);
    for(int i=0;i<9; i++){
        obst.append(scene->addRect(300+(i*300),280,40,40,QPen(Qt::black), brocha));
    }
    // Llama a setSprite para cambiar el sprite de la trampa
    //obst.append(scene->addRect(0,270,40,40,QPen(Qt::NoPen), brocha));
    //obst.append(scene->addRect(600,270,40,40,QPen(Qt::NoPen), QBrush(Qt::black)));
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
        //trampa->setSprite(0);
        for (auto enem : enemigos) {
            enem->movimiento(4,0); // Aquí llamas a la función movimiento para cada enemigo
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
        enem1->movimiento(4,0); // Cambia esto para llamar a movimiento con los parámetros adecuados
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

void MainWindow::Trampa(Trampas *trampa){
    trampa->setSprite(0);
}
