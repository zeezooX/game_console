void toneSafe(int freq, int duration) {
  ledcWriteTone(0, freq);
  delay(duration);
  ledcWriteTone(0, 0);
}

void vgaPrintNumber(int number, int x, int y, byte color) {
  char scoreChar[2];
  sprintf(scoreChar, "%d", number);
  myPrint(scoreChar, x, y, color);
}

void myDrawNumber(int x, int y, int number, byte color) {
  if (number > 0) {
    int digits = int(log10(number)) + 1;
    char scoreChar[digits];
    sprintf(scoreChar, "%d", number);
    myFullRect(x + 8, y, -10 - 8 * (digits - 1), 12, 0);
    myPrint(scoreChar, x - 8 * (digits - 1), y, color);
  } else {
    myPrint("00", x, y, color);
  }
}

void draw_line(int x0, int y0, int x1, int y1, byte color) {
  myColor(color);
  Canvas.drawLine(x0, y0, x1, y1);
}

void myLine(int x0, int y0, int x1, int y1, int color) {
  myColor(color);
  Canvas.setPenColor(colA, colB, colC);
  Canvas.drawLine(x0, y0, x1, y1);
}

void putpixel(int x0, int y0, byte color) {
  myColor(color);
  Canvas.setPixel(x0, y0);
}

void putBigPixel(int x0, int y0, byte color) {
  myColor(color);
  //Canvas.setPixel(x0, y0);
  Canvas.setBrushColor(colA, colB, colC);
  Canvas.fillRectangle(x0 - 1, y0 - 1, x0 + 1, y0 + 1);
  Canvas.setBrushColor(0, 0, 0);
}

int myGetPixel(int x, int y) {  //--------------------- for Snake ----------------------------
  //Canvas.waitCompletion();
  int red = Canvas.getPixel(x, y).R;
  int green = Canvas.getPixel(x, y).G;
  int blue = Canvas.getPixel(x, y).B;
  if (red == 0 && green == 0 && blue == 0) { return 0; }
  if (red == 1 && green == 0 && blue == 0) { return 1; }
  if (red == 0 && green == 1 && blue == 0) { return 2; }
  if (red == 0 && green == 0 && blue == 1) { return 3; }
  if (red == 1 && green == 1 && blue == 0) { return 4; }
  if (red == 1 && green == 0 && blue == 1) { return 5; }
  if (red == 0 && green == 1 && blue == 1) { return 6; }
  if (red == 1 && green == 1 && blue == 1) { return 7; }
}

int vgaget(int x, int y) {  //----------------------- for Tetris ------------------------------
  Canvas.waitCompletion();
  int red = Canvas.getPixel(x + 2, y + 1).R;
  int green = Canvas.getPixel(x + 2, y + 1).G;
  int blue = Canvas.getPixel(x + 2, y + 1).B;
  if (red == 0 && green == 0 && blue == 0) { return 0; }
  if (red == 1 && green == 0 && blue == 0) { return 1; }
  if (red == 0 && green == 1 && blue == 0) { return 2; }
  if (red == 0 && green == 0 && blue == 1) { return 3; }
  if (red == 1 && green == 1 && blue == 0) { return 4; }
  if (red == 1 && green == 0 && blue == 1) { return 5; }
  if (red == 0 && green == 1 && blue == 1) { return 6; }
  if (red == 1 && green == 1 && blue == 1) { return 7; }
}

void myRect(int x0, int y0, int w, int h, int color) {
  myColor(color);
  Canvas.setPenColor(colA, colB, colC);
  Canvas.drawRectangle(x0, y0, x0 + w, y0 + h);
}

void myFullRect(int x0, int y0, int w, int h, int color) {
  myColor(color);
  Canvas.setBrushColor(colA, colB, colC);
  Canvas.fillRectangle(x0, y0, x0 + w, y0 + h);
  Canvas.setBrushColor(0, 0, 0);
}

void mySquare(int x0, int y0, int color) {  //--------------------------------------------- double color inner version ----------------------------------
  myColor(color);
  Canvas.setBrushColor(colA, colB, colC);  //--------------------------------------------------- colore riempimento e sfondo --------------------------
  Canvas.fillRectangle(x0, y0 + 1, x0 + squareX - 2, y0 + squareY);
  if (color != 0) { myColor(color + 1); }
  if (color == 7) { myColor(2); }
  Canvas.setPenColor(colA, colB, colC);
  Canvas.setPixel(x0 + squareX / 2, y0 + squareY / 2);
  Canvas.setPixel(x0 + squareX / 2 - 1, y0 + squareY / 2);
  Canvas.setPixel(x0 + squareX / 2, y0 + squareY / 2 + 1);
  Canvas.setPixel(x0 + squareX / 2 - 1, y0 + squareY / 2 + 1);
  Canvas.setBrushColor(0, 0, 0);
}

void mySquare4(int x0, int y0, int color) {  //--------------------------------------------- double color border + inner version ------------------------
  myColor(color);
  Canvas.setBrushColor(colA, colB, colC);  //--------------------------------------------------- colore riempimento e sfondo --------------------------
  Canvas.fillRectangle(x0 + 1, y0 + 2, x0 + squareX - 3, y0 + 1 + squareY - 2);
  if (color != 0) { myColor(color + 1); }
  if (color == 7) { myColor(2); }
  Canvas.setPenColor(colA, colB, colC);
  Canvas.drawRectangle(x0, y0 + 1, x0 + squareX - 2, y0 + squareY);
  Canvas.setPixel(x0 + squareX / 2, y0 + squareY / 2);
  Canvas.setPixel(x0 + squareX / 2 - 1, y0 + squareY / 2);
  Canvas.setPixel(x0 + squareX / 2, y0 + squareY / 2 + 1);
  Canvas.setPixel(x0 + squareX / 2 - 1, y0 + squareY / 2 + 1);
  Canvas.setBrushColor(0, 0, 0);
}

