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
        if (wave.HasFlag(WaveType.Sine))
            sinusAudioWaveIntensity = Mathf.SmoothDamp(sinusAudioWaveIntensity, intensityTarget, ref volumeVelocity, volumeTime);
        else if (wave.HasFlag(WaveType.Saw))
            squareAudioWaveIntensity = Mathf.SmoothDamp(squareAudioWaveIntensity, intensityTarget, ref volumeVelocity, volumeTime);
        else if (wave.HasFlag(WaveType.Square))
            sawAudioWaveIntensity = Mathf.SmoothDamp(sawAudioWaveIntensity, intensityTarget, ref volumeVelocity, volumeTime);
        if (sinusAudioWaveIntensity + squareAudioWaveIntensity + sawAudioWaveIntensity < 0.001f && intensityTarget == 0) {
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
