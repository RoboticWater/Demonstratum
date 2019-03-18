using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WoodSelector : Selector
{
    public Wood[] wood;
    public float outlineWidth = 0.1f;

    public override void SetHighlight(bool on) {
        foreach (Wood w in wood) {
            w.material.SetFloat("_OutlineWidth", on ? outlineWidth : 0);
        }
    }

    public override void Select() {
        
    }
}
