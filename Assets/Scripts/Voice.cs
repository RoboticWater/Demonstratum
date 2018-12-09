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
	public float chordTime = 1f;


	RectTransform rectTransform;

	VoiceState voiceState;
	bool canSpeak = true;
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
		switch (voiceState)
		{
			case VoiceState.SpeakingNote:
				SetNote(audioControllers[curNote], voiceNotes[curNote].input.x, voiceNotes[curNote].input.y);
				for (int i = 0; i < audioControllers.Length; i++)
				{
					audioControllers[i].masterVolume = Mathf.SmoothDamp(audioControllers[i].masterVolume, i == curNote ? noteMaxVol : 0, ref voiceVels[i], voiceSpeed);
				}
				break;
			case VoiceState.SpeakingChord:
				for (int i = 0; i < audioControllers.Length; i++)
				{
					audioControllers[i].masterVolume = Mathf.SmoothDamp(audioControllers[i].masterVolume, chordMaxVol, ref voiceVels[i], voiceSpeed);
				}
				chordTime -= Time.deltaTime;
				if (chordTime <= 0)
				{
					voiceState = VoiceState.Silent;
					for (int i = audioControllers.Length - 1; i >= 0; i--)
						RemoveVoiceNote(i);
				}
				break;
			case VoiceState.Silent:
				for (int i = 0; i < audioControllers.Length; i++)
				{
					audioControllers[i].masterVolume = Mathf.SmoothDamp(audioControllers[i].masterVolume, 0, ref voiceVels[i], voiceSpeed);
				}
				break;
		}

		if (Input.GetButtonDown("Undo"))
		{
			RemoveVoiceNote(--curNote);
		}
	}

	public void OnPointerDown(PointerEventData eventData)
	{
		if (!canSpeak)
			return;
		voiceState = VoiceState.SpeakingNote;
		voiceNotes[curNote] = MakeVoiceNote(eventData.position - (Vector2)rectTransform.position);
	}

	public void OnDrag(PointerEventData eventData)
	{
		if (voiceNotes[curNote] == null || !canSpeak)
			return;
		Vector2 localPos = eventData.position - (Vector2)rectTransform.position;
		if (localPos.magnitude > rectTransform.sizeDelta.x / 2)
		{
			voiceState = VoiceState.Silent;
			RemoveVoiceNote(curNote);
			return;
		}
		voiceNotes[curNote].transform.position = eventData.position;
		voiceNotes[curNote].input = GetVoiceVect(eventData.position - (Vector2)rectTransform.position, rectTransform.sizeDelta);
	}

	public void OnPointerUp(PointerEventData eventData)
	{
		if (voiceState == VoiceState.SpeakingNote)
		{
			voiceState = VoiceState.Silent;
			curNote++;
			if (curNote == voiceNotes.Length)
			{
				curNote = 0;
				canSpeak = false;
				StartCoroutine(SpeakChord());
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

	IEnumerator SpeakChord()
	{
		yield return new WaitForSeconds(0.4f);
		voiceState = VoiceState.SpeakingChord;
	}
}


public enum VoiceState
{
	Silent, SpeakingNote, SpeakingChord
}