//
//  Clap-to-switch; Arduino/AVR Project
//  for Hallym University Capstone Design
//
//  Written by Kayman Kim
//
//  Last updated 04-29-2018
//
//  cts_02.ino
//

#include "TimerObject.h"

int ledPin = 7;
int ledPin2 = 8;
int thresholdH = 610;            // high threshold; Th(H)
int thresholdL = 550;            // low threshold; Th(L)
int tc = 50;                    // clap sound wave time; T(c)
int tw = 100;                   // 대기 시간; T(w)
int tr = 200;                   // 박수 간격; T(r)
int match[10] = {0, 800, 200};  // 박수 패턴; clap, 800ms 대기, clap, 400ms 대기, clap
int ml = 3;                     // 패턴 길이
int claps[10] = {0};            // 박수 입력
int cc = 0;                     // 입력 박수 횟수
int tb = 0;                     // 박수 간 간격(ms)
TimerObject *timeout;           // 타이머

void setup() {
    Serial.begin(115200);
    
    timeout = new TimerObject(2000, &callback);     // 타이머 생성; 2초
    pinMode(ledPin, OUTPUT);                        // 핀 모드 설정; LED핀, 출력
    pinMode(ledPin2, OUTPUT);                       // 핀 모드 설정; LED핀, 출력
}

void callback() {               // 초기화 함수; 타이머 시간 도달 시 발생
    memset(claps, 0, sizeof(int) * 10);
    cc = 0;
    tb = 0;
    timeout->Stop();
    Serial.println("clap reseted");
}

int round_t(int t, int v) {     // 정수 반올림 함수
    return (int)(round((float)t / v) * v);
}

void printArray(int *arr) {     // 배열 출력
    Serial.print("{");
    for (int i = 0; i < 10; i++) {
        Serial.print(arr[i]);
        Serial.print(", ");
    }
    Serial.print("}");
}

bool checkMatch(int *match, int ml, int *claps) {   // 패턴 검사
    for (int i = 0; i < ml; i++) {
        if (match[i] != claps[i])
            return false;
    }
    return true;
}

void loop() {
    Serial.println(analogRead(A0));
    delay(50);
}
