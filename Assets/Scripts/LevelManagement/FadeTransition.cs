using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FadeTransition : TransitionEffect
{
    public IEnumerator Transition(System.Action callback) {
        yield return null;
        callback();
    }
}
