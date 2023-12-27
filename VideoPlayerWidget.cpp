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
#include <QMediaMetaData>

#include "VideoList.h"



VideoPlayerWidget::VideoPlayerWidget(QWidget* parent)
    : QWidget(parent),
    player(new QMediaPlayer),
    videoWidget(new QVideoWidget),
    playButton(new QPushButton),
    pauseButton(new QPushButton),
    stopButton(new QPushButton),
    volumeSlider(new QSlider),
    audioOutput(new QAudioOutput),
    confirmButton(new QPushButton),
    expandButton(new QPushButton),
    positionSlider(new QSlider),
    durationLabel (new QLabel),
    seeDetails(new QPushButton),
    skipForwardButton (new QPushButton),
    skipBackwardButton (new QPushButton)

{
    this->showNormal();

    setWindowIcon(QIcon(":/new/prefix1/play.ico"));

    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    audioOutput = new QAudioOutput(this);
    player->setVideoOutput(videoWidget);
    player->setAudioOutput(audioOutput);
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
    expandButton->setFixedSize(60, 35);
    skipForwardButton = new QPushButton("skip forward 5s", this);
    skipBackwardButton = new QPushButton("skip backward 5s", this);
    expandButton->setFixedSize(60, 35);
    expandButton->setFixedSize(60, 35);

    urlField = new QLineEdit(this);
    urlField->setReadOnly(true);
    urlField->setPlaceholderText("Video Path Will be Added By the List Here");

    volumeSlider->setFixedWidth(70);

    durationLabel = new QLabel(this);
    durationLabel->setText("00:00:00");
    durationLabel->setFixedWidth(70);



    durationLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    durationLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    seeDetails = new QPushButton("See More Details About The Video");
    seeDetails-> setFixedSize(200, 20);
    seeDetails->setStyleSheet("background-color: lightblue; color: black;");





    // Connect slots
    connect(playButton, &QPushButton::clicked, player, &QMediaPlayer::play);
    connect(pauseButton, &QPushButton::clicked, player, &QMediaPlayer::pause);
    connect(stopButton, &QPushButton::clicked, player, &QMediaPlayer::stop);
    connect(confirmButton, &QPushButton::clicked, this, &VideoPlayerWidget::checkFileExtension);
    connect(volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));
    connect(positionSlider, &QSlider::sliderMoved, this, &VideoPlayerWidget::setPosition);
    connect(player, &QMediaPlayer::positionChanged, this, &VideoPlayerWidget::updatePosition);
    connect(player, &QMediaPlayer::durationChanged, this, &VideoPlayerWidget::updateDuration);
    connect(expandButton, &QPushButton::clicked, this, &VideoPlayerWidget::makeFullscreen);
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(onDurationChanged(qint64)));
    connect(seeDetails, &QPushButton::clicked, this, &VideoPlayerWidget::showVideoInfo);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &VideoPlayerWidget::onMediaStatusChanged);
    connect(skipForwardButton, &QPushButton::clicked, this, &VideoPlayerWidget::skipForward);
    connect(skipBackwardButton, &QPushButton::clicked, this, &VideoPlayerWidget::skipBackward);



    QVBoxLayout* layout = new QVBoxLayout;
    QHBoxLayout* topLayout = new QHBoxLayout;
    QHBoxLayout* bottomLayout = new QHBoxLayout;



    topLayout->addWidget(urlField);


    bottomLayout->addWidget(playButton);
    bottomLayout->addWidget(pauseButton);
    bottomLayout->addWidget(stopButton);
    bottomLayout->addWidget(volumeSlider);
    bottomLayout->addWidget(expandButton);
    bottomLayout->addWidget(durationLabel);
    bottomLayout->addWidget(skipBackwardButton);
    bottomLayout->addWidget(skipForwardButton);
    layout->addLayout(topLayout);
    layout->addWidget(videoWidget);
    layout->addLayout(bottomLayout);
    topLayout->addWidget(confirmButton);

    layout->addWidget(positionSlider);
    layout->addWidget(seeDetails);

    setLayout(layout);


}


void VideoPlayerWidget::checkFileExtension()
{
    QString filePath = urlField->text();
    player->setSource(QUrl::fromLocalFile(filePath));
    player->play();
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
    seeDetails->hide();
    QMessageBox::information(nullptr, "Info", "Press Exit Key to Escape Full Screen");


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
        seeDetails->show();

    }
    else {
        QWidget::keyPressEvent(event);
    }
}
void VideoPlayerWidget::setVideoPath(const QString& videoPath)
{
    urlField->setText(videoPath);
}
void VideoPlayerWidget::closeEvent(QCloseEvent* event)
{
    player->setAudioOutput(nullptr);
    QWidget::closeEvent(event);
}
QString formatDuration(qint64 duration) {
    int hours = duration / 3600000;
    int minutes = (duration % 3600000) / 60000;
    int seconds = (duration % 60000) / 1000;
    return QString("%1:%2:%3").arg(hours, 2, 10, QChar('0')).arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));

}
void VideoPlayerWidget::onDurationChanged(qint64 duration) {
    QString durationText = formatDuration(duration);
    durationLabel->setText(durationText);

}

void VideoPlayerWidget::showVideoInfo()
{
    
    QMessageBox msgBox(this);
    
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    msgBox.setText("See details");
    msgBox.setDetailedText(videoInfo);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void VideoPlayerWidget::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia) {
        QMediaMetaData metadata = player->metaData();
        QString videoCodec = metadata.stringValue(QMediaMetaData::VideoCodec);
        QString Format = metadata.stringValue(QMediaMetaData::FileFormat);
        QString videoBitRate = metadata.stringValue(QMediaMetaData::VideoBitRate);
        QString videoFrameRate = metadata.stringValue(QMediaMetaData::VideoFrameRate);
        QString resolution = metadata.stringValue(QMediaMetaData::Resolution);

        videoInfo.append("videoCodec:"+videoCodec  +"\n");
        videoInfo.append("VideoFormat" + Format + "\n");
        videoInfo.append("VideoBitRate:"+ videoBitRate + ": " + "\n");
        videoInfo.append("videoFrameRate: "+ videoFrameRate  + "\n");
        videoInfo.append("resolution:"+resolution +"\n");
    }
}

void VideoPlayerWidget::skipForward() {
    qint64 currentPosition = player->position();
    player->setPosition(currentPosition + 5000); // Skip forward by 5000 ms (5 seconds)
}

void VideoPlayerWidget::skipBackward() {
    qint64 currentPosition = player->position();
    player->setPosition(currentPosition - 5000); // Skip backward by 5000 ms (5 seconds)
}
