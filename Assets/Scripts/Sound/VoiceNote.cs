using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VoiceNote : ProceduralAudioController
{
    public float volumeTime = 0.1f;
    WaveType wave;
    float volumeVelocity = 0;
    float intensityTarget;
    AudioSource audioSource;
    public bool doReaction = true;

    private void Start()
    {
        audioSource = GetComponent<AudioSource>();
    }

    public bool Playing {
        get { return useSawAudioWave | useSinusAudioWave | useSquareAudioWave; }
    }

    public void SetWave(float intensity, WaveType wave) {
        this.intensityTarget = intensity;
        this.wave = wave;
        useSawAudioWave = wave.HasFlag(WaveType.Saw);
        useSinusAudioWave = wave.HasFlag(WaveType.Sine);
        useSquareAudioWave = wave.HasFlag(WaveType.Square);
    }

    void Update() {
        float intensity = Mathf.SmoothDamp(audioSource.volume, intensityTarget, ref volumeVelocity, volumeTime);
        audioSource.volume = intensity;
        if (doReaction)
            AudioManager.instance.SoundReactions(intensity);
        
        if (wave.HasFlag(WaveType.Sine))
            sinusAudioWaveIntensity = 1;
        else if (wave.HasFlag(WaveType.Saw))
            squareAudioWaveIntensity = 1;//Mathf.SmoothDamp(squareAudioWaveIntensity, intensityTarget, ref volumeVelocity, volumeTime);
        else if (wave.HasFlag(WaveType.Square))
            sawAudioWaveIntensity = 1;//Mathf.SmoothDamp(sawAudioWaveIntensity, intensityTarget, ref volumeVelocity, volumeTime);
        if (audioSource.volume < 0.001f && intensityTarget == 0) {
            gameObject.SetActive(false);
        }
    } 

    public void Silence() {
        this.intensityTarget = 0;
    }
}

[Flags] public enum WaveType
{
    None, Sine, Square, Saw
}
