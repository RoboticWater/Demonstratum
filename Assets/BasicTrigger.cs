using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class BasicTrigger : MonoBehaviour
{
    public UnityEvent e;
    private void OnTriggerEnter(Collider other) {
        e.Invoke();
    }
}
