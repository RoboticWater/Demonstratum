using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
	public static GameManager instance;
	
	int spawnPointID;
	public int SpawnPointID {
		set { spawnPointID = value; }
	}

	LevelManager level;
	public LevelManager Level {
		get { return level; }
	}

	Player player;
	public Player Player {
		get { return player; }
	}

	private Dictionary<string, object> Storage;

	public Color[] NOTE_COLORS = { Color.red, Color.blue, Color.green, Color.yellow };
	public AnimationCurve NOTE_CURVE;

	private void Awake()
	{
		Storage = new Dictionary<string, object>();
		if (instance == null)
			instance = this;
		else if (instance != this)
			Destroy(gameObject);
		DontDestroyOnLoad(gameObject);
	}

	void OnEnable()
    {
        SceneManager.sceneLoaded += OnSceneLoaded;
    }

	void OnDisable()
    {
        SceneManager.sceneLoaded -= OnSceneLoaded;
    }

	private void OnSceneLoaded(Scene scene, LoadSceneMode mode)
	{
		player = Object.FindObjectOfType<Player>();
		level = Object.FindObjectOfType<LevelManager>();
		level.spawnPoints[spawnPointID].OrientActor(player.transform);
	}

	public void SetObject(string key, object value) {
		Storage[key] = value;
	}

	public object GetObject(string key) {
		return Storage.ContainsKey(key) ? Storage[key] : null;
	}
}
