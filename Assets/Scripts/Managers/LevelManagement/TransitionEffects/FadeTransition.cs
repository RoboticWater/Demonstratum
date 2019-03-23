using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FadeTransition : TransitionEffect
{
    public bool fadeIn;
    public Color fadeColor = new Color(0,0,0,1);
    public Material fadeMaterial;
    public AnimationCurve effectCurve;

    public override IEnumerator Transition(System.Action callback) {
        fadeMaterial.SetColor("_Color", fadeColor);
        float time = 0;
		float perc = 0;
		float lastTime = Time.realtimeSinceStartup;
		do
		{
			time += Time.realtimeSinceStartup - lastTime;
			lastTime = Time.realtimeSinceStartup;
			perc = Mathf.Clamp01(time / effectTime);
            fadeMaterial.SetFloat("_Fade", 2 * effectCurve.Evaluate(perc) - 1);
			yield return null;
		} while (perc < 1);
        fadeMaterial.SetFloat("_Fade", 2 * effectCurve.Evaluate(perc) - 1);
        callback();
    }
}
