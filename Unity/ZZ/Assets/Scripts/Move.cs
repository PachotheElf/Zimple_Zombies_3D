using UnityEngine;
using System.Collections;
using System.IO.Ports;

public class Move : MonoBehaviour {
	public Rigidbody rb;
	public SerialPort serial= new SerialPort("\\\\.\\COM2",115200);
	int id = 0;
	bool hall;
	Vector3 dataAccel = new Vector3(0,0,0);

	Vector3 accelOffsets = new Vector3(-117,-117,117);	//	the z-axis is a special little butterfly with its own "quirks"
	// Use this for initialization
	void Start () {
		rb = GetComponent<Rigidbody>();
		serial.ReadBufferSize = 8;
		serial.ReadTimeout = 1;
		serial.Open();	
		print(serial.IsOpen);
		Time.fixedDeltaTime = 0.014f;
	}
	
	// Update is called once per frame
	void FixedUpdate () {
		id = serial.ReadByte ();
		dataAccel = Vector3.zero;
		switch(id){
		case 0xFF:	//	1111 1111	Accel, hall down
		case 0xF0:	//	1111 0000	Accel, hall up
			hall = (id & 0xF) > 0 ? true : false;	//	Getting the hall sensor value from id
			dataAccel.x = serial.ReadByte ();
			dataAccel.z = -serial.ReadByte ();	//	The y-axis in unity is the
			dataAccel.y = serial.ReadByte ();	//	z-axis in the real world
			dataAccel += accelOffsets;
			print (dataAccel);
			break;
		default:	//	Frame mismatch or bit error
			print("Frame or bit error");
			break;
		}
		rb.AddForce (dataAccel,ForceMode.Acceleration);
	}
}
