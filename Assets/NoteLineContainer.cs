using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[ExecuteInEditMode]
public class NoteLineContainer : MonoBehaviour
{
    NoteLine[] noteLines;
    public NoteLine[] NoteLines {
        get { return noteLines; }
    }
    
    [Header("Prefabs")]
    public GameObject noteLinePrefab;

    #if UNITY_EDITOR
    private void Start()
    {
        if (!Application.isEditor) return;
        noteLines = GetComponentsInChildren<NoteLine>();
    }

    private void Update() {
        if (!Application.isEditor) return;
        if (noteLines.Length != transform.childCount) {
            noteLines = GetComponentsInChildren<NoteLine>();
        }
    }
    #endif
}
