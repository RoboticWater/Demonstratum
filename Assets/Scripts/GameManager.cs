using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
	public static GameManager instance;
	public Player player;
	public Hashtable sharedData;
	public LevelManager levelManager;

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
