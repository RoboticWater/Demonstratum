using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lightning : MonoBehaviour
{

	public float strikeProb = 0.01f;
	public float intensity = 5;
	public float decay = 0.3f;
	public GameObject lightPlane;
	public float minIntensity = 1f;
	public float maxIntensity = 1.2f;
	public bool startFiring;

	Light l;
	Material planeMat;
	AudioSource[] sources;
	int curSource;

	// Use this for initialization
	void Start()
	{
		l = GetComponent<Light>();
		planeMat = lightPlane.GetComponent<MeshRenderer>().material;
		sources = GetComponents<AudioSource>();
		if (startFiring)
		{
			Strike(maxIntensity);
		}
	}


	private void FixedUpdate()
	{
		if (Random.value < strikeProb && l.intensity < 0.01f)
		{
			Strike();
		}
		else
		{
			l.intensity = Mathf.Lerp(l.intensity, 0, decay);
			planeMat.color = Color.Lerp(planeMat.color, new Color(1, 1, 1, 0), decay);
		}
	}

	void Strike(float value = 0)
	{
		float i = value;
		if (i == 0)
			i = Random.Range(minIntensity, maxIntensity);
		l.intensity = intensity * i;
		planeMat.color = new Color(1, 1, 1, i);
		sources[curSource].Stop();
		sources[curSource].pitch = Random.value < 0.2f ? Random.Range(0.8f, 1f) : Random.Range(0.5f, 0.8f);
		sources[curSource].volume = i;
		sources[curSource].Play();
		curSource = ++curSource % sources.Length;
	}
}
