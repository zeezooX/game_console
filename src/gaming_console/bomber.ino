//-----------------------------------------------------------------------------------------------
//--------------------- This is the main loop of Bomber -----------------------------------------
//-----------------------------------------------------------------------------------------------
void BomberLoop() {
  Canvas.clear();
  drawBomberIni();
  BomberLives(bomberLives);
  BomberScore(bomberScore);
  planeRX = 340;  //------------- this is needed for correct inizialization of planeR -------------
  planeRXold = 340;
  bomberX = 120;
  bomb1 = 0;
  bomb2 = 0;
  while (state == 1) {  //----------------------- Bomber starts here --------------------------
    bomberDelay = bomberDelayOld;
    planeLX += -planeLV;
    if (planeLX < 12) {
      planeLX = 267;
      bomberScore += -4;
      BomberScore(bomberScore);
      planeLY = random(10, 105);
      planeLV = random(80., 190.) / 100.;
    }
    planeRX += planeRV;
    if (planeRX > 291) {
      planeRX = 28;
      bomberScore += -4;
      BomberScore(bomberScore);
      planeRY = random(10, 105);
      planeRV = random(80., 190.) / 100.;
    }
    NormalProcessInputs();
    planeL(planeLXold, planeLYold, 0);
    planeL(int(planeLX), planeLY, 3);
    planeR(planeRXold, planeRYold, 0);
    planeR(int(planeRX), planeRY, 6);
    myBomb1();
    myBomb2();
    shot(bomberX, 1);
    bomber(bomberX, 1);
    if (button_circle) { state = 0; }  //----------- stop the game is UP and DOWN are pressed together ------------------
    if (button_ps) { ESP.restart(); }
    planeLXold = int(planeLX);
    planeLYold = planeLY;
    planeRXold = int(planeRX);
    planeRYold = planeRY;
    bomb1Xold = int(bomb1X);
    bomb1Yold = int(bomb1Y);
    bomb2Xold = int(bomb2X);
    bomb2Yold = int(bomb2Y);
    delay(bomberDelay);
  }
  clearInputs();
  delay(200);
}
//-----------------------------------------------------------------------------------------------
//--------------------- This is the end loop of Bomber ------------------------------------------
//-----------------------------------------------------------------------------------------------

void drawBomberIni() {  //-------------- Bomber screen inizialization -----------------------------
  myRect(11, 5, 280, 156, 7);
  myRect(10, 4, 282, 158, 7);
  myPrint("Score", 10, 164, 2);
  myPrint("Lives", 114, 164, 2);
  drawLives(breakoutLives);
  myFullRect(12, 155, 278, 5, 2);
  state = 1;
}

void shot(int x, int c) {
  if (button_cross == 1) {
    myLine(bomberX + bomberL / 2, 141, bomberX + bomberL / 2, 6, 1);
    for (int i = 1; i <= 9; i++) {
      myLine(bomberX + bomberL / 2, 156 - i * 15, bomberX + bomberL / 2, 156 - (i + 1) * 15, 4);
      delay(bomberDelay / 10);
    }
    myLine(bomberX + bomberL / 2, 141, bomberX + bomberL / 2, 6, 0);
    bomberDelay = 0;
    bomberScore += -1;
    BomberScore(bomberScore);
    checkShot(bomberX + bomberL / 2);
  }
}

void myBomber(int x, int c) {
  myFullRect(x + bomberL / 2 - 1, 142, 2, 3, c);
  myFullRect(x + bomberL / 2 - 4, 145, 8, 4, c);
  myFullRect(x, 150, bomberL, 4, c);
}

void planeL(int x, int y, int c) {
  myLine(x, y, x + 12, y, c);
  myLine(x + 1, y - 1, x + 13, y - 1, c);
  myLine(x + 3, y - 2, x + 9, y - 2, c);
  myLine(x + 13, y - 2, x + 14, y - 2, c);
  myLine(x + 14, y - 3, x + 15, y - 3, c);
  myLine(x + 15, y - 4, x + 16, y - 4, c);
  myLine(x + 4, y + 1, x + 7, y + 1, c);
  myLine(x + 6, y + 2, x + 9, y + 2, c);
}

