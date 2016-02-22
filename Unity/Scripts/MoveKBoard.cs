using UnityEngine;
using System.Collections;
using System.IO.Ports;

public class MoveKBoard : MonoBehaviour
{
    private Rigidbody rb;
    private Transform tf;
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        tf = GetComponent<Transform>();
        Time.fixedDeltaTime = 0.014f;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (Input.GetKey(KeyCode.W)) rb.AddForce(new Vector3(0f, 0f, 10f), ForceMode.Acceleration) ;
        if (Input.GetKey(KeyCode.S)) rb.AddForce(new Vector3(0f, 0f, -10f), ForceMode.Acceleration);
        if (Input.GetKey(KeyCode.A)) rb.AddForce(new Vector3(-10f, 0f, 0f), ForceMode.Acceleration);
        if (Input.GetKey(KeyCode.D)) rb.AddForce(new Vector3(10f, 0f, 1f), ForceMode.Acceleration);
        if (Input.GetKey(KeyCode.T))
        {
            tf.localScale += new Vector3(1f, 1f, 1f);
        }
        if (Input.GetKey(KeyCode.Y))
        {
            tf.localScale += new Vector3(-1f, -1f, -1f);
        }
    }
}
