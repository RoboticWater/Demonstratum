using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[ExecuteInEditMode]
public class Pixelate : MonoBehaviour {
	public Material effectMat;
	public float pixels = 64;
	private void Start()
	{
		print(Screen.width / Screen.height);
		effectMat.SetFloat("_Ratio", Screen.width / Screen.height);
	}

	private void OnRenderImage(RenderTexture source, RenderTexture destination)
	{
		effectMat.SetFloat("_Pixels", pixels);
		Graphics.Blit(source, destination, effectMat);
	}
}
