using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class ChordListener : Persistent, SoundReactor
{
    [SerializeField] protected Chord activationChord;
    protected bool listening;

    public abstract void OnSound(float intensity);

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

    private void TestChord(float[] notes) {

    }
}
