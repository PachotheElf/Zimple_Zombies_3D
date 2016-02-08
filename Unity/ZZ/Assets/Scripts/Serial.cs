using UnityEngine;
using System.Collections;
using System.IO.Ports;

public class Serial : MonoBehaviour {
	public SerialPort serial= new SerialPort("\\\\.\\COM2",115200);
	public GameObject personaje;

	// Use this for initialization
	void Start () {
		serial.Open();	
		print(serial.IsOpen);
	}
	
	// Update is called once per frame
	void Update () {

			int datanum = serial.ReadByte ();
			print (datanum);
	}
}
