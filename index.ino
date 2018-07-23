// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>
#include <string.h>

// Some variables to replace. My neopixel example has 3 neopixels, so set to 3
#define NUMPIXELS 3
// Our data is located at D0, so all PINOUTS should come from here
#define PINOUT D0

// From the neopixel library, define our set of pixels
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PINOUT, WS2812B);


// A function for setting all pixels to a single color
void setColor(int r, int g, int b) {
    for(int i = 0; i < NUMPIXELS; i++ ) {
         pixels.setColor(i, r, g, b);   
    }
}

// Sets pixel color at specified index only
void setSingleColor(int index, int r, int g, int b) {
    pixels.setColor(index, r, g, b);
}
 
// Enums, which will be looked at in our loop() to see if any SET COLOR commands have been called
enum Command_type {
     NONE,
     SET_RED,
     SET_GREEN,
     SET_BLUE,
     SET_STOPLIGHT,
     SET_RANDOM
};

enum Command_type action;

// handling of our command. this is our command for our registered particle function
int command(String _cmd) {
    String cmd = _cmd.toLowerCase();
    
    if(cmd == "red") {
        action = SET_RED;
    } else 
    if(cmd == "green" ) {
        action = SET_GREEN;
    } else 
    if(cmd == "blue") {
        action = SET_BLUE;
    } else 
    if (cmd == "stop light") {
        action = SET_STOPLIGHT;
    } else
    if (cmd == "random") {
        action = SET_RANDOM;
    }
    return -1;
}

void setup() {
    action = NONE;
    pixels.begin();
    // register our particle function. You don't need to do anything beforehand here. Declare it below just like this
    // and when you flash it, it should then be available on your particle console and at IFTTT (via Particle API).
    Particle.function("command", command);
    // these guys are really bright! So we'll set them to 32 (range from 0-255)
    pixels.setBrightness(32);
}

void loop() {
    // if action is set to none, no operations need to occur. just finish
    if(action != NONE) {
        switch (action) {
            case SET_RED: 
                setColor(255,0,0); 
                break;
            case SET_GREEN: 
                setColor(0,255,0);
                break;
            case SET_BLUE: 
                setColor(0,0,255); 
                break;
            case SET_STOPLIGHT:
                setSingleColor(0, 255, 0, 0);
                setSingleColor(1, 255, 255, 0);
                setSingleColor(2, 0, 255, 0);
                break;
            case SET_RANDOM:
                int r1 = rand()%255; int g1 = rand()%255; int b1 = rand()%255;
                int r2 = rand()%255; int g2 = rand()%255; int b2 = rand()%255;
                int r3 = rand()%255; int g3 = rand()%255; int b3 = rand()%255;
                
                setSingleColor(0, r1, g1, b1);
                setSingleColor(1, r2, g2, b2);
                setSingleColor(2, r3, g3, b3);
                break;
        }
        // an action occurred, and we handled it. set action enum to none
        action = NONE;
        // an action occurred, so it's time to rener the pixels. Update by pixels.show();
        pixels.show();
    }
}