#include "qt_mygui.h"
#include "qmessagebox.h"

#include "qfiledialog.h"
#include "qfile.h"
#include "qlabel.h"
#include "qpainter.h"
#include "qimage.h"
#include "qtimer.h"
#include "qlist.h"
#include "qmath.h"
#include "qpoint.h"
#include "qdebug.h"
#include "qstring.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <stdlib.h>

using namespace std;

int maxSize = 1000;
QLineSeries *mySeries;
Qt_MyGui::Qt_MyGui(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::Qt_MyGuiClass())
{
	ui->setupUi(this);
	
	MyChart();
	
	connect(ui->btn_loadData, &QPushButton::clicked, [=]() {
		this->LoadData();
	});

	connect(ui->btn_start, &QPushButton::clicked, [=]() {
		this->start_run();
	});
	connect(ui->btn_pause, &QPushButton::clicked, [=]() {
		this->pause_btn();
	});
	connect(ui->btn_exit, &QPushButton::clicked, [=]() {
		this->close();
	});
}

void Qt_MyGui::start_run() 
{
	//cout << "begin" << endl;
	//读取文件，并绘图
	//QString filename = QFileDialog::getOpenFileName(this,"打开文件","D:/myQt/day04/Qt_MyGui/Qt_MyGui/contactForce_20N.txt");
	//if (filename.isEmpty())     //如果未选择文件便确认，即返回
	//	return;
	//QFile file("D:/myQt/day04/Qt_MyGui/Qt_MyGui/contactForce_20N.txt");
	QFile file("D:/myQt/day04/Qt_MyGui/Qt_MyGui/Data.txt");
	QVector<QPointF> points;
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		for (int i=0; !file.atEnd(); i++)
		{
			QByteArray line = file.readLine();
			//QString str = ;
			points.append(QPointF(i, line.toFloat()));		
		}
		mySeries->replace(points);		
	}
	//通过定时器，逐渐将数据读取
	
}

void Qt_MyGui::pause_btn()
{

}



void Qt_MyGui::MyChart()
{
	QChart *myChart = new QChart;
	QChartView *chartView = new QChartView(myChart);
	chartView->setRubberBand(QChartView::RectangleRubberBand);
	chartView->setRenderHint(QPainter::Antialiasing);

	mySeries = new QLineSeries;
	myChart->addSeries(mySeries);

	for (int i = 0; i < maxSize; i++)
	{
		mySeries->append(i, 20);
		/*mySeries->append(i, 0);*/
	}

	mySeries->setUseOpenGL(true);
	//qDebug() << mySeries->useOpenGL();

	//坐标系格式
	QValueAxis *AxisX = new QValueAxis;
	AxisX->setRange(0, maxSize);
	AxisX->setLabelFormat("%g");
	AxisX->setTickCount(11);
	AxisX->setTitleText("axisX");
	QValueAxis *AxisY = new QValueAxis;
	AxisY->setRange(-2.0, 22.0);
	AxisY->setTickCount(12);
	AxisY->setTitleText("axisY");

	//添加坐标系到chart中
	myChart->setAxisX(AxisX, mySeries);
	myChart->setAxisY(AxisY, mySeries);
	myChart->setFont(QFont("Monospace", 12));
	myChart->setTitle(QStringLiteral("力信号读取"));
	
	myChart->setTitleBrush(Qt::black);
	myChart->legend()->setLabelColor(Qt::white);
	//设置X轴字体颜色
	myChart->axisX()->setLabelsColor(Qt::white);
	//设置Y轴字体颜色
	myChart->axisY()->setLabelsColor(Qt::white);
	// 背景色
	//myChart->setBackgroundBrush(QColor(0, 60, 220));
	//myChart->setBackgroundVisible(false);//去背景
	//myChart->setStyleSheet(" background-image:url(:/1.png);");
	//setAttribute(Qt::WA_TranslucentBackground);
	//chartView->setStyleSheet("background: transparent");
	//设置一个布局 将图表连接起来
	QVBoxLayout *layout = ui->verticalLayout;
	layout->addWidget(chartView);
}

void Qt_MyGui::LoadData()
{
	fstream ofile;
	int i = 0;
	float pi = 3.14159;
	ofile.open("D:/myQt/day04/Qt_MyGui/Qt_MyGui/Data.txt",ios::out|ios::binary);
	//ofile.clear();
	int n = rand() %500;
	while (i < n+100)
	{
		if (ofile.is_open())
		{
			ofile << 10 + 5 * sin(i/pi) << endl;
		}
		i++;
	}
	ofile.close();
}

Qt_MyGui::~Qt_MyGui() 
{
	delete ui;
}
