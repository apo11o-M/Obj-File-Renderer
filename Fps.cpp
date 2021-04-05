// 4/2/2021
// This class calculates and updates the FPS of the current window
//
// Basically what it does is it has a counter(mFrame), and everytime the window
// renders a frame, the counter goes up by one. If the elapsed time after the  
// last output is more than one second (or whatever second we would like), we
// reset the counter and update the FPS variable to print.

#ifndef FPS_CPP
#define FPS_CPP
#include <SFML/Graphics.hpp>

class FPS {
    public:
        FPS() : mFrame(0), mFps(0) {}
        const unsigned int getFPS() const {return mFps;}

    private:
        unsigned int mFrame;
        unsigned int mFps;
        sf::Clock mClock;

    public:
        void update() {
            if(mClock.getElapsedTime().asSeconds() >= 0.5f) {
                mFps = mFrame * 2;
                mFrame = 0;
                mClock.restart();
            }
            mFrame++;
        }

};

#endif