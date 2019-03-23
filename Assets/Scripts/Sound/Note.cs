using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class Note : MonoBehaviour
{
    VoiceNote voiceNote;
    RectTransform rect;
    public bool doReaction = true;
    [SerializeField] float frequency;
    [SerializeField] float oscillation;

    public float Radius {
        get { return GetComponent<RectTransform>().sizeDelta.x / 2; }
    }

    public Vector2 LocalPosition {
        get { return transform.localPosition; }
        set { transform.localPosition = value; }
    }

    public float Frequency {
        get { return frequency; }
        set {
            if (voiceNote != null)
                voiceNote.mainFrequency = frequency; 
            frequency = value; 
        }
    }

    public float Oscillation {
        get { return oscillation; }
        set {
            if (voiceNote != null) {
                voiceNote.useFrequencyModulation = value != 0;
                voiceNote.frequencyModulationOscillatorFrequency = value; 
            }
            oscillation = value; 
        }
    }

    public void Play(float intensity = 1f) {
        voiceNote = AudioManager.instance.GetNote();
        voiceNote.doReaction = false;
        voiceNote.mainFrequency = frequency;
        voiceNote.frequencyModulationOscillatorFrequency = oscillation; 
        voiceNote.useFrequencyModulation = oscillation != 0;
        voiceNote.SetWave(intensity, WaveType.Sine);
    }

    public void Stop() {
        voiceNote.Silence();
        voiceNote = null;
    }
}
