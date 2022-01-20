#include "mainmenu.hh"
#include "ui_mainmenu.h"

namespace StudentSide {

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{   
    ui->setupUi(this);

    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(5);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_spinBox_valueChanged(int a)
{
    time_ = a;

}

void MainMenu::on_startButton_clicked()
{
    emit startGame(time_);
    MainMenu::accept();
}

}//namespace

