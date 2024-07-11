#include "audio_engine.hpp"

// AudioEngineBuffers
bool AudioEngineBuffers::initialize() {
    if (!buffer_place.loadFromFile("./sounds/place_tetromino.wav")) return false;
    if (!buffer_harddrop.loadFromFile("./sounds/hard_drop.wav")) return false;
    if (!buffer_menu_transition.loadFromFile("./sounds/menu_transition.wav")) return false;
    if (!buffer_collision.loadFromFile("./sounds/collision.wav")) return false;
    if (!buffer_one_line_clear.loadFromFile("./sounds/one_line_clear.wav")) return false;
    if (!buffer_two_line_clear.loadFromFile("./sounds/two_line_clear.wav")) return false;
    if (!buffer_three_line_clear.loadFromFile("./sounds/three_line_clear.wav")) return false;
    if (!buffer_four_line_clear.loadFromFile("./sounds/four_line_clear.wav")) return false;
    return true;
}

// AudioEngine
    bool AudioEngine::initialize() {
        if (!buffers.initialize()) return false;
        place.setBuffer(buffers.buffer_place);
        harddrop.setBuffer(buffers.buffer_harddrop);
        menu_transition.setBuffer(buffers.buffer_menu_transition);
        collision.setBuffer(buffers.buffer_collision);
        one_line_clear.setBuffer(buffers.buffer_one_line_clear);
        two_line_clear.setBuffer(buffers.buffer_two_line_clear);
        three_line_clear.setBuffer(buffers.buffer_three_line_clear);
        four_line_clear.setBuffer(buffers.buffer_four_line_clear);
        if (!play_music.openFromFile("music/tetris.ogg")) return false;
        return true;
    }

    void AudioEngine::playPlace() {
        place.play();
    }

    void AudioEngine::playHardDrop() {
        harddrop.play();
    }

    void AudioEngine::playMenuTransition() {
        menu_transition.play();
    }

    void AudioEngine::playCollision() {
        collision.play();
    }

    void AudioEngine::playOneLineClear() {
        one_line_clear.play();
    }

    void AudioEngine::playTwoLineClear() {
        two_line_clear.play();
    }

    void AudioEngine::playThreeLineClear() {
        three_line_clear.play();
    }

    void AudioEngine::playFourLineClear() {
        four_line_clear.play();
    }

    void AudioEngine::playMusic() {
        play_music.setLoop(true);
        play_music.play();
    }

    void AudioEngine::stopMusic() {
        play_music.stop();
    }