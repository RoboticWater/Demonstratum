using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaterSpout : MonoBehaviour
{
    public float spoutStart = 1;
    public float spoutEnd = 0;
    public AnimationCurve spoutCurve;
    public float spoutTime = 1;
    public AudioSource audioSource;
    public float audioStart = 0;
    public float audioEnd = 1;
    public float audioTimeOffset;

    Material m;

    private void Start() {
        m = GetComponent<MeshRenderer>().sharedMaterial;
        m.SetFloat("_Dissolve", spoutStart);
        audioSource.time = audioTimeOffset;
    }
    
    public void StartSpout() {
        StartCoroutine(Spout());
    }

    IEnumerator Spout(bool off = false) {
        float startTime = Time.timeSinceLevelLoad;
        float perc;
        if (!off) {
            audioSource.gameObject.SetActive(true);
        }
        do {
            perc = (Time.timeSinceLevelLoad - startTime) / spoutTime;
            m.SetFloat("_Dissolve", Mathf.Lerp(spoutStart, spoutEnd, spoutCurve.Evaluate(off ? 1- perc : perc)));
            audioSource.volume = Mathf.Lerp(audioStart, audioEnd, spoutCurve.Evaluate(off ? 1- perc : perc));
            yield return null;
        } while(perc < 1);
        audioSource.volume = off ? audioStart : audioEnd;
        m.SetFloat("_Dissolve", off ? spoutStart : spoutEnd);
        if (off) {
            audioSource.gameObject.SetActive(false);
        }
    }

    public void Disable() {
        StartCoroutine(Spout(true));
    }
}
