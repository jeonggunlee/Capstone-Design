This is a directory for the Team of DigitalDoorLock
지금까지 블루투스를 활성화 하고 기기 검색을 하는 단계까지 진행하였다.



이전 글 : 블루투스 활성화 글 보기, 블루투스 기기 검색하기 글 보기



저번 프로젝트에 이어 블루투스 연결하는 단계를 포스팅 하겠다.



검색한 기기에 연결하기 위해서는 ConnectThread와 ConnectedThread에 대해서 알고 있어야 한다.

BluetoothService.java 파일에 ConnectThread와 ConnectedThread 클래스를 내부 클래스로 삽입해준다.



1. ConnectThread



BluetoothService.java

public class BluetoothService {
	... // 이전 부분 생략

	// RFCOMM Protocol
	private static final UUID MY_UUID = 
		UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
	
	private BluetoothAdapter btAdapter;
	
	private ConnectThread mConnectThread;
	private ConnectedThread mConnectedThread;

	... // 이전 부분 생략
		
	private class ConnectThread extends Thread {
		private final BluetoothSocket mmSocket;
		private final BluetoothDevice mmDevice;

		public ConnectThread(BluetoothDevice device) {
			mmDevice = device;
			BluetoothSocket tmp = null;
			
			// 디바이스 정보를 얻어서 BluetoothSocket 생성
			try {
                tmp = device.createRfcommSocketToServiceRecord(MY_UUID);
            } catch (IOException e) {
                Log.e(TAG, "create() failed", e);
            }
			mmSocket = tmp;
		}

		public void run() {
			Log.i(TAG, "BEGIN mConnectThread");
			setName("ConnectThread");
			
			// 연결을 시도하기 전에는 항상 기기 검색을 중지한다.
			// 기기 검색이 계속되면 연결속도가 느려지기 때문이다.
			btAdapter.cancelDiscovery();

			// BluetoothSocket 연결 시도
			try {
				// BluetoothSocket 연결 시도에 대한 return 값은 succes 또는 exception이다.
				mmSocket.connect();
				Log.d(TAG, "Connect Success");
				
			} catch (IOException e) {
				connectionFailed();		// 연결 실패시 불러오는 메소드
				Log.d(TAG, "Connect Fail");
				
				// socket을 닫는다.
				try {
					mmSocket.close();
				} catch (IOException e2) {
					Log.e(TAG,
							"unable to close() socket during connection failure",
							e2);
				}
				// 연결중? 혹은 연결 대기상태인 메소드를 호출한다.
				BluetoothService.this.start();
				return;
			}

			// ConnectThread 클래스를 reset한다.
			synchronized (BluetoothService.this) {
				mConnectThread = null;
			}

			// ConnectThread를 시작한다.
			connected(mmSocket, mmDevice);
		}

		public void cancel() {
			try {
				mmSocket.close();
			} catch (IOException e) {
				Log.e(TAG, "close() of connect socket failed", e);
			}
		}
	}
}


여기서 UUID라는 변수가 있는데 이것은 Bluetooth 통신 프로토콜이다. 블루투스 통신을 할 때 그에 맞는 프로토콜로 통신을 해 주어야 한다. 간단한 예로 블루투스 기능이 지원되는 이어폰과의 통신을 원한다면 그에 맞는 프로토콜을 사용하여야 하고, 스마트폰 끼리의 블루투스 통신은 또 그에 맞는 프로토콜을 사용해야 한다. 

지금 위에서 사용한 프로토콜은 아마 스마트폰끼리의 블루투스 통신을 하는데 사용하는 프로토콜일 것이다.



블루투스 프로토콜 종류 보기 - [안드로이드] 블루투스 프로토콜 UUID 리스트



출처: http://dsnight.tistory.com/44?category=485244 [기초 탄탄 영상털이's Stroy]
