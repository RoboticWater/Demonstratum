using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class Note : MonoBehaviour
{
    NoteLine noteLine;
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
        set { frequency = value; }
    }
    // Start is called before the first frame update
    void Start()
    {
        rect = GetComponent<RectTransform>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void Play() {

    }

    public void Stop() {

    }
}