void planeR(int x, int y, int c) {
  myLine(x, y, x - 12, y, c);
  myLine(x - 1, y - 1, x - 13, y - 1, c);
  myLine(x - 3, y - 2, x - 9, y - 2, c);
  myLine(x - 13, y - 2, x - 14, y - 2, c);
  myLine(x - 14, y - 3, x - 15, y - 3, c);
  myLine(x - 15, y - 4, x - 16, y - 4, c);
  myLine(x - 4, y + 1, x - 7, y + 1, c);
  myLine(x - 6, y + 2, x - 9, y + 2, c);
}

void bomb(int x, int y, int c) {
  myLine(x, y, x + 8, y, c);
  myLine(x + 9, y - 1, x + 9, y + 1, c);
  myLine(x + 1, y + 1, x + 6, y + 1, c);
  myLine(x + 1, y - 1, x + 6, y - 1, c);
  myLine(x + 2, y + 2, x + 5, y + 2, c);
  myLine(x + 2, y - 2, x + 5, y - 2, c);
}

void bombR(int x, int y, int c) {
  myLine(x, y, x - 8, y, c);
  myLine(x - 9, y - 1, x - 9, y + 1, c);
  myLine(x - 1, y + 1, x - 6, y + 1, c);
  myLine(x - 1, y - 1, x - 6, y - 1, c);
  myLine(x - 2, y + 2, x - 5, y + 2, c);
  myLine(x - 2, y - 2, x - 5, y - 2, c);
}

void bomber(float x, int c) {  //----------------------- bomber motion control -----------------------------------
  if (button_left == 1) {
    myBomber(bomberX, 0);
    if (button_left_old == 1) {
      bomberSpeed += -speedStep;
      if (bomberSpeed < -bomberSpeedMax) { bomberSpeed = -bomberSpeedMax; }
    } else {
      bomberSpeed = -speedStep;
      button_left_old = 1;
    }
    bomberX += bomberSpeed;
    if (bomberX < 12) { bomberX = 12; }
    myBomber(bomberX, c);
    delay(bomberDelay);
    bomberDelay = 0;
  } else {
    button_left_old = 0;
  }
  if (button_right == 1) {
    myBomber(bomberX, 0);
    if (button_right_old == 1) {
      bomberSpeed += speedStep;
      if (bomberSpeed > bomberSpeedMax) { bomberSpeed = bomberSpeedMax; }
    } else {
      bomberSpeed = speedStep;
      button_right_old = 1;
    }
    bomberX += bomberSpeed;
    if (bomberX > 290 - bomberL) { bomberX = 290 - bomberL; }
    myBomber(bomberX, c);
    delay(bomberDelay);
    bomberDelay = 0;
  } else {
    button_right_old = 0;
  }
}

