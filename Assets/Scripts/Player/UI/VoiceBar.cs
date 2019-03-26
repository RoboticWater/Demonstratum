using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VoiceBar : MonoBehaviour
{
    CanvasGroup canvasGroup;
    NoteLine[] noteLines;
    [Header("Fade Effect")]
    [SerializeField] private AnimationCurve effectCurve;
    [SerializeField] private float effectTime = 0.5f;

    [Header("Speaking")]
    private bool speaking;
    [SerializeField] private float lineTime = 0.8f;
    [SerializeField] private float lineRest = 0.05f;

    [Header("References")]
    [SerializeField] private Transform noteLinesContainer;

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
        int lastFilled = -1;
        for (int i = 0; i < noteLines.Length; i++) {
            if (!noteLines[i].Empty)
                lastFilled = i;
        }
<<<<<<< HEAD
        if (lastFilled < 0) {
            speaking = false;
            yield break;
        }
=======
        if (lastFilled < 0)
            yield break;
>>>>>>> ece97262fcf14c7f90a685449b1030ad84e0e8ce
        for (int i = 0; i < lastFilled + 1; i++) {
            NoteLine nl = noteLines[i];
            nl.Play();
            yield return new WaitForSeconds(lineTime);
            nl.Stop();
            yield return new WaitForSeconds(lineRest);
        }
        speaking = false;
    }

    public void AddChord(Chord c) {
        foreach (NoteLine nl in noteLines) {
            if (nl.Empty) {
                nl.SetChord(c);
                return;
            }
        }
        foreach (NoteLine nl in noteLines) {
            if (!nl.HasChord) {
                nl.SetChord(c);
                return;
            }
        }
    }
}
