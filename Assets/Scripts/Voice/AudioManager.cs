using System.Linq;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AudioManager : MonoBehaviour
{

    public int poolStep = 6;
    public static AudioManager instance;

    [Header("References")]
    public Transform voiceNoteContainer;
    public SoundReactor[] soundReactors;

    [Header("Prefabs")]
    public GameObject voiceNotePrefab;

    List<VoiceNote> voiceNotes;

    private void Awake()
	{
		if (instance == null)
			instance = this;
		else if (instance != this)
			Destroy(gameObject);
		DontDestroyOnLoad(gameObject);
	}

    private void Start() {
        voiceNotes = new List<VoiceNote>(voiceNoteContainer.GetComponentsInChildren<VoiceNote>());
    }

    public VoiceNote GetNote() {
        foreach (VoiceNote n in voiceNotes) {
            if (!n.gameObject.activeSelf) {
                n.gameObject.SetActive(true);
                return n;
            }
        }
        List<VoiceNote> pool = ExpandPool();
        pool[0].gameObject.SetActive(true);
        return pool[0];
    }

    public List<VoiceNote> GetNotes(int num) {
        List<VoiceNote> outNotes = (from note in voiceNotes where !note.Playing select note).ToList();;
        if (outNotes.Count >= num) {
            outNotes = outNotes.GetRange(0, num);
            foreach(VoiceNote n in outNotes)
                n.gameObject.SetActive(true);
            return outNotes;
        }
        outNotes = outNotes.Concat(ExpandPool()).ToList().GetRange(0, num);
        foreach(VoiceNote n in outNotes)
            n.gameObject.SetActive(true);
        return outNotes;
    }

    List<VoiceNote> ExpandPool() {
        List<VoiceNote> newNotes = new List<VoiceNote>();
        for (int i = 0; i < poolStep; i++) {
            GameObject voiceNote = Instantiate(voiceNotePrefab, voiceNoteContainer);
            voiceNote.SetActive(false);
            voiceNotes.Add(voiceNote.GetComponent<VoiceNote>());
            newNotes.Add(voiceNote.GetComponent<VoiceNote>());
        }
        return newNotes;
    }

    public void SoundReactions(float intensity) {
        foreach (SoundReactor s in soundReactors) {
            s.OnSound(intensity);
        }
    }

    public void SilenceAll() {

    }
}
