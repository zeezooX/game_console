//-----------------------------------------------------------------------------------------------
//--------------------- This is the main loop of Tetris ---------------------------------------
//-----------------------------------------------------------------------------------------------
void TetrisLoop() {
  TetrisProcessInputs();

  if (noLoop < 1) {  // --------------- to generate new Tetraminos --------------------------------
    blockN = blockNext;
    if (noLoop == -1) {             // -------------- only at the game beginning  -------------------------
      blockN = 2 + int(random(6));  // -------------- tetraminos "O" is excluded -----------------
    }
    drawGameScreen();
    TetrisDrawScore(score);
    blockNext = 1 + int(random(7));
    blockDef(blockNext);
    drawBlockNext();
    blockDef(blockN);
    x = 57;
    y = 5;
    button_right = 1;
    noLoop = 1;
  }
  if (button_up == 1) {  // ------------------------ rotation -------------------------
    if (button_up == 1) { rotationDirection = 1; }
    delBlock();
    blockRotation(rotationDirection);
    checkBlockRotation();
  }
  if (button_right == 1 || button_left == 1) {  // ------- translation ----------------------
    if (button_right == 1) { delta = 3; }
    if (button_left == 1) { delta = -3; }
    delBlock();
    checkBlockTranslation();
  }
  myTime++;
  if (myTime % fast > fast - 2 || button_down == 1) {  // --- Tetraminos falling ----------
    if (fast < 3) { fast = 2; }
    y = y + 2;
    delBlock();
    replaceBlock();
  } else {
    delay(10 + 2 * fast);
  }
}
//-----------------------------------------------------------------------------------------------
//--------------------- This is the end of the main loop of Tetris ----------------------------------------
//-----------------------------------------------------------------------------------------------

void TetrisDrawScore(int i) {
  if (i > 60) {
    level = level + 1;
    score = 0;
    i = 0;
    if (fast > 5) {
      fast = fast - 2;
    } else {
      fast = fast - 1;
    }
    if (fast < 3) { fast = 2; }
  }
  smoothRect(208, 77, 62, 30, 8, 2);
  Canvas.drawText(222, 80, "Level");
  myDrawNumber(234, 93, level, 2);
  smoothRect(208, 124, 62, 30, 8, 2);
  Canvas.drawText(222, 126, "Score");
  myDrawNumber(245, 139, scoreNew * 10, 2);
}

void drawBorder() {  //-------------------- Tetris -------------------------------
  myRect(120, 4, squareX * (myColumns - 1) - 3, squareY * myRaws + 19, 4);
  myRect(119, 3, squareX * (myColumns - 1) - 1, squareY * myRaws + 21, 3);
  myRect(118, 2, squareX * (myColumns - 1) + 1, squareY * myRaws + 23, 2);
  myRect(117, 1, squareX * (myColumns - 1) + 3, squareY * myRaws + 25, 7);
  Canvas.drawText(220, 16, "Next");
  smoothRect(210, 10, 50, 40, 10, 4);
}

// --------------------- this is for the beginning game window ------------------------
void drawStartScreen() {
  drawBorder();
  drawGameScreen();
  button = 0;
  delay(200);
}

// ---------------------- this is the main function to draw the game screen -----------
void drawGameScreen() {
  drawBorder();
}


// ----------------------- Tetriminos definition --------------------------------------
void blockDef(int i) {
  if (i == 1) {
    // O
    block[0][0] = 0;
    block[0][1] = 0;
    block[1][0] = 1;
    block[1][1] = 0;
    block[2][0] = 0;
    block[2][1] = 1;
    block[3][0] = 1;
    block[3][1] = 1;
    color = 1;
  }
  if (i == 2) {
    // L
    block[0][0] = -1;
    block[0][1] = 0;
    block[1][0] = 0;
    block[1][1] = 0;
    block[2][0] = 1;
    block[2][1] = 0;
    block[3][0] = -1;
    block[3][1] = 1;
    color = 2;
  }
  if (i == 3) {
    // J
    block[0][0] = -1;
    block[0][1] = 0;
    block[1][0] = 0;
    block[1][1] = 0;
    block[2][0] = 1;
    block[2][1] = 0;
    block[3][0] = 1;
    block[3][1] = 1;
    color = 3;
  }
  if (i == 4) {
    // I
    block[0][0] = -1;
    block[0][1] = 0;
    block[1][0] = 0;
    block[1][1] = 0;
    block[2][0] = 1;
    block[2][1] = 0;
    block[3][0] = 2;
    block[3][1] = 0;
    color = 4;
  }
  if (i == 5) {
    // S
    block[0][0] = -1;
    block[0][1] = 0;
    block[1][0] = 0;
    block[1][1] = 0;
    block[2][0] = 0;
    block[2][1] = 1;
    block[3][0] = 1;
    block[3][1] = 1;
    color = 5;
  }
  if (i == 6) {
    // Z
    block[0][0] = -1;
    block[0][1] = 1;
    block[1][0] = 0;
    block[1][1] = 1;
    block[2][0] = 0;
    block[2][1] = 0;
    block[3][0] = 1;
    block[3][1] = 0;
    color = 6;
  }
  if (i == 7) {
    // T
    block[0][0] = -1;
    block[0][1] = 0;
    block[1][0] = 0;
    block[1][1] = 0;
    block[2][0] = 0;
    block[2][1] = 1;
    block[3][0] = 1;
    block[3][1] = 0;
    color = 7;
  }
}

