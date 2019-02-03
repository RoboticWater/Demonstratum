using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class Note : MonoBehaviour
{
    NoteLine noteLine;
    VoiceNote voiceNote;
    RectTransform rect;
    [SerializeField] float frequency;

    public NoteLine NoteLine {
        set { noteLine = value; }
    }

    public float Radius {
        get { return rect.sizeDelta.x / 2; }
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
    // Start is called before the first frame update
    void Start()
    {
        rect = GetComponent<RectTransform>();
    }

    public void Play(float intensity) {
        voiceNote = AudioManager.instance.GetNote();
        voiceNote.mainFrequency = frequency;
        voiceNote.SetWave(intensity, WaveType.Sine);
    }

    public void Stop() {
        voiceNote.Silence();
        voiceNote = null;
    }
}
