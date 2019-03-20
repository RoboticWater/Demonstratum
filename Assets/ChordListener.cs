using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class ChordListener : Persistent
{
    protected bool listening;

    private void OnTriggerEnter(Collider other) {
        if (other.GetComponent<Player>() != null) {
            listening = true;
        }
    }
    
    private void OnTriggerExit(Collider other) {
        if (other.GetComponent<Player>() != null) {
            listening = false;
        }
    }
}
