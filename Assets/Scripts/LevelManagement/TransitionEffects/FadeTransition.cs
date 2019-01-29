using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FadeTransition : TransitionEffect
{
    public override IEnumerator Transition(System.Action callback) {
        yield return null;
        callback();
    }
}
