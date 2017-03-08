#include <UTFT.h>
#include <UTouch.h>
#include <TaskScheduler.h>

#include "board.c"

#include "board11.c"
#include "board21.c"
#include "board31.c"
#include "board41.c"
#include "board12.c"
#include "board22.c"
#include "board32.c"
#include "board42.c"
#include "board13.c"
#include "board23.c"
#include "board33.c"
#include "board43.c"
#include "board14.c"
#include "board24.c"
#include "board34.c"
#include "board44.c"

int InitialBoardFood[2][82] = { { 15, 36, 59, 81, 105, 133, 158, 181, 203, 224,
    15, 59, 105, 133, 181, 224, 15, 36, 59, 81, 105, 133, 158, 181, 203,
    224, 15, 36, 59, 81, 105, 133, 158, 181, 203, 224, 59, 181, 59, 181, 59,
    181, 15, 36, 59, 81, 105, 133, 158, 181, 203, 224, 15, 36, 59, 81, 105,
    133, 158, 181, 203, 224, 15, 36, 59, 81, 105, 133, 158, 181, 203, 224,
    15, 36, 59, 81, 105, 133, 158, 181, 203, 224 }, { 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 30, 30, 30, 30, 30, 30, 45, 45, 45, 45, 45, 45, 45,
    45, 45, 45, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 90, 90, 112, 112,
    135, 135, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 178, 178,
    178, 178, 178, 178, 178, 178, 178, 178, 202, 202, 202, 202, 202, 202,
    202, 202, 202, 202, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226 } };

int BoardFood[2][82] = { { 15, 36, 59, 81, 105, 133, 158, 181, 203, 224, 15, 59,
    105, 133, 181, 224, 15, 36, 59, 81, 105, 133, 158, 181, 203, 224, 15,
    36, 59, 81, 105, 133, 158, 181, 203, 224, 59, 181, 59, 181, 59, 181, 15,
    36, 59, 81, 105, 133, 158, 181, 203, 224, 15, 36, 59, 81, 105, 133, 158,
    181, 203, 224, 15, 36, 59, 81, 105, 133, 158, 181, 203, 224, 15, 36, 59,
    81, 105, 133, 158, 181, 203, 224 }, { 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 30, 30, 30, 30, 30, 30, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
    67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 90, 90, 112, 112, 135, 135, 157,
    157, 157, 157, 157, 157, 157, 157, 157, 157, 178, 178, 178, 178, 178,
    178, 178, 178, 178, 178, 202, 202, 202, 202, 202, 202, 202, 202, 202,
    202, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226 } };

void MovePacman();
void MoveRedGhost();
void StartPinkGhost();
void MovePinkGhost();
void StartBlueGhost();
void MoveBlueGhost();
void StartOrangeGhost();
void MoveOrangeGhost();
int CheckPosition(int x, int y, int Direction);
void EatFood(int x, int y);
void AvoidFood(int x, int y, int Direction);
void DrawPacman(int x, int y);
void DrawRedGhost(int x, int y);
void DrawPinkGhost(int x, int y);
void DrawBlueGhost(int x, int y);
void DrawOrangeGhost(int x, int y);
void DrawFood();
void DrawBackground();
void StartOver();

Task TaskMovePacman(20, TASK_FOREVER, &MovePacman);
Task TaskMoveRedGhost(50, TASK_FOREVER, &MoveRedGhost);
Task TaskStartPinkGhost(50, TASK_FOREVER, &StartPinkGhost);
Task TaskMovePinkGhost(50, TASK_FOREVER, &MovePinkGhost);
Task TaskStartBlueGhost(45, TASK_FOREVER, &StartBlueGhost);
Task TaskMoveBlueGhost(45, TASK_FOREVER, &MoveBlueGhost);
Task TaskStartOrangeGhost(45, TASK_FOREVER, &StartOrangeGhost);
Task TaskMoveOrangeGhost(45, TASK_FOREVER, &MoveOrangeGhost);

// Creating Objects
UTFT myGLCD(ILI9341_16, 38, 39, 40, 41); //Parameters should be adjusted to your Display/Schield model
UTouch myTouch(6, 5, 4, 3, 2);
Scheduler runner;

int touch_x = 0, touch_y = 0;             // Touch positions initialization

int pacman_position_x = 156, pacman_position_y = 175;  // Pacman's start
int PacmanDirection = 0;

unsigned int steps = 0;
int FoodCounter = 0;
int lives = 3;

int red_ghost_position_x = 156, red_ghost_position_y = 87; // Red Ghost's start
int RedGhostDirection = 0;
int angle_red = 0;
int wall_red = 0;
int priority_red = 0;
int third_choice_red = 0;
int exception_red = 0;
int variable_red = 0;

int pink_ghost_position_x = 156, pink_ghost_position_y = 107; // Pink Ghost's start
int PinkGhostDirection = 0;
int angle_pink = 0;
int wall_pink = 0;
int priority_pink = 1;
int third_choice_pink = 0;
int exception_pink = 0;
int variable_pink = 0;
int count_steps_pink = 0;

int blue_ghost_position_x = 141, blue_ghost_position_y = 107; // Blue Ghost's start
int BlueGhostDirection = 0;
int priority_blue = 0;
int count_steps_blue = 0;

int orange_ghost_position_x = 171, orange_ghost_position_y = 107; // Orange Ghost's start
int OrangeGhostDirection = 0;
int priority_orange = 0;
int count_steps_orange = 0;

extern uint8_t BigFont[];

extern unsigned int pacman_right[0x64];
extern unsigned int pacman_left[0x64];
extern unsigned int pacman_up[0x64];
extern unsigned int pacman_down[0x64];

extern unsigned int pacman_right_closed[0x64];
extern unsigned int pacman_left_closed[0x64];
extern unsigned int pacman_up_closed[0x64];
extern unsigned int pacman_down_closed[0x64];

extern unsigned int red[0x64];
extern unsigned int pink[0x64];
extern unsigned int blue[0x64];
extern unsigned int orange[0x64];

extern unsigned int food[0x09];

void setup() {

  Serial.begin(9600);
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  DrawBackground();
  DrawFood();
  DrawPacman(pacman_position_x, pacman_position_y);
  DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
  DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
  DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
  DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);

  runner.init();
  runner.addTask(TaskMovePacman);
  runner.addTask(TaskMoveRedGhost);
  runner.addTask(TaskStartPinkGhost);
  runner.addTask(TaskMovePinkGhost);
  runner.addTask(TaskStartBlueGhost);
  runner.addTask(TaskMoveBlueGhost);
  runner.addTask(TaskStartOrangeGhost);
  runner.addTask(TaskMoveOrangeGhost);

  TaskMovePacman.enable();
  TaskMoveRedGhost.enable();
  TaskStartPinkGhost.enable();
  TaskStartBlueGhost.enable();
  TaskStartOrangeGhost.enable();

}

void loop() {
  runner.execute();
}

void MovePacman() {

  if (myTouch.dataAvailable()) { // Read touch position
    myTouch.read();
    touch_x = myTouch.getX();
    touch_y = myTouch.getY();

    EatFood(pacman_position_x, pacman_position_y);

    if ((touch_x >= 5) && (touch_x <= 30) && (touch_y >= 4) && (touch_y <= 30)) { // Move right

      PacmanDirection = 1;

      if (pacman_position_x == 268 && (pacman_position_y == 108 || pacman_position_y == 109 || pacman_position_y == 110)) { // Pacman uses tunnel when moving right
        myGLCD.setColor(0, 0, 0);
        for (int i = 0; i < 10; i++) {
          for (int j = 0; j < 10; j++) {
            myGLCD.drawPixel(268 + i, pacman_position_y + j);
          }
        }
        pacman_position_x = 46;
      }

      if (CheckPosition(pacman_position_x, pacman_position_y,PacmanDirection)) {
        pacman_position_x = pacman_position_x + 1;
        steps = steps + 1;
        DrawPacman(pacman_position_x, pacman_position_y);
      }
    }
    
    else if ((touch_x >= 5) && (touch_x <= 30) && (touch_y >= 44) && (touch_y <= 70)) { // Move left

      PacmanDirection = 2;

      if (pacman_position_x == 45 && (pacman_position_y == 108 || pacman_position_y == 109 || pacman_position_y == 110)) { // Pacman uses tunnel when moving left
        myGLCD.setColor(0, 0, 0);
        for (int i = 0; i < 10; i++) {
          for (int j = 0; j < 10; j++) {
            myGLCD.drawPixel(46 + i, pacman_position_y + j);
          }
        }
        pacman_position_x = 267;
      }

      if (CheckPosition(pacman_position_x, pacman_position_y,PacmanDirection)) {
        pacman_position_x = pacman_position_x - 1;
        steps = steps + 1;
        DrawPacman(pacman_position_x, pacman_position_y);
      }
    }
    
    else if ((touch_x >= 5) && (touch_x <= 30) && (touch_y >= 84) && (touch_y <= 110)) {  // Move up
      PacmanDirection = 3;
      if (CheckPosition(pacman_position_x, pacman_position_y,PacmanDirection)) {
        pacman_position_y = pacman_position_y - 1;
        steps = steps + 1;
        DrawPacman(pacman_position_x, pacman_position_y);
      }
    }
    
    else if ((touch_x >= 5) && (touch_x <= 30) && (touch_y >= 124) && (touch_y <= 150)) { // Move down
      PacmanDirection = 4;
      if (CheckPosition(pacman_position_x, pacman_position_y,PacmanDirection)) {
        pacman_position_y = pacman_position_y + 1;
        steps = steps + 1;
        DrawPacman(pacman_position_x, pacman_position_y);
      }
    }
    
  }

}

void StartPinkGhost() {
  if (count_steps_pink < 80) {     // Pink ghost does not move
      count_steps_pink = count_steps_pink + 1;
  }
  else if (count_steps_pink >= 80 && count_steps_pink <= 101) {
      count_steps_pink = count_steps_pink + 1;
      PinkGhostDirection = 3;
      pink_ghost_position_y = pink_ghost_position_y - 1;
      DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
  }
  else if (count_steps_pink > 101) {
      TaskMovePinkGhost.enable();
  }
}

