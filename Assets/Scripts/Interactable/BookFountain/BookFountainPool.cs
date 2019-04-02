using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BookFountainPool : SoundListener
{
    public WaterSpout[] spouts;
    public WaterRise water;
    public float riseDelay = 0.3f;
    int waterLevel = 0;

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

    public override void OnSound(Note n)
    {
        if (listening) {
            waterLevel = 1;
            StartCoroutine(StartWater());
        }
    }

    public override void OnFail()
    {
        throw new System.NotImplementedException();
    }

    public override void OnSoundFinish(Note n)
    {
        
    }
}
