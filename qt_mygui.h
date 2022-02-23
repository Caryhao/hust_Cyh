#pragma once
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE

#include <QtWidgets/QWidget>
#include "ui_qt_mygui.h"

#include "qmessagebox.h"
#include "qchart.h"
#include "qgridlayout.h"
#include "qsplineseries.h"
#include "qvalueaxis.h"
#include "qlayout.h"
#include <QHBoxLayout>

class Qt_MyGui : public QWidget
{
	Q_OBJECT

public:
	Qt_MyGui(QWidget *parent = Q_NULLPTR);
	~Qt_MyGui();

	void MyChart();
	void start_run();
	void pause_btn();

	void LoadData();

private:
	Ui::Qt_MyGuiClass *ui;
};
