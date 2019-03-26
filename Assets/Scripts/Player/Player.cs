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
	public Camera cam;
	
	Selector selected;
	[HideInInspector]public Selector holding;
	
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
		if (Input.GetButtonDown("Fire1")) {
			UI.ShowReticle();
			if (holding) {
				holding.Select();
			} else if (selected != null) {
				selected.Select();
			}
		}
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
<<<<<<< HEAD
		if (Physics.Raycast(cam.transform.position, cam.transform.forward, out hit, selectionRange, ~LayerMask.GetMask("Player"))) {
=======
		if (Physics.Raycast(cam.transform.position, cam.transform.forward, out hit, selectionRange)) {
>>>>>>> ece97262fcf14c7f90a685449b1030ad84e0e8ce
			Selector[] selectors = hit.collider.gameObject.GetComponents<Selector>();
			if (selectors.Length > 0) {
				UI.ShowReticle();
				if (selected != selectors[0]) {
					if (selected)
						selected.SetHighlight(false);
					selected = selectors[0];
					selected.SetHighlight(true);
				}
			} else if (selected) {
				selected.SetHighlight(false);
				selected = null;
			}
		} else if (selected) {
			selected.SetHighlight(false);
			selected = null;
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
