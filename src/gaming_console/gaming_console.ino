/*********************************************************************** 
*  ESP32 Game Console - by Ahmed Gamal, Omar Ramadan, and Ziyad Eslam  * 
*                                                                      *
*  ESP32 retro arcade game console with PlayStation 4 controller.      *
*  Games: Tetris, Snake, Breakout, and Bomber.                         *
*                                                                      *
*  VGA output uses the FabGL VGA Library by                            * 
*  Fabrizio Di Vittorio. For more datails see:                         *
*  https://github.com/fdivitto/fabgl/                                  *
*                                                                      *
*  PlayStation 4 input by aed3's PS4-esp32 library:                    *
*  https://github.com/aed3/PS4-esp32/                                  *
*                                                                      * 
*  This project is heavily based on Rob Cai's instructable:            *
*  https://www.instructables.com/ESP32-VGA-Arcade-Games-and-Joystick/  *
*                                                                      * 
***********************************************************************/

#include "fabgl.h"
#include <canvas.h>
#include <vgacontroller.h>
#include <PS4Controller.h>
#include "BluetoothSerial.h" 

//----------------------------------- Common ----------------------------------------------
bool button = 0;
bool button_right = 0;
bool button_up = 0;
bool button_left = 0;
bool button_down = 0;
bool button_right_old = 0;
bool button_up_old = 0;
bool button_left_old = 0;
bool button_down_old = 0;
bool button_square = 0;
bool button_cross = 0;
bool button_circle = 0;
bool button_triangle = 0;
bool button_ps = 0;
int colA, colB, colC;
int choice;
int gameSelect = 1;
long millis_old = 0;
bool connected_old = true;;
bool app = false;
BluetoothSerial BLE;

