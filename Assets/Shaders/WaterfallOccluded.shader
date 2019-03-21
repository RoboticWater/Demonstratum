Shader "Custom/WaterfallOccluded"
{
    Properties
    {
        _Color ("Color", Color) = (1,1,1,1)
        _MainTex ("Albedo (RGB)", 2D) = "white" {}
        _Glossiness ("Smoothness", Range(0,1)) = 0.5
        _Metallic ("Metallic", Range(0,1)) = 0.0
        _OcclusionTex ("Occlusion Render Texture", 2D) = "white" {}
        _WavesTex ("Waves Texture", 2D) = "black" {}
        _WavesColor ("Waves Color", Color) = (1,1,1,1)
        _Speed ("Speed", Float) = 25
        _Offset ("Vertex Offset", Float) = 1.0
    }
    SubShader
    {
        Tags { "Queue"="Transparent" "RenderType"="Transparent" }
        LOD 200

        CGPROGRAM
        // Physically based Standard lighting model, and enable shadows on all light types
        #pragma surface surf Standard fullforwardshadows vertex:vert alpha:fade

        // Use shader model 3.0 target, to get nicer looking lighting
        #pragma target 3.0

        sampler2D _MainTex;
        sampler2D _WavesTex;
        uniform sampler2D _OcclusionTex;

        struct Input
        {
            float2 uv_MainTex;
            float2 uv_WavesTex;
        };

        half _Glossiness;
        half _Metallic;
        fixed4 _Color;
        uniform float _OrthographicCamSize;
        uniform float3 _Position;
        fixed4 _WavesColor;
        float _Speed;
        float _Offset;

        void vert(inout appdata_full v)
        {
            float4 off = tex2Dlod(_WavesTex, float4(v.texcoord.x, v.texcoord.y + _Speed * 0.01 * _Time.w, 0, 0)) * _Offset;
            v.vertex.xyz += v.normal * off;
        }

        // Add instancing support for this shader. You need to check 'Enable Instancing' on materials that use the shader.
        // See https://docs.unity3d.com/Manual/GPUInstancing.html for more information about instancing.
        // #pragma instancing_options assumeuniformscaling
        UNITY_INSTANCING_BUFFER_START(Props)
            // put more per-instance properties here
        UNITY_INSTANCING_BUFFER_END(Props)

        void surf (Input IN, inout SurfaceOutputStandard o)
        {
            half occ = tex2D (_OcclusionTex, IN.uv_MainTex).r;
            clip(occ - 0.5);
            // Albedo comes from a texture tinted by color
            fixed4 c = tex2D (_MainTex, IN.uv_MainTex) * _Color;
            // float2 uv = IN.worldpos

            fixed4 waves = tex2D (_WavesTex, float2(IN.uv_WavesTex.x, IN.uv_WavesTex.y + _Speed *_Time.x + 0.1 * sin(IN.uv_MainTex.x * 10 + _Time.z)));
            o.Albedo = saturate(c.rgb - waves.rgb * waves.a * _WavesColor.a) + waves.rgb * _WavesColor * waves.a * _WavesColor.a;
            // Metallic and smoothness come from slider variables
            o.Metallic = _Metallic;
            o.Smoothness = _Glossiness;
            o.Alpha = c.a * occ;
        }
        ENDCG
    }
    FallBack "Diffuse"
}
