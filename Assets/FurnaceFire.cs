using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FurnaceFire : MonoBehaviour
{
    public int totalWood = 5;
    public int curWood;

    public float fireStartSize = 0.1f;
    public float fireEndSize = 0.1f;

    ParticleSystem fire;

    private void Start()
    {
        fire = GetComponent<ParticleSystem>();
    }

    private void OnTriggerEnter(Collider other) {
        Wood w = other.GetComponent<Wood>();
        if (w != null) {
            curWood += 1;
            float fireSize = Mathf.Lerp(fireStartSize, fireEndSize, (float) totalWood / curWood);
            fire.transform.localScale = new Vector3(fireSize, fireSize, fireSize);
            w.Die();
        }
    }
}
