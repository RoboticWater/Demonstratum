using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using Utils;

public class NoteLine : MonoBehaviour, IPointerDownHandler, IPointerUpHandler, IDragHandler
{
    List<Note> notes;
    Note curNote;
    RectTransform rect;

    [Header("Note Line Values")]
    [SerializeField] private float minFreq = 261.63f;
    [SerializeField] private float maxFreq = 523.25f;

    [Header("References")]
    [SerializeField] private Transform notesContainer;
    [SerializeField] private GameObject playingIcon;
    [SerializeField] private GameObject chordContainer;
    [SerializeField] private Image chordIcon;

    [Header("Prefabs")]
    [SerializeField] private GameObject notePrefab;

    public Vector2 Position {
        get { return rect.position; }
        set { rect.position = value; }
    }

    public bool Empty {
        get { return notes.Count == 0; }
    }

    public bool HasChord {
        get { return chord != null; }
    }

    Chord chord;

    /// <summary>
    /// Instantiates all variabes
    /// </summary>
    void Start()
    {
        notes = new List<Note>();
        rect = GetComponent<RectTransform>();
        chordContainer.SetActive(false);
    }

    /// <summary>
    /// Toggles this noteline on, playing all notes on the line until told to stop
    /// </summary>
    public void Play() {
        playingIcon.SetActive(true);
        foreach (Note n in notes) {
            n.Play(1);
        }
    }

    /// <summary>
    /// Toggles this noteline off, silencing all notes on this line
    /// </summary>
    public void Stop() {
        playingIcon.SetActive(false);
        foreach (Note n in notes) {
            n.Stop();
        }
    }

    public void SetChord(Chord c) {
        chordContainer.SetActive(true);
        chordIcon.sprite = c.icon.sprite;
        chordIcon.color = c.icon.color;
        chord = c;
        ClearNotes();
        foreach (float freq in c.frequencies) {
            notes.Add(makeNote(freq));
        }
    }

    void UnsetChord() {
        chord = null;
        ClearNotes();
        chordContainer.SetActive(false);
    }

    void ClearNotes() {
        foreach (Note n in notes) {
            Destroy(n.gameObject);
        }
        notes.Clear();
    }

    Note makeNote(float frequency) {
        GameObject noteObject = Instantiate(notePrefab, notesContainer);
        Note n = noteObject.GetComponent<Note>();
        // n.NoteLine = this;
        SetNoteValuesFromFreq(n, frequency);
        return n;
    }

    /// <summary>
    /// When the user drags their mouse on this element, if there's a note currently in use, change its position and frequency values
    /// </summary>
    /// <param name="eventData">Event  data from the mouse, e.g. position</param>
    public void OnDrag(PointerEventData eventData)
    {
        if (curNote != null) {
            Vector2 localPos;
            RectTransformUtility.ScreenPointToLocalPointInRectangle(rect, eventData.position, eventData.pressEventCamera, out localPos);
            SetNoteValuesFromPos(curNote, localPos);
        }
    }

    /// <summary>
    /// When the user clicks their mouse down on this element:
    /// - On right click, delete a note if they're over one
    /// - On left click, if there isn't a current note (there shouldn't be) then make one and instantiate its values
    /// </summary>
    /// <param name="eventData">Event  data from the mouse, e.g. position</param>
    public void OnPointerDown(PointerEventData eventData)
    {
        if (eventData.button == PointerEventData.InputButton.Right) {
            if (HasChord) {
                UnsetChord();
                return;
            }
            Vector2 localPos;
            RectTransformUtility.ScreenPointToLocalPointInRectangle(rect, eventData.position, eventData.pressEventCamera, out localPos);
            Note selected = SelectedNote(localPos);
            if (selected != null)
                DeleteNote(selected);
        } else if (curNote == null) {
            GameObject noteObject = Instantiate(notePrefab, notesContainer);
            curNote = noteObject.GetComponent<Note>();
            // curNote.NoteLine = this;
            Vector2 localPos;
            RectTransformUtility.ScreenPointToLocalPointInRectangle(rect, eventData.position, eventData.pressEventCamera, out localPos);
            SetNoteValuesFromPos(curNote, localPos);
            curNote.Play(1f);
        }
    }

    /// <summary>
    /// When the user unclicks their mouse on this element, if there's a current note, silence it, then if the note isn't occupying the same space as another, add it to the note list, otherwise discard it
    /// </summary>
    /// <param name="eventData">Event  data from the mouse, e.g. position</param>
    public void OnPointerUp(PointerEventData eventData)
    {
        if (curNote != null) {
            curNote.Stop();
            Vector2 localPos;
            RectTransformUtility.ScreenPointToLocalPointInRectangle(rect, eventData.position, eventData.pressEventCamera, out localPos);
            if (SelectedNote(localPos) == null)
                notes.Add(curNote);
            else {
               DeleteNote(curNote);
            }
            curNote = null;
        }
    }

    /// <summary>
    /// Performs all the necessary actions to delete a note from this line
    /// </summary>
    /// <param name="note">The Note object to remove from this line</param>
    public void DeleteNote(Note note) {
        notes.Remove(note);
        Destroy(note.gameObject);
    }

    /// <summary>
    /// Maps a local position value to all the necessary note values. In this case, the x is ignored and the y is mapped to frequency
    /// </summary>
    /// <param name="localPos">Position relative to the anchor point of this element</param>
    void SetNoteValuesFromPos(Note n, Vector2 localPos) {
        Vector2 constrainedPos = ConstrainedPosition(localPos);
        n.LocalPosition = constrainedPos;
        n.Frequency = Utils.Math.Map(constrainedPos.y, -rect.sizeDelta.y / 2, rect.sizeDelta.y / 2, minFreq, maxFreq);
    }
    void SetNoteValuesFromFreq(Note n, float freq) {
        float localy = Utils.Math.Map(freq, minFreq, maxFreq, -rect.sizeDelta.y / 2, rect.sizeDelta.y / 2);
        n.LocalPosition = new Vector2(0, localy);
        n.Frequency = freq;
    }

    /// <summary>
    /// Constrains a position vector to x = 0, bottom of line <= y <= top of line
    /// </summary>
    /// <param name="pos">Position to constrain</param>
    /// <returns></returns>
    Vector2 ConstrainedPosition(Vector2 pos) {
        return new Vector2(0, Mathf.Clamp(pos.y, -rect.sizeDelta.y / 2, rect.sizeDelta.y / 2));
    }

    /// <summary>
    /// Determines if the input position is overlapping any notes. This is necessary here and not in the notes themselves because pointer events for children are surpressed
    /// </summary>
    /// <param name="localPos">Position relative to the anchor point of this element</param>
    /// <returns></returns>
    Note SelectedNote(Vector2 localPos) {
        foreach (Note n in notes) {
            if (Vector2.Distance(n.LocalPosition, localPos) < n.Radius)
                return n;
        }
        return null;
    }

    // TODO
    /// <summary>
    /// Gets how incorrect this line is compared to the given chord
    /// </summary>
    /// <param name="chord">Array of frequencies of a chord</param>
    /// <returns>The error between the chord values and this line's note values</returns>
    float ChordError(float[] chord) {
        return 0;
    }
}
