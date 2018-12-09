using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class Voice : MonoBehaviour, IPointerDownHandler, IPointerUpHandler, IDragHandler
{
	public Player player;
	public ProceduralAudioController[] audioControllers;
	public GameObject voiceNotePrefab;
	public float voiceSpeed = 0.3f;
	public float noteMaxVol = 0.5f;
	public float chordMaxVol = 0.8f;


	RectTransform rectTransform;

	bool speaking;
	int curNote;
	VoiceNote[] voiceNotes;
	float[] voiceVels;

	private void Start()
	{
		rectTransform = GetComponent<RectTransform>();
		voiceNotes = new VoiceNote[audioControllers.Length];
		voiceVels = new float[audioControllers.Length];
	}

	private void Update()
	{
		if (speaking)
		{
			SetNote(audioControllers[curNote], voiceNotes[curNote].input.x, voiceNotes[curNote].input.y);
			for (int i = 0; i < audioControllers.Length; i++)
			{
				audioControllers[i].masterVolume = Mathf.SmoothDamp(audioControllers[i].masterVolume, i == curNote ? noteMaxVol : 0, ref voiceVels[i], voiceSpeed);
			}
		}
		else
		{
			for (int i = 0; i < audioControllers.Length; i++)
			{
				audioControllers[i].masterVolume = Mathf.SmoothDamp(audioControllers[i].masterVolume, 0, ref voiceVels[i], voiceSpeed);
			}
		}
		if (Input.GetButtonDown("Undo"))
		{
			RemoveVoiceNote(--curNote);
		}
	}

	public void OnPointerDown(PointerEventData eventData)
	{
		speaking = true;
		voiceNotes[curNote] = MakeVoiceNote(eventData.position - (Vector2)rectTransform.position);
	}

	public void OnDrag(PointerEventData eventData)
	{
		if (voiceNotes[curNote] == null)
			return;
		Vector2 localPos = eventData.position - (Vector2)rectTransform.position;
		if (localPos.magnitude > rectTransform.sizeDelta.x / 2)
		{
			speaking = false;
			RemoveVoiceNote(curNote);
			return;
		}
		voiceNotes[curNote].transform.position = eventData.position;
		voiceNotes[curNote].input = GetVoiceVect(eventData.position - (Vector2)rectTransform.position, rectTransform.sizeDelta);
	}

	public void OnPointerUp(PointerEventData eventData)
	{
		if (speaking)
		{
			speaking = false;
			curNote++;
			if (curNote == voiceNotes.Length)
			{
				for (int i = 0; i < voiceNotes.Length; i++)
					RemoveVoiceNote(i);
				curNote = 0;
			}
		}
	}

	void SetNote(ProceduralAudioController pac, float freq, float osc)
	{
		pac.mainFrequency = freq;
		pac.frequencyModulationOscillatorIntensity = osc;
	}

	void RemoveVoiceNote(int index)
	{
		if (voiceNotes[index] == null)
			return;
		Destroy(voiceNotes[index].gameObject);
		// if (index < voiceNotes.Length - 1)
		// 	voiceNotes[index] = voiceNotes[index + 1];
		// else
		voiceNotes[index] = null;
	}

	VoiceNote MakeVoiceNote(Vector2 pos)
	{
		GameObject noteObject = Instantiate(voiceNotePrefab, transform);
		VoiceNote vn = noteObject.GetComponent<VoiceNote>();
		vn.Instantiate(GetVoiceVect(pos, rectTransform.sizeDelta), GameManager.instance.levelManager.curGoal[curNote], curNote);
		vn.transform.localPosition = pos;
		return vn;
	}

	Vector2 GetVoiceVect(Vector2 pos, Vector2 sizeDelta)
	{
		Vector2 polar = FromCartesian(pos);
		return new Vector2(Map(-Mathf.PI / 2, 3 * Mathf.PI / 2, 440, 783.99f, polar.x), Map(0, sizeDelta.x / 2, 10, 1, polar.y)); ;
	}

	float Map(float from, float to, float from2, float to2, float value)
	{
		return Mathf.Lerp(from2, to2, Mathf.InverseLerp(from, to, value));
	}

	public Vector2 FromCartesian(Vector3 cart)
	{
		if (cart.x == 0f)
			cart.x = Mathf.Epsilon;
		float radius = cart.magnitude;
		float theta = Mathf.Atan(cart.y / cart.x);
		if (cart.x < 0f)
			theta += Mathf.PI;
		return new Vector2(theta, radius);
	}
}
