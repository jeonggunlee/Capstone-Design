# Weather_box를 소개합니다.^^

**간단소개**
   - **주제: 실시간 날씨 데이터를 시각적으로 표현하기(구름,비,빛) + 미세먼지,온습도 센서 데이터 표현하기**
   - **프로젝트 기간: 2018.03.07 ~ 2018.06.14**
   - **팀원: 컴퓨터공학과 김민정,김태훈,이지은,현동아**
   - **성과: 캡스톤 경진대회 은상 수상**
   - **부품: (nodeMCU,블루투스,neoPixcelLED,수중펌프,릴레이,가습기,아크릴판,우드락,콘센트)+ (아두이노보드,미센먼지센서,온습도센서,LCD,도트매트릭스)**
          
**목적**
>   - 우리는 수 많은 IT제품들에 열광하고 둘러싸여 생활하고 있습니다. 쏟아져 나오는 인공물 속에서 자연의 모습을 품은 제품을 만나면 얼마나 반가울까?     **weather_box를 통해 자연이 주는 감성을 되살릴 수 있습니다.**

  1. 외출하기 전, 뉴스나 인터넷을 통해 날씨정보를 찾기 귀찮지 않습니까? **weather_box는 눈길만 닿아도** 현재 날씨 상황을 쉽게 보여줍니다.   
  2. **비 오는 날은 물방울이 주룩주룩, 안개 끼는 날이면 뿌연 구름들이 뭉게뭉게, 햇빛이 쨍쨍한 날은 밝은 빛**을 냅니다.    
  3. **은은한 빛은 내는 LED조명과 빗방울 떨어지는 소리로 인테리어 효과**를 줄 수 있습니다.        
  4. **알고 싶은 지역을 설정해 해당 지역의 날씨**를 나타낼 수 있습니다.          
  5. **멀리 떨어져 지내는 사랑하는 가족 혹은 친구들이 살고 있는 날씨**는 어떨지 궁금하지 않나요? 그들이 생활하는 곳의 날씨를 생동감있게 확인할 수 있습니다.         
   
**설명**
     >   - **날씨표현**: 와이파이(esp8266 nodeMCU)를 사용해 openweathermap(날씨정보를 제공하는 API사이트)에서 온도등 필요한 데이터를 파싱하여 가져옵니다. 파싱한 값에 따라 부품들을 동작시킵니다. 그리고 와이파이보드와 블루투스를 연동하여 앱을 이용해 지역을 변경할 수 있습니다.    
     - **빛,번개**: 상단에 방수 처리된 NeoPixcel LED Strip을 부착하여 빛을 제어해 표현합니다.        
     - **비**: 하단의 물을 펌프와 고무튜브로 상단까지 끌어올려 위에서 물방울을 떨어트려 표현합니다. 이때 필요한 12V의 전원은 릴레이 모듈로 외부전원을 제어해 공급합니다.         
     - **안개,구름**: USB 가습기 모듈의 스위치를 제어해 물을 분사합니다.         
     - **미센먼지+온습도센서**: 상단 밖에 미세먼지 센서를 부착해 도트매트릭스에 얼굴표정으로 값을 표현합니다.(^^:좋음/-_-:보통/ㅠㅠ:나쁨) 
                               상단 안쪽에 미세먼지센서를 위치시켜 LCD에 습도값,온도값을 표현합니다.       
   
**활용방안 및 기대효과**
>   - 4차 산업인 홈 IOT시대에서 weather_box를 빼놓을 수 없습니다. 창문을 열거나 밖을 나가지 않아도 현재 바깥 날씨를 직접적으로 볼 수 있어서 **우산과 옷차림을 준비**할 수 있습니다. 날씨 상태를 볼 수 있고 **빗소리**를 들으며 책을 읽거나 **무드등**으로 **인테리어 효과**를 줄 수 있습니다. 
>   - 별도의 조작 없이도 weather_box가 모든 제어를 자동으로 해주기 때문에 **IT기기를 잘 사용하지 못하는 층**, 어린 아이들이 있는 가정이나 어린이집도 사용자 층으로 기대할 수 있습니다. 기기를 잘 다루지 못해도 쉽게 날씨를 접할 수 있어서 편리하고 아이들 눈높이의 **시각적인 효과로 재미와 세계지역의 날씨**에 대해 알 수 있습니다. 떨어져 지내는 친구들이나 가족들이 사는 지역으로 **앱을 이용해 장소 변경**할 수 있어서 먼 지역의 기상상태를 찾아봐야 하는 불편함을 줄일 수 있습니다. 그리고 실시간으로 변하는 **날씨가 업데이트되어 최신의 날씨 상태**를 확인할 수 있습니다.        

