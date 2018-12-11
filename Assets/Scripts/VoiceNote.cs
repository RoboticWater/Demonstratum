using System.Collections;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.UI.Extensions;

public class VoiceNote : MonoBehaviour
{
	Image img;
	UILineRenderer line;
	RectTransform rt;
	public Vector2 input;

	public void Instantiate(Vector2 input, int index)
	{
		img = GetComponent<Image>();
		line = GetComponentInChildren<UILineRenderer>();
		// rt = 
		this.input = input;
		Color temp = GameManager.instance.NOTE_COLORS[index];
		temp.a = 0;
		line.color = temp;
	}

	public void UpdateLine(Vector2 error)
	{
		line.Points[0] = new Vector2(0, 0);
		line.Points[1] = error;
		line.SetAllDirty();
	}

	public void drawError(float degree, float life)
	{
		line.Points[1] *= degree;
		line.SetAllDirty();
		StartCoroutine(drawErrorLine(life));
	}

	IEnumerator drawErrorLine(float life)
	{
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
			Color temp = line.color;
			temp.a = Mathf.Lerp(0, 1, GameManager.instance.NOTE_CURVE.Evaluate(perc));
			line.color = temp;
			yield return null;
		} while (perc < 1);
	}
}