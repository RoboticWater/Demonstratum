using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Flower : SoundReactor
{
    public Material m;
    public Color c0, c1;
    
    private void Start() {
        m.SetColor("_ColorFlower", Color.Lerp(c0, c1, 0));
    }

    public void OnSound(float intensity) {
        m.SetColor("_ColorFlower", Color.Lerp(c0, c1, intensity));
    }
}
