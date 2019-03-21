using System.Collections;
using System.Collections.Generic;
using UnityEngine;
 
public class SetInteractiveShaderEffects : MonoBehaviour
{
    [SerializeField]
    RenderTexture rt;
    // Start is called before the first frame update
    void Awake()
    {
        Shader.SetGlobalTexture("_OcclusionTex", rt);
        Shader.SetGlobalFloat("_OrthographicCamSize", GetComponent<Camera>().orthographicSize);
    }
 
}