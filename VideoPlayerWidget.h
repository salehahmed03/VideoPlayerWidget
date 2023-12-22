#pragma once

#ifndef VIDEOPLAYERWIDGET_H
#define VIDEOPLAYERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QSlider>
#include <QLabel>


class VideoPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayerWidget(QWidget* parent = nullptr);
     void setVideoPath(const QString& videoPath);

     
    
    
private slots:
    
    void checkFileExtension();
    

    void setPosition(int position);

    void updatePosition(qint64 position);

    void updateDuration(qint64 duration);

    void setVolume(int value);

    void makeFullscreen();
    void keyPressEvent(QKeyEvent* event);
    
    void closeEvent(QCloseEvent* event) override;

    void onDurationChanged(qint64 duration);


    


private:
    
    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    QVideoWidget* videoWidget;
    QPushButton* playButton;
    QPushButton* pauseButton;
    QPushButton* stopButton;
    QLineEdit* urlField; 
    QSlider* volumeSlider;
    QPushButton* expandButton;
    QPushButton* confirmButton;
    QSlider* positionSlider;
    QLabel* durationLabel;


    
};



#endif // VIDEOPLAYERWIDGET_H