<img src="https://github.com/dongaah/Capstone-Design/blob/master/WeatherBox/exex/img_sun.png?raw=true" width="270" height="420"> <img src="https://github.com/dongaah/Capstone-Design/blob/master/WeatherBox/exex/cloudy.png?raw=true" width="270" height="420"> <img src="https://github.com/dongaah/Capstone-Design/blob/master/WeatherBox/exex/raining.png?raw=true" width="270" height="420">


**코드**
      - **1. 아두이노 제어**
         
    #include <ArduinoJson.h>
    #ifdef __AVR__
    #include <avr/power.h>
    #endif
    #include <SPI.h>  //API시 필요
    #include <ESP8266WiFi.h>  
    #include <Adafruit_NeoPixel.h>
    #include<SoftwareSerial.h>
    #define PIN D6                     // 네오픽셀 할당 핀(Digital 6)
    #define NUM_LEDS 60
    #define N_LEDS 30
    #define BRIGHTNESS 1000
    #define CLOUD D7
    #define PUMP D2
    SoftwareSerial BTSerial(D3, D5);
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
    #define VARID "70b9642cec0afd458b10d3914b597364"  //api key

------------------------------------------------------------------------------------
                    
      //블루투스 연결시 사용한 변수  
      String cLine = "";
      String latString = "";
      String lonString = "";
      boolean readingLat = false;
      boolean readingLon = false;
      int i=2;
      int j=2;

--------------------------------------------------------------------------------------
                              
    char ssid[] = "Hallym WiFi";       // wifi ssid
    char pass[] = "1111133333";        // wifi password
    int status = WL_IDLE_STATUS;       // the Wifi radio's status
    char server[] = "api.openweathermap.org";
    int getInt(String input);
    void Animation(); //파싱해오는 weather값에 따라 이펙트 출력
    void a(byte state); //가습기 상태
    void httpRequest();
    void printWifiStatus();
    WiFiClient client;
    IPAddress hostIp;
              
------------------------------------------------------------------------------------------------------------
                 
    unsigned long lastConnectionTime = 0;         // last time you connected to the server, in milliseconds
    const unsigned long postingInterval = 1000L; // delay between updates, in milliseconds
    boolean readingVal;
    boolean getIsConnected = false;
    int val, temp;
    float tempVal;
    float temphum;
    String rcvbuf;
    int weather;  //날씨코드 저장
    int b = 1;  //가습기 상태 저장
    String currentLine = "";          // 서버에서 전송된 데이터 String저장
    String tempString = "";           // 온도 저장 변수
    String humString = "";            // 습도 저장 변수
    String timeString = "";           // 시간 정보 변수
    String pressureString = "";       // 압력 정보 변수
    boolean readingTemp = false;      //온도 데이터가 있는지 여부 판단
    boolean readingHum = false;       //습도 데이터가 있는지 여부 판단
    boolean readingTime = false;      //시간 데이터가 있는지 여부 판단
    boolean readingPressure = false;  //압력 데이터가 있는지 여부 판단
    boolean readingWeather = false;
    String weatherString = "";

    void setup() {
    strip.setBrightness(BRIGHTNESS);
    Serial.begin(9600);
    BTSerial.begin(9600);
    Serial.println();
    pinMode(D2,OUTPUT); //pump
    pinMode(D7,OUTPUT); //cloud
    pinMode(D8,OUTPUT); //cloud
    #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
    #endif
    strip.begin();
    WiFi.disconnect();
    delay(1000);
  
    //connect to preferred SSID
    WiFi.begin(ssid, pass);
    Serial.println("Connecting");

    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println();

    // print SSID name,local IP allotted ,MAC address & signal strength
    Serial.println();
    Serial.print("Connected to SSID          : ");
    Serial.println(WiFi.SSID());
    Serial.print("IP address allotted to ESP : ");
    Serial.println(WiFi.localIP());
    httpRequest();
    } 
                     