// -------------------------- expansion for 4:3 monitors ------------------------------
void blockExtension() {
  for (int i = 0; i < 4; i++) {
    blockExt[0][0] = block[0][0] * 3;
    blockExt[0][1] = block[0][1] * 2;
    blockExt[1][0] = block[1][0] * 3;
    blockExt[1][1] = block[1][1] * 2;
    blockExt[2][0] = block[2][0] * 3;
    blockExt[2][1] = block[2][1] * 2;
    blockExt[3][0] = block[3][0] * 3;
    blockExt[3][1] = block[3][1] * 2;
  }
}

void blockRotation(int rotationDirection) {
  for (int i = 0; i < 4; i++) {
    blockOld[0][0] = block[0][0];
    blockOld[0][1] = block[0][1];
    blockOld[1][0] = block[1][0];
    blockOld[1][1] = block[1][1];
    blockOld[2][0] = block[2][0];
    blockOld[2][1] = block[2][1];
    blockOld[3][0] = block[3][0];
    blockOld[3][1] = block[3][1];
  }
  for (int i = 0; i < 4; i++) {
    block[0][0] = blockOld[0][1] * rotationDirection;
    block[0][1] = -blockOld[0][0] * rotationDirection;
    block[1][0] = blockOld[1][1] * rotationDirection;
    block[1][1] = -blockOld[1][0] * rotationDirection;
    block[2][0] = blockOld[2][1] * rotationDirection;
    block[2][1] = -blockOld[2][0] * rotationDirection;
    block[3][0] = blockOld[3][1] * rotationDirection;
    block[3][1] = -blockOld[3][0] * rotationDirection;
  }
}
void blockTranslation(int x, int y) {
  for (int i = 0; i < 4; i++) {
    blockTr[0][0] = blockExt[0][0] + x;
    blockTr[0][1] = blockExt[0][1] + y;
    blockTr[1][0] = blockExt[1][0] + x;
    blockTr[1][1] = blockExt[1][1] + y;
    blockTr[2][0] = blockExt[2][0] + x;
    blockTr[2][1] = blockExt[2][1] + y;
    blockTr[3][0] = blockExt[3][0] + x;
    blockTr[3][1] = blockExt[3][1] + y;
  }
}

void delBlock() {
  if (noDelete == 1) {
    noDelete = 0;
  } else {
    for (int i = 0; i < 4; i++) {
      mySquare(blockTr[i][0] * 2 + 31, blockTr[i][1] * 3 + 1, 0);
    }
  }
}

void drawBlock() {
  for (int i = 0; i < 4; i++) {
    mySquare(blockTr[i][0] * 2 + 31, blockTr[i][1] * 3 + 1, color);
  }
  for (int i = 0; i < 4; i++) {
    blockTmp[0][0] = blockTr[0][0];
    blockTmp[0][1] = blockTr[0][1];
    blockTmp[1][0] = blockTr[1][0];
    blockTmp[1][1] = blockTr[1][1];
    blockTmp[2][0] = blockTr[2][0];
    blockTmp[2][1] = blockTr[2][1];
    blockTmp[3][0] = blockTr[3][0];
    blockTmp[3][1] = blockTr[3][1];
  }
}

void drawBlockTmp() {
  for (int i = 0; i < 4; i++) {
    mySquare(blockTmp[i][0] * 2 + 31, blockTmp[i][1] * 3 + 1, color);
  }
}

