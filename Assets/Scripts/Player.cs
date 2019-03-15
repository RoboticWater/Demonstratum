using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityStandardAssets.Characters.FirstPerson;
using Kino;
using UnityEngine.SceneManagement;

public class Player : MonoBehaviour
{
	
	[Header("Health")]
	public float health = 100;
	public float regen = 7;
	public float regenDelay = 3;
	public float regenTimer;
	public float selectionRange = 10;
	
	[Header("References")]
	public MainUI UI;
	public DigitalGlitch glitchEffect;
	FirstPersonController firstPerson;
	Camera cam;
	
	
	void Start()
	{
		firstPerson = GetComponent<FirstPersonController>();
		regenTimer = regenDelay;
		firstPerson.m_MouseLook.SetCursorLock(firstPerson.canLook);
		UI.voiceBar.Visible = !firstPerson.canLook;
	}

	// Update is called once per frame
	void Update()
	{
		if (Input.GetButtonDown("Switch"))
		{
			firstPerson.m_MouseLook.SetCursorLock(!firstPerson.m_MouseLook.lockCursor);
			UI.voiceBar.Visible = firstPerson.canLook;
			firstPerson.canLook = !firstPerson.canLook;
		}
		glitchEffect._intensity = Mathf.Clamp(1 - (health / 100f), 0, 1);
		if (health < 100)
		{
			if (health <= 0)
				Death();
			regenTimer -= Time.deltaTime;
			if (regenTimer < 0)
			{
				health += regen * Time.deltaTime;
			}
		}
		RaycastHit hit;
		if (Physics.Raycast(cam.transform.position, cam.transform.forward, out hit, selectionRange)) {
			if (Input.GetButtonDown("Fire1")) {
				Selector.Select();
			} else (hit.collider.gameObject.GetComponent<Selector>()) {
				Selector.Highlight();
			}
		}
	}

	public void damage(float damage)
	{
		regenTimer = regenDelay;
		health -= damage;
	}

	public void Death() {
		//TODO death script
	}
}