--------------------------------------------------------------------------------------------------------
                        
    void loop() {  
    String valString;

    //블루투스로 받아온 문자열 잘라서 위도, 경도 변수에 저장
    while(BTSerial.available()) {
    char ch = BTSerial.read();   
    cLine += ch;

    if(ch == '\n') {
      cLine = "";
    }

    //위도
    if(cLine.endsWith("lat=")) {
      readingLat = true;
      latString = "";
    }

    if(readingLat) {
      if(ch != '&') { //전송될 문자가 '&'이 올때까지 위도값으로 인식
        latString += ch;
      }
      else {  //전송된 문자가 '&'이면 그만저장하고 출력
        readingLat = false;
        i = latString.length();
        latString = latString.substring(1,i);
      }
    }

    //경도
    if(cLine.endsWith("lon=")) {
      readingLon = true;
      lonString = "";
    }
    
    if(readingLon) {
      if(ch != ';') {
        lonString += ch;
      }
      else {
        readingLon = false;
        i = lonString.length();
        lonString = lonString.substring(1,i);
      }//end else
    }//end if
    }
                           
-------------------------------------------------------------------------------
                        
            //api로 받아온 날씨 자르기
            while (client.available()) {     
      char inChar = client.read();  //inChar에 읽어온 내용 저장
    currentLine += inChar;

    if(inChar == '\n') {
      currentLine="";
    }

    //온도
    if(currentLine.endsWith("<temperature value=")) {
      readingTemp = true;
      tempString="";
    }

    if(readingTemp) {
      if(inChar != 'm') {
        tempString += inChar;
      }
      else {
        readingTemp = false;
        Serial.print(" - Temperchar: ");
        Serial.print(getInt(tempString)-273);
        Serial.println((char)176);
      }
    }

    //날씨 번호
    if(currentLine.endsWith("number=")) {
      readingWeather = true;
      weatherString="";
    }
    
    if(readingWeather) {
      if(inChar != 'v') {
        weatherString += inChar;
      }
      else {
        readingWeather = false;
        weather = getInt(weatherString);
        Serial.print(" - weather code: ");
        Serial.println(weather);
        Animation();
      }
    }

    //현재 스트링이 </current>로 끝났다면 연결을 끊고 다시 서버와 연결을 준비한다.
    if ( currentLine.endsWith("</current>")) { 
      delay(10000); //10초뒤에 서버와 연결을 끊고 재연결을 시도한다.
      client.stop(); 
      httpRequest();
    }
    }//end while
 
    if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
    }
    rcvbuf = "";
    }
                        
---------------------------------------------------------------------------------------------

          // this method makes a HTTP connection to the server
            void httpRequest() {
              Serial.println();

     // close any connection before send a new request
     // this will free the socket on the WiFi shield
     client.stop();

    // if there's a successful connection
    if (client.connect(server, 80)) {
    Serial.println("Connecting...");

    // send the HTTP PUT request
    client.print("GET /data/2.5/weather?lat="+latString+"&lon="+lonString+"&appid=");
    client.print(VARID);
    client.print("&mode=xml");
    client.println(" HTTP/1.1");
    client.println("Host: api.openweathermap.org");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made
    lastConnectionTime = millis();
    getIsConnected = true;
    }
    else {
    // if you couldn't make a connection
    Serial.println("Connection failed");
    getIsConnected = false;
    }
    }