void StartBlueGhost() {

  if (FoodCounter < 41) { // Blue ghost does not move unless pacman collects 41 points

  } 
  else {
    
    if (count_steps_blue < 120) {     // Blue ghost does not move
        count_steps_blue = count_steps_blue + 1;
    }
    else if (count_steps_blue >= 120 && count_steps_blue <= 131) {
        count_steps_blue = count_steps_blue + 1;
        BlueGhostDirection = 1;
        blue_ghost_position_x = blue_ghost_position_x + 1;
        DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
    }
    else if (count_steps_blue >= 132 && count_steps_blue <= 150) {
        count_steps_blue = count_steps_blue + 1;
        BlueGhostDirection = 3;
        blue_ghost_position_y = blue_ghost_position_y - 1;
        DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
    }
    else if (count_steps_blue > 150) {
        TaskMoveBlueGhost.enable();
    }
    
  }
}

void StartOrangeGhost() {

  if (FoodCounter < 51) { // Orange ghost does not move unless pacman collects 51 points

  }
  else {
    
    if (count_steps_orange < 160) {     // Orange ghost does not move
        count_steps_orange = count_steps_orange + 1;
    }
    else if (count_steps_orange >= 160 && count_steps_orange <= 171) {
        count_steps_orange = count_steps_orange + 1;
        OrangeGhostDirection = 2;
        orange_ghost_position_x = orange_ghost_position_x - 1;
        DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);
    } 
    else if (count_steps_orange >= 172 && count_steps_orange <= 190) {
        count_steps_orange = count_steps_orange + 1;
        OrangeGhostDirection = 3;
        orange_ghost_position_y = orange_ghost_position_y - 1;
        DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);
    }
    else if (count_steps_orange > 190) {
        TaskMoveOrangeGhost.enable();
    }
    
  }

}

void MoveRedGhost() {

  AvoidFood(red_ghost_position_x, red_ghost_position_y, RedGhostDirection);

  if ((pacman_position_x == red_ghost_position_x
      || pacman_position_x == red_ghost_position_x + 1
      || pacman_position_x == red_ghost_position_x + 2
      || pacman_position_x == red_ghost_position_x + 3
      || pacman_position_x == red_ghost_position_x + 4
      || pacman_position_x == red_ghost_position_x + 5
      || pacman_position_x == red_ghost_position_x + 6
      || pacman_position_x == red_ghost_position_x + 7
      || pacman_position_x == red_ghost_position_x + 8
      || pacman_position_x == red_ghost_position_x - 1
      || pacman_position_x == red_ghost_position_x - 2
      || pacman_position_x == red_ghost_position_x - 3
      || pacman_position_x == red_ghost_position_x - 4
      || pacman_position_x == red_ghost_position_x - 5
      || pacman_position_x == red_ghost_position_x - 6
      || pacman_position_x == red_ghost_position_x - 7
      || pacman_position_x == red_ghost_position_x - 8)
      && (pacman_position_y == red_ghost_position_y
          || pacman_position_y == red_ghost_position_y + 1
          || pacman_position_y == red_ghost_position_y + 2
          || pacman_position_y == red_ghost_position_y + 3
          || pacman_position_y == red_ghost_position_y + 4
          || pacman_position_y == red_ghost_position_y + 5
          || pacman_position_y == red_ghost_position_y + 6
          || pacman_position_y == red_ghost_position_y + 7
          || pacman_position_y == red_ghost_position_y + 8
          || pacman_position_y == red_ghost_position_y - 1
          || pacman_position_y == red_ghost_position_y - 2
          || pacman_position_y == red_ghost_position_y - 3
          || pacman_position_y == red_ghost_position_y - 4
          || pacman_position_y == red_ghost_position_y - 5
          || pacman_position_y == red_ghost_position_y - 6
          || pacman_position_y == red_ghost_position_y - 7
          || pacman_position_y == red_ghost_position_y - 8)) // Red Ghost catches pacman
      {
    lives = lives - 1;
    StartOver();
  }

  if (pacman_position_x > red_ghost_position_x && pacman_position_y > red_ghost_position_y) { // Ghost upper left , pacman down right
    if (priority_red == 0) {
      if (angle_red == 0 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          angle_red = 1;
        }
      } else if (angle_red == 0 && wall_red == 0 && exception_red == 1) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 1;
          exception_red = 0;
          variable_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 1;
          exception_red = 0;
          variable_red = 0;
        }
      } else if (angle_red == 1 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          angle_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          angle_red = 0;
        }
      } else if (angle_red == 0 && wall_red == 1 && exception_red == 0) { // when ghost is left and pacman right. Ghost moves up to avoid the wall_red
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          wall_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 1;
          wall_red = 0;
          third_choice_red = 1;
          variable_red = 4;
        }
      }
    } else if (priority_red == 1) {
      if (angle_red == 0 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          angle_red = 1;
        }
      } else if (angle_red == 0 && wall_red == 0 && exception_red == 1) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 0;
          exception_red = 0;
          variable_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 0;
          exception_red = 0;
          variable_red = 0;
        }
      } else if (angle_red == 1 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          angle_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          angle_red = 0;
        }
      } else if (angle_red == 0 && wall_red == 1 && exception_red == 0) { // when ghost is up and pacman down. Ghost moves left to avoid the wall_red
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          wall_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 0;
          wall_red = 0;
          third_choice_red = 1;
          variable_red = 1;
        }
      }
    }
  } else if (pacman_position_x < red_ghost_position_x && pacman_position_y < red_ghost_position_y) { // Ghost down right , pacman upper left
    if (priority_red == 0) {
      if (angle_red == 0 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          angle_red = 1;
        }
      } else if (angle_red == 0 && wall_red == 0 && exception_red == 1) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 1;
          exception_red = 0;
          variable_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 1;
          exception_red = 0;
          variable_red = 0;
        }
      } else if (angle_red == 0 && wall_red == 1 && exception_red == 0) { // when ghost is right and pacman left. Ghost moves down to avoid the wall_red
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          wall_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 1;
          wall_red = 0;
          third_choice_red = 1;
          variable_red = 3;
        }
      } else if (angle_red == 1 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          angle_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          angle_red = 0;
        }
      }
    } else if (priority_red == 1) {
      if (angle_red == 0 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          angle_red = 1;
        }
      } else if (angle_red == 0 && wall_red == 0 && exception_red == 1) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 0;
          exception_red = 0;
          variable_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 0;
          exception_red = 0;
          variable_red = 0;
        }
      } else if (angle_red == 1 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          angle_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          angle_red = 0;
        }
      } else if (angle_red == 0 && wall_red == 1 && exception_red == 0) { // when ghost is down and pacman up. Ghost moves right to avoid the wall_red
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          wall_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 0;
          wall_red = 0;
          third_choice_red = 1;
          variable_red = 2;
        }
      }
    }
  } else if (pacman_position_x > red_ghost_position_x && pacman_position_y < red_ghost_position_y) { // Ghost down left , pacman upper right
    if (priority_red == 0) {
      if (angle_red == 0 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          angle_red = 1;
        }
      } else if (angle_red == 0 && wall_red == 0 && exception_red == 1) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 1;
          exception_red = 0;
          variable_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 1;
          exception_red = 0;
          variable_red = 0;
        }
      } else if (angle_red == 0 && wall_red == 1 && exception_red == 0) { // when ghost is left and pacman right. Ghost moves down to avoid the wall_red
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          wall_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 1;
          wall_red = 0;
          third_choice_red = 1;
          variable_red = 3;
        }
      } else if (angle_red == 1 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          angle_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          angle_red = 0;
        }
      }
    } else if (priority_red == 1) {
      if (angle_red == 0 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          angle_red = 1;
        }
      } else if (angle_red == 0 && wall_red == 0 && exception_red == 1) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 0;
          exception_red = 0;
          variable_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 0;
          exception_red = 0;
          variable_red = 0;
        }
      } else if (angle_red == 0 && wall_red == 1 && exception_red == 0) { // when ghost is down and pacman up. Ghost moves left to avoid the wall_red
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          wall_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 0;
          wall_red = 0;
          third_choice_red = 1;
          variable_red = 1;
        }
      } else if (angle_red == 1 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          angle_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          angle_red = 0;
        }
      }
    }
  } else if (pacman_position_x < red_ghost_position_x && pacman_position_y > red_ghost_position_y) { // Ghost upper right , pacman down left
    if (priority_red == 0) {
      if (angle_red == 0 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 3)) {
          angle_red = 1;
        }
      } else if (angle_red == 1 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          angle_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          angle_red = 0;
        }
      } else if (angle_red == 0 && wall_red == 0 && exception_red == 1) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 1;
          exception_red = 0;
          variable_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 1;
          exception_red = 0;
          variable_red = 0;
        }
      }

      else if (angle_red == 0 && wall_red == 1 && exception_red == 0) { // when ghost is right and pacman left. Ghost moves up to avoid the wall_red
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          wall_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 1;
          wall_red = 0;
          third_choice_red = 1;
          variable_red = 4;
        }
      }
    } else if (priority_red == 1) {
      if (angle_red == 0 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 1)) {
          angle_red = 1;
        }
      } else if (angle_red == 0 && wall_red == 0 && exception_red == 1) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,3)) {
          RedGhostDirection = 3;
          red_ghost_position_y = red_ghost_position_y - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 0;
          exception_red = 0;
          variable_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          RedGhostDirection = 4;
          red_ghost_position_y = red_ghost_position_y + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 0;
          exception_red = 0;
          variable_red = 0;
        }
      } else if (angle_red == 1 && wall_red == 0 && exception_red == 0) {
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          angle_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          angle_red = 0;
        }
      } else if (angle_red == 0 && wall_red == 1 && exception_red == 0) { // when ghost is up and pacman down. Ghost moves right to avoid the wall_red
        if (CheckPosition(red_ghost_position_x, red_ghost_position_y,1)) {
          RedGhostDirection = 1;
          red_ghost_position_x = red_ghost_position_x + 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 4)) {
          wall_red = 0;
        } else if (CheckPosition(red_ghost_position_x,red_ghost_position_y, 2)) {
          RedGhostDirection = 2;
          red_ghost_position_x = red_ghost_position_x - 1;
          DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
          priority_red = 0;
          wall_red = 0;
          third_choice_red = 1;
          variable_red = 2;
        }
      }
    }
  } else if (pacman_position_x == red_ghost_position_x && pacman_position_y > red_ghost_position_y) { // Ghost up , pacman down
    if (wall_red == 0 && third_choice_red == 0) {
      if (CheckPosition(red_ghost_position_x, red_ghost_position_y, 4)) {
        RedGhostDirection = 4;
        red_ghost_position_y = red_ghost_position_y + 1;
        DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
      } else if (CheckPosition(red_ghost_position_x, red_ghost_position_y,1)) {
        RedGhostDirection = 1;
        red_ghost_position_x = red_ghost_position_x + 1;
        DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        priority_red = 1;
        wall_red = 1;
      } else if (CheckPosition(red_ghost_position_x, red_ghost_position_y,2)) {
        RedGhostDirection = 2;
        red_ghost_position_x = red_ghost_position_x - 1;
        DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        priority_red = 1;
        wall_red = 1;
      }
    } else if (wall_red == 0 && third_choice_red == 1 && variable_red == 2) {
      RedGhostDirection = 2;
      red_ghost_position_x = red_ghost_position_x - 1;
      DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
      third_choice_red = 0;
      exception_red = 1;
    } else if (wall_red == 0 && third_choice_red == 1 && variable_red == 1) {
      RedGhostDirection = 1;
      red_ghost_position_x = red_ghost_position_x + 1;
      DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
      third_choice_red = 0;
      exception_red = 1;
    }
  } else if (pacman_position_x == red_ghost_position_x && pacman_position_y < red_ghost_position_y) { // Ghost down , pacman up
    if (wall_red == 0 && third_choice_red == 0) {
      if (CheckPosition(red_ghost_position_x, red_ghost_position_y, 3)) {
        RedGhostDirection = 3;
        red_ghost_position_y = red_ghost_position_y - 1;
        DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
      } else if (CheckPosition(red_ghost_position_x, red_ghost_position_y,1)) {
        RedGhostDirection = 1;
        red_ghost_position_x = red_ghost_position_x + 1;
        DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        priority_red = 1;
        wall_red = 1;
      } else if (CheckPosition(red_ghost_position_x, red_ghost_position_y,2)) {
        RedGhostDirection = 2;
        red_ghost_position_x = red_ghost_position_x - 1;
        DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        priority_red = 1;
        wall_red = 1;
      }
    } else if (wall_red == 0 && third_choice_red == 1 && variable_red == 2) {
      RedGhostDirection = 2;
      red_ghost_position_x = red_ghost_position_x - 1;
      DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
      third_choice_red = 0;
      exception_red = 1;
    } else if (wall_red == 0 && third_choice_red == 1 && variable_red == 1) {
      RedGhostDirection = 1;
      red_ghost_position_x = red_ghost_position_x + 1;
      DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
      third_choice_red = 0;
      exception_red = 1;
    }
  } else if (pacman_position_x > red_ghost_position_x && pacman_position_y == red_ghost_position_y) { // Ghost left , pacman right
    if (wall_red == 0 && third_choice_red == 0) {
      if (CheckPosition(red_ghost_position_x, red_ghost_position_y, 1)) {
        RedGhostDirection = 1;
        red_ghost_position_x = red_ghost_position_x + 1;
        DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
      } else if (CheckPosition(red_ghost_position_x, red_ghost_position_y,3)) {
        RedGhostDirection = 3;
        red_ghost_position_y = red_ghost_position_y - 1;
        DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        priority_red = 0;
        wall_red = 1;
      } else if (CheckPosition(red_ghost_position_x, red_ghost_position_y,4)) {
        RedGhostDirection = 4;
        red_ghost_position_y = red_ghost_position_y + 1;
        DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        priority_red = 0;
        wall_red = 1;
      }
    } else if (wall_red == 0 && third_choice_red == 1 && variable_red == 4) {
      RedGhostDirection = 4;
      red_ghost_position_y = red_ghost_position_y + 1;
      DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
      third_choice_red = 0;
      exception_red = 1;
    } else if (wall_red == 0 && third_choice_red == 1 && variable_red == 3) {
      RedGhostDirection = 3;
      red_ghost_position_y = red_ghost_position_y - 1;
      DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
      third_choice_red = 0;
      exception_red = 1;
    }
  } else if (pacman_position_x < red_ghost_position_x && pacman_position_y == red_ghost_position_y) { // Ghost right , pacman left
    if (wall_red == 0 && third_choice_red == 0) {
      if (CheckPosition(red_ghost_position_x, red_ghost_position_y, 2)) {
        RedGhostDirection = 2;
        red_ghost_position_x = red_ghost_position_x - 1;
        DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
      } else if (CheckPosition(red_ghost_position_x, red_ghost_position_y,3)) {
        RedGhostDirection = 3;
        red_ghost_position_y = red_ghost_position_y - 1;
        DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        priority_red = 0;
        wall_red = 1;
      } else if (CheckPosition(red_ghost_position_x, red_ghost_position_y,4)) {
        RedGhostDirection = 4;
        red_ghost_position_y = red_ghost_position_y + 1;
        DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
        priority_red = 0;
        wall_red = 1;
      }
    } else if (wall_red == 0 && third_choice_red == 1 && variable_red == 4) {
      RedGhostDirection = 4;
      red_ghost_position_y = red_ghost_position_y + 1;
      DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
      third_choice_red = 0;
      exception_red = 1;
    } else if (wall_red == 0 && third_choice_red == 1 && variable_red == 3) {
      RedGhostDirection = 3;
      red_ghost_position_y = red_ghost_position_y - 1;
      DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
      third_choice_red = 0;
      exception_red = 1;
    }
  }

}

