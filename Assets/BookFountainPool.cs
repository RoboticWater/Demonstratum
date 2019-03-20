using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BookFountainPool : ChordListener
{
    public WaterSpout[] spouts;
    public WaterRise water;
    public float riseDelay = 0.3f;
    int waterLevel = 0;

    private void OnTriggerEnter(Collider other) {
        waterLevel = 1;
        StartCoroutine(StartWater());
    }

    IEnumerator StartWater() {
        foreach (WaterSpout s in spouts) {
            s.StartSpout();
        }
        yield return new WaitForSeconds(riseDelay);
        water.StartRise();
    }
    
    public override void Save() {
        GameManager.instance.SetObject(this, "_waterLevel", waterLevel);
    }
}