----------------------------------------------------------------------------------------------

    int getInt(String input) {
    int i = 2;
    while(input[i] != '"'){
    i++;
    }
    input = input.substring(2,i);
    char carray[20];
    input.toCharArray(carray, sizeof(carray));
    temp = atoi(carray);
    return temp;
    }

---------------------------------------------------------------------------------------------------

    void Animation()        // 파싱해오는 weather값에 따라 이펙트 출력
    {
     /*Lightening Rain*/
    if(weather <= 232 && weather >= 200)
    {
    Rain_PUMP(1);
    Lightening_LED();
    
    Cloud_PUMP(1);//Cloud Effect
    Serial.println("lightening");
    }
     /*Light Rain*/
    else if(weather <= 321 && weather >= 300)
    {
    Rain_PUMP(1);
    Light_Rainy_LED();
    Cloud_PUMP(0); 
    //Serial.println("light"); 
    }
     /*White Snow*/
    else if(weather <= 622 && weather >= 600)
    {
    Rain_PUMP(1);
    Snowy_LED();
    //Serial.println("white");
    }
      /*Fog*/
    else if(weather <= 721 && weather >= 701 || (weather == 741))
     {
    Rain_PUMP(1);
    Cloud_PUMP(1);//Cloud Effect
    //No LED
    //Serial.println("Fog");
    Lightening_LED();
    //Serial.println("LEd");
      }
      /*Dark Cloudy*/
    else if((weather == 731) || (weather == 751) || (weather == 761) || (weather == 781))
    {
    Rain_PUMP(0);
    Cloudy_LED();
    Cloud_PUMP(1);// Cloud Effect
    //Serial.println("dark");
    }
      /*General Cloud*/
    else if(weather <= 804 && weather >= 800)
    {
    Rain_PUMP(1);
    Fine_LED();
    Cloud_PUMP(1);// Cloud Effect
    //Serial.println("general");
     }
    }

    void a(byte state)  //가습기 상태 변화 함수
     {
     if(b == state){
     Serial.println("b==state");
     }
    else {
    Serial.println("b!=state");
    digitalWrite(CLOUD,HIGH);
    delay(2000);
    digitalWrite(CLOUD,LOW);
    b = state; 
      }
    }

     void Cloud_PUMP(byte state)           // 구름(가습기)구동 함수
     {
     a(state);
      }
     void Rain_PUMP(byte stat)            // 펌프 구동 함수
     {
     if(stat == 0){digitalWrite(PUMP,LOW);}
      else if(stat == 1){digitalWrite(PUMP,HIGH);}
     }

     void Fine_LED()                       // '맑은 날' LED 출력
    {
     int i;
     for(i=0;i<201;i++)
      {
       LED_ON(strip.Color(255,i,0));
        }
     for(i=0;i<47;i++)
     {
     LED_ON(strip.Color(255,200,i));    
     }
    for(i=0;i<56;i++)
      {
      LED_ON(strip.Color(255,200+i,46));
      }
    for(i=0;i<210;i++)
    {
     LED_ON(strip.Color(255,255,46+i));
    }
    for(i=0;i<256;i++)
    {
    LED_ON(strip.Color(255,255-i,255-i));
    }
    }

    void Cloudy_LED()                     // '구름 낀 날' LED 출력
     {
     int i,j;
     for(j=30;j<255;j++)
     {
      LED_ON(strip.Color(j, j, j));
      }
     for(j=255;j>30;j--)
    {
      LED_ON(strip.Color(j, j, j));

      }
    delay(3000);
     }

    void Snowy_LED()                      // '눈 오는 날' LED 출력
      {
     LED_ON(strip.Color(150, 150, 150));
     delay(2000);
     LED_ON(strip.Color(0,0,0));
     delay(10);
     LED_ON(strip.Color(150, 150, 150));
     }
    void Light_Rainy_LED()                // '약한 비' LED 출력
    {
    int i;
    for(i=0;i<201;i++)
    {
      LED_ON(strip.Color(0,234-i,234-i));
    }
    for(i=0;i<201;i++)
    {
     LED_ON(strip.Color(0,34+i,34+i));
     }
    }

    void Lightening_LED()                  // '뇌우' LED 출력
    {
    //Serial.println("fsfdsdfd");
    int i,j,k;
    for(i=0;i<15;i++)
    {
    LED_ON(strip.Color(80, 80, 250));
    delay(10);
    LED_ON(strip.Color(0, 0, 0));
    delay(5);
    }
    for(i=0;i<5;i++)
    {
    LED_ON(strip.Color(80, 80, 250));
    delay(500);
    LED_ON(strip.Color(0, 0, 0));
    delay(100);
    } 
    for(i=0;i<8;i++)
    {
    LED_ON(strip.Color(80, 80, 250));
    delay(1000);
    LED_ON(strip.Color(0, 0, 0));
    delay(50);
    }
    }

    }
    }
    }
    }
    }
    }
    }
