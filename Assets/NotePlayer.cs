using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NotePlayer : ProceduralAudioController
{
    Note note;
    public Note Note {
        set {
            note = value;
            playing = true;
            SetAudioValues();
        }
        get { return note; }
    }
    bool playing;
    public bool Playing {
        set { playing = value; }
        get { return playing; }
    }
    public float VolumeDelta = 0.1f;
    float[] velocities = new float[6];
    AudioSource audioSource;

    private void Start()
    {
        audioSource = GetComponent<AudioSource>();
    }

    private void Update() {
        UpdateAudioValues();
        if (note.HasReaction) {
            AudioManager.instance.SoundReactions(note);
        }
        if (audioSource.volume < 0.001f && !playing) {
            gameObject.SetActive(false);
        }
    }

    void UpdateAudioValues() {
        audioSource.volume = Mathf.SmoothDamp(audioSource.volume, playing ? note.Volume : 0, ref velocities[0], VolumeDelta);
        mainFrequency = note.Frequency;
        sinusAudioWaveIntensity = note.Sin;
        useSinusAudioWave = note.Sin > 0.001f;
        squareAudioWaveIntensity = note.Square;
        useSquareAudioWave = note.Square > 0.001f;
        sawAudioWaveIntensity = note.Saw;
        useSawAudioWave = note.Saw > 0.001f;
        frequencyModulationOscillatorFrequency = note.Oscillation;
        useFrequencyModulation = note.Oscillation > 0.001f;
        // audioSource.volume = Mathf.SmoothDamp(audioSource.volume, note.Frequency, ref velocities[1], VolumeDelta);
        // sinusAudioWaveIntensity = Mathf.SmoothDamp(masterVolume, note.Sin, ref velocities[2], VolumeDelta);
        // squareAudioWaveIntensity = Mathf.SmoothDamp(masterVolume, note.Square, ref velocities[3], VolumeDelta);
        // sawAudioWaveIntensity = Mathf.SmoothDamp(masterVolume, note.Saw, ref velocities[4], VolumeDelta);
        // frequencyModulationOscillatorFrequency = Mathf.SmoothDamp(masterVolume, note.Oscillation, ref velocities[5], VolumeDelta);
    }

    void SetAudioValues() {
        // print(note.HasReaction);
        // audioSource.volume = Mathf.SmoothDamp(audioSource.volume, note.Volume, ref velocities[0], VolumeDelta);
        mainFrequency = note.Frequency;
        sinusAudioWaveIntensity = note.Sin;
        squareAudioWaveIntensity = note.Square;
        sawAudioWaveIntensity = note.Saw;
        frequencyModulationOscillatorFrequency = note.Oscillation;
    }
}
