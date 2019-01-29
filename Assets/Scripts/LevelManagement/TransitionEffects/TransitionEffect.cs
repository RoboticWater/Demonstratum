using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class TransitionEffect : MonoBehaviour
{
    abstract public IEnumerator Transition(System.Action callback);
}
