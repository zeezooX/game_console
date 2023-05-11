void drawBreakoutIni() {
  myRect(11, 5, 280, 156, 7);
  myRect(10, 4, 282, 158, 7);
  myPrint("Score", 10, 164, 2);
  myPrint("Lives", 114, 164, 2);
  for (int i = 2; i < 13; i++) {
    for (int j = 1; j < 6; j++) {
      myFullRect(20 * i, 8 * j + 10, 18, 6, (2 * i + j) % 6 + 1);
    }
  }
  drawPad(padX, 1);
  drawLives(breakoutLives);
  delay(300);
  state = 1;
  BreakoutLoop();
}

void drawPad(int x, int c) {
  myFullRect(padX, 145, padLength, 4, 1 * c);
  myFullRect(padX + 4, 145, padLength - 8, 2, 2 * c);
}

void drawBall(int x, int y, int color) {
  myLine(x - 1, y - 2, x + 1, y - 2, color);
  myLine(x - 1, y + 2, x + 1, y + 2, color);
  myLine(x - 2, y - 1, x - 2, y + 1, color);
  myLine(x + 2, y - 1, x + 2, y + 1, color);
  myFullRect(x - 1, y - 1, 2, 2, color);
}

void drawLives(int lives) {
  for (int i = 1; i < 15; i++) {
    if (i <= lives) {
      drawBall(150 + i * 10, 172, 4);
    } else {
      drawBall(150 + i * 10, 172, 0);
    }
  }
}

