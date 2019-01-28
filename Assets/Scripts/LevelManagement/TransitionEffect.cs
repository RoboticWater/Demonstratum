using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public interface TransitionEffect
{
    IEnumerator Transition(System.Action callback);
}
