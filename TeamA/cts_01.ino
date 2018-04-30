//
//  Clap-to-switch; Arduino/AVR Project
//  for Hallym University Capstone Design
//
//  Written by Kayman Kim
//
//  Last updated 04-29-2018
//
//  cts_01.ino
//

#include "TimerObject.h"
#include <Servo.h>

int sensorPin = 5;              // 마이크 핀
Servo servo;                    // 서보
int buttonPin = 7;              // 버튼 핀
int thresholdH = 15;            // high threshold; Th(H)
int thresholdL = 2;             // low threshold; Th(L)
int tc = 50;                    // clap time; T(c)
int tw = 50;                    // 박수간 최소 간격
int match[10] = {0, 800, 400};  // 박수 패턴; clap, 800ms 대기, clap, 400ms 대기, clap
int claps[10] = {0}             // 박수 패턴 입력; 100ms 단위로 반올림됨
int cc = 0                      // 박수 횟수
int tb = 0;                     // 박수 간격
TimerObject *timeout;           // 타이머
int onRecord = 0                // 기록 상태

void setup()
{
    timeout = new TimerObject(2000, callback());    // 타이머 생성; 2초 타임아웃
    pinMode(sensorPin, INPUT);                      // 마이크 핀을 입력 모드로
    pinMode(buttonPin, INPUT);                      // 버튼 핀을 입력 모드로
    servo.attach(6);                                // 서보 핀 연결
}

void callback()
{
    if (onRecord)                               // 기록 모드가 켜져 있을 경우
    {
        memcpy(match, claps, 10);               // 입력된 패턴을 매치 패턴에 입력 
        onRecord = 0;                           // 기록 모드 종료
    }

    memset(clap, 0, sizeof(clap));              // 박수 초기화
    cc = tb = 0;                                // 박수 횟수와 간격 초기화
}

void moveServo()
{
    if (servo.read() == 0)  servo.write(90);    // 서보가 0일 경우, 90도
    else                    servo.write(0);     // 이외에는 0도
}

void loop()
{
    if (digitalRead(buttonPin) == HIGH && onRecord == 0)
        onRecord = 1;
        
    if (analogRead(sensorPin) > thresholdH) {       // 값이 최대값보다 높은 지 확인
        if (timeout->isEnabled()) {                 // 타이머가 켜져 있을 경우
            tb = round(timeout->getInterval(), 1);  // 소수점 1번째 자리까지 반올림
            timeout->Stop();                        // 타이머 멈춤
        }
        delay(tc);                                  // T(c) 동안 대기
        if (analogRead(sensorPin) < thresholdL) {   // 값이 최소값보다 낮은 지 확인
            claps[cc] = tb;                         // 박수 카운터에 박수간 간격 추가
            timeout->Start();                       // 타이머 시작
            delay(tw);
        }
    }
    
    if (match == clap) {                            // 패턴과 입력 값이 일치할 경우
        moveServo();                                // 서보 작동
        reset();                                    // 변수 초기화   
    }

    timeout->Update();                              // 타이머 업데이트
}