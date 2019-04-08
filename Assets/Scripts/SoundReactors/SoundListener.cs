using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public abstract class SoundListener : Persistent, SoundReactor
{
    protected bool listening;
    [SerializeField] protected UnityEvent soundEvent;

    public abstract void OnSound(Note n, NoteLine l);
    public abstract void OnSoundFinish(Note n, NoteLine l);
    public abstract void OnFail();

    private void OnTriggerEnter(Collider other) {
        if (other.GetComponent<Player>()) {
            listening = true;
        }
    }
    
    private void OnTriggerExit(Collider other) {
        if (other.GetComponent<Player>()) {
            listening = false;
        }
    }

    private void TestSound(float[] notes) {

    }
}
