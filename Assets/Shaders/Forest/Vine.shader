Shader "Custom/Vine"
{
    Properties
    {
        _Color ("Color", Color) = (1,1,1,1)
        _MainTex ("Gradient Tex", 2D) = "white" {}
        _Glossiness ("Smoothness", Range(0,1)) = 0.5
        _Metallic ("Metallic", Range(0,1)) = 0.0

        _Distance ("Vine distance", Range(-1,1)) = 0
        _MaxThick ("Max thickness", Float) = 0
        _OffThick ("Thickness offset to zero", Float) = 0
        _Clip ("Clip cutoff", Float) = 0.01
    }
    SubShader
    {
        // Tags { "RenderType"="Opaque"  }
        Tags { "RenderType"="Opaque" "Queue" = "Transparent" }

        LOD 200

        CGPROGRAM
        // Physically based Standard lighting model, and enable shadows on all light types
        #pragma surface surf Standard fullforwardshadows vertex:vert

        // Use shader model 3.0 target, to get nicer looking lighting
        #pragma target 3.0

        sampler2D _MainTex;

        struct Input
        {
            float2 uv_MainTex;
        };

        half _Glossiness;
        half _Metallic;
        fixed4 _Color;
        float _Distance;
        float _MaxThick;
        float _OffThick;
        float _Clip;

        // Add instancing support for this shader. You need to check 'Enable Instancing' on materials that use the shader.
        // See https://docs.unity3d.com/Manual/GPUInstancing.html for more information about instancing.
        // #pragma instancing_options assumeuniformscaling
        UNITY_INSTANCING_BUFFER_START(Props)
            // put more per-instance properties here
        UNITY_INSTANCING_BUFFER_END(Props)

        void vert(inout appdata_full v)
        {
            half g = tex2Dlod(_MainTex, float4(v.texcoord.x, v.texcoord.y, 0, 0)).r;
            v.vertex.xyz += v.normal * lerp(_OffThick, _MaxThick, saturate(1 - g - _Distance));
        }

        void surf (Input IN, inout SurfaceOutputStandard o)
        {
            // Albedo comes from a texture tinted by color
            half g = tex2D(_MainTex, IN.uv_MainTex).r;
            clip(1 - g - _Distance - _Clip);
            o.Albedo = _Color.rgb;
            // Metallic and smoothness come from slider variables
            o.Metallic = _Metallic;
            o.Smoothness = _Glossiness;
            o.Alpha = 1;
        }
        ENDCG
    }
    FallBack "Diffuse"
}
