//
//  Clap-to-switch; Arduino/AVR Project
//  for Hallym University Capstone Design
//
//  Written by Kayman Kim
//
//  Last updated 05-21-2018
//
//  cts_03.ino
//

#include "TimerObject.h"
#include "SoftwareServo.h"

// pin variables
int buttonPin = 2;
int r_ledPin = 4;
int g_ledPin = 0;
int servoPin = 1;
int micPin = 3;

SoftwareServo servo;            // 서보
int servoStatus = 0;            // 서보 상태
TimerObject *timeout;           // 타이머
int onRecord = 0;               // 기록 상태
int thresholdH = 600;           // high threshold; Th(H)
int thresholdL = 550;           // low threshold; Th(L)
int tc = 50;                    // clap sound wave time; T(c)
int tw = 100;                   // 대기 시간; T(w)
int tr = 200;                   // 박수 간격; T(r)
int match[10] = {0, 800, 200};  // 박수 패턴; clap, 800ms 대기, clap, 400ms 대기, clap
int ml = 3;                     // 패턴 길이
int claps[10] = {0};            // 박수 입력
int cc = 0;                     // 입력 박수 횟수
int tb = 0;                     // 박수 간 간격(ms)

void setup() {
    // Serial.begin(115200);

    servo.attach(servoPin);
    moveServo();
    
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(r_ledPin, OUTPUT);                        // 핀 모드 설정; LED핀, 출력
    pinMode(g_ledPin, OUTPUT);                       // 핀 모드 설정; LED핀, 출력

    timeout = new TimerObject(2000, &callback);     // 타이머 생성; 2초
}

void led_blink(int ledPin, int count) {
    for (int i = 0; i < count; i++) {
        digitalWrite(ledPin, HIGH);
        delay(100);
        digitalWrite(ledPin, LOW);
        delay(100);
    }
}

void callback() {               // 초기화 함수; 타이머 시간 도달 시 발생
    if (onRecord){
        memcpy(match, claps, 10);
        onRecord = 0;
        led_blink(r_ledPin, 3);
        // Serial.println("new pattern set");
    }
    
    memset(claps, 0, sizeof(int) * 10);
    cc = 0;
    tb = 0;
    timeout->Stop();
    led_blink(g_ledPin, 3);
    // Serial.println("clap reseted");
}

int round_t(int t, int v) {     // 정수 반올림 함수
    return (int)(round((float)t / v) * v);
}

void printArray(int *arr) {     // 배열 출력
    // Serial.print("{");
    for (int i = 0; i < 10; i++) {
        // Serial.print(arr[i]);
        // Serial.print(", ");
    }
    // Serial.print("}");
}

bool checkMatch(int *match, int *claps) {   // 패턴 검사
    for (int i = 0; i < 10; i++) {
        if (match[i] != claps[i])
            return false;
    }
    return true;
}

void moveServo() {
    if (servoStatus == 0)  { servo.write(80); servoStatus = 1; }
    else                   { servo.write(10); servoStatus = 0; }
}

void loop() {
    if (digitalRead(buttonPin) == HIGH && onRecord == 0) {
        // Serial.write("record mode is on");
        onRecord = 1;
        led_blink(r_ledPin, 5);
        digitalWrite(r_ledPin, HIGH);
    }
      
    if (analogRead(micPin) > thresholdH) {
        if (timeout->isEnabled()) {
            tb = round_t(timeout->getCurrentTime(), 200);
            timeout->Stop();  
        }
        delay(tc);
        if (analogRead(micPin) < thresholdL) {
            claps[cc++] = tb;
            // Serial.print("clap count:");
            // Serial.print(cc);
            // Serial.print(", clap delay: ");
            // Serial.println(tb);
            printArray(claps);
            // Serial.println();
            timeout->Start();
            digitalWrite(g_ledPin, HIGH);
            delay(tw);
            digitalWrite(g_ledPin, LOW);
        }
    }
    
    if (checkMatch(match, claps) && onRecord == 0) {
        // Serial.println("pattern checked");
        moveServo();
        digitalWrite(r_ledPin, HIGH);
        delay(500);
        digitalWrite(r_ledPin, LOW);
        callback();
    }
    
    SoftwareServo::refresh();
    timeout->Update();
}
