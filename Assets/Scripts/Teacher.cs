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
	public float initialDelay = 20;
	bool speaking;
	public Student student;
	public int maxAttempts;
	public int attempt = 1;
	public Transform[] speechSpheres;
	public Vector3 home;

	Human human;
	IEnumerator coroutine;


	private void Start()
	{
		teachTimer = initialDelay;
		human = GetComponent<Human>();
		home = transform.position;
	}

	void Update()
	{
		if (human.state == HumanState.Attack || human.state == HumanState.Chase)
		{
			StopCoroutine(coroutine);
			Silence();
			GameManager.instance.levelManager.canIncrement = true;
			speaking = false;
		}
		if (!speaking)
		{
			teachTimer -= Time.deltaTime;
			if (teachTimer < 0)
			{
				coroutine = TeachChord();
				StartCoroutine(coroutine);
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

	void Silence()
	{
		for (int i = 0; i < audioControllers.Length; i++)
		{
			audioControllers[i].masterVolume = 0;
		}
	}

	IEnumerator TeachChord()
	{
		speaking = true;
		human.goTo(home);
		yield return new WaitUntil(() => Vector3.Distance(transform.position, home) < 2);
		teachTimer = teachRate;
		GameManager.instance.levelManager.canIncrement = false;
		SetNotes();
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
		yield return new WaitForSeconds(notePause);
		StartCoroutine(student.LearnChord(attempt++));
		if (attempt > maxAttempts)
		{
			GameManager.instance.levelManager.IncrementGoal();
		}
	}
}
