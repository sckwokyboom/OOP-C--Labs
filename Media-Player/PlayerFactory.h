#ifndef MAIN_CPP_PLAYERFACTORY_H
#define MAIN_CPP_PLAYERFACTORY_H

class PlayerFactory {
public:
    PlayerFactory() = default;
    PlayerFactory(PlayerFactory &other) = delete;
    PlayerFactory *operator=(PlayerFactory &other) = delete;
    ~PlayerFactory() {
        for (auto &pair: creators_) {
            delete pair.second;
            std::cout << "Delete ctor" << std::endl;
        }
    }

    static PlayerFactory & getInstance() {
        static PlayerFactory obj;
        return obj;
    }

    bool registerPlayer(MediaPlayer *player, const int &i) {
        creators_[i] = player;
        return true;
    }

    MediaPlayer * getPlayer(const int &i) {
        if (creators_[i] != nullptr)
            return creators_[i];
        throw std::runtime_error("Non-existent player id");
    }
private:
    std::unordered_map<int, MediaPlayer *> creators_;
};

namespace {
    const int MP3_PLAYER_CODE = 1;
    const int MIDI_PLAYER_CODE = 2;

    MediaPlayer * MidiPlayer_creator() {
        return new MidiPlayer();
    }

    bool MidiPlayer = PlayerFactory::getInstance().registerPlayer(MidiPlayer_creator(), MIDI_PLAYER_CODE);

    MediaPlayer * MP3Player_creator() {
        return new MP3Player();
    }

    bool MP3Player = PlayerFactory::getInstance().registerPlayer(MP3Player_creator(), MP3_PLAYER_CODE);
}


#endif //MAIN_CPP_PLAYERFACTORY_H
