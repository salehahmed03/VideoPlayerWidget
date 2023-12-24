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
	removeButton(new QPushButton),
	swapButton(new QPushButton)
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
	swapButton = new QPushButton("Swap");
	buttonLayout->addWidget(swapButton);

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
	connect(swapButton, &QPushButton::clicked, this, &VideoList::onSwapClicked);
	connect(listView, &QListView::clicked, this, &VideoList::onItemClickedForSwap);
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

	if (v.getIsValid() && !videoPath.isEmpty()) {
		videoPlayer.list.push(v);
		updateListView();
		lineEdit->clear();
	}
	else {
		QMessageBox::warning(this, "Try again", "Path is wrong, No file Was added");
	}

}

void VideoList::openFileDialog()
{
	QString videoPath = QFileDialog::getOpenFileName(this, tr("Open Video"), "", tr("All Files (*)"));
	Video v(videoPath.toStdString());
	if (v.getIsValid() && !videoPath.isEmpty()) {
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
	if (videoPlayer.currentVideo == nullptr) {
		return;
	}
	videoPlayer.next();
	string s = videoPlayer.currentVideo->data.getFilePath();
	QString qString = QString::fromStdString(s);
	V->setVideoPath(qString);
	QMessageBox::information(nullptr, "Info", "Press Confirm To Play The Video");
}

void VideoList::onPreviousClicked()
{
	if (videoPlayer.currentVideo == nullptr) {
		return;
	}
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

void VideoList::onRemoveClicked() {
	if (selectedVideoPathRemove.isEmpty()) {
		QMessageBox::warning(this, "Warning", "No video selected for removal");
		return;
	}
	string s = selectedVideoPathRemove.toStdString();
	int i = videoPlayer.list.searchByPath(s);
	if (i != -1) {
		videoPlayer.list.erase(i);
		updateListView();
	}
	else {
		return;
	}
}

void VideoList::onItemClickedForSwap(const QModelIndex& index)
{
	if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
		selectedVideoPathSwap2 = index.data(Qt::DisplayRole).toString();
	}
	else {
		selectedVideoPathSwap1 = index.data(Qt::DisplayRole).toString();
		selectedVideoPathSwap2.clear();
	}
}

void VideoList::onSwapClicked() {
	if (!selectedVideoPathSwap1.isEmpty() && !selectedVideoPathSwap2.isEmpty()) {
		string s1 = selectedVideoPathSwap1.toStdString();
		string s2 = selectedVideoPathSwap2.toStdString();
		videoPlayer.list.swap(s1, s2);
		updateListView();
	}
	else {
		QMessageBox::warning(this, "Warning", "Choose Two Videos inorder to swap");
		return;
	}
}