void MovePinkGhost() {

  TaskStartPinkGhost.disable();

  AvoidFood(pink_ghost_position_x, pink_ghost_position_y, PinkGhostDirection);

  if ((pacman_position_x == pink_ghost_position_x
      || pacman_position_x == pink_ghost_position_x + 1
      || pacman_position_x == pink_ghost_position_x + 2
      || pacman_position_x == pink_ghost_position_x + 3
      || pacman_position_x == pink_ghost_position_x + 4
      || pacman_position_x == pink_ghost_position_x + 5
      || pacman_position_x == pink_ghost_position_x + 6
      || pacman_position_x == pink_ghost_position_x + 7
      || pacman_position_x == pink_ghost_position_x + 8
      || pacman_position_x == pink_ghost_position_x - 1
      || pacman_position_x == pink_ghost_position_x - 2
      || pacman_position_x == pink_ghost_position_x - 3
      || pacman_position_x == pink_ghost_position_x - 4
      || pacman_position_x == pink_ghost_position_x - 5
      || pacman_position_x == pink_ghost_position_x - 6
      || pacman_position_x == pink_ghost_position_x - 7
      || pacman_position_x == pink_ghost_position_x - 8)
      && (pacman_position_y == pink_ghost_position_y
          || pacman_position_y == pink_ghost_position_y + 1
          || pacman_position_y == pink_ghost_position_y + 2
          || pacman_position_y == pink_ghost_position_y + 3
          || pacman_position_y == pink_ghost_position_y + 4
          || pacman_position_y == pink_ghost_position_y + 5
          || pacman_position_y == pink_ghost_position_y + 6
          || pacman_position_y == pink_ghost_position_y + 7
          || pacman_position_y == pink_ghost_position_y + 8
          || pacman_position_y == pink_ghost_position_y - 1
          || pacman_position_y == pink_ghost_position_y - 2
          || pacman_position_y == pink_ghost_position_y - 3
          || pacman_position_y == pink_ghost_position_y - 4
          || pacman_position_y == pink_ghost_position_y - 5
          || pacman_position_y == pink_ghost_position_y - 6
          || pacman_position_y == pink_ghost_position_y - 7
          || pacman_position_y == pink_ghost_position_y - 8)) // Pink Ghost catches pacman
      {
    lives = lives - 1;
    StartOver();
  }

  if (pacman_position_x > pink_ghost_position_x && pacman_position_y > pink_ghost_position_y) { // Ghost upper left , pacman down right
    if (priority_pink == 0) {
      if (angle_pink == 0 && wall_pink == 0 && exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
          angle_pink = 1;
        }
      } else if (angle_pink == 0 && wall_pink == 0 && exception_pink == 1) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 1;
          exception_pink = 0;
          variable_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 1;
          exception_pink = 0;
          variable_pink = 0;
        }
      } else if (angle_pink == 1 && wall_pink == 0 && exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
          angle_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          angle_pink = 0;
        }
      } else if (angle_pink == 0 && wall_pink == 1 && exception_pink == 0) { // when ghost is left and pacman right. Ghost moves up to avoid the wall_pink
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
          wall_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 1;
          wall_pink = 0;
          third_choice_pink = 1;
          variable_pink = 4;
        }
      }
    } else if (priority_pink == 1) {
      if (angle_pink == 0 && wall_pink == 0 && exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          angle_pink = 1;
        }
      } else if (angle_pink == 0 && wall_pink == 0 && exception_pink == 1) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 0;
          exception_pink = 0;
          variable_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 0;
          exception_pink = 0;
          variable_pink = 0;
        }
      } else if (angle_pink == 1 && wall_pink == 0 && exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          angle_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
          angle_pink = 0;
        }
      } else if (angle_pink == 0 && wall_pink == 1 && exception_pink == 0) { // when ghost is up and pacman down. Ghost moves left to avoid the wall_pink
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          wall_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 0;
          wall_pink = 0;
          third_choice_pink = 1;
          variable_pink = 1;
        }
      }
    }
  } else if (pacman_position_x < pink_ghost_position_x && pacman_position_y < pink_ghost_position_y) { // Ghost down right , pacman upper left
    if (priority_pink == 0) {
      if (angle_pink == 0 && wall_pink == 0 && exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          angle_pink = 1;
        }
      } else if (angle_pink == 0 && wall_pink == 0 && exception_pink == 1) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 1;
          exception_pink = 0;
          variable_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 1;
          exception_pink = 0;
          variable_pink = 0;
        }
      } else if (angle_pink == 0 && wall_pink == 1 && exception_pink == 0) { // when ghost is right and pacman left. Ghost moves down to avoid the wall_pink
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          wall_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 1;
          wall_pink = 0;
          third_choice_pink = 1;
          variable_pink = 3;
        }
      } else if (angle_pink == 1 && wall_pink == 0&& exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          angle_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
          angle_pink = 0;
        }
      }
    } else if (priority_pink == 1) {
      if (angle_pink == 0 && wall_pink == 0 && exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
          angle_pink = 1;
        }
      } else if (angle_pink == 0 && wall_pink == 0 && exception_pink == 1) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 0;
          exception_pink = 0;
          variable_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 0;
          exception_pink = 0;
          variable_pink = 0;
        }
      } else if (angle_pink == 1 && wall_pink == 0 && exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
          angle_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          angle_pink = 0;
        }
      } else if (angle_pink == 0 && wall_pink == 1 && exception_pink == 0) { // when ghost is down and pacman up. Ghost moves right to avoid the wall_pink
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
          wall_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 0;
          wall_pink = 0;
          third_choice_pink = 1;
          variable_pink = 2;
        }
      }
    }
  } else if (pacman_position_x > pink_ghost_position_x && pacman_position_y < pink_ghost_position_y) { // Ghost down left , pacman upper right
    if (priority_pink == 0) {
      if (angle_pink == 0 && wall_pink == 0 && exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          angle_pink = 1;
        }
      } else if (angle_pink == 0 && wall_pink == 0 && exception_pink == 1) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 1;
          exception_pink = 0;
          variable_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 1;
          exception_pink = 0;
          variable_pink = 0;
        }
      } else if (angle_pink == 0 && wall_pink == 1 && exception_pink == 0) { // when ghost is left and pacman right. Ghost moves down to avoid the wall_pink
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
          wall_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 1;
          wall_pink = 0;
          third_choice_pink = 1;
          variable_pink = 3;
        }
      } else if (angle_pink == 1 && wall_pink == 0 && exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
          angle_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
          angle_pink = 0;
        }
      }
    } else if (priority_pink == 1) {
      if (angle_pink == 0 && wall_pink == 0 && exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          angle_pink = 1;
        }
      } else if (angle_pink == 0 && wall_pink == 0 && exception_pink == 1) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 0;
          exception_pink = 0;
          variable_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 0;
          exception_pink = 0;
          variable_pink = 0;
        }
      } else if (angle_pink == 0 && wall_pink == 1 && exception_pink == 0) { // when ghost is down and pacman up. Ghost moves left to avoid the wall_pink
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y, 3)) {
          wall_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y, 1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 0;
          wall_pink = 0;
          third_choice_pink = 1;
          variable_pink = 1;
        }
      } else if (angle_pink == 1 && wall_pink == 0 && exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
          angle_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
          angle_pink = 0;
        }
      }
    }
  } else if (pacman_position_x < pink_ghost_position_x && pacman_position_y > pink_ghost_position_y) { // Ghost upper right , pacman down left
    if (priority_pink == 0) {
      if (angle_pink == 0 && wall_pink == 0 && exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
          angle_pink = 1;
        }
      } else if (angle_pink == 1 && wall_pink == 0 && exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          angle_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          angle_pink = 0;
        }
      } else if (angle_pink == 0 && wall_pink == 0 && exception_pink == 1) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 1;
          exception_pink = 0;
          variable_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 1;
          exception_pink = 0;
          variable_pink = 0;
        }
      }

      else if (angle_pink == 0 && wall_pink == 1 && exception_pink == 0) { // when ghost is right and pacman left. Ghost moves up to avoid the wall_pink
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          wall_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 1;
          wall_pink = 0;
          third_choice_pink = 1;
          variable_pink = 4;
        }
      }
    } else if (priority_pink == 1) {
      if (angle_pink == 0 && wall_pink == 0 && exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
          angle_pink = 1;
        }
      } else if (angle_pink == 0 && wall_pink == 0 && exception_pink == 1) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,3)) {
          PinkGhostDirection = 3;
          pink_ghost_position_y = pink_ghost_position_y - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 0;
          exception_pink = 0;
          variable_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          PinkGhostDirection = 4;
          pink_ghost_position_y = pink_ghost_position_y + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 0;
          exception_pink = 0;
          variable_pink = 0;
        }
      } else if (angle_pink == 1 && wall_pink == 0 && exception_pink == 0) {
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          angle_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          angle_pink = 0;
        }
      } else if (angle_pink == 0 && wall_pink == 1 && exception_pink == 0) { // when ghost is up and pacman down. Ghost moves right to avoid the wall_pink
        if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,1)) {
          PinkGhostDirection = 1;
          pink_ghost_position_x = pink_ghost_position_x + 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
          wall_pink = 0;
        } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
          PinkGhostDirection = 2;
          pink_ghost_position_x = pink_ghost_position_x - 1;
          DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
          priority_pink = 0;
          wall_pink = 0;
          third_choice_pink = 1;
          variable_pink = 2;
        }
      }
    }
  } else if (pacman_position_x == pink_ghost_position_x && pacman_position_y > pink_ghost_position_y) { // Ghost up , pacman down
    if (wall_pink == 0 && third_choice_pink == 0) {
      if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,4)) {
        PinkGhostDirection = 4;
        pink_ghost_position_y = pink_ghost_position_y + 1;
        DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
      } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
        PinkGhostDirection = 1;
        pink_ghost_position_x = pink_ghost_position_x + 1;
        DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        priority_pink = 1;
        wall_pink = 1;
      } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
        PinkGhostDirection = 2;
        pink_ghost_position_x = pink_ghost_position_x - 1;
        DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        priority_pink = 1;
        wall_pink = 1;
      }
    } else if (wall_pink == 0 && third_choice_pink == 1 && variable_pink == 2) {
      PinkGhostDirection = 2;
      pink_ghost_position_x = pink_ghost_position_x - 1;
      DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
      third_choice_pink = 0;
      exception_pink = 1;
    } else if (wall_pink == 0 && third_choice_pink == 1 && variable_pink == 1) {
      PinkGhostDirection = 1;
      pink_ghost_position_x = pink_ghost_position_x + 1;
      DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
      third_choice_pink = 0;
      exception_pink = 1;
    }
  } else if (pacman_position_x == pink_ghost_position_x && pacman_position_y < pink_ghost_position_y) { // Ghost down , pacman up
    if (wall_pink == 0 && third_choice_pink == 0) {
      if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,3)) {
        PinkGhostDirection = 3;
        pink_ghost_position_y = pink_ghost_position_y - 1;
        DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
      } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 1)) {
        PinkGhostDirection = 1;
        pink_ghost_position_x = pink_ghost_position_x + 1;
        DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        priority_pink = 1;
        wall_pink = 1;
      } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 2)) {
        PinkGhostDirection = 2;
        pink_ghost_position_x = pink_ghost_position_x - 1;
        DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        priority_pink = 1;
        wall_pink = 1;
      }
    } else if (wall_pink == 0 && third_choice_pink == 1 && variable_pink == 2) {
      PinkGhostDirection = 2;
      pink_ghost_position_x = pink_ghost_position_x - 1;
      DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
      third_choice_pink = 0;
      exception_pink = 1;
    } else if (wall_pink == 0 && third_choice_pink == 1 && variable_pink == 1) {
      PinkGhostDirection = 1;
      pink_ghost_position_x = pink_ghost_position_x + 1;
      DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
      third_choice_pink = 0;
      exception_pink = 1;
    }
  } else if (pacman_position_x > pink_ghost_position_x && pacman_position_y == pink_ghost_position_y) { // Ghost left , pacman right
    if (wall_pink == 0 && third_choice_pink == 0) {
      if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,1)) {
        PinkGhostDirection = 1;
        pink_ghost_position_x = pink_ghost_position_x + 1;
        DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
      } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
        PinkGhostDirection = 3;
        pink_ghost_position_y = pink_ghost_position_y - 1;
        DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        priority_pink = 0;
        wall_pink = 1;
      } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
        PinkGhostDirection = 4;
        pink_ghost_position_y = pink_ghost_position_y + 1;
        DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        priority_pink = 0;
        wall_pink = 1;
      }
    } else if (wall_pink == 0 && third_choice_pink == 1 && variable_pink == 4) {
      PinkGhostDirection = 4;
      pink_ghost_position_y = pink_ghost_position_y + 1;
      DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
      third_choice_pink = 0;
      exception_pink = 1;
    } else if (wall_pink == 0 && third_choice_pink == 1 && variable_pink == 3) {
      PinkGhostDirection = 3;
      pink_ghost_position_y = pink_ghost_position_y - 1;
      DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
      third_choice_pink = 0;
      exception_pink = 1;
    }
  } else if (pacman_position_x < pink_ghost_position_x && pacman_position_y == pink_ghost_position_y) { // Ghost right , pacman left
    if (wall_pink == 0 && third_choice_pink == 0) {
      if (CheckPosition(pink_ghost_position_x, pink_ghost_position_y,2)) {
        PinkGhostDirection = 2;
        pink_ghost_position_x = pink_ghost_position_x - 1;
        DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
      } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 3)) {
        PinkGhostDirection = 3;
        pink_ghost_position_y = pink_ghost_position_y - 1;
        DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        priority_pink = 0;
        wall_pink = 1;
      } else if (CheckPosition(pink_ghost_position_x,pink_ghost_position_y, 4)) {
        PinkGhostDirection = 4;
        pink_ghost_position_y = pink_ghost_position_y + 1;
        DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
        priority_pink = 0;
        wall_pink = 1;
      }
    } else if (wall_pink == 0 && third_choice_pink == 1 && variable_pink == 4) {
      PinkGhostDirection = 4;
      pink_ghost_position_y = pink_ghost_position_y + 1;
      DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
      third_choice_pink = 0;
      exception_pink = 1;
    } else if (wall_pink == 0 && third_choice_pink == 1 && variable_pink == 3) {
      PinkGhostDirection = 3;
      pink_ghost_position_y = pink_ghost_position_y - 1;
      DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
      third_choice_pink = 0;
      exception_pink = 1;
    }
  }

}

