using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody), typeof(Collider))]
public class Wood : MonoBehaviour
{
    public float breakForce = 0.25f;
    bool DoPhysics {
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
    Material m;
    Rigidbody r;
    Collider c;
    
    void Start()
    {
        r = GetComponent<Rigidbody>();
        m = GetComponent<MeshRenderer>().material;
        DoPhysics = false;
    }

    public void Break() {
        DoPhysics = true;
        r.AddForce(Random.insideUnitSphere * (breakForce / 4) - GameManager.instance.Player.transform.forward * breakForce, ForceMode.Impulse);
    }

    public void Die() {
        StartCoroutine(DeathSequence());
    }

    IEnumerator DeathSequence() {
        do {
            m.SetFloat("_Dissolve", m.GetFloat("_Dissolve") - 0.1f);
            yield return null;
        } while(m.GetFloat("_Dissolve") <= 0);
    }
}
