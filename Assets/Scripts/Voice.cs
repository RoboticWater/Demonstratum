using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public class Voice : MonoBehaviour, IPointerDownHandler, IPointerUpHandler, IDragHandler
{
	public Player player;
	public ProceduralAudioController[] audioControllers;
	public GameObject voiceNotePrefab;
	public float voiceSpeed = 0.3f;
	public float noteMaxVol = 0.5f;
	public float chordMaxVol = 0.8f;
	public float chordLength = 1f;
	public Image successRing;
	public float noteError = 40f;
	float chordTime;


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
		chordTime = chordLength;
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
					chordTime = chordLength;
					voiceState = VoiceState.Silent;
					canSpeak = true;
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

		if (Input.GetButtonDown("Undo") && canSpeak)
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
		UpdateNote(curNote, eventData.position);
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
		UpdateNote(curNote, eventData.position);
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

	void UpdateNote(int note, Vector2 pos)
	{
		voiceNotes[note].transform.position = pos;
		voiceNotes[note].input = GetVoiceVect(pos - (Vector2)rectTransform.position, rectTransform.sizeDelta);
		voiceNotes[note].UpdateLine(GetActualDir(voiceNotes[note].input, GameManager.instance.levelManager.curGoal[note]));
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
		Vector2 input = GetVoiceVect(pos, rectTransform.sizeDelta);
		vn.Instantiate(input, curNote);
		vn.transform.localPosition = pos;
		return vn;
	}

	Vector2 GetVoiceVect(Vector2 pos, Vector2 sizeDelta)
	{
		Vector2 polar = FromCartesian(pos);
		return new Vector2(Map(-Mathf.PI / 2, 3 * Mathf.PI / 2, 400, 800, polar.x), Map(0, sizeDelta.x / 2, 10, 1, polar.y));
	}

	Vector2 GetActualDir(Vector2 input, Vector2 actual)
	{
		Vector2 mInput = new Vector2(Map(400, 800, -Mathf.PI / 2, 3 * Mathf.PI / 2, input.x), Map(10, 1, 0, rectTransform.sizeDelta.x / 2, input.y));
		Vector2 mActual = new Vector2(Map(400, 800, -Mathf.PI / 2, 3 * Mathf.PI / 2, actual.x), Map(10, 1, 0, rectTransform.sizeDelta.x / 2, actual.y));
		return ToCartesian(mActual) - ToCartesian(mInput);
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

	public Vector3 ToCartesian(Vector2 v)
	{
		return v.y * new Vector2(Mathf.Cos(v.x), Mathf.Sin(v.x));
	}

	public bool CheckSuccess()
	{
		bool val = true;
		foreach (VoiceNote v in voiceNotes)
		{
			val &= v.error.magnitude < noteError;
		}
		return val;
	}

	IEnumerator SpeakChord()
	{
		yield return new WaitForSeconds(0.4f);
		bool success = CheckSuccess();
		if (success)
			GameManager.instance.levelManager.IncrementGoal();
		for (int i = 0; i < voiceNotes.Length; i++)
		{
			if (success)
			{
				if (i == 0)
					voiceNotes[i].drawError(0, chordLength, successRing);
				else
					voiceNotes[i].drawError(0, chordLength);
			}
			else
			{
				voiceNotes[i].drawError(0.5f, chordLength);
			}
		}
		voiceState = VoiceState.SpeakingChord;
	}
}

public enum VoiceState
{
	Silent, SpeakingNote, SpeakingChord
}