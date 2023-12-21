#include "VideoList.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileDialog>
#include <QMessageBox>

VideoList::VideoList(QWidget* parent)
	: QMainWindow(parent), 
	lineEdit(new QLineEdit),
	listView(new QListView),
	NextButton(new QPushButton),
	PreviousButton(new QPushButton),
	okButton(new QPushButton),
	browseButton(new QPushButton)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/new/prefix1/play.ico"));
	QVBoxLayout* layout = new QVBoxLayout;
	QLabel* label = new QLabel("List of videos");
	layout->addWidget(label);
	layout->addWidget(listView);
	lineEdit->setPlaceholderText("Paste Video path Here");
	layout->addWidget(lineEdit);

	QHBoxLayout* buttonLayout = new QHBoxLayout; 
	okButton = new QPushButton("OK");
	buttonLayout->addWidget(okButton); 
	NextButton = new QPushButton("NEXT");
	buttonLayout->addWidget(NextButton);
	PreviousButton = new QPushButton("PREVIOUS");
	buttonLayout->addWidget(PreviousButton);
	browseButton = new QPushButton("Browse folders", this);
	buttonLayout->addWidget(browseButton);

	layout->addLayout(buttonLayout);

	QWidget* centralWidget = new QWidget;
	centralWidget->setLayout(layout);
	setCentralWidget(centralWidget);
	connect(okButton, &QPushButton::clicked, this, &VideoList::addVideoPath);
	connect(browseButton, &QPushButton::clicked, this, &VideoList::openFileDialog);
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

void VideoList::openFileDialog()
{
	QString videoPath = QFileDialog::getOpenFileName(this, tr("Open Video"), "", tr("Video Files (*.mp4 *.avi *.mkv)"));
	if (!videoPath.isEmpty()) {
		addVideoPathToListView(videoPath);
		lineEdit->clear();
	}
}
