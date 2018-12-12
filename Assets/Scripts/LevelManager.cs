using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LevelManager : MonoBehaviour
{
	public Vector2[] curGoal;
	public Goal[] goals;
	int curGoalIndex = 0;
	public bool canIncrement = true;


	public Fade fade;
	public float fadeTime;
	public string nextLevel;

	private void Start()
	{
		curGoal = goals[0].notes;
	}

	public void IncrementGoal()
	{
		if (canIncrement)
		{
			++curGoalIndex;
			if (curGoalIndex >= goals.Length)
			{
				EndGame();
				return;
			}
			curGoal = goals[curGoalIndex].notes;
			GameManager.instance.teacher.attempt = 1;
		}
		else
			StartCoroutine(IncrementAsync());
	}

	IEnumerator IncrementAsync()
	{
		yield return new WaitUntil(() => canIncrement);
		++curGoalIndex;
		if (curGoalIndex >= goals.Length)
		{
			EndGame();
		}
		else
		{
			curGoal = goals[curGoalIndex].notes;
		}
	}

	void EndGame()
	{
		StartCoroutine(TransitionAnimation());
	}

	IEnumerator TransitionAnimation()
	{
		fade.FadeOut(fadeTime);
		yield return new WaitForSeconds(fadeTime);
		SceneManager.LoadScene("End");
	}
}

[System.Serializable]
public class Goal
{
	public Vector2[] notes = new Vector2[3];
}