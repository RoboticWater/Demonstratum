using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Fade : MonoBehaviour
{
	Image img;
	public AudioSource[] audioSources;

	private void Start()
	{
		img = GetComponent<Image>();
	}

	public void FadeOut(float effectLength)
	{
		StartCoroutine(FadeAnim(effectLength, true));
	}

	public void FadeIn(float effectLength)
	{
		StartCoroutine(FadeAnim(effectLength, false));
	}

	IEnumerator FadeAnim(float effectLength, bool fadeOut = true)
	{
		float time = 0;
		float perc = 0;
		float lastTime = Time.realtimeSinceStartup;
		Color c = img.color;
		do
		{
			time += Time.realtimeSinceStartup - lastTime;
			lastTime = Time.realtimeSinceStartup;
			perc = Mathf.Clamp01(time / effectLength);
			c = img.color;
			c.a = fadeOut ? perc : 1 - perc;
			img.color = c;
			foreach (AudioSource a in audioSources)
				a.volume = fadeOut ? 1 - perc : perc;
			yield return null;
		} while (perc < 1);
		c = img.color;
		c.a = fadeOut ? 1 : 0;
		img.color = c;
	}
}
