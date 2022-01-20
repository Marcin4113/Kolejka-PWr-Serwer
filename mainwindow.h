#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();
		
		bool get_stan(int num);
		
	private slots:
		void on_stan_1_clicked();
		
		void on_stan_3_clicked();
		
		void on_stan_2_clicked();
		
		void on_stan_4_clicked();
		
		void on_stan_5_clicked();
	
		void on_stan_6_clicked();
	
		void on_stan_7_clicked();
	
		void on_stan_8_clicked();
	
	private:
		Ui::MainWindow *ui;
		
		bool stan[8] = {false, false, false, false, false, false, false, false};
};
#endif // MAINWINDOW_H
