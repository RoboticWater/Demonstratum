using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoardsManager : ChordListener
{
    public Wood[] wood;
    private void OnTriggerEnter(Collider other) {
        foreach (Wood w in wood) {
            w.Break();
        }
    }
}
