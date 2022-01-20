#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

bool MainWindow::get_stan(int num)
{
	return stan[num];
}

void MainWindow::on_stan_1_clicked()
{
    stan[0] = !stan[0];
    
    if (stan[0])
    {
        ui->stan_1->setStyleSheet("font-weight: bold;");
    }
    else
    {
        ui->stan_1->setStyleSheet("font-weight: normal;");
    }
}

void MainWindow::on_stan_2_clicked()
{
    
    stan[1] = !stan[1];
    
    if (stan[1])
    {
        ui->stan_2->setStyleSheet("font-weight: bold;");
    }
    else
    {
        ui->stan_2->setStyleSheet("font-weight: normal;");
    }
}

void MainWindow::on_stan_3_clicked()
{
    stan[2] = !stan[2];
    
    if (stan[2])
    {
        ui->stan_3->setStyleSheet("font-weight: bold;");
    }
    else
    {
        ui->stan_3->setStyleSheet("font-weight: normal;");
    }
}

void MainWindow::on_stan_4_clicked()
{
    stan[3] = !stan[3];
    
    if (stan[3])
    {
        ui->stan_4->setStyleSheet("font-weight: bold;");
    }
    else
    {
        ui->stan_4->setStyleSheet("font-weight: normal;");
    }
}

void MainWindow::on_stan_5_clicked()
{
    stan[4] = !stan[4];
    
    if (stan[4])
    {
        ui->stan_5->setStyleSheet("font-weight: bold;");
    }
    else
    {
        ui->stan_5->setStyleSheet("font-weight: normal;");
    }
}

void MainWindow::on_stan_6_clicked()
{
    stan[5] = !stan[5];
    
    if (stan[5])
    {
        ui->stan_6->setStyleSheet("font-weight: bold;");
    }
    else
    {
        ui->stan_6->setStyleSheet("font-weight: normal;");
    }
}

void MainWindow::on_stan_7_clicked()
{
    stan[6] = !stan[6];
    
    if (stan[6])
    {
        ui->stan_7->setStyleSheet("font-weight: bold;");
    }
    else
    {
        ui->stan_7->setStyleSheet("font-weight: normal;");
    }
}

void MainWindow::on_stan_8_clicked()
{
    stan[7] = !stan[7];
    
    if (stan[7])
    {
        ui->stan_8->setStyleSheet("font-weight: bold;");
    }
    else
    {
        ui->stan_8->setStyleSheet("font-weight: normal;");
    }
}
