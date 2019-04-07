using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI.Extensions;


public class UINote : Note
{
    RectTransform rect;
    UILineRenderer line;
    public float ErrorLife;
    public float Radius {
        get { return GetComponent<RectTransform>().sizeDelta.x / 2; }
    }

    public Vector2 LocalPosition {
        get { return transform.localPosition; }
        set { transform.localPosition = value; }
    }

    public void MakeNote(float frequency, Vector2 localPosition, float oscillation=0, float volume=1, float sin=1, float saw=0, float square=0) {
        base.MakeNote(frequency, true, oscillation, volume, sin, saw, square);
		LocalPosition = localPosition;
    }

    public void ShowError(float correct) {
        StartCoroutine(ErrorRoutine(correct));
    }

    // Image img;
	// UILineRenderer line;
	// RectTransform rt;
	// public Vector2 input;

	// public void Instantiate(Vector2 input, int index)
	// {
	// 	img = GetComponent<Image>();
	// 	line = GetComponentInChildren<UILineRenderer>();
	// 	// rt = 
	// 	this.input = input;
	// 	Color temp = GameManager.instance.NOTE_COLORS[index];
	// 	temp.a = 0;
	// 	line.color = temp;
	// }

    // public void UpdateLine(Vector2 error)
	// {
	// 	line.Points[0] = new Vector2(0, 0);
	// 	line.Points[1] = error;
	// 	line.SetAllDirty();
	// }

	// public void drawError(float degree, float life)
	// {
	// 	line.Points[1] *= degree;
	// 	line.SetAllDirty();
	// 	StartCoroutine(drawErrorLine(life));
	// }

    IEnumerator ErrorRoutine(float correct) {
		yield return new WaitForSeconds(1);
		// float time = 0;
		// float perc = 0;
		// float lastTime = Time.realtimeSinceStartup;
		// // Quaternion curLook = transform.rotation;
		// do
		// {
		// 	time += Time.realtimeSinceStartup - lastTime;
		// 	lastTime = Time.realtimeSinceStartup;
		// 	perc = Mathf.Clamp01(time / ErrorLife);
		// 	// TODO set line visibility
		// 	Color temp = line.color;
		// 	temp.a = Mathf.Lerp(0, 1, GameManager.instance.NOTE_CURVE.Evaluate(perc));
		// 	line.color = temp;
		// 	yield return null;
		// } while (perc < 1);
    }
}