//---------------------------------- Tetris --------------------------------------
int block[4][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
int blockExt[4][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
int blockOld[4][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
int blockTmp[4][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
int blockTr[4][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
int yLine[4] = { 0, 0, 0, 0 };
int yLineTmp[4] = { 0, 0, 0, 0 };
int myRGB[3] = { 0, 0, 0 };
int yCounter = 0;
int x = 60;
int y = 6;
int z = 10;
int score = 1;
int scoreNew = 1;
int noLoop = -1;
int rotationDirection = 1;
int delta = 0;
int color = 1;
int colorOld;
int blockN, blockNext;
int busy;
int noDelete = 0;
int k = 0;
int a = 40;
int b = 10;
int counterMenu = 0;
unsigned long myTime = 0;
int fast = 14;  //14;
int resX = 320;
int resY = 200;
int squareX = 7;
int squareY = 6;
int myColumns = 11;
int myRaws = 26;
int level = 1;
int grid[29][11];
//----------------------------------------------------------------------------------------

//--------------------------------------------- Snake ------------------------------------
byte counterMenuSnake = 0;
byte counterMenu2 = 0;
byte state = 1;
byte scoreSnake = 0;
byte levelSnake = 1;
byte scoreMax = 12;  //default = 12
int foodX;
int foodY;
int snakeMaxLength = 199;
int sx[200];  // > slength + scoreMax*delta + 1 = 40
int sy[200];
int slength = 9;     // snake starting length
int slengthIni = 9;  // snake starting length
int deltaSnake = 9;  // snake length increment
int i;
byte direct = 3;
int speedDelay = 32;
int VGAX_WIDTH = 320;
int VGAX_HEIGHT = 200;
int x0Area = 100;
int y0Area = 20;
int x1Area = 300;
int y1Area = 180;
float cornerStep = 50.;
//---------------------------------------------------------------------------------------

//------------------------------------------- Breakout ----------------------------------
float ballSpeed;
float ballAngle;
float ballAngle0;
int ballX, ballY, ballXold, ballYold;
int padLength = 24;
float padX;
int levelBreakout;
int breakoutLives;
int sgx = 1;
int sgy = 1;
int sgx0, sgy0;
float vxr, vyr;
int vx, vy;
int hitA, hitB, hitC, hitD, hit, hit0;
int brickCounter, brickCounterOld;
int breakoutSpeed;
float padSpeedStep = 0.25;
float padSpeed;
byte padSpeedMax = 8;
//---------------------------------------------------------------------------------------

//------------------------------- Bomber ------------------------------------------------
int bomberX = 120;
int bomberL = 22;
float bomberSpeed;
float speedStep = 0.25;
byte bomberSpeedMax = 8;
int bomberDelayOld = 10;
int bomberDelay = 10;
float planeLV = 1;
float planeRV = 0.8;
float planeLX, planeRX;
int planeLY, planeRY;
int planeLXold = 100;
int planeLYold = 40;
int planeRXold = 20;
int planeRYold = 30;
int expX, expY, expXmin, expXmax, expYmin, expYmax;
float bomb1X, bomb1Y, bomb1V, bomb2X, bomb2Y, bomb2V;
int bomb1Xold, bomb1Yold, bomb2Xold, bomb2Yold;
bool bomb1, bomb2;
double time1, time2;
double bomberScoreIni = 200;
double bomberScore = 200;
int bomberLives = 3;
//---------------------------------------------------------------------------------------

//------------------------------------------------------ Setup -----------------------------------------------------------------
void setup() {
  // 8 colors
  VGAController.begin(GPIO_NUM_22, GPIO_NUM_19, GPIO_NUM_17, GPIO_NUM_23, GPIO_NUM_15);
  VGAController.setResolution(VGA_320x200_75Hz);
  Canvas.selectFont(Canvas.getPresetFontInfo(40, 14));
  randomSeed(analogRead(33));
  Serial.begin(9600);
  ledcAttachPin(25, 0);
  myPrint(" press boot button for app control", 1, 1, 7);
  while(millis() < 1500) {
    app |= !digitalRead(0);
  }
  if(!app) {
    PS4.begin("b0:7d:64:0f:95:2c");
    connected_old = true;
  }
  else {
    BLE.begin("Game Console");
    connected_old = false;
  }
  Canvas.setPenColor(0, 0, 0);
  Canvas.clear();
  toneSafe(660, 200);
  toneSafe(770, 200);
  toneSafe(880, 200);
  toneSafe(990, 200);
}

//------------------------------------- main loop --------------------------------------------
//--------------------------------------------------------------------------------------------
void loop() {
  otherProcessInputs();
  if (button_ps) {
    ESP.restart();
  }
  if (button_circle && choice) {
    choice = 0;
    Canvas.setPenColor(0, 0, 0);
    Canvas.clear();
  }

  switch (choice) {

    case 1:
      if (PS4.isConnected()) PS4.setLed(0, 255, 255);
      TetrisLoop();
      connected_old = false;
      break;

    case 2:
      if (PS4.isConnected()) PS4.setLed(255, 0, 255);
      SnakeLoop();
      if (choice == 0) {
        Canvas.setPenColor(0, 0, 0);
        Canvas.clear();
      }
      connected_old = false;
      break;

    case 3:
      if (PS4.isConnected()) PS4.setLed(255, 0, 0);
      BreakoutLoop();
      connected_old = false;
      break;

    case 4:
      if (PS4.isConnected()) PS4.setLed(0, 255, 0);
      if (PS4.isConnected()) PS4.sendToController();
      BomberLoop();
      Canvas.clear();
      choice = 0;
      connected_old = false;
      break;

    default:
      if (PS4.isConnected()) PS4.setLed(255, 255, 255);
      ChoiceMenu();
      break;
  }

  if (millis() - millis_old >= 100) {
    if (PS4.isConnected()) PS4.sendToController();
    millis_old = millis();
  }
}
//--------------------------------- end of main loop -----------------------------------------
//--------------------------------------------------------------------------------------------
