using System;
using UnityEngine;

namespace Assets.Scripts.Cam.Effects {
	[ExecuteInEditMode]
	[RequireComponent(typeof(UnityEngine.Camera))]
	[AddComponentMenu("Image Effects/Custom/Retro Size")]
	public class RetroSize : MonoBehaviour {
		[Header("Resolution")]
		public int verticalResolution = 144;
		public float aspectRatio = 1.333f;
		int horizontalResolution {
			get { return (int) (verticalResolution * aspectRatio); }
		}

		protected void Start() {
			if (!SystemInfo.supportsImageEffects)
				enabled = false;
		}

		public void OnRenderImage(RenderTexture src, RenderTexture dest) {

			RenderTexture scaled = RenderTexture.GetTemporary(horizontalResolution, verticalResolution);
			scaled.filterMode = FilterMode.Point;
			Graphics.Blit(src, scaled);
			Graphics.Blit(scaled, dest);
			RenderTexture.ReleaseTemporary(scaled);
		}
	}
}