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
#include "VideoPlayerWidget.h"

VideoList::VideoList(QWidget* parent)
	: QMainWindow(parent),
	lineEdit(new QLineEdit),
	listView(new QListView),
	NextButton(new QPushButton),
	PreviousButton(new QPushButton),
	okButton(new QPushButton),
	browseButton(new QPushButton),
	removeButton(new QPushButton)
{

	ui.setupUi(this);

	setWindowIcon(QIcon(":/new/prefix1/play.ico"));

	QVBoxLayout* layout = new QVBoxLayout;
	QLabel* label = new QLabel("List of videos,Double click to Play The Video");
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
	removeButton = new QPushButton("Remove");
	buttonLayout->addWidget(removeButton);

	layout->addLayout(buttonLayout);
	buttonLayout->addWidget(removeButton);

	QWidget* centralWidget = new QWidget;
	centralWidget->setLayout(layout);
	setCentralWidget(centralWidget);
	connect(okButton, &QPushButton::clicked, this, &VideoList::addVideoPath);
	connect(browseButton, &QPushButton::clicked, this, &VideoList::openFileDialog);
	connect(listView, &QListView::doubleClicked, this, &VideoList::listItemDoubleClicked);
	connect(NextButton, &QPushButton::clicked, this, &VideoList::onNextClicked);
	connect(PreviousButton, &QPushButton::clicked, this, &VideoList::onPreviousClicked);
	connect(listView, &QListView::clicked, this, &VideoList::onItemClickedForRemove);
	connect(removeButton, &QPushButton::clicked, this, &VideoList::onRemoveClicked);
}

VideoList::~VideoList()
{
}

void VideoList::updateListView()
{
	QStandardItemModel* model = qobject_cast<QStandardItemModel*>(listView->model());

	if (!model) {
		model = new QStandardItemModel(listView);
		listView->setModel(model);
	}

	model->clear();

	for (int i = 0; i < videoPlayer.list.nodeCount(); ++i) {
		string videoName = videoPlayer.list.searchByIndex(i);

		QStandardItem* item = new QStandardItem(QString::fromStdString(videoName));
		model->appendRow(item);
	}
}


void VideoList::addVideoPath()
{
	QString videoPath = lineEdit->text();
	Video v(videoPath.toStdString());

	if (v.getIsValid()) {
		videoPlayer.list.push(v);
		updateListView();
		lineEdit->clear();
	}
	else {
		QMessageBox::warning(this, "Try again", "No file Was added");
	}

}

void VideoList::openFileDialog()
{
	QString videoPath = QFileDialog::getOpenFileName(this, tr("Open Video"), "", tr("All Files (*)"));
	Video v(videoPath.toStdString());
	if (v.getIsValid()) {
		videoPlayer.list.push(v);
		updateListView();
		lineEdit->clear();
	}
	else {
		QMessageBox::warning(this, "Try again", "No file Was added");
	}
}

void VideoList::listItemDoubleClicked(const QModelIndex& index)
{
	selectedVideoPath = index.data(Qt::DisplayRole).toString();
	videoPlayer.setCurrentVideoByPath(selectedVideoPath.toStdString());
	string s = videoPlayer.currentVideo->data.getFilePath();
	QString qString = QString::fromStdString(s);
	V->setVideoPath(qString);
	QMessageBox::information(nullptr, "Info", "Press Confirm To Play The Video");
}

void VideoList::onNextClicked()
{
	videoPlayer.next();
	string s = videoPlayer.currentVideo->data.getFilePath();
	QString qString = QString::fromStdString(s);
	V->setVideoPath(qString);
	QMessageBox::information(nullptr, "Info", "Press Confirm To Play The Video");
}

void VideoList::onPreviousClicked()
{
	videoPlayer.previous();
	string s = videoPlayer.currentVideo->data.getFilePath();
	QString qString = QString::fromStdString(s);
	V->setVideoPath(qString);
	QMessageBox::information(nullptr, "Info", "Press Confirm To Play The Video");
}

void VideoList::onItemClickedForRemove(const QModelIndex& index)
{
	selectedVideoPathRemove = index.data(Qt::DisplayRole).toString();
}

void VideoList::onRemoveClicked()
{
	string s = selectedVideoPathRemove.toStdString();
	int i = videoPlayer.list.searchByPath(s);
	videoPlayer.list.erase(i);
	updateListView();
}