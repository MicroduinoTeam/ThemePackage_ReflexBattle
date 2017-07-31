//胜利音乐：机器猫
int tone_list[] = {262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988, 1046, 1175, 1318, 1397, 1568, 1760, 1967};
int music_3[] = {5, 8, 8, 10, 13, 10, 12, 12, 13, 12, 10, 11, 10, 9, 6, 9, 9, 11, 14, 14, 13, 12, 11, 11, 10, 6, 7, 8, 9, 0};
float rhythm_3[] = {0.5, 0.25, 0.5, 0.25, 0.5, 0.25, 1, 0.5, 0.25, 0.5, 0.25, 0.5, 0.25, 1, 0.5, 0.25, 0.5, 0.25, 0.5, 0.25, 0.5, 0.25, 1, 0.5, 0.25, 0.5, 1, 0.5, 3};
void playMusic() {
  for (int a = 0; music_3[a] != 0; a++) {
    if (music_3[a] != 22) {
      tone(BuzzerPin, tone_list[music_3[a] - 1]);
    }
    else {
      noTone(BuzzerPin);
    }
    delay(rhythm_3[a] * 300);
    noTone(BuzzerPin);
    delay(30);
  }
}
//“叮”声特效
void buzzerTinkle() {
  tone(BuzzerPin, 2000);
  delay(50);
  noTone(BuzzerPin);
  delay(100);
}
//“警报”声特效
void buzzerAlarm() {
  tone(BuzzerPin, 1200);
  delay(200);
  tone(BuzzerPin, 600);
  delay(200);
  tone(BuzzerPin, 1200);
  delay(200);
  tone(BuzzerPin, 600);
  delay(200);
  noTone(BuzzerPin);
}
