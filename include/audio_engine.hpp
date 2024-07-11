#ifndef AUDIO_ENGINE_HPP
#define AUDIO_ENGINE_HPP

#include <SFML/Audio.hpp>

struct AudioEngineBuffers {  
    sf::SoundBuffer buffer_place;
    sf::SoundBuffer buffer_harddrop;
    sf::SoundBuffer buffer_menu_transition;
    sf::SoundBuffer buffer_collision;
    sf::SoundBuffer buffer_one_line_clear;
    sf::SoundBuffer buffer_two_line_clear;
    sf::SoundBuffer buffer_three_line_clear;
    sf::SoundBuffer buffer_four_line_clear;

    bool initialize();
};

class AudioEngine {
    public:
        AudioEngine() {}
        
        bool initialize();

        void playPlace();

        void playHardDrop();

        void playMenuTransition();

        void playCollision();

        void playOneLineClear();

        void playTwoLineClear();

        void playThreeLineClear();

        void playFourLineClear();

        void playMusic();

        void stopMusic();

    private:
        AudioEngineBuffers buffers;
        sf::Music play_music;
        sf::Sound place;
        sf::Sound harddrop;
        sf::Sound menu_transition;
        sf::Sound collision;
        sf::Sound one_line_clear;
        sf::Sound two_line_clear;
        sf::Sound three_line_clear;
        sf::Sound four_line_clear;
};

#endif