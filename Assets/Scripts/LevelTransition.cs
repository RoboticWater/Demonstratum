using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LevelTransition : MonoBehaviour
{
	public Fade fade;
	public float fadeTime;
	public string nextLevel;
	void Start()
	{

	}

	// Update is called once per frame
	void Update()
	{

	}

	public void Transition()
	{
		StartCoroutine(TransitionAnimation());
	}

	IEnumerator TransitionAnimation()
	{
		fade.FadeOut(fadeTime);
		yield return new WaitForSeconds(fadeTime);
		SceneManager.LoadScene(nextLevel);
	}

	private void OnTriggerEnter(Collider other)
	{
		Transition();
	}
}
