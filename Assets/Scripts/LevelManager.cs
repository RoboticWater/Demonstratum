using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LevelManager : MonoBehaviour
{
	[HideInInspector]
	public Vector2[] curGoal;
	public Goal[] goals;

	private void Start()
	{
		curGoal = goals[0].notes;
	}

	public void SetCurGoal(int i)
	{
		curGoal = goals[i].notes;
	}
}

[System.Serializable]
public class Goal
{
	public Vector2[] notes = new Vector2[3];
}