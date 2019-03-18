using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoardsManager : ChordListener
{
    public Wood[] wood;
    public GameObject woodSelectorPrefab;
    public bool broken;

    private void Start()
    {
        if (GameManager.instance.GetObject(GetInstanceID() + "_open") != null) {

        }
    }

    private void OnTriggerEnter(Collider other) {
        if (!broken) {
            broken = true;
            // GameObject woodSelector = Instantiate(woodSelectorPrefab, wood[0].transform);
            // woodSelector.GetComponent<WoodSelector>().wood = wood;
            foreach (Wood w in wood) {
                w.Break();
            }
        }
    }
}