void MoveBlueGhost() {

  TaskStartBlueGhost.disable();

  AvoidFood(blue_ghost_position_x, blue_ghost_position_y, BlueGhostDirection);

  if ((pacman_position_x == blue_ghost_position_x
      || pacman_position_x == blue_ghost_position_x + 1
      || pacman_position_x == blue_ghost_position_x + 2
      || pacman_position_x == blue_ghost_position_x + 3
      || pacman_position_x == blue_ghost_position_x + 4
      || pacman_position_x == blue_ghost_position_x + 5
      || pacman_position_x == blue_ghost_position_x + 6
      || pacman_position_x == blue_ghost_position_x + 7
      || pacman_position_x == blue_ghost_position_x + 8
      || pacman_position_x == blue_ghost_position_x - 1
      || pacman_position_x == blue_ghost_position_x - 2
      || pacman_position_x == blue_ghost_position_x - 3
      || pacman_position_x == blue_ghost_position_x - 4
      || pacman_position_x == blue_ghost_position_x - 5
      || pacman_position_x == blue_ghost_position_x - 6
      || pacman_position_x == blue_ghost_position_x - 7
      || pacman_position_x == blue_ghost_position_x - 8)
      && (pacman_position_y == blue_ghost_position_y
          || pacman_position_y == blue_ghost_position_y + 1
          || pacman_position_y == blue_ghost_position_y + 2
          || pacman_position_y == blue_ghost_position_y + 3
          || pacman_position_y == blue_ghost_position_y + 4
          || pacman_position_y == blue_ghost_position_y + 5
          || pacman_position_y == blue_ghost_position_y + 6
          || pacman_position_y == blue_ghost_position_y + 7
          || pacman_position_y == blue_ghost_position_y + 8
          || pacman_position_y == blue_ghost_position_y - 1
          || pacman_position_y == blue_ghost_position_y - 2
          || pacman_position_y == blue_ghost_position_y - 3
          || pacman_position_y == blue_ghost_position_y - 4
          || pacman_position_y == blue_ghost_position_y - 5
          || pacman_position_y == blue_ghost_position_y - 6
          || pacman_position_y == blue_ghost_position_y - 7
          || pacman_position_y == blue_ghost_position_y - 8)) // Blue Ghost catches pacman
      {
    lives = lives - 1;
    StartOver();
  }

  if (priority_blue == 0) {

    if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y, 3)) {
      BlueGhostDirection = 3;
      blue_ghost_position_y = blue_ghost_position_y - 1;
      DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
    } else if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y,2)) {
      BlueGhostDirection = 2;
      blue_ghost_position_x = blue_ghost_position_x - 1;
      DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
    } else if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y,4)) {
      priority_blue = 1;
    }

  }

  else if (priority_blue == 1) {

    if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y, 4)) {
      BlueGhostDirection = 4;
      blue_ghost_position_y = blue_ghost_position_y + 1;
      DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
    } else if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y,1)) {
      BlueGhostDirection = 1;
      blue_ghost_position_x = blue_ghost_position_x + 1;
      DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
    } else if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y,2)) {
      priority_blue = 2;
    }
  }

  else if (priority_blue == 2) {

    if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y, 2)) {
      BlueGhostDirection = 2;
      blue_ghost_position_x = blue_ghost_position_x - 1;
      DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
    } else if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y,4)) {
      BlueGhostDirection = 4;
      blue_ghost_position_y = blue_ghost_position_y + 1;
      DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
    } else if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y,1)) {
      priority_blue = 3;
    }
  }

  else if (priority_blue == 3) {

    if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y, 1)) {
      BlueGhostDirection = 1;
      blue_ghost_position_x = blue_ghost_position_x + 1;
      DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
    } else if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y,3)) {
      BlueGhostDirection = 3;
      blue_ghost_position_y = blue_ghost_position_y - 1;
      DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
    } else if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y,2)) {
      priority_blue = 4;
    }
  }

  else if (priority_blue == 4) {

    if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y, 2)) {
      BlueGhostDirection = 2;
      blue_ghost_position_x = blue_ghost_position_x - 1;
      DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
    } else if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y,3)) {
      BlueGhostDirection = 3;
      blue_ghost_position_y = blue_ghost_position_y - 1;
      DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
    } else if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y,1)) {
      priority_blue = 5;
    }
  }

  else if (priority_blue == 5) {

    if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y, 3)) {
      BlueGhostDirection = 3;
      blue_ghost_position_y = blue_ghost_position_y - 1;
      DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
    } else if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y,1)) {
      BlueGhostDirection = 1;
      blue_ghost_position_x = blue_ghost_position_x + 1;
      DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
    } else if (CheckPosition(blue_ghost_position_x, blue_ghost_position_y,2)) {
      priority_blue = 0;
    }
  }

}

