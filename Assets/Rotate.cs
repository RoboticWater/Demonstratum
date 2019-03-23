using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rotate : MonoBehaviour
{
    public Vector3 rotateVector;

    // Update is called once per frame
    void Update()
    {
        transform.eulerAngles += rotateVector * Time.deltaTime;
    }
}
