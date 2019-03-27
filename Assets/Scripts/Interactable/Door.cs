using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Door : MonoBehaviour {
    public Animator[] animators;
    public bool isOpen;

    private void Start() {
        animators = GetComponentsInChildren<Animator>();    
    }

    public void Open() {
        isOpen = true;
        foreach (Animator a in animators) {
            a.SetBool("Open", true);
        }
    }

    public void Close() {
        isOpen = false;
        foreach (Animator a in animators) a.SetBool("Open", false);
    }
}