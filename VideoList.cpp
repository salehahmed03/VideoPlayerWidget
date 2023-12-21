#include "VideoList.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QStandardItem>

VideoList::VideoList(QWidget* parent)
	: QMainWindow(parent), lineEdit(new QLineEdit), listView(new QListView), NextButton(new QPushButton), PreviousButton(new QPushButton), okButton(new QPushButton)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/new/prefix1/play.ico"));
	QVBoxLayout* layout = new QVBoxLayout;
	QLabel* label = new QLabel("List of videos");
	layout->addWidget(label);
	layout->addWidget(listView);
	lineEdit->setPlaceholderText("Paste Video path Here");
	layout->addWidget(lineEdit);
	QPushButton* okButton = new QPushButton("OK");
	layout->addWidget(okButton);
	QPushButton* NextButton = new QPushButton("NEXT");
	layout->addWidget(NextButton);
	QPushButton* PreviousButton = new QPushButton("PREVIOUS");
	layout->addWidget(PreviousButton);
	QWidget* centralWidget = new QWidget;
	centralWidget->setLayout(layout);
	setCentralWidget(centralWidget);
	connect(okButton, &QPushButton::clicked, this, &VideoList::addVideoPath);
}

VideoList::~VideoList()
{
}

void VideoList::addVideoPath()
{
	QString videoPath = lineEdit->text();
	addVideoPathToListView(videoPath);
	lineEdit->clear();
}

void VideoList::addVideoPathToListView(const QString& videoPath)
{
	QStandardItemModel* model = qobject_cast<QStandardItemModel*>(listView->model());

	if (!model) {
		model = new QStandardItemModel(listView);
		listView->setModel(model);
	}
	QStandardItem* item = new QStandardItem(videoPath);

	model->appendRow(item);
}
