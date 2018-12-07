using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class VoiceNote : MonoBehaviour {
    public static Color[] NOTE_COLORS = {Color.red, Color.blue, Color.green, Color.yellow};
    public static AnimationCurve NOTE_CURVE;
    Image img;
    LineRenderer line;
    Vector2 input, actual;

    void Instantiate(Vector2 input, Vector2 actual, int index) {
        img = GetComponent<Image>();
        line = GetComponent<LineRenderer>();
        this.input = input;
        this.actual = actual;
        Color temp = NOTE_COLORS[index];
        temp.a = 0;
        line.startColor = temp;
        line.endColor = temp;
    }

    void drawError(float degree) {
        // TODO set line point positions
        line.SetPosition(0, transform.position);
        line.SetPosition(1, transform.position + (Vector3)(degree * (actual - input)));
        StartCoroutine(drawErrorLine(degree));
    }

    IEnumerator drawErrorLine(float life) {
        float time = 0;
        float perc = 0;
        float lastTime = Time.realtimeSinceStartup;
        Quaternion curLook = transform.rotation;
        do
        {
          time += Time.realtimeSinceStartup - lastTime;
          lastTime = Time.realtimeSinceStartup;
          perc = Mathf.Clamp01(time / life);
          // TODO set line visibility
          Color temp = line.startColor;
          temp.a = Mathf.Lerp(0, 1, NOTE_CURVE.Evaluate(perc));
          line.startColor = temp;
          line.endColor = temp;
          yield return null;
        } while (perc < 1);
    }
}