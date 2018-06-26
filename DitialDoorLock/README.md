**Smart DoorLock**
===========
한림대학교 컴퓨터공학과 - 송아현, 양세림, 윤여원


**1. 개발 목적**
===========
 현대 사회에는 점차 1인 가구가 증가하고 있습니다. 그렇다 보니 1인 가구의 보안 문제도 화제가 되고 있습니다. 현재 대부분의 가정은 도어락을 이용하고 있습니다. 하지만 도어락의 보안은 점차 문제가 발생하고 있을 뿐만 아니라, 범죄자들이 다양한 방법으로 도어락을 열고 있습니다. 이러한 문제를 해결하기 위한 방법을 고민하다가, 사람들이 자신의 분신과도 같게 생각하는 스마트폰을 생각해 스마트폰의 보안 방법을 이용하기로 하였습니다. 

![default](https://user-images.githubusercontent.com/37283269/41849271-40b451f0-78bb-11e8-8941-a45cb8ede9c1.png)

![default](https://user-images.githubusercontent.com/37283269/41849273-4459d8b6-78bb-11e8-9603-ae1f40fa0ca8.png)

 실제 ‘세계이동통신사업자협회(GSMA)’ 에 따르면 2017년 기준, 세계 스마트폰 보급률이 51%라고 합니다. 그 중 한국의 스마트폰 보급률은 85%로 세계 최고 수준을 기록하고 있습니다. 현재 시중에는 스마트폰의 잠금을 푸는 다양한 방법들이 나와 있습니다. ‘두잇서베이’에서 진행한 스마트폰 사용실태 대한 설문조사 중 일부인 잠금 장치 사용에 관한 통계에 따르면 ‘패턴’을 이용하는 것이 34.6%로 잠금 장치 방법으로써 많이 사용되고 있습니다. 

 그래서 기존의 번호를 누르던 도어락에 패턴이라는 장치를 추가하여 보안의 문제를 해결하고자 합니다. 뿐만 아니라, 도어락 근처에 2개의 카메라를 이용해서 근처의 외부인이나 수상한 사람이 있는 경우 검출하여 도어락을 사용하고 있는 입주민의 핸드폰에 설치된 어플리케이션에 검출한 사진을 보내줘, 최종적으로 'Smart DoorLock'을 개발할 것입니다. 

![default](https://user-images.githubusercontent.com/37283269/41849333-88c5d324-78bb-11e8-9053-50542195c7a7.png)

![default](https://user-images.githubusercontent.com/37283269/41849340-8c4de72a-78bb-11e8-9f9a-64329b58cfc9.png)


**2. 개발 내용**
===========
 ‘Smart DoorLock’은 아파트 현관같이 공동 현관에서 사용하기에 적합한 도어락입니다. 사용자가 패턴 비밀번호, 숫자 비밀번호 두 가지 방법 중 편리한 방법을 택해 출입할 수 있습니다.

 그리고 ‘Smart DoorLock’ 전용 앱(어플리케이션)을 통해 현관 앞에 설치된 CCTV에 탐색된 수상한 사람을 캡처한 여러 장의 사진을 확인할 수 있습니다. 만약 외부인 방문으로 현관 비밀번호를 알려 줘야 할 때 사용자가 알고 있는 비밀번호가 아닌 1회용 숫자 비밀번호를 앱으로 발생시켜 외부인으로부터 비밀번호 유출을 막을 수 있습니다. 발생된 1회용 비밀번호를 외부인에게 알려주면 외부인은 발생한 시간으로부터 10분 안으로 사용이 가능하고 한 번 입력하여 출입하게 되면 다음에 사용하지 못하도록 하여 재방문 시에 무단침입을 막을 수 있습니다. 이 경우 택배기사나 배달기사 같은 외부인이 무단침입 하는 경우를 막을 수 있어 해당 건물에 사는 사람들을 편리하지만 범죄로부터 안전할 수 있도록 구현하였습니다. 

 패턴과 숫자 키패드는 라즈베리파이 터치스크린에 띄워서 사용할 수 있고 html 파일과 자바스크립트, jquery를 이용하여 작동될 수 있도록 하였습니다. 비밀번호를 입력한 후 서버에 저장되어 있는 비밀번호 값과 비교하여 맞으면 TRUE 값을, 틀리면 FALSE 값을 서버에게 전달하여 문을 열기 위한 신호를 줄 수 있도록 하였습니다.

 CCTV는 라즈베리파이 전용 파이카메라를 사용하여 촬영을 합니다. 현관 앞에 카메라를 설치하여 계속 촬영을 하게 되는데 이 때 수상한 사람이 10분이상 계속 머물게 되면 캡처를 합니다. 수상한 사람임을 판단하기 위해 HOG 기법을 사용하여 먼저 얼굴 인식으로 사람임을 확인하고 그 다음 보행자 인지 검출하여 캡처를 하게됩니다. 캡처한 사진 파일은 데이터베이스로 전송된 후, 이 건물에 입주한 사람들이 갖고 있는 전용 앱으로 전송하여 상황을 인지할 수 있도록 하였습니다.

 ‘Smart DoorLock’ 전용 앱은 1회용 숫자 비밀번호 생성과 CCTV촬영에서 캡처된 사진 파일을 확인하기로 구성되어 있습니다. 1회용 숫자 비밀번호 생성을 원하면 서버에 신호가 가서 랜덤한 숫자 비밀번호를 전송해줍니다. 사진 파일 또한 서버로부터 전송되어 실시간으로 확인할 수 있도록 알람이 울리도록 하였습니다. 그리고 이 앱은 입주민 임을 확인하기 위해 간단한 아이디와 비밀번호를 해당 건물에 입주한 사람들에게 제공하여 사용할 수 있도록 하였습니다.서버는 패턴 비밀번호, 숫자 비밀번호의 정보를 갖고 있어 사용자가 비밀번호를 입력했을 경우 자바스크립트에서 온 값을 통해 문을 열어 줄지 말지에 대해 결정을 합니다. 

 그리고 사용자가 전용 앱을 통해 1회용 숫자 비밀번호 생성을 원할 경우 앱에서 랜덤한 숫자 조합을 통해 비밀번호를 생성하여 데이터베이스로 전송합니다.  이 1회용 비밀번호를 통해서 문이 열릴 수 있도록 서버에서 자바스크립트로 원래 비밀번호 값과 1회용 숫자 비밀번호 값 두 가지를 전송하여 비교할 수 있도록 하였습니다. 서버에는 CCTV촬영으로 캡처된 사진파일이 저장된 후 전용 앱으로 전송해주고 앱 사용시 필요한 아이디와 비밀번호에 대한 DB(데이터베이스)값도 저장되어 있습니다. 

**3. 소스 및 주석**
===========
### ① Web page

 pattern_db.php
-----------
- [pattern_db.pho.txt](https://github.com/jeonggunlee/Capstone-Design/files/2132974/pattern_db.pho.txt)

- 패턴 키패드를 그려주기 위한 소스
![default](https://user-images.githubusercontent.com/37283269/41851034-97d502b2-78c1-11e8-8f0a-505fc1315ada.JPG)

```
<!doctype html>
<html>
<head>
<meta charset="utf-8">
<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
<meta name="viewport" content="width=device-width, initial-scale=1">

<style>
.button {
border-style : solid;
border-color : #555555;
border-width:2px;
/* outline : 0; 클릭시 파란테두리 생기는거 없앰 */
background-color:#b0e0e6;   /*--백그라운드 정의---*/
font:20px 굴림;      /*--폰트 정의---*/
font-weight:bolder;   /*--폰트 굵기 bold---*/
color:#555555;    /*--폰트 색깔 000000---*/
width:100px;
height:100px;  /*--버튼 크기---*/
}
</style>

<?	# mysql 접속을 위한 작업.
	$host = '210.115.229.91';
	$dbName = 'master_pw';
	$user = 'root';
	$pw = 'dblab2316';

	#db접속을 위한 mysqli_connect 사용.
	$mysqli = mysqli_connect($host, $user, $pw, $dbName);

	# query문을 통해 master_pw의 password db테이블에 접속.
	$select_query = "SELECT master_pw FROM password";
 
	#db 접속에 성공했는지 확인하기 위한 조건문.
	if($mysqli){
	//	echo "MySQL 접속 성공";
	}else{
	//	echo "MySQL 접속 실패";
	}
	
	echo '<br>';

	$result = mysqli_query($mysqli, $select_query);
	

	$data = mysqli_fetch_array($result) ;

	$master_pw = $data[0];
	//	$door_check = $data[1];
	//	$daily_pw = $data['daily_pw'];


	//echo $master_pw;

?>
<form>
<!-form을 이용해 php의 변수를 html의 변수로 넘겨주기위한 작업.->
	<input type="hidden" name="m_pw" id="m_pw" value="<?php $master_pw; ?>">
</form>


<title>jQuery gesture.password.js Plugin Demo</title>
</head>

<body>
<div id="jquery-script-menu">

<h2>Z모양으로 패턴을 그려보세요.</h2>
<div id="gesturepwd"></div>
<br><input type=button name="전환" value="전환" class = "button" onclick="location.href='210.115.229.91/var/www/html/tmp/number4.html'";>&nbsp;&nbsp;


</body>
<script src="jquery-2.1.4.min.js"></script>
<script src="jquery.gesture.password.js"></script>

<script>

$("#gesturepwd").GesturePasswd({
backgroundColor:"#b0e0e6",  //배경색상
color:"#FFFFFF",   //패턴 동그라미 색상
roundRadii:50,    //동그라미 크기
pointRadii:20, //패턴 그릴때 표시되는 동그라미 크기
space:60,  //패턴 간격
width:480,   //박스 가로 크기
height:480,  //박스 세로크기
lineColor:"#ECF0F1",   //패턴그릴때 표시되는 선 색상
zindex :100  //레이어 Z값
});

$("#gesturepwd").on("hasPasswd",function(e,passwd){
var result;
var db_pw = "";

db_pw = document.getElementById("m_pw").innerHTML="<?=$master_pw;?>"; //db에서 마스터 비번 값 불러와 script 변수에 저장.

if(passwd == db_pw){
	result=true;
}
else {
	result=false;
}

	if(result == true){
		$("#gesturepwd").trigger("passwdRight");	//비밀번호가 맞을 경우 색깔 초록색으로 변경
			setTimeout(function(){
				location.href = '210.115.229.91/var/www/html/tmp/finish_true.html';
		},500); 
	}
	else{
		$("#gesturepwd").trigger("passwdWrong");	//비밀번호가 맞을 경우 색깔 빨간색으로 변경
			setTimeout(function(){
				location.href = '210.115.229.91/var/www/html/tmp/finish_false.html';
		},500); 
	}
});
</script>
<?php
	mysqli_close($mysqli); 
?>
</html>
```

number.php
-----------
- [number.txt](https://github.com/jeonggunlee/Capstone-Design/files/2132975/number.txt)

- 숫자 키패드를 그려주기 위한 소스
![default](https://user-images.githubusercontent.com/37283269/41851010-8b5ccd08-78c1-11e8-96a0-1d69d3770251.JPG)

```
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<style>
.button {
border-style : solid;
border-color : #555555;
border-width:2px;
/* outline : 0; 클릭시 파란테두리 생기는거 없앰 */
background-color:#b0e0e6;   /*--백그라운드 정의---*/
font:20px 굴림;      /*--폰트 정의---*/
font-weight:bolder;   /*--폰트 굵기 bold---*/
color:#555555;    /*--폰트 색깔 000000---*/
width:100px;
height:100px;  /*--버튼 크기---*/
}
</style>

<?php
	# mysql 접속을 위한 작업.
	$host = '210.115.229.91';
	$dbName = 'master_pw';
	$user = 'root';
	$pw = 'dblab2316';

	#db접속을 위한 mysqli_connect 사용.
	$mysqli = mysqli_connect($host, $user, $pw, $dbName);

	# query문을 통해 master_pw의 password db테이블에 접속.
	$select_query = "SELECT master_pw FROM password";
 
	#db 접속에 성공했는지 확인하기 위한 조건문.
	if($mysqli){
	//	echo "MySQL 접속 성공";
	}else{
	//	echo "MySQL 접속 실패";
	}
	
	echo '<br>';

	$result = mysqli_query($mysqli, $select_query);
	
	$data = mysqli_fetch_array($result) ;

	$master_pw = $data[0];

	$daily_pw = $data[2];

?>
<form>
<!-form을 이용해 php의 변수를 html의 변수로 넘겨주기위한 작업.->
	<input type="hidden" name="m_pw" id="m_pw" value="<?php $master_pw; ?>">
	<input type="hidden" name="d_pw" id="d_pw" value="<?php $daily_pw; ?>">
</form>

<title>Smart DoorLock_keypad</title>
</head>
<body>
<center>
<!--canvas id="myCanvas" width = "500", height="500"-->
<input type=button value=1 class = "button" onclick = "save('1')">&nbsp;&nbsp;
<input type=button value=2 class = "button" onclick = "save('2')">&nbsp;&nbsp;
<input type=button value=3 class = "button" onclick = "save('3')">&nbsp;&nbsp;
<br><br>
<input type=button value=4 class = "button" onclick = "save('4')">&nbsp;&nbsp;
<input type=button value=5 class = "button" onclick = "save('5')">&nbsp;&nbsp;
<input type=button value=6 class = "button" onclick = "save('6')">&nbsp;&nbsp;
<br><br>
<input type=button value=7 class = "button" onclick = "save('7')">&nbsp;&nbsp;
<input type=button value=8 class = "button" onclick = "save('8')">&nbsp;&nbsp;
<input type=button value=9 class = "button" onclick = "save('9')">&nbsp;&nbsp;
<br><br>
<input type=button value=# class = "button" onclick = "save('#')">&nbsp;&nbsp;
<input type=button value=0 class = "button" onclick = "save('0')">&nbsp;&nbsp;
<input type=button value=* class = "button" onclick = "save('*')">&nbsp;&nbsp;
<br><br>
<input type=button name="전환" value="전환" class = "button" onclick="location.href='210.115.229.91/var/www/html/tmp/pattern_db12.html'";>&nbsp;&nbsp;

</center>

<script language=javascript>

var passwd = "";
var p = "";
var db_pw = "";
var db_dpw = "";

db_pw = document.getElementById("m_pw").innerHTML="<?=$master_pw;?>"; //db에서 마스터 비번 값 불러와 script 변수에 저장.
db_dpw = document.getElementById("d_pw").innerHTML="<?=$daily_pw;?>"; //1회용 비밀번호
alert(db_pw);
<!- save : 숫자 버튼의 속성값을 가져와 저장하는 함수. ->concat 활용
function save(num) {

	if(num == "*") {
		if(db_dpw == null){

			if(passwd == db_pw){
				//alert(db_pw);
				location.href = '210.115.229.91/var/www/html/tmp/finish_true.html'
			}
			else{
				alert("비밀번호가 틀립니다.");
				passwd = "";
				location.href = '210.115.229.91/var/www/html/tmp/finish_false.html';
			}
		}
		else{
			if(passwd == db_pw || passwd == db_dpw){
				location.href = '210.115.229.91/var/www/html/tmp/finish_true.html'
			}
			else{
				alert("비밀번호가 틀립니다.");
				passwd = "";
				location.href = '210.115.229.91/var/www/html/tmp/finish_false.html';	
			}
			
		}
		passwd = "";	
		
	}
	else{
		p = passwd.concat(num);
		//alert(p);
		passwd = p;
	}
}
</script>

</body>
<?php
	#mysql 접속 닫기.
	mysqli_close($mysqli); 
?>
</html>
```
finish_true.php
-----------
- [finish_true.txt](https://github.com/jeonggunlee/Capstone-Design/files/2132976/finish_true.txt)

- 문이 열리는 걸 표현해주고 db값을 저장해 주는 소스

![default](https://user-images.githubusercontent.com/37283269/41851049-a4e28f38-78c1-11e8-92ce-52aa7d5d9a42.JPG)

```
<!doctype html>
<html>
<?php
	# mysql 접속을 위한 작업.
	$host = '210.115.229.91';
	$dbName = 'master_pw';
	$user = 'root';
	$pw = 'dblab2316';

	#db접속을 위한 mysqli_connect 사용.
	$mysqli = mysqli_connect($host, $user, $pw, $dbName);

	# query문을 통해 master_pw의 password db테이블에 접속.
	$select_query = "SELECT master_pw FROM password";
 
	#db 접속에 성공했는지 확인하기 위한 조건문.
	if($mysqli){
		echo "MySQL 접속 성공";
	}else{
		echo "MySQL 접속 실패";
	}
	
	echo '<br>';

	//$result = mysqli_query($mysqli, $select_query);
	


	$t = "true";
	
	// DB의 door_check에 결과 값 저장.
	$update_query = "update password set door_check = '$t'";
	
	$result = mysqli_query($mysqli, $update_query);

	//$data = mysqli_fetch_array($result)

	mysqli_close($mysqli); 
?>
<body>
<center>
<h2>문이 열립니다.</h2>
</center>
</body>
</html>


```

finish_false.php
-----------
- [finish_false.txt](https://github.com/jeonggunlee/Capstone-Design/files/2132977/finish_false.txt)

- 문이 닫히는 걸 표현해주고 db값을 저장해 주는 소스

![default](https://user-images.githubusercontent.com/37283269/41851055-a8ad3c4e-78c1-11e8-91f2-f3417db3f9b2.JPG)

```
<!doctype html>
<html>
<?php
	# mysql 접속을 위한 작업.
	$host = '210.115.229.91';
	$dbName = 'master_pw';
	$user = 'root';
	$pw = 'dblab2316';

	#db접속을 위한 mysqli_connect 사용.
	$mysqli = mysqli_connect($host, $user, $pw, $dbName);

	# query문을 통해 master_pw의 password db테이블에 접속.
	$select_query = "SELECT master_pw FROM password";
 
	#db 접속에 성공했는지 확인하기 위한 조건문.
	if($mysqli){
		echo "MySQL 접속 성공";
	}else{
		echo "MySQL 접속 실패";
	}
	
	echo '<br>';

	//$result = mysqli_query($mysqli, $select_query);
	


	$f = "false";
	
	// DB의 door_check에 결과 값 저장.
	$update_query = "update password set door_check = '$f'";
	
	$result = mysqli_query($mysqli, $update_query);

	//$data = mysqli_fetch_array($result)

	mysqli_close($mysqli); 
?>
<body>
<center>
<h2>문이 열립니다.</h2>
</center>
</body>
</html>

```

### ② OpenCV 
- [body_detection.zip](https://github.com/jeonggunlee/Capstone-Design/files/2133033/body_detection.zip)

Capstone.cpp
-----------
- 보행자 검출을 위한 소스.

```
// Capstone.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/cvaux.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

using namespace cv;

int body_detect(int, char **);
void _body_detect_and_draw(IplImage *);

int count = 0; //사진을 저장할때 사용하는 변수
clock_t start = 0, end = 0; //시간 측정하기 위한 변수
int body_flag = 0; //인식한 상체에 대해 카운트하는 변수
static CvMemStorage *storage = 0; //계산하기 위한 메모리 공간 생성
static CvHaarClassifierCascade *cascade = 0; //HaarClassifier 생성

int main(int argc, char **argv) {
	body_detect(argc, argv);
}

int body_detect(int argc, char **argv) {
	CvCapture *capture = 0; //for video capture
	IplImage *frame;
	int optlen = strlen("--cascade=");
	const char *input_name;
	const char *cascade_name;

	//cascade file including
	//1. user define
	//2. using default cascade xml files
	if (argc > 1 && strncmp(argv[1], "--cascade=", optlen) == 0) {
		cascade_name = argv[1] + optlen;
		input_name = argc > 2 ? argv[2] : 0;
	}
	else {
		cascade_name = "./opencv/data/haarcascades/haarcascade_mcs_upperbody.xml"; //상체 검출
		input_name = argc > 1 ? argv[1] : 0;
	}

	//open cascade files and check validation
	if (!(cascade = (CvHaarClassifierCascade *)cvLoad(cascade_name, 0, 0, 0))) { //학습된 결과 인식기는 xml파일에 저장된다.
		fprintf(stderr, "ERROR: Couldn't load classifier cascade\n");
		fprintf(stderr, "Usage: facedetect --cascade=\"<cascade_path>\" [filenameIcamera_index]\n");
		return -1;
	}

	//prepare to acception a input images from files or videos(Cam)
	storage = cvCreateMemStorage(0);
	if (!input_name || (isdigit(input_name[0]) && input_name[1] == '\0'))
		capture = cvCaptureFromCAM(!input_name ? 0 : input_name[0] - '0');
	else
		capture = cvCaptureFromCAM(0); //카메라에서 입력 받음.

	cvNamedWindow("Result", 1);

	while (!0) {
		if (!(frame = cvQueryFrame(capture)))
			break;
		_body_detect_and_draw(frame);
		if (cvWaitKey(10) >= 0)
			break;
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("Result");
	return 0;
}


static CvScalar colors;
void _body_detect_and_draw(IplImage *img) {
	char image_name[100] = "0";
	colors = { 0,255,0 };
	double scale = 2.0; //계산속도 빠르게 하기 위해 영상을 축소해서 처리.
	IplImage *gray = cvCreateImage(cvSize(img->width, img->height), 8, 1);
	IplImage *small_Img = cvCreateImage(cvSize(cvRound(img->width / scale), cvRound(img->height / scale)), 8, 1);

	cvCvtColor(img, gray, CV_BGR2GRAY); //흑백으로 변환
	cvResize(gray, small_Img, CV_INTER_LINEAR); //영상 축소
	cvClearMemStorage(storage); //메모리 초기화

	if (cascade) {
		CvSeq *body = cvHaarDetectObjects(small_Img, cascade, storage, 1.1, 2, 0, cvSize(30, 30), cvSize(300, 300));
		//사람의 상체가 검출되면 start시간을 측정하고, 검출이 끝나게 되면 end시간을 측정해서 total Time을 구한다.
		//만약 total Time이 5초 이상인 경우는 서버로 사진을 전송합니다.
		if (body->total > 0 && body_flag == 0) {
			body_flag = 1;
			start = clock();
		}

		if (body->total == 0 && body_flag == 1) {
			body_flag = 0;
			end = clock();
			printf("start = %.3lf\n", (double)start / CLOCKS_PER_SEC); //시작 시간에 대한 정보 출력
			printf("end = %.3lf\n", (double)end / CLOCKS_PER_SEC); //종료 시간에 대한 정보 출력
			printf("total Time : %.3fs\n", (double)(end - start) / CLOCKS_PER_SEC); //검출된 시간에 대한 정보 출력

			if ((double)(end - start) / CLOCKS_PER_SEC > 5.0) { //인식된 시간이 5초 이상인 경우
				sprintf(image_name, "./Pictures/Capture_%d.jpg", count); //.jpg형식으로 사진이 자동 저장됨
				cvSaveImage(image_name, img);
				system("scp -P 22 ./Pictures/Capture_0.jpg root@주소:../var/www/html/tmp/tmp_project/"); //서버에 사진을 전송
			}
		}

		for (int i = 0; i < (body ? body->total : 0); i++) { //검출한 상체에 중심점 잡아서 동그라미 그리기
			CvRect *r = (CvRect *)cvGetSeqElem(body, i);
			CvPoint center;
			center.x = cvRound((r->x + r->width*0.5)*scale);
			center.y = cvRound((r->y + r->width*0.5)*scale);
			int radius = cvRound((r->width + r->height)*0.25*scale);
			cvCircle(img, center, radius, colors, 3, 8, 0);
		}
	}

	cvShowImage("Result", img); //결과 영상 디스플레이
	cvReleaseImage(&gray);
	cvReleaseImage(&small_Img);
}
```

### ③ Application
- [SmartDoorLock_application.zip](https://github.com/jeonggunlee/Capstone-Design/files/2133062/SmartDoorLock_application.zip)

![default](https://user-images.githubusercontent.com/37283269/41850383-4ddee1d4-78bf-11e8-836d-dcadafb8ec4a.jpg)

activity_main_xml
-----------
- [activity_main_xml.txt](https://github.com/jeonggunlee/Capstone-Design/files/2133308/activity_main_xml.txt)

```
<?xml version="1.0" encoding="utf-8"?>
<android.support.constraint.ConstraintLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    tools:context=".MainActivity">

    <LinearLayout
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        android:orientation="vertical"
        tools:layout_editor_absoluteX="0dp"
        tools:layout_editor_absoluteY="197dp">

        <Button
            android:id="@+id/passwd"
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:text="1회용 비밀번호 생성"
            tools:layout_editor_absoluteX="16dp"
            tools:layout_editor_absoluteY="214dp" />

        <Button
            android:id="@+id/cctv"
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:text="CCTV 확인"
            tools:layout_editor_absoluteX="218dp"
            tools:layout_editor_absoluteY="214dp" />

    </LinearLayout>

</android.support.constraint.ConstraintLayout>
```

AndoridManifest_xml
-----------
- [AndoridManifest_xml.txt](https://github.com/jeonggunlee/Capstone-Design/files/2133311/AndoridManifest_xml.txt)

```
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools"
    package="com.example.lg.smartdoorlock">
    <uses-permission android:name="android.permission.INTERNET"/>
    <application
        android:allowBackup="true"
        android:icon="@mipmap/ic_launcher"
        android:label="@string/app_name"
        android:roundIcon="@mipmap/ic_launcher_round"
        android:supportsRtl="true"
        android:theme="@style/AppTheme">
        <activity android:name=".MainActivity">
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />

                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>
        <activity android:name=".PasswdActivity" />
        <activity android:name=".CctvActivity"
            tools:ignore="DuplicateActivity" />
    </application>
</manifest>
```

cctv_main_xml
-----------
- [cctv_main_xml.txt](https://github.com/jeonggunlee/Capstone-Design/files/2133314/cctv_main_xml.txt)

```
<?xml version="1.0" encoding="utf-8"?>
<android.support.constraint.ConstraintLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    tools:context=".CctvActivity">

    <ScrollView
        android:id="@+id/scroll"
        android:layout_width="match_parent"
        android:layout_height="match_parent">

        <LinearLayout
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:orientation="vertical">

            <ImageView
                android:id="@+id/imageView"
                android:layout_width="match_parent"
                android:layout_height="wrap_content"
                android:src="@android:color/background_light" />
        </LinearLayout>
    </ScrollView>

</android.support.constraint.ConstraintLayout>
```

CctvActivity_java
-----------
- [CctvActivity_java.txt](https://github.com/jeonggunlee/Capstone-Design/files/2133318/CctvActivity_java.txt)


```
package com.example.lg.smartdoorlock;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.pm.ActivityInfo;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.os.StrictMode;
import android.renderscript.ScriptGroup;
import android.widget.ImageView;
import android.widget.ScrollView;
import android.view.Menu;
import android.widget.TextView;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.io.File;
import java.util.ArrayList;

public class CctvActivity extends Activity {
    ImageView imView;
    ScrollView scroll;
    String imgUrl = "http://210.115.xxx.xx/tmp/tmp_project/Capture_0.jpg"; //이미지 저장되어있는 url 주소
    Bitmap bmImg; //이미지 저장하기 위한 bitmap
    back task;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.cctv_main);
        task = new back();

        scroll = (ScrollView)findViewById(R.id.scroll);
        imView = (ImageView) findViewById(R.id.imageView);
        task.execute(imgUrl); //url주소 넘겨줌
    }

    //비동기화
    private class back extends AsyncTask<String, Integer, Bitmap> {
        protected Bitmap doInBackground(String... urls) {
            try {
                if(this.isCancelled()){
                    return null;
                }

                //url 연결
                URL myFileUrl = new URL(urls[0]);
                HttpURLConnection conn = (HttpURLConnection) myFileUrl.openConnection();
                conn.setDoInput(true);
                conn.connect();

                InputStream is = conn.getInputStream();

                //이미지 갖고오기
                bmImg = BitmapFactory.decodeStream(is);
            } catch (IOException e) {
                e.printStackTrace();
            }
            return bmImg;
        }

        protected void onCancelled(){
            super.onCancelled();
        }

        //doInBackground()로 부터 리턴된 값이 onPostExecute()의 매개변수로 넘어옴
        //갖고온 이미지 이미지뷰에 set
        protected void onPostExecute(Bitmap img) {
            imView.setImageBitmap(img);
        }
    }

}
```

MainActivity_java
-----------
- [Uploading MainActivity_java.txt…]()

```
package com.example.lg.smartdoorlock;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private Button passwd, cctv;
    Intent intent_p, intent_c; //다음 화면으로 넘어가기 위해 필요한 것
    // intent_p 는 비밀번호 생성버튼에 대한 인텐트, intent_c는 cctv버튼에 대한 인텐트

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        setContentView(R.layout.activity_main);
        init();
    }

    @Override
    public void onClick(View v) {
        switch(v.getId()){
            case R.id.passwd : //passwd 버튼을누르면
                intent_p = new Intent(MainActivity.this, PasswdActivity.class); //mainactivity화면에서  passwdactivity화면으로 넘어가는 인텐트 생성
                startActivity(intent_p); //그 인텐트를 실행
                break;
            case R.id.cctv : //cctv 버튼을 누르면
                intent_c = new Intent(MainActivity.this, CctvActivity.class); //mainactivity화면에서  cctvactivity화면으로 넘어가는 인텐트 생성
                startActivity(intent_c);//그 인텐트를 실행
                break;
        }
    }

    public void init(){
        passwd = (Button)findViewById(R.id.passwd);
        cctv = (Button)findViewById(R.id.cctv);

        passwd.setOnClickListener(this);
        cctv.setOnClickListener(this);
    }
}

```

passwd_main_xml
-----------
- [passwd_main_xml.txt](https://github.com/jeonggunlee/Capstone-Design/files/2133325/passwd_main_xml.txt)

```
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:baselineAligned="false"
    android:orientation="vertical">

    <TextView
        android:id="@+id/tv_outPut"
        android:layout_width="match_parent"
        android:layout_height="60dp"
        android:text="1회용 비밀번호가 생성됩니다."
        android:textAlignment="center"
        android:textAllCaps="false"
        android:textSize="30sp" />

    <Button
        android:id="@+id/newpasswd"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:text="1회용 비밀번호 생성" />
</LinearLayout>

```

PasswdActivity_java
-----------
- [PasswdActivity_java.txt](https://github.com/jeonggunlee/Capstone-Design/files/2133329/PasswdActivity_java.txt)


```
package com.example.lg.smartdoorlock;

import android.app.Activity;
import android.content.ContentValues;
import android.content.pm.ActivityInfo;
import android.os.AsyncTask;
import android.os.Build;
import android.os.StrictMode;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.NetworkInterface;
import java.net.URL;
import java.util.Map;

public class PasswdActivity extends AppCompatActivity implements View.OnClickListener{

    private Button newpasswd; //1회용 비밀번호 생성하는 버튼변수
    private TextView tv_outPut; //랜덤으로 생성된 비밀번호를 보여줄 텍스트뷰 변수
    String url = "http://210.115.xxx.xx/tmp/connection.php"; //1회용 비밀번호 생성해주는 php 파일 주소

    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT); //화면 세로로 고정
        setContentView(R.layout.passwd_main);
        init();
    }

    //비동기화
    public class NetworkTask extends AsyncTask<Void, Void, String>{
        private String url;
        private ContentValues values;

        public NetworkTask(String url, ContentValues values) {

            this.url = url;
            this.values = values;
        }

        @Override
        protected String doInBackground(Void... params) {

            String result; // 요청 결과를 저장할 변수.
            RequestHttpURLConnection requestHttpURLConnection = new RequestHttpURLConnection(); //url 연결 객체
            result = requestHttpURLConnection.request(url, values); // 해당 URL로 부터 결과물을 얻어옴

            return result;
        }

        @Override
        protected void onPostExecute(String s) {
            super.onPostExecute(s);

            //doInBackground()로 부터 리턴된 값이 onPostExecute()의 매개변수로 넘어오므로 s를 출력함.
            tv_outPut.setText(s);
        }
    }

    public void onClick(View v){ //버튼 클릭시
        switch(v.getId()){
            case R.id.newpasswd :
                NetworkTask networkTask = new NetworkTask(url, null); //클릭시 비동기화 객체 실행
                networkTask.execute();
                newpasswd.setEnabled(false); //중복 비밀번호 생성 방지 - 한번 버튼이 실행되면 실행 안되도록 함
                break;
        }
    }

    public void init(){
        newpasswd = (Button)findViewById(R.id.newpasswd);

        tv_outPut = (TextView)findViewById(R.id.tv_outPut);

        newpasswd.setOnClickListener(this);
    }

}

```
RequestHttpURLConnection_java
-----------
- [Uploading RequestHttpURLConnection_java.txt…]()

```
package com.example.lg.smartdoorlock;

import android.content.ContentValues;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Map;

public class RequestHttpURLConnection {

    public String request(String _url, ContentValues _params){

        // HttpURLConnection 참조 변수.
        HttpURLConnection urlConn = null;
        // URL 뒤에 붙여서 보낼 파라미터.
        StringBuffer sbParams = new StringBuffer();


        //StringBuffer에 파라미터 연결
        // 보낼 데이터가 없으면 파라미터를 비운다.
        if (_params == null)
            sbParams.append("");
            // 보낼 데이터가 있으면 파라미터를 채운다.
        else {
            // 파라미터가 2개 이상이면 파라미터 연결에 &가 필요하므로 스위칭할 변수 생성.
            boolean isAnd = false;
            // 파라미터 키와 값.
            String key;
            String value;

            for(Map.Entry<String, Object> parameter : _params.valueSet()){
                key = parameter.getKey();
                value = parameter.getValue().toString();

                // 파라미터가 두개 이상일때, 파라미터 사이에 &를 붙인다.
                if (isAnd)
                    sbParams.append("&");

                sbParams.append(key).append("=").append(value);

                // 파라미터가 2개 이상이면 isAnd를 true로 바꾸고 다음 루프부터 &를 붙인다.
                if (!isAnd)
                    if (_params.size() >= 2)
                        isAnd = true;
            }
        } //else 끝


         //HttpURLConnection을 통해 web의 데이터를 가져온다.
        try{
            //url 연결
            URL url = new URL(_url);
            urlConn = (HttpURLConnection) url.openConnection();

            // [2-1]. urlConn 설정.
            urlConn.setRequestMethod("POST"); // URL 요청에 대한 메소드 설정 : POST.
            urlConn.setDoInput(true);
            urlConn.setRequestProperty("Accept-Charset", "UTF-8"); // Accept-Charset utf-8로 설정.
            urlConn.setRequestProperty("Content-Type", "application/x-www-form-urlencoded;charset=UTF-8");

            // [2-2]. parameter 전달 및 데이터 읽어오기.
            String strParams = sbParams.toString(); //sbParams에 정리한 파라미터들을 스트링으로 저장. 예)id=id1&pw=123;
            OutputStream os = urlConn.getOutputStream();
            os.write(strParams.getBytes("UTF-8")); // 출력 스트림에 출력.
            os.flush(); // 출력 스트림을 플러시하고 버퍼링 된 모든 출력 바이트를 강제 실행.
            os.close(); // 출력 스트림을 닫고 모든 시스템 자원을 해제.

            //연결 요청 확인.
            // 실패 시 null을 리턴하고 메서드를 종료.
            if (urlConn.getResponseCode() != HttpURLConnection.HTTP_OK) {
                return null;
            }

            // 요청한 URL의 출력물을 BufferedReader로 받는다.
            BufferedReader reader = new BufferedReader(new InputStreamReader(urlConn.getInputStream(), "UTF-8"));

            // 출력물의 라인과 그 합에 대한 변수.
            String line;
            String page = "";

            // 라인을 받아와 합친다.
            while ((line = reader.readLine()) != null){
                page += line;
            }

            reader.close();
            return page;

        } catch (MalformedURLException e) { // for URL.
            e.printStackTrace();
        } catch (IOException e) { // for openConnection().
            e.printStackTrace();
        } finally {
            if (urlConn != null)
                urlConn.disconnect();
        }

        return null;

    }

}

```

### ④ RasberryPi
servo.c
-----------
- [servo.txt](https://github.com/jeonggunlee/Capstone-Design/files/2133157/servo.txt)

- 서보모터 제어를 위한 소스

```
#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <mysql.h>
#include <errno.h>


#define SERVO 1


#define DB_HOST "210.115.229.91"
#define DB_UWER "root"
#define DB_PASS "dblab2316"
#define DB_NAME "passwd"
#define CHOP(x) x[strlen(x) - 1]

int main()
{
	char str;
	MYSQL *connection=NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_stat;

	char d_c[10];
	char query[255];

	my_sql(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if(connetion == NULL)
	{
		fprintf(stderr, "%s", mysql_error(connection));
		exit(1);
	}
	query_stat = mysql_query(connection, "seket * from password");

	if(query_stat != 0)
	{
		fprintf(stderr, "%s", mysql_error(connection));
		exit(1);
	}
	
	sql_result = mysql_store_result(connection);

	printf("door_check db data : ");
	while((sql_row = mysql_fetch_row(sql_result))!=NULL)
	{
		printf("%s", sql_row[1]);
	}

	mysql_free_result(sql_result);

	if(wiringPiSetup() == -1)
	 return 1;

	softPwmCreate(SERVO, 0, 200);

	while(1)
	{
		//fputs("select c, r, l, q : ", stdout);
		printf("data : ");

		//scanf("%c", &str);
		//getchar();
		
		//if(str == 'c')
		//{
			//softPwmWrite(SERVO, 15);
			//break;
		//}
		if(sql_row[1] == "true"){	// 문 열림 제어
			softPwmWrite(SERVO, 24);
			break;
		}
		//else if(str == 'r')
		else if(sql_row[1] == "false"){	// 문 닫힘 제어
			softPwmWrite(SERVO, 5);
		}
		//else if(str == 'l')
			
		//else if(str == 'q')
		//	return 0;
	
	}

	mysql_close(connection);
	return 0;
}

```



**4. 실제 구현 영상**
===========
![default](https://user-images.githubusercontent.com/37283269/41851863-4b52cdd6-78c4-11e8-9a0e-462bda2c51c6.jpeg)

- [Smart DoorLock](https://youtu.be/PY2b_K4tPGk)

**5. 활용 방안 및 기대효과**
===========

 통계청 '한국의 사회동향'에 따르면, 2010년에 아파트는 전국의 총 주택 1400호 가운데 59.0%에 해당하는 820만 호 가까이로 늘었습니다. 특히 1995~2000년, 2005~2010년 동안은 아파트 증가분이 총 주택 증가분을 넘어섰습니다. 2014년 ‘현재 한국인이 향후 거주하고 싶은 주택유형’ 중 아파트가 48.1%를 차지하고 있으며 아파트는 한국인의 중요한 주거형태로 자리 잡고 있습니다.

 지난 2011년 한해동안 발생한 단순 주거침입 범죄는 모두 6천390건입니다. 특히 ‘대검찰청 범죄분석통계’에 따르면 2010년 발생한 성폭력 범죄 중 26.6%에 해당하는 5천298건이 아파트나 연립주택 등 주거지에서 발생했으며, 살인 범죄 역시 43.9%인 554건이 주거지에서 벌어진 것으로 분석됐습니다.

 이러한 아파트의 공동 현관문에 ‘Smart DoorLock’을 설치하여, 패턴을 이용하여 기억하기 쉽게 잠금 해제를 할 수 있고, 익숙하지 않은 사용자들에게는 번호로 바꾸어 잠금 해제를 이용할 수도 있습니다. 또한, 사용자들에게 보행자 검출이 가능한 CCTV의 기능으로 주거침입으로 인한 범죄 발생의 예방이 기대됩니다. 

 이처럼 잠금해제 방식이 사용자들에게 익숙하고, 범죄예방도 가능하다고 느껴져, 충분히 ‘Smart DoorLock’은 이용 가치가 있다고 판단됩니다. 

![-](https://user-images.githubusercontent.com/37283269/41852235-81e71d06-78c5-11e8-9065-ca28acb355b5.jpg)
![-](https://user-images.githubusercontent.com/37283269/41852244-88e55780-78c5-11e8-9343-849874e98c87.jpg)


**6. 발표자료**
===========

- [종설_week1 ppt.pdf](https://github.com/jeonggunlee/Capstone-Design/files/2133106/_week1.ppt.pdf)
- [종설_week2 ppt.pdf](https://github.com/jeonggunlee/Capstone-Design/files/2133107/_week2.ppt.pdf)
- [종설_week3 ppt.pdf](https://github.com/jeonggunlee/Capstone-Design/files/2133108/_week3.ppt.pdf)
- [종설_week4 ppt.pdf](https://github.com/jeonggunlee/Capstone-Design/files/2133109/_week4.ppt.pdf)
- [종설_week5 ppt.pdf](https://github.com/jeonggunlee/Capstone-Design/files/2133111/_week5.ppt.pdf)
- [종설_week6 ppt.pdf](https://github.com/jeonggunlee/Capstone-Design/files/2133112/_week6.ppt.pdf)
- [종설_week7 ppt.pdf](https://github.com/jeonggunlee/Capstone-Design/files/2133113/_week7.ppt.pdf)
- [종설_week9.ppt.pdf](https://github.com/jeonggunlee/Capstone-Design/files/2133114/_week9.ppt.pdf)
- [종설_week10.pdf](https://github.com/jeonggunlee/Capstone-Design/files/2133116/_week10.pdf)
- [종설_최종 ppt.pdf](https://github.com/jeonggunlee/Capstone-Design/files/2133117/_.ppt.pdf)
