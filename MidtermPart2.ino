const int rows[8] = {10, 12, 11, 8, A3, 7, 2, 5};
const int cols[8] = {A4, A7, A2, A0, 6, A1, 3, 9};

const int LEFT_BTN  = 4;
const int RIGHT_BTN = A5;

int matrix[8][8] = {0};
int playerX = 3;
bool gameOver = false;
bool justReset = true;

const int MAX_BULLETS = 3;
int bulletX[MAX_BULLETS];
int bulletY[MAX_BULLETS];
bool bulletActive[MAX_BULLETS];
unsigned long lastBulletTime = 0;
int bulletInterval = 200;

const int MAX_ALIENS = 3;
int alienX[MAX_ALIENS];
int alienY[MAX_ALIENS];
unsigned long lastAlienMove = 0;
int alienInterval = 500;

unsigned long lastLevelUp = 0;
int level = 1;

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
    digitalWrite(rows[i], LOW);
    digitalWrite(cols[i], HIGH);
  }
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(RIGHT_BTN, INPUT_PULLUP);
  randomSeed(analogRead(A1));

  delay(150);
  clearMatrix();
  showFrame();
  resetGame();
}

void loop() {
  if (gameOver) {
    rippleExplosion(); 
    resetGame();
    delay(300);
    return;
  }

  handleInput();
  autoFire();
  moveBullets();
  moveAliens();
  checkCollisions();

  if (!justReset){
    drawScene();
  }
  justReset = false;
  levelUp();
}

void handleInput() {
  static unsigned long lastPress = 0;
  unsigned long now = millis();
  if (now - lastPress < 120){
    return;
  }

  bool L = digitalRead(LEFT_BTN) == LOW;
  bool R = digitalRead(RIGHT_BTN) == LOW;

  if (L && !R && playerX > 0){
    playerX--;
  }
  if (R && !L && playerX < 7){
    playerX++;
  }
  lastPress = now;
}

void autoFire() {
  unsigned long now = millis();
  if (now - lastBulletTime < bulletInterval){
    return;
  }
  lastBulletTime = now;

  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!bulletActive[i]) {
      bulletActive[i] = true;
      bulletX[i] = playerX;
      bulletY[i] = 6;
      break;
    }
  }
}


void moveBullets() {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bulletActive[i]) {
      bulletY[i]--;
      if (bulletY[i] < 0){
        bulletActive[i] = false;
      }
    }
  }
}

void moveAliens() {
  unsigned long now = millis();
  if (now - lastAlienMove < alienInterval){ 
    return;
  }
  lastAlienMove = now;

  for (int i = 0; i < MAX_ALIENS; i++) {
    alienY[i]++;
    if (alienY[i] >= 7) { 
      gameOver = true;
      return;
    }
  }
}

void checkCollisions() {
  for (int a = 0; a < MAX_ALIENS; a++) {
    for (int b = 0; b < MAX_BULLETS; b++) {
      if (bulletActive[b] && alienX[a] == bulletX[b] && alienY[a] == bulletY[b]) {
        bulletActive[b] = false;
        alienY[a] = -random(2, 5);
        alienX[a] = random(0, 8);
      }
    }
  }
}

void levelUp() {
  unsigned long now = millis();
  if (now - lastLevelUp > 8000) {
    lastLevelUp = now;
    level++;
    if (alienInterval > 250){
      alienInterval -= 30;
    }
    if (bulletInterval > 100){
      bulletInterval -= 10;
    }
  }
}

void drawScene() {
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      matrix[r][c] = 0;
    }
  }
  matrix[7][playerX] = 1;

  for (int i = 0; i < MAX_ALIENS; i++){
    if (alienY[i] >= 0 && alienY[i] < 8){
      matrix[alienY[i]][alienX[i]] = 1;
    }
  }

  for (int i = 0; i < MAX_BULLETS; i++){
    if (bulletActive[i] && bulletY[i] >= 0 && bulletY[i] < 8){
      matrix[bulletY[i]][bulletX[i]] = 1;
    }
  }

  for (int r = 0; r < 8; r++) {
    digitalWrite(rows[r], HIGH);
    for (int c = 0; c < 8; c++){
      digitalWrite(cols[c], matrix[r][c] ? LOW : HIGH);
    }
    delay(1);
    for (int c = 0; c < 8; c++){
      digitalWrite(cols[c], HIGH);
    }
    digitalWrite(rows[r], LOW);
  }
}

void rippleExplosion() {
  int center[4][2] = {{3,3}, {3,4}, {4,3}, {4,4}};
  int maxRadius = 6;

  for (int r = 0; r <= maxRadius; r++) {
    clearMatrix();
    for (int y = 0; y < 8; y++) {
      for (int x = 0; x < 8; x++) {
        bool inCenter = false;
        for (int i = 0; i < 4; i++) {
          int cx = center[i][0];
          int cy = center[i][1];
          int dist = abs(x - cx) + abs(y - cy);
          if (dist == r){
            inCenter = true;
          }
        }
        if (inCenter) {
          matrix[y][x] = 1;
        }
      }
    }
    showDimFrame(60);
    delay(120);
  }

  for (int fade = 0; fade < 3; fade++) {
    clearMatrix();
    for (int y = 0; y < 8; y++){
      for (int x = 0; x < 8; x++){
        matrix[y][x] = 1;
      }
    }
    showDimFrame(40 - fade * 10);
    delay(100);
    clearMatrix();
    showDimFrame(20);
    delay(100);
  }

  clearMatrix();
  showFrame();
}

void showFrame() {
  for (int r = 0; r < 8; r++) {
    digitalWrite(rows[r], HIGH);
    for (int c = 0; c < 8; c++){
      digitalWrite(cols[c], matrix[r][c] ? LOW : HIGH);
    }
    delay(3);
    for (int c = 0; c < 8; c++){ 
      digitalWrite(cols[c], HIGH);
    }
    digitalWrite(rows[r], LOW);
  }
}

void showDimFrame(int repeats) {
  for (int i = 0; i < repeats; i++) {
    for (int r = 0; r < 8; r++) {
      digitalWrite(rows[r], HIGH);
      for (int c = 0; c < 8; c++){
        digitalWrite(cols[c], matrix[r][c] ? LOW : HIGH);
      }
      delayMicroseconds(200); // shorter = dimmer
      for (int c = 0; c < 8; c++){
        digitalWrite(cols[c], HIGH);
      }
      digitalWrite(rows[r], LOW);
    }
  }
}

void clearMatrix() {
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      matrix[r][c] = 0;
    }
  }
}

void resetGame() {
  playerX = 3;
  gameOver = false;
  justReset = true;

  for (int i = 0; i < MAX_ALIENS; i++) {
    alienX[i] = random(0, 8);
    alienY[i] = -random(2, 5);
  }

  for (int i = 0; i < MAX_BULLETS; i++){
    bulletActive[i] = false;
  }

  clearMatrix();
  showFrame();

  lastAlienMove = millis();
  lastBulletTime = millis();
  lastLevelUp = millis();
  level = 1;
}
