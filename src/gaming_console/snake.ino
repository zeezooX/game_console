//------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------- This is the main loop of Snake --------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
void SnakeLoop() {

  NormalProcessInputs();

  if (state == 1) {  //-------------------- start screen ---------------------------------------------
    delay(10);
    NormalProcessInputs();
    if (button == 1) {
      button = 0;
      Canvas.clear();
      drawSnakeStartScreen();
      state = 2;
    }
  }

  if (state == 2) {  //--------------------- snake waiting for start ------------------------------------------------
    if (scoreSnake == scoreMax || scoreSnake == 0) {
      NormalProcessInputs();
    }
    if (button == 1) {
      scoreSnake = 0;
      SnakeDrawScore();
      button = 0;
      button_right = 0;
      button_up = 0;
      button_left = 0;
      button_down = 0;
      direct = 3;
      x = -1;
      y = 0;
      i = slength - 1;
      state = 3;
    }
  }

  if (state == 3) {
    NormalProcessInputs();
    //-------------------- change direction --------------------------------------------
    if (direct == 1) {
      if (button_up == 1) {
        x = 0;
        y = -1;
        direct = 2;
        button_down = 0;
      }
      if (button_down == 1) {
        x = 0;
        y = +1;
        direct = 4;
      }
    } else {
      if (direct == 2) {
        if (button_right == 1) {
          x = +1;
          y = 0;
          direct = 1;
          button_left = 0;
        }
        if (button_left == 1) {
          x = -1;
          y = 0;
          direct = 3;
        }
      } else {
        if (direct == 3) {
          if (button_up == 1) {
            x = 0;
            y = -1;
            direct = 2;
            button_down = 0;
          }
          if (button_down == 1) {
            x = 0;
            y = +1;
            direct = 4;
          }
        } else {
          if (direct == 4) {
            if (button_right == 1) {
              x = +1;
              y = 0;
              direct = 1;
              button_left = 0;
            }
            if (button_left == 1) {
              x = -1;
              y = 0;
              direct = 3;
            }
          }
        }
      }
    }

    //----------------------- delete tail --------------------------------------
    putBigPixel(sx[i], sy[i], 0);
    if (i > 0) {
      putBigPixel(sx[i - 1], sy[i - 1], 2);
    } else {
      putBigPixel(sx[slength - 1], sy[slength - 1], 2);
    }
    if (i == slength - 1) {
      sx[i] = sx[0] + x;
      sy[i] = sy[0] + y;
    } else {
      sx[i] = sx[i + 1] + x;
      sy[i] = sy[i + 1] + y;
    }

    //--------------------- out from border ------------------------------------
    if (sx[i] < x0Area + 1) { SnakeGameOver(); }
    if (sx[i] > x1Area - 1) { SnakeGameOver(); }
    if (sy[i] < y0Area + 1) { SnakeGameOver(); }
    if (sy[i] > y1Area - 1) { SnakeGameOver(); }

    //--------------------- check eating food -------------------------------------------------------------------------------------------------------------------------
    if (sx[i] > foodX - 3 && sx[i] < foodX + 3 && sy[i] > foodY - 3 && sy[i] < foodY + 3) {
      putBigPixel(foodX, foodY, 0);
      toneSafe(660, 30);
      SnakeFoodIni();
      SnakeDrawBorder();
      putBigPixel(foodX, foodY, 1);
      if (sx[i] == foodX || sy[i] == foodY) {
        slength = slength + 2 * deltaSnake;
        scoreSnake += 2;
      } else {
        slength = slength + deltaSnake;
        scoreSnake++;
      }
      if (scoreSnake > scoreMax) {
        speedDelay = int(speedDelay * 0.8);
        levelSnake += 1;
        toneSafe(880, 30);
        newMatch();
        drawSnakeIni();
        state = 2;
      }
      SnakeDrawScore();
    }
    putBigPixel(foodX, foodY, 1);

    //----------------------- increase head and Game Over -------------------------------------
    if (checkHit(sx[i], sy[i]) == 0) {
      putBigPixel(sx[i], sy[i], 2);
    } else  //-------- Sneke hit himself ----------------------------------------------------
    {
      SnakeGameOver();
    }
    putBigPixel(1, 1, 0);

    i--;
    if (i < 0) { i = slength - 1; }
    delay(speedDelay);
  }
}
//------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------- end of the main loop of Snake ------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

