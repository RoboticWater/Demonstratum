using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class TransitionEffect : MonoBehaviour
{
    public float effectTime = 1;
    abstract public IEnumerator Transition(System.Action callback);
}
