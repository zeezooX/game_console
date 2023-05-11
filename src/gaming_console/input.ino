bool data_button_right;
bool data_button_up;
bool data_button_left;
bool data_button_down;
bool data_button_cross;
bool data_button_circle;
bool data_button_ps;

void receiveInput() {
  if (PS4.isConnected()) {
    data_button_right = PS4.data.button.right || PS4.data.button.upright || PS4.data.button.downright;
    data_button_up = PS4.data.button.up || PS4.data.button.upleft || PS4.data.button.upright;
    data_button_left = PS4.data.button.left || PS4.data.button.upleft || PS4.data.button.downleft;
    data_button_down = PS4.data.button.down || PS4.data.button.downleft || PS4.data.button.downright;
    data_button_cross = PS4.data.button.cross;
    data_button_circle = PS4.data.button.circle;
    data_button_ps = PS4.data.button.ps;
  } else if (app) {
    while (BLE.available()) {
      int incoming = BLE.read();
      switch (incoming) {
        case 10:
          data_button_right = true;
          break;
        case 11:
          data_button_right = false;
          break;

        case 20:
          data_button_up = true;
          break;
        case 21:
          data_button_up = false;
          break;

        case 30:
          data_button_left = true;
          break;
        case 31:
          data_button_left = false;
          break;

        case 40:
          data_button_down = true;
          break;
        case 41:
          data_button_down = false;
          break;

        case 50:
          data_button_cross = true;
          break;
        case 51:
          data_button_cross = false;
          break;

        case 60:
          data_button_circle = true;
          break;
        case 61:
          data_button_circle = false;
          break;

        case 70:
          data_button_ps = true;
          break;
        case 71:
          data_button_ps = false;
          break;
      }
    }
  } else {
    data_button_right = false;
    data_button_up = false;
    data_button_left = false;
    data_button_down = false;
    data_button_cross = false;
    data_button_circle = false;
    data_button_ps = false;
  }
}

void SingleTapProcessInputs() {
  otherProcessInputs();

  if (button_right == 0) {
    if (button_right_old == 0) {
      button_right = data_button_right;
      if (button_right == 1) { button_right_old = 1; }
    } else {
      button_right_old = data_button_right;
    }
  } else {
    button_right = 0;
  }

  if (button_up == 0) {
    if (button_up_old == 0) {
      button_up = data_button_up;
      if (button_up == 1) { button_up_old = 1; }
    } else {
      button_up_old = data_button_up;
    }
  } else {
    button_up = 0;
  }

  if (button_left == 0) {
    if (button_left_old == 0) {
      button_left = data_button_left;
      if (button_left == 1) { button_left_old = 1; }
    } else {
      button_left_old = data_button_left;
    }
  } else {
    button_left = 0;
  }

  if (button_down == 0) {
    if (button_down_old == 0) {
      button_down = data_button_down;
      if (button_down == 1) { button_down_old = 1; }
    } else {
      button_down_old = data_button_down;
    }
  } else {
    button_down = 0;
  }

  button = button_up || button_down;
}

void TetrisProcessInputs() {
  otherProcessInputs();

  button_down_old = button_down;

  if (button_right == 0) {
    if (button_right_old == 0) {
      button_right = data_button_right;
      if (button_right == 1) { button_right_old = 1; }
    } else {
      button_right_old = data_button_right;
    }
  } else {
    button_right = 0;
  }

  if (button_up == 0) {
    if (button_up_old == 0) {
      button_up = data_button_up;
      if (button_up == 1) { button_up_old = 1; }
    } else {
      button_up_old = data_button_up;
    }
  } else {
    button_up = 0;
  }

  if (button_left == 0) {
    if (button_left_old == 0) {
      button_left = data_button_left;
      if (button_left == 1) { button_left_old = 1; }
    } else {
      button_left_old = data_button_left;
    }
  } else {
    button_left = 0;
  }

  button_down = data_button_down;
  if (button_down == 1) { delay(15); }
  button = button_up || button_down;
}

void NormalProcessInputs() {
  otherProcessInputs();

  if (data_button_up)
    button_up = true;
  else
    button_up = false;
  if (data_button_down)
    button_down = true;
  else
    button_down = false;
  if (data_button_left)
    button_left = true;
  else
    button_left = false;
  if (data_button_right)
    button_right = true;
  else
    button_right = false;
  button = button_right | button_up | button_left | button_down | button_cross | button_circle;
}

void otherProcessInputs() {
  receiveInput();
  if (data_button_cross)
    button_cross = true;
  else
    button_cross = false;
  if (data_button_circle)
    button_circle = true;
  else
    button_circle = false;
  if (data_button_ps)
    button_ps = true;
  else
    button_ps = false;
}

void clearInputs() {
  button_right = 0;
  button_up = 0;
  button_left = 0;
  button_down = 0;
  button = 0;
  button_square = 0;
  button_cross = 0;
  button_circle = 0;
  button_triangle = 0;
  button_ps = 0;
}