void checkBlock() {
  busy = 0;
  for (int i = 0; i < 4; i++) {
    busy = busy + vgaget(2 * blockTr[i][0] + 31, 3 * blockTr[i][1] + 2);
  }
}

void replaceBlock() {
  blockExtension();
  blockTranslation(x, y);
  checkBlock();
  if (busy == 0) {
    drawBlock();
  } else  // ---------- else is run if the block cannot get down  -----------------
  {
    drawBlockTmp();
    checkForFullLine();  // ---- check if the line is filled when the block cannot get down anymore ----------------------
    noLoop = 0;
    noDelete = 1;
    if (y < 8) {
      gameOver();
    }
  }
}

void gameOver() {  // ------------------------------------------- Tetris Game Over ! --------------------------------------------------
  noLoop = -1;
  score = 1;
  level = 1;
  scoreNew = score;
  fast = 14;
  clearInputs();
  myTime = 0;
  smoothRect(20, 91, 78, 20, 6, 1);
  myPrint("Game Over", 24, 94, 1);
  delay(300);
  toneSafe(660, 200);
  toneSafe(330, 200);
  toneSafe(165, 200);
  toneSafe(82, 200);
  myPrint("  O: home", 16, 114, 7);
  myPrint("Any: retry", 16, 129, 7);
  while (button == 0) {
    NormalProcessInputs();
    delay(100);
  }
  clearInputs();
  Canvas.setPenColor(0, 0, 0);
  Canvas.clear();
  if (button_circle == 1) {
    choice = 0;
  } else {
    choice = 1;
  }
}

void drawBlockNext() {  // ----- draw next block on the right side --------------------------------
  blockExtension();
  blockTranslation(100, 10);
  Canvas.setPenColor(0, 0, 0);
  Canvas.setBrushColor(0, 0, 0);
  Canvas.fillRectangle(221, 28, 252, 46);
  Canvas.setBrushColor(0, 0, 0);
  drawBlock();
}

void checkBlockTranslation() {
  x = x + delta;
  blockExtension();
  blockTranslation(x, y);
  checkBlock();
  if (busy == 0) {
    drawBlock();
  } else {
    x = x - delta;
    blockExtension();
    blockTranslation(x, y);
    drawBlock();
  }
}

void checkBlockRotation() {
  blockExtension();
  blockTranslation(x, y);
  checkBlock();
  if (busy == 0) {
    drawBlock();
  } else {
    rotationDirection = -rotationDirection;
    blockRotation(rotationDirection);
    blockExtension();
    blockTranslation(x, y);
    drawBlock();
  }
}

void checkForFullLine() {  // --------------------- check if the line is full and must be deleted --------------
  for (int i = 0; i < 4; i++) {
    for (int j = 45; j < 76; j += 3) {
      if (vgaget(2 * j + 32, 3 * blockTmp[i][1] + 3) > 0) { k++; }
    }
    if (k == 11) {  // ------------------------------ line is full and must be deleted ----------------------------------------------------------
      Canvas.setBrushColor(0, 0, 0);
      Canvas.fillRectangle(121, blockTmp[i][1] * 3 + 2, 120 + (squareX - 1) * 11, blockTmp[i][1] * 3 + 1 + squareY);
      yLineTmp[yCounter] = blockTmp[i][1];
      yLine[yCounter] = blockTmp[i][1];
      yCounter++;
      toneSafe(660, 30);
    }
    k = 0;
  }
  if (yLineTmp[yCounter - 1] < yLine[0]) {
    for (int i = 0; i < yCounter; i++) {  // ------------- inversion ---------------------------------------
      yLine[i] = yLineTmp[yCounter - i - 1];
    }
  }
  for (int i = 0; i < yCounter; i++) {  // --------------- block translation to lower position --------------
    for (int y = yLine[i] - 2; y > 0; y = y - 2) {
      for (int x = 45; x < 76; x += 3) {
        colorOld = vgaget(2 * x + 32, 3 * y + 2);
        if (colorOld > 0) {
          mySquare(x * 2 + 31, y * 3 + 1, 0);
          mySquare(x * 2 + 31, (y + 2) * 3 + 1, colorOld);
        }
      }
    }
  }
  if (yCounter != 0) {
    score += 2 * int(pow(2, yCounter)) * level;
    scoreNew += 2 * int(pow(2, yCounter)) * level;
    toneSafe(990, 30);
  }
  TetrisDrawScore(score);
  yCounter = 0;
}