void MoveOrangeGhost() {

  TaskStartOrangeGhost.disable();

  AvoidFood(orange_ghost_position_x, orange_ghost_position_y,
      OrangeGhostDirection);

  if ((pacman_position_x == orange_ghost_position_x
      || pacman_position_x == orange_ghost_position_x + 1
      || pacman_position_x == orange_ghost_position_x + 2
      || pacman_position_x == orange_ghost_position_x + 3
      || pacman_position_x == orange_ghost_position_x + 4
      || pacman_position_x == orange_ghost_position_x + 5
      || pacman_position_x == orange_ghost_position_x + 6
      || pacman_position_x == orange_ghost_position_x + 7
      || pacman_position_x == orange_ghost_position_x + 8
      || pacman_position_x == orange_ghost_position_x - 1
      || pacman_position_x == orange_ghost_position_x - 2
      || pacman_position_x == orange_ghost_position_x - 3
      || pacman_position_x == orange_ghost_position_x - 4
      || pacman_position_x == orange_ghost_position_x - 5
      || pacman_position_x == orange_ghost_position_x - 6
      || pacman_position_x == orange_ghost_position_x - 7
      || pacman_position_x == orange_ghost_position_x - 8)
      && (pacman_position_y == orange_ghost_position_y
          || pacman_position_y == orange_ghost_position_y + 1
          || pacman_position_y == orange_ghost_position_y + 2
          || pacman_position_y == orange_ghost_position_y + 3
          || pacman_position_y == orange_ghost_position_y + 4
          || pacman_position_y == orange_ghost_position_y + 5
          || pacman_position_y == orange_ghost_position_y + 6
          || pacman_position_y == orange_ghost_position_y + 7
          || pacman_position_y == orange_ghost_position_y + 8
          || pacman_position_y == orange_ghost_position_y - 1
          || pacman_position_y == orange_ghost_position_y - 2
          || pacman_position_y == orange_ghost_position_y - 3
          || pacman_position_y == orange_ghost_position_y - 4
          || pacman_position_y == orange_ghost_position_y - 5
          || pacman_position_y == orange_ghost_position_y - 6
          || pacman_position_y == orange_ghost_position_y - 7
          || pacman_position_y == orange_ghost_position_y - 8)) // Orange Ghost catches pacman
      {
    lives = lives - 1;
    StartOver();
  }

  if (priority_orange == 0) {

    if (CheckPosition(orange_ghost_position_x, orange_ghost_position_y,3)) {
      OrangeGhostDirection = 3;
      orange_ghost_position_y = orange_ghost_position_y - 1;
      DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);
    } else if (CheckPosition(orange_ghost_position_x,orange_ghost_position_y, 1)) {
      OrangeGhostDirection = 1;
      orange_ghost_position_x = orange_ghost_position_x + 1;
      DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);
    } else if (CheckPosition(orange_ghost_position_x,orange_ghost_position_y, 2)) {
      priority_orange = 1;
    }
  }

  else if (priority_orange == 1) {

    if (CheckPosition(orange_ghost_position_x, orange_ghost_position_y,4)) {
      OrangeGhostDirection = 4;
      orange_ghost_position_y = orange_ghost_position_y + 1;
      DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);
    } else if (CheckPosition(orange_ghost_position_x,orange_ghost_position_y, 2)) {
      OrangeGhostDirection = 2;
      orange_ghost_position_x = orange_ghost_position_x - 1;
      DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);
    } else if (CheckPosition(orange_ghost_position_x,orange_ghost_position_y, 1)) {
      priority_orange = 2;
    }
  }

  else if (priority_orange == 2) {

    if (CheckPosition(orange_ghost_position_x, orange_ghost_position_y,1)) {
      OrangeGhostDirection = 1;
      orange_ghost_position_x = orange_ghost_position_x + 1;
      DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);
    } else if (CheckPosition(orange_ghost_position_x,orange_ghost_position_y, 4)) {
      OrangeGhostDirection = 4;
      orange_ghost_position_y = orange_ghost_position_y + 1;
      DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);
    } else if (CheckPosition(orange_ghost_position_x,orange_ghost_position_y, 2)) {
      priority_orange = 3;
    }
  }

  else if (priority_orange == 3) {

    if (CheckPosition(orange_ghost_position_x, orange_ghost_position_y,2)) {
      OrangeGhostDirection = 2;
      orange_ghost_position_x = orange_ghost_position_x - 1;
      DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);
    } else if (CheckPosition(orange_ghost_position_x,orange_ghost_position_y, 3)) {
      OrangeGhostDirection = 3;
      orange_ghost_position_y = orange_ghost_position_y - 1;
      DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);
    } else if (CheckPosition(orange_ghost_position_x,orange_ghost_position_y, 1)) {
      priority_orange = 4;
    }
  }

  else if (priority_orange == 4) {

    if (CheckPosition(orange_ghost_position_x, orange_ghost_position_y,1)) {
      OrangeGhostDirection = 1;
      orange_ghost_position_x = orange_ghost_position_x + 1;
      DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);
    } else if (CheckPosition(orange_ghost_position_x,orange_ghost_position_y, 3)) {
      OrangeGhostDirection = 3;
      orange_ghost_position_y = orange_ghost_position_y - 1;
      DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);
    } else if (CheckPosition(orange_ghost_position_x,orange_ghost_position_y, 2)) {
      priority_orange = 5;
    }
  }

  else if (priority_orange == 5) {

    if (CheckPosition(orange_ghost_position_x, orange_ghost_position_y,3)) {
      OrangeGhostDirection = 3;
      orange_ghost_position_y = orange_ghost_position_y - 1;
      DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);
    } else if (CheckPosition(orange_ghost_position_x,orange_ghost_position_y, 2)) {
      OrangeGhostDirection = 2;
      orange_ghost_position_x = orange_ghost_position_x - 1;
      DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);
    } else if (CheckPosition(orange_ghost_position_x,orange_ghost_position_y, 1)) {
      priority_orange = 0;
    }
  }

}

