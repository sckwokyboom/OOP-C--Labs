#include <stdexcept>
#include <string>
#include <unordered_map>
#include "MediaPlayer.h"
#include "PlayerFactory.h"

int main(int argc, char **argv) {
    std::string arg;
    int n;
    if (argc == 1) {
        std::cerr << "No args" << std::endl;
        return 0;
    }

    try {
        arg = argv[1];
        std::size_t pos;
        n = std::stoi(arg, &pos);
        if (pos < arg.size()) {
            std::cerr << "Trailing characters after number: " << arg << std::endl;
        }
    } catch (std::invalid_argument const &ex) {
        std::cerr << "Invalid number: " << arg << std::endl;
        return 0;
    } catch (std::out_of_range const &ex) {
        std::cerr << "Number out of range: " << arg << std::endl;
        return 0;
    }
    PlayerFactory::getInstance().getPlayer(n)->play();
    return 0;
}

/*
1. создайте базовый класс MediaPlayer. Этот класс должен иметь виртуальную функцию void play()
2. создайте двух наследников MediaPlayer: MidiPlayer и MP3Player. Каждый из них должен перегружать
   метод play и печатать в консоль какое-нибудь сообщение
3. создайте класс PlayerFactory, в котором будут методы:
    - bool registerPlayer(MediaPlayer * player, int i)
    - MediaPlayer * getPlayer(int)
   не забудьте сделать этот класс синглтоном (как мы делали с getInstance)
4. сделайте регистрацию MidiPlayer и MP3Player с помощью объявления глобальных переменных
   в анонимном нэймспейсе (как делали на семинаре)
5. напишите метод main, который парсит из входных аргументов целое число и пытается создать
   и запустить плеер который зарегистрирован с тем же числом. если не находит такой плеер, то печатает ошибку.
   Плееры должны искаться с помощью методов фабрики.
Подсказка: сразу объявляйте каждый класс в отдельном хэдере
Подсказка2: не забудьте include guard'ы
*/
