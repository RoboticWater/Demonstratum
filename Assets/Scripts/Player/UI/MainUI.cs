using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MainUI : MonoBehaviour
{
    public Image fade;
    public VoiceBar voiceBar;
    [SerializeField] private Image reticle;
    public float reticleHideTime = 2;
    public float hideTime = 0.3f;
    public float reticleMaxAlpha = 0.5f;
    public AnimationCurve reticleHideCurve;
    float reticleHideTimer;
    bool changingVisibility;

    private void Start() {
        Color c = reticle.color;
        c.a = 0;
        reticle.color = c;
    }

    private void Update() {
        if (reticleHideTimer > 0) {
            reticleHideTimer -= Time.deltaTime;
        } else {
            if (!changingVisibility && reticle.color.a != 0)
                StartCoroutine(SetReticleVisibility(false));
        }
    }

    public void ShowReticle() {
        StartCoroutine(SetReticleVisibility(true));
        reticleHideTimer = reticleHideTime;
    }

    IEnumerator SetReticleVisibility(bool visible) {
        changingVisibility = true;
        float lastTime = Time.timeSinceLevelLoad;
        float perc = visible ? 0 : 1;
        Color c;
        do {
            perc += (visible ? 1 : -1) * (Time.timeSinceLevelLoad - lastTime) / hideTime;
            lastTime = Time.timeSinceLevelLoad;
            c = reticle.color;
            c.a = Mathf.Lerp(0, reticleMaxAlpha, reticleHideCurve.Evaluate(perc));
            reticle.color = c;
            yield return null;
        } while(perc <= 1 && perc >= 0);
        c = reticle.color;
        c.a = visible ? reticleMaxAlpha : 0;
        reticle.color = c;
        changingVisibility = false;
    }
}
