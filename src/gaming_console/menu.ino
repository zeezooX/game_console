//------------------------------------------------------ Menu -----------------------------------------------------------------
void ChoiceMenu() {
  clearInputs();
  myPrint("HOME", 133, 10, 7);
  smoothRect(60, 32, 180, 110 + 20, 10, 7);
  myPrint("Tetris     ", 90, 40, 6);
  myPrint("Snake      ", 90, 60, 5);
  myPrint("Breakout   ", 90, 80, 1);
  myPrint("Bomber      ", 90, 100, 2);
  myRect(190, 40, 12, 12, 7);
  myRect(190, 60, 12, 12, 7);
  myRect(190, 80, 12, 12, 7);
  myRect(190, 100, 12, 12, 7);
  if ((app || PS4.isConnected()) && connected_old == false) {
    connected_old = true;
    myFullRect(70, 130, 150, 30, 0);
    myPrint(" X: start  O: select", 70, 130, 7);
    myFullRect(155, 135, 10, 2, 0);
    myPrint("PS: reset  O: home", 70, 145, 7);
  } else if ((!app && !PS4.isConnected()) && connected_old == true) {
    connected_old = false;
    myFullRect(70, 130, 150, 30, 0);
    myPrint("Controller", 110, 130, 7);
    myPrint("not connected!", 95, 145, 7);
  }
  delay(100);
  SingleTapProcessInputs();
  if (button_down == 1) {
    myFullRect(191, 41 + (gameSelect - 1) * 20, 10, 10, 0);
    if (gameSelect < 4) {
      gameSelect += 1;
    } else {
      gameSelect = 1;
    }
    delay(100);
  }
  if (button_up == 1) {
    myFullRect(191, 41 + (gameSelect - 1) * 20, 10, 10, 0);
    if (gameSelect > 1) {
      gameSelect -= 1;
    } else {
      gameSelect = 4;
    }
    delay(100);
  }
  myFullRect(191, 41 + (gameSelect - 1) * 20, 10, 10, 4);
  if (button_cross == 1) {
    switch (gameSelect) {
      case 1:  // Tetris
        Canvas.setPenColor(0, 0, 0);
        Canvas.clear();
        drawGameScreen();
        TetrisDrawScore(score);
        noLoop = -1;
        score = 1;
        level = 1;
        scoreNew = score;
        fast = 14;
        clearInputs();
        myTime = 0;
        choice = 1;
        break;
      case 2:  // Snake
        SnakeFoodIni();
        speedDelay = 32;
        levelSnake = 1;
        newMatch();
        drawSnakeIni();
        state = 2;
        choice = 2;
        break;
      case 3:  // Breakout
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
        break;
      case 4:  // Bomber
        bomberScore = bomberScoreIni;
        bomberLives = 3;
        choice = 4;
        break;
      default:
        choice = 0;
        break;
    }
  }
}
//------------------------------------------------ End of Menu -----------------------------------------------------------------------
