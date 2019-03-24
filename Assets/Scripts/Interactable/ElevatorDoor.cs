using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ElevatorDoor : MonoBehaviour
{
    Animator animator;
    public bool isOpen;

    private void Start() {
        animator = GetComponent<Animator>();    
    }
    
    public void Open() {
        isOpen = true;
        animator.SetBool("Open", true);
    }

    public void Close() {
        isOpen = false;
        animator.SetBool("Open", false);
    }
}
