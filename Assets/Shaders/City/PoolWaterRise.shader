Shader "Custom/PoolWaterRise"
{
    Properties
    {
        _Color ("Color", Color) = (1,1,1,1)
        _MainTex ("Albedo (RGB)", 2D) = "white" {}
        _Glossiness ("Smoothness", Range(0,1)) = 0.5
        _Metallic ("Metallic", Range(0,1)) = 0.0
        _OffsetMask ("Water Rise Offset Mask", 2D) = "white" {}
        _Offset ("Water Rise Offset", Float) = 0.0
        _WavesTex ("Waves Texture", 2D) = "black" {}
        _WavesColor ("Waves Color", Color) = (1,1,1,1)
        _Speed ("Speed", Float) = 25
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 200

        CGPROGRAM
        // Physically based Standard lighting model, and enable shadows on all light types
        #pragma surface surf Standard fullforwardshadows vertex:vert

        // Use shader model 3.0 target, to get nicer looking lighting
        #pragma target 3.0

        sampler2D _MainTex;
        sampler2D _OffsetMask;
        sampler2D _WavesTex;

        struct Input
        {
            float2 uv_MainTex;
            float2 uv_WavesTex;
        };

        half _Glossiness;
        half _Metallic;
        fixed4 _Color;
        fixed4 _WavesColor;

        float _Offset;
        float _Speed;

        // Add instancing support for this shader. You need to check 'Enable Instancing' on materials that use the shader.
        // See https://docs.unity3d.com/Manual/GPUInstancing.html for more information about instancing.
        // #pragma instancing_options assumeuniformscaling
        UNITY_INSTANCING_BUFFER_START(Props)
            // put more per-instance properties here
        UNITY_INSTANCING_BUFFER_END(Props)

        void vert(inout appdata_full v)
        {
            float4 off = tex2Dlod(_OffsetMask, float4(v.texcoord.xy, 0, 0)) * _Offset;
            v.vertex.z += off;
        }

        void surf (Input IN, inout SurfaceOutputStandard o)
        {
            // Albedo comes from a texture tinted by color
            fixed4 c = tex2D (_MainTex, IN.uv_MainTex) * _Color;
            fixed4 waves = tex2D (_WavesTex, float2(IN.uv_WavesTex.x - _Speed *_Time.x, IN.uv_WavesTex.y + 0.1 * sin(IN.uv_MainTex.y * 10 + _Time.z)));
            o.Albedo = saturate(c.rgb - waves.rgb * waves.a * _WavesColor.a) + waves.rgb * _WavesColor * waves.a * _WavesColor.a;
            // Metallic and smoothness come from slider variables
            o.Metallic = _Metallic;
            o.Smoothness = _Glossiness;
            o.Alpha = c.a;
        }
        ENDCG
    }
    FallBack "Diffuse"
}
