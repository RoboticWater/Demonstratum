using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Button : Selector
{
    public float outlineWidth = 0.1f;
    public float highlightTime = 0.1f;
    public AnimationCurve highlightCurve;

    bool highlightOn;
    bool highlighting;

    Material m;

    public override void Select()
    {
        throw new System.NotImplementedException();
    }

    public override void SetHighlight(bool on)
    {
        highlightOn = on;
        if (!highlighting) {
            StartCoroutine(Highlight());
        }
    }

    IEnumerator Highlight() {
        highlighting = true;
        float lastTime = Time.timeSinceLevelLoad;
        float perc = highlightOn ? 0 : 1;
        do {
            perc += (highlightOn ? 1 : -1) * (Time.timeSinceLevelLoad - lastTime) / highlightTime;
            lastTime = Time.timeSinceLevelLoad;
            m.SetFloat("_OutlineWidth", Mathf.Lerp(0, outlineWidth, highlightCurve.Evaluate(perc)));
            yield return null;
        } while(perc <= 1 && perc >= 0);
        m.SetFloat("_OutlineWidth", highlightOn ? outlineWidth : 0);
        highlighting = false;
    }

    private void OnDestroy() {
        GameManager.instance.DeregsiterPersistent(this);
        Destroy(m);
    }
}