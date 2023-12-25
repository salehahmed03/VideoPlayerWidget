#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include<QHash>
#include <QMediaMetaData>
#include <ui_VideoList.h>
#include "VideoPlayer.h"
#include "VideoPlayerWidget.h"

class VideoList : public QMainWindow
{
	Q_OBJECT

public:
	VideoPlayerWidget* V = new VideoPlayerWidget;
	VideoPlayer videoPlayer;
	VideoList(QWidget* parent = nullptr);
	~VideoList();



private slots:
	void addVideoPath();
	void updateListView();
	void openFileDialog();
	void listItemDoubleClicked(const QModelIndex& index);
	void onNextClicked();
	void onPreviousClicked();
	void onItemClickedForRemove(const QModelIndex& index);
	void onRemoveClicked();
	void onItemClickedForSwap(const QModelIndex& index);
	void onSwapClicked();
	


private:
	QLineEdit* lineEdit;
	QListView* listView;
	QPushButton* okButton;
	QPushButton* PreviousButton;
	QPushButton* NextButton;
	QPushButton* browseButton;
	QString selectedVideoPath;
	QString selectedVideoPathRemove;
	QString selectedVideoPathSwap1;
	QString selectedVideoPathSwap2;
	QPushButton* removeButton;
	QPushButton* swapButton;
	

	Ui::VideoListClass ui;
};