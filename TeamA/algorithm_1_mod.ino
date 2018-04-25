#include "TimerObject.h"

int sensorPin = 5;          // 마이크 핀
int outputPin = 7;          // 출력 핀
int thresholdH = 20;        // high threshold; Th(H)
int thresholdL = 2;         // low threshold; Th(L)
int tc = 50;                // clap time; T(c)
int tw = 100;               // 박수간 최소 간격
int match[] = {0, 800, 400} // 박수 패턴; clap, 800ms 대기, clap, 400ms 대기, clap
int claps[10]               // 박수 카운터; 값 = 박수간 간격; 100ms 단위로 반올림됨
int cc = 0                  // 박수 횟수
int tb = 0;                 // 박수간 간격
TimerObject timeout;

void setup()
{
    timeout = new TimerObject(2000, reset());
    ...
}

void reset()
{
    memset(clap, 0, sizeof(clap));    // 타이머 완료 시 박수 카운터 초기화
    cc = 0
    tb = 0
}

void loop()
{
    if (analogRead(sensorPin) > thresholdH) {        // 값이 최대값보다 높은 지 확인
        if (timeout.isEnabled()) {                   // 타이머가 켜져 있을 경우
            tb = round(timeout.getInterval(), 1);    // 소수점 1번째 자리까지 반올림
            timeout.Stop();                          // 타이머 멈춤
        }
        delay(tc);                                   // T(c) 동안 대기
        if (analogRead(sensorPin) < thresholdL) {    // 값이 최소값보다 낮은 지 확인
            claps[cc] = tb;                          // 박수 카운터에 박수간 간격 추가
            timeout.Start();                         // 타이머 시작
            delay(tw);
        }
    }
    if (match == clap) {                             // 패턴과 입력 값이 일치할 경우
        digitalWrite(outputPin, write(!outputPin));  // 출력 핀을 작동한다
        reset();
    }
}