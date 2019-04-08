using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class Note : MonoBehaviour
{
    [SerializeField] float sin;
    public float Sin {
        get { return sin; }
        set { sin = value; }
    }
    [SerializeField] float saw;
    public float Saw {
        get { return saw; }
        set { saw = value; }
    }
    [SerializeField] float square;
    public float Square {
        get { return square; }
        set { square = value; }
    }
    [SerializeField] float volume;
    public float Volume {
        get { return volume; }
        set { volume = value; }
    }
    [SerializeField] float frequency;
    public float Frequency {
        get { return frequency; }
        set { frequency = value; }
    }
    [SerializeField] float oscillation;
    public float Oscillation {
        get { return oscillation; }
        set { oscillation = value; }
    }
    [SerializeField] bool hasReaction;
    public bool HasReaction {
        get { return hasReaction; }
        set { hasReaction = value; }
    }
    NotePlayer player;
    [SerializeField] NoteLine noteLine;
    public NoteLine NoteLine {
        get { return noteLine; }
        set { noteLine = value; }
    }

    public void MakeNote(float frequency, bool hasReaction, float oscillation=0, float volume=1, float sin=1, float saw=0, float square=0) {
        // print(hasReaction);
        Frequency = frequency;
        HasReaction = hasReaction;
        Volume = volume;
        Oscillation = oscillation;
        Sin = sin;
        Saw = saw;
        Square = square;
    }

    public void Play() {
        player = AudioManager.instance.GetNotePlayer();
        player.Playing = true;
        player.Note = this;
    }

    public void Stop() {
        player.Playing = false;
    }
}
