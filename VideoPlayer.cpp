#include "VideoPlayer.h"
#ifdef VideoPlayer_H

VideoPlayer::VideoPlayer() {
    currentVideo = list.first;
    isPlaying = false;
}

void VideoPlayer::setCurrentVideoByName(const string& name) {
    int index = list.searchByName(name);
    if (index >= 0 && index < list.nodeCount()) {
        videoLinkedList::NodePointer ptr = list.first;
        for (int i = 0; i < index; ++i) {
            ptr = ptr->next;
        }
        currentVideo = ptr;
        isPlaying = true;
    }
    else {
        cout << "Video name not found" << endl;
    }
}

void VideoPlayer::setCurrentVideoByPath(const string& path) {
    int index = list.searchByPath(path);
    if (index >= 0 && index < list.nodeCount()) {
        videoLinkedList::NodePointer ptr = list.first;
        for (int i = 0; i < index; ++i) {
            ptr = ptr->next;
        }
        currentVideo = ptr;
        isPlaying = true;
    }
    else {
        cout << "Video path not found" << endl;
    }
}

void VideoPlayer::setCurrentVideoByIndex(int index) {
    if (index >= 0 && index < list.nodeCount()) {
        videoLinkedList::NodePointer ptr = list.first;
        for (int i = 0; i < index; ++i) {
            ptr = ptr->next;
        }
        currentVideo = ptr;
        isPlaying = true;
    }
    else {
        cout << "Video path not found" << endl;
    }
}

void VideoPlayer::pause() {
    if (!isPlaying) {
        cout << "The Video: " << currentVideo->data.getFileName() << " is already paused" << endl;
        return;
    }
    cout << currentVideo->data.getFileName() << " is paused" << endl;
    isPlaying = false;
}

void VideoPlayer::resume() {
    if (isPlaying) {
        cout << "The Video: " << currentVideo->data.getFileName() << " is already resumed" << endl;
        return;
    }
    cout << currentVideo->data.getFileName() << " is resumed" << endl;
    isPlaying = true;
}

void VideoPlayer::next() {
    currentVideo = currentVideo->next;
    cout << "The Video: " << currentVideo->data.getFileName() << endl;
    isPlaying = true;
}

void VideoPlayer::previous() {
    currentVideo = currentVideo->prev;
    cout << "The Video: " << currentVideo->data.getFileName() << endl;
    isPlaying = true;
}

void VideoPlayer::swap(const string& name1, const string& name2) {
    list.swap(name1, name2);
}

#endif
