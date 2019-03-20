using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VoiceBar : MonoBehaviour
{
    CanvasGroup canvasGroup;
    NoteLine[] noteLines;
    [Header("Fade Effect")]
    public AnimationCurve effectCurve;
    public float effectTime = 0.5f;

    [Header("Speaking")]
    bool speaking;
    public float lineTime = 0.8f;
    public float lineRest = 0.05f;

    [Header("References")]
    public Transform noteLinesContainer;

    public bool Visible {
        get { return canvasGroup.alpha > 0.5f; }
        set {
            if (value == canvasGroup.alpha > 0.5f)
                return;
            StartCoroutine(Fade(value));
        }
    }

    void Awake()
    {
        canvasGroup = GetComponent<CanvasGroup>();
        noteLines = noteLinesContainer.GetComponentsInChildren<NoteLine>();
    }

    void Update()
    {
        if (Input.GetButton("Speak") && !speaking) {
            StartCoroutine(Speak());
        }
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

    IEnumerator Speak() {
        speaking = true;
        foreach (NoteLine nl in noteLines) {
            nl.Play();
            yield return new WaitForSeconds(lineTime);
            nl.Stop();
            yield return new WaitForSeconds(lineRest);
        }
        speaking = false;
    }
}
