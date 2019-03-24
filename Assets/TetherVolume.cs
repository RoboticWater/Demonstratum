using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TetherVolume : MonoBehaviour
{
    Transform previousParent;
    bool tethered;

    private void OnTriggerEnter(Collider other) {
        Player p = other.GetComponent<Player>();
        if (p) {
            tethered = true;
            previousParent = p.transform.parent;
            p.transform.SetParent(transform);
        }
    }

    private void OnTriggerExit(Collider other)
    {
        Player p = other.GetComponent<Player>();
        if (p) {
            tethered = false;
            p.transform.SetParent(previousParent);
        }
    }
}
