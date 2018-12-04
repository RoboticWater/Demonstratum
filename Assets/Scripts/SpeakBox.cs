using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class SpeakBox : MonoBehaviour, IPointerEnterHandler, IPointerExitHandler
{

	[Range(1, 20000)]  //Creates a slider in the inspector
	public float frequency1;

	[Range(1, 20000)]  //Creates a slider in the inspector
	public float frequency2;

	public float sampleRate = 44100;
	public float waveLengthInSeconds = 2.0f;

	int timeIndex = 0;

	AudioSource audioSource;
	RectTransform rt;

	bool inBox;
	Vector2 voice;

	public void Start()
	{
		rt = GetComponent<RectTransform>();
		audioSource = gameObject.AddComponent<AudioSource>();
		audioSource.playOnAwake = false;
		audioSource.spatialBlend = 0;
		audioSource.Stop();
	}

	private void FixedUpdate()
	{
		bool playing = Input.GetMouseButton(0) && inBox;
		if (playing)
		{
			if (!audioSource.isPlaying)
				audioSource.Play();
			voice = 2 * ((Vector2)Input.mousePosition - rt.anchoredPosition) / rt.sizeDelta.x;
		}
		audioSource.volume = Mathf.Lerp(audioSource.volume, playing ? 1 : 0, 0.5f);
		if (audioSource.volume < 0.01f)
			audioSource.Stop();
	}

	public void OnPointerEnter(PointerEventData e)
	{
		inBox = true;

	}

	public void OnPointerExit(PointerEventData e)
	{
		inBox = false;
	}

	void OnAudioFilterRead(float[] data, int channels)
	{
		for (int i = 0; i < data.Length; i += channels)
		{
			data[i] = CreateSine(timeIndex, 400 + 200 * voice.x, sampleRate);

			if (channels == 2)
				data[i + 1] = CreateSine(timeIndex, 400 + 200 * voice.x, sampleRate);

			timeIndex++;

			//if timeIndex gets too big, reset it to 0
			if (timeIndex >= (sampleRate * waveLengthInSeconds))
			{
				timeIndex = 0;
			}
		}
	}

	//Creates a sinewave
	public float CreateSine(int timeIndex, float frequency, float sampleRate)
	{
		return Mathf.Sin(2 * Mathf.PI * timeIndex * frequency / sampleRate);
	}
}