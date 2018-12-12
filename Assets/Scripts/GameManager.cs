using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
	public static GameManager instance;
	public Player player;
	public Hashtable sharedData;
	public LevelManager levelManager;
	public Teacher teacher;
	public Student student;
	public Human[] humans;

	public Color[] NOTE_COLORS = { Color.red, Color.blue, Color.green, Color.yellow };
	public AnimationCurve NOTE_CURVE;

	private void Awake()
	{
		if (instance == null)
			instance = this;
		else if (instance != this)
			Destroy(gameObject);
		DontDestroyOnLoad(gameObject);
	}

	private void Start()
	{
		player = Object.FindObjectOfType<Player>();
	}
}
