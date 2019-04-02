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
    public List<SoundReactor> soundReactors;

    [Header("Prefabs")]
    public GameObject voiceNotePrefab;

    List<NotePlayer> notePlayers;

    private void Awake()
	{
		if (instance == null)
			instance = this;
		else if (instance != this)
			Destroy(gameObject);
		DontDestroyOnLoad(gameObject);
	}

    private void Start() {
        soundReactors = new List<SoundReactor>();
        notePlayers = new List<NotePlayer>(voiceNoteContainer.GetComponentsInChildren<NotePlayer>());
        GetSoundReactors();
    }

    public void GetSoundReactors() {
        var srs = FindObjectsOfType<MonoBehaviour>().OfType<SoundReactor>();
        foreach (SoundReactor s in srs) {
            soundReactors.Add(s);
        }
    }

    public NotePlayer GetNote() {
        foreach (NotePlayer n in notePlayers) {
            if (!n.gameObject.activeSelf) {
                n.gameObject.SetActive(true);
                return n;
            }
        }
        List<NotePlayer> pool = ExpandPool();
        pool[0].gameObject.SetActive(true);
        return pool[0];
    }

    public NotePlayer GetNotePlayer() {
        foreach (NotePlayer n in notePlayers) {
            if (!n.gameObject.activeSelf) {
                n.gameObject.SetActive(true);
                return n;
            }
        }
        List<NotePlayer> pool = ExpandPool();
        pool[0].gameObject.SetActive(true);
        return pool[0];
    }

    public List<NotePlayer> GetNotes(int num) {
        List<NotePlayer> outNotes = (from note in notePlayers where !note.Playing select note).ToList();
        if (outNotes.Count >= num) {
            outNotes = outNotes.GetRange(0, num);
            foreach(NotePlayer n in outNotes)
                n.gameObject.SetActive(true);
            return outNotes;
        }
        outNotes = outNotes.Concat(ExpandPool()).ToList().GetRange(0, num);
        foreach(NotePlayer n in outNotes)
            n.gameObject.SetActive(true);
        return outNotes;
    }

    List<NotePlayer> ExpandPool() {
        List<NotePlayer> newNotes = new List<NotePlayer>();
        for (int i = 0; i < poolStep; i++) {
            GameObject voiceNote = Instantiate(voiceNotePrefab, voiceNoteContainer);
            voiceNote.SetActive(false);
            notePlayers.Add(voiceNote.GetComponent<NotePlayer>());
            newNotes.Add(voiceNote.GetComponent<NotePlayer>());
        }
        return newNotes;
    }

    public void SoundReactions(Note n) {
        foreach (SoundReactor s in soundReactors) {
            s.OnSound(n);
        }
    }
    public void SoundFinishReactions(Note n) {
        foreach (SoundReactor s in soundReactors) {
            s.OnSoundFinish(n);
        }
    }

    public void SilenceAll() {

    }
}
