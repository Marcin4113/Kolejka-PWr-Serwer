#ifndef WORKING_WINDOW_H
#define WORKING_WINDOW_H

#include <QDialog>
#include "client_connection.h"

namespace Ui {
	class WorkingWindow;
}

enum class SlotStatus
{
	FREE,
	BUSY,
	BREAK
};

class WorkingWindow : public QDialog
{
		Q_OBJECT
		
	public:
		explicit WorkingWindow(ClientConnection* p_connection, QWidget *parent = nullptr);
		
		void update_position_in_queue(int p_pos);
		
		~WorkingWindow();
		
	private slots:
		void on_ButtonFree_clicked();
		
		void on_ButtoBusy_clicked();
		
		void on_ButtonBreak_clicked();
		
		void on_ButtonExit_clicked();
		
	private:
		Ui::WorkingWindow *ui;
		
		ClientConnection* m_connection;
		SlotStatus slot_status;
};

#endif // WORKING_WINDOW_H
