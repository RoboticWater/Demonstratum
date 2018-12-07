using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityStandardAssets.Characters.FirstPerson;

public class Player : MonoBehaviour
{
    FirstPersonController firstPerson;
    // Start is called before the first frame update
    void Start()
    {
        firstPerson = GetComponent<FirstPersonController>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetButtonDown("Switch")) {
            firstPerson.m_MouseLook.SetCursorLock(!firstPerson.m_MouseLook.lockCursor);
        }
    }
}
