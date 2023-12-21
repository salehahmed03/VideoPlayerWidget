#include"VideoPlayerWidget.h"
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>
#include <QAudioOutput>
#include <QSlider>
#include <QSlider>
#include <QLabel>
#include <QKeyEvent>



VideoPlayerWidget::VideoPlayerWidget(QWidget* parent)
    : QWidget(parent),
    player(new QMediaPlayer),
    videoWidget(new QVideoWidget),
    playButton(new QPushButton),
    pauseButton(new QPushButton),
    stopButton(new QPushButton),
    volumeSlider(new QSlider),
    urlField(new QLineEdit),
    audioOutput(new QAudioOutput),
    browseButton(new QPushButton),
    confirmButton(new QPushButton),
    expandButton (new QPushButton),
    positionSlider (new QSlider)
   

{
    this->showNormal();
    setWindowIcon(QIcon(":/new/prefix1/play.ico"));
    
    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    audioOutput = new QAudioOutput(this);
    
    player->setAudioOutput(audioOutput);
    player->setVideoOutput(videoWidget);
    
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);
    playButton = new QPushButton("Play", this);
    pauseButton = new QPushButton("Pause", this);
    stopButton = new QPushButton("Stop", this);
    confirmButton = new QPushButton("Confirm", this);
    confirmButton->setStyleSheet("background-color: green; color: white;");
    stopButton->setStyleSheet("background-color: red; color: white;");
    positionSlider = new QSlider(Qt::Horizontal, this);
    expandButton = new QPushButton("Expand", this);
    expandButton->setFixedSize(60,35);
    urlField = new QLineEdit(this);
    urlField->setPlaceholderText("Insert Your URL or VideoPath here");
    browseButton = new QPushButton("Browse folders", this);
    volumeSlider->setFixedWidth(70);
   


    // Connect slots
    connect(playButton, &QPushButton::clicked, player, &QMediaPlayer::play);
    connect(pauseButton, &QPushButton::clicked, player, &QMediaPlayer::pause);
    connect(stopButton, &QPushButton::clicked, player, &QMediaPlayer::stop);
    connect(browseButton, &QPushButton::clicked, this, &VideoPlayerWidget::openFileDialog);
    connect(confirmButton, &QPushButton::clicked, this, &VideoPlayerWidget::checkFileExtension);
    connect(volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));
    connect(positionSlider, &QSlider::sliderMoved, this, &VideoPlayerWidget::setPosition);
    connect(player, &QMediaPlayer::positionChanged, this, &VideoPlayerWidget::updatePosition);
    connect(player, &QMediaPlayer::durationChanged, this, &VideoPlayerWidget::updateDuration);
    connect(expandButton, &QPushButton::clicked, this, &VideoPlayerWidget::makeFullscreen);
   

    QVBoxLayout* layout = new QVBoxLayout;
    QHBoxLayout* topLayout = new QHBoxLayout;
    QHBoxLayout* bottomLayout = new QHBoxLayout;
    
    

    topLayout->addWidget(urlField);
    topLayout->addWidget(browseButton);

    bottomLayout->addWidget(playButton);
    bottomLayout->addWidget(pauseButton);
    bottomLayout->addWidget(stopButton);
    bottomLayout->addWidget(volumeSlider);
    bottomLayout->addWidget(expandButton);
    layout->addLayout(topLayout);
    layout->addWidget(videoWidget);
    layout->addLayout(bottomLayout);
    topLayout->addWidget(confirmButton);
    layout->addWidget(positionSlider);
    

    setLayout(layout);


}
void VideoPlayerWidget::openFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "/", tr("Video Files (*.mp4 *.avi *.mkv)"));
    urlField->setText(filePath);
    //msh 3arf tt8er wla la
}

void VideoPlayerWidget::checkFileExtension()
{
    QString filePath = urlField->text();
    if (filePath.endsWith(".mp4") || filePath.endsWith(".avi") || filePath.endsWith(".mkv"))
    {
        
        player->setSource(QUrl::fromLocalFile(filePath));
        player->play(); 
        //to be replaced by our orginal checking code ....
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Unacceptable Path, Make Sure That extension given is (*.mp4 *.avi *.mkv) and Try Again !!!"));
        /*dont change message*/
    }
}



void VideoPlayerWidget::setPosition(int position) {
    player->setPosition(position);
}

void VideoPlayerWidget::updatePosition(qint64 position) {
    positionSlider->setValue(position);
}

void VideoPlayerWidget::updateDuration(qint64 duration) {
    positionSlider->setRange(0, duration);
}
void VideoPlayerWidget::setVolume(int value) {
    audioOutput->setVolume(value / 100.0);
}
void VideoPlayerWidget::makeFullscreen() {
    this->showFullScreen();
    playButton->hide();
    pauseButton->hide();
    stopButton->hide();
    volumeSlider->hide();
    positionSlider->hide();
    expandButton->hide();
    urlField->hide();
    confirmButton->hide();
    browseButton->hide();
    
}
void VideoPlayerWidget::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape && this->isFullScreen()) {
        this->showMaximized();
        playButton->show();
        pauseButton->show();
        stopButton->show();
        volumeSlider->show();
        positionSlider->show();
        expandButton->show();
        urlField->show();
        confirmButton->show();
        browseButton->show();
    }
    else {
        QWidget::keyPressEvent(event);
    }
}