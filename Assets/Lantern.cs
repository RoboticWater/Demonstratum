using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lantern : MonoBehaviour
{
    Material m;

    bool lighting;
    bool lit;

    private void Awake() {
        m = GetComponent<Renderer>().material;
    }

    private void OnDestroy() {
        Destroy(m);
    }

    public ToggleLight() {
        if (!lighting)
            StartCoroutine(ToggleLightRoutine());
    }

    IEnumerator ToggleLightRoutine() {

    }
}
