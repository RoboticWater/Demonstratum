using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Mover : Persistent
{
    public Vector3 endOffset;
    Vector3 startPos;
    public float moveTime = 0.1f;
    public AnimationCurve motionCurve;

    [SerializeField] bool moved;
    bool moving;

    void Start()
    {
        startPos = transform.position;
        object m = GameManager.instance.GetObject(this, "moved");
        if (m != null && (bool) m) {
            transform.position = startPos + endOffset;
            moved = (bool) m;
        }
    }

    public void Move() {
        StartCoroutine(MoveRoutine());
    }

    IEnumerator MoveRoutine() {
        moving = true;
        float lastTime = Time.timeSinceLevelLoad;
        float perc = moved ? 1 : 0;
        Vector3 endPos = startPos + endOffset;
        do {
            perc += (moved ? -1 : 1) * (Time.timeSinceLevelLoad - lastTime) / moveTime;
            lastTime = Time.timeSinceLevelLoad;
            transform.position = Vector3.Lerp(startPos, endPos, motionCurve.Evaluate(perc));
            yield return null;
        } while(perc <= 1 && perc >= 0);
        transform.position = moved ? startPos : endPos;
        moved = !moved;
        moving = false;
    }

    public override void Save()
    {
        GameManager.instance.SetObject(this, "moved", moved || moving);
    }
}
