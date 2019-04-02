using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class SequenceListener : SoundListener, SoundReactor
{

    List<Note> sequence;
    public UnityEvent[] sequenceActivateEvents;
    public UnityEvent[] sequenceDectivateEvents;
    public float[] frequencies;
    List<Note> heardNotes;
    bool completed;
    public float error = 0.01f;
    public float successReactionDelay = 0.5f;

    public override void OnSoundFinish(Note n) {
        if (heardNotes.Contains(n))
            return;
        if (testNote(n, heardNotes.Count)) {
            sequenceActivateEvents[heardNotes.Count].Invoke();
        }
        heardNotes.Add(n);
        if (heardNotes.Count >= frequencies.Length) {
            bool success = true;
            int i = 0;
            foreach (Note note in heardNotes) {
                success &= testNote(note, i);
                print(success);
            }
            StartCoroutine(DelayedReaction(success));
        }
    }

    bool testNote(Note n, int index) {
        print(Mathf.Abs(n.Frequency));
        return Mathf.Abs(n.Frequency - frequencies[index]) < error;
    }

    // Start is called before the first frame update
    void Start()
    {
        heardNotes = new List<Note>();
        object c = GameManager.instance.GetObject(this, "completed");
        if (c != null && (bool) c) {
            gameObject.SetActive(false);
        }
    }

    public override void Save() {
        GameManager.instance.SetObject(this, "completed", completed);
    }

    IEnumerator DelayedReaction(bool success) {
        yield return new WaitForSeconds(successReactionDelay);
        if (success) {
            print("success");
            soundEvent.Invoke();
        }
        else
            OnFail();

    }

    public override void OnFail()
    {
        int i = 0;
        foreach (Note n in heardNotes) {
            UINote uiNote = n as UINote;
            if (uiNote)
                uiNote.ShowError(frequencies[i++]);
        }
        heardNotes = new List<Note>();
    }

    public override void OnSound(Note n)
    {
        
    }
}
