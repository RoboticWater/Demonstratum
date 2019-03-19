using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody), typeof(Collider))]
public class Wood : MonoBehaviour
{
    public float breakForce = 0.25f;
    public bool DoPhysics {
        get {
            return r.isKinematic && r.detectCollisions;
        }
        set {
            r.isKinematic = !value;
            r.detectCollisions = value;
            if (value)
                r.WakeUp();
            else
                r.Sleep();
        }
    }
    public float dissolveTime = 1;
    public bool dead;
    public float deathOffset;
    public bool brokenOnStart;
    [HideInInspector] public Material material;
    Rigidbody r;
    Collider c;
    AudioSource audioSource;

    void Start()
    {
        audioSource = GetComponent<AudioSource>();
        r = GetComponent<Rigidbody>();
        material = GetComponent<MeshRenderer>().material;
        DoPhysics = false;
        if (brokenOnStart) {
            DoPhysics = true;
        }
    }

    public void Break() {
        DoPhysics = true;
        r.AddForce(Random.insideUnitSphere * (breakForce / 4) - GameManager.instance.Player.transform.forward * breakForce, ForceMode.Impulse);
    }

    public void Die() {
        if (dead)
            return;
        dead = true;
        StartCoroutine(DeathSequence());
    }

    IEnumerator DeathSequence() {
        yield return new WaitForSeconds(deathOffset);
        audioSource.pitch = Random.Range(0.8f, 1.8f);
        audioSource.Play();
        yield return new WaitForSeconds(0.8f);
        float startTime = Time.timeSinceLevelLoad;
        float perc = 0;
        do {
            perc = (Time.timeSinceLevelLoad - startTime) / dissolveTime;
            material.SetFloat("_Dissolve", perc);
            yield return null;
        } while(perc < 1);
        material.SetFloat("_Dissolve", 1);
        Destroy(this.gameObject);
    }
}
