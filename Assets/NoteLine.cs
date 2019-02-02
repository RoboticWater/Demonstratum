using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using Utils;

public class NoteLine : MonoBehaviour, IPointerDownHandler, IPointerUpHandler, IDragHandler
{
    List<Note> notes;
    Note curNote;
    RectTransform rect;

    [Header("Note Line Values")]
    public float minFreq = 261.63f;
    public float maxFreq = 523.25f;

    [Header("References")]
    public Transform notesContainer;

    [Header("Prefabs")]
    public GameObject notePrefab;

    public Vector2 Position {
        get { return rect.position; }
        set { rect.position = value; }
    }

    // Start is called before the first frame update
    void Start()
    {
        notes = new List<Note>();
        rect = GetComponent<RectTransform>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void OnDrag(PointerEventData eventData)
    {
        if (curNote != null) {
            Vector2 localPos;
            RectTransformUtility.ScreenPointToLocalPointInRectangle(rect, eventData.position, eventData.pressEventCamera, out localPos);
            SetNoteValues(localPos);
        }
    }

    public void OnPointerDown(PointerEventData eventData)
    {
        if (eventData.button == PointerEventData.InputButton.Right) {
            Vector2 localPos;
            RectTransformUtility.ScreenPointToLocalPointInRectangle(rect, eventData.position, eventData.pressEventCamera, out localPos);
            Note selected = SelectedNote(localPos);
            if (selected != null)
                DeleteNote(selected);
        } else if (curNote == null) {
            GameObject noteObject = Instantiate(notePrefab, notesContainer);
            curNote = noteObject.GetComponent<Note>();
            curNote.NoteLine = this;
            
            Vector2 localPos;
            RectTransformUtility.ScreenPointToLocalPointInRectangle(rect, eventData.position, eventData.pressEventCamera, out localPos);
            SetNoteValues(localPos);
            notes.Add(curNote);
        }
    }

    public void OnPointerUp(PointerEventData eventData)
    {
        if (curNote != null) {
            curNote = null;
        }
    }

    public void DeleteNote(Note note) {
        notes.Remove(note);
        Destroy(note.gameObject);
    }

    void SetNoteValues(Vector2 localPos) {
        Vector2 constrainedPos = ConstrainedPosition(localPos);
        curNote.LocalPosition = constrainedPos;
        curNote.Frequency = Utils.Math.Map(constrainedPos.y, -rect.sizeDelta.y / 2, rect.sizeDelta.y / 2, minFreq, maxFreq);
    }

    Vector2 ConstrainedPosition(Vector2 pos) {
        return new Vector2(0, Mathf.Clamp(pos.y, -rect.sizeDelta.y / 2, rect.sizeDelta.y / 2));
    }

    Note SelectedNote(Vector2 localPos) {
        foreach (Note n in notes) {
            if (Vector2.Distance(n.LocalPosition, localPos) < n.Radius)
                return n;
        }
        return null;
    }

    float ChordError(float[] chord) {
        if (chord.Length != notes.Count)
            return 10000;
        float error = 0;
        for (int i = 0; i < chord.Length; i++) {
            error += Mathf.Abs(notes[i].Frequency - chord[i]);
        }
        return error;
    }
}
