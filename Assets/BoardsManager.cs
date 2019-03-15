using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoardsManager : ChordListener
{
    public Wood[] wood;
    public GameObject woodSelectorPrefab;
    private void OnTriggerEnter(Collider other) {
        Instantiate(woodSelectorPrefab, wood[0].transform);
        foreach (Wood w in wood) {
            w.Break();
        }
    }
}
