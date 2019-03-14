using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Wood : MonoBehaviour
{
    Material m;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
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
