#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>

#include <ui_VideoList.h>

class VideoList : public QMainWindow
{
	Q_OBJECT

public:
	VideoList(QWidget* parent = nullptr);
	~VideoList();
private slots:
	void addVideoPath();

private:
	QLineEdit* lineEdit;
	QListView* listView;
	QPushButton* okButton;
	QPushButton* PreviousButton;
	QPushButton* NextButton;
	void addVideoPathToListView(const QString& videoPath);
	Ui::VideoListClass ui;
};
