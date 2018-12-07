using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class Voice : MonoBehaviour, IPointerDownHandler, IPointerUpHandler, IPointerExitHandler, IDragHandler
{
    RectTransform rectTransform;
    public Player player;
    public ProceduralAudioController ac;

    private bool speaking;
    private Vector2 voiceVect;
    private VoiceNote[] notes;

    public void OnPointerDown(PointerEventData eventData)
    {
        if (Input.GetMouseButton(1)) {
            print("right");
        }
        Vector2 vect = eventData.position - (Vector2)rectTransform.position;
        if (vect.magnitude < rectTransform.sizeDelta.x / 2) {
            voiceVect = FromCartesian(vect);
            speaking = true;
            ac.useSinusAudioWave = true;
            ac.mainFrequency = Map(-Mathf.PI / 2, 3 * Mathf.PI / 2, 440, 783.99f, voiceVect.y);
            ac.frequencyModulationOscillatorIntensity = Map(0, rectTransform.sizeDelta.x / 2, 10, 1, voiceVect.x);
            // print(Map(-Mathf.PI / 2, 3 * Mathf.PI / 2,
            //     0, 1, voiceVect.y));
            // print(Map(0, rectTransform.sizeDelta.x / 2,
            //     0, 1, voiceVect.x));
        }
            
    }

    void Start()
    {
        rectTransform = GetComponent<RectTransform>();
    }

    void Update()
    {
        if (speaking) {
            ac.useSinusAudioWave = true;
            ac.mainFrequency = Map(-Mathf.PI / 2, 3 * Mathf.PI / 2, 440, 783.99f, voiceVect.y);
            ac.frequencyModulationOscillatorIntensity = Map(0, rectTransform.sizeDelta.x / 2, 10, 1, voiceVect.x);
        }
    }

    public Vector2 FromCartesian(Vector3 cart)
    {
        if( cart.x == 0f )
            cart.x = Mathf.Epsilon;
        float radius = cart.magnitude;
 
        float polar = Mathf.Atan(cart.y / cart.x);
 
        if( cart.x < 0f )
            polar += Mathf.PI;
        return new Vector2(radius, polar);
    }
    float Map (float from, float to, float from2, float to2, float value) {
        return Mathf.Lerp (from2, to2, Mathf.InverseLerp (from, to, value));
    }

    public void OnPointerUp(PointerEventData eventData)
    {
        speaking = false;
        ac.useSinusAudioWave = false;
    }

    public void OnPointerExit(PointerEventData eventData)
    {
        speaking = false;
        ac.useSinusAudioWave = false;
    }

    public void OnDrag(PointerEventData eventData)
    {
        Vector2 vect = eventData.position - (Vector2)rectTransform.position;
        if (vect.magnitude < rectTransform.sizeDelta.x / 2) {
            voiceVect = FromCartesian(vect);
            speaking = true;
            ac.useSinusAudioWave = true;
            ac.mainFrequency = Map(-Mathf.PI / 2, 3 * Mathf.PI / 2, 440, 783.99f, voiceVect.y);
            ac.frequencyModulationOscillatorIntensity = Map(0, rectTransform.sizeDelta.x / 2, 10, 1, voiceVect.x);
            // print(Map(-Mathf.PI / 2, 3 * Mathf.PI / 2,
            //     0, 1, voiceVect.y));
            // print(Map(0, rectTransform.sizeDelta.x / 2,
            //     0, 1, voiceVect.x));
        }
    }
}