void mySquare3(int x0, int y0, int color) {  //--------------------------------------------- double color border version --------------------------------
  myColor(color);
  Canvas.setBrushColor(colA, colB, colC);  //--------------------------------------------------- colore riempimento e sfondo --------------------------
  Canvas.fillRectangle(x0 + 1, y0 + 2, x0 + squareX - 3, y0 + 1 + squareY - 2);
  if (color != 0) { myColor(color + 1); }
  if (color == 7) { myColor(2); }
  Canvas.setPenColor(colA, colB, colC);
  Canvas.drawRectangle(x0, y0 + 1, x0 + squareX - 2, y0 + squareY);
  Canvas.setBrushColor(0, 0, 0);
}

void mySquare2(int x0, int y0, int color) {  //------------------------------------------------------- simple version -----------------------------------
  myColor(color);
  Canvas.setBrushColor(colA, colB, colC);
  Canvas.fillRectangle(x0, y0 + 1, x0 + squareX - 2, y0 + squareY);
  Canvas.setBrushColor(0, 0, 0);
}

void myColor(int color) {
  color = color % 8;
  if (color == 0) {
    colA = 0;
    colB = 0;
    colC = 0;
  }
  if (color == 1) {
    colA = 1;
    colB = 0;
    colC = 0;
  }
  if (color == 2) {
    colA = 0;
    colB = 1;
    colC = 0;
  }
  if (color == 3) {
    colA = 0;
    colB = 0;
    colC = 1;
  }
  if (color == 4) {
    colA = 1;
    colB = 1;
    colC = 0;
  }
  if (color == 5) {
    colA = 1;
    colB = 0;
    colC = 1;
  }
  if (color == 6) {
    colA = 0;
    colB = 1;
    colC = 1;
  }
  if (color == 7) {
    colA = 1;
    colB = 1;
    colC = 1;
  }
  Canvas.setPenColor(colA, colB, colC);
}

void myColorMandelbrot(int color) {
  if (color != 0) { color = color % 7 + 1; }  //------------- version for Mandelbrot ---------------------
  if (color == 0) {
    colA = 0;
    colB = 0;
    colC = 0;
  }
  if (color == 1) {
    colA = 1;
    colB = 0;
    colC = 0;
  }
  if (color == 2) {
    colA = 0;
    colB = 1;
    colC = 0;
  }
  if (color == 3) {
    colA = 0;
    colB = 0;
    colC = 1;
  }
  if (color == 4) {
    colA = 1;
    colB = 1;
    colC = 0;
  }
  if (color == 5) {
    colA = 1;
    colB = 0;
    colC = 1;
  }
  if (color == 6) {
    colA = 0;
    colB = 1;
    colC = 1;
  }
  if (color == 7) {
    colA = 1;
    colB = 1;
    colC = 1;
  }
  Canvas.setPenColor(colA, colB, colC);
}

void setPrint(int x, int y, int color) {
  myColor(color);
  Canvas.setPenColor(colA, colB, colC);
  Canvas.moveTo(x, y);
}

void smoothRect(int x0, int y0, int w, int h, int r, int color) {  //----- 1.6 comes from the resolution ratio - 320/200 --------------
  myLine(x0 + 1.6 * r, y0 - 1, x0 + w - 1.6 * r, y0 - 1, color);
  myLine(x0 + 1.6 * r, y0 + h, x0 + w - 1.6 * r, y0 + h, color);
  myLine(x0 - 1, y0 + r, x0 - 1, y0 + h - r, color);
  myLine(x0 + w, y0 + r, x0 + w, y0 + h - r, color);
  myColor(color);
  for (int i = 0; i <= 25; i++) {
    Canvas.setPenColor(colA, colB, colC);
    Canvas.setPixel(x0 + w - r * 1.6 * (1 - cos(i / 25. * 3.1415 / 2.)), y0 + r * (1 - sin(i / 25. * 3.1415 / 2.)));
    Canvas.setPixel(x0 + r * 1.6 * (1 - cos(i / 25. * 3.1415 / 2.)), y0 + r * (1 - sin(i / 25. * 3.1415 / 2.)));
    Canvas.setPixel(x0 + w - r * 1.6 * (1 - cos(i / 25. * 3.1415 / 2.)), y0 + h - r * (1 - sin(i / 25. * 3.1415 / 2.)));
    Canvas.setPixel(x0 + r * 1.6 * (1 - cos(i / 25. * 3.1415 / 2.)), y0 + h - r * (1 - sin(i / 25. * 3.1415 / 2.)));
  }
}

void myPrint(char* str, byte x, byte y, byte color) {
  Canvas.selectFont(Canvas.getPresetFontInfo(40, 14));
  myColor(color);
  Canvas.drawText(x, y, str);
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int myPos(int x) {
  if (x < 0) {
    return -x;
  } else {
    return x;
  }
}
