using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BirdSinger : ChordListener
{
    [Header("Notes")]
    [SerializeField] private ParticleSystem noteParticle;
    [SerializeField] private float[] frequencies;
    [SerializeField] private float[] oscillations;
    [SerializeField] private float[] playTimes;
    Note[] notes;

    [Header("Singing")]
    [SerializeField] private float noteRestTime = 0.2f;
    [SerializeField] private float singRestTime = 2f;
    [SerializeField] private BirdSinger nextSinger;

    [Header("Animating")]
    [SerializeField] private float lookSpeed = 2.5f;

    [Header("Prefabs")]
    [SerializeField] private GameObject BirdNotePrefab;

    bool singing;
    
    void Start()
    {
        notes = new Note[frequencies.Length];
        for (int i = 0; i < frequencies.Length; i++) {
            GameObject noteObject = Instantiate(BirdNotePrefab, transform);
            notes[i] = noteObject.GetComponent<Note>();
            notes[i].doReaction = false;
            notes[i].GetComponent<Note>().Frequency = frequencies[i];
            notes[i].Oscillation = oscillations[i];
        }
    }

    private void Update() {
        if (listening) {
            if (!singing)
                StartCoroutine(Sing());
            Vector3 dir = GameManager.instance.Player.transform.position - transform.position;
            dir.y = 0;
            Quaternion rot = Quaternion.LookRotation(dir);
            transform.rotation = Quaternion.Slerp(transform.rotation, rot, lookSpeed * Time.deltaTime);
        }
    }

    IEnumerator Sing() {
        singing = true;
        for (int i = 0; i < notes.Length; i++) {
            Note n = notes[i];
            n.Play(0.3f);
            var main = noteParticle.main;
            main.startLifetime = playTimes[i];
            noteParticle.Emit(1);
            yield return new WaitForSeconds(playTimes[i]);
            n.Stop();
            yield return new WaitForSeconds(noteRestTime);
        }
        yield return new WaitForSeconds(singRestTime);
        singing = false;
    }

    public override void OnSound(float intensity)
    {
        if (listening)
            print("Next bird");
    }

    public override void Save()
    {
        
    }
}
