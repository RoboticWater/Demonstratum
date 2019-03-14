using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaterRise : MonoBehaviour
{
    public float riseStart = 0;
    public float riseEnd = 1;
    public AnimationCurve riseCurve;
    public float riseTime = 1;
    public AudioSource audioSource;
    public float audioStart = 0;
    public float audioEnd = 1;

    Material m;

    private void Start() {
        m = GetComponent<MeshRenderer>().sharedMaterial;
        m.SetFloat("_Offset", riseStart);
    }
    
    public void StartRise() {
        StartCoroutine(Rise());
    }

    IEnumerator Rise(bool off = false) {
        float startTime = Time.timeSinceLevelLoad;
        float perc;
        if (!off) {
            audioSource.gameObject.SetActive(true);
        }
        do {
            perc = (Time.timeSinceLevelLoad - startTime) / riseTime;
            m.SetFloat("_Offset", Mathf.Lerp(riseStart, riseEnd, riseCurve.Evaluate(off ? 1- perc : perc)));
            audioSource.volume = Mathf.Lerp(audioStart, audioEnd, riseCurve.Evaluate(off ? 1- perc : perc));
            yield return null;
        } while(perc < 1);
        m.SetFloat("_Offset", off ? riseStart : riseEnd);
        audioSource.volume = off ? audioStart : audioEnd;
        if (off) {
            audioSource.gameObject.SetActive(false);
        }
    }


    public void Disable() {
        StartCoroutine(Rise(true));
    }
}
