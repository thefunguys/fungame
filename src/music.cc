#include "music.h"
#include "sfml.h"
#include "fns.h"

sf::Sound* sound;
sf::SoundBuffer* sb;

void play(std::string song) {
    delete sound;
    delete sb;
    sb = new sf::SoundBuffer;
    if (!sb->loadFromFile(song)) {
        dbpf("failed to load song %s\n", song.c_str());
        return;
    }
    sound = new sf::Sound;
    sound->setBuffer(*sb);
    sound->play();
}