int CheckPosition(int x, int y, int Direction) {
  if (Direction == 1) {  // check when moving right
    int temp_position = x + 10;
    if (y >= 1 && y <= 60 && temp_position >= 1 + 40 && temp_position <= 60 + 40) { // board11
      for (int i = 0; i < 689; i++) {
        int board_x = pgm_read_byte(&(board11[1][i])) + 40;
        int board_y = pgm_read_byte(&(board11[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 61 && y <= 120 && temp_position >= 1 + 40 && temp_position <= 60 + 40) { // board21
      for (int i = 0; i < 604; i++) {
        int board_x = pgm_read_byte(&(board21[1][i])) + 40;
        int board_y = pgm_read_byte(&(board21[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 121 && y <= 180 && temp_position >= 1 + 40 && temp_position <= 60 + 40) { // board31
      for (int i = 0; i < 662; i++) {
        int board_x = pgm_read_byte(&(board31[1][i])) + 40;
        int board_y = pgm_read_byte(&(board31[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 181 && y <= 240 && temp_position >= 1 + 40 && temp_position <= 60 + 40) { // board41
      for (int i = 0; i < 728; i++) {
        int board_x = pgm_read_byte(&(board41[1][i])) + 40;
        int board_y = pgm_read_byte(&(board41[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 1 && y <= 60 && temp_position >= 61 + 40 && temp_position <= 120 + 40) { // board12
      for (int i = 0; i < 602; i++) {
        int board_x = pgm_read_byte(&(board12[1][i])) + 40;
        int board_y = pgm_read_byte(&(board12[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 61 && y <= 120 && temp_position >= 61 + 40 && temp_position <= 120 + 40) { // board22
      for (int i = 0; i < 504; i++) {
        int board_x = pgm_read_byte(&(board22[1][i])) + 40;
        int board_y = pgm_read_byte(&(board22[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 121 && y <= 180 && temp_position >= 61 + 40 && temp_position <= 120 + 40) { // board32
      for (int i = 0; i < 578; i++) {
        int board_x = pgm_read_byte(&(board32[1][i])) + 40;
        int board_y = pgm_read_byte(&(board32[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 181 && y <= 240 && temp_position >= 61 + 40 && temp_position <= 120 + 40) { // board42
      for (int i = 0; i < 660; i++) {
        int board_x = pgm_read_byte(&(board42[1][i])) + 40;
        int board_y = pgm_read_byte(&(board42[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 1 && y <= 60 && temp_position >= 121 + 40 && temp_position <= 180 + 40) { // board13
      for (int i = 0; i < 604; i++) {
        int board_x = pgm_read_byte(&(board13[1][i])) + 40;
        int board_y = pgm_read_byte(&(board13[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 61 && y <= 120 && temp_position >= 121 + 40 && temp_position <= 180 + 40) { // board23
      for (int i = 0; i < 512; i++) {
        int board_x = pgm_read_byte(&(board23[1][i])) + 40;
        int board_y = pgm_read_byte(&(board23[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 121 && y <= 180 && temp_position >= 121 + 40 && temp_position <= 180 + 40) { // board33
      for (int i = 0; i < 590; i++) {
        int board_x = pgm_read_byte(&(board33[1][i])) + 40;
        int board_y = pgm_read_byte(&(board33[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 181 && y <= 240 && temp_position >= 121 + 40 && temp_position <= 180 + 40) { // board43
      for (int i = 0; i < 664; i++) {
        int board_x = pgm_read_byte(&(board43[1][i])) + 40;
        int board_y = pgm_read_byte(&(board43[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 1 && y <= 60 && temp_position >= 181 + 40 && temp_position <= 240 + 40) { // board14
      for (int i = 0; i < 693; i++) {
        int board_x = pgm_read_byte(&(board14[1][i])) + 40;
        int board_y = pgm_read_byte(&(board14[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 61 && y <= 120 && temp_position >= 181 + 40 && temp_position <= 240 + 40) { // board24
      for (int i = 0; i < 604; i++) {
        int board_x = pgm_read_byte(&(board24[1][i])) + 40;
        int board_y = pgm_read_byte(&(board24[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 121 && y <= 180 && temp_position >= 181 + 40 && temp_position <= 240 + 40) { // board34
      for (int i = 0; i < 662; i++) {
        int board_x = pgm_read_byte(&(board34[1][i])) + 40;
        int board_y = pgm_read_byte(&(board34[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 181 && y <= 240 && temp_position >= 181 + 40 && temp_position <= 240 + 40) { // board44
      for (int i = 0; i < 732; i++) {
        int board_x = pgm_read_byte(&(board44[1][i])) + 40;
        int board_y = pgm_read_byte(&(board44[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    }
  } else if (Direction == 2) { // check when moving left
    int temp_position = x - 1;
    if (y >= 1 && y <= 60 && temp_position >= 1 + 40 && temp_position <= 60 + 40) { // board11
      for (int i = 0; i < 689; i++) {
        int board_x = pgm_read_byte(&(board11[1][i])) + 40;
        int board_y = pgm_read_byte(&(board11[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 61 && y <= 120 && temp_position >= 1 + 40 && temp_position <= 60 + 40) { // board21
      for (int i = 0; i < 604; i++) {
        int board_x = pgm_read_byte(&(board21[1][i])) + 40;
        int board_y = pgm_read_byte(&(board21[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 121 && y <= 180 && temp_position >= 1 + 40 && temp_position <= 60 + 40) { // board31
      for (int i = 0; i < 662; i++) {
        int board_x = pgm_read_byte(&(board31[1][i])) + 40;
        int board_y = pgm_read_byte(&(board31[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 181 && y <= 240 && temp_position >= 1 + 40 && temp_position <= 60 + 40) { // board41
      for (int i = 0; i < 728; i++) {
        int board_x = pgm_read_byte(&(board41[1][i])) + 40;
        int board_y = pgm_read_byte(&(board41[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 1 && y <= 60 && temp_position >= 61 + 40 && temp_position <= 120 + 40) { // board12
      for (int i = 0; i < 602; i++) {
        int board_x = pgm_read_byte(&(board12[1][i])) + 40;
        int board_y = pgm_read_byte(&(board12[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 61 && y <= 120 && temp_position >= 61 + 40 && temp_position <= 120 + 40) { // board22
      for (int i = 0; i < 504; i++) {
        int board_x = pgm_read_byte(&(board22[1][i])) + 40;
        int board_y = pgm_read_byte(&(board22[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 121 && y <= 180 && temp_position >= 61 + 40 && temp_position <= 120 + 40) { // board32
      for (int i = 0; i < 578; i++) {
        int board_x = pgm_read_byte(&(board32[1][i])) + 40;
        int board_y = pgm_read_byte(&(board32[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 181 && y <= 240 && temp_position >= 61 + 40 && temp_position <= 120 + 40) { // board42
      for (int i = 0; i < 660; i++) {
        int board_x = pgm_read_byte(&(board42[1][i])) + 40;
        int board_y = pgm_read_byte(&(board42[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 1 && y <= 60 && temp_position >= 121 + 40 && temp_position <= 180 + 40) { // board13
      for (int i = 0; i < 604; i++) {
        int board_x = pgm_read_byte(&(board13[1][i])) + 40;
        int board_y = pgm_read_byte(&(board13[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 61 && y <= 120 && temp_position >= 121 + 40 && temp_position <= 180 + 40) { // board23
      for (int i = 0; i < 512; i++) {
        int board_x = pgm_read_byte(&(board23[1][i])) + 40;
        int board_y = pgm_read_byte(&(board23[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 121 && y <= 180 && temp_position >= 121 + 40 && temp_position <= 180 + 40) { // board33
      for (int i = 0; i < 590; i++) {
        int board_x = pgm_read_byte(&(board33[1][i])) + 40;
        int board_y = pgm_read_byte(&(board33[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 181 && y <= 240 && temp_position >= 121 + 40 && temp_position <= 180 + 40) { // board43
      for (int i = 0; i < 664; i++) {
        int board_x = pgm_read_byte(&(board43[1][i])) + 40;
        int board_y = pgm_read_byte(&(board43[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 1 && y <= 60 && temp_position >= 181 + 40 && temp_position <= 240 + 40) { // board14
      for (int i = 0; i < 693; i++) {
        int board_x = pgm_read_byte(&(board14[1][i])) + 40;
        int board_y = pgm_read_byte(&(board14[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 61 && y <= 120 && temp_position >= 181 + 40 && temp_position <= 240 + 40) { // board24
      for (int i = 0; i < 604; i++) {
        int board_x = pgm_read_byte(&(board24[1][i])) + 40;
        int board_y = pgm_read_byte(&(board24[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 121 && y <= 180 && temp_position >= 181 + 40 && temp_position <= 240 + 40) { // board34
      for (int i = 0; i < 662; i++) {
        int board_x = pgm_read_byte(&(board34[1][i])) + 40;
        int board_y = pgm_read_byte(&(board34[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    } else if (y >= 181 && y <= 240 && temp_position >= 181 + 40 && temp_position <= 240 + 40) { // board44
      for (int i = 0; i < 732; i++) {
        int board_x = pgm_read_byte(&(board44[1][i])) + 40;
        int board_y = pgm_read_byte(&(board44[0][i]));
        if (temp_position == board_x
            && (y == board_y || y + 1 == board_y || y + 2 == board_y
                || y + 3 == board_y || y + 4 == board_y
                || y + 5 == board_y || y + 6 == board_y
                || y + 7 == board_y || y + 8 == board_y
                || y + 9 == board_y))
          return 0;
      }
    }
  } else if (Direction == 3) { // check when moving up
    int temp_position = y - 1;
    if (temp_position >= 1 && temp_position <= 60 && x >= 1 + 40 && x <= 60 + 40) { // board11
      for (int i = 0; i < 689; i++) {
        int board_x = pgm_read_byte(&(board11[1][i])) + 40;
        int board_y = pgm_read_byte(&(board11[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 61 && temp_position <= 120 && x >= 1 + 40 && x <= 60 + 40) { // board21
      for (int i = 0; i < 604; i++) {
        int board_x = pgm_read_byte(&(board21[1][i])) + 40;
        int board_y = pgm_read_byte(&(board21[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 121 && temp_position <= 180 && x >= 1 + 40 && x <= 60 + 40) { // board31
      for (int i = 0; i < 662; i++) {
        int board_x = pgm_read_byte(&(board31[1][i])) + 40;
        int board_y = pgm_read_byte(&(board31[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 181 && temp_position <= 240 && x >= 1 + 40 && x <= 60 + 40) { // board41
      for (int i = 0; i < 728; i++) {
        int board_x = pgm_read_byte(&(board41[1][i])) + 40;
        int board_y = pgm_read_byte(&(board41[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 1 && temp_position <= 60 && x >= 61 + 40 && x <= 120 + 40) { // board12
      for (int i = 0; i < 602; i++) {
        int board_x = pgm_read_byte(&(board12[1][i])) + 40;
        int board_y = pgm_read_byte(&(board12[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 61 && temp_position <= 120 && x >= 61 + 40 && x <= 120 + 40) { // board22
      for (int i = 0; i < 504; i++) {
        int board_x = pgm_read_byte(&(board22[1][i])) + 40;
        int board_y = pgm_read_byte(&(board22[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 121 && temp_position <= 180 && x >= 61 + 40 && x <= 120 + 40) { // board32
      for (int i = 0; i < 578; i++) {
        int board_x = pgm_read_byte(&(board32[1][i])) + 40;
        int board_y = pgm_read_byte(&(board32[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 181 && temp_position <= 240 && x >= 61 + 40 && x <= 120 + 40) { // board42
      for (int i = 0; i < 660; i++) {
        int board_x = pgm_read_byte(&(board42[1][i])) + 40;
        int board_y = pgm_read_byte(&(board42[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 1 && temp_position <= 60 && x >= 121 + 40 && x <= 180 + 40) { // board13
      for (int i = 0; i < 604; i++) {
        int board_x = pgm_read_byte(&(board13[1][i])) + 40;
        int board_y = pgm_read_byte(&(board13[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 61 && temp_position <= 120 && x >= 121 + 40 && x <= 180 + 40) { // board23
      for (int i = 0; i < 512; i++) {
        int board_x = pgm_read_byte(&(board23[1][i])) + 40;
        int board_y = pgm_read_byte(&(board23[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 121 && temp_position <= 180 && x >= 121 + 40 && x <= 180 + 40) { // board33
      for (int i = 0; i < 590; i++) {
        int board_x = pgm_read_byte(&(board33[1][i])) + 40;
        int board_y = pgm_read_byte(&(board33[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 181 && temp_position <= 240 && x >= 121 + 40 && x <= 180 + 40) { // board43
      for (int i = 0; i < 664; i++) {
        int board_x = pgm_read_byte(&(board43[1][i])) + 40;
        int board_y = pgm_read_byte(&(board43[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 1 && temp_position <= 60 && x >= 181 + 40 && x <= 240 + 40) { // board14
      for (int i = 0; i < 693; i++) {
        int board_x = pgm_read_byte(&(board14[1][i])) + 40;
        int board_y = pgm_read_byte(&(board14[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 61 && temp_position <= 120 && x >= 181 + 40 && x <= 240 + 40) { // board24
      for (int i = 0; i < 604; i++) {
        int board_x = pgm_read_byte(&(board24[1][i])) + 40;
        int board_y = pgm_read_byte(&(board24[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 121 && temp_position <= 180 && x >= 181 + 40 && x <= 240 + 40) { // board34
      for (int i = 0; i < 662; i++) {
        int board_x = pgm_read_byte(&(board34[1][i])) + 40;
        int board_y = pgm_read_byte(&(board34[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 181 && temp_position <= 240 && x >= 181 + 40 && x <= 240 + 40) { // board44
      for (int i = 0; i < 732; i++) {
        int board_x = pgm_read_byte(&(board44[1][i])) + 40;
        int board_y = pgm_read_byte(&(board44[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    }
  } else if (Direction == 4) { // check when moving down
    int temp_position = y + 10;
    if (temp_position >= 1 && temp_position <= 60 && x >= 1 + 40 && x <= 60 + 40) { // board11
      for (int i = 0; i < 689; i++) {
        int board_x = pgm_read_byte(&(board11[1][i])) + 40;
        int board_y = pgm_read_byte(&(board11[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 61 && temp_position <= 120 && x >= 1 + 40 && x <= 60 + 40) { // board21
      for (int i = 0; i < 604; i++) {
        int board_x = pgm_read_byte(&(board21[1][i])) + 40;
        int board_y = pgm_read_byte(&(board21[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 121 && temp_position <= 180 && x >= 1 + 40 && x <= 60 + 40) { // board31
      for (int i = 0; i < 662; i++) {
        int board_x = pgm_read_byte(&(board31[1][i])) + 40;
        int board_y = pgm_read_byte(&(board31[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 181 && temp_position <= 240 && x >= 1 + 40 && x <= 60 + 40) { // board41
      for (int i = 0; i < 728; i++) {
        int board_x = pgm_read_byte(&(board41[1][i])) + 40;
        int board_y = pgm_read_byte(&(board41[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 1 && temp_position <= 60 && x >= 61 + 40 && x <= 120 + 40) { // board12
      for (int i = 0; i < 602; i++) {
        int board_x = pgm_read_byte(&(board12[1][i])) + 40;
        int board_y = pgm_read_byte(&(board12[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 61 && temp_position <= 120 && x >= 61 + 40 && x <= 120 + 40) { // board22
      for (int i = 0; i < 504; i++) {
        int board_x = pgm_read_byte(&(board22[1][i])) + 40;
        int board_y = pgm_read_byte(&(board22[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 121 && temp_position <= 180 && x >= 61 + 40 && x <= 120 + 40) { // board32
      for (int i = 0; i < 578; i++) {
        int board_x = pgm_read_byte(&(board32[1][i])) + 40;
        int board_y = pgm_read_byte(&(board32[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 181 && temp_position <= 240 && x >= 61 + 40 && x <= 120 + 40) { // board42
      for (int i = 0; i < 660; i++) {
        int board_x = pgm_read_byte(&(board42[1][i])) + 40;
        int board_y = pgm_read_byte(&(board42[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 1 && temp_position <= 60 && x >= 121 + 40 && x <= 180 + 40) { // board13
      for (int i = 0; i < 604; i++) {
        int board_x = pgm_read_byte(&(board13[1][i])) + 40;
        int board_y = pgm_read_byte(&(board13[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 61 && temp_position <= 120 && x >= 121 + 40 && x <= 180 + 40) { // board23
      for (int i = 0; i < 512; i++) {
        int board_x = pgm_read_byte(&(board23[1][i])) + 40;
        int board_y = pgm_read_byte(&(board23[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 121 && temp_position <= 180 && x >= 121 + 40 && x <= 180 + 40) { // board33
      for (int i = 0; i < 590; i++) {
        int board_x = pgm_read_byte(&(board33[1][i])) + 40;
        int board_y = pgm_read_byte(&(board33[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 181 && temp_position <= 240 && x >= 121 + 40 && x <= 180 + 40) { // board43
      for (int i = 0; i < 664; i++) {
        int board_x = pgm_read_byte(&(board43[1][i])) + 40;
        int board_y = pgm_read_byte(&(board43[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 1 && temp_position <= 60 && x >= 181 + 40 && x <= 240 + 40) { // board14
      for (int i = 0; i < 693; i++) {
        int board_x = pgm_read_byte(&(board14[1][i])) + 40;
        int board_y = pgm_read_byte(&(board14[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 61 && temp_position <= 120 && x >= 181 + 40 && x <= 240 + 40) { // board24
      for (int i = 0; i < 604; i++) {
        int board_x = pgm_read_byte(&(board24[1][i])) + 40;
        int board_y = pgm_read_byte(&(board24[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 121 && temp_position <= 180 && x >= 181 + 40 && x <= 240 + 40) { // board34
      for (int i = 0; i < 662; i++) {
        int board_x = pgm_read_byte(&(board34[1][i])) + 40;
        int board_y = pgm_read_byte(&(board34[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    } else if (temp_position >= 181 && temp_position <= 240 && x >= 181 + 40 && x <= 240 + 40) { // board44
      for (int i = 0; i < 732; i++) {
        int board_x = pgm_read_byte(&(board44[1][i])) + 40;
        int board_y = pgm_read_byte(&(board44[0][i]));
        if ((x == board_x || x + 1 == board_x || x + 2 == board_x
            || x + 3 == board_x || x + 4 == board_x
            || x + 5 == board_x || x + 6 == board_x
            || x + 7 == board_x || x + 8 == board_x
            || x + 9 == board_x) && temp_position == board_y)
          return 0;
      }
    }
  }
  return 1;
}

void EatFood(int x, int y) {
  for (int i = 0; i < 82; i++) {
    int board_x = BoardFood[0][i] + 40;
    int board_y = BoardFood[1][i];
    if ((x == board_x || x + 1 == board_x || x + 2 == board_x
        || x + 3 == board_x || x + 4 == board_x || x + 5 == board_x
        || x + 6 == board_x || x + 7 == board_x)
        && (y == board_y || y + 1 == board_y || y + 2 == board_y
            || y + 3 == board_y || y + 4 == board_y
            || y + 5 == board_y || y + 6 == board_y
            || y + 7 == board_y)) {
      BoardFood[0][i] = -1;
      BoardFood[1][i] = -1;
      FoodCounter = FoodCounter + 1;
    }
  }
}

void AvoidFood(int x, int y, int Direction) {
  if (Direction == 1) {  // check when moving right
    int temp_position = x - 1;
    for (int i = 0; i < 82; i++) {
      int board_x = BoardFood[0][i] + 40;
      int board_y = BoardFood[1][i];
      if (temp_position == board_x || temp_position - 1 == board_x || temp_position - 2 == board_x)
        myGLCD.drawBitmap(board_x, board_y, 3, 3, food);
    }
  } else if (Direction == 2) { // check when moving left
    int temp_position = x + 10;
    for (int i = 0; i < 82; i++) {
      int board_x = BoardFood[0][i] + 40;
      int board_y = BoardFood[1][i];
      if (temp_position == board_x || temp_position + 1 == board_x || temp_position + 2 == board_x)
        myGLCD.drawBitmap(board_x, board_y, 3, 3, food);
    }
  } else if (Direction == 3) { // check when moving up
    int temp_position = y + 10;
    for (int i = 0; i < 82; i++) {
      int board_x = BoardFood[0][i] + 40;
      int board_y = BoardFood[1][i];
      if (temp_position == board_y || temp_position + 1 == board_y || temp_position + 2 == board_y)
        myGLCD.drawBitmap(board_x, board_y, 3, 3, food);
    }
  } else if (Direction == 4) { // check when moving down
    int temp_position = y - 1;
    for (int i = 0; i < 82; i++) {
      int board_x = BoardFood[0][i] + 40;
      int board_y = BoardFood[1][i];
      if (temp_position == board_y || temp_position - 1 == board_y || temp_position - 2 == board_y)
        myGLCD.drawBitmap(board_x, board_y, 3, 3, food);
    }
  }

}

void DrawPacman(int x, int y) {
  if (PacmanDirection == 0) {  // Draw initial pattern
        myGLCD.drawBitmap(x, y, 10, 10, pacman_right);
  } else if (PacmanDirection == 1) {  // Draw pattern , when moving right
          myGLCD.drawBitmap(x, y, 10, 10, pacman_right);
          myGLCD.setColor(0, 0, 0);
          for (int i = 0; i < 10; i++) {
                myGLCD.drawPixel(x - 1, y + i);
          }
          if ( ( steps % 10 >= 6 ) && ( steps % 10 <= 10 ) ) {          
                myGLCD.drawBitmap(x, y, 10, 10, pacman_right_closed);
                myGLCD.setColor(0, 0, 0);
                for (int i = 0; i < 10; i++) {
                    myGLCD.drawPixel(x - 1, y + i);
                }         
          }    
  } else if (PacmanDirection == 2) { // Draw pattern , when moving left
          myGLCD.drawBitmap(x, y, 10, 10, pacman_left);
          myGLCD.setColor(0, 0, 0);
          for (int i = 0; i < 10; i++) {
                myGLCD.drawPixel(x + 10, y + i);
          }
          if ( ( steps % 10 >= 6 ) && ( steps % 10 <= 10 ) ) {  
                myGLCD.drawBitmap(x, y, 10, 10, pacman_left_closed);
                myGLCD.setColor(0, 0, 0);
                for (int i = 0; i < 10; i++) {
                    myGLCD.drawPixel(x + 10, y + i);
                }
          }      
  } else if (PacmanDirection == 3) { // Draw pattern , when moving up
          myGLCD.drawBitmap(x, y, 10, 10, pacman_up);
          myGLCD.setColor(0, 0, 0);
          for (int i = 0; i < 10; i++) {
                myGLCD.drawPixel(x + i, y + 10);
          }
          if ( ( steps % 10 >= 6 ) && ( steps % 10 <= 10 ) ) {       
                myGLCD.drawBitmap(x, y, 10, 10, pacman_up_closed);
                myGLCD.setColor(0, 0, 0);
                for (int i = 0; i < 10; i++) {
                    myGLCD.drawPixel(x + i, y + 10);
                }
          }     
  } else if (PacmanDirection == 4) {  // Draw pattern , when moving down
          myGLCD.drawBitmap(x, y, 10, 10, pacman_down);
          myGLCD.setColor(0, 0, 0);
          for (int i = 0; i < 10; i++) {
                myGLCD.drawPixel(x + i, y - 1);
          }
          if ( ( steps % 10 >= 6 ) && ( steps % 10 <= 10 ) ) {  
                myGLCD.drawBitmap(x, y, 10, 10, pacman_down_closed);
                myGLCD.setColor(0, 0, 0);
                for (int i = 0; i < 10; i++) {
                    myGLCD.drawPixel(x + i, y - 1);
                }
          }   
    }
}

void DrawRedGhost(int x, int y) {
  if (RedGhostDirection == 0) { // initial pattern
    myGLCD.drawBitmap(x, y, 10, 10, red);
  } else if (RedGhostDirection == 1) { // Draw pattern , when moving right
    myGLCD.drawBitmap(x, y, 10, 10, red);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x - 1, y + i);
    }
  } else if (RedGhostDirection == 2) {  // Draw pattern , when moving left
    myGLCD.drawBitmap(x, y, 10, 10, red);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x + 10, y + i);
    }
  } else if (RedGhostDirection == 3) {  // Draw pattern , when moving up
    myGLCD.drawBitmap(x, y, 10, 10, red);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x + i, y + 10);
    }
  } else if (RedGhostDirection == 4) {  // Draw pattern , when moving down
    myGLCD.drawBitmap(x, y, 10, 10, red);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x + i, y - 1);
    }
  }
}

void DrawPinkGhost(int x, int y) {
  if (PinkGhostDirection == 0) { // initial pattern
    myGLCD.drawBitmap(x, y, 10, 10, pink);
  } else if (PinkGhostDirection == 1) { // Draw pattern , when moving right
    myGLCD.drawBitmap(x, y, 10, 10, pink);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x - 1, y + i);
    }
  } else if (PinkGhostDirection == 2) {  // Draw pattern , when moving left
    myGLCD.drawBitmap(x, y, 10, 10, pink);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x + 10, y + i);
    }
  } else if (PinkGhostDirection == 3) {  // Draw pattern , when moving up
    myGLCD.drawBitmap(x, y, 10, 10, pink);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x + i, y + 10);
    }
  } else if (PinkGhostDirection == 4) {  // Draw pattern , when moving down
    myGLCD.drawBitmap(x, y, 10, 10, pink);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x + i, y - 1);
    }
  }
}

void DrawBlueGhost(int x, int y) {
  if (BlueGhostDirection == 0) { // initial pattern
    myGLCD.drawBitmap(x, y, 10, 10, blue);
  } else if (BlueGhostDirection == 1) { // Draw pattern , when moving right
    myGLCD.drawBitmap(x, y, 10, 10, blue);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x - 1, y + i);
    }
  } else if (BlueGhostDirection == 2) {  // Draw pattern , when moving left
    myGLCD.drawBitmap(x, y, 10, 10, blue);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x + 10, y + i);
    }
  } else if (BlueGhostDirection == 3) {  // Draw pattern , when moving up
    myGLCD.drawBitmap(x, y, 10, 10, blue);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x + i, y + 10);
    }
  } else if (BlueGhostDirection == 4) {  // Draw pattern , when moving down
    myGLCD.drawBitmap(x, y, 10, 10, blue);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x + i, y - 1);
    }
  }
}

void DrawOrangeGhost(int x, int y) {
  if (OrangeGhostDirection == 0) { // initial pattern
    myGLCD.drawBitmap(x, y, 10, 10, orange);
  } else if (OrangeGhostDirection == 1) { // Draw pattern , when moving right
    myGLCD.drawBitmap(x, y, 10, 10, orange);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x - 1, y + i);
    }
  } else if (OrangeGhostDirection == 2) {  // Draw pattern , when moving left
    myGLCD.drawBitmap(x, y, 10, 10, orange);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x + 10, y + i);
    }
  } else if (OrangeGhostDirection == 3) {  // Draw pattern , when moving up
    myGLCD.drawBitmap(x, y, 10, 10, orange);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x + i, y + 10);
    }
  } else if (OrangeGhostDirection == 4) {  // Draw pattern , when moving down
    myGLCD.drawBitmap(x, y, 10, 10, orange);
    myGLCD.setColor(0, 0, 0);
    for (int i = 0; i < 10; i++) {
      myGLCD.drawPixel(x + i, y - 1);
    }
  }
}

void DrawFood() {
  int Displayint1, Displayint2;
  for (int i = 0; i < 82; i++) {
    Displayint1 = BoardFood[0][i];
    Displayint2 = BoardFood[1][i];
    if (Displayint1 != -1 && Displayint2 != -1)
      myGLCD.drawBitmap(Displayint1 + 40, Displayint2, 3, 3, food);
  }
}

void DrawBackground() {
  int Displayint1, Displayint2; // Draw stage
  myGLCD.setColor(0, 0, 255);
  for (int i = 0; i < 10018; i++) {
    Displayint1 = pgm_read_byte(&(board[1][i]));
    Displayint2 = pgm_read_byte(&(board[0][i]));
    myGLCD.drawPixel(Displayint1 + 40, Displayint2);
  }

  myGLCD.setColor(100, 100, 100); // Draw right button
  myGLCD.fillRoundRect(5, 4, 30, 30);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(5, 4, 30, 30);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 100, 100);
  myGLCD.print("R", 10, 9);

  myGLCD.setColor(100, 100, 100);  // Draw left button
  myGLCD.fillRoundRect(5, 44, 30, 70);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(5, 44, 30, 70);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 100, 100);
  myGLCD.print("L", 10, 49);

  myGLCD.setColor(100, 100, 100);  // Draw up button
  myGLCD.fillRoundRect(5, 84, 30, 110);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(5, 84, 30, 110);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 100, 100);
  myGLCD.print("U", 10, 89);

  myGLCD.setColor(100, 100, 100); // Draw down button
  myGLCD.fillRoundRect(5, 124, 30, 150);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(5, 124, 30, 150);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 100, 100);
  myGLCD.print("D", 10, 129);
}

void StartOver() {

  TaskMovePacman.disable();
  TaskMoveRedGhost.disable();
  TaskStartPinkGhost.disable();
  TaskMovePinkGhost.disable();
  TaskStartBlueGhost.disable();
  TaskMoveBlueGhost.disable();
  TaskStartOrangeGhost.disable();
  TaskMoveOrangeGhost.disable();

  pacman_position_x = 156, pacman_position_y = 175;  // Pacman's start
  PacmanDirection = 0;
  steps = 0;

  red_ghost_position_x = 156, red_ghost_position_y = 87; // Red Ghost's start
  RedGhostDirection = 0;
  angle_red = 0;
  wall_red = 0;
  priority_red = 0;
  third_choice_red = 0;
  exception_red = 0;
  variable_red = 0;

  pink_ghost_position_x = 156, pink_ghost_position_y = 107; // Pink Ghost's start
  PinkGhostDirection = 0;
  angle_pink = 0;
  wall_pink = 0;
  priority_pink = 1;
  third_choice_pink = 0;
  exception_pink = 0;
  variable_pink = 0;
  count_steps_pink = 0;

  blue_ghost_position_x = 141, blue_ghost_position_y = 107; // Blue Ghost's start
  BlueGhostDirection = 0;
  priority_blue = 0;
  count_steps_blue = 0;

  orange_ghost_position_x = 171, orange_ghost_position_y = 107; // Orange Ghost's start
  OrangeGhostDirection = 0;
  priority_orange = 0;
  count_steps_orange = 0;

  if (lives == -1) {
    int x, y;
    for (int i = 0; i < 82; i++) {
      x = InitialBoardFood[0][i];
      y = InitialBoardFood[1][i];

      BoardFood[0][i] = x;
      BoardFood[1][i] = y;
    }
    FoodCounter = 0;
    lives = 3;
  }

  delay(1000);
  myGLCD.clrScr();
  DrawBackground();
  DrawFood();
  DrawPacman(pacman_position_x, pacman_position_y);
  DrawRedGhost(red_ghost_position_x, red_ghost_position_y);
  DrawPinkGhost(pink_ghost_position_x, pink_ghost_position_y);
  DrawBlueGhost(blue_ghost_position_x, blue_ghost_position_y);
  DrawOrangeGhost(orange_ghost_position_x, orange_ghost_position_y);

  TaskMovePacman.enable();
  TaskMoveRedGhost.enable();
  TaskStartPinkGhost.enable();
  TaskStartBlueGhost.enable();
  TaskStartOrangeGhost.enable();

}