void checkShot(int x) {                     //--------------------- This checks if Planes or Bombs have been shot ----------------------------
  if (x >= planeLX && x <= planeLX + 16) {  //----------------- plane Left has been shot -----------------------
    planeL(planeLX, planeLY, 1);
    expXmin = planeLX + 8;
    expXmax = expXmin;
    expYmin = planeLY - 1;
    expYmax = expYmin;
    delay(100);
    planeL(planeLX, planeLY, 0);
    toneSafe(660, 30);
    for (int i = 1; i < 4; i++) {
      for (int j = 1; j < 10; j++) {
        expX = random(-6 * i, 6 * i) + planeLX + 8;
        expY = random(-6 * i, 6 * i) + planeLY - 1;
        if (expX > 12 && expX < 290 && expY > 10 && expY < 135) {
          putpixel(expX, expY, 4);
          if (expX < expXmin) { expXmin = expX; }
          if (expX > expXmax) { expXmax = expX; }
          if (expY < expYmin) { expYmin = expY; }
          if (expY > expYmax) { expYmax = expY; }
        }
      }
      delay(50);
    }
    myFullRect(expXmin, expYmin, expXmax - expXmin, expYmax - expYmin, 0);
    planeLX = 267 - random(24);
    planeLY = random(10, 105);
    bomberScore += bomberScoreIni / 10 + 1;
    BomberScore(bomberScore);
  }
  if (x >= planeRX - 16 && x <= planeRX) {  //----------------- plane Right has been shot -----------------------
    planeR(planeRX, planeRY, 1);
    expXmin = planeRX - 8;
    expXmax = expXmin;
    expYmin = planeRY - 1;
    expYmax = expYmin;
    delay(100);
    planeR(planeRX, planeRY, 0);
    toneSafe(660, 30);
    for (int i = 1; i < 4; i++) {
      for (int j = 1; j < 10; j++) {
        expX = random(-6 * i, 6 * i) + planeRX - 8;
        expY = random(-6 * i, 6 * i) + planeRY - 1;
        if (expX > 12 && expX < 290 && expY > 10 && expY < 135) {
          putpixel(expX, expY, 4);
          if (expX < expXmin) { expXmin = expX; }
          if (expX > expXmax) { expXmax = expX; }
          if (expY < expYmin) { expYmin = expY; }
          if (expY > expYmax) { expYmax = expY; }
        }
      }
      delay(50);
    }
    myFullRect(expXmin, expYmin, expXmax - expXmin, expYmax - expYmin, 0);
    planeRX = 28 + random(24);
    planeRY = random(10, 105);
    bomberScore += bomberScoreIni / 10 + 1;
    BomberScore(bomberScore);
  }
  if (x >= int(bomb1X) && x <= int(bomb1X) + 8) {  //----------------- bomb one has been shot -----------------------
    bomb(int(bomb1X), int(bomb1Y), 6);
    expXmin = int(bomb1X) + 4;
    expXmax = expXmin;
    expYmin = int(bomb1Y);
    expYmax = expYmin;
    delay(100);
    bomb(int(bomb1X), int(bomb1Y), 0);
    toneSafe(660, 30);
    for (int i = 1; i < 4; i++) {
      for (int j = 1; j < 10; j++) {
        expX = random(-4 * i, 4 * i) + int(bomb1X) + 4;
        expY = random(-4 * i, 4 * i) + int(bomb1Y);
        if (expX > 12 && expX < 290 && expY > 10 && expY < 135) {
          putpixel(expX, expY, 4);
          if (expX < expXmin) { expXmin = expX; }
          if (expX > expXmax) { expXmax = expX; }
          if (expY < expYmin) { expYmin = expY; }
          if (expY > expYmax) { expYmax = expY; }
        }
      }
      delay(50);
      myFullRect(expXmin, expYmin, expXmax - expXmin, expYmax - expYmin, 0);
      bomb1X = 0;
      bomb1 = 0;
    }
    bomberScore += bomberScoreIni / 20 + 1;
    BomberScore(bomberScore);
  }
  if (x >= int(bomb2X) - 8 && x <= int(bomb2X)) {  //----------------- bomb two has been shot -----------------------
    bombR(int(bomb2X), int(bomb2Y), 6);
    expXmin = int(bomb2X) + 4;
    expXmax = expXmin;
    expYmin = int(bomb2Y);
    expYmax = expYmin;
    delay(100);
    bombR(int(bomb2X), int(bomb2Y), 0);
    toneSafe(660, 30);
    for (int i = 1; i < 4; i++) {
      for (int j = 1; j < 10; j++) {
        expX = random(-4 * i, 4 * i) + int(bomb2X) - 4;
        expY = random(-4 * i, 4 * i) + int(bomb2Y);
        if (expX > 12 && expX < 290 && expY > 10 && expY < 135) {
          putpixel(expX, expY, 4);
          if (expX < expXmin) { expXmin = expX; }
          if (expX > expXmax) { expXmax = expX; }
          if (expY < expYmin) { expYmin = expY; }
          if (expY > expYmax) { expYmax = expY; }
        }
      }
      delay(50);
      myFullRect(expXmin, expYmin, expXmax - expXmin, expYmax - expYmin, 0);
      bomb2X = 0;
      bomb2 = 0;
    }
    bomberScore += bomberScoreIni / 20 + 1;
    BomberScore(bomberScore);
  }
}

