using UnityEngine;
using System.Collections;
using System.IO.Ports;

public class Move : MonoBehaviour {
	private Rigidbody rb;
    private Transform tf;
	public SerialPort serial= new SerialPort("\\\\.\\COM2",115200);
	int id = 0;
	bool hall;
	Vector3 dataAccel = new Vector3(0,0,0);
    int prox = 0;

	Vector3 accelOffsets = new Vector3(-117,-117,117);	//	the z-axis is a special little butterfly with its own "quirks"
    Vector3 proxoffset = new Vector3(1f, 1f, 1f);

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

        //First byte AKA Hall
		id = serial.ReadByte ();
		dataAccel = Vector3.zero;
		switch(id){
		case 0xFF: hall = true;
                break;//	1111 1111	Accel, hall down
		case 0xF0: hall = false;	//	1111 0000	Accel, hall up
			    break;
		default:	//	Frame mismatch or bit error
			print("Frame or bit error");
			    break;
		}

        //2nd, 3rd and 4th byte, Acceleration
        dataAccel.x = serial.ReadByte();
        dataAccel.z = -serial.ReadByte();   //	The y-axis in unity is the
        dataAccel.y = serial.ReadByte();    //	z-axis in the real world
        dataAccel += accelOffsets;
        print(dataAccel);
        rb.AddForce (dataAccel,ForceMode.Acceleration);

        //Last byte AKA proximity
        prox = 50/(serial.ReadByte()); //Grows at closer range (0x05) and at max range (0x90) gets smaller
        print(prox);
        tf.localScale = new Vector3(prox, prox, prox) + proxoffset; //Size should be between 1.03-11 w offset
    }
}
