using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityStandardAssets.Characters.FirstPerson;
using Kino;

public class Player : MonoBehaviour
{
	FirstPersonController firstPerson;
	public DigitalGlitch glitch;
	public float health = 100;
	// Start is called before the first frame update
	void Start()
	{
		firstPerson = GetComponent<FirstPersonController>();
	}

	// Update is called once per frame
	void Update()
	{
		if (Input.GetButtonDown("Switch"))
		{
			firstPerson.m_MouseLook.SetCursorLock(!firstPerson.m_MouseLook.lockCursor);
			firstPerson.canLook = !firstPerson.canLook;
		}
		glitch._intensity = 1 - (health / 100f);
	}

	public void damage(float damage)
	{
		health -= damage;
	}
}
