#pragma once
#ifndef VideoPlayer_H
#define VideoPlayer_H

#include "Video.h"
#include "videoLinkedList.h"
#include <iostream>
#include <string>
using namespace std;

class VideoPlayer {
private:
    videoLinkedList::NodePointer currentVideo;
    bool isPlaying;

public:
    videoLinkedList list;
    VideoPlayer();
    void setCurrentVideoByName(const string& name);
    void setCurrentVideoByPath(const string& path);
    void setCurrentVideoByIndex(int index);
    void pause();
    void resume();
    void next();
    void previous();
    void swap(const string& name1, const string& name2);
};

#endif