void SnakeFoodIni() {
  do {
    foodX = random(x1Area - x0Area - 4) + x0Area + 2;
    foodY = random(y1Area - y0Area - 4) + y0Area + 2;
    // ------------ choose the following for food up to the border -----------------------------------------
  } while (myGetPixel(foodX, foodY) > 1);
}

void SnakeDrawBorder() {
  myColor(4);
  Canvas.drawRectangle(x0Area - 1, y0Area - 1, x1Area + 1, y1Area + 1);
}

void SnakeDrawScore() {
  myPrint("Score", 35, 20, 2);
  myPrint("Level", 35, 60, 5);
  myColor(0);
  Canvas.setBrushColor(0, 0, 0);
  Canvas.fillRectangle(20, 40, 70, 52);
  Canvas.setBrushColor(0, 0, 0);
  Canvas.fillRectangle(20, 80, 70, 92);
  vgaPrintNumber(scoreSnake % 10, 55, 40, 4);
  vgaPrintNumber(levelSnake % 10, 55, 80, 4);
  if (scoreSnake > 9) {
    vgaPrintNumber(1, 45, 40, 4);
  }
  if (levelSnake > 9) {
    vgaPrintNumber(1, 45, 80, 4);
  }
}

int checkHit(int x, int y) {  //--------------------- check if snake hit himself -----------------------------------------------
  if (direct == 1) {
    if (myGetPixel(x + 1, y) == 2 || myGetPixel(x + 1, y - 1) == 2 || myGetPixel(x + 1, y + 1) == 2) { return 1; };
  }
  if (direct == 2) {
    if (myGetPixel(x + 1, y - 1) == 2 || myGetPixel(x, y - 1) == 2 || myGetPixel(x - 1, y - 1) == 2) { return 1; };
  }
  if (direct == 3) {
    if (myGetPixel(x - 1, y) == 2 || myGetPixel(x - 1, y - 1) == 2 || myGetPixel(x - 1, y + 1) == 2) { return 1; };
  }
  if (direct == 4) {
    if (myGetPixel(x + 1, y + 1) == 2 || myGetPixel(x, y + 1) == 2 || myGetPixel(x - 1, y + 1) == 2) { return 1; };
  }
  return 0;
}

//--------------- this is for the Snake game beginning window ---------------------------------------------------------------------------------------
void drawSnakeStartScreen() {
  Canvas.clear();
  SnakeDrawBorder();
  drawSnakeIni();
  SnakeDrawScore();
  button = 0;
  delay(200);
}

void drawSnakeIni() {
  for (byte i = 0; i < slength; i++) {
    sx[i] = x0Area + 100 + i;
    sy[i] = y0Area + 70;
    putBigPixel(sx[i], sy[i], 2);
  }
  for (byte i = slength; i < snakeMaxLength; i++) {
    sx[i] = 1;
    sy[i] = 1;
  }
  putBigPixel(foodX, foodY, 1);
}

//----------------- Snake re-inizialize new match -----------------------------------------------------------------------
void newMatch() {
  scoreSnake = 0;
  slength = slengthIni;
  i = slength - 1;
  for (int i = slength; i < snakeMaxLength; i++) {
    sx[i] = 0;
    sy[i] = 0;
  }
  Canvas.clear();
  SnakeDrawBorder();
  SnakeDrawScore();
  putBigPixel(foodX, foodY, 1);
}

//---------------- Snake Game Over -----------------------------------------------------------------------------------
void SnakeGameOver() {
  smoothRect(16, 118, 78, 20, 6, 1);
  myPrint("Game Over", 20, 121, 1);
  delay(100);
  toneSafe(660, 200);
  toneSafe(330, 200);
  toneSafe(165, 200);
  toneSafe(82, 200);
  button == 0;
  clearInputs();
  myPrint("  O: home", 12, 141, 7);
  myPrint("Any: retry", 12, 156, 7);
  while (button == 0) { NormalProcessInputs(); }
  speedDelay = 32;
  levelSnake = 1;
  state = 2;
  Canvas.setPenColor(0, 0, 0);
  Canvas.clear();
  if (button_circle == 1) {
    choice = 0;
  } else {
    SnakeFoodIni();
    newMatch();
    drawSnakeIni();
    choice = 2;
  }
}
