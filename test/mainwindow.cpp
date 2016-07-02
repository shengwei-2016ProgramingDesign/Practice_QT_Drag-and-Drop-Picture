#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //enter the event Filter
    qApp->installEventFilter(this);
    //
    hold = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    mouseEvent = (QMouseEvent *) event ;

    std::cout<<mouseEvent->pos().x()<<" "<<mouseEvent->pos().y()<<std::endl;

    if(event->type() == QEvent::MouseButtonPress && thePicture->pos().x() <= mouseEvent->pos().x() &&mouseEvent->pos().x() <= thePicture->pos().x()+thePicture->pixmap().width() && thePicture->pos().y() <= mouseEvent->pos().y() &&mouseEvent->pos().y() <= thePicture->pos().y()+thePicture->pixmap().height()){
        hold = 1;
    }
    if(event->type() == QEvent::MouseMove && hold >= 1){
        thePicture->setPos(mouseEvent->pos().x()- 0.5*thePicture->pixmap().width(),mouseEvent->pos().y()- 0.5*thePicture->pixmap().height());
    }
    if(event->type() == QEvent::MouseButtonRelease){
        hold =0;
    }
    return false;
}

void MainWindow::showEvent(QShowEvent *)
{
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedHeight(600);
    ui->graphicsView->setFixedWidth(800);

    thePicture = new QGraphicsPixmapItem();
    thePicture->setPixmap(QPixmap(":/Pic/TC.png"));
    thePicture->setPos(100,100);

    //std::cout<<thePicture->pos().x()<<","<<thePicture->pos().y()<<std::endl;
    scene->addItem(thePicture);
}
