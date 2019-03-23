using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FurnaceFire : Persistent
{
    public int totalWood = 5;
    public int curWood;

    public float fireStartSize = 0.1f;
    public float fireEndSize = 0.1f;
    public float fireGrowSpeed = 0.05f;

    public float lightRandom = 0.1f;
    public float lightSpeed = 0.1f;
    public float minLightIntensity = 0.9f;
    public float maxLightIntensity = 1;
    public float minAreaSize = 2.5f;
    public float maxAreaSize = 8.15f;
    float intensityTarget = 1;

    public ParticleSystem fire;
    public Light fireLight;
    AudioSource audioSource;
    
    private void Start() {
        fire.transform.localScale = new Vector3(fireStartSize, fireStartSize, fireStartSize);
        fireLight.range = minAreaSize;
        audioSource = GetComponent<AudioSource>();

        object curWood = GameManager.instance.GetObject(this, "_curWood");
        if (curWood != null) {
            this.curWood = (int) curWood;
            fire.transform.localScale = new Vector3(fireEndSize, fireEndSize, fireEndSize) * (float) this.curWood / totalWood + 
                new Vector3(fireStartSize, fireStartSize, fireStartSize);
            fireLight.range = minAreaSize + maxAreaSize * (float) this.curWood / totalWood;
            audioSource.volume = 0.1f + (float) this.curWood / totalWood;
        }
    }

    private void FixedUpdate() {
        fireLight.intensity = Mathf.Lerp(fireLight.intensity, intensityTarget, lightSpeed);
        if (Random.Range(0.0f, 1.0f) < lightRandom) {
            fireLight.intensity = Random.Range(0.8f, 1); 
        }
        fire.transform.localScale = Vector3.Lerp(fire.transform.localScale, 
            new Vector3(fireEndSize, fireEndSize, fireEndSize) * (float) curWood / totalWood + 
            new Vector3(fireStartSize, fireStartSize, fireStartSize), fireGrowSpeed);
        fireLight.range = Mathf.Lerp(fireLight.range, minAreaSize + maxAreaSize * (float) curWood / totalWood, fireGrowSpeed);
        audioSource.volume = Mathf.Lerp(audioSource.volume, 0.1f + (float) curWood / totalWood, fireGrowSpeed);
    }

    private void OnTriggerEnter(Collider other) {
        Wood w = other.GetComponent<Wood>();
        if (w != null) {
            curWood += 1;
            GameManager.instance.SetObject(this, "_curWood", curWood);           
            w.Die();
            var main = fire.main;
            main.startSizeMultiplier = 2.2f;
            fire.Emit(20);
            main.startSizeMultiplier = 1;
        }
    }

    public override void Save() {
        GameManager.instance.SetObject(this, "_curWood", curWood);
    }
}
