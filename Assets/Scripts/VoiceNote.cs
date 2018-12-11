using System.Collections;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.UI.Extensions;

public class VoiceNote : MonoBehaviour
{
	Image img;
	UILineRenderer line;
	RectTransform rt;
	public Vector2 input, error;
	int index;

	public void Instantiate(Vector2 input, int index)
	{
		img = GetComponent<Image>();
		line = GetComponentInChildren<UILineRenderer>();
		// rt = 
		this.input = input;
		Color temp = GameManager.instance.NOTE_COLORS[index];
		temp.a = 0;
		line.color = temp;
		this.index = index;
	}

	public void UpdateLine(Vector2 e)
	{
		line.Points[0] = new Vector2(0, 0);
		line.Points[1] = e;
		error = e;
		line.SetAllDirty();
	}

	public void drawError(float degree, float life, Image success = null)
	{
		line.Points[1] *= degree;
		line.SetAllDirty();
		StartCoroutine(drawErrorLine(life, success));
	}

	IEnumerator drawErrorLine(float life, Image success = null)
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
			if (success != null)
			{
				temp = success.color;
				temp.a = Mathf.Lerp(0, 1, GameManager.instance.NOTE_CURVE.Evaluate(perc)) / 3;
				success.color = temp;
			}
			yield return null;
		} while (perc < 1);
	}
}