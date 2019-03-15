using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FurnaceFire : MonoBehaviour
{
    public int totalWood = 5;
    public int curWood;

    public float fireStartSize = 0.1f;
    public float fireEndSize = 0.1f;

    public float lightRandom = 0.1f;
    public float lightSpeed = 0.1f;
    public float minLightIntensity = 0.9f;
    public float maxLightIntensity = 1;
    public float minAreaSize = 2.5f;
    public float maxAreaSize = 8.15f;
    float intensityTarget = 1;

    ParticleSystem fire;
    public Light light;

    private void Start()
    {
        fire = GetComponent<ParticleSystem>();
    }

    private void FixedUpdate() {
        light.intensity = Mathf.Lerp(light.intensity, intensityTarget, lightSpeed);
        if (Random.Range(0.0f, 1.0f) < lightRandom) {
            light.intensity = Random.Range(0.8f, 1); 
        }
    }

    private void OnTriggerEnter(Collider other) {
        Wood w = other.GetComponent<Wood>();
        if (w != null) {
            curWood += 1;
            float fireSize = Mathf.Lerp(fireStartSize, fireEndSize, (float) totalWood / curWood);
            fire.transform.localScale = new Vector3(fireSize, fireSize, fireSize);
            light.range = Mathf.Lerp(minAreaSize, maxAreaSize, (float) totalWood / curWood);
            w.Die();
        }
    }
}
