using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Persistent : MonoBehaviour {
    [HideInInspector] public string ID;

    void Awake() {
        ID = gameObject.name + transform.position.GetHashCode().ToString();
        GameManager.instance.RegsiterPersistent(this);
    }

    public abstract void Save();
}