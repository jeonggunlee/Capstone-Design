https://github.com/cobaltp/clap-to-switch

Clap-to-Switch Project
Hallym University Capstone Design Project, Spring 2018\
한림대학교 컴퓨터공학과 종합설계프로젝트, 2018년 1학기

Clap-to-Switch Project\
박수 소리로 스위치 작동 프로젝트

목차
==========
1. [개요](#introduction)
1. [알고리즘](#algorithm)
	1. [의사 코드](#pseudocode)
1. [설계](#design)
	1. [회로 설계](#circuit_design)
1. [프로토타입 제작](#prototyping)
	1. [프로토타입 코드](#prototype_code)
	1. [실험 영상](#test_video)
1. [추후 계획](#further_plans)
1. [참조 및 출처](#references)

## 1. 개요<a name='introduction'/>
특정한 박수 패턴(e.g. 337 박수 등)을 이용하여 스위치를 연결하거나 차단시키는 장치를 개발한다.\
마이크를 이용하여 소리를 입력받아 증폭시킨 뒤, 마이크로프로세서의 ADC Input으로 전달하여 패턴을 처리, 기 입력된 패턴과 비교하여 일치할 경우 스위치를 작동 또는 차단시킨다.\
필요할 경우, 패턴 등록 기능 등을 추가한다.

## 2. 작동 알고리즘<a name='algorithm'/>
박수와 음성의 비교\
![](https://raw.githubusercontent.com/cobaltp/Capstone-Design/master/TeamA/Images/clap1.jpg)\
![](https://raw.githubusercontent.com/cobaltp/Capstone-Design/master/TeamA/Images/clap2.jpg)


박수 소리와 일반적인 잡음, 음성은 dB가 확연하게 차이나므로 이를 이용하여 마이크로 입력되는 소리에서 박수 소리를 얻어낼 수 있다.\
(단순한 큰 소리와 구분짓는 것은 불가능하지만, 단순한 큰 소리가 패턴으로 나타나는 경우는 없으므로 고려하지 않는다.)

이를 이용하여 알고리즘을 생성할 수 있으며, 다음과 같이 나타낼 수 있다.

변수 목록\
(H), (L): 소리의 최대, 최소 한계치\
(B): 박수 간격\
(C): 박수 측정 간 대기 시간\
(W): 박수 측정 후 대기 시간\
(K): 박수 횟수

1. 입력이 있을 때까지 대기한다.
2. 입력을 확인하여 최대 한계치(H)보다 높을 경우 다음으로 이동, 아닐 경우 1로 이동한다.
3. 만약 타이머가 켜져 있을 경우, 박수 간격 시간(B)을 타이머의 현재 시간으로 설정한 뒤 타이머를 종료한다.
4. (소리가 줄어들 때 까지) 일정 시간(C)동안 대기한다.
5. 입력을 확인하여 최소 한계치(L)보다 낮을 경우 다음으로 이동, 아닐 경우 1로 이동한다.
6. 박수 배열에 박수 간격 시간(B)를 추가하고, 박수 횟수(K)를 1만큼 증가시킨다.
7. 타이머를 초기화한 뒤 다시 시작시킨다.
8. 측정 후 대기시간(W)만큼 대기한다.
9. 장치에 기 입력된 패턴과 사용자가 입력한 박수 패턴을 비교한다.
10. 만약 패턴이 일치할 경우, 스위치를 작동 또는 차단하고, 아닐 경우 1로 이동한다.

### 2.1. 의사 코드<a name='pseudocode'/>
2의 알고리즘을 다음과 같이 Python 스타일의 의사 코드로 작성해보았다.\
(다음 코드는 <a href='https://github.com/cobaltp/Capstone-Design/TeamA/Code/algorithm1.py'>/Code/algorithm1.py</a>의 내용과 동일하다.)

```python3
sensorPin = 5           # 마이크 핀
outputPin = 7           # 출력 핀
thresholdH = 20         # high threshold; Th(H)
thresholdL = 2          # low threshold; Th(L)
tc = 0.05               # clap time; T(c)
tw = 0.1                # 박수간 최소 간격
match = [0, 0.8, 0.4]   # 박수 패턴; clap, 800ms 대기, clap, wait 400ms, clap
clap = []               # 박수 카운터; 값 = 박수간 간격; 100ms 단위로 반올림됨
tb = 0                  # 박수간 간격
timeout = Timer(2, callback())  # 타임아웃 타이머; 타이머 완료 시 박수 카운터 초기화
 
def callback():
    del clap[:]         # 타이머 완료 시 박수 카운터 초기화
 
def loop():
    if read(sensorPin) > thresholdH:                # 값이 최대값보다 높은 지 확인
        if timeout.isEnabled():                     # 타이머가 켜져 있을 경우
            tb = round(timeout.getInterval(), 1)    # 소수점 1번째 자리까지 반올림
            timeout.Stop()                          # 타이머 멈춤
        sleep(tc)                                   # T(c) 동안 대기
        if read(sensorPin) < thresholdL:            # 값이 최소값보다 낮은 지 확인
            clap.append(tb)                         # 박수 카운터에 박수간 간격 추가
            timeout.start()                         # 타이머 시작
    if match == clap:                               # 패턴과 입력 값이 일치할 경우
        write(outputPin, write(outputPin))          # 출력 핀을 작동한다
```

## 3. 설계<a name='design'/>
장치를 구성하기 위해 필요한 회로는 다음과 같다.

1. 오디오 증폭 회로
2. 마이크로프로세서 회로
3. (필요할 경우) 전원 회로

### 3.1. 회로 설계<a name='circuit_design'/>
무료 EDA 툴인 <a href='http://http://kicad-pcb.org/'>KiCad</a>를 이용하여 다음과 같이 회로 도면을 작성하였다.\
KiCad용 회로 파일은 <a href='https://github.com/cobaltp/Capstone-Design/TeamA/Design/clap-to-switch_prototype/'>/Design/clap-to-switch_prototype</a>에서 구할 수 있다.\
부품 상세 내용은 <a href='https://github.com/cobaltp/Capstone-Design/blob/master/TeamA/예산%20계획서'>예산 계획서 파일</a>을 참조하라.

![](https://raw.githubusercontent.com/cobaltp/Capstone-Design/master/TeamA/Images/cts_design.jpg)\
전체 회로의 모습.

각 회로를 확대하면 다음과 같다.

![](https://raw.githubusercontent.com/cobaltp/Capstone-Design/master/TeamA/Images/cts_design_amp.jpg)\
오디오 증폭 회로

![](https://raw.githubusercontent.com/cobaltp/Capstone-Design/master/TeamA/Images/cts_design_avr.jpg)\
마이크로프로세서 회로

![](https://raw.githubusercontent.com/cobaltp/Capstone-Design/master/TeamA/Images/cts_design_reg.jpg)\
전원 회로(9V-5V 레귤레이터 회로)

## 4. 프로토타입 제작<a name='prototyping'/>
ATTiny를 이용하여 프로토타입을 제작하였다.\
(ATTiny로의 업로드는 Arduino를 ISP로 사용하여 진행하였다. 다음 링크를 참조하였다.)\
(https://kocoafab.cc/tutorial/view/289)

![프로토타입의 모습](https://raw.githubusercontent.com/cobaltp/Capstone-Design/master/TeamA/Images/cts_prototype_1.jpg)

회로 세부 부분 설명

![](https://raw.githubusercontent.com/cobaltp/Capstone-Design/master/TeamA/Images/cts_prototype_2.jpg)

![](https://raw.githubusercontent.com/cobaltp/Capstone-Design/master/TeamA/Images/cts_prototype_3.jpg)

![](https://raw.githubusercontent.com/cobaltp/Capstone-Design/master/TeamA/Images/cts_prototype_4.jpg)

![](https://raw.githubusercontent.com/cobaltp/Capstone-Design/master/TeamA/Images/cts_prototype_5.jpg)

## 4.1. 프로토타입 코드<a name='prototype_code'/>
프로토타입에 사용한 코드는 다음과 같다.\
(<a href='https://github.com/cobaltp/Capstone_Design/TeamA/Code/cts_03/cts_03.ino'>/Code/cts_03/cts_03.ino</a>)

```cpp
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
    servo.attach(servoPin);
    moveServo();
    
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(r_ledPin, OUTPUT);                      // 핀 모드 설정; LED핀, 출력
    pinMode(g_ledPin, OUTPUT);                      // 핀 모드 설정; LED핀, 출력

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

void callback() {                            // 초기화 함수; 타이머 시간 도달 시 발생
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
}

int round_t(int t, int v) {                 // 정수 반올림 함수
    return (int)(round((float)t / v) * v);
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
            printArray(claps);
            timeout->Start();
            digitalWrite(g_ledPin, HIGH);
            delay(tw);
            digitalWrite(g_ledPin, LOW);
        }
    }
    
    if (checkMatch(match, claps) && onRecord == 0) {
        moveServo();
        digitalWrite(r_ledPin, HIGH);
        delay(500);
        digitalWrite(r_ledPin, LOW);
        callback();
    }
    
    SoftwareServo::refresh();
    timeout->Update();
}
```

### 4.2. 실험 영상<a name='test_video'/>
[![패턴 확인 실험 영상](http://img.youtube.com/vi/OW1-RDwN8mk/0.jpg)](https://youtu.be/OW1-RDwN8mk)]

박수를 인식하면 녹색 LED가 점멸하며, 특정 패턴을 입력하여 인식에 성공한 경우 일정 시간 동안 붉은색 LED가 점등한다.

## 5. 추후 계획<a name='further_plans'/>
프로토타입 방식으로 제작한 현재 장치를 브래드보드를 이용하여 실물로 제작하는 게 우선이다.\
그 다음으로는 입출력의 확대가 있겠다.\
현재는 출력 장치가 1개뿐이 없지만, 추후 인식할 수 있는 패턴을 여러 개로 늘리고 출력을 확장하여 활용성을 높혀야 한다.\
(입출력 핀이 많은 마이크로컨트롤러를 사용하거나, 시프트 레지스터를 이용할 수 있겠다.)

## 6. 출처 및 참조<a name='references'/>
YouTube - Turn your lights on with clapping?! by GreatScott!! (https://www.youtube.com/watch?v=7Ao6KD8f9J4) \
LM386 microphone amplifier by Dimitar Kovachev (https://lowvoltage.wordpress.com/2011/05/15/lm386-mic-amp/) \
LM386 Power Amplifier Datasheet by Texas Instruments (http://www.ti.com/lit/ds/symlink/lm386.pdf)
