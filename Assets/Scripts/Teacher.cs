using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Teacher : MonoBehaviour
{
	public ProceduralAudioController[] audioControllers;
	public float teachRate;
	public float noteLength;
	public float notePause = 0.1f;
	public float chordLength;
	public AnimationCurve speakCurve;
	float teachTimer;
	bool speaking;
	public Student student;
	public int maxAttempts;
	public int attempt = 1;

	void Update()
	{
		if (!speaking)
		{
			teachTimer -= Time.deltaTime;
			if (teachTimer < 0)
			{
				StartCoroutine(TeachChord());
			}
		}
	}

	void SetNotes()
	{
		Vector2[] goal = GameManager.instance.levelManager.curGoal;
		for (int i = 0; i < audioControllers.Length; i++)
		{
			audioControllers[i].mainFrequency = goal[i].x;
			audioControllers[i].frequencyModulationOscillatorIntensity = goal[i].y;
		}

	}

	IEnumerator TeachChord()
	{
		teachTimer = teachRate;
		speaking = true;
		GameManager.instance.levelManager.canIncrement = false;
		SetNotes();
		float time = 0;
		float perc = 0;
		float lastTime = Time.realtimeSinceStartup;
		Quaternion curLook = transform.rotation;
		foreach (Vector2 note in GameManager.instance.levelManager.curGoal)
		{
			time = 0;
			do
			{
				time += Time.realtimeSinceStartup - lastTime;
				lastTime = Time.realtimeSinceStartup;
				perc = Mathf.Clamp01(time / noteLength);
				foreach (ProceduralAudioController p in audioControllers)
				{
					p.masterVolume = Mathf.Lerp(0, 0.6f, speakCurve.Evaluate(perc));
				}
				yield return null;
			} while (perc < 1);
			yield return new WaitForSeconds(notePause);
		}
		time = 0;
		do
		{
			time += Time.realtimeSinceStartup - lastTime;
			lastTime = Time.realtimeSinceStartup;
			perc = Mathf.Clamp01(time / chordLength);
			foreach (ProceduralAudioController p in audioControllers)
			{
				p.masterVolume = Mathf.Lerp(0, 0.8f, speakCurve.Evaluate(perc));
			}
			yield return null;
		} while (perc < 1);
		GameManager.instance.levelManager.canIncrement = true;
		speaking = false;
		StartCoroutine(student.LearnChord(attempt++));
		if (attempt >= maxAttempts)
		{
			GameManager.instance.levelManager.IncrementGoal();
		}
	}
}
