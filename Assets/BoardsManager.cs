using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoardsManager : ChordListener
{
    public Wood[] wood;
    public GameObject woodSelectorPrefab;
    public bool broken;

    AudioSource audioSource;

    private void Start()
    {
        audioSource = GetComponent<AudioSource>();
        if (GameManager.instance.GetObject(GetInstanceID() + "_open") != null) {

        }
    }

    private void OnTriggerEnter(Collider other) {
        if (!broken && other.GetComponent<Player>()) {
            broken = true;
            audioSource.pitch = Random.Range(0.8f, 1.2f);
            audioSource.Play();
            for (int i = 0; i < wood.Length; i++) {
                Wood w = wood[i];
                w.deathOffset = i * Random.Range(0.4f, 0.6f);
                w.Break();
                GameObject woodSelector = Instantiate(woodSelectorPrefab, w.transform);
                woodSelector.GetComponent<WoodSelector>().wood = new List<Wood>(wood);
            }
        }
    }
}
