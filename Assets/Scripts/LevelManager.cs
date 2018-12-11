using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LevelManager : MonoBehaviour
{
	public Vector2[] curGoal;
	public Goal[] goals;
	int curGoalIndex = 0;
	public bool canIncrement = true;

	private void Start()
	{
		curGoal = goals[0].notes;
	}

	public void IncrementGoal()
	{
		if (canIncrement)
		{
			curGoal = goals[++curGoalIndex].notes;
			GameManager.instance.teacher.attempt = 1;
		}
		else
			StartCoroutine(IncrementAsync());
	}

	IEnumerator IncrementAsync()
	{
		yield return new WaitUntil(() => canIncrement);
		curGoal = goals[++curGoalIndex].notes;
	}
}

[System.Serializable]
public class Goal
{
	public Vector2[] notes = new Vector2[3];
}