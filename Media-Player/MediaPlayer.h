#ifndef MAIN_CPP_MEDIAPLAYER_H
#define MAIN_CPP_MEDIAPLAYER_H

#include <iostream>

class MediaPlayer {
public:
    virtual ~MediaPlayer() = default;
    virtual void play() = 0;
};

class MidiPlayer: public MediaPlayer {
public:
    void play() override {
        std::cout << "MidiPlayer" << std::endl;
    }
};

class MP3Player: public MediaPlayer {
public:
    void play() override {
        std::cout << "MP3Player" << std::endl;
    }
};

#endif //MAIN_CPP_MEDIAPLAYER_H
