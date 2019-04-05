using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;

public class VineBridge : Persistent
{

    public float startVal;
    public float endVal;
    public AnimationCurve growCurve;
    public float growTime = 0.5f;

    Material[] mats;

    bool growing;
    bool grown;

    private void Start() {
        object g = GameManager.instance.GetObject(this, "_grown");
        if (g != null) {
            foreach (Material m in mats)
                m.SetFloat("_Distance", (bool) g ? endVal : startVal);
        }
        mats = GetComponentsInChildren<Renderer>().Select(r => r.material).ToArray();
    }

    public void ToggleGrow() {
        if (!growing)
            StartCoroutine(GrowRoutine());
    }

    IEnumerator GrowRoutine() {
        growing = true;
        float lastTime = Time.timeSinceLevelLoad;
        float perc = grown ? 1 : 0;
        do {
            perc += (grown ? -1 : 1) * (Time.timeSinceLevelLoad - lastTime) / growTime;
            lastTime = Time.timeSinceLevelLoad;
            foreach (Material m in mats)
                m.SetFloat("_Distance", Mathf.Lerp(startVal, endVal, growCurve.Evaluate(perc)));
            yield return null;
        } while(perc <= 1 && perc >= 0);
        foreach (Material m in mats)
            m.SetFloat("_Distance", grown ? endVal : startVal);
        grown = !grown;
        growing = false;
    }

    private void OnDestroy() {
        GameManager.instance.DeregsiterPersistent(this);
        foreach (Material m in mats)
            Destroy(m);
    }

    public override void Save()
    {
        GameManager.instance.SetObject(this, "_grown", grown);
    }
}
