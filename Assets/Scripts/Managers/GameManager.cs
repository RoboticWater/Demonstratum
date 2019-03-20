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
	private List<Persistent> persistent;
	public bool debug;

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
		persistent = new List<Persistent>();
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

	public void SetObject(Persistent p, string key, object value) {
		if (debug)
			print("STORING: " + value + " at: " + uniqueKey(p, key));
		Storage[uniqueKey(p, key)] = value;
	}

	public object GetObject(Persistent p, string key) {
		string k = uniqueKey(p, key);
		if (debug) {
			if (Storage.ContainsKey(k)) {
				print("GETTING: " + k + " return: " + Storage[k]);
			}
		}
		return Storage.ContainsKey(k) ? Storage[k] : null;
	}

	string uniqueKey(Persistent p, string key) {
		return p.ID + key;
	}

	public void RegsiterPersistent(Persistent p) {
		persistent.Add(p);
	}

	public void DeregsiterPersistent(Persistent p) {
		persistent.Remove(p);
	}

	public void Save() {
		foreach (Persistent p in persistent) {
			p.Save();
		}
		persistent.Clear();
	}
}
