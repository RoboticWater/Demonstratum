using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BookFountainPool : ChordListener
{
    public WaterSpout[] spouts;
    public WaterRise water;
    public float riseDelay = 0.3f;

    private void OnTriggerEnter(Collider other) {
        StartCoroutine(StartWater());
    }

    IEnumerator StartWater() {
        foreach (WaterSpout s in spouts) {
            s.StartSpout();
        }
        yield return new WaitForSeconds(riseDelay);
        water.StartRise();
    }
}
