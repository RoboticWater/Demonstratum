using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIChord : Chord
{
    public bool acquired;
    bool acquiring;
    public AnimationCurve acquireCurve;
    public float acquireTime = 0.5f;
    public Transform startTransform;
    public ParticleSystem acquireParticles;
    public ParticleSystem acquireRing;
    [HideInInspector] public Color ChordColor;
    [HideInInspector] public Image icon;
    [HideInInspector] public Button button;

    public bool acquire;

    private void Start() {
        icon = GetComponent<Image>();  
        button = GetComponent<Button>(); 
        button.interactable = false;
        ChordColor = GetComponent<Image>().color;
        if (!acquired) {
            Color c = ChordColor;
            c.a = 0;
            icon.color = c;
        }
    }

    private void Update() {
        if (acquire)
            Acquire();
    }

    public void Acquire() {
        if (!acquired && !acquiring)
            StartCoroutine(AcquireRoutine());
    }

    IEnumerator AcquireRoutine() {
        acquiring = true;
        var main = acquireParticles.main;
        main.startColor = ChordColor;
        main = acquireRing.main;
        main.startColor = ChordColor;
        acquireParticles.Emit(20);
        acquireRing.Emit(1);
        Vector3 startPos = startTransform.position;
        Vector3 endPos = transform.position;
        transform.position = startPos;
        float lastTime = Time.timeSinceLevelLoad;
        float perc = 0;
        do {
            perc += (Time.timeSinceLevelLoad - lastTime) / (acquireTime / 2f);
            lastTime = Time.timeSinceLevelLoad;
            Color c = ChordColor;
            c.a =  acquireCurve.Evaluate(perc);
            icon.color = c;
            yield return null;
        } while(perc <= 1);
        icon.color = ChordColor;
        yield return new WaitForSeconds(0.3f);
        lastTime = Time.timeSinceLevelLoad;
        perc = 0;
        do {
            perc += (Time.timeSinceLevelLoad - lastTime) / acquireTime;
            lastTime = Time.timeSinceLevelLoad;
            transform.position = Vector3.Lerp(startPos, endPos, acquireCurve.Evaluate(perc));
            yield return null;
        } while(perc <= 1);
        transform.position = endPos;
        acquired = true;
        acquiring = false;
        button.interactable = true;
    }
}
