using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaterDrip : MonoBehaviour
{
    public float rippleTimeOffset;
    public float dripWait = 0.1f;
    public float dripProbability = 0.01f;
    public ParticleSystem drop;
    public ParticleSystem ripple;

    void FixedUpdate()
    {
        if (Random.Range(0f, 1f) < dripProbability) {
            StartCoroutine(Drip());
        }
    }

    IEnumerator Drip() {
        drop.Emit(1);
        yield return new WaitForSeconds(rippleTimeOffset);
        ripple.Emit(1);
        yield return new WaitForSeconds(dripWait);
    }
}