void checkBomberShot(int whichBomb) {                                                      //------------------------- checks if bomb has hit the Bomber -----------------------------------------------
  if (int(bomb1X) + 9 >= bomberX && int(bomb1X) <= bomberX + bomberL && whichBomb == 1) {  //----------------- bomber has been shot by bomb Left -----------------------
    bomber(bomberX, 4);
    expXmin = bomberX + bomberL / 2;
    expXmax = expXmin;
    expYmin = 146;
    expYmax = expYmin;
    delay(100);
    for (int i = 1; i < 8; i++) {
      for (int j = 1; j < 15; j++) {
        expX = random(-5 * i, 5 * i) + bomberX + bomberL / 2;
        expY = random(-6 * i, 3 * i) + 146;
        if (expX > 12 && expX < 290 && expY > 10 && expY < 162) {
          putpixel(expX, expY, 4);
          if (expX < expXmin) { expXmin = expX; }
          if (expX > expXmax) { expXmax = expX; }
          if (expY < expYmin) { expYmin = expY; }
          if (expY > expYmax) { expYmax = expY; }
        }
      }
      delay(50);
    }
    toneSafe(330, 200);
    delay(1000);
    myFullRect(expXmin, expYmin, expXmax - expXmin, expYmax - expYmin, 0);
    drawBomberIni();
    myBomber(bomberX, 1);
    bomberScore = bomberScoreIni;
    bomberLives += -1;
    BomberLives(bomberLives);
  }
  if (int(bomb2X) >= bomberX && int(bomb2X) - 9 <= bomberX + bomberL && whichBomb == 2) {  //----------------- bomber has been shot by bomb Right -----------------------
    bomber(bomberX, 4);
    expXmin = bomberX + bomberL / 2;
    expXmax = expXmin;
    expYmin = 146;
    expYmax = expYmin;
    delay(100);
    for (int i = 1; i < 8; i++) {
      for (int j = 1; j < 15; j++) {
        expX = random(-5 * i, 5 * i) + bomberX + bomberL / 2;
        expY = random(-6 * i, 3 * i) + 146;
        if (expX > 12 && expX < 290 && expY > 10 && expY < 162) {
          putpixel(expX, expY, 4);
          if (expX < expXmin) { expXmin = expX; }
          if (expX > expXmax) { expXmax = expX; }
          if (expY < expYmin) { expYmin = expY; }
          if (expY > expYmax) { expYmax = expY; }
        }
      }
      delay(50);
    }
    toneSafe(330, 200);
    delay(1000);
    myFullRect(expXmin, expYmin, expXmax - expXmin, expYmax - expYmin, 0);
    drawBomberIni();
    myBomber(bomberX, 1);
    bomberScore = bomberScoreIni;
    bomberLives += -1;
    BomberLives(bomberLives);
  }
}

