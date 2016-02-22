using UnityEngine;
using System.Collections;



public class camfollow : MonoBehaviour {
	private Transform playt;


	// Use this for initialization
	void Start (){
		
		playt = GameObject.FindGameObjectWithTag ("Player").transform;

	}

	// Update is called once per frame
	void Update () {

		transform.position = new Vector3(playt.position.x+10,playt.position.y+10f,playt.position.z-10f);
	}
}
