using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Chord : MonoBehaviour
{
    public float[] frequencies;
    Image icon;

    private void Start() {
        icon = GetComponent<Image>();   
    }
}