void myBomb1() {  //------------------------- bomb 1 motion ---------------------------
  if (bomb1 == 1) {
    bomb1X -= bomb1V;
    bomb1Y += pow(((millis() - time1) / 1000.), 2);
    bomb(bomb1Xold, bomb1Yold, 0);
    if (bomb1Y > 150) {
      checkBomberShot(1);  //------------------- this checks if bomb hit the Bomber ----------------
      myBomber(bomberX, 1);
    }
    if (bomb1X < 12 || bomb1X > 281 || bomb1Y > 150) {
      bomb(bomb1Xold, bomb1Yold, 0);
      bomb1 = 0;
    } else {
      bomb(int(bomb1X), int(bomb1Y), 5);
    }
  } else {
    if (random(50) == 5) {  //---------------- heter it draws a new bomb ---------------------
      bomb1X = planeLX;
      bomb1Y = planeLY + 4;
      bomb1V = random(-100., 100.) / 100.;
      time1 = millis();
      bomb1 = 1;
    }
  }
}

void myBomb2() {  //------------------------- bomb 2 motion ---------------------------
  if (bomb2 == 1) {
    bomb2X -= bomb2V;
    bomb2Y += pow(((millis() - time2) / 1000.), 2);
    bombR(bomb2Xold, bomb2Yold, 0);
    if (bomb2Y > 150) {
      checkBomberShot(2);  //------------------- this checks if bomb hit the Bomber ----------------
      myBomber(bomberX, 1);
    }
    if (bomb2X < 12 + 9 || bomb2X > 281 + 9 || bomb2Y > 150) {
      bombR(bomb2Xold, bomb2Yold, 0);
      bomb2 = 0;
    } else {
      bombR(int(bomb2X), int(bomb2Y), 7);
    }
  } else {
    if (random(50) == 5) {  //---------------- here it draws a new bomb  ---------------------
      bomb2X = planeRX;
      bomb2Y = planeRY + 4;
      bomb2V = random(-100., 100.) / 100.;
      time2 = millis();
      bomb2 = 1;
    }
  }
}

void BomberScore(int i) {  //----------------------- bomber score drawing ----------------------
  if (i > 2000 && bomberLives < 12) {
    bomberLives += 1;
    toneSafe(880, 30);
    bomberScore = bomberScoreIni;
    BomberLives(bomberLives);
  }
  if (i < 0) {
    toneSafe(330, 200);
    bomberLives += -1;
    bomberScore = bomberScoreIni;
    delay(200);
    BomberLives(bomberLives);
    delay(200);
  }
  myFullRect(52, 165, 50, 10, 0);
  myDrawNumber(85, 164, bomberScore, 4);
}

void BomberLives(int bomberLivesTemp) {  //----------------------- bomber lives drawing ----------------------
  for (int j = 1; j < 12; j++) {
    if (j <= bomberLivesTemp) {
      drawBall(150 + j * 10, 172, 4);
    } else {
      drawBall(150 + j * 10, 172, 0);
    }
  }
  if (bomberLivesTemp == 0) {  //------------------------- bomber Game Over ----------------------------------------
    smoothRect(116, 68, 78, 20, 6, 1);
    myPrint("Game Over", 120, 71, 1);
    delay(100);
    toneSafe(660, 200);
    toneSafe(330, 200);
    toneSafe(165, 200);
    toneSafe(82, 200);
    button == 0;
    clearInputs();
    myPrint("O: return to home", 90, 91, 7);
    myPrint("Any: restart game", 90, 106, 7);
    while (button == 0) { NormalProcessInputs(); }
    if (button_circle == 1) {
      state = 0;
    } else {  //-------------------------------- restart new Bomber game --------------------------------
      Canvas.clear();
      drawBomberIni();
      bomberScore = bomberScoreIni;
      bomberLives = 3;
      for (int j = 1; j < 4; j++) {
        drawBall(150 + j * 10, 172, 3);
      }
      myFullRect(52, 165, 50, 10, 0);
      myDrawNumber(85, 164, bomberScore, 4);
      planeRX = 340;  //------------- this is needed for correct inizialization of planeR -------------
      planeRXold = 340;
      planeLX = 28;  //------------- this is needed for correct inizialization of planeR -------------
      planeLXold = 340;
      bomberX = 120;
      myBomber(bomberX, 1);
      bomb1 = 0;
      bomb2 = 0;
      delay(100);
    }
  }
}
