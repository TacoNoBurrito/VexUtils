/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\tradl                                            */
/*    Created:      Tue Mar 01 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <vector>
#include <thread>
#include <string.h>

class ButtonPressable {

  public:

  // Brain Dimensions 480 x 240 (first 32 are used by vex itself on the y-axis)
  const int brainDimX = 480;
  const int brainDimY = 240;

  int x;
  int y;
  int width;
  int height;
  std::string text = "Filler";
  
  // red
  vex::color boxColor = vex::color(255, 0, 0);

  void (*onPress)();

  vex::thread pressListener;
  bool running = true;

  void pressListenerThread() {
    while (true) {
      if (!running) return;
      if (Brain.Screen.pressing()) {
        int xPos = Brain.Screen.xPosition();
        int yPos = Brain.Screen.yPosition();
        if (xPos >= x && x <= (x + width) && yPos >= y && y <= (y + height)) {
          onPress();
        }
      }
      this_thread::sleep_for(20);
    }
  }

  void draw() {
    Brain.Screen.setPenColor(boxColor);
    Brain.Screen.drawRectangle(x, y, width, height);
    Brain.Screen.setPenColor(vex::color(0, 0, 0));
    Brain.Screen.printAt(
      ((x + (width / 2)) - (text.length() * 3)), // x 
      (y  + (width / 2)), // y
      false, 
      text.c_str()
    );
  }

  void stopListener() {
    running = false;
  }

  void startListener() {
    pressListener = vex::thread(pressListener);
  }

};

void addButton(int x, int y, int width, int height, void (*onPress)(), std::string text = "Filler", vex::color color = vex::color(255, 0, 0)) {
  ButtonPressable pressableButton;
  pressableButton.x = x;
  pressableButton.y = y;
  pressableButton.width = width;
  pressableButton.height = height;
  pressableButton.onPress = onPress;
  pressableButton.startListener();
  pressableButton.draw();
}

void onButtonPress() {
  Brain.Screen.clearScreen();
}

int main() {
  addButton(0, 0, 250, 100, onButtonPress, "Clear", vex::color(255, 0, 0));
}
