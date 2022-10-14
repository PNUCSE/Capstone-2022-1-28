### 1. 프로젝트 소개
* 주제 : UWB/BLE 기반 3D 실내측위 및 동기화
* 팀명 : 버퍼 리스트

- [ ] UWB or BLE 기반 실내측위 시스템 개발
- [ ] ToA 또는 TDoA를 활용한 위치 측정 모듈 개발
- [ ] 여러 대의 UWB/BLE Anchor를 배치하여 3D 위치 측정 및 오차 제어
- [ ] 디지털트윈 공간 상 물체 위치 동기화(unity 활용)

### 2. 팀소개

안현기, tykr0001@pusan.ac.kr, 개발총괄

김춘수, spiderman@marvel.com, 알고리즘 설계

이현진, doctorstrange@marvel.com, 백앤드 개발

### 3. 시스템 구성도

![image](https://user-images.githubusercontent.com/54882000/195843844-bba79f5d-f276-434f-9bc4-ec28f533a9dc.png)

BLE Tag 모듈이 일정한 간격으로 Blink 신호를 방송하면 4대의 Scanner 모듈이 이를 수신하고 RSSI를 측정한다. 측정한 RSSI 값을 기반으로 3D 좌표를 계산하기 위해 RSSI 값을 Server PC로 전송해야 하는데 각각의 Scanner 모듈을 PC에 유선으로 연결하여 값을 전송하기에는 현실적으로 무리가 있다. 따라서 Scanner 모듈 중 하나를 Master 모듈로, 나머지를 Slaver 모듈로 임의로 정한 후 Master 모듈이 게이트웨이 역할을 수행하도록 구성했다. Master-Slave간 통신은 마찬가지로 BLE 통신을 이용한다.

Master 모듈은 각 Scanner 모듈에서 측정한 RSSI 값을 Server PC와 유선으로 연결한 후 직렬통신을 통해 JSON 형식으로 전송한다. Server PC는 전송 받은 RSSI 값을 바탕으로 사변측량(Quadrilateration) 알고리즘으로 3D 좌표를 계산한다. 실시간으로 계산된 좌표를 Web Server에 업로드하면 Client PC가 원격으로 값을 참조하고, 3D 공간좌표를 렌더링하도록 구성했다.

### 4. 소개 및 시연 영상

[![부산대학교 정보컴퓨터공학부 소개](http://img.youtube.com/vi/zh_gQ_lmLqE/0.jpg)](https://youtu.be/zh_gQ_lmLqE)

### 5. 설치 및 사용법

본 프로젝트는 nodejs와 webgl로 수행되었으며 mathjs, kalmanjs 라이브러리를 필수적으로 설치해야 합니다.

또한 BLE 모듈은 Adafruit Itsybitsy nrf52840 모듈을 사용하였습니다.