int checkBrick(int x, int y, int c) {
  hit0 = 0;
  if (y < 130 && x > 22 + 4 && x < 280 - 4 && c != 7) {  //-------------- check if hit a brick -----------------
    drawBall(ballXold, ballYold, 0);
    if (vgaget(20 * int(x / 20) + 10, 8 * int((y - 10) / 8) + 10 + 4) > 0) {  //-------------- brick has been hit -----------------
      drawBall(ballXold, ballYold, 4);
      myFullRect(20 * int(x / 20), 8 * int((y - 10) / 8) + 10, 18, 6, 0);
      hit0 = 1;
    }
  } else {
    if (c == 1) {
      drawPad(padX, 1);
      if (myPos(ballX - padX - padLength / 2) > 8) { sgx = -sgx; }
    } else {
      if (y > 154) {  //--------------------- hit bottom floor -------------------------------
                      //--------------------------------- nothing -------------------------
      }
    }
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------- main loop of Breakout --------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
void BreakoutLoop() {
  NormalProcessInputs();

  if (state == 1) {  //--------------------- Breakout waiting for start ------------------------------------------------
    breakoutPad(1);
    if (button_down == 1) {
      delay(400);
      NormalProcessInputs();
      if (button_down == 1) {
        Canvas.setPenColor(0, 0, 0);
        Canvas.clear();
        clearInputs();
        choice = 0;
        delay(50);
        ChoiceMenu();
      }
    }
    if (button_cross == 1) {
      vx = 1;
      vy = 1;
      sgy = -1;
      if (breakoutSpeed > 10) {
        breakoutSpeed += -2;
      } else {
        breakoutSpeed += -1;
      }
      if (breakoutSpeed < 6) { breakoutSpeed = 6; }
      state = 2;
    }
  }

  if (state == 2) {  //--------------------- Breakout running ------------------------------------------------
    ballXold = ballX;
    ballYold = ballY;
    ballX = ballX + sgx * vx;
    ballY = ballY + sgy * vy;
    sgx0 = sgx;
    sgy0 = sgy;

    hitA = myGetPixel(ballX + 2 * sgx, ballY + 2 * sgy);
    hitB = myGetPixel(ballX - 2 * sgx, ballY + 2 * sgy);
    hitC = myGetPixel(ballX + 2 * sgx, ballY - 2 * sgy);
    if (hitA > 0) {
      if (hitB > 0) {
        checkBrick(ballX - 2 * sgx, ballY + 2 * sgy, hitB);
        hit += hit0;
        checkBrick(ballX + 2 * sgx, ballY + 2 * sgy, hitA);
        hit += hit0;
        {
          sgy = -sgy;
          ballY = ballY + sgy * vy;
        }
      }
      if (hitC > 0) {
        checkBrick(ballX + 2 * sgx, ballY - 2 * sgy, hitC);
        hit += hit0;
        checkBrick(ballX + 2 * sgx, ballY + 2 * sgy, hitA);
        hit += hit0;
        {
          sgx = -sgx;
          ballX = ballX + sgx * vx;
        }
      }
    } else {
      if (hitB > 0) {
        checkBrick(ballX - 2 * sgx, ballY + 2 * sgy, hitB);
        hit += hit0;
        hit0 = 0;
        {
          sgy = -sgy;
          ballY = ballY + sgy * vy;
        }
      }
      if (hitC > 0) {
        checkBrick(ballX + 2 * sgx, ballY - 2 * sgy, hitC);
        hit += hit0;
        hit0 = 0;
        {
          sgx = -sgx;
          ballX = ballX + sgx * vx;
        }
      }
    }
    hit0 = 0;

    if (hit > 0) {
      brickCounter += hit;
      brickCounterOld += hit;
      toneSafe(660, 30);
      myDrawNumber(70, 164, brickCounter, 4);
      hit = 0;

      if (brickCounterOld > 54) {  //--------------- all bricks destroyed ----------------------
        drawBall(ballXold, ballYold, 0);
        ballX = padX + padLength / 2;
        ballY = 142;
        ballXold = ballX;
        ballYold = ballY;
        breakoutLives += 1;
        toneSafe(880, 30);
        drawBreakoutIni();
        brickCounterOld = 0;
        state = 1;
      }
    }

    if (ballX > 288 || ballX < 16) {
      sgx = -sgx;
      ballX = ballX + 2 * sgx * vx;
    }
    if (ballY < 8) {
      sgy = -sgy;
      ballY = ballY + 2 * sgy * vy;
    }

    if (ballY > 156) {  //--------------------------- the ball hit the bottom and looss a life ------------------------------------
      drawBall(ballXold, ballYold, 0);
      ballX = padX + padLength / 2;
      ballY = 142;
      ballXold = ballX;
      ballYold = ballY;
      breakoutLives += -1;
      toneSafe(330, 200);
      drawLives(breakoutLives);
      if (breakoutSpeed >= 10) {
        breakoutSpeed += 2;
      } else {
        breakoutSpeed += 1;
      }
      state = 1;
    }

    drawBall(ballXold, ballYold, 0);
    drawBall(ballX, ballY, 4);
    delay(breakoutSpeed);

    breakoutPad(0);

    if (breakoutLives < 1) {  //----------------- Breakout game Over! ----------------------------
      brickCounterOld = 0;
      if (breakoutLives < 1) {
        button_down = 0;
        smoothRect(106, 87, 78, 20, 6, 1);
        myPrint("Game Over", 110, 90, 1);
        toneSafe(660, 200);
        toneSafe(330, 200);
        toneSafe(165, 200);
        toneSafe(82, 200);
        delay(500);
        myPrint("O: return to home", 80, 111, 7);
        myPrint("Any: restart game", 80, 126, 7);
        while (button == 0) {
          NormalProcessInputs();
          delay(50);
        }
      }
      if (button_circle == 1) {
        Canvas.setPenColor(0, 0, 0);
        Canvas.clear();
        choice = 0;
        clearInputs();
        delay(50);
        ChoiceMenu();
      } else {
        ballSpeed = 1;
        ballAngle = 45.;
        ballAngle0 = ballAngle;
        padX = 160;
        ballX = padX + padLength / 2;
        ballY = 142;
        levelBreakout = 1;
        breakoutLives = 3;
        breakoutSpeed = 18;
        brickCounter = 0;
        brickCounterOld = 0;
        Canvas.setPenColor(0, 0, 0);
        Canvas.clear();
        drawBall(padX + padLength / 2, ballY, 4);
        drawBreakoutIni();
        choice = 3;
      }
    }
  }
}
//------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------- end of the main loop of Breakout ---------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

void breakoutPad(bool ball) {  //----------------------- breakout pad motion control -----------------------------------
  if (button_left == 1) {
    drawPad(int(padX), 0);
    if (ball == 1) {
      ballX = int(padX) + padLength / 2;
      drawBall(ballX, ballY, 0);
    }
    if (button_left_old == 1) {
      padSpeed += -padSpeedStep;
      if (padSpeed < -padSpeedMax) { padSpeed = -padSpeedMax; }
    } else {
      padSpeed = -padSpeedStep;
      button_left_old = 1;
    }
    padX += padSpeed;
    if (padX <= 2 + padLength / 2) { padX = padLength / 2; }
    drawPad(int(padX), 1);
    if (ball == 1) {
      ballX = int(padX) + padLength / 2;
      drawBall(ballX, ballY, 4);
      delay(20);
    }
  } else {
    button_left_old = 0;
  }
  if (button_right == 1) {
    drawPad(int(padX), 0);
    if (ball == 1) {
      ballX = int(padX) + padLength / 2;
      drawBall(ballX, ballY, 0);
    }
    if (button_right_old == 1) {
      padSpeed += padSpeedStep;
      if (padSpeed > padSpeedMax) { padSpeed = padSpeedMax; }
    } else {
      padSpeed = padSpeedStep;
      button_right_old = 1;
    }
    padX += padSpeed;
    if (padX >= 278 - padLength / 2) { padX = 278 - padLength / 2; }
    drawPad(int(padX), 1);
    if (ball == 1) {
      ballX = int(padX) + padLength / 2;
      drawBall(ballX, ballY, 4);
      delay(20);
    }
  } else {
    button_right_old = 0;
  }
}
