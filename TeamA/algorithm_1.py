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
        write(outputPin, write(!outputPin))         # 출력 핀을 작동한다