----------------------------------------------------------------------------------
  - **2. 장소변경 앱 만들기** 
  
     **build.gradle(Module: app)에 compile 'com.akexorcist:bluetoothspp:1.0.0' 추가
       
         MainActivity.java
        package com.example.leeje.lasttest;
        import android.content.Intent;
        import android.location.Address;
        import android.location.Geocoder;
        import android.net.Uri;
        import android.support.v7.app.AppCompatActivity;
        import android.os.Bundle;
        import android.util.Log;
        import android.view.View;
        import android.widget.Button;
        import android.widget.EditText;
        import android.widget.TextView;

        import java.io.IOException;
        import java.util.List;

        import android.app.Activity;
        import android.bluetooth.BluetoothAdapter;
        import android.content.Intent;
        import android.support.v7.app.AppCompatActivity;
        import android.os.Bundle;
        import android.view.View;
        import android.widget.Button;
        import android.widget.Toast;
        import app.akexorcist.bluetotohspp.library.BluetoothSPP;
        import app.akexorcist.bluetotohspp.library.BluetoothState;
        import app.akexorcist.bluetotohspp.library.DeviceList;
  
        public class MainActivity extends AppCompatActivity {
        private BluetoothSPP bt;

        String temp ;   //temp에 문자열 저장
        String []arr ; //,기준으로 자르기
        String []latitude ; //위도
        String []longitude ;    //경도

        @Override
        protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
           setContentView(R.layout.activity_main);

        bt = new BluetoothSPP(this); //Initializing

        if (!bt.isBluetoothAvailable()) { //블루투스 사용 불가
            Toast.makeText(getApplicationContext()
                    , "Bluetooth is not available"
                    , Toast.LENGTH_SHORT).show();
            finish();
        }

        bt.setOnDataReceivedListener(new BluetoothSPP.OnDataReceivedListener() { //데이터 수신
            public void onDataReceived(byte[] data, String message) {
                Toast.makeText(MainActivity.this, message, Toast.LENGTH_SHORT).show();
            }
        });

        bt.setBluetoothConnectionListener(new BluetoothSPP.BluetoothConnectionListener() { //연결됐을 때
            public void onDeviceConnected(String name, String address) {
                Toast.makeText(getApplicationContext()
                        , "Connected to " + name + "\n" + address
                        , Toast.LENGTH_SHORT).show();
            }

            public void onDeviceDisconnected() { //연결해제
                Toast.makeText(getApplicationContext()
                        , "Connection lost", Toast.LENGTH_SHORT).show();
            }

            public void onDeviceConnectionFailed() { //연결실패
                Toast.makeText(getApplicationContext()
                        , "Unable to connect", Toast.LENGTH_SHORT).show();
            }
        });

        Button btnConnect = findViewById(R.id.btnConnect); //연결시도
        btnConnect.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if (bt.getServiceState() == BluetoothState.STATE_CONNECTED) {
                    bt.disconnect();
                } else {
                    Intent intent = new Intent(getApplicationContext(), DeviceList.class);
                    startActivityForResult(intent, BluetoothState.REQUEST_CONNECT_DEVICE);
                }
            }
        });
        //여기까지 bluetooth

        final TextView tv = (TextView) findViewById(R.id.textView4); // 결과창
        Button b1 = (Button)findViewById(R.id.button1);
        Button b2 = (Button)findViewById(R.id.button2);
        Button b3 = (Button)findViewById(R.id.button3);
        Button b4 = (Button)findViewById(R.id.button4);

        final EditText et1 = (EditText)findViewById(R.id.editText1);
        final EditText et2 = (EditText)findViewById(R.id.editText2);
        final EditText et3 = (EditText)findViewById(R.id.editText3);

        final Geocoder geocoder = new Geocoder(this);

        b1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // 위도,경도 입력 후 변환 버튼 클릭
                List<Address> list = null;
                try {
                    double d1 = Double.parseDouble(et1.getText().toString());
                    double d2 = Double.parseDouble(et2.getText().toString());

                    list = geocoder.getFromLocation(
                            d1, // 위도
                            d2, // 경도
                            10); // 얻어올 값의 개수
                } catch (IOException e) {
                    e.printStackTrace();
                    Log.e("test", "입출력 오류 - 서버에서 주소변환시 에러발생");
                }
                if (list != null) {
                    if (list.size()==0) {
                        tv.setText("해당되는 주소 정보는 없습니다");
                    } else {
                        tv.setText(list.get(0).toString());
                    }
                }
            }
        });

        //변환 2 눌렀을때 주소->위도, 경도
        b2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                List<Address> list = null;
                String str = et3.getText().toString();
                try {
                    list = geocoder.getFromLocationName(
                            str, // 지역 이름
                            10); // 읽을 개수
                } catch (IOException e) {
                    e.printStackTrace();
                    Log.e("test","입출력 오류 - 서버에서 주소변환시 에러발생");
                }
                if (list != null) {
                    if (list.size() == 0) {
                        tv.setText("해당되는 주소 정보는 없습니다");
                    } else {    //list에 값이 있으면 문자열 자르기
                        //tv.setText(list.get(0).toString());
                        temp = list.get(0).toString();   //temp에 문자열 저장
                        arr = temp.split(","); //,기준으로 자르기
                        latitude = arr[10].split("="); //위도
                        longitude = arr[12].split("=");    //경도
                        //위도와 경도 어플 화면에 출력
                        tv.setText("위도: " + latitude[1] + "\n경도: " + longitude[1]);
                    }
                }
            }
        });

        b3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // 위도,경도 입력 후 지도 버튼 클릭 => 지도화면으로 인텐트 날리기
                double d1 = Double.parseDouble(et1.getText().toString());
                double d2 = Double.parseDouble(et2.getText().toString());

                Intent intent = new Intent(
                        Intent.ACTION_VIEW,
                        Uri.parse("geo:" + d1 + "," + d2));
                startActivity(intent);
            }
        });

        b4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // 주소입력후 지도2버튼 클릭시 해당 위도경도값의 지도화면으로 이동
                List<Address> list = null;
                String str = et3.getText().toString();
                try {
                    list = geocoder.getFromLocationName
                            (str, // 지역 이름
                                    10); // 읽을 개수
                } catch (IOException e) {
                    e.printStackTrace();
                    Log.e("test","입출력 오류 - 서버에서 주소변환시 에러발생");
                }

                if (list != null) {
                    if (list.size() == 0) {
                        tv.setText("해당되는 주소 정보는 없습니다");
                    } else {
                        // 해당되는 주소로 인텐트 날리기
                        Address addr = list.get(0);
                        double lat = addr.getLatitude();
                        double lon = addr.getLongitude();

                        String sss = String.format("geo:%f,%f", lat, lon);

                        Intent intent = new Intent(
                                Intent.ACTION_VIEW,
                                Uri.parse(sss));
                        startActivity(intent);
                    }
                }
            }
        });

    } // end onCreate

    public void onDestroy() {
        super.onDestroy();
        bt.stopService(); //블루투스 중지
    }

    public void onStart() {
        super.onStart();
        if (!bt.isBluetoothEnabled()) { //
            Intent intent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(intent, BluetoothState.REQUEST_ENABLE_BT);
        } else {
            if (!bt.isServiceAvailable()) {
                bt.setupService();
                bt.startService(BluetoothState.DEVICE_OTHER); //DEVICE_ANDROID는 안드로이드 기기 끼리
                setup();
            }
        }
    }
