using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Chord : MonoBehaviour
{
    public float[] frequencies;
    [HideInInspector] public Color ChordColor;
    [HideInInspector] public Image icon;

    private void Start() {
        icon = GetComponent<Image>();  
        ChordColor = GetComponent<Image>().color; 
    }
}
