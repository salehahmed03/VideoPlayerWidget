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
#include <sstream> 
#include <iomanip>


class AddressList : public QMainWindow
{
	Q_OBJECT

public:
	AddressList(QWidget* parent = nullptr);
	void updateAddressListView(VideoPlayer& videoPlayer);

private slots:

private:
	QListView* listView;
	Ui::VideoListClass ui;
};