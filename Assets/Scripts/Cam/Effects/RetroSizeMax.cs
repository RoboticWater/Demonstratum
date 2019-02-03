using System;
using UnityEngine;

namespace Assets.Scripts.Cam.Effects {
	[ExecuteInEditMode]
	[RequireComponent(typeof(UnityEngine.Camera))]
	[AddComponentMenu("Image Effects/Custom/Retro Size")]
	public class RetroSizeMax : MonoBehaviour {
		[Header("Colors")]
		public Color[] colors;

		private Material m_material;
		private Shader shader;

		[Header("Resolution")]
		public int verticalResolution = 144;
		public float aspectRatio = 1.333f;
		int horizontalResolution {
			get { return (int) (verticalResolution * aspectRatio); }
		}

		private Material material {
			get {
				return m_material;
			}
		}

		private void Awake() {
			if (m_material == null) {
				shader = Shader.Find("Oxysoft/RetroPixelMax");
				m_material = new Material(shader) {hideFlags = HideFlags.DontSave};
			}
		}

		protected void Start() {
			if (!SystemInfo.supportsImageEffects)
				enabled = false;
		}

		public void OnRenderImage(RenderTexture src, RenderTexture dest) {

			RenderTexture scaled = RenderTexture.GetTemporary(horizontalResolution, verticalResolution);
			RenderTexture colorized = RenderTexture.GetTemporary(horizontalResolution, verticalResolution);
			colorized.filterMode = FilterMode.Point;
			scaled.filterMode = FilterMode.Point;
			Graphics.Blit(src, scaled);
			if (material && colors.Length > 0) {
				material.SetInt("_ColorCount", colors.Length);
				material.SetColorArray("_Colors", colors);
				Graphics.Blit(scaled, colorized, material);
                Graphics.Blit(colorized, dest);
			} else {
				Graphics.Blit(scaled, dest);
			}
			RenderTexture.ReleaseTemporary(scaled);
			RenderTexture.ReleaseTemporary(colorized);
		}

		private void OnDisable() {
			#if UNITY_EDITOR
			if (m_material)
				DestroyImmediate(m_material);
			#else
			if (m_material)
				Destroy(m_material);
			#endif
		}
	}
}