----------------------------------------------------------------------------------------------------------      
   > activity_main.xml
   
    <?xml version="1.0" encoding="utf-8"?>
    <android.support.constraint.ConstraintLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    tools:context=".MainActivity">

    <Button
        android:id="@+id/btnConnect"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="연결"
        app:layout_constraintBottom_toBottomOf="parent"
        app:layout_constraintLeft_toLeftOf="parent"
        app:layout_constraintRight_toRightOf="parent"
        app:layout_constraintTop_toTopOf="parent" />

    <Button
        android:id="@+id/btnSend"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_marginTop="8dp"
        android:text="보내기"
        app:layout_constraintLeft_toLeftOf="parent"
        app:layout_constraintRight_toRightOf="parent"
        app:layout_constraintTop_toBottomOf="@+id/btnConnect" />


    <RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"
        android:layout_width="fill_parent"
        android:layout_height="fill_parent" >
        <TextView
            android:id="@+id/textView1"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_alignParentLeft="true"
            android:layout_alignParentTop="true"
            android:text="위도"
            android:textAppearance="?android:attr/textAppearanceLarge" />
        <EditText
            android:id="@+id/editText1"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_alignParentTop="true"
            android:layout_centerHorizontal="true"
            android:ems="10"
            android:inputType="numberDecimal" />
        <EditText
            android:id="@+id/editText2"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_alignLeft="@+id/editText1"
            android:layout_alignTop="@+id/textView2"
            android:ems="10"
            android:inputType="numberDecimal" />
        <TextView
            android:id="@+id/textView3"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_alignParentLeft="true"
            android:layout_below="@+id/editText2"
            android:layout_marginTop="26dp"
            android:text="주소"
            android:textAppearance="?android:attr/textAppearanceLarge" />
        <EditText
            android:id="@+id/editText3"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_alignLeft="@+id/editText2"
            android:layout_alignTop="@+id/textView3"
            android:ems="10" >
            <requestFocus />
        </EditText>
        <TextView
            android:id="@+id/textView2"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_alignParentLeft="true"
            android:layout_below="@+id/editText1"
            android:layout_marginTop="22dp"
            android:text="경도"
            android:textAppearance="?android:attr/textAppearanceLarge" />
        <Button
            android:id="@+id/button1"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_alignBaseline="@+id/editText2"
            android:layout_alignBottom="@+id/editText2"
            android:layout_alignParentRight="true"
            android:text="변환1" />
        <Button
            android:id="@+id/button2"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_alignBaseline="@+id/textView3"
            android:layout_alignBottom="@+id/textView3"
            android:layout_alignParentRight="true"
            android:text="변환2" />
        <TextView
            android:id="@+id/textView4"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_alignParentBottom="true"
            android:layout_alignParentLeft="true"
            android:layout_alignParentRight="true"
            android:layout_below="@+id/button2"
            android:layout_marginTop="28dp"
            android:text="조회한 주소정보 출력"
            android:textAppearance="?android:attr/textAppearanceMedium" />
        <Button
            android:id="@+id/button3"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_alignBottom="@+id/editText2"
            android:layout_alignRight="@+id/editText2"
            android:text="지도1" />
        <Button
            android:id="@+id/button4"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_alignBaseline="@+id/editText3"
            android:layout_alignBottom="@+id/editText3"
            android:layout_alignRight="@+id/editText3"
            android:text="지도2" />
    </RelativeLayout>
    </android.support.constraint.ConstraintLayout>
--------------------------------------------------------------------------------------------------------------------
**동영상**


-시연 동영상 참조 -> [Weather Box test](https://youtu.be/GDOYBwniNqM)  

[![weather box test](http://img.youtube.com/vi/GDOYBwniNqM/0.jpg)](https://www.youtubehttps://youtu.be/GDOYBwniNqM)


