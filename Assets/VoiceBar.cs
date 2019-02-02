using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VoiceBar : MonoBehaviour
{
    CanvasGroup canvasGroup;
    public AnimationCurve effectCurve;
    public float effectTime = 0.5f;

    public bool Visible {
        get { return canvasGroup.alpha > 0.5f; }
        set {
            if (value == canvasGroup.alpha > 0.5f)
                return;
            StartCoroutine(Fade(value));
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        canvasGroup = GetComponent<CanvasGroup>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    IEnumerator Fade(bool visible) {
        float time = 0;
		float perc = 0;
		float lastTime = Time.realtimeSinceStartup;
		do
		{
			time += Time.realtimeSinceStartup - lastTime;
			lastTime = Time.realtimeSinceStartup;
			perc = Mathf.Clamp01(time / effectTime);
            canvasGroup.alpha = effectCurve.Evaluate(visible ? perc : 1 - perc);
			yield return null;
		} while (perc < 1);
        canvasGroup.alpha = visible ? 1 : 0;
    }
}
