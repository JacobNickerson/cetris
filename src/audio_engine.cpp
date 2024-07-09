#include "audio_engine.hpp"

// AudioEngineBuffers
void AudioEngineBuffers::initialize() {
    buffer_place.loadFromFile("./sounds/place_tetromino.wav");
    buffer_harddrop.loadFromFile("./sounds/hard_drop.wav");
    buffer_menu_transition.loadFromFile("./sounds/menu_transition.wav");
    buffer_collision.loadFromFile("./sounds/collision.wav");
    buffer_one_line_clear.loadFromFile("./sounds/one_line_clear.wav");
    buffer_two_line_clear.loadFromFile("./sounds/two_line_clear.wav");
    buffer_three_line_clear.loadFromFile("./sounds/three_line_clear.wav");
    buffer_four_line_clear.loadFromFile("./sounds/four_line_clear.wav");

}

// AudioEngine
    void AudioEngine::initialize() {
        place.setBuffer(buffers.buffer_place);
        harddrop.setBuffer(buffers.buffer_harddrop);
        menu_transition.setBuffer(buffers.buffer_menu_transition);
        collision.setBuffer(buffers.buffer_collision);
        one_line_clear.setBuffer(buffers.buffer_one_line_clear);
        two_line_clear.setBuffer(buffers.buffer_two_line_clear);
        three_line_clear.setBuffer(buffers.buffer_three_line_clear);
        four_line_clear.setBuffer(buffers.buffer_four_line_clear);
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