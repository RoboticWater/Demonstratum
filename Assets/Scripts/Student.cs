using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Student : MonoBehaviour
{

	public ProceduralAudioController[] audioControllers;
	public float noteLength;
	public float notePause = 0.1f;
	public float chordLength;
	public AnimationCurve speakCurve;
	public Transform[] speechSpheres;
	bool speaking;

	void SetNotes(int attempt)
	{
		Vector2[] goal = GameManager.instance.levelManager.curGoal;
		for (int i = 0; i < audioControllers.Length; i++)
		{
			audioControllers[i].mainFrequency = goal[i].x + Random.Range(-40f, 40f) / Mathf.Pow(attempt, 2);
			audioControllers[i].frequencyModulationOscillatorIntensity = goal[i].y + Random.Range(-3f, 3f) / Mathf.Pow(attempt, 2);
		}

	}

	public IEnumerator LearnChord(int attempt)
	{
		speaking = true;
		SetNotes(attempt);
		float time = 0;
		float perc = 0;
		float lastTime = Time.realtimeSinceStartup;
		Quaternion curLook = transform.rotation;
		for (int i = 0; i < audioControllers.Length; i++)
		{
			time = 0;
			lastTime = Time.realtimeSinceStartup;
			speechSpheres[i].gameObject.SetActive(true);
			do
			{
				time += Time.realtimeSinceStartup - lastTime;
				lastTime = Time.realtimeSinceStartup;
				perc = Mathf.Clamp01(time / noteLength);
				float val = Mathf.Lerp(0, 0.6f, speakCurve.Evaluate(perc));
				audioControllers[i].masterVolume = val;
				speechSpheres[i].localScale = new Vector3(val / 2, val / 2, val / 2);
				yield return null;
			} while (perc < 1);
			speechSpheres[i].gameObject.SetActive(false);
			yield return new WaitForSeconds(notePause);
		}
		time = 0;
		lastTime = Time.realtimeSinceStartup;
		speechSpheres[3].gameObject.SetActive(true);
		do
		{
			time += Time.realtimeSinceStartup - lastTime;
			lastTime = Time.realtimeSinceStartup;
			perc = Mathf.Clamp01(time / chordLength);
			float val = Mathf.Lerp(0, 0.8f, speakCurve.Evaluate(perc));
			foreach (ProceduralAudioController p in audioControllers)
			{
				p.masterVolume = val;
			}
			speechSpheres[3].localScale = new Vector3(val / 1.5F, val / 1.5F, val / 1.5F);
			yield return null;
		} while (perc < 1);
		speechSpheres[3].gameObject.SetActive(false);
		GameManager.instance.levelManager.canIncrement = true;
		speaking = false;
	}
}
