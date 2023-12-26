#include "AddressList.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileDialog>
#include <QMessageBox>
#include<QHash>
#include <QMediaMetaData>
#include <QTextEdit>

AddressList::AddressList(QWidget* parent)
	: QMainWindow(parent),
	listView(new QListView)

{
	this->showNormal();
	ui.setupUi(this);
	setWindowTitle("Address List");
	listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	setWindowIcon(QIcon(":/new/prefix1/play.ico"));

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(listView);


	QWidget* centralWidget = new QWidget;
	centralWidget->setLayout(layout);
	setCentralWidget(centralWidget);

}

void AddressList::updateAddressListView(VideoPlayer& videoPlayer) {
	QStandardItemModel* model = qobject_cast<QStandardItemModel*>(listView->model());

	if (!model) {
		model = new QStandardItemModel(listView);
		listView->setModel(model);
	}

	model->clear();

	LPVOID address;
	videoLinkedList::NodePointer ptr;
	string addressString;
	for (int i = 0; i < videoPlayer.list.nodeCount(); ++i) {
		ptr = videoPlayer.list.getElementPtrByIndex(i);
		address = ptr->data.getFileAddress();
		stringstream stream;
		stream << "0x" << hex << reinterpret_cast<uintptr_t>(address);
		addressString = stream.str();

		QStandardItem* item = new QStandardItem(QString::fromStdString(addressString));
		model->appendRow(item);
	}
}

