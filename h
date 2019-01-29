[33mcommit 3be10158da18ab85757ec5e99bcbe7b55164a422[m[33m ([m[1;36mHEAD -> [m[1;32mmaster[m[33m)[m
Author: RoboticWater <jakebritti@gmail.com>
Date:   Sun Jan 27 21:57:40 2019 -0500

    refactored human, broke core gameloop to make it better eventually, level transitions

[1mdiff --git a/Assets/Editor/HumanEditor.cs b/Assets/Editor/GuardEditor.cs[m
[1msimilarity index 89%[m
[1mrename from Assets/Editor/HumanEditor.cs[m
[1mrename to Assets/Editor/GuardEditor.cs[m
[1mindex 7e4cb50..f6c5c13 100644[m
[1m--- a/Assets/Editor/HumanEditor.cs[m
[1m+++ b/Assets/Editor/GuardEditor.cs[m
[36m@@ -1,9 +1,9 @@[m
 using UnityEngine;[m
 using UnityEditor;[m
 [m
[31m-[CustomEditor(typeof(Human))][m
[32m+[m[32m[CustomEditor(typeof(Guard))][m
 [CanEditMultipleObjects][m
[31m-public class HumanEditor : Editor[m
[32m+[m[32mpublic class GuardEditor : Editor[m
 {[m
 	SerializedProperty minWaitTime;[m
 	SerializedProperty maxWaitTime;[m
[36m@@ -97,11 +97,11 @@[m [mpublic class HumanEditor : Editor[m
 	private void OnSceneViewGUI(SceneView sv)[m
 	{[m
 		Handles.color = new Color(1, 0, 0, 1);[m
[31m-		Human hu = target as Human;[m
[31m-		Handles.DrawWireDisc(hu.searchPosition, hu.transform.up, searchRadius.floatValue);[m
[32m+[m		[32mGuard guard = target as Guard;[m
[32m+[m		[32mHandles.DrawWireDisc(guard.searchPosition, guard.transform.up, searchRadius.floatValue);[m
 		Handles.color = new Color(0, 1, 0, 0.2f);[m
[31m-		Handles.DrawSolidArc(hu.transform.position, hu.transform.up, hu.transform.forward, viewAngle.floatValue, viewDistance.floatValue);[m
[31m-		Handles.DrawSolidArc(hu.transform.position, hu.transform.up, hu.transform.forward, -viewAngle.floatValue, viewDistance.floatValue);[m
[32m+[m		[32mHandles.DrawSolidArc(guard.transform.position, guard.transform.up, guard.transform.forward, viewAngle.floatValue, viewDistance.floatValue);[m
[32m+[m		[32mHandles.DrawSolidArc(guard.transform.position, guard.transform.up, guard.transform.forward, -viewAngle.floatValue, viewDistance.floatValue);[m
 	}[m
 [m
 	private void MinMax(string label, SerializedProperty min, SerializedProperty max)[m
[1mdiff --git a/Assets/Editor/HumanEditor.cs.meta b/Assets/Editor/GuardEditor.cs.meta[m
[1msimilarity index 83%[m
[1mrename from Assets/Editor/HumanEditor.cs.meta[m
[1mrename to Assets/Editor/GuardEditor.cs.meta[m
[1mindex 0342e01..d31665a 100644[m
[1m--- a/Assets/Editor/HumanEditor.cs.meta[m
[1m+++ b/Assets/Editor/GuardEditor.cs.meta[m
[36m@@ -1,5 +1,5 @@[m
 fileFormatVersion: 2[m
[31m-guid: 6bfd1c14be9314cf59c97ac6e85f1cb2[m
[32m+[m[32mguid: b932d550ae516294aa72d7a4e85e5946[m
 MonoImporter:[m
   externalObjects: {}[m
   serializedVersion: 2[m
[1mdiff --git a/Assets/Prefabs/Player.prefab b/Assets/Prefabs/Player.prefab[m
[1mnew file mode 100644[m
[1mindex 0000000..27880d0[m
[1m--- /dev/null[m
[1m+++ b/Assets/Prefabs/Player.prefab[m
[36m@@ -0,0 +1,1055 @@[m
[32m+[m[32m%YAML 1.1[m
[32m+[m[32m%TAG !u! tag:unity3d.com,2011:[m
[32m+[m[32m--- !u!1 &191660435[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 191660434}[m
[32m+[m[32m  - component: {fileID: 2394568271403543367}[m
[32m+[m[32m  - component: {fileID: 8674479352748739781}[m
[32m+[m[32m  - component: {fileID: 7563236940125432422}[m
[32m+[m[32m  - component: {fileID: 1682084038602996238}[m
[32m+[m[32m  - component: {fileID: 191660436}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Player[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &191660434[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 191660435}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: -8.560701, y: 0.03, z: -6.445184}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 4285382750410468155}[m
[32m+[m[32m  - {fileID: 2007200795}[m
[32m+[m[32m  m_Father: {fileID: 0}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!143 &2394568271403543367[m
[32m+[m[32mCharacterController:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 191660435}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Height: 1.8[m
[32m+[m[32m  m_Radius: 0.5[m
[32m+[m[32m  m_SlopeLimit: 45[m
[32m+[m[32m  m_StepOffset: 0.3[m
[32m+[m[32m  m_SkinWidth: 0.08[m
[32m+[m[32m  m_MinMoveDistance: 0[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!114 &8674479352748739781[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 191660435}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: 05ec5cf00ca181d45a42ba1870e148c3, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  m_IsWalking: 0[m
[32m+[m[32m  m_WalkSpeed: 5[m
[32m+[m[32m  m_RunSpeed: 10[m
[32m+[m[32m  m_RunstepLenghten: 0.7[m
[32m+[m[32m  m_JumpSpeed: 10[m
[32m+[m[32m  m_StickToGroundForce: 10[m
[32m+[m[32m  m_GravityMultiplier: 2[m
[32m+[m[32m  m_MouseLook:[m
[32m+[m[32m    XSensitivity: 2[m
[32m+[m[32m    YSensitivity: 2[m
[32m+[m[32m    clampVerticalRotation: 1[m
[32m+[m[32m    MinimumX: -90[m
[32m+[m[32m    MaximumX: 90[m
[32m+[m[32m    smooth: 0[m
[32m+[m[32m    smoothTime: 5[m
[32m+[m[32m    lockCursor: 1[m
[32m+[m[32m  m_UseFovKick: 1[m
[32m+[m[32m  m_FovKick:[m
[32m+[m[32m    Camera: {fileID: 0}[m
[32m+[m[32m    originalFov: 0[m
[32m+[m[32m    FOVIncrease: 3[m
[32m+[m[32m    TimeToIncrease: 1[m
[32m+[m[32m    TimeToDecrease: 1[m
[32m+[m[32m    IncreaseCurve:[m
[32m+[m[32m      serializedVersion: 2[m
[32m+[m[32m      m_Curve:[m
[32m+[m[32m      - serializedVersion: 3[m
[32m+[m[32m        time: 0[m
[32m+[m[32m        value: 0[m
[32m+[m[32m        inSlope: 0[m
[32m+[m[32m        outSlope: 0[m
[32m+[m[32m        tangentMode: 0[m
[32m+[m[32m        weightedMode: 0[m
[32m+[m[32m        inWeight: 0.33333334[m
[32m+[m[32m        outWeight: 0.33333334[m
[32m+[m[32m      - serializedVersion: 3[m
[32m+[m[32m        time: 1[m
[32m+[m[32m        value: 1[m
[32m+[m[32m        inSlope: 2[m
[32m+[m[32m        outSlope: 2[m
[32m+[m[32m        tangentMode: 0[m
[32m+[m[32m        weightedMode: 0[m
[32m+[m[32m        inWeight: 0.33333334[m
[32m+[m[32m        outWeight: 0.33333334[m
[32m+[m[32m      m_PreInfinity: 2[m
[32m+[m[32m      m_PostInfinity: 2[m
[32m+[m[32m      m_RotationOrder: 4[m
[32m+[m[32m  m_UseHeadBob: 1[m
[32m+[m[32m  m_HeadBob:[m
[32m+[m[32m    HorizontalBobRange: 0.1[m
[32m+[m[32m    VerticalBobRange: 0.1[m
[32m+[m[32m    Bobcurve:[m
[32m+[m[32m      serializedVersion: 2[m
[32m+[m[32m      m_Curve:[m
[32m+[m[32m      - serializedVersion: 3[m
[32m+[m[32m        time: 0[m
[32m+[m[32m        value: 0[m
[32m+[m[32m        inSlope: 0[m
[32m+[m[32m        outSlope: 0[m
[32m+[m[32m        tangentMode: 0[m
[32m+[m[32m        weightedMode: 0[m
[32m+[m[32m        inWeight: 0.33333334[m
[32m+[m[32m        outWeight: 0.33333334[m
[32m+[m[32m      - serializedVersion: 3[m
[32m+[m[32m        time: 0.5[m
[32m+[m[32m        value: 1[m
[32m+[m[32m        inSlope: 0[m
[32m+[m[32m        outSlope: 0[m
[32m+[m[32m        tangentMode: 0[m
[32m+[m[32m        weightedMode: 0[m
[32m+[m[32m        inWeight: 0.33333334[m
[32m+[m[32m        outWeight: 0.33333334[m
[32m+[m[32m      - serializedVersion: 3[m
[32m+[m[32m        time: 1[m
[32m+[m[32m        value: 0[m
[32m+[m[32m        inSlope: 0[m
[32m+[m[32m        outSlope: 0[m
[32m+[m[32m        tangentMode: 0[m
[32m+[m[32m        weightedMode: 0[m
[32m+[m[32m        inWeight: 0.33333334[m
[32m+[m[32m        outWeight: 0.33333334[m
[32m+[m[32m      - serializedVersion: 3[m
[32m+[m[32m        time: 1.5[m
[32m+[m[32m        value: -1[m
[32m+[m[32m        inSlope: 0[m
[32m+[m[32m        outSlope: 0[m
[32m+[m[32m        tangentMode: 0[m
[32m+[m[32m        weightedMode: 0[m
[32m+[m[32m        inWeight: 0.33333334[m
[32m+[m[32m        outWeight: 0.33333334[m
[32m+[m[32m      - serializedVersion: 3[m
[32m+[m[32m        time: 2[m
[32m+[m[32m        value: 0[m
[32m+[m[32m        inSlope: 0[m
[32m+[m[32m        outSlope: 0[m
[32m+[m[32m        tangentMode: 0[m
[32m+[m[32m        weightedMode: 0[m
[32m+[m[32m        inWeight: 0.33333334[m
[32m+[m[32m        outWeight: 0.33333334[m
[32m+[m[32m      m_PreInfinity: 2[m
[32m+[m[32m      m_PostInfinity: 2[m
[32m+[m[32m      m_RotationOrder: 4[m
[32m+[m[32m    VerticaltoHorizontalRatio: 2[m
[32m+[m[32m  m_JumpBob:[m
[32m+[m[32m    BobDuration: 0.2[m
[32m+[m[32m    BobAmount: 0.1[m
[32m+[m[32m  m_StepInterval: 5[m
[32m+[m[32m  m_FootstepSounds:[m
[32m+[m[32m  - {fileID: 8300000, guid: 42e65e088b3f4374e851b8dbd38f3df9, type: 3}[m
[32m+[m[32m  - {fileID: 8300000, guid: 8bc94ec6ed537e743b481638bdcd503d, type: 3}[m
[32m+[m[32m  m_JumpSound: {fileID: 8300000, guid: 5897aeed9b676024fbb8c694b421a861, type: 3}[m
[32m+[m[32m  m_LandSound: {fileID: 8300000, guid: 3b09d59f4499d45428baa7a21e954296, type: 3}[m
[32m+[m[32m  canLook: 1[m
[32m+[m[32m--- !u!54 &7563236940125432422[m
[32m+[m[32mRigidbody:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 191660435}[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Mass: 1[m
[32m+[m[32m  m_Drag: 0[m
[32m+[m[32m  m_AngularDrag: 0.05[m
[32m+[m[32m  m_UseGravity: 1[m
[32m+[m[32m  m_IsKinematic: 1[m
[32m+[m[32m  m_Interpolate: 0[m
[32m+[m[32m  m_Constraints: 0[m
[32m+[m[32m  m_CollisionDetection: 0[m
[32m+[m[32m--- !u!82 &1682084038602996238[m
[32m+[m[32mAudioSource:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 191660435}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 4[m
[32m+[m[32m  OutputAudioMixerGroup: {fileID: 0}[m
[32m+[m[32m  m_audioClip: {fileID: 0}[m
[32m+[m[32m  m_PlayOnAwake: 1[m
[32m+[m[32m  m_Volume: 0.1[m
[32m+[m[32m  m_Pitch: 1[m
[32m+[m[32m  Loop: 0[m
[32m+[m[32m  Mute: 0[m
[32m+[m[32m  Spatialize: 0[m
[32m+[m[32m  SpatializePostEffects: 0[m
[32m+[m[32m  Priority: 128[m
[32m+[m[32m  DopplerLevel: 1[m
[32m+[m[32m  MinDistance: 1[m
[32m+[m[32m  MaxDistance: 500[m
[32m+[m[32m  Pan2D: 0[m
[32m+[m[32m  rolloffMode: 0[m
[32m+[m[32m  BypassEffects: 0[m
[32m+[m[32m  BypassListenerEffects: 0[m
[32m+[m[32m  BypassReverbZones: 0[m
[32m+[m[32m  rolloffCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 1[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m  panLevelCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 0[m
[32m+[m[32m  spreadCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m  reverbZoneMixCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 0[m
[32m+[m[32m--- !u!114 &191660436[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 191660435}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: 5a6c2ac7036cb471a9431d8e60177b9b, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  glitch: {fileID: 683945354}[m
[32m+[m[32m  health: 100[m
[32m+[m[32m  regen: 7[m
[32m+[m[32m  regenDelay: 3[m
[32m+[m[32m  regenTimer: 0[m
[32m+[m[32m  fade: {fileID: 0}[m
[32m+[m[32m  fadeTime: 0[m
[32m+[m[32m  nextLevel:[m[41m [m
[32m+[m[32m--- !u!1 &683945352[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 4285382750410468155}[m
[32m+[m[32m  - component: {fileID: 683945353}[m
[32m+[m[32m  - component: {fileID: 4361266720098586669}[m
[32m+[m[32m  - component: {fileID: 7553910962877619053}[m
[32m+[m[32m  - component: {fileID: 1842100818029722376}[m
[32m+[m[32m  - component: {fileID: 7821342484998891458}[m
[32m+[m[32m  - component: {fileID: 2281808240385602055}[m
[32m+[m[32m  - component: {fileID: 8566911541392328705}[m
[32m+[m[32m  - component: {fileID: 683945354}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: FirstPersonCharacter[m
[32m+[m[32m  m_TagString: MainCamera[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &4285382750410468155[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 683945352}[m
[32m+[m[32m  m_LocalRotation: {x: 0, y: 0, z: 0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0.8, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 191660434}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!20 &683945353[m
[32m+[m[32mCamera:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 683945352}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_ClearFlags: 1[m
[32m+[m[32m  m_BackGroundColor: {r: 0.19215687, g: 0.3019608, b: 0.4745098, a: 0.019607844}[m
[32m+[m[32m  m_projectionMatrixMode: 1[m
[32m+[m[32m  m_SensorSize: {x: 36, y: 24}[m
[32m+[m[32m  m_LensShift: {x: 0, y: 0}[m
[32m+[m[32m  m_GateFitMode: 2[m
[32m+[m[32m  m_FocalLength: 50[m
[32m+[m[32m  m_NormalizedViewPortRect:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    x: 0[m
[32m+[m[32m    y: 0[m
[32m+[m[32m    width: 1[m
[32m+[m[32m    height: 1[m
[32m+[m[32m  near clip plane: 0.3[m
[32m+[m[32m  far clip plane: 1000[m
[32m+[m[32m  field of view: 60[m
[32m+[m[32m  orthographic: 0[m
[32m+[m[32m  orthographic size: 5[m
[32m+[m[32m  m_Depth: 0[m
[32m+[m[32m  m_CullingMask:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Bits: 4294967295[m
[32m+[m[32m  m_RenderingPath: -1[m
[32m+[m[32m  m_TargetTexture: {fileID: 0}[m
[32m+[m[32m  m_TargetDisplay: 0[m
[32m+[m[32m  m_TargetEye: 3[m
[32m+[m[32m  m_HDR: 0[m
[32m+[m[32m  m_AllowMSAA: 1[m
[32m+[m[32m  m_AllowDynamicResolution: 0[m
[32m+[m[32m  m_ForceIntoRT: 1[m
[32m+[m[32m  m_OcclusionCulling: 1[m
[32m+[m[32m  m_StereoConvergence: 10[m
[32m+[m[32m  m_StereoSeparation: 0.022[m
[32m+[m[32m--- !u!81 &4361266720098586669[m
[32m+[m[32mAudioListener:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 683945352}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m--- !u!124 &7553910962877619053[m
[32m+[m[32mBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 683945352}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m--- !u!114 &1842100818029722376[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 683945352}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: 948f4100a11a5c24981795d21301da5c, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  volumeTrigger: {fileID: 0}[m
[32m+[m[32m  volumeLayer:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Bits: 4294967295[m
[32m+[m[32m  stopNaNPropagation: 1[m
[32m+[m[32m  finalBlitToCameraTarget: 1[m
[32m+[m[32m  antialiasingMode: 0[m
[32m+[m[32m  temporalAntialiasing:[m
[32m+[m[32m    jitterSpread: 0.75[m
[32m+[m[32m    sharpness: 0.25[m
[32m+[m[32m    stationaryBlending: 0.95[m
[32m+[m[32m    motionBlending: 0.85[m
[32m+[m[32m  subpixelMorphologicalAntialiasing:[m
[32m+[m[32m    quality: 2[m
[32m+[m[32m  fastApproximateAntialiasing:[m
[32m+[m[32m    fastMode: 0[m
[32m+[m[32m    keepAlpha: 0[m
[32m+[m[32m  fog:[m
[32m+[m[32m    enabled: 1[m
[32m+[m[32m    excludeSkybox: 1[m
[32m+[m[32m  debugLayer:[m
[32m+[m[32m    lightMeter:[m
[32m+[m[32m      width: 512[m
[32m+[m[32m      height: 256[m
[32m+[m[32m      showCurves: 1[m
[32m+[m[32m    histogram:[m
[32m+[m[32m      width: 512[m
[32m+[m[32m      height: 256[m
[32m+[m[32m      channel: 3[m
[32m+[m[32m    waveform:[m
[32m+[m[32m      exposure: 0.12[m
[32m+[m[32m      height: 256[m
[32m+[m[32m    vectorscope:[m
[32m+[m[32m      size: 256[m
[32m+[m[32m      exposure: 0.12[m
[32m+[m[32m    overlaySettings:[m
[32m+[m[32m      linearDepth: 0[m
[32m+[m[32m      motionColorIntensity: 4[m
[32m+[m[32m      motionGridSize: 64[m
[32m+[m[32m      colorBlindnessType: 0[m
[32m+[m[32m      colorBlindnessStrength: 1[m
[32m+[m[32m  m_Resources: {fileID: 11400000, guid: d82512f9c8e5d4a4d938b575d47f88d4, type: 2}[m
[32m+[m[32m  m_ShowToolkit: 0[m
[32m+[m[32m  m_ShowCustomSorter: 0[m
[32m+[m[32m  breakBeforeColorGrading: 0[m
[32m+[m[32m  m_BeforeTransparentBundles: [][m
[32m+[m[32m  m_BeforeStackBundles: [][m
[32m+[m[32m  m_AfterStackBundles: [][m
[32m+[m[32m--- !u!114 &7821342484998891458[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 683945352}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: ad06e60d35a297149adcc16be5979131, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  pattern: {fileID: 2800000, guid: 3fe921721e92c8d45ad530c33811eb6f, type: 3}[m
[32m+[m[32m  threshold: 1[m
[32m+[m[32m  strength: 0.88[m
[32m+[m[32m--- !u!114 &2281808240385602055[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 683945352}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: ba54bbb8d59fc1d48a351f7d6a559f82, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  horizontalResolution: 160[m
[32m+[m[32m  verticalResolution: 144[m
[32m+[m[32m--- !u!114 &8566911541392328705[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 683945352}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: 64f9144a767f6d842a42451779fca81c, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  colors:[m
[32m+[m[32m  - {r: 0, g: 0, b: 0, a: 0}[m
[32m+[m[32m  - {r: 0.3490566, g: 0.3490566, b: 0.3490566, a: 0}[m
[32m+[m[32m  - {r: 0.503, g: 0.503, b: 0.503, a: 0}[m
[32m+[m[32m  - {r: 0.6603774, g: 0.6603774, b: 0.6603774, a: 0}[m
[32m+[m[32m  - {r: 0.8301887, g: 0.8301887, b: 0.8301887, a: 0}[m
[32m+[m[32m  - {r: 0.385, g: 0.385, b: 0.385, a: 0}[m
[32m+[m[32m  - {r: 0.26, g: 0.26, b: 0.26, a: 0}[m
[32m+[m[32m  - {r: 0.20754719, g: 0.20754719, b: 0.20754719, a: 0}[m
[32m+[m[32m  - {r: 0.118999995, g: 0.063, b: 0.063, a: 1}[m
[32m+[m[32m  - {r: 0.22745098, g: 0.03661961, b: 0.03661961, a: 1}[m
[32m+[m[32m  - {r: 0.3764706, g: 0.09487058, b: 0.09487058, a: 1}[m
[32m+[m[32m  - {r: 0.636, g: 0.2297428, b: 0.19588801, a: 1}[m
[32m+[m[32m  - {r: 0.057647064, g: 0.094797395, b: 0.13725491, a: 1}[m
[32m+[m[32m  - {r: 0.05644801, g: 0.14025602, b: 0.252, a: 1}[m
[32m+[m[32m  - {r: 0.12073602, g: 0.23971145, b: 0.39200002, a: 1}[m
[32m+[m[32m  - {r: 0.26040003, g: 0.41924518, b: 0.6, a: 1}[m
[32m+[m[32m  - {r: 0.12385714, g: 0.289, b: 0.07798414, a: 1}[m
[32m+[m[32m  - {r: 0.18946666, g: 0.46400002, b: 0.116000004, a: 1}[m
[32m+[m[32m  - {r: 0.22943097, g: 0.538, b: 0.12804401, a: 1}[m
[32m+[m[32m  - {r: 0.32435524, g: 0.6698113, b: 0.17377181, a: 1}[m
[32m+[m[32m  - {r: 0.147, g: 0.14207551, b: 0.078057, a: 1}[m
[32m+[m[32m  - {r: 0.259, g: 0.25168326, b: 0.08339799, a: 1}[m
[32m+[m[32m  - {r: 0.48299998, g: 0.46236518, b: 0.111572996, a: 1}[m
[32m+[m[32m  - {r: 0.67800003, g: 0.65073144, b: 0.180348, a: 1}[m
[32m+[m[32m  - {r: 0.7921569, g: 0.21641412, b: 0.21071371, a: 1}[m
[32m+[m[32m  - {r: 0.8301887, g: 0.797788, b: 0.23887502, a: 1}[m
[32m+[m[32m  - {r: 0.34897533, g: 0.8018868, b: 0.22316661, a: 1}[m
[32m+[m[32m  - {r: 0.259, g: 0.47303677, b: 0.7254902, a: 1}[m
[32m+[m[32m--- !u!114 &683945354[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 683945352}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: 9a3a070408aa941ab83ae10be1708848, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  _intensity: 0[m
[32m+[m[32m  _shader: {fileID: 4800000, guid: ba40dc630e1d9417cb9ea22586ece1e1, type: 3}[m
[32m+[m[32m--- !u!1 &1351403726[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1351403727}[m
[32m+[m[32m  - component: {fileID: 1351403728}[m
[32m+[m[32m  - component: {fileID: 1351403729}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Voice (1)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1351403727[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1351403726}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 2007200795}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!82 &1351403728[m
[32m+[m[32mAudioSource:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1351403726}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 4[m
[32m+[m[32m  OutputAudioMixerGroup: {fileID: 0}[m
[32m+[m[32m  m_audioClip: {fileID: 0}[m
[32m+[m[32m  m_PlayOnAwake: 1[m
[32m+[m[32m  m_Volume: 0.1[m
[32m+[m[32m  m_Pitch: 1[m
[32m+[m[32m  Loop: 0[m
[32m+[m[32m  Mute: 0[m
[32m+[m[32m  Spatialize: 0[m
[32m+[m[32m  SpatializePostEffects: 0[m
[32m+[m[32m  Priority: 128[m
[32m+[m[32m  DopplerLevel: 1[m
[32m+[m[32m  MinDistance: 1[m
[32m+[m[32m  MaxDistance: 500[m
[32m+[m[32m  Pan2D: 0[m
[32m+[m[32m  rolloffMode: 0[m
[32m+[m[32m  BypassEffects: 0[m
[32m+[m[32m  BypassListenerEffects: 0[m
[32m+[m[32m  BypassReverbZones: 0[m
[32m+[m[32m  rolloffCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 1[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m  panLevelCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m  spreadCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m  reverbZoneMixCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m--- !u!114 &1351403729[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1351403726}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: cb38115528397a343805dd7e97358c67, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  autoPlay: 0[m
[32m+[m[32m  masterVolume: 0[m
[32m+[m[32m  mainFrequency: 500[m
[32m+[m[32m  useSinusAudioWave: 1[m
[32m+[m[32m  sinusAudioWaveIntensity: 0.7[m
[32m+[m[32m  useSquareAudioWave: 1[m
[32m+[m[32m  squareAudioWaveIntensity: 0.3[m
[32m+[m[32m  useSawAudioWave: 0[m
[32m+[m[32m  sawAudioWaveIntensity: 0[m
[32m+[m[32m  useAmplitudeModulation: 0[m
[32m+[m[32m  amplitudeModulationOscillatorFrequency: 1[m
[32m+[m[32m  useFrequencyModulation: 1[m
[32m+[m[32m  frequencyModulationOscillatorFrequency: 6[m
[32m+[m[32m  frequencyModulationOscillatorIntensity: 1[m
[32m+[m[32m  amplitudeModulationRangeOut: 0[m
[32m+[m[32m  frequencyModulationRangeOut: 0[m
[32m+[m[32m--- !u!1 &1384269232[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1384269235}[m
[32m+[m[32m  - component: {fileID: 1384269234}[m
[32m+[m[32m  - component: {fileID: 1384269233}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Voice (2)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1384269235[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1384269232}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 2007200795}[m
[32m+[m[32m  m_RootOrder: 2[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!82 &1384269234[m
[32m+[m[32mAudioSource:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1384269232}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 4[m
[32m+[m[32m  OutputAudioMixerGroup: {fileID: 0}[m
[32m+[m[32m  m_audioClip: {fileID: 0}[m
[32m+[m[32m  m_PlayOnAwake: 1[m
[32m+[m[32m  m_Volume: 0.1[m
[32m+[m[32m  m_Pitch: 1[m
[32m+[m[32m  Loop: 0[m
[32m+[m[32m  Mute: 0[m
[32m+[m[32m  Spatialize: 0[m
[32m+[m[32m  SpatializePostEffects: 0[m
[32m+[m[32m  Priority: 128[m
[32m+[m[32m  DopplerLevel: 1[m
[32m+[m[32m  MinDistance: 1[m
[32m+[m[32m  MaxDistance: 500[m
[32m+[m[32m  Pan2D: 0[m
[32m+[m[32m  rolloffMode: 0[m
[32m+[m[32m  BypassEffects: 0[m
[32m+[m[32m  BypassListenerEffects: 0[m
[32m+[m[32m  BypassReverbZones: 0[m
[32m+[m[32m  rolloffCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 1[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m  panLevelCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m  spreadCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m  reverbZoneMixCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m--- !u!114 &1384269233[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1384269232}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: cb38115528397a343805dd7e97358c67, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  autoPlay: 0[m
[32m+[m[32m  masterVolume: 0[m
[32m+[m[32m  mainFrequency: 500[m
[32m+[m[32m  useSinusAudioWave: 1[m
[32m+[m[32m  sinusAudioWaveIntensity: 0.7[m
[32m+[m[32m  useSquareAudioWave: 0[m
[32m+[m[32m  squareAudioWaveIntensity: 0[m
[32m+[m[32m  useSawAudioWave: 1[m
[32m+[m[32m  sawAudioWaveIntensity: 0.3[m
[32m+[m[32m  useAmplitudeModulation: 0[m
[32m+[m[32m  amplitudeModulationOscillatorFrequency: 1[m
[32m+[m[32m  useFrequencyModulation: 1[m
[32m+[m[32m  frequencyModulationOscillatorFrequency: 6[m
[32m+[m[32m  frequencyModulationOscillatorIntensity: 1[m
[32m+[m[32m  amplitudeModulationRangeOut: 0[m
[32m+[m[32m  frequencyModulationRangeOut: 0[m
[32m+[m[32m--- !u!1 &1489212691[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1489212694}[m
[32m+[m[32m  - component: {fileID: 1489212693}[m
[32m+[m[32m  - component: {fileID: 1489212692}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Voice[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1489212694[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1489212691}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 2007200795}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!82 &1489212693[m
[32m+[m[32mAudioSource:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1489212691}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 4[m
[32m+[m[32m  OutputAudioMixerGroup: {fileID: 0}[m
[32m+[m[32m  m_audioClip: {fileID: 0}[m
[32m+[m[32m  m_PlayOnAwake: 1[m
[32m+[m[32m  m_Volume: 0.1[m
[32m+[m[32m  m_Pitch: 1[m
[32m+[m[32m  Loop: 0[m
[32m+[m[32m  Mute: 0[m
[32m+[m[32m  Spatialize: 0[m
[32m+[m[32m  SpatializePostEffects: 0[m
[32m+[m[32m  Priority: 128[m
[32m+[m[32m  DopplerLevel: 1[m
[32m+[m[32m  MinDistance: 1[m
[32m+[m[32m  MaxDistance: 500[m
[32m+[m[32m  Pan2D: 0[m
[32m+[m[32m  rolloffMode: 0[m
[32m+[m[32m  BypassEffects: 0[m
[32m+[m[32m  BypassListenerEffects: 0[m
[32m+[m[32m  BypassReverbZones: 0[m
[32m+[m[32m  rolloffCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 1[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m  panLevelCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m  spreadCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m  reverbZoneMixCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m--- !u!114 &1489212692[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1489212691}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: cb38115528397a343805dd7e97358c67, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  autoPlay: 0[m
[32m+[m[32m  masterVolume: 0[m
[32m+[m[32m  mainFrequency: 500[m
[32m+[m[32m  useSinusAudioWave: 1[m
[32m+[m[32m  sinusAudioWaveIntensity: 1[m
[32m+[m[32m  useSquareAudioWave: 0[m
[32m+[m[32m  squareAudioWaveIntensity: 0[m
[32m+[m[32m  useSawAudioWave: 0[m
[32m+[m[32m  sawAudioWaveIntensity: 0[m
[32m+[m[32m  useAmplitudeModulation: 0[m
[32m+[m[32m  amplitudeModulationOscillatorFrequency: 1[m
[32m+[m[32m  useFrequencyModulation: 1[m
[32m+[m[32m  frequencyModulationOscillatorFrequency: 6[m
[32m+[m[32m  frequencyModulationOscillatorIntensity: 1[m
[32m+[m[32m  amplitudeModulationRangeOut: 0[m
[32m+[m[32m  frequencyModulationRangeOut: 0[m
[32m+[m[32m--- !u!1 &2007200794[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 2007200795}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Voices[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &2007200795[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 2007200794}[m
[32m+[m[32m  m_LocalRotation: {x: 0, y: 0, z: 0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 1489212694}[m
[32m+[m[32m  - {fileID: 1351403727}[m
[32m+[m[32m  - {fileID: 1384269235}[m
[32m+[m[32m  m_Father: {fileID: 191660434}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[1mdiff --git a/Assets/Prefabs/Player.prefab.meta b/Assets/Prefabs/Player.prefab.meta[m
[1mnew file mode 100644[m
[1mindex 0000000..f272cd4[m
[1m--- /dev/null[m
[1m+++ b/Assets/Prefabs/Player.prefab.meta[m
[36m@@ -0,0 +1,7 @@[m
[32m+[m[32mfileFormatVersion: 2[m
[32m+[m[32mguid: 74d6c2fd5f712d44e8342e6b94738c12[m
[32m+[m[32mPrefabImporter:[m
[32m+[m[32m  externalObjects: {}[m
[32m+[m[32m  userData:[m[41m [m
[32m+[m[32m  assetBundleName:[m[41m [m
[32m+[m[32m  assetBundleVariant:[m[41m [m
[1mdiff --git a/Assets/Scenes/Forest.unity b/Assets/Scenes/Forest.unity[m
[1mindex 537ff82..fc0172f 100644[m
[1m--- a/Assets/Scenes/Forest.unity[m
[1m+++ b/Assets/Scenes/Forest.unity[m
[36m@@ -145,7 +145,7 @@[m [mTransform:[m
   - {fileID: 645119126}[m
   - {fileID: 191660434}[m
   m_Father: {fileID: 0}[m
[31m-  m_RootOrder: 9[m
[32m+[m[32m  m_RootOrder: 8[m
   m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
 --- !u!1001 &8932031[m
 PrefabInstance:[m
[36m@@ -1915,75 +1915,6 @@[m [mTransform:[m
     type: 3}[m
   m_PrefabInstance: {fileID: 111320974}[m
   m_PrefabAsset: {fileID: 0}[m
[31m---- !u!1001 &116021703[m
[31m-PrefabInstance:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  serializedVersion: 2[m
[31m-  m_Modification:[m
[31m-    m_TransformParent: {fileID: 223386903}[m
[31m-    m_Modifications:[m
[31m-    - target: {fileID: 100000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_Name[m
[31m-      value: Ivy (4)[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalPosition.x[m
[31m-      value: -11.06[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalPosition.y[m
[31m-      value: 0.97[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalPosition.z[m
[31m-      value: 10.35[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.x[m
[31m-      value: -0.0000021979208[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.y[m
[31m-      value: -0.7071079[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.z[m
[31m-      value: 0.70710576[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.w[m
[31m-      value: 0.00000011921574[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_RootOrder[m
[31m-      value: 4[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalEulerAnglesHint.x[m
[31m-      value: -270[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalEulerAnglesHint.y[m
[31m-      value: 0[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalEulerAnglesHint.z[m
[31m-      value: -179.99998[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalScale.x[m
[31m-      value: 1.7616019[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalScale.y[m
[31m-      value: 1.6536406[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalScale.z[m
[31m-      value: -2.432771[m
[31m-      objectReference: {fileID: 0}[m
[31m-    m_RemovedComponents: [][m
[31m-  m_SourcePrefab: {fileID: 100100000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
 --- !u!1001 &116212019[m
 PrefabInstance:[m
   m_ObjectHideFlags: 0[m
[36m@@ -2655,101 +2586,78 @@[m [mPrefabInstance:[m
   m_Modification:[m
     m_TransformParent: {fileID: 518009}[m
     m_Modifications:[m
[31m-    - target: {fileID: 100000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[32m+[m[32m    - target: {fileID: 191660435, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
       propertyPath: m_Name[m
       value: Player[m
       objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
       propertyPath: m_LocalPosition.x[m
       value: -8.560701[m
       objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
       propertyPath: m_LocalPosition.y[m
       value: 0.03[m
       objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
       propertyPath: m_LocalPosition.z[m
       value: -6.445184[m
       objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
       propertyPath: m_LocalRotation.x[m
       value: -0[m
       objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
       propertyPath: m_LocalRotation.y[m
       value: -0[m
       objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
       propertyPath: m_LocalRotation.z[m
       value: -0[m
       objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
       propertyPath: m_LocalRotation.w[m
       value: 1[m
       objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
       propertyPath: m_RootOrder[m
       value: 3[m
       objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
       propertyPath: m_LocalEulerAnglesHint.x[m
       value: 0[m
       objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
       propertyPath: m_LocalEulerAnglesHint.y[m
       value: 0[m
       objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
       propertyPath: m_LocalEulerAnglesHint.z[m
       value: 0[m
       objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 8200000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_Volume[m
[31m-      value: 0.1[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 11400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: canLook[m
[31m-      value: 1[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 1958383183347616696, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: m_Enabled[m
[31m-      value: 1[m
[31m-      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660436, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: fade[m
[32m+[m[32m      value:[m[41m [m
[32m+[m[32m      objectReference: {fileID: 118565761}[m
     m_RemovedComponents: [][m
[31m-  m_SourcePrefab: {fileID: 100100000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[32m+[m[32m  m_SourcePrefab: {fileID: 100100000, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
 --- !u!4 &191660434 stripped[m
 Transform:[m
[31m-  m_CorrespondingSourceObject: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12,[m
     type: 3}[m
   m_PrefabInstance: {fileID: 191660433}[m
   m_PrefabAsset: {fileID: 0}[m
[31m---- !u!1 &191660435 stripped[m
[31m-GameObject:[m
[31m-  m_CorrespondingSourceObject: {fileID: 100000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[32m+[m[32m--- !u!114 &191660436 stripped[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 191660436, guid: 74d6c2fd5f712d44e8342e6b94738c12,[m
     type: 3}[m
   m_PrefabInstance: {fileID: 191660433}[m
   m_PrefabAsset: {fileID: 0}[m
[31m---- !u!114 &191660436[m
[31m-MonoBehaviour:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
[31m-  m_GameObject: {fileID: 191660435}[m
[32m+[m[32m  m_GameObject: {fileID: 0}[m
   m_Enabled: 1[m
   m_EditorHideFlags: 0[m
   m_Script: {fileID: 11500000, guid: 5a6c2ac7036cb471a9431d8e60177b9b, type: 3}[m
   m_Name: [m
   m_EditorClassIdentifier: [m
[31m-  glitch: {fileID: 683945354}[m
[31m-  health: 100[m
[31m-  regen: 7[m
[31m-  regenDelay: 3[m
[31m-  regenTimer: 0[m
[31m-  fade: {fileID: 118565761}[m
[31m-  fadeTime: 0[m
[31m-  nextLevel: [m
 --- !u!1 &195799969[m
 GameObject:[m
   m_ObjectHideFlags: 0[m
[36m@@ -2814,7 +2722,7 @@[m [mTransform:[m
   m_LocalScale: {x: 1, y: 1, z: 1}[m
   m_Children: [][m
   m_Father: {fileID: 0}[m
[31m-  m_RootOrder: 5[m
[32m+[m[32m  m_RootOrder: 4[m
   m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
 --- !u!1001 &200252933[m
 PrefabInstance:[m
[36m@@ -3227,9 +3135,6 @@[m [mTransform:[m
   m_Children:[m
   - {fileID: 1968055214}[m
   - {fileID: 1284139984}[m
[31m-  - {fileID: 2109163166}[m
[31m-  - {fileID: 611777864}[m
[31m-  - {fileID: 598987249}[m
   - {fileID: 1554008800}[m
   - {fileID: 1502974871}[m
   - {fileID: 563944440}[m
[36m@@ -3268,7 +3173,7 @@[m [mTransform:[m
   m_Children:[m
   - {fileID: 1607779497}[m
   m_Father: {fileID: 0}[m
[31m-  m_RootOrder: 8[m
[32m+[m[32m  m_RootOrder: 7[m
   m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
 --- !u!1001 &245569265[m
 PrefabInstance:[m
[36m@@ -4965,7 +4870,7 @@[m [mTransform:[m
   m_LocalScale: {x: 4.7760997, y: 9.18969, z: 4.7760997}[m
   m_Children: [][m
   m_Father: {fileID: 223386903}[m
[31m-  m_RootOrder: 9[m
[32m+[m[32m  m_RootOrder: 6[m
   m_LocalEulerAnglesHint: {x: 0, y: -90.00001, z: 60.000004}[m
 --- !u!65 &453242636[m
 BoxCollider:[m
[36m@@ -5025,75 +4930,6 @@[m [mMeshFilter:[m
   m_PrefabAsset: {fileID: 0}[m
   m_GameObject: {fileID: 453242634}[m
   m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[31m---- !u!1001 &490355784[m
[31m-PrefabInstance:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  serializedVersion: 2[m
[31m-  m_Modification:[m
[31m-    m_TransformParent: {fileID: 223386903}[m
[31m-    m_Modifications:[m
[31m-    - target: {fileID: 100000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_Name[m
[31m-      value: Ivy (2)[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalPosition.x[m
[31m-      value: -13.64[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalPosition.y[m
[31m-      value: 1.89[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalPosition.z[m
[31m-      value: 7.11195[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.x[m
[31m-      value: -0[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.y[m
[31m-      value: -0.70710576[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.z[m
[31m-      value: -0[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.w[m
[31m-      value: 0.7071079[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_RootOrder[m
[31m-      value: 2[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalEulerAnglesHint.x[m
[31m-      value: 0[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalEulerAnglesHint.y[m
[31m-      value: -90.00001[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalEulerAnglesHint.z[m
[31m-      value: 0[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalScale.x[m
[31m-      value: 1.761601[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalScale.y[m
[31m-      value: 1.6536397[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalScale.z[m
[31m-      value: -2.432771[m
[31m-      objectReference: {fileID: 0}[m
[31m-    m_RemovedComponents: [][m
[31m-  m_SourcePrefab: {fileID: 100100000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
 --- !u!1001 &499154702[m
 PrefabInstance:[m
   m_ObjectHideFlags: 0[m
[36m@@ -5874,7 +5710,7 @@[m [mTransform:[m
   m_LocalScale: {x: 4.7761016, y: 15.058226, z: 1.8195732}[m
   m_Children: [][m
   m_Father: {fileID: 223386903}[m
[31m-  m_RootOrder: 7[m
[32m+[m[32m  m_RootOrder: 4[m
   m_LocalEulerAnglesHint: {x: 0, y: -90.00001, z: 90.00001}[m
 --- !u!65 &563944441[m
 BoxCollider:[m
[36m@@ -6274,12 +6110,6 @@[m [mTransform:[m
     type: 3}[m
   m_PrefabInstance: {fileID: 594832416}[m
   m_PrefabAsset: {fileID: 0}[m
[31m---- !u!4 &598987249 stripped[m
[31m-Transform:[m
[31m-  m_CorrespondingSourceObject: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17,[m
[31m-    type: 3}[m
[31m-  m_PrefabInstance: {fileID: 116021703}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
 --- !u!1001 &605502510[m
 PrefabInstance:[m
   m_ObjectHideFlags: 0[m
[36m@@ -6440,12 +6270,6 @@[m [mPrefabInstance:[m
       objectReference: {fileID: 2100000, guid: 1e6893fb8cb6d064bb4e7341258411b4, type: 2}[m
     m_RemovedComponents: [][m
   m_SourcePrefab: {fileID: 100100000, guid: 742b2e9bb92ed0e428b7ef5ccafe7f46, type: 3}[m
[31m---- !u!4 &611777864 stripped[m
[31m-Transform:[m
[31m-  m_CorrespondingSourceObject: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17,[m
[31m-    type: 3}[m
[31m-  m_PrefabInstance: {fileID: 1451746442}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
 --- !u!1001 &617840306[m
 PrefabInstance:[m
   m_ObjectHideFlags: 0[m
[36m@@ -6635,7 +6459,7 @@[m [mTransform:[m
   m_LocalScale: {x: 1, y: 1, z: 1}[m
   m_Children: [][m
   m_Father: {fileID: 0}[m
[31m-  m_RootOrder: 4[m
[32m+[m[32m  m_RootOrder: 3[m
   m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
 --- !u!114 &626196613[m
 MonoBehaviour:[m
[36m@@ -7496,32 +7320,12 @@[m [mTransform:[m
     type: 3}[m
   m_PrefabInstance: {fileID: 680119244}[m
   m_PrefabAsset: {fileID: 0}[m
[31m---- !u!1 &683945352 stripped[m
[31m-GameObject:[m
[31m-  m_CorrespondingSourceObject: {fileID: 100002, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-    type: 3}[m
[31m-  m_PrefabInstance: {fileID: 191660433}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
 --- !u!20 &683945353 stripped[m
 Camera:[m
[31m-  m_CorrespondingSourceObject: {fileID: 2000000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 683945353, guid: 74d6c2fd5f712d44e8342e6b94738c12,[m
     type: 3}[m
   m_PrefabInstance: {fileID: 191660433}[m
   m_PrefabAsset: {fileID: 0}[m
[31m---- !u!114 &683945354[m
[31m-MonoBehaviour:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
[31m-  m_GameObject: {fileID: 683945352}[m
[31m-  m_Enabled: 1[m
[31m-  m_EditorHideFlags: 0[m
[31m-  m_Script: {fileID: 11500000, guid: 9a3a070408aa941ab83ae10be1708848, type: 3}[m
[31m-  m_Name: [m
[31m-  m_EditorClassIdentifier: [m
[31m-  _intensity: 0[m
[31m-  _shader: {fileID: 4800000, guid: ba40dc630e1d9417cb9ea22586ece1e1, type: 3}[m
 --- !u!1001 &684855018[m
 PrefabInstance:[m
   m_ObjectHideFlags: 0[m
[36m@@ -8304,7 +8108,7 @@[m [mPrefabInstance:[m
       objectReference: {fileID: 0}[m
     - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
       propertyPath: m_RootOrder[m
[31m-      value: 2[m
[32m+[m[32m      value: 1[m
       objectReference: {fileID: 0}[m
     - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
       propertyPath: m_LocalEulerAnglesHint.x[m
[36m@@ -8363,7 +8167,7 @@[m [mTransform:[m
   m_LocalScale: {x: 4.7761016, y: 9.18969, z: 2.36828}[m
   m_Children: [][m
   m_Father: {fileID: 223386903}[m
[31m-  m_RootOrder: 10[m
[32m+[m[32m  m_RootOrder: 7[m
   m_LocalEulerAnglesHint: {x: 0, y: -150, z: 180.00002}[m
 --- !u!65 &757221851[m
 BoxCollider:[m
[36m@@ -9358,7 +9162,7 @@[m [mRectTransform:[m
   - {fileID: 118565760}[m
   - {fileID: 1604026824}[m
   m_Father: {fileID: 0}[m
[31m-  m_RootOrder: 6[m
[32m+[m[32m  m_RootOrder: 5[m
   m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
   m_AnchorMin: {x: 0, y: 0}[m
   m_AnchorMax: {x: 0, y: 0}[m
[36m@@ -9540,7 +9344,7 @@[m [mTransform:[m
   - {fileID: 223386903}[m
   - {fileID: 1163596910}[m
   m_Father: {fileID: 0}[m
[31m-  m_RootOrder: 7[m
[32m+[m[32m  m_RootOrder: 6[m
   m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
 --- !u!1001 &872164585[m
 PrefabInstance:[m
[36m@@ -10785,7 +10589,7 @@[m [mTransform:[m
   m_LocalScale: {x: 1, y: 1, z: 1}[m
   m_Children: [][m
   m_Father: {fileID: 0}[m
[31m-  m_RootOrder: 3[m
[32m+[m[32m  m_RootOrder: 2[m
   m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
 --- !u!1001 &971966828[m
 PrefabInstance:[m
[36m@@ -11239,7 +11043,7 @@[m [mTransform:[m
   m_LocalScale: {x: 4.7761016, y: 15.058229, z: 1.81957}[m
   m_Children: [][m
   m_Father: {fileID: 223386903}[m
[31m-  m_RootOrder: 8[m
[32m+[m[32m  m_RootOrder: 5[m
   m_LocalEulerAnglesHint: {x: 0, y: 0, z: 90.00001}[m
 --- !u!65 &1009188300[m
 BoxCollider:[m
[36m@@ -14457,162 +14261,18 @@[m [mTransform:[m
     type: 3}[m
   m_PrefabInstance: {fileID: 1342965703}[m
   m_PrefabAsset: {fileID: 0}[m
[31m---- !u!1 &1351403726[m
[31m-GameObject:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
[31m-  serializedVersion: 6[m
[31m-  m_Component:[m
[31m-  - component: {fileID: 1351403727}[m
[31m-  - component: {fileID: 1351403728}[m
[31m-  - component: {fileID: 1351403729}[m
[31m-  m_Layer: 0[m
[31m-  m_Name: Voice (1)[m
[31m-  m_TagString: Untagged[m
[31m-  m_Icon: {fileID: 0}[m
[31m-  m_NavMeshLayer: 0[m
[31m-  m_StaticEditorFlags: 0[m
[31m-  m_IsActive: 1[m
[31m---- !u!4 &1351403727[m
[31m-Transform:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
[31m-  m_GameObject: {fileID: 1351403726}[m
[31m-  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[31m-  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[31m-  m_LocalScale: {x: 1, y: 1, z: 1}[m
[31m-  m_Children: [][m
[31m-  m_Father: {fileID: 2007200795}[m
[31m-  m_RootOrder: 1[m
[31m-  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[31m---- !u!82 &1351403728[m
[31m-AudioSource:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m--- !u!114 &1351403729 stripped[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 1351403729, guid: 74d6c2fd5f712d44e8342e6b94738c12,[m
[32m+[m[32m    type: 3}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 191660433}[m
   m_PrefabAsset: {fileID: 0}[m
[31m-  m_GameObject: {fileID: 1351403726}[m
[31m-  m_Enabled: 1[m
[31m-  serializedVersion: 4[m
[31m-  OutputAudioMixerGroup: {fileID: 0}[m
[31m-  m_audioClip: {fileID: 0}[m
[31m-  m_PlayOnAwake: 1[m
[31m-  m_Volume: 0.1[m
[31m-  m_Pitch: 1[m
[31m-  Loop: 0[m
[31m-  Mute: 0[m
[31m-  Spatialize: 0[m
[31m-  SpatializePostEffects: 0[m
[31m-  Priority: 128[m
[31m-  DopplerLevel: 1[m
[31m-  MinDistance: 1[m
[31m-  MaxDistance: 500[m
[31m-  Pan2D: 0[m
[31m-  rolloffMode: 0[m
[31m-  BypassEffects: 0[m
[31m-  BypassListenerEffects: 0[m
[31m-  BypassReverbZones: 0[m
[31m-  rolloffCustomCurve:[m
[31m-    serializedVersion: 2[m
[31m-    m_Curve:[m
[31m-    - serializedVersion: 3[m
[31m-      time: 0[m
[31m-      value: 1[m
[31m-      inSlope: 0[m
[31m-      outSlope: 0[m
[31m-      tangentMode: 0[m
[31m-      weightedMode: 0[m
[31m-      inWeight: 0.33333334[m
[31m-      outWeight: 0.33333334[m
[31m-    - serializedVersion: 3[m
[31m-      time: 1[m
[31m-      value: 0[m
[31m-      inSlope: 0[m
[31m-      outSlope: 0[m
[31m-      tangentMode: 0[m
[31m-      weightedMode: 0[m
[31m-      inWeight: 0.33333334[m
[31m-      outWeight: 0.33333334[m
[31m-    m_PreInfinity: 2[m
[31m-    m_PostInfinity: 2[m
[31m-    m_RotationOrder: 4[m
[31m-  panLevelCustomCurve:[m
[31m-    serializedVersion: 2[m
[31m-    m_Curve:[m
[31m-    - serializedVersion: 3[m
[31m-      time: 0[m
[31m-      value: 0[m
[31m-      inSlope: 0[m
[31m-      outSlope: 0[m
[31m-      tangentMode: 0[m
[31m-      weightedMode: 0[m
[31m-      inWeight: 0.33333334[m
[31m-      outWeight: 0.33333334[m
[31m-    m_PreInfinity: 2[m
[31m-    m_PostInfinity: 2[m
[31m-    m_RotationOrder: 4[m
[31m-  spreadCustomCurve:[m
[31m-    serializedVersion: 2[m
[31m-    m_Curve:[m
[31m-    - serializedVersion: 3[m
[31m-      time: 0[m
[31m-      value: 0[m
[31m-      inSlope: 0[m
[31m-      outSlope: 0[m
[31m-      tangentMode: 0[m
[31m-      weightedMode: 0[m
[31m-      inWeight: 0.33333334[m
[31m-      outWeight: 0.33333334[m
[31m-    m_PreInfinity: 2[m
[31m-    m_PostInfinity: 2[m
[31m-    m_RotationOrder: 4[m
[31m-  reverbZoneMixCustomCurve:[m
[31m-    serializedVersion: 2[m
[31m-    m_Curve:[m
[31m-    - serializedVersion: 3[m
[31m-      time: 0[m
[31m-      value: 1[m
[31m-      inSlope: 0[m
[31m-      outSlope: 0[m
[31m-      tangentMode: 0[m
[31m-      weightedMode: 0[m
[31m-      inWeight: 0.33333334[m
[31m-      outWeight: 0.33333334[m
[31m-    m_PreInfinity: 2[m
[31m-    m_PostInfinity: 2[m
[31m-    m_RotationOrder: 4[m
[31m---- !u!114 &1351403729[m
[31m-MonoBehaviour:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
[31m-  m_GameObject: {fileID: 1351403726}[m
[32m+[m[32m  m_GameObject: {fileID: 0}[m
   m_Enabled: 1[m
   m_EditorHideFlags: 0[m
   m_Script: {fileID: 11500000, guid: cb38115528397a343805dd7e97358c67, type: 3}[m
   m_Name: [m
   m_EditorClassIdentifier: [m
[31m-  autoPlay: 0[m
[31m-  masterVolume: 0[m
[31m-  mainFrequency: 500[m
[31m-  useSinusAudioWave: 1[m
[31m-  sinusAudioWaveIntensity: 0.7[m
[31m-  useSquareAudioWave: 1[m
[31m-  squareAudioWaveIntensity: 0.3[m
[31m-  useSawAudioWave: 0[m
[31m-  sawAudioWaveIntensity: 0[m
[31m-  useAmplitudeModulation: 0[m
[31m-  amplitudeModulationOscillatorFrequency: 1[m
[31m-  useFrequencyModulation: 1[m
[31m-  frequencyModulationOscillatorFrequency: 6[m
[31m-  frequencyModulationOscillatorIntensity: 1[m
[31m-  amplitudeModulationRangeOut: 0[m
[31m-  frequencyModulationRangeOut: 0[m
 --- !u!1001 &1358181888[m
 PrefabInstance:[m
   m_ObjectHideFlags: 0[m
[36m@@ -14853,162 +14513,18 @@[m [mCanvasRenderer:[m
   m_PrefabAsset: {fileID: 0}[m
   m_GameObject: {fileID: 1376020231}[m
   m_CullTransparentMesh: 0[m
[31m---- !u!1 &1384269232[m
[31m-GameObject:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
[31m-  serializedVersion: 6[m
[31m-  m_Component:[m
[31m-  - component: {fileID: 1384269235}[m
[31m-  - component: {fileID: 1384269234}[m
[31m-  - component: {fileID: 1384269233}[m
[31m-  m_Layer: 0[m
[31m-  m_Name: Voice (2)[m
[31m-  m_TagString: Untagged[m
[31m-  m_Icon: {fileID: 0}[m
[31m-  m_NavMeshLayer: 0[m
[31m-  m_StaticEditorFlags: 0[m
[31m-  m_IsActive: 1[m
[31m---- !u!114 &1384269233[m
[32m+[m[32m--- !u!114 &1384269233 stripped[m
 MonoBehaviour:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 1384269233, guid: 74d6c2fd5f712d44e8342e6b94738c12,[m
[32m+[m[32m    type: 3}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 191660433}[m
   m_PrefabAsset: {fileID: 0}[m
[31m-  m_GameObject: {fileID: 1384269232}[m
[32m+[m[32m  m_GameObject: {fileID: 0}[m
   m_Enabled: 1[m
   m_EditorHideFlags: 0[m
   m_Script: {fileID: 11500000, guid: cb38115528397a343805dd7e97358c67, type: 3}[m
   m_Name: [m
   m_EditorClassIdentifier: [m
[31m-  autoPlay: 0[m
[31m-  masterVolume: 0[m
[31m-  mainFrequency: 500[m
[31m-  useSinusAudioWave: 1[m
[31m-  sinusAudioWaveIntensity: 0.7[m
[31m-  useSquareAudioWave: 0[m
[31m-  squareAudioWaveIntensity: 0[m
[31m-  useSawAudioWave: 1[m
[31m-  sawAudioWaveIntensity: 0.3[m
[31m-  useAmplitudeModulation: 0[m
[31m-  amplitudeModulationOscillatorFrequency: 1[m
[31m-  useFrequencyModulation: 1[m
[31m-  frequencyModulationOscillatorFrequency: 6[m
[31m-  frequencyModulationOscillatorIntensity: 1[m
[31m-  amplitudeModulationRangeOut: 0[m
[31m-  frequencyModulationRangeOut: 0[m
[31m---- !u!82 &1384269234[m
[31m-AudioSource:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
[31m-  m_GameObject: {fileID: 1384269232}[m
[31m-  m_Enabled: 1[m
[31m-  serializedVersion: 4[m
[31m-  OutputAudioMixerGroup: {fileID: 0}[m
[31m-  m_audioClip: {fileID: 0}[m
[31m-  m_PlayOnAwake: 1[m
[31m-  m_Volume: 0.1[m
[31m-  m_Pitch: 1[m
[31m-  Loop: 0[m
[31m-  Mute: 0[m
[31m-  Spatialize: 0[m
[31m-  SpatializePostEffects: 0[m
[31m-  Priority: 128[m
[31m-  DopplerLevel: 1[m
[31m-  MinDistance: 1[m
[31m-  MaxDistance: 500[m
[31m-  Pan2D: 0[m
[31m-  rolloffMode: 0[m
[31m-  BypassEffects: 0[m
[31m-  BypassListenerEffects: 0[m
[31m-  BypassReverbZones: 0[m
[31m-  rolloffCustomCurve:[m
[31m-    serializedVersion: 2[m
[31m-    m_Curve:[m
[31m-    - serializedVersion: 3[m
[31m-      time: 0[m
[31m-      value: 1[m
[31m-      inSlope: 0[m
[31m-      outSlope: 0[m
[31m-      tangentMode: 0[m
[31m-      weightedMode: 0[m
[31m-      inWeight: 0.33333334[m
[31m-      outWeight: 0.33333334[m
[31m-    - serializedVersion: 3[m
[31m-      time: 1[m
[31m-      value: 0[m
[31m-      inSlope: 0[m
[31m-      outSlope: 0[m
[31m-      tangentMode: 0[m
[31m-      weightedMode: 0[m
[31m-      inWeight: 0.33333334[m
[31m-      outWeight: 0.33333334[m
[31m-    m_PreInfinity: 2[m
[31m-    m_PostInfinity: 2[m
[31m-    m_RotationOrder: 4[m
[31m-  panLevelCustomCurve:[m
[31m-    serializedVersion: 2[m
[31m-    m_Curve:[m
[31m-    - serializedVersion: 3[m
[31m-      time: 0[m
[31m-      value: 0[m
[31m-      inSlope: 0[m
[31m-      outSlope: 0[m
[31m-      tangentMode: 0[m
[31m-      weightedMode: 0[m
[31m-      inWeight: 0.33333334[m
[31m-      outWeight: 0.33333334[m
[31m-    m_PreInfinity: 2[m
[31m-    m_PostInfinity: 2[m
[31m-    m_RotationOrder: 4[m
[31m-  spreadCustomCurve:[m
[31m-    serializedVersion: 2[m
[31m-    m_Curve:[m
[31m-    - serializedVersion: 3[m
[31m-      time: 0[m
[31m-      value: 0[m
[31m-      inSlope: 0[m
[31m-      outSlope: 0[m
[31m-      tangentMode: 0[m
[31m-      weightedMode: 0[m
[31m-      inWeight: 0.33333334[m
[31m-      outWeight: 0.33333334[m
[31m-    m_PreInfinity: 2[m
[31m-    m_PostInfinity: 2[m
[31m-    m_RotationOrder: 4[m
[31m-  reverbZoneMixCustomCurve:[m
[31m-    serializedVersion: 2[m
[31m-    m_Curve:[m
[31m-    - serializedVersion: 3[m
[31m-      time: 0[m
[31m-      value: 1[m
[31m-      inSlope: 0[m
[31m-      outSlope: 0[m
[31m-      tangentMode: 0[m
[31m-      weightedMode: 0[m
[31m-      inWeight: 0.33333334[m
[31m-      outWeight: 0.33333334[m
[31m-    m_PreInfinity: 2[m
[31m-    m_PostInfinity: 2[m
[31m-    m_RotationOrder: 4[m
[31m---- !u!4 &1384269235[m
[31m-Transform:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
[31m-  m_GameObject: {fileID: 1384269232}[m
[31m-  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[31m-  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[31m-  m_LocalScale: {x: 1, y: 1, z: 1}[m
[31m-  m_Children: [][m
[31m-  m_Father: {fileID: 2007200795}[m
[31m-  m_RootOrder: 2[m
[31m-  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
 --- !u!1001 &1387462522[m
 PrefabInstance:[m
   m_ObjectHideFlags: 0[m
[36m@@ -15584,75 +15100,6 @@[m [mTransform:[m
     type: 3}[m
   m_PrefabInstance: {fileID: 1451073942}[m
   m_PrefabAsset: {fileID: 0}[m
[31m---- !u!1001 &1451746442[m
[31m-PrefabInstance:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  serializedVersion: 2[m
[31m-  m_Modification:[m
[31m-    m_TransformParent: {fileID: 223386903}[m
[31m-    m_Modifications:[m
[31m-    - target: {fileID: 100000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_Name[m
[31m-      value: Ivy (3)[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalPosition.x[m
[31m-      value: -11.06[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalPosition.y[m
[31m-      value: 0.97[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalPosition.z[m
[31m-      value: 8.62[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.x[m
[31m-      value: 0.000000119209275[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.y[m
[31m-      value: -0.7071078[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.z[m
[31m-      value: -0.7071058[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.w[m
[31m-      value: 0.000002197921[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_RootOrder[m
[31m-      value: 3[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalEulerAnglesHint.x[m
[31m-      value: -90.00001[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalEulerAnglesHint.y[m
[31m-      value: 0[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalEulerAnglesHint.z[m
[31m-      value: -180.00002[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalScale.x[m
[31m-      value: 1.7616[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalScale.y[m
[31m-      value: 1.6536397[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalScale.z[m
[31m-      value: -2.43277[m
[31m-      objectReference: {fileID: 0}[m
[31m-    m_RemovedComponents: [][m
[31m-  m_SourcePrefab: {fileID: 100100000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
 --- !u!1001 &1456932211[m
 PrefabInstance:[m
   m_ObjectHideFlags: 0[m
[36m@@ -15908,162 +15355,18 @@[m [mTransform:[m
     type: 3}[m
   m_PrefabInstance: {fileID: 1387462522}[m
   m_PrefabAsset: {fileID: 0}[m
[31m---- !u!1 &1489212691[m
[31m-GameObject:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
[31m-  serializedVersion: 6[m
[31m-  m_Component:[m
[31m-  - component: {fileID: 1489212694}[m
[31m-  - component: {fileID: 1489212693}[m
[31m-  - component: {fileID: 1489212692}[m
[31m-  m_Layer: 0[m
[31m-  m_Name: Voice[m
[31m-  m_TagString: Untagged[m
[31m-  m_Icon: {fileID: 0}[m
[31m-  m_NavMeshLayer: 0[m
[31m-  m_StaticEditorFlags: 0[m
[31m-  m_IsActive: 1[m
[31m---- !u!114 &1489212692[m
[32m+[m[32m--- !u!114 &1489212692 stripped[m
 MonoBehaviour:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 1489212692, guid: 74d6c2fd5f712d44e8342e6b94738c12,[m
[32m+[m[32m    type: 3}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 191660433}[m
   m_PrefabAsset: {fileID: 0}[m
[31m-  m_GameObject: {fileID: 1489212691}[m
[32m+[m[32m  m_GameObject: {fileID: 0}[m
   m_Enabled: 1[m
   m_EditorHideFlags: 0[m
   m_Script: {fileID: 11500000, guid: cb38115528397a343805dd7e97358c67, type: 3}[m
   m_Name: [m
   m_EditorClassIdentifier: [m
[31m-  autoPlay: 0[m
[31m-  masterVolume: 0[m
[31m-  mainFrequency: 500[m
[31m-  useSinusAudioWave: 1[m
[31m-  sinusAudioWaveIntensity: 1[m
[31m-  useSquareAudioWave: 0[m
[31m-  squareAudioWaveIntensity: 0[m
[31m-  useSawAudioWave: 0[m
[31m-  sawAudioWaveIntensity: 0[m
[31m-  useAmplitudeModulation: 0[m
[31m-  amplitudeModulationOscillatorFrequency: 1[m
[31m-  useFrequencyModulation: 1[m
[31m-  frequencyModulationOscillatorFrequency: 6[m
[31m-  frequencyModulationOscillatorIntensity: 1[m
[31m-  amplitudeModulationRangeOut: 0[m
[31m-  frequencyModulationRangeOut: 0[m
[31m---- !u!82 &1489212693[m
[31m-AudioSource:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
[31m-  m_GameObject: {fileID: 1489212691}[m
[31m-  m_Enabled: 1[m
[31m-  serializedVersion: 4[m
[31m-  OutputAudioMixerGroup: {fileID: 0}[m
[31m-  m_audioClip: {fileID: 0}[m
[31m-  m_PlayOnAwake: 1[m
[31m-  m_Volume: 0.1[m
[31m-  m_Pitch: 1[m
[31m-  Loop: 0[m
[31m-  Mute: 0[m
[31m-  Spatialize: 0[m
[31m-  SpatializePostEffects: 0[m
[31m-  Priority: 128[m
[31m-  DopplerLevel: 1[m
[31m-  MinDistance: 1[m
[31m-  MaxDistance: 500[m
[31m-  Pan2D: 0[m
[31m-  rolloffMode: 0[m
[31m-  BypassEffects: 0[m
[31m-  BypassListenerEffects: 0[m
[31m-  BypassReverbZones: 0[m
[31m-  rolloffCustomCurve:[m
[31m-    serializedVersion: 2[m
[31m-    m_Curve:[m
[31m-    - serializedVersion: 3[m
[31m-      time: 0[m
[31m-      value: 1[m
[31m-      inSlope: 0[m
[31m-      outSlope: 0[m
[31m-      tangentMode: 0[m
[31m-      weightedMode: 0[m
[31m-      inWeight: 0.33333334[m
[31m-      outWeight: 0.33333334[m
[31m-    - serializedVersion: 3[m
[31m-      time: 1[m
[31m-      value: 0[m
[31m-      inSlope: 0[m
[31m-      outSlope: 0[m
[31m-      tangentMode: 0[m
[31m-      weightedMode: 0[m
[31m-      inWeight: 0.33333334[m
[31m-      outWeight: 0.33333334[m
[31m-    m_PreInfinity: 2[m
[31m-    m_PostInfinity: 2[m
[31m-    m_RotationOrder: 4[m
[31m-  panLevelCustomCurve:[m
[31m-    serializedVersion: 2[m
[31m-    m_Curve:[m
[31m-    - serializedVersion: 3[m
[31m-      time: 0[m
[31m-      value: 0[m
[31m-      inSlope: 0[m
[31m-      outSlope: 0[m
[31m-      tangentMode: 0[m
[31m-      weightedMode: 0[m
[31m-      inWeight: 0.33333334[m
[31m-      outWeight: 0.33333334[m
[31m-    m_PreInfinity: 2[m
[31m-    m_PostInfinity: 2[m
[31m-    m_RotationOrder: 4[m
[31m-  spreadCustomCurve:[m
[31m-    serializedVersion: 2[m
[31m-    m_Curve:[m
[31m-    - serializedVersion: 3[m
[31m-      time: 0[m
[31m-      value: 0[m
[31m-      inSlope: 0[m
[31m-      outSlope: 0[m
[31m-      tangentMode: 0[m
[31m-      weightedMode: 0[m
[31m-      inWeight: 0.33333334[m
[31m-      outWeight: 0.33333334[m
[31m-    m_PreInfinity: 2[m
[31m-    m_PostInfinity: 2[m
[31m-    m_RotationOrder: 4[m
[31m-  reverbZoneMixCustomCurve:[m
[31m-    serializedVersion: 2[m
[31m-    m_Curve:[m
[31m-    - serializedVersion: 3[m
[31m-      time: 0[m
[31m-      value: 1[m
[31m-      inSlope: 0[m
[31m-      outSlope: 0[m
[31m-      tangentMode: 0[m
[31m-      weightedMode: 0[m
[31m-      inWeight: 0.33333334[m
[31m-      outWeight: 0.33333334[m
[31m-    m_PreInfinity: 2[m
[31m-    m_PostInfinity: 2[m
[31m-    m_RotationOrder: 4[m
[31m---- !u!4 &1489212694[m
[31m-Transform:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
[31m-  m_GameObject: {fileID: 1489212691}[m
[31m-  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[31m-  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[31m-  m_LocalScale: {x: 1, y: 1, z: 1}[m
[31m-  m_Children: [][m
[31m-  m_Father: {fileID: 2007200795}[m
[31m-  m_RootOrder: 0[m
[31m-  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
 --- !u!1001 &1495577103[m
 PrefabInstance:[m
   m_ObjectHideFlags: 0[m
[36m@@ -16295,7 +15598,7 @@[m [mTransform:[m
   m_LocalScale: {x: 4.7760997, y: 9.18969, z: 2.3682768}[m
   m_Children: [][m
   m_Father: {fileID: 223386903}[m
[31m-  m_RootOrder: 6[m
[32m+[m[32m  m_RootOrder: 3[m
   m_LocalEulerAnglesHint: {x: 0, y: -90.00001, z: 90.00001}[m
 --- !u!65 &1502974872[m
 BoxCollider:[m
[36m@@ -16928,7 +16231,7 @@[m [mTransform:[m
   m_LocalScale: {x: 4.7760997, y: 9.18969, z: 4.7760997}[m
   m_Children: [][m
   m_Father: {fileID: 223386903}[m
[31m-  m_RootOrder: 5[m
[32m+[m[32m  m_RootOrder: 2[m
   m_LocalEulerAnglesHint: {x: 0, y: 0, z: 90.00001}[m
 --- !u!65 &1554008801[m
 BoxCollider:[m
[36m@@ -18410,7 +17713,7 @@[m [mTransform:[m
   m_LocalScale: {x: 1, y: 1, z: 1}[m
   m_Children: [][m
   m_Father: {fileID: 0}[m
[31m-  m_RootOrder: 10[m
[32m+[m[32m  m_RootOrder: 9[m
   m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
 --- !u!1001 &1666496501[m
 PrefabInstance:[m
[36m@@ -20572,75 +19875,6 @@[m [mMonoBehaviour:[m
   m_Name: [m
   m_EditorClassIdentifier: [m
   vel: {x: 0, y: 0.1, z: 0}[m
[31m---- !u!1001 &1970401937[m
[31m-PrefabInstance:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  serializedVersion: 2[m
[31m-  m_Modification:[m
[31m-    m_TransformParent: {fileID: 0}[m
[31m-    m_Modifications:[m
[31m-    - target: {fileID: 100000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_Name[m
[31m-      value: Ivy (1)[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalPosition.x[m
[31m-      value: -13.3[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalPosition.y[m
[31m-      value: -0.97[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalPosition.z[m
[31m-      value: 7.11195[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.x[m
[31m-      value: -0[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.y[m
[31m-      value: -0.70710576[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.z[m
[31m-      value: -0[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalRotation.w[m
[31m-      value: 0.7071079[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_RootOrder[m
[31m-      value: 1[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalEulerAnglesHint.x[m
[31m-      value: 0[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalEulerAnglesHint.y[m
[31m-      value: -90.00001[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalEulerAnglesHint.z[m
[31m-      value: 0[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalScale.x[m
[31m-      value: 1.7616[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalScale.y[m
[31m-      value: 2.1261108[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
[31m-      propertyPath: m_LocalScale.z[m
[31m-      value: 2.4327698[m
[31m-      objectReference: {fileID: 0}[m
[31m-    m_RemovedComponents: [][m
[31m-  m_SourcePrefab: {fileID: 100100000, guid: 94a3aadeeeececf4ba50be1877217d17, type: 3}[m
 --- !u!1001 &1976829441[m
 PrefabInstance:[m
   m_ObjectHideFlags: 0[m
[36m@@ -21005,39 +20239,6 @@[m [mTransform:[m
     type: 3}[m
   m_PrefabInstance: {fileID: 2003814196}[m
   m_PrefabAsset: {fileID: 0}[m
[31m---- !u!1 &2007200794[m
[31m-GameObject:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
[31m-  serializedVersion: 6[m
[31m-  m_Component:[m
[31m-  - component: {fileID: 2007200795}[m
[31m-  m_Layer: 0[m
[31m-  m_Name: Voices[m
[31m-  m_TagString: Untagged[m
[31m-  m_Icon: {fileID: 0}[m
[31m-  m_NavMeshLayer: 0[m
[31m-  m_StaticEditorFlags: 0[m
[31m-  m_IsActive: 1[m
[31m---- !u!4 &2007200795[m
[31m-Transform:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  m_CorrespondingSourceObject: {fileID: 0}[m
[31m-  m_PrefabInstance: {fileID: 0}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
[31m-  m_GameObject: {fileID: 2007200794}[m
[31m-  m_LocalRotation: {x: 0, y: 0, z: 0, w: 1}[m
[31m-  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[31m-  m_LocalScale: {x: 1, y: 1, z: 1}[m
[31m-  m_Children:[m
[31m-  - {fileID: 1489212694}[m
[31m-  - {fileID: 1351403727}[m
[31m-  - {fileID: 1384269235}[m
[31m-  m_Father: {fileID: 191660434}[m
[31m-  m_RootOrder: 1[m
[31m-  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
 --- !u!1001 &2007540129[m
 PrefabInstance:[m
   m_ObjectHideFlags: 0[m
[36m@@ -22339,12 +21540,6 @@[m [mPrefabInstance:[m
       objectReference: {fileID: 2100000, guid: 1e6893fb8cb6d064bb4e7341258411b4, type: 2}[m
     m_RemovedComponents: [][m
   m_SourcePrefab: {fileID: 100100000, guid: 742b2e9bb92ed0e428b7ef5ccafe7f46, type: 3}[m
[31m---- !u!4 &2109163166 stripped[m
[31m-Transform:[m
[31m-  m_CorrespondingSourceObject: {fileID: 400000, guid: 94a3aadeeeececf4ba50be1877217d17,[m
[31m-    type: 3}[m
[31m-  m_PrefabInstance: {fileID: 490355784}[m
[31m-  m_PrefabAsset: {fileID: 0}[m
 --- !u!1001 &2121053764[m
 PrefabInstance:[m
   m_ObjectHideFlags: 0[m
[1mdiff --git a/Assets/Scenes/Lab.unity b/Assets/Scenes/Lab.unity[m
[1mindex 9bef07a..2028e99 100644[m
[1m--- a/Assets/Scenes/Lab.unity[m
[1m+++ b/Assets/Scenes/Lab.unity[m
[36m@@ -5703,12 +5703,30 @@[m [mAudioSource:[m
     m_PreInfinity: 2[m
     m_PostInfinity: 2[m
     m_RotationOrder: 4[m
[31m---- !u!1 &596693362 stripped[m
[32m+[m[32m--- !u!1 &596693362[m
 GameObject:[m
[31m-  m_CorrespondingSourceObject: {fileID: 100002, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-    type: 3}[m
[31m-  m_PrefabInstance: {fileID: 1682151495}[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
   m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 6810918338577156403}[m
[32m+[m[32m  - component: {fileID: 2776673361385657755}[m
[32m+[m[32m  - component: {fileID: 373202782472825907}[m
[32m+[m[32m  - component: {fileID: 7916406034419739445}[m
[32m+[m[32m  - component: {fileID: 76708441666808462}[m
[32m+[m[32m  - component: {fileID: 5822202920596260570}[m
[32m+[m[32m  - component: {fileID: 8780659592860411983}[m
[32m+[m[32m  - component: {fileID: 188923647463420049}[m
[32m+[m[32m  - component: {fileID: 596693363}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: FirstPersonCharacter[m
[32m+[m[32m  m_TagString: MainCamera[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
 --- !u!114 &596693363[m
 MonoBehaviour:[m
   m_ObjectHideFlags: 0[m
[36m@@ -6403,12 +6421,27 @@[m [mTransform:[m
   m_Father: {fileID: 0}[m
   m_RootOrder: 4[m
   m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[31m---- !u!1 &1506325277 stripped[m
[32m+[m[32m--- !u!1 &1506325277[m
 GameObject:[m
[31m-  m_CorrespondingSourceObject: {fileID: 100000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-    type: 3}[m
[31m-  m_PrefabInstance: {fileID: 1682151495}[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
   m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1506325283}[m
[32m+[m[32m  - component: {fileID: 237364049342690865}[m
[32m+[m[32m  - component: {fileID: 4889337988091006837}[m
[32m+[m[32m  - component: {fileID: 1703590444980832192}[m
[32m+[m[32m  - component: {fileID: 4884165746284290741}[m
[32m+[m[32m  - component: {fileID: 1506325278}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Player[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
 --- !u!114 &1506325278[m
 MonoBehaviour:[m
   m_ObjectHideFlags: 0[m
[36m@@ -6429,12 +6462,22 @@[m [mMonoBehaviour:[m
   fade: {fileID: 0}[m
   fadeTime: 0[m
   nextLevel: [m
[31m---- !u!4 &1506325283 stripped[m
[32m+[m[32m--- !u!4 &1506325283[m
 Transform:[m
[31m-  m_CorrespondingSourceObject: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-    type: 3}[m
[31m-  m_PrefabInstance: {fileID: 1682151495}[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
   m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1506325277}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -1, z: -0, w: 0.0000029504295}[m
[32m+[m[32m  m_LocalPosition: {x: 1.261, y: 0.904, z: 2.409}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 6810918338577156403}[m
[32m+[m[32m  - {fileID: 1548055403}[m
[32m+[m[32m  m_Father: {fileID: 0}[m
[32m+[m[32m  m_RootOrder: 2[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: -180.00002, z: 0}[m
 --- !u!1 &1548055402[m
 GameObject:[m
   m_ObjectHideFlags: 0[m
[36m@@ -6661,170 +6704,6 @@[m [mTransform:[m
   m_Father: {fileID: 1387813999}[m
   m_RootOrder: 1[m
   m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[31m---- !u!1001 &1682151495[m
[31m-PrefabInstance:[m
[31m-  m_ObjectHideFlags: 0[m
[31m-  serializedVersion: 2[m
[31m-  m_Modification:[m
[31m-    m_TransformParent: {fileID: 0}[m
[31m-    m_Modifications:[m
[31m-    - target: {fileID: 100000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_Name[m
[31m-      value: Player[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_LocalPosition.x[m
[31m-      value: 1.261[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_LocalPosition.y[m
[31m-      value: 0.904[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_LocalPosition.z[m
[31m-      value: 2.409[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_LocalRotation.x[m
[31m-      value: -0[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_LocalRotation.y[m
[31m-      value: -1[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_LocalRotation.z[m
[31m-      value: -0[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_LocalRotation.w[m
[31m-      value: 0.0000029504295[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_RootOrder[m
[31m-      value: 2[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_LocalEulerAnglesHint.x[m
[31m-      value: 0[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_LocalEulerAnglesHint.y[m
[31m-      value: -180.00002[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_LocalEulerAnglesHint.z[m
[31m-      value: 0[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 8200000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_Volume[m
[31m-      value: 0.1[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 11400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: canLook[m
[31m-      value: 1[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 11400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_WalkSpeed[m
[31m-      value: 3[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 11400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_RunSpeed[m
[31m-      value: 7[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 11400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_HeadBob.HorizontalBobRange[m
[31m-      value: 0.05[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 11400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_HeadBob.VerticalBobRange[m
[31m-      value: 0.05[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 11400000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_UseHeadBob[m
[31m-      value: 1[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 14300000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
[31m-      propertyPath: m_Radius[m
[31m-      value: 0.38[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 4993169200533872811, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: m_Enabled[m
[31m-      value: 1[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 7585956492611610989, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: m_Enabled[m
[31m-      value: 1[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 1958383183347616696, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: m_Enabled[m
[31m-      value: 1[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 1958383183347616696, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: colors.Array.data[1].r[m
[31m-      value: 0.23529412[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 1958383183347616696, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: colors.Array.data[1].g[m
[31m-      value: 0.23529412[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 1958383183347616696, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: colors.Array.data[1].b[m
[31m-      value: 0.23529412[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 1958383183347616696, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: colors.Array.data[20].r[m
[31m-      value: 0.14509805[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 1958383183347616696, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: colors.Array.data[20].g[m
[31m-      value: 0.14117648[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 1958383183347616696, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: colors.Array.data[20].b[m
[31m-      value: 0.078431375[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 1958383183347616696, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: colors.Array.data[6].r[m
[31m-      value: 0.25882354[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 1958383183347616696, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: colors.Array.data[6].g[m
[31m-      value: 0.25882354[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 1958383183347616696, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: colors.Array.data[6].b[m
[31m-      value: 0.25882354[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 1958383183347616696, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: colors.Array.data[7].r[m
[31m-      value: 0.20784314[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 1958383183347616696, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: colors.Array.data[7].g[m
[31m-      value: 0.20784314[m
[31m-      objectReference: {fileID: 0}[m
[31m-    - target: {fileID: 1958383183347616696, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd,[m
[31m-        type: 3}[m
[31m-      propertyPath: colors.Array.data[7].b[m
[31m-      value: 0.20784314[m
[31m-      objectReference: {fileID: 0}[m
[31m-    m_RemovedComponents: [][m
[31m-  m_SourcePrefab: {fileID: 100100000, guid: d35c5e9bda4b34a3abf3e5c0f8a0bbcd, type: 3}[m
 --- !u!1 &1758335396[m
 GameObject:[m
   m_ObjectHideFlags: 0[m
[36m@@ -7429,3 +7308,460 @@[m [mTransform:[m
     type: 3}[m
   m_PrefabInstance: {fileID: 2090327704}[m
   m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m--- !u!114 &76708441666808462[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 596693362}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: 948f4100a11a5c24981795d21301da5c, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  volumeTrigger: {fileID: 0}[m
[32m+[m[32m  volumeLayer:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Bits: 4294967295[m
[32m+[m[32m  stopNaNPropagation: 1[m
[32m+[m[32m  finalBlitToCameraTarget: 1[m
[32m+[m[32m  antialiasingMode: 0[m
[32m+[m[32m  temporalAntialiasing:[m
[32m+[m[32m    jitterSpread: 0.75[m
[32m+[m[32m    sharpness: 0.25[m
[32m+[m[32m    stationaryBlending: 0.95[m
[32m+[m[32m    motionBlending: 0.85[m
[32m+[m[32m  subpixelMorphologicalAntialiasing:[m
[32m+[m[32m    quality: 2[m
[32m+[m[32m  fastApproximateAntialiasing:[m
[32m+[m[32m    fastMode: 0[m
[32m+[m[32m    keepAlpha: 0[m
[32m+[m[32m  fog:[m
[32m+[m[32m    enabled: 1[m
[32m+[m[32m    excludeSkybox: 1[m
[32m+[m[32m  debugLayer:[m
[32m+[m[32m    lightMeter:[m
[32m+[m[32m      width: 512[m
[32m+[m[32m      height: 256[m
[32m+[m[32m      showCurves: 1[m
[32m+[m[32m    histogram:[m
[32m+[m[32m      width: 512[m
[32m+[m[32m      height: 256[m
[32m+[m[32m      channel: 3[m
[32m+[m[32m    waveform:[m
[32m+[m[32m      exposure: 0.12[m
[32m+[m[32m      height: 256[m
[32m+[m[32m    vectorscope:[m
[32m+[m[32m      size: 256[m
[32m+[m[32m      exposure: 0.12[m
[32m+[m[32m    overlaySettings:[m
[32m+[m[32m      linearDepth: 0[m
[32m+[m[32m      motionColorIntensity: 4[m
[32m+[m[32m      motionGridSize: 64[m
[32m+[m[32m      colorBlindnessType: 0[m
[32m+[m[32m      colorBlindnessStrength: 1[m
[32m+[m[32m  m_Resources: {fileID: 11400000, guid: d82512f9c8e5d4a4d938b575d47f88d4, type: 2}[m
[32m+[m[32m  m_ShowToolkit: 0[m
[32m+[m[32m  m_ShowCustomSorter: 0[m
[32m+[m[32m  breakBeforeColorGrading: 0[m
[32m+[m[32m  m_BeforeTransparentBundles: [][m
[32m+[m[32m  m_BeforeStackBundles: [][m
[32m+[m[32m  m_AfterStackBundles: [][m
[32m+[m[32m--- !u!114 &188923647463420049[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 596693362}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: 64f9144a767f6d842a42451779fca81c, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  colors:[m
[32m+[m[32m  - {r: 0, g: 0, b: 0, a: 0}[m
[32m+[m[32m  - {r: 0.23529412, g: 0.23529412, b: 0.23529412, a: 0}[m
[32m+[m[32m  - {r: 0.503, g: 0.503, b: 0.503, a: 0}[m
[32m+[m[32m  - {r: 0.6603774, g: 0.6603774, b: 0.6603774, a: 0}[m
[32m+[m[32m  - {r: 0.8301887, g: 0.8301887, b: 0.8301887, a: 0}[m
[32m+[m[32m  - {r: 0.385, g: 0.385, b: 0.385, a: 0}[m
[32m+[m[32m  - {r: 0.25882354, g: 0.25882354, b: 0.25882354, a: 0}[m
[32m+[m[32m  - {r: 0.20784314, g: 0.20784314, b: 0.20784314, a: 0}[m
[32m+[m[32m  - {r: 0.118999995, g: 0.063, b: 0.063, a: 1}[m
[32m+[m[32m  - {r: 0.22745098, g: 0.03661961, b: 0.03661961, a: 1}[m
[32m+[m[32m  - {r: 0.3764706, g: 0.09487058, b: 0.09487058, a: 1}[m
[32m+[m[32m  - {r: 0.636, g: 0.2297428, b: 0.19588801, a: 1}[m
[32m+[m[32m  - {r: 0.057647064, g: 0.094797395, b: 0.13725491, a: 1}[m
[32m+[m[32m  - {r: 0.05644801, g: 0.14025602, b: 0.252, a: 1}[m
[32m+[m[32m  - {r: 0.12073602, g: 0.23971145, b: 0.39200002, a: 1}[m
[32m+[m[32m  - {r: 0.26040003, g: 0.41924518, b: 0.6, a: 1}[m
[32m+[m[32m  - {r: 0.12385714, g: 0.289, b: 0.07798414, a: 1}[m
[32m+[m[32m  - {r: 0.18946666, g: 0.46400002, b: 0.116000004, a: 1}[m
[32m+[m[32m  - {r: 0.22943097, g: 0.538, b: 0.12804401, a: 1}[m
[32m+[m[32m  - {r: 0.32435524, g: 0.6698113, b: 0.17377181, a: 1}[m
[32m+[m[32m  - {r: 0.14509805, g: 0.14117648, b: 0.078431375, a: 1}[m
[32m+[m[32m  - {r: 0.259, g: 0.25168326, b: 0.08339799, a: 1}[m
[32m+[m[32m  - {r: 0.48299998, g: 0.46236518, b: 0.111572996, a: 1}[m
[32m+[m[32m  - {r: 0.67800003, g: 0.65073144, b: 0.180348, a: 1}[m
[32m+[m[32m  - {r: 0.7921569, g: 0.21641412, b: 0.21071371, a: 1}[m
[32m+[m[32m  - {r: 0.8301887, g: 0.797788, b: 0.23887502, a: 1}[m
[32m+[m[32m  - {r: 0.34897533, g: 0.8018868, b: 0.22316661, a: 1}[m
[32m+[m[32m  - {r: 0.259, g: 0.47303677, b: 0.7254902, a: 1}[m
[32m+[m[32m--- !u!143 &237364049342690865[m
[32m+[m[32mCharacterController:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1506325277}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Height: 1.8[m
[32m+[m[32m  m_Radius: 0.38[m
[32m+[m[32m  m_SlopeLimit: 45[m
[32m+[m[32m  m_StepOffset: 0.3[m
[32m+[m[32m  m_SkinWidth: 0.08[m
[32m+[m[32m  m_MinMoveDistance: 0[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!81 &373202782472825907[m
[32m+[m[32mAudioListener:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 596693362}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m--- !u!54 &1703590444980832192[m
[32m+[m[32mRigidbody:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1506325277}[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Mass: 1[m
[32m+[m[32m  m_Drag: 0[m
[32m+[m[32m  m_AngularDrag: 0.05[m
[32m+[m[32m  m_UseGravity: 1[m
[32m+[m[32m  m_IsKinematic: 1[m
[32m+[m[32m  m_Interpolate: 0[m
[32m+[m[32m  m_Constraints: 0[m
[32m+[m[32m  m_CollisionDetection: 0[m
[32m+[m[32m--- !u!20 &2776673361385657755[m
[32m+[m[32mCamera:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 596693362}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_ClearFlags: 1[m
[32m+[m[32m  m_BackGroundColor: {r: 0.19215687, g: 0.3019608, b: 0.4745098, a: 0.019607844}[m
[32m+[m[32m  m_projectionMatrixMode: 1[m
[32m+[m[32m  m_SensorSize: {x: 36, y: 24}[m
[32m+[m[32m  m_LensShift: {x: 0, y: 0}[m
[32m+[m[32m  m_GateFitMode: 2[m
[32m+[m[32m  m_FocalLength: 50[m
[32m+[m[32m  m_NormalizedViewPortRect:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    x: 0[m
[32m+[m[32m    y: 0[m
[32m+[m[32m    width: 1[m
[32m+[m[32m    height: 1[m
[32m+[m[32m  near clip plane: 0.3[m
[32m+[m[32m  far clip plane: 1000[m
[32m+[m[32m  field of view: 60[m
[32m+[m[32m  orthographic: 0[m
[32m+[m[32m  orthographic size: 5[m
[32m+[m[32m  m_Depth: 0[m
[32m+[m[32m  m_CullingMask:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Bits: 4294967295[m
[32m+[m[32m  m_RenderingPath: -1[m
[32m+[m[32m  m_TargetTexture: {fileID: 0}[m
[32m+[m[32m  m_TargetDisplay: 0[m
[32m+[m[32m  m_TargetEye: 3[m
[32m+[m[32m  m_HDR: 0[m
[32m+[m[32m  m_AllowMSAA: 1[m
[32m+[m[32m  m_AllowDynamicResolution: 0[m
[32m+[m[32m  m_ForceIntoRT: 1[m
[32m+[m[32m  m_OcclusionCulling: 1[m
[32m+[m[32m  m_StereoConvergence: 10[m
[32m+[m[32m  m_StereoSeparation: 0.022[m
[32m+[m[32m--- !u!82 &4884165746284290741[m
[32m+[m[32mAudioSource:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1506325277}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 4[m
[32m+[m[32m  OutputAudioMixerGroup: {fileID: 0}[m
[32m+[m[32m  m_audioClip: {fileID: 0}[m
[32m+[m[32m  m_PlayOnAwake: 1[m
[32m+[m[32m  m_Volume: 0.1[m
[32m+[m[32m  m_Pitch: 1[m
[32m+[m[32m  Loop: 0[m
[32m+[m[32m  Mute: 0[m
[32m+[m[32m  Spatialize: 0[m
[32m+[m[32m  SpatializePostEffects: 0[m
[32m+[m[32m  Priority: 128[m
[32m+[m[32m  DopplerLevel: 1[m
[32m+[m[32m  MinDistance: 1[m
[32m+[m[32m  MaxDistance: 500[m
[32m+[m[32m  Pan2D: 0[m
[32m+[m[32m  rolloffMode: 0[m
[32m+[m[32m  BypassEffects: 0[m
[32m+[m[32m  BypassListenerEffects: 0[m
[32m+[m[32m  BypassReverbZones: 0[m
[32m+[m[32m  rolloffCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 1[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m  panLevelCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 0[m
[32m+[m[32m  spreadCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m  reverbZoneMixCustomCurve:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve:[m
[32m+[m[32m    - serializedVersion: 3[m
[32m+[m[32m      time: 0[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      inSlope: 0[m
[32m+[m[32m      outSlope: 0[m
[32m+[m[32m      tangentMode: 0[m
[32m+[m[32m      weightedMode: 0[m
[32m+[m[32m      inWeight: 0.33333334[m
[32m+[m[32m      outWeight: 0.33333334[m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 0[m
[32m+[m[32m--- !u!114 &4889337988091006837[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1506325277}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: 05ec5cf00ca181d45a42ba1870e148c3, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  m_IsWalking: 0[m
[32m+[m[32m  m_WalkSpeed: 3[m
[32m+[m[32m  m_RunSpeed: 7[m
[32m+[m[32m  m_RunstepLenghten: 0.7[m
[32m+[m[32m  m_JumpSpeed: 10[m
[32m+[m[32m  m_StickToGroundForce: 10[m
[32m+[m[32m  m_GravityMultiplier: 2[m
[32m+[m[32m  m_MouseLook:[m
[32m+[m[32m    XSensitivity: 2[m
[32m+[m[32m    YSensitivity: 2[m
[32m+[m[32m    clampVerticalRotation: 1[m
[32m+[m[32m    MinimumX: -90[m
[32m+[m[32m    MaximumX: 90[m
[32m+[m[32m    smooth: 0[m
[32m+[m[32m    smoothTime: 5[m
[32m+[m[32m    lockCursor: 1[m
[32m+[m[32m  m_UseFovKick: 1[m
[32m+[m[32m  m_FovKick:[m
[32m+[m[32m    Camera: {fileID: 0}[m
[32m+[m[32m    originalFov: 0[m
[32m+[m[32m    FOVIncrease: 3[m
[32m+[m[32m    TimeToIncrease: 1[m
[32m+[m[32m    TimeToDecrease: 1[m
[32m+[m[32m    IncreaseCurve:[m
[32m+[m[32m      serializedVersion: 2[m
[32m+[m[32m      m_Curve:[m
[32m+[m[32m      - serializedVersion: 3[m
[32m+[m[32m        time: 0[m
[32m+[m[32m        value: 0[m
[32m+[m[32m        inSlope: 0[m
[32m+[m[32m        outSlope: 0[m
[32m+[m[32m        tangentMode: 0[m
[32m+[m[32m        weightedMode: 0[m
[32m+[m[32m        inWeight: 0.33333334[m
[32m+[m[32m        outWeight: 0.33333334[m
[32m+[m[32m      - serializedVersion: 3[m
[32m+[m[32m        time: 1[m
[32m+[m[32m        value: 1[m
[32m+[m[32m        inSlope: 2[m
[32m+[m[32m        outSlope: 2[m
[32m+[m[32m        tangentMode: 0[m
[32m+[m[32m        weightedMode: 0[m
[32m+[m[32m        inWeight: 0.33333334[m
[32m+[m[32m        outWeight: 0.33333334[m
[32m+[m[32m      m_PreInfinity: 2[m
[32m+[m[32m      m_PostInfinity: 2[m
[32m+[m[32m      m_RotationOrder: 4[m
[32m+[m[32m  m_UseHeadBob: 1[m
[32m+[m[32m  m_HeadBob:[m
[32m+[m[32m    HorizontalBobRange: 0.05[m
[32m+[m[32m    VerticalBobRange: 0.05[m
[32m+[m[32m    Bobcurve:[m
[32m+[m[32m      serializedVersion: 2[m
[32m+[m[32m      m_Curve:[m
[32m+[m[32m      - serializedVersion: 3[m
[32m+[m[32m        time: 0[m
[32m+[m[32m        value: 0[m
[32m+[m[32m        inSlope: 0[m
[32m+[m[32m        outSlope: 0[m
[32m+[m[32m        tangentMode: 0[m
[32m+[m[32m        weightedMode: 0[m
[32m+[m[32m        inWeight: 0.33333334[m
[32m+[m[32m        outWeight: 0.33333334[m
[32m+[m[32m      - serializedVersion: 3[m
[32m+[m[32m        time: 0.5[m
[32m+[m[32m        value: 1[m
[32m+[m[32m        inSlope: 0[m
[32m+[m[32m        outSlope: 0[m
[32m+[m[32m        tangentMode: 0[m
[32m+[m[32m        weightedMode: 0[m
[32m+[m[32m        inWeight: 0.33333334[m
[32m+[m[32m        outWeight: 0.33333334[m
[32m+[m[32m      - serializedVersion: 3[m
[32m+[m[32m        time: 1[m
[32m+[m[32m        value: 0[m
[32m+[m[32m        inSlope: 0[m
[32m+[m[32m        outSlope: 0[m
[32m+[m[32m        tangentMode: 0[m
[32m+[m[32m        weightedMode: 0[m
[32m+[m[32m        inWeight: 0.33333334[m
[32m+[m[32m        outWeight: 0.33333334[m
[32m+[m[32m      - serializedVersion: 3[m
[32m+[m[32m        time: 1.5[m
[32m+[m[32m        value: -1[m
[32m+[m[32m        inSlope: 0[m
[32m+[m[32m        outSlope: 0[m
[32m+[m[32m        tangentMode: 0[m
[32m+[m[32m        weightedMode: 0[m
[32m+[m[32m        inWeight: 0.33333334[m
[32m+[m[32m        outWeight: 0.33333334[m
[32m+[m[32m      - serializedVersion: 3[m
[32m+[m[32m        time: 2[m
[32m+[m[32m        value: 0[m
[32m+[m[32m        inSlope: 0[m
[32m+[m[32m        outSlope: 0[m
[32m+[m[32m        tangentMode: 0[m
[32m+[m[32m        weightedMode: 0[m
[32m+[m[32m        inWeight: 0.33333334[m
[32m+[m[32m        outWeight: 0.33333334[m
[32m+[m[32m      m_PreInfinity: 2[m
[32m+[m[32m      m_PostInfinity: 2[m
[32m+[m[32m      m_RotationOrder: 4[m
[32m+[m[32m    VerticaltoHorizontalRatio: 2[m
[32m+[m[32m  m_JumpBob:[m
[32m+[m[32m    BobDuration: 0.2[m
[32m+[m[32m    BobAmount: 0.1[m
[32m+[m[32m  m_StepInterval: 5[m
[32m+[m[32m  m_FootstepSounds:[m
[32m+[m[32m  - {fileID: 8300000, guid: 42e65e088b3f4374e851b8dbd38f3df9, type: 3}[m
[32m+[m[32m  - {fileID: 8300000, guid: 8bc94ec6ed537e743b481638bdcd503d, type: 3}[m
[32m+[m[32m  m_JumpSound: {fileID: 8300000, guid: 5897aeed9b676024fbb8c694b421a861, type: 3}[m
[32m+[m[32m  m_LandSound: {fileID: 8300000, guid: 3b09d59f4499d45428baa7a21e954296, type: 3}[m
[32m+[m[32m  canLook: 1[m
[32m+[m[32m--- !u!114 &5822202920596260570[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 596693362}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: ad06e60d35a297149adcc16be5979131, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  pattern: {fileID: 2800000, guid: 3fe921721e92c8d45ad530c33811eb6f, type: 3}[m
[32m+[m[32m  threshold: 1[m
[32m+[m[32m  strength: 0.88[m
[32m+[m[32m--- !u!4 &6810918338577156403[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 596693362}[m
[32m+[m[32m  m_LocalRotation: {x: 0, y: 0, z: 0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0.8, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 1506325283}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!124 &7916406034419739445[m
[32m+[m[32mBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 596693362}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m--- !u!114 &8780659592860411983[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 596693362}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: ba54bbb8d59fc1d48a351f7d6a559f82, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  horizontalResolution: 160[m
[32m+[m[32m  verticalResolution: 144[m
[1mdiff --git a/Assets/Scenes/MechanicsTesting.meta b/Assets/Scenes/MechanicsTesting.meta[m
[1mnew file mode 100644[m
[1mindex 0000000..579519b[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scenes/MechanicsTesting.meta[m
[36m@@ -0,0 +1,8 @@[m
[32m+[m[32mfileFormatVersion: 2[m
[32m+[m[32mguid: 1b458432c00319b4c925ad6e1ddc6093[m
[32m+[m[32mfolderAsset: yes[m
[32m+[m[32mDefaultImporter:[m
[32m+[m[32m  externalObjects: {}[m
[32m+[m[32m  userData:[m[41m [m
[32m+[m[32m  assetBundleName:[m[41m [m
[32m+[m[32m  assetBundleVariant:[m[41m [m
[1mdiff --git a/Assets/Scenes/MechanicsTesting/Blue.mat b/Assets/Scenes/MechanicsTesting/Blue.mat[m
[1mnew file mode 100644[m
[1mindex 0000000..34b4295[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scenes/MechanicsTesting/Blue.mat[m
[36m@@ -0,0 +1,77 @@[m
[32m+[m[32m%YAML 1.1[m
[32m+[m[32m%TAG !u! tag:unity3d.com,2011:[m
[32m+[m[32m--- !u!21 &2100000[m
[32m+[m[32mMaterial:[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_Name: Blue[m
[32m+[m[32m  m_Shader: {fileID: 46, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_ShaderKeywords:[m[41m [m
[32m+[m[32m  m_LightmapFlags: 4[m
[32m+[m[32m  m_EnableInstancingVariants: 0[m
[32m+[m[32m  m_DoubleSidedGI: 0[m
[32m+[m[32m  m_CustomRenderQueue: -1[m
[32m+[m[32m  stringTagMap: {}[m
[32m+[m[32m  disabledShaderPasses: [][m
[32m+[m[32m  m_SavedProperties:[m
[32m+[m[32m    serializedVersion: 3[m
[32m+[m[32m    m_TexEnvs:[m
[32m+[m[32m    - _BumpMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _DetailAlbedoMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _DetailMask:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _DetailNormalMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _EmissionMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _MainTex:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _MetallicGlossMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _OcclusionMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _ParallaxMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    m_Floats:[m
[32m+[m[32m    - _BumpScale: 1[m
[32m+[m[32m    - _Cutoff: 0.5[m
[32m+[m[32m    - _DetailNormalMapScale: 1[m
[32m+[m[32m    - _DstBlend: 0[m
[32m+[m[32m    - _GlossMapScale: 1[m
[32m+[m[32m    - _Glossiness: 0.5[m
[32m+[m[32m    - _GlossyReflections: 1[m
[32m+[m[32m    - _Metallic: 0[m
[32m+[m[32m    - _Mode: 0[m
[32m+[m[32m    - _OcclusionStrength: 1[m
[32m+[m[32m    - _Parallax: 0.02[m
[32m+[m[32m    - _SmoothnessTextureChannel: 0[m
[32m+[m[32m    - _SpecularHighlights: 1[m
[32m+[m[32m    - _SrcBlend: 1[m
[32m+[m[32m    - _UVSec: 0[m
[32m+[m[32m    - _ZWrite: 1[m
[32m+[m[32m    m_Colors:[m
[32m+[m[32m    - _Color: {r: 0, g: 0.48301983, b: 1, a: 1}[m
[32m+[m[32m    - _EmissionColor: {r: 0, g: 0, b: 0, a: 1}[m
[1mdiff --git a/Assets/Scenes/MechanicsTesting/Blue.mat.meta b/Assets/Scenes/MechanicsTesting/Blue.mat.meta[m
[1mnew file mode 100644[m
[1mindex 0000000..3f0fe83[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scenes/MechanicsTesting/Blue.mat.meta[m
[36m@@ -0,0 +1,8 @@[m
[32m+[m[32mfileFormatVersion: 2[m
[32m+[m[32mguid: 3e79eece95bcf264183f87344299720f[m
[32m+[m[32mNativeFormatImporter:[m
[32m+[m[32m  externalObjects: {}[m
[32m+[m[32m  mainObjectFileID: 2100000[m
[32m+[m[32m  userData:[m[41m [m
[32m+[m[32m  assetBundleName:[m[41m [m
[32m+[m[32m  assetBundleVariant:[m[41m [m
[1mdiff --git a/Assets/Scenes/MechanicsTesting/Green.mat b/Assets/Scenes/MechanicsTesting/Green.mat[m
[1mnew file mode 100644[m
[1mindex 0000000..38d54d5[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scenes/MechanicsTesting/Green.mat[m
[36m@@ -0,0 +1,77 @@[m
[32m+[m[32m%YAML 1.1[m
[32m+[m[32m%TAG !u! tag:unity3d.com,2011:[m
[32m+[m[32m--- !u!21 &2100000[m
[32m+[m[32mMaterial:[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_Name: Green[m
[32m+[m[32m  m_Shader: {fileID: 46, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_ShaderKeywords:[m[41m [m
[32m+[m[32m  m_LightmapFlags: 4[m
[32m+[m[32m  m_EnableInstancingVariants: 0[m
[32m+[m[32m  m_DoubleSidedGI: 0[m
[32m+[m[32m  m_CustomRenderQueue: -1[m
[32m+[m[32m  stringTagMap: {}[m
[32m+[m[32m  disabledShaderPasses: [][m
[32m+[m[32m  m_SavedProperties:[m
[32m+[m[32m    serializedVersion: 3[m
[32m+[m[32m    m_TexEnvs:[m
[32m+[m[32m    - _BumpMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _DetailAlbedoMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _DetailMask:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _DetailNormalMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _EmissionMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _MainTex:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _MetallicGlossMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _OcclusionMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _ParallaxMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    m_Floats:[m
[32m+[m[32m    - _BumpScale: 1[m
[32m+[m[32m    - _Cutoff: 0.5[m
[32m+[m[32m    - _DetailNormalMapScale: 1[m
[32m+[m[32m    - _DstBlend: 0[m
[32m+[m[32m    - _GlossMapScale: 1[m
[32m+[m[32m    - _Glossiness: 0.5[m
[32m+[m[32m    - _GlossyReflections: 1[m
[32m+[m[32m    - _Metallic: 0[m
[32m+[m[32m    - _Mode: 0[m
[32m+[m[32m    - _OcclusionStrength: 1[m
[32m+[m[32m    - _Parallax: 0.02[m
[32m+[m[32m    - _SmoothnessTextureChannel: 0[m
[32m+[m[32m    - _SpecularHighlights: 1[m
[32m+[m[32m    - _SrcBlend: 1[m
[32m+[m[32m    - _UVSec: 0[m
[32m+[m[32m    - _ZWrite: 1[m
[32m+[m[32m    m_Colors:[m
[32m+[m[32m    - _Color: {r: 0.12300229, g: 1, b: 0, a: 1}[m
[32m+[m[32m    - _EmissionColor: {r: 0, g: 0, b: 0, a: 1}[m
[1mdiff --git a/Assets/Scenes/MechanicsTesting/Green.mat.meta b/Assets/Scenes/MechanicsTesting/Green.mat.meta[m
[1mnew file mode 100644[m
[1mindex 0000000..cc77e09[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scenes/MechanicsTesting/Green.mat.meta[m
[36m@@ -0,0 +1,8 @@[m
[32m+[m[32mfileFormatVersion: 2[m
[32m+[m[32mguid: 8ef02f699b63e7044a183e0cf62efb74[m
[32m+[m[32mNativeFormatImporter:[m
[32m+[m[32m  externalObjects: {}[m
[32m+[m[32m  mainObjectFileID: 2100000[m
[32m+[m[32m  userData:[m[41m [m
[32m+[m[32m  assetBundleName:[m[41m [m
[32m+[m[32m  assetBundleVariant:[m[41m [m
[1mdiff --git a/Assets/Scenes/MechanicsTesting/Ground.mat b/Assets/Scenes/MechanicsTesting/Ground.mat[m
[1mnew file mode 100644[m
[1mindex 0000000..61df093[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scenes/MechanicsTesting/Ground.mat[m
[36m@@ -0,0 +1,77 @@[m
[32m+[m[32m%YAML 1.1[m
[32m+[m[32m%TAG !u! tag:unity3d.com,2011:[m
[32m+[m[32m--- !u!21 &2100000[m
[32m+[m[32mMaterial:[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_Name: Ground[m
[32m+[m[32m  m_Shader: {fileID: 46, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_ShaderKeywords:[m[41m [m
[32m+[m[32m  m_LightmapFlags: 4[m
[32m+[m[32m  m_EnableInstancingVariants: 0[m
[32m+[m[32m  m_DoubleSidedGI: 0[m
[32m+[m[32m  m_CustomRenderQueue: -1[m
[32m+[m[32m  stringTagMap: {}[m
[32m+[m[32m  disabledShaderPasses: [][m
[32m+[m[32m  m_SavedProperties:[m
[32m+[m[32m    serializedVersion: 3[m
[32m+[m[32m    m_TexEnvs:[m
[32m+[m[32m    - _BumpMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _DetailAlbedoMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _DetailMask:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _DetailNormalMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _EmissionMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _MainTex:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _MetallicGlossMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _OcclusionMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _ParallaxMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    m_Floats:[m
[32m+[m[32m    - _BumpScale: 1[m
[32m+[m[32m    - _Cutoff: 0.5[m
[32m+[m[32m    - _DetailNormalMapScale: 1[m
[32m+[m[32m    - _DstBlend: 0[m
[32m+[m[32m    - _GlossMapScale: 1[m
[32m+[m[32m    - _Glossiness: 0.5[m
[32m+[m[32m    - _GlossyReflections: 1[m
[32m+[m[32m    - _Metallic: 0[m
[32m+[m[32m    - _Mode: 0[m
[32m+[m[32m    - _OcclusionStrength: 1[m
[32m+[m[32m    - _Parallax: 0.02[m
[32m+[m[32m    - _SmoothnessTextureChannel: 0[m
[32m+[m[32m    - _SpecularHighlights: 1[m
[32m+[m[32m    - _SrcBlend: 1[m
[32m+[m[32m    - _UVSec: 0[m
[32m+[m[32m    - _ZWrite: 1[m
[32m+[m[32m    m_Colors:[m
[32m+[m[32m    - _Color: {r: 0.1509434, g: 0.1509434, b: 0.1509434, a: 1}[m
[32m+[m[32m    - _EmissionColor: {r: 0, g: 0, b: 0, a: 1}[m
[1mdiff --git a/Assets/Scenes/MechanicsTesting/Ground.mat.meta b/Assets/Scenes/MechanicsTesting/Ground.mat.meta[m
[1mnew file mode 100644[m
[1mindex 0000000..d16c08b[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scenes/MechanicsTesting/Ground.mat.meta[m
[36m@@ -0,0 +1,8 @@[m
[32m+[m[32mfileFormatVersion: 2[m
[32m+[m[32mguid: 577ffc801fa3b794995ef08e35b7d8ba[m
[32m+[m[32mNativeFormatImporter:[m
[32m+[m[32m  externalObjects: {}[m
[32m+[m[32m  mainObjectFileID: 2100000[m
[32m+[m[32m  userData:[m[41m [m
[32m+[m[32m  assetBundleName:[m[41m [m
[32m+[m[32m  assetBundleVariant:[m[41m [m
[1mdiff --git a/Assets/Scenes/MechanicsTesting/MechanicsTesting0.unity b/Assets/Scenes/MechanicsTesting/MechanicsTesting0.unity[m
[1mnew file mode 100644[m
[1mindex 0000000..a910cc1[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scenes/MechanicsTesting/MechanicsTesting0.unity[m
[36m@@ -0,0 +1,1610 @@[m
[32m+[m[32m%YAML 1.1[m
[32m+[m[32m%TAG !u! tag:unity3d.com,2011:[m
[32m+[m[32m--- !u!29 &1[m
[32m+[m[32mOcclusionCullingSettings:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_OcclusionBakeSettings:[m
[32m+[m[32m    smallestOccluder: 5[m
[32m+[m[32m    smallestHole: 0.25[m
[32m+[m[32m    backfaceThreshold: 100[m
[32m+[m[32m  m_SceneGUID: 00000000000000000000000000000000[m
[32m+[m[32m  m_OcclusionCullingData: {fileID: 0}[m
[32m+[m[32m--- !u!104 &2[m
[32m+[m[32mRenderSettings:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  serializedVersion: 9[m
[32m+[m[32m  m_Fog: 0[m
[32m+[m[32m  m_FogColor: {r: 0.5, g: 0.5, b: 0.5, a: 1}[m
[32m+[m[32m  m_FogMode: 3[m
[32m+[m[32m  m_FogDensity: 0.01[m
[32m+[m[32m  m_LinearFogStart: 0[m
[32m+[m[32m  m_LinearFogEnd: 300[m
[32m+[m[32m  m_AmbientSkyColor: {r: 0.212, g: 0.227, b: 0.259, a: 1}[m
[32m+[m[32m  m_AmbientEquatorColor: {r: 0.114, g: 0.125, b: 0.133, a: 1}[m
[32m+[m[32m  m_AmbientGroundColor: {r: 0.047, g: 0.043, b: 0.035, a: 1}[m
[32m+[m[32m  m_AmbientIntensity: 1[m
[32m+[m[32m  m_AmbientMode: 0[m
[32m+[m[32m  m_SubtractiveShadowColor: {r: 0.42, g: 0.478, b: 0.627, a: 1}[m
[32m+[m[32m  m_SkyboxMaterial: {fileID: 10304, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_HaloStrength: 0.5[m
[32m+[m[32m  m_FlareStrength: 1[m
[32m+[m[32m  m_FlareFadeSpeed: 3[m
[32m+[m[32m  m_HaloTexture: {fileID: 0}[m
[32m+[m[32m  m_SpotCookie: {fileID: 10001, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m  m_DefaultReflectionMode: 0[m
[32m+[m[32m  m_DefaultReflectionResolution: 128[m
[32m+[m[32m  m_ReflectionBounces: 1[m
[32m+[m[32m  m_ReflectionIntensity: 1[m
[32m+[m[32m  m_CustomReflection: {fileID: 0}[m
[32m+[m[32m  m_Sun: {fileID: 0}[m
[32m+[m[32m  m_IndirectSpecularColor: {r: 0.44657898, g: 0.4964133, b: 0.5748178, a: 1}[m
[32m+[m[32m  m_UseRadianceAmbientProbe: 0[m
[32m+[m[32m--- !u!157 &3[m
[32m+[m[32mLightmapSettings:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  serializedVersion: 11[m
[32m+[m[32m  m_GIWorkflowMode: 0[m
[32m+[m[32m  m_GISettings:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_BounceScale: 1[m
[32m+[m[32m    m_IndirectOutputScale: 1[m
[32m+[m[32m    m_AlbedoBoost: 1[m
[32m+[m[32m    m_EnvironmentLightingMode: 0[m
[32m+[m[32m    m_EnableBakedLightmaps: 1[m
[32m+[m[32m    m_EnableRealtimeLightmaps: 1[m
[32m+[m[32m  m_LightmapEditorSettings:[m
[32m+[m[32m    serializedVersion: 10[m
[32m+[m[32m    m_Resolution: 2[m
[32m+[m[32m    m_BakeResolution: 40[m
[32m+[m[32m    m_AtlasSize: 1024[m
[32m+[m[32m    m_AO: 0[m
[32m+[m[32m    m_AOMaxDistance: 1[m
[32m+[m[32m    m_CompAOExponent: 1[m
[32m+[m[32m    m_CompAOExponentDirect: 0[m
[32m+[m[32m    m_Padding: 2[m
[32m+[m[32m    m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m    m_LightmapsBakeMode: 1[m
[32m+[m[32m    m_TextureCompression: 1[m
[32m+[m[32m    m_FinalGather: 0[m
[32m+[m[32m    m_FinalGatherFiltering: 1[m
[32m+[m[32m    m_FinalGatherRayCount: 256[m
[32m+[m[32m    m_ReflectionCompression: 2[m
[32m+[m[32m    m_MixedBakeMode: 2[m
[32m+[m[32m    m_BakeBackend: 1[m
[32m+[m[32m    m_PVRSampling: 1[m
[32m+[m[32m    m_PVRDirectSampleCount: 32[m
[32m+[m[32m    m_PVRSampleCount: 500[m
[32m+[m[32m    m_PVRBounces: 2[m
[32m+[m[32m    m_PVRFilterTypeDirect: 0[m
[32m+[m[32m    m_PVRFilterTypeIndirect: 0[m
[32m+[m[32m    m_PVRFilterTypeAO: 0[m
[32m+[m[32m    m_PVRFilteringMode: 1[m
[32m+[m[32m    m_PVRCulling: 1[m
[32m+[m[32m    m_PVRFilteringGaussRadiusDirect: 1[m
[32m+[m[32m    m_PVRFilteringGaussRadiusIndirect: 5[m
[32m+[m[32m    m_PVRFilteringGaussRadiusAO: 2[m
[32m+[m[32m    m_PVRFilteringAtrousPositionSigmaDirect: 0.5[m
[32m+[m[32m    m_PVRFilteringAtrousPositionSigmaIndirect: 2[m
[32m+[m[32m    m_PVRFilteringAtrousPositionSigmaAO: 1[m
[32m+[m[32m    m_ShowResolutionOverlay: 1[m
[32m+[m[32m  m_LightingDataAsset: {fileID: 0}[m
[32m+[m[32m  m_UseShadowmask: 1[m
[32m+[m[32m--- !u!196 &4[m
[32m+[m[32mNavMeshSettings:[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_BuildSettings:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    agentTypeID: 0[m
[32m+[m[32m    agentRadius: 0.5[m
[32m+[m[32m    agentHeight: 2[m
[32m+[m[32m    agentSlope: 45[m
[32m+[m[32m    agentClimb: 0.4[m
[32m+[m[32m    ledgeDropHeight: 0[m
[32m+[m[32m    maxJumpAcrossDistance: 0[m
[32m+[m[32m    minRegionArea: 2[m
[32m+[m[32m    manualCellSize: 0[m
[32m+[m[32m    cellSize: 0.16666667[m
[32m+[m[32m    manualTileSize: 0[m
[32m+[m[32m    tileSize: 256[m
[32m+[m[32m    accuratePlacement: 0[m
[32m+[m[32m    debug:[m
[32m+[m[32m      m_Flags: 0[m
[32m+[m[32m  m_NavMeshData: {fileID: 0}[m
[32m+[m[32m--- !u!1 &322251354[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 322251355}[m
[32m+[m[32m  - component: {fileID: 322251358}[m
[32m+[m[32m  - component: {fileID: 322251357}[m
[32m+[m[32m  - component: {fileID: 322251356}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &322251355[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 322251354}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 1.5, y: 0.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 758258226}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &322251356[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 322251354}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &322251357[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 322251354}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 10303, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &322251358[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 322251354}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1001 &357762935[m
[32m+[m[32mPrefabInstance:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Modification:[m
[32m+[m[32m    m_TransformParent: {fileID: 0}[m
[32m+[m[32m    m_Modifications:[m
[32m+[m[32m    - target: {fileID: 191660435, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_Name[m
[32m+[m[32m      value: Player[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalPosition.x[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalPosition.y[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalPosition.z[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalRotation.x[m
[32m+[m[32m      value: -0[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalRotation.y[m
[32m+[m[32m      value: -0[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalRotation.z[m
[32m+[m[32m      value: -0[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalRotation.w[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_RootOrder[m
[32m+[m[32m      value: 3[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalEulerAnglesHint.x[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalEulerAnglesHint.y[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalEulerAnglesHint.z[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    m_RemovedComponents: [][m
[32m+[m[32m  m_SourcePrefab: {fileID: 100100000, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m--- !u!1 &361783145[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 361783146}[m
[32m+[m[32m  - component: {fileID: 361783149}[m
[32m+[m[32m  - component: {fileID: 361783148}[m
[32m+[m[32m  - component: {fileID: 361783147}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube (1)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &361783146[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 361783145}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: -1.5, y: 0.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 1649474500}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &361783147[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 361783145}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &361783148[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 361783145}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 2100000, guid: 3e79eece95bcf264183f87344299720f, type: 2}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &361783149[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 361783145}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &447113241[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 447113242}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Environment[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &447113242[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 447113241}[m
[32m+[m[32m  m_LocalRotation: {x: 0, y: 0, z: 0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 589442155}[m
[32m+[m[32m  - {fileID: 758258226}[m
[32m+[m[32m  - {fileID: 1649474500}[m
[32m+[m[32m  - {fileID: 985726785}[m
[32m+[m[32m  m_Father: {fileID: 0}[m
[32m+[m[32m  m_RootOrder: 4[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &451913202[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 451913203}[m
[32m+[m[32m  - component: {fileID: 451913206}[m
[32m+[m[32m  - component: {fileID: 451913205}[m
[32m+[m[32m  - component: {fileID: 451913204}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube (1)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &451913203[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 451913202}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: -1.5, y: 0.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 985726785}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &451913204[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 451913202}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &451913205[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 451913202}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 10303, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &451913206[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 451913202}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &485091410[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 485091412}[m
[32m+[m[32m  - component: {fileID: 485091411}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: LevelManager[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!114 &485091411[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 485091410}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: 451d7f0f694268548afd4adfedae22f0, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  spawnPoints:[m
[32m+[m[32m  - {fileID: 998035790}[m
[32m+[m[32m  guards: [][m
[32m+[m[32m--- !u!4 &485091412[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 485091410}[m
[32m+[m[32m  m_LocalRotation: {x: 0, y: 0, z: 0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 1035849310}[m
[32m+[m[32m  - {fileID: 1473508068}[m
[32m+[m[32m  m_Father: {fileID: 0}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &589442151[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 589442155}[m
[32m+[m[32m  - component: {fileID: 589442154}[m
[32m+[m[32m  - component: {fileID: 589442153}[m
[32m+[m[32m  - component: {fileID: 589442152}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Ground[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!64 &589442152[m
[32m+[m[32mMeshCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 589442151}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 3[m
[32m+[m[32m  m_Convex: 0[m
[32m+[m[32m  m_CookingOptions: 14[m
[32m+[m[32m  m_Mesh: {fileID: 10209, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!23 &589442153[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 589442151}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 2100000, guid: 577ffc801fa3b794995ef08e35b7d8ba, type: 2}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &589442154[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 589442151}[m
[32m+[m[32m  m_Mesh: {fileID: 10209, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!4 &589442155[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 589442151}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 10, y: 10, z: 10}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 447113242}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &590726897[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 590726898}[m
[32m+[m[32m  - component: {fileID: 590726901}[m
[32m+[m[32m  - component: {fileID: 590726900}[m
[32m+[m[32m  - component: {fileID: 590726899}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube (2)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &590726898[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 590726897}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 1.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 4, y: 0.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 985726785}[m
[32m+[m[32m  m_RootOrder: 2[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &590726899[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 590726897}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &590726900[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 590726897}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 10303, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &590726901[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 590726897}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &684559206[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 684559208}[m
[32m+[m[32m  - component: {fileID: 684559207}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: GameManager[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!114 &684559207[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 684559206}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: 2c4cd66c48c3c46c6b02c1d43fbcb552, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  NOTE_COLORS:[m
[32m+[m[32m  - {r: 1, g: 0, b: 0, a: 1}[m
[32m+[m[32m  - {r: 0, g: 0, b: 1, a: 1}[m
[32m+[m[32m  - {r: 0, g: 1, b: 0, a: 1}[m
[32m+[m[32m  - {r: 1, g: 0.92156863, b: 0.015686275, a: 1}[m
[32m+[m[32m  NOTE_CURVE:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve: [][m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m--- !u!4 &684559208[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 684559206}[m
[32m+[m[32m  m_LocalRotation: {x: 0, y: 0, z: 0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 0}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &713161344[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 713161345}[m
[32m+[m[32m  - component: {fileID: 713161348}[m
[32m+[m[32m  - component: {fileID: 713161347}[m
[32m+[m[32m  - component: {fileID: 713161346}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube (2)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &713161345[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 713161344}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 1.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 4, y: 0.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 758258226}[m
[32m+[m[32m  m_RootOrder: 2[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &713161346[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 713161344}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &713161347[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 713161344}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 10303, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &713161348[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 713161344}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &740519834[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 740519836}[m
[32m+[m[32m  - component: {fileID: 740519835}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Directional Light[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!108 &740519835[m
[32m+[m[32mLight:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 740519834}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 8[m
[32m+[m[32m  m_Type: 1[m
[32m+[m[32m  m_Color: {r: 1, g: 0.95686275, b: 0.8392157, a: 1}[m
[32m+[m[32m  m_Intensity: 1[m
[32m+[m[32m  m_Range: 10[m
[32m+[m[32m  m_SpotAngle: 30[m
[32m+[m[32m  m_CookieSize: 10[m
[32m+[m[32m  m_Shadows:[m
[32m+[m[32m    m_Type: 2[m
[32m+[m[32m    m_Resolution: -1[m
[32m+[m[32m    m_CustomResolution: -1[m
[32m+[m[32m    m_Strength: 1[m
[32m+[m[32m    m_Bias: 0.05[m
[32m+[m[32m    m_NormalBias: 0.4[m
[32m+[m[32m    m_NearPlane: 0.2[m
[32m+[m[32m  m_Cookie: {fileID: 0}[m
[32m+[m[32m  m_DrawHalo: 0[m
[32m+[m[32m  m_Flare: {fileID: 0}[m
[32m+[m[32m  m_RenderMode: 0[m
[32m+[m[32m  m_CullingMask:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Bits: 4294967295[m
[32m+[m[32m  m_Lightmapping: 4[m
[32m+[m[32m  m_LightShadowCasterMode: 0[m
[32m+[m[32m  m_AreaSize: {x: 1, y: 1}[m
[32m+[m[32m  m_BounceIntensity: 1[m
[32m+[m[32m  m_ColorTemperature: 6570[m
[32m+[m[32m  m_UseColorTemperature: 0[m
[32m+[m[32m  m_ShadowRadius: 0[m
[32m+[m[32m  m_ShadowAngle: 0[m
[32m+[m[32m--- !u!4 &740519836[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 740519834}[m
[32m+[m[32m  m_LocalRotation: {x: 0.40821788, y: -0.23456968, z: 0.10938163, w: 0.8754261}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 3, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 0}[m
[32m+[m[32m  m_RootOrder: 2[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 50, y: -30, z: 0}[m
[32m+[m[32m--- !u!1 &758258225[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 758258226}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Arch (3)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &758258226[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 758258225}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 10}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 2, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 322251355}[m
[32m+[m[32m  - {fileID: 1587525856}[m
[32m+[m[32m  - {fileID: 713161345}[m
[32m+[m[32m  m_Father: {fileID: 447113242}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &985726784[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 985726785}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Arch (5)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &985726785[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 985726784}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: -10}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 2, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 1288063794}[m
[32m+[m[32m  - {fileID: 451913203}[m
[32m+[m[32m  - {fileID: 590726898}[m
[32m+[m[32m  m_Father: {fileID: 447113242}[m
[32m+[m[32m  m_RootOrder: 3[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &998035788[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 998035789}[m
[32m+[m[32m  - component: {fileID: 998035790}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: SpawnPoint[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &998035789[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 998035788}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: -10}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 0.25, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 1473508068}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!114 &998035790[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 998035788}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: bcb395a5241a3934e80899fffd824cc0, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m--- !u!1 &1035849309[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1035849310}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: LevelTransitions[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1035849310[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1035849309}[m
[32m+[m[32m  m_LocalRotation: {x: 0, y: 0, z: 0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 1727168293}[m
[32m+[m[32m  - {fileID: 1543903000}[m
[32m+[m[32m  m_Father: {fileID: 485091412}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &1288063793[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1288063794}[m
[32m+[m[32m  - component: {fileID: 1288063797}[m
[32m+[m[32m  - component: {fileID: 1288063796}[m
[32m+[m[32m  - component: {fileID: 1288063795}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1288063794[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1288063793}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 1.5, y: 0.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 985726785}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &1288063795[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1288063793}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &1288063796[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1288063793}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 10303, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &1288063797[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1288063793}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &1302110469[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1302110470}[m
[32m+[m[32m  - component: {fileID: 1302110473}[m
[32m+[m[32m  - component: {fileID: 1302110472}[m
[32m+[m[32m  - component: {fileID: 1302110471}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube (2)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1302110470[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1302110469}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 1.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 4, y: 0.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 1649474500}[m
[32m+[m[32m  m_RootOrder: 2[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &1302110471[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1302110469}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &1302110472[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1302110469}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 2100000, guid: 3e79eece95bcf264183f87344299720f, type: 2}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &1302110473[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1302110469}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &1473508067[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1473508068}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: SpawnPoints[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1473508068[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1473508067}[m
[32m+[m[32m  m_LocalRotation: {x: 0, y: 0, z: 0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 998035789}[m
[32m+[m[32m  m_Father: {fileID: 485091412}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &1543902999[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1543903000}[m
[32m+[m[32m  - component: {fileID: 1543903002}[m
[32m+[m[32m  - component: {fileID: 1543903001}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: LevelTransition (1)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1543903000[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1543902999}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 10, y: 0, z: 10}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 2, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 1035849310}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!114 &1543903001[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1543902999}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: 7b3a3031df40333409e2c058ef1742b7, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  toLevel: MechanicsTesting1[m
[32m+[m[32m  spawnPointID: 1[m
[32m+[m[32m--- !u!65 &1543903002[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1543902999}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 1[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0.5, z: 0}[m
[32m+[m[32m--- !u!1 &1587525855[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1587525856}[m
[32m+[m[32m  - component: {fileID: 1587525859}[m
[32m+[m[32m  - component: {fileID: 1587525858}[m
[32m+[m[32m  - component: {fileID: 1587525857}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube (1)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1587525856[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1587525855}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: -1.5, y: 0.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 758258226}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &1587525857[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1587525855}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &1587525858[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1587525855}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 10303, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &1587525859[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1587525855}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &1641136969[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1641136970}[m
[32m+[m[32m  - component: {fileID: 1641136973}[m
[32m+[m[32m  - component: {fileID: 1641136972}[m
[32m+[m[32m  - component: {fileID: 1641136971}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1641136970[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1641136969}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 1.5, y: 0.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 1649474500}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &1641136971[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1641136969}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &1641136972[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1641136969}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 2100000, guid: 3e79eece95bcf264183f87344299720f, type: 2}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &1641136973[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1641136969}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &1649474499[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1649474500}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Arch (4)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1649474500[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1649474499}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 10, y: 0, z: 10}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 2, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 1641136970}[m
[32m+[m[32m  - {fileID: 361783146}[m
[32m+[m[32m  - {fileID: 1302110470}[m
[32m+[m[32m  m_Father: {fileID: 447113242}[m
[32m+[m[32m  m_RootOrder: 2[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &1727168289[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1727168293}[m
[32m+[m[32m  - component: {fileID: 1727168290}[m
[32m+[m[32m  - component: {fileID: 1727168294}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: LevelTransition[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!65 &1727168290[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1727168289}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 1[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0.5, z: 0}[m
[32m+[m[32m--- !u!4 &1727168293[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1727168289}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 10}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 2, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 1035849310}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!114 &1727168294[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1727168289}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: 7b3a3031df40333409e2c058ef1742b7, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  toLevel: MechanicsTesting1[m
[32m+[m[32m  spawnPointID: 0[m
[1mdiff --git a/Assets/Scenes/MechanicsTesting/MechanicsTesting0.unity.meta b/Assets/Scenes/MechanicsTesting/MechanicsTesting0.unity.meta[m
[1mnew file mode 100644[m
[1mindex 0000000..d18d90b[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scenes/MechanicsTesting/MechanicsTesting0.unity.meta[m
[36m@@ -0,0 +1,7 @@[m
[32m+[m[32mfileFormatVersion: 2[m
[32m+[m[32mguid: e23281db68bf41d4486c81842718c8f4[m
[32m+[m[32mDefaultImporter:[m
[32m+[m[32m  externalObjects: {}[m
[32m+[m[32m  userData:[m[41m [m
[32m+[m[32m  assetBundleName:[m[41m [m
[32m+[m[32m  assetBundleVariant:[m[41m [m
[1mdiff --git a/Assets/Scenes/MechanicsTesting/MechanicsTesting1.unity b/Assets/Scenes/MechanicsTesting/MechanicsTesting1.unity[m
[1mnew file mode 100644[m
[1mindex 0000000..15a6d80[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scenes/MechanicsTesting/MechanicsTesting1.unity[m
[36m@@ -0,0 +1,1595 @@[m
[32m+[m[32m%YAML 1.1[m
[32m+[m[32m%TAG !u! tag:unity3d.com,2011:[m
[32m+[m[32m--- !u!29 &1[m
[32m+[m[32mOcclusionCullingSettings:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_OcclusionBakeSettings:[m
[32m+[m[32m    smallestOccluder: 5[m
[32m+[m[32m    smallestHole: 0.25[m
[32m+[m[32m    backfaceThreshold: 100[m
[32m+[m[32m  m_SceneGUID: 00000000000000000000000000000000[m
[32m+[m[32m  m_OcclusionCullingData: {fileID: 0}[m
[32m+[m[32m--- !u!104 &2[m
[32m+[m[32mRenderSettings:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  serializedVersion: 9[m
[32m+[m[32m  m_Fog: 0[m
[32m+[m[32m  m_FogColor: {r: 0.5, g: 0.5, b: 0.5, a: 1}[m
[32m+[m[32m  m_FogMode: 3[m
[32m+[m[32m  m_FogDensity: 0.01[m
[32m+[m[32m  m_LinearFogStart: 0[m
[32m+[m[32m  m_LinearFogEnd: 300[m
[32m+[m[32m  m_AmbientSkyColor: {r: 0.212, g: 0.227, b: 0.259, a: 1}[m
[32m+[m[32m  m_AmbientEquatorColor: {r: 0.114, g: 0.125, b: 0.133, a: 1}[m
[32m+[m[32m  m_AmbientGroundColor: {r: 0.047, g: 0.043, b: 0.035, a: 1}[m
[32m+[m[32m  m_AmbientIntensity: 1[m
[32m+[m[32m  m_AmbientMode: 0[m
[32m+[m[32m  m_SubtractiveShadowColor: {r: 0.42, g: 0.478, b: 0.627, a: 1}[m
[32m+[m[32m  m_SkyboxMaterial: {fileID: 10304, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_HaloStrength: 0.5[m
[32m+[m[32m  m_FlareStrength: 1[m
[32m+[m[32m  m_FlareFadeSpeed: 3[m
[32m+[m[32m  m_HaloTexture: {fileID: 0}[m
[32m+[m[32m  m_SpotCookie: {fileID: 10001, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m  m_DefaultReflectionMode: 0[m
[32m+[m[32m  m_DefaultReflectionResolution: 128[m
[32m+[m[32m  m_ReflectionBounces: 1[m
[32m+[m[32m  m_ReflectionIntensity: 1[m
[32m+[m[32m  m_CustomReflection: {fileID: 0}[m
[32m+[m[32m  m_Sun: {fileID: 0}[m
[32m+[m[32m  m_IndirectSpecularColor: {r: 0.44657898, g: 0.4964133, b: 0.5748178, a: 1}[m
[32m+[m[32m  m_UseRadianceAmbientProbe: 0[m
[32m+[m[32m--- !u!157 &3[m
[32m+[m[32mLightmapSettings:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  serializedVersion: 11[m
[32m+[m[32m  m_GIWorkflowMode: 0[m
[32m+[m[32m  m_GISettings:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_BounceScale: 1[m
[32m+[m[32m    m_IndirectOutputScale: 1[m
[32m+[m[32m    m_AlbedoBoost: 1[m
[32m+[m[32m    m_EnvironmentLightingMode: 0[m
[32m+[m[32m    m_EnableBakedLightmaps: 1[m
[32m+[m[32m    m_EnableRealtimeLightmaps: 1[m
[32m+[m[32m  m_LightmapEditorSettings:[m
[32m+[m[32m    serializedVersion: 10[m
[32m+[m[32m    m_Resolution: 2[m
[32m+[m[32m    m_BakeResolution: 40[m
[32m+[m[32m    m_AtlasSize: 1024[m
[32m+[m[32m    m_AO: 0[m
[32m+[m[32m    m_AOMaxDistance: 1[m
[32m+[m[32m    m_CompAOExponent: 1[m
[32m+[m[32m    m_CompAOExponentDirect: 0[m
[32m+[m[32m    m_Padding: 2[m
[32m+[m[32m    m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m    m_LightmapsBakeMode: 1[m
[32m+[m[32m    m_TextureCompression: 1[m
[32m+[m[32m    m_FinalGather: 0[m
[32m+[m[32m    m_FinalGatherFiltering: 1[m
[32m+[m[32m    m_FinalGatherRayCount: 256[m
[32m+[m[32m    m_ReflectionCompression: 2[m
[32m+[m[32m    m_MixedBakeMode: 2[m
[32m+[m[32m    m_BakeBackend: 1[m
[32m+[m[32m    m_PVRSampling: 1[m
[32m+[m[32m    m_PVRDirectSampleCount: 32[m
[32m+[m[32m    m_PVRSampleCount: 500[m
[32m+[m[32m    m_PVRBounces: 2[m
[32m+[m[32m    m_PVRFilterTypeDirect: 0[m
[32m+[m[32m    m_PVRFilterTypeIndirect: 0[m
[32m+[m[32m    m_PVRFilterTypeAO: 0[m
[32m+[m[32m    m_PVRFilteringMode: 1[m
[32m+[m[32m    m_PVRCulling: 1[m
[32m+[m[32m    m_PVRFilteringGaussRadiusDirect: 1[m
[32m+[m[32m    m_PVRFilteringGaussRadiusIndirect: 5[m
[32m+[m[32m    m_PVRFilteringGaussRadiusAO: 2[m
[32m+[m[32m    m_PVRFilteringAtrousPositionSigmaDirect: 0.5[m
[32m+[m[32m    m_PVRFilteringAtrousPositionSigmaIndirect: 2[m
[32m+[m[32m    m_PVRFilteringAtrousPositionSigmaAO: 1[m
[32m+[m[32m    m_ShowResolutionOverlay: 1[m
[32m+[m[32m  m_LightingDataAsset: {fileID: 0}[m
[32m+[m[32m  m_UseShadowmask: 1[m
[32m+[m[32m--- !u!196 &4[m
[32m+[m[32mNavMeshSettings:[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_BuildSettings:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    agentTypeID: 0[m
[32m+[m[32m    agentRadius: 0.5[m
[32m+[m[32m    agentHeight: 2[m
[32m+[m[32m    agentSlope: 45[m
[32m+[m[32m    agentClimb: 0.4[m
[32m+[m[32m    ledgeDropHeight: 0[m
[32m+[m[32m    maxJumpAcrossDistance: 0[m
[32m+[m[32m    minRegionArea: 2[m
[32m+[m[32m    manualCellSize: 0[m
[32m+[m[32m    cellSize: 0.16666667[m
[32m+[m[32m    manualTileSize: 0[m
[32m+[m[32m    tileSize: 256[m
[32m+[m[32m    accuratePlacement: 0[m
[32m+[m[32m    debug:[m
[32m+[m[32m      m_Flags: 0[m
[32m+[m[32m  m_NavMeshData: {fileID: 0}[m
[32m+[m[32m--- !u!1 &74505284[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 74505285}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Arch (5)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &74505285[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 74505284}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: -10}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 2, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 796341103}[m
[32m+[m[32m  - {fileID: 369299006}[m
[32m+[m[32m  - {fileID: 400983897}[m
[32m+[m[32m  m_Father: {fileID: 447113242}[m
[32m+[m[32m  m_RootOrder: 2[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &285933341[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 285933342}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Arch (3)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &285933342[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 285933341}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 10}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 2, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 974402445}[m
[32m+[m[32m  - {fileID: 2025210364}[m
[32m+[m[32m  - {fileID: 1976581955}[m
[32m+[m[32m  m_Father: {fileID: 447113242}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1001 &357762935[m
[32m+[m[32mPrefabInstance:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Modification:[m
[32m+[m[32m    m_TransformParent: {fileID: 0}[m
[32m+[m[32m    m_Modifications:[m
[32m+[m[32m    - target: {fileID: 191660435, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_Name[m
[32m+[m[32m      value: Player[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalPosition.x[m
[32m+[m[32m      value: -5.756775[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalPosition.y[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalPosition.z[m
[32m+[m[32m      value: -6.991519[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalRotation.x[m
[32m+[m[32m      value: -0[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalRotation.y[m
[32m+[m[32m      value: -0[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalRotation.z[m
[32m+[m[32m      value: -0[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalRotation.w[m
[32m+[m[32m      value: 1[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_RootOrder[m
[32m+[m[32m      value: 3[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalEulerAnglesHint.x[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalEulerAnglesHint.y[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    - target: {fileID: 191660434, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m      propertyPath: m_LocalEulerAnglesHint.z[m
[32m+[m[32m      value: 0[m
[32m+[m[32m      objectReference: {fileID: 0}[m
[32m+[m[32m    m_RemovedComponents: [][m
[32m+[m[32m  m_SourcePrefab: {fileID: 100100000, guid: 74d6c2fd5f712d44e8342e6b94738c12, type: 3}[m
[32m+[m[32m--- !u!1 &369299005[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 369299006}[m
[32m+[m[32m  - component: {fileID: 369299009}[m
[32m+[m[32m  - component: {fileID: 369299008}[m
[32m+[m[32m  - component: {fileID: 369299007}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube (1)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &369299006[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 369299005}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: -1.5, y: 0.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 74505285}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &369299007[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 369299005}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &369299008[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 369299005}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 10303, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &369299009[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 369299005}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &400983896[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 400983897}[m
[32m+[m[32m  - component: {fileID: 400983900}[m
[32m+[m[32m  - component: {fileID: 400983899}[m
[32m+[m[32m  - component: {fileID: 400983898}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube (2)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &400983897[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 400983896}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 1.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 4, y: 0.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 74505285}[m
[32m+[m[32m  m_RootOrder: 2[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &400983898[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 400983896}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &400983899[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 400983896}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 10303, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &400983900[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 400983896}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &447113241[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 447113242}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Environment[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &447113242[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 447113241}[m
[32m+[m[32m  m_LocalRotation: {x: 0, y: 0, z: 0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 285933342}[m
[32m+[m[32m  - {fileID: 1944337698}[m
[32m+[m[32m  - {fileID: 74505285}[m
[32m+[m[32m  - {fileID: 589442155}[m
[32m+[m[32m  m_Father: {fileID: 0}[m
[32m+[m[32m  m_RootOrder: 4[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &485091410[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 485091412}[m
[32m+[m[32m  - component: {fileID: 485091411}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: LevelManager[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!114 &485091411[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 485091410}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: 451d7f0f694268548afd4adfedae22f0, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  spawnPoints:[m
[32m+[m[32m  - {fileID: 998035790}[m
[32m+[m[32m  - {fileID: 1493991152}[m
[32m+[m[32m  guards: [][m
[32m+[m[32m--- !u!4 &485091412[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 485091410}[m
[32m+[m[32m  m_LocalRotation: {x: 0, y: 0, z: 0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 1035849310}[m
[32m+[m[32m  - {fileID: 1473508068}[m
[32m+[m[32m  m_Father: {fileID: 0}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &589442151[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 589442155}[m
[32m+[m[32m  - component: {fileID: 589442154}[m
[32m+[m[32m  - component: {fileID: 589442153}[m
[32m+[m[32m  - component: {fileID: 589442152}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Ground[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!64 &589442152[m
[32m+[m[32mMeshCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 589442151}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 3[m
[32m+[m[32m  m_Convex: 0[m
[32m+[m[32m  m_CookingOptions: 14[m
[32m+[m[32m  m_Mesh: {fileID: 10209, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!23 &589442153[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 589442151}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 2100000, guid: 577ffc801fa3b794995ef08e35b7d8ba, type: 2}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &589442154[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 589442151}[m
[32m+[m[32m  m_Mesh: {fileID: 10209, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!4 &589442155[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 589442151}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 10, y: 10, z: 10}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 447113242}[m
[32m+[m[32m  m_RootOrder: 3[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &684559206[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 684559208}[m
[32m+[m[32m  - component: {fileID: 684559207}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: GameManager[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!114 &684559207[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 684559206}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: 2c4cd66c48c3c46c6b02c1d43fbcb552, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  NOTE_COLORS:[m
[32m+[m[32m  - {r: 1, g: 0, b: 0, a: 1}[m
[32m+[m[32m  - {r: 0, g: 0, b: 1, a: 1}[m
[32m+[m[32m  - {r: 0, g: 1, b: 0, a: 1}[m
[32m+[m[32m  - {r: 1, g: 0.92156863, b: 0.015686275, a: 1}[m
[32m+[m[32m  NOTE_CURVE:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Curve: [][m
[32m+[m[32m    m_PreInfinity: 2[m
[32m+[m[32m    m_PostInfinity: 2[m
[32m+[m[32m    m_RotationOrder: 4[m
[32m+[m[32m--- !u!4 &684559208[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 684559206}[m
[32m+[m[32m  m_LocalRotation: {x: 0, y: 0, z: 0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 0}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &740519834[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 740519836}[m
[32m+[m[32m  - component: {fileID: 740519835}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Directional Light[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!108 &740519835[m
[32m+[m[32mLight:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 740519834}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 8[m
[32m+[m[32m  m_Type: 1[m
[32m+[m[32m  m_Color: {r: 1, g: 0.95686275, b: 0.8392157, a: 1}[m
[32m+[m[32m  m_Intensity: 1[m
[32m+[m[32m  m_Range: 10[m
[32m+[m[32m  m_SpotAngle: 30[m
[32m+[m[32m  m_CookieSize: 10[m
[32m+[m[32m  m_Shadows:[m
[32m+[m[32m    m_Type: 2[m
[32m+[m[32m    m_Resolution: -1[m
[32m+[m[32m    m_CustomResolution: -1[m
[32m+[m[32m    m_Strength: 1[m
[32m+[m[32m    m_Bias: 0.05[m
[32m+[m[32m    m_NormalBias: 0.4[m
[32m+[m[32m    m_NearPlane: 0.2[m
[32m+[m[32m  m_Cookie: {fileID: 0}[m
[32m+[m[32m  m_DrawHalo: 0[m
[32m+[m[32m  m_Flare: {fileID: 0}[m
[32m+[m[32m  m_RenderMode: 0[m
[32m+[m[32m  m_CullingMask:[m
[32m+[m[32m    serializedVersion: 2[m
[32m+[m[32m    m_Bits: 4294967295[m
[32m+[m[32m  m_Lightmapping: 4[m
[32m+[m[32m  m_LightShadowCasterMode: 0[m
[32m+[m[32m  m_AreaSize: {x: 1, y: 1}[m
[32m+[m[32m  m_BounceIntensity: 1[m
[32m+[m[32m  m_ColorTemperature: 6570[m
[32m+[m[32m  m_UseColorTemperature: 0[m
[32m+[m[32m  m_ShadowRadius: 0[m
[32m+[m[32m  m_ShadowAngle: 0[m
[32m+[m[32m--- !u!4 &740519836[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 740519834}[m
[32m+[m[32m  m_LocalRotation: {x: 0.40821788, y: -0.23456968, z: 0.10938163, w: 0.8754261}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 3, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 0}[m
[32m+[m[32m  m_RootOrder: 2[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 50, y: -30, z: 0}[m
[32m+[m[32m--- !u!1 &796341102[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 796341103}[m
[32m+[m[32m  - component: {fileID: 796341106}[m
[32m+[m[32m  - component: {fileID: 796341105}[m
[32m+[m[32m  - component: {fileID: 796341104}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &796341103[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 796341102}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 1.5, y: 0.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 74505285}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &796341104[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 796341102}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &796341105[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 796341102}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 10303, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &796341106[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 796341102}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &834571339[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 834571340}[m
[32m+[m[32m  - component: {fileID: 834571343}[m
[32m+[m[32m  - component: {fileID: 834571342}[m
[32m+[m[32m  - component: {fileID: 834571341}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube (1)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &834571340[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 834571339}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: -1.5, y: 0.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 1944337698}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &834571341[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 834571339}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &834571342[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 834571339}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 2100000, guid: 3e79eece95bcf264183f87344299720f, type: 2}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &834571343[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 834571339}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &974402444[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 974402445}[m
[32m+[m[32m  - component: {fileID: 974402448}[m
[32m+[m[32m  - component: {fileID: 974402447}[m
[32m+[m[32m  - component: {fileID: 974402446}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &974402445[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 974402444}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 1.5, y: 0.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 285933342}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &974402446[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 974402444}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &974402447[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 974402444}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 10303, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &974402448[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 974402444}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &998035788[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 998035789}[m
[32m+[m[32m  - component: {fileID: 998035790}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: SpawnPoint[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &998035789[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 998035788}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 10}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 0.25, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 1473508068}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!114 &998035790[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 998035788}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: bcb395a5241a3934e80899fffd824cc0, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m--- !u!1 &1035849309[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1035849310}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: LevelTransitions[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1035849310[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1035849309}[m
[32m+[m[32m  m_LocalRotation: {x: 0, y: 0, z: 0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 1727168293}[m
[32m+[m[32m  m_Father: {fileID: 485091412}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &1473508067[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1473508068}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: SpawnPoints[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1473508068[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1473508067}[m
[32m+[m[32m  m_LocalRotation: {x: 0, y: 0, z: 0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 998035789}[m
[32m+[m[32m  - {fileID: 1493991151}[m
[32m+[m[32m  m_Father: {fileID: 485091412}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &1493991150[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1493991151}[m
[32m+[m[32m  - component: {fileID: 1493991152}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: SpawnPoint (1)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1493991151[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1493991150}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 10, y: 0, z: 10}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 0.25, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 1473508068}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!114 &1493991152[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1493991150}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: bcb395a5241a3934e80899fffd824cc0, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m--- !u!1 &1527026817[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1527026818}[m
[32m+[m[32m  - component: {fileID: 1527026821}[m
[32m+[m[32m  - component: {fileID: 1527026820}[m
[32m+[m[32m  - component: {fileID: 1527026819}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube (2)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1527026818[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1527026817}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 1.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 4, y: 0.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 1944337698}[m
[32m+[m[32m  m_RootOrder: 2[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &1527026819[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1527026817}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &1527026820[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1527026817}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 2100000, guid: 3e79eece95bcf264183f87344299720f, type: 2}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &1527026821[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1527026817}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &1727168289[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1727168293}[m
[32m+[m[32m  - component: {fileID: 1727168290}[m
[32m+[m[32m  - component: {fileID: 1727168294}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: LevelTransition[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!65 &1727168290[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1727168289}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 1[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0.5, z: 0}[m
[32m+[m[32m--- !u!4 &1727168293[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1727168289}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 0, z: -10}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 2, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 1035849310}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!114 &1727168294[m
[32m+[m[32mMonoBehaviour:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1727168289}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_EditorHideFlags: 0[m
[32m+[m[32m  m_Script: {fileID: 11500000, guid: 7b3a3031df40333409e2c058ef1742b7, type: 3}[m
[32m+[m[32m  m_Name:[m[41m [m
[32m+[m[32m  m_EditorClassIdentifier:[m[41m [m
[32m+[m[32m  toLevel: MechanicsTesting0[m
[32m+[m[32m  spawnPointID: 0[m
[32m+[m[32m--- !u!1 &1924359157[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1924359158}[m
[32m+[m[32m  - component: {fileID: 1924359161}[m
[32m+[m[32m  - component: {fileID: 1924359160}[m
[32m+[m[32m  - component: {fileID: 1924359159}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1924359158[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1924359157}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 1.5, y: 0.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 1944337698}[m
[32m+[m[32m  m_RootOrder: 0[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &1924359159[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1924359157}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &1924359160[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1924359157}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 2100000, guid: 3e79eece95bcf264183f87344299720f, type: 2}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &1924359161[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1924359157}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &1944337697[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1944337698}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Arch (4)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1944337698[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1944337697}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 10, y: 0, z: 10}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 2, z: 1}[m
[32m+[m[32m  m_Children:[m
[32m+[m[32m  - {fileID: 1924359158}[m
[32m+[m[32m  - {fileID: 834571340}[m
[32m+[m[32m  - {fileID: 1527026818}[m
[32m+[m[32m  m_Father: {fileID: 447113242}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!1 &1976581954[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 1976581955}[m
[32m+[m[32m  - component: {fileID: 1976581958}[m
[32m+[m[32m  - component: {fileID: 1976581957}[m
[32m+[m[32m  - component: {fileID: 1976581956}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube (2)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &1976581955[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1976581954}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: 0, y: 1.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 4, y: 0.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 285933342}[m
[32m+[m[32m  m_RootOrder: 2[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &1976581956[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1976581954}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &1976581957[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1976581954}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 10303, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &1976581958[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 1976581954}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[32m+[m[32m--- !u!1 &2025210363[m
[32m+[m[32mGameObject:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_Component:[m
[32m+[m[32m  - component: {fileID: 2025210364}[m
[32m+[m[32m  - component: {fileID: 2025210367}[m
[32m+[m[32m  - component: {fileID: 2025210366}[m
[32m+[m[32m  - component: {fileID: 2025210365}[m
[32m+[m[32m  m_Layer: 0[m
[32m+[m[32m  m_Name: Cube (1)[m
[32m+[m[32m  m_TagString: Untagged[m
[32m+[m[32m  m_Icon: {fileID: 0}[m
[32m+[m[32m  m_NavMeshLayer: 0[m
[32m+[m[32m  m_StaticEditorFlags: 0[m
[32m+[m[32m  m_IsActive: 1[m
[32m+[m[32m--- !u!4 &2025210364[m
[32m+[m[32mTransform:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 2025210363}[m
[32m+[m[32m  m_LocalRotation: {x: -0, y: -0, z: -0, w: 1}[m
[32m+[m[32m  m_LocalPosition: {x: -1.5, y: 0.75, z: 0}[m
[32m+[m[32m  m_LocalScale: {x: 1, y: 1.5, z: 1}[m
[32m+[m[32m  m_Children: [][m
[32m+[m[32m  m_Father: {fileID: 285933342}[m
[32m+[m[32m  m_RootOrder: 1[m
[32m+[m[32m  m_LocalEulerAnglesHint: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!65 &2025210365[m
[32m+[m[32mBoxCollider:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 2025210363}[m
[32m+[m[32m  m_Material: {fileID: 0}[m
[32m+[m[32m  m_IsTrigger: 0[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  m_Size: {x: 1, y: 1, z: 1}[m
[32m+[m[32m  m_Center: {x: 0, y: 0, z: 0}[m
[32m+[m[32m--- !u!23 &2025210366[m
[32m+[m[32mMeshRenderer:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 2025210363}[m
[32m+[m[32m  m_Enabled: 1[m
[32m+[m[32m  m_CastShadows: 1[m
[32m+[m[32m  m_ReceiveShadows: 1[m
[32m+[m[32m  m_DynamicOccludee: 1[m
[32m+[m[32m  m_MotionVectors: 1[m
[32m+[m[32m  m_LightProbeUsage: 1[m
[32m+[m[32m  m_ReflectionProbeUsage: 1[m
[32m+[m[32m  m_RenderingLayerMask: 1[m
[32m+[m[32m  m_RendererPriority: 0[m
[32m+[m[32m  m_Materials:[m
[32m+[m[32m  - {fileID: 10303, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_StaticBatchInfo:[m
[32m+[m[32m    firstSubMesh: 0[m
[32m+[m[32m    subMeshCount: 0[m
[32m+[m[32m  m_StaticBatchRoot: {fileID: 0}[m
[32m+[m[32m  m_ProbeAnchor: {fileID: 0}[m
[32m+[m[32m  m_LightProbeVolumeOverride: {fileID: 0}[m
[32m+[m[32m  m_ScaleInLightmap: 1[m
[32m+[m[32m  m_PreserveUVs: 0[m
[32m+[m[32m  m_IgnoreNormalsForChartDetection: 0[m
[32m+[m[32m  m_ImportantGI: 0[m
[32m+[m[32m  m_StitchLightmapSeams: 0[m
[32m+[m[32m  m_SelectedEditorRenderState: 3[m
[32m+[m[32m  m_MinimumChartSize: 4[m
[32m+[m[32m  m_AutoUVMaxDistance: 0.5[m
[32m+[m[32m  m_AutoUVMaxAngle: 89[m
[32m+[m[32m  m_LightmapParameters: {fileID: 0}[m
[32m+[m[32m  m_SortingLayerID: 0[m
[32m+[m[32m  m_SortingLayer: 0[m
[32m+[m[32m  m_SortingOrder: 0[m
[32m+[m[32m--- !u!33 &2025210367[m
[32m+[m[32mMeshFilter:[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_GameObject: {fileID: 2025210363}[m
[32m+[m[32m  m_Mesh: {fileID: 10202, guid: 0000000000000000e000000000000000, type: 0}[m
[1mdiff --git a/Assets/Scenes/MechanicsTesting/MechanicsTesting1.unity.meta b/Assets/Scenes/MechanicsTesting/MechanicsTesting1.unity.meta[m
[1mnew file mode 100644[m
[1mindex 0000000..135129e[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scenes/MechanicsTesting/MechanicsTesting1.unity.meta[m
[36m@@ -0,0 +1,7 @@[m
[32m+[m[32mfileFormatVersion: 2[m
[32m+[m[32mguid: 7332de914921c364487ec84875bdaf3e[m
[32m+[m[32mDefaultImporter:[m
[32m+[m[32m  externalObjects: {}[m
[32m+[m[32m  userData:[m[41m [m
[32m+[m[32m  assetBundleName:[m[41m [m
[32m+[m[32m  assetBundleVariant:[m[41m [m
[1mdiff --git a/Assets/Scenes/MechanicsTesting/Red.mat b/Assets/Scenes/MechanicsTesting/Red.mat[m
[1mnew file mode 100644[m
[1mindex 0000000..bf1d64a[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scenes/MechanicsTesting/Red.mat[m
[36m@@ -0,0 +1,77 @@[m
[32m+[m[32m%YAML 1.1[m
[32m+[m[32m%TAG !u! tag:unity3d.com,2011:[m
[32m+[m[32m--- !u!21 &2100000[m
[32m+[m[32mMaterial:[m
[32m+[m[32m  serializedVersion: 6[m
[32m+[m[32m  m_ObjectHideFlags: 0[m
[32m+[m[32m  m_CorrespondingSourceObject: {fileID: 0}[m
[32m+[m[32m  m_PrefabInstance: {fileID: 0}[m
[32m+[m[32m  m_PrefabAsset: {fileID: 0}[m
[32m+[m[32m  m_Name: Red[m
[32m+[m[32m  m_Shader: {fileID: 46, guid: 0000000000000000f000000000000000, type: 0}[m
[32m+[m[32m  m_ShaderKeywords:[m[41m [m
[32m+[m[32m  m_LightmapFlags: 4[m
[32m+[m[32m  m_EnableInstancingVariants: 0[m
[32m+[m[32m  m_DoubleSidedGI: 0[m
[32m+[m[32m  m_CustomRenderQueue: -1[m
[32m+[m[32m  stringTagMap: {}[m
[32m+[m[32m  disabledShaderPasses: [][m
[32m+[m[32m  m_SavedProperties:[m
[32m+[m[32m    serializedVersion: 3[m
[32m+[m[32m    m_TexEnvs:[m
[32m+[m[32m    - _BumpMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _DetailAlbedoMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _DetailMask:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _DetailNormalMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _EmissionMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _MainTex:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _MetallicGlossMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _OcclusionMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    - _ParallaxMap:[m
[32m+[m[32m        m_Texture: {fileID: 0}[m
[32m+[m[32m        m_Scale: {x: 1, y: 1}[m
[32m+[m[32m        m_Offset: {x: 0, y: 0}[m
[32m+[m[32m    m_Floats:[m
[32m+[m[32m    - _BumpScale: 1[m
[32m+[m[32m    - _Cutoff: 0.5[m
[32m+[m[32m    - _DetailNormalMapScale: 1[m
[32m+[m[32m    - _DstBlend: 0[m
[32m+[m[32m    - _GlossMapScale: 1[m
[32m+[m[32m    - _Glossiness: 0.5[m
[32m+[m[32m    - _GlossyReflections: 1[m
[32m+[m[32m    - _Metallic: 0[m
[32m+[m[32m    - _Mode: 0[m
[32m+[m[32m    - _OcclusionStrength: 1[m
[32m+[m[32m    - _Parallax: 0.02[m
[32m+[m[32m    - _SmoothnessTextureChannel: 0[m
[32m+[m[32m    - _SpecularHighlights: 1[m
[32m+[m[32m    - _SrcBlend: 1[m
[32m+[m[32m    - _UVSec: 0[m
[32m+[m[32m    - _ZWrite: 1[m
[32m+[m[32m    m_Colors:[m
[32m+[m[32m    - _Color: {r: 1, g: 0, b: 0, a: 1}[m
[32m+[m[32m    - _EmissionColor: {r: 0, g: 0, b: 0, a: 1}[m
[1mdiff --git a/Assets/Scenes/MechanicsTesting/Red.mat.meta b/Assets/Scenes/MechanicsTesting/Red.mat.meta[m
[1mnew file mode 100644[m
[1mindex 0000000..4383548[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scenes/MechanicsTesting/Red.mat.meta[m
[36m@@ -0,0 +1,8 @@[m
[32m+[m[32mfileFormatVersion: 2[m
[32m+[m[32mguid: f6769b67523ad644eb59686999191a55[m
[32m+[m[32mNativeFormatImporter:[m
[32m+[m[32m  externalObjects: {}[m
[32m+[m[32m  mainObjectFileID: 2100000[m
[32m+[m[32m  userData:[m[41m [m
[32m+[m[32m  assetBundleName:[m[41m [m
[32m+[m[32m  assetBundleVariant:[m[41m [m
[1mdiff --git a/Assets/Scripts/ApplicationContoller.cs b/Assets/Scripts/ApplicationContoller.cs[m
[1mdeleted file mode 100644[m
[1mindex 4544caa..0000000[m
[1m--- a/Assets/Scripts/ApplicationContoller.cs[m
[1m+++ /dev/null[m
[36m@@ -1,25 +0,0 @@[m
[31m-﻿/*	Author: Kostas Sfikas[m
[31m-	Date: April 2017[m
[31m-	Language: c#[m
[31m-	Platform: Unity 5.5.0 f3 (personal edition) */[m
[31m-[m
[31m-using System.Collections;[m
[31m-using System.Collections.Generic;[m
[31m-using UnityEngine;[m
[31m-[m
[31m-public class ApplicationContoller : MonoBehaviour {[m
[31m-	/* This class just "listens" for the ESC key and if it is pressed it exits/quits the application.[m
[31m-	This will not work in the editor, it will work only while a build is running.*/[m
[31m-[m
[31m-	// Use this for initialization[m
[31m-	void Start () {[m
[31m-		// nothing is needed here[m
[31m-	}[m
[31m-	[m
[31m-	// Update is called once per frame[m
[31m-	void Update () {[m
[31m-		if (Input.GetKeyDown (KeyCode.Escape)) {[m
[31m-			Application.Quit ();[m
[31m-		}[m
[31m-	}[m
[31m-}[m
[1mdiff --git a/Assets/Scripts/ApplicationContoller.cs.meta b/Assets/Scripts/ApplicationContoller.cs.meta[m
[1mdeleted file mode 100644[m
[1mindex e53c5a7..0000000[m
[1m--- a/Assets/Scripts/ApplicationContoller.cs.meta[m
[1m+++ /dev/null[m
[36m@@ -1,12 +0,0 @@[m
[31m-fileFormatVersion: 2[m
[31m-guid: 073367ba007d1c949944918ed3db4280[m
[31m-timeCreated: 1491327188[m
[31m-licenseType: Free[m
[31m-MonoImporter:[m
[31m-  serializedVersion: 2[m
[31m-  defaultReferences: [][m
[31m-  executionOrder: 0[m
[31m-  icon: {instanceID: 0}[m
[31m-  userData: [m
[31m-  assetBundleName: [m
[31m-  assetBundleVariant: [m
[1mdiff --git a/Assets/Scripts/CameraController.cs b/Assets/Scripts/CameraController.cs[m
[1mdeleted file mode 100644[m
[1mindex b7fce94..0000000[m
[1m--- a/Assets/Scripts/CameraController.cs[m
[1m+++ /dev/null[m
[36m@@ -1,23 +0,0 @@[m
[31m-﻿using System.Collections;[m
[31m-using System.Collections.Generic;[m
[31m-using UnityEngine;[m
[31m-[m
[31m-public class CameraController : MonoBehaviour {[m
[31m-[m
[31m-	Vector3 lookPoint;[m
[31m-	Vector3 camPos;[m
[31m-	// Use this for initialization[m
[31m-	void Start () {[m
[31m-		lookPoint = new Vector3 (0.0f, 0.0f, 0.0f);[m
[31m-	}[m
[31m-	[m
[31m-	// Update is called once per frame[m
[31m-	void Update () {[m
[31m-		float xx = Mathf.Sin (Time.time/10.0f) * 2.5f;[m
[31m-		float zz = Mathf.Cos (Time.time/10.0f) * 2.5f;[m
[31m-		float yy = Mathf.Sin (Time.time/4.0f) + 1.0f;[m
[31m-		camPos = new Vector3 (xx, yy, zz);[m
[31m-		transform.position = camPos;[m
[31m-		transform.LookAt (lookPoint);[m
[31m-	}[m
[31m-}[m
[1mdiff --git a/Assets/Scripts/CameraController.cs.meta b/Assets/Scripts/CameraController.cs.meta[m
[1mdeleted file mode 100644[m
[1mindex 4b889d7..0000000[m
[1m--- a/Assets/Scripts/CameraController.cs.meta[m
[1m+++ /dev/null[m
[36m@@ -1,12 +0,0 @@[m
[31m-fileFormatVersion: 2[m
[31m-guid: b6eb0ac3624356149a4003f71c793f1d[m
[31m-timeCreated: 1490776197[m
[31m-licenseType: Free[m
[31m-MonoImporter:[m
[31m-  serializedVersion: 2[m
[31m-  defaultReferences: [][m
[31m-  executionOrder: 0[m
[31m-  icon: {instanceID: 0}[m
[31m-  userData: [m
[31m-  assetBundleName: [m
[31m-  assetBundleVariant: [m
[1mdiff --git a/Assets/Scripts/GameManager.cs b/Assets/Scripts/GameManager.cs[m
[1mdeleted file mode 100644[m
[1mindex 50ecfd4..0000000[m
[1m--- a/Assets/Scripts/GameManager.cs[m
[1m+++ /dev/null[m
[36m@@ -1,31 +0,0 @@[m
[31m-﻿using System.Collections;[m
[31m-using System.Collections.Generic;[m
[31m-using UnityEngine;[m
[31m-[m
[31m-public class GameManager : MonoBehaviour[m
[31m-{[m
[31m-	public static GameManager instance;[m
[31m-	public Player player;[m
[31m-	public Hashtable sharedData;[m
[31m-	public LevelManager levelManager;[m
[31m-	public Teacher teacher;[m
[31m-	public Student student;[m
[31m-	public Human[] humans;[m
[31m-[m
[31m-	public Color[] NOTE_COLORS = { Color.red, Color.blue, Color.green, Color.yellow };[m
[31m-	public AnimationCurve NOTE_CURVE;[m
[31m-[m
[31m-	private void Awake()[m
[31m-	{[m
[31m-		if (instance == null)[m
[31m-			instance = this;[m
[31m-		else if (instance != this)[m
[31m-			Destroy(gameObject);[m
[31m-		DontDestroyOnLoad(gameObject);[m
[31m-	}[m
[31m-[m
[31m-	private void Start()[m
[31m-	{[m
[31m-		player = Object.FindObjectOfType<Player>();[m
[31m-	}[m
[31m-}[m
[1mdiff --git a/Assets/Scripts/Human.cs b/Assets/Scripts/Human.cs[m
[1mindex ee5e902..19d808e 100644[m
[1m--- a/Assets/Scripts/Human.cs[m
[1m+++ b/Assets/Scripts/Human.cs[m
[36m@@ -4,7 +4,7 @@[m [musing UnityEngine;[m
 using UnityEngine.AI;[m
 using UnityEditor;[m
 [m
[31m-public class Human : MonoBehaviour[m
[32m+[m[32mpublic class Guard : MonoBehaviour[m[41m[m
 {[m
 [m
 	public float minWaitTime;[m
[36m@@ -31,7 +31,7 @@[m [mpublic class Human : MonoBehaviour[m
 	public Color idleCol;[m
 	public Color chaseCol;[m
 	public bool passive;[m
[31m-	public Human[] alertOthers;[m
[32m+[m	[32mpublic Guard[] alertOthers;[m[41m[m
 [m
 	private NavMeshAgent agent;[m
 	public HumanState state;[m
[36m@@ -103,7 +103,7 @@[m [mpublic class Human : MonoBehaviour[m
 			sightTimer += Time.deltaTime;[m
 			if (sightTimer > sightLengthError)[m
 			{[m
[31m-				foreach (Human h in alertOthers)[m
[32m+[m				[32mforeach (Guard h in alertOthers)[m[41m[m
 				{[m
 					h.MoveToAttack();[m
 				}[m
[36m@@ -160,21 +160,21 @@[m [mpublic class Human : MonoBehaviour[m
 		{[m
 			agent.SetDestination(lastPlayerPos);[m
 			sight.color = chaseCol;[m
[31m-			if (Vector3.Distance(GameManager.instance.player.transform.position, transform.position) < attackDist)[m
[32m+[m			[32mif (Vector3.Distance(GameManager.instance.Player.transform.position, transform.position) < attackDist)[m[41m[m
 			{[m
 				agent.isStopped = true;[m
 				state = HumanState.Attack;[m
 			}[m
 			return;[m
 		}[m
[31m-		Vector3 toPlayer = GameManager.instance.player.transform.position - sight.transform.position;[m
[32m+[m		[32mVector3 toPlayer = GameManager.instance.Player.transform.position - sight.transform.position;[m[41m[m
 		if (toPlayer.magnitude <= chaseViewDistance)[m
 		{[m
 			RaycastHit hit;[m
 			if (Physics.Raycast(sight.transform.position, toPlayer, out hit, viewDistance))[m
 			{[m
 				if (hit.collider.gameObject.GetComponent<Player>() != null)[m
[31m-					lastPlayerPos = GameManager.instance.player.transform.position;[m
[32m+[m					[32mlastPlayerPos = GameManager.instance.Player.transform.position;[m[41m[m
 				else[m
 				{[m
 					searchPosition = lastPlayerPos;[m
[36m@@ -191,7 +191,7 @@[m [mpublic class Human : MonoBehaviour[m
 		}[m
 		agent.SetDestination(lastPlayerPos);[m
 		sight.color = chaseCol;[m
[31m-		if (Vector3.Distance(GameManager.instance.player.transform.position, transform.position) < attackDist)[m
[32m+[m		[32mif (Vector3.Distance(GameManager.instance.Player.transform.position, transform.position) < attackDist)[m[41m[m
 		{[m
 			agent.isStopped = true;[m
 			state = HumanState.Attack;[m
[36m@@ -200,7 +200,7 @@[m [mpublic class Human : MonoBehaviour[m
 [m
 	private bool playerInSight()[m
 	{[m
[31m-		Vector3 toPlayer = GameManager.instance.player.transform.position - sight.transform.position;[m
[32m+[m		[32mVector3 toPlayer = GameManager.instance.Player.transform.position - sight.transform.position;[m[41m[m
 		float angle = Vector2.Angle(new Vector2(toPlayer.x, toPlayer.z),[m
 				new Vector2(transform.forward.x, transform.forward.z));[m
 		bool inSight = false;[m
[36m@@ -219,14 +219,14 @@[m [mpublic class Human : MonoBehaviour[m
 	{[m
 		if (moveToAttack)[m
 			moveToAttack = false;[m
[31m-		Vector3 direction = (GameManager.instance.player.transform.position - transform.position).normalized;[m
[32m+[m		[32mVector3 direction = (GameManager.instance.Player.transform.position - transform.position).normalized;[m[41m[m
 		Quaternion lookRotation = Quaternion.LookRotation(new Vector3(direction.x, 0, direction.z));[m
 		transform.rotation = Quaternion.Slerp(transform.rotation, lookRotation, Time.deltaTime * 12);[m
 [m
[31m-		Vector3 toPlayer = GameManager.instance.player.transform.position - head.transform.position;[m
[32m+[m		[32mVector3 toPlayer = GameManager.instance.Player.transform.position - head.transform.position;[m[41m[m
 		if (toPlayer.magnitude > attackDist)[m
 		{[m
[31m-			agent.SetDestination(GameManager.instance.player.transform.position);[m
[32m+[m			[32magent.SetDestination(GameManager.instance.Player.transform.position);[m[41m[m
 			agent.isStopped = false;[m
 			state = HumanState.Chase;[m
 			return;[m
[36m@@ -238,7 +238,7 @@[m [mpublic class Human : MonoBehaviour[m
 			{[m
 				if (hit.collider.gameObject.GetComponent<Player>() == null)[m
 				{[m
[31m-					agent.SetDestination(GameManager.instance.player.transform.position);[m
[32m+[m					[32magent.SetDestination(GameManager.instance.Player.transform.position);[m[41m[m
 					agent.isStopped = false;[m
 					state = HumanState.Chase;[m
 					return;[m
[36m@@ -253,7 +253,7 @@[m [mpublic class Human : MonoBehaviour[m
 			GameObject projectile = Instantiate(projectilePrefab);[m
 			projectile.transform.position = head.transform.position + transform.forward * 0.5f;[m
 			Projectile p = projectile.GetComponent<Projectile>();[m
[31m-			p.dir = GameManager.instance.player.transform.position - head.transform.position;[m
[32m+[m			[32mp.dir = GameManager.instance.Player.transform.position - head.transform.position;[m[41m[m
 			p.damage = damage;[m
 		}[m
 	}[m
[1mdiff --git a/Assets/Scripts/LevelManagement.meta b/Assets/Scripts/LevelManagement.meta[m
[1mnew file mode 100644[m
[1mindex 0000000..5a0b2e5[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scripts/LevelManagement.meta[m
[36m@@ -0,0 +1,8 @@[m
[32m+[m[32mfileFormatVersion: 2[m
[32m+[m[32mguid: 31d10ad249e33d548b5777cd704b46b4[m
[32m+[m[32mfolderAsset: yes[m
[32m+[m[32mDefaultImporter:[m
[32m+[m[32m  externalObjects: {}[m
[32m+[m[32m  userData:[m[41m [m
[32m+[m[32m  assetBundleName:[m[41m [m
[32m+[m[32m  assetBundleVariant:[m[41m [m
[1mdiff --git a/Assets/Scripts/LevelManagement/FadeTransition.cs b/Assets/Scripts/LevelManagement/FadeTransition.cs[m
[1mnew file mode 100644[m
[1mindex 0000000..0beed62[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scripts/LevelManagement/FadeTransition.cs[m
[36m@@ -0,0 +1,11 @@[m
[32m+[m[32m﻿using System.Collections;[m
[32m+[m[32musing System.Collections.Generic;[m
[32m+[m[32musing UnityEngine;[m
[32m+[m
[32m+[m[32mpublic class FadeTransition : TransitionEffect[m
[32m+[m[32m{[m
[32m+[m[32m    public IEnumerator Transition(System.Action callback) {[m
[32m+[m[32m        yield return null;[m
[32m+[m[32m        callback();[m
[32m+[m[32m    }[m
[32m+[m[32m}[m
[1mdiff --git a/Assets/Scripts/Student.cs.meta b/Assets/Scripts/LevelManagement/FadeTransition.cs.meta[m
[1msimilarity index 83%[m
[1mrename from Assets/Scripts/Student.cs.meta[m
[1mrename to Assets/Scripts/LevelManagement/FadeTransition.cs.meta[m
[1mindex f6c0367..1b3b799 100644[m
[1m--- a/Assets/Scripts/Student.cs.meta[m
[1m+++ b/Assets/Scripts/LevelManagement/FadeTransition.cs.meta[m
[36m@@ -1,5 +1,5 @@[m
 fileFormatVersion: 2[m
[31m-guid: 3597dfd4f5fd27f409803652a0d62aa9[m
[32m+[m[32mguid: 49cab610ecd907841bd8e27ba17e4fb2[m
 MonoImporter:[m
   externalObjects: {}[m
   serializedVersion: 2[m
[1mdiff --git a/Assets/Scripts/LevelManagement/LevelTransition.cs b/Assets/Scripts/LevelManagement/LevelTransition.cs[m
[1mnew file mode 100644[m
[1mindex 0000000..af1983a[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scripts/LevelManagement/LevelTransition.cs[m
[36m@@ -0,0 +1,29 @@[m
[32m+[m[32m﻿using System.Collections;[m
[32m+[m[32musing System.Collections.Generic;[m
[32m+[m[32musing UnityEngine;[m
[32m+[m[32musing UnityEngine.SceneManagement;[m
[32m+[m
[32m+[m[32mpublic class LevelTransition : MonoBehaviour[m
[32m+[m[32m{[m
[32m+[m	[32mpublic string toLevel;[m
[32m+[m	[32mpublic int spawnPointID = 0;[m
[32m+[m	[32mpublic TransitionEffect outTransition;[m[41m [m
[32m+[m
[32m+[m	[32mprivate void OnTriggerEnter(Collider other) {[m
[32m+[m		[32mif (outTransition == null) {[m
[32m+[m			[32mStartCoroutine(outTransition.Transition(() => {[m
[32m+[m				[32mGameManager.instance.SpawnPointID = spawnPointID;[m
[32m+[m				[32mSceneManager.LoadScene(toLevel);[m
[32m+[m			[32m}));[m
[32m+[m		[32m} else {[m
[32m+[m			[32mGameManager.instance.SpawnPointID = spawnPointID;[m
[32m+[m			[32mSceneManager.LoadScene(toLevel);[m
[32m+[m		[32m}[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mvoid OnDrawGizmos()[m
[32m+[m[32m    {[m
[32m+[m[32m        Gizmos.color = new Color(1, 0, 0, 0.3f);[m
[32m+[m[32m        Gizmos.DrawCube(transform.position + new Vector3(0,1,0), new Vector3(1, 2, 1));[m
[32m+[m[32m    }[m
[32m+[m[32m}[m
[1mdiff --git a/Assets/Scripts/LevelTransition.cs.meta b/Assets/Scripts/LevelManagement/LevelTransition.cs.meta[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/LevelTransition.cs.meta[m
[1mrename to Assets/Scripts/LevelManagement/LevelTransition.cs.meta[m
[1mdiff --git a/Assets/Scripts/LevelManagement/SpawnPoint.cs b/Assets/Scripts/LevelManagement/SpawnPoint.cs[m
[1mnew file mode 100644[m
[1mindex 0000000..c2e4cf3[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scripts/LevelManagement/SpawnPoint.cs[m
[36m@@ -0,0 +1,16 @@[m
[32m+[m[32m﻿using System.Collections;[m
[32m+[m[32musing System.Collections.Generic;[m
[32m+[m[32musing UnityEngine;[m
[32m+[m
[32m+[m[32mpublic class SpawnPoint : MonoBehaviour[m
[32m+[m[32m{[m
[32m+[m[32m    public void OrientActor(Transform actor) {[m
[32m+[m[32m        actor.position = transform.position + Vector3.up;[m
[32m+[m[32m        actor.rotation = transform.rotation;[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m[32m    void OnDrawGizmos() {[m
[32m+[m[32m        Gizmos.color = new Color(0, 1, 0, 0.3f);[m
[32m+[m[32m        Gizmos.DrawCube(transform.position + new Vector3(0,1,0), new Vector3(1, 2, 1));[m
[32m+[m[32m    }[m
[32m+[m[32m}[m
[1mdiff --git a/Assets/Scripts/LevelManagement/SpawnPoint.cs.meta b/Assets/Scripts/LevelManagement/SpawnPoint.cs.meta[m
[1mnew file mode 100644[m
[1mindex 0000000..1eb5149[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scripts/LevelManagement/SpawnPoint.cs.meta[m
[36m@@ -0,0 +1,11 @@[m
[32m+[m[32mfileFormatVersion: 2[m
[32m+[m[32mguid: bcb395a5241a3934e80899fffd824cc0[m
[32m+[m[32mMonoImporter:[m
[32m+[m[32m  externalObjects: {}[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  defaultReferences: [][m
[32m+[m[32m  executionOrder: 0[m
[32m+[m[32m  icon: {instanceID: 0}[m
[32m+[m[32m  userData:[m[41m [m
[32m+[m[32m  assetBundleName:[m[41m [m
[32m+[m[32m  assetBundleVariant:[m[41m [m
[1mdiff --git a/Assets/Scripts/LevelManagement/TransitionEffect.cs b/Assets/Scripts/LevelManagement/TransitionEffect.cs[m
[1mnew file mode 100644[m
[1mindex 0000000..d61375f[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scripts/LevelManagement/TransitionEffect.cs[m
[36m@@ -0,0 +1,8 @@[m
[32m+[m[32m﻿using System.Collections;[m
[32m+[m[32musing System.Collections.Generic;[m
[32m+[m[32musing UnityEngine;[m
[32m+[m
[32m+[m[32mpublic interface TransitionEffect[m
[32m+[m[32m{[m
[32m+[m[32m    IEnumerator Transition(System.Action callback);[m
[32m+[m[32m}[m
[1mdiff --git a/Assets/Scripts/LevelManagement/TransitionEffect.cs.meta b/Assets/Scripts/LevelManagement/TransitionEffect.cs.meta[m
[1mnew file mode 100644[m
[1mindex 0000000..169f27f[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scripts/LevelManagement/TransitionEffect.cs.meta[m
[36m@@ -0,0 +1,11 @@[m
[32m+[m[32mfileFormatVersion: 2[m
[32m+[m[32mguid: 0dd615a2483cd824084f553d95fd4c22[m
[32m+[m[32mMonoImporter:[m
[32m+[m[32m  externalObjects: {}[m
[32m+[m[32m  serializedVersion: 2[m
[32m+[m[32m  defaultReferences: [][m
[32m+[m[32m  executionOrder: 0[m
[32m+[m[32m  icon: {instanceID: 0}[m
[32m+[m[32m  userData:[m[41m [m
[32m+[m[32m  assetBundleName:[m[41m [m
[32m+[m[32m  assetBundleVariant:[m[41m [m
[1mdiff --git a/Assets/Scripts/LevelManager.cs b/Assets/Scripts/LevelManager.cs[m
[1mindex 600dd9c..1cde749 100644[m
[1m--- a/Assets/Scripts/LevelManager.cs[m
[1m+++ b/Assets/Scripts/LevelManager.cs[m
[36m@@ -5,67 +5,6 @@[m [musing UnityEngine.SceneManagement;[m
 [m
 public class LevelManager : MonoBehaviour[m
 {[m
[31m-	public Vector2[] curGoal;[m
[31m-	public Goal[] goals;[m
[31m-	int curGoalIndex = 0;[m
[31m-	public bool canIncrement = true;[m
[31m-[m
[31m-[m
[31m-	public Fade fade;[m
[31m-	public float fadeTime;[m
[31m-	public string nextLevel;[m
[31m-[m
[31m-	private void Start()[m
[31m-	{[m
[31m-		curGoal = goals[0].notes;[m
[31m-	}[m
[31m-[m
[31m-	public void IncrementGoal()[m
[31m-	{[m
[31m-		if (canIncrement)[m
[31m-		{[m
[31m-			++curGoalIndex;[m
[31m-			if (curGoalIndex >= goals.Length)[m
[31m-			{[m
[31m-				EndGame();[m
[31m-				return;[m
[31m-			}[m
[31m-			curGoal = goals[curGoalIndex].notes;[m
[31m-			GameManager.instance.teacher.attempt = 1;[m
[31m-		}[m
[31m-		else[m
[31m-			StartCoroutine(IncrementAsync());[m
[31m-	}[m
[31m-[m
[31m-	IEnumerator IncrementAsync()[m
[31m-	{[m
[31m-		yield return new WaitUntil(() => canIncrement);[m
[31m-		++curGoalIndex;[m
[31m-		if (curGoalIndex >= goals.Length)[m
[31m-		{[m
[31m-			EndGame();[m
[31m-		}[m
[31m-		else[m
[31m-		{[m
[31m-			curGoal = goals[curGoalIndex].notes;[m
[31m-		}[m
[31m-	}[m
[31m-[m
[31m-	void EndGame()[m
[31m-	{[m
[31m-		StartCoroutine(TransitionAnimation());[m
[31m-	}[m
[31m-[m
[31m-	IEnumerator TransitionAnimation()[m
[31m-	{[m
[31m-		fade.FadeOut(fadeTime);[m
[31m-		yield return new WaitForSeconds(fadeTime);[m
[31m-		SceneManager.LoadScene("End");[m
[31m-	}[m
[31m-}[m
[31m-[m
[31m-[System.Serializable][m
[31m-public class Goal[m
[31m-{[m
[31m-	public Vector2[] notes = new Vector2[3];[m
[32m+[m	[32mpublic SpawnPoint[] spawnPoints;[m
[32m+[m	[32mpublic Guard[] guards;[m
 }[m
\ No newline at end of file[m
[1mdiff --git a/Assets/Scripts/LevelTransition.cs b/Assets/Scripts/LevelTransition.cs[m
[1mdeleted file mode 100644[m
[1mindex 721fa3a..0000000[m
[1m--- a/Assets/Scripts/LevelTransition.cs[m
[1m+++ /dev/null[m
[36m@@ -1,38 +0,0 @@[m
[31m-﻿using System.Collections;[m
[31m-using System.Collections.Generic;[m
[31m-using UnityEngine;[m
[31m-using UnityEngine.SceneManagement;[m
[31m-[m
[31m-public class LevelTransition : MonoBehaviour[m
[31m-{[m
[31m-	public Fade fade;[m
[31m-	public float fadeTime;[m
[31m-	public string nextLevel;[m
[31m-	void Start()[m
[31m-	{[m
[31m-[m
[31m-	}[m
[31m-[m
[31m-	// Update is called once per frame[m
[31m-	void Update()[m
[31m-	{[m
[31m-[m
[31m-	}[m
[31m-[m
[31m-	public void Transition()[m
[31m-	{[m
[31m-		StartCoroutine(TransitionAnimation());[m
[31m-	}[m
[31m-[m
[31m-	IEnumerator TransitionAnimation()[m
[31m-	{[m
[31m-		fade.FadeOut(fadeTime);[m
[31m-		yield return new WaitForSeconds(fadeTime);[m
[31m-		SceneManager.LoadScene(nextLevel);[m
[31m-	}[m
[31m-[m
[31m-	private void OnTriggerEnter(Collider other)[m
[31m-	{[m
[31m-		Transition();[m
[31m-	}[m
[31m-}[m
[1mdiff --git a/Assets/Scripts/Managers.meta b/Assets/Scripts/Managers.meta[m
[1mnew file mode 100644[m
[1mindex 0000000..eb9d1fd[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scripts/Managers.meta[m
[36m@@ -0,0 +1,8 @@[m
[32m+[m[32mfileFormatVersion: 2[m
[32m+[m[32mguid: 31fe9b5fabb74f241ba3920d2af88a8c[m
[32m+[m[32mfolderAsset: yes[m
[32m+[m[32mDefaultImporter:[m
[32m+[m[32m  externalObjects: {}[m
[32m+[m[32m  userData:[m[41m [m
[32m+[m[32m  assetBundleName:[m[41m [m
[32m+[m[32m  assetBundleVariant:[m[41m [m
[1mdiff --git a/Assets/Scripts/Managers/GameManager.cs b/Assets/Scripts/Managers/GameManager.cs[m
[1mnew file mode 100644[m
[1mindex 0000000..cf5c35a[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scripts/Managers/GameManager.cs[m
[36m@@ -0,0 +1,54 @@[m
[32m+[m[32m﻿using System.Collections;[m
[32m+[m[32musing System.Collections.Generic;[m
[32m+[m[32musing UnityEngine;[m
[32m+[m[32musing UnityEngine.SceneManagement;[m
[32m+[m
[32m+[m[32mpublic class GameManager : MonoBehaviour[m
[32m+[m[32m{[m
[32m+[m	[32mpublic static GameManager instance;[m
[32m+[m[41m	[m
[32m+[m	[32mint spawnPointID;[m
[32m+[m	[32mpublic int SpawnPointID {[m
[32m+[m		[32mset { spawnPointID = value; }[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mLevelManager level;[m
[32m+[m	[32mpublic LevelManager Level {[m
[32m+[m		[32mget { return level; }[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mPlayer player;[m
[32m+[m	[32mpublic Player Player {[m
[32m+[m		[32mget { return player; }[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mpublic Color[] NOTE_COLORS = { Color.red, Color.blue, Color.green, Color.yellow };[m
[32m+[m	[32mpublic AnimationCurve NOTE_CURVE;[m
[32m+[m
[32m+[m	[32mprivate void Awake()[m
[32m+[m	[32m{[m
[32m+[m		[32mif (instance == null)[m
[32m+[m			[32minstance = this;[m
[32m+[m		[32melse if (instance != this)[m
[32m+[m			[32mDestroy(gameObject);[m
[32m+[m		[32mDontDestroyOnLoad(gameObject);[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mvoid OnEnable()[m
[32m+[m[32m    {[m
[32m+[m[32m        SceneManager.sceneLoaded += OnSceneLoaded;[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m	[32mvoid OnDisable()[m
[32m+[m[32m    {[m
[32m+[m[32m        SceneManager.sceneLoaded -= OnSceneLoaded;[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m	[32mprivate void OnSceneLoaded(Scene scene, LoadSceneMode mode)[m
[32m+[m	[32m{[m
[32m+[m		[32mplayer = Object.FindObjectOfType<Player>();[m
[32m+[m		[32mlevel = Object.FindObjectOfType<LevelManager>();[m
[32m+[m		[32mlevel.spawnPoints[spawnPointID].OrientActor(player.transform);[m
[32m+[m	[32m}[m
[32m+[m[41m	[m
[32m+[m[32m}[m
[1mdiff --git a/Assets/Scripts/GameManager.cs.meta b/Assets/Scripts/Managers/GameManager.cs.meta[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/GameManager.cs.meta[m
[1mrename to Assets/Scripts/Managers/GameManager.cs.meta[m
[1mdiff --git a/Assets/Scripts/Procedural Audio.meta b/Assets/Scripts/Procedural Audio.meta[m
[1mnew file mode 100644[m
[1mindex 0000000..e4c1fb7[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scripts/Procedural Audio.meta[m	
[36m@@ -0,0 +1,8 @@[m
[32m+[m[32mfileFormatVersion: 2[m
[32m+[m[32mguid: e26b2fa79da887142bad168323f0221d[m
[32m+[m[32mfolderAsset: yes[m
[32m+[m[32mDefaultImporter:[m
[32m+[m[32m  externalObjects: {}[m
[32m+[m[32m  userData:[m[41m [m
[32m+[m[32m  assetBundleName:[m[41m [m
[32m+[m[32m  assetBundleVariant:[m[41m [m
[1mdiff --git a/Assets/Scripts/Classes.meta b/Assets/Scripts/Procedural Audio/Classes.meta[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/Classes.meta[m
[1mrename to Assets/Scripts/Procedural Audio/Classes.meta[m
[1mdiff --git a/Assets/Scripts/Classes/SawWave.cs b/Assets/Scripts/Procedural Audio/Classes/SawWave.cs[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/Classes/SawWave.cs[m
[1mrename to Assets/Scripts/Procedural Audio/Classes/SawWave.cs[m
[1mdiff --git a/Assets/Scripts/Classes/SawWave.cs.meta b/Assets/Scripts/Procedural Audio/Classes/SawWave.cs.meta[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/Classes/SawWave.cs.meta[m
[1mrename to Assets/Scripts/Procedural Audio/Classes/SawWave.cs.meta[m
[1mdiff --git a/Assets/Scripts/Classes/SinusWave.cs b/Assets/Scripts/Procedural Audio/Classes/SinusWave.cs[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/Classes/SinusWave.cs[m
[1mrename to Assets/Scripts/Procedural Audio/Classes/SinusWave.cs[m
[1mdiff --git a/Assets/Scripts/Classes/SinusWave.cs.meta b/Assets/Scripts/Procedural Audio/Classes/SinusWave.cs.meta[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/Classes/SinusWave.cs.meta[m
[1mrename to Assets/Scripts/Procedural Audio/Classes/SinusWave.cs.meta[m
[1mdiff --git a/Assets/Scripts/Classes/SquareWave.cs b/Assets/Scripts/Procedural Audio/Classes/SquareWave.cs[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/Classes/SquareWave.cs[m
[1mrename to Assets/Scripts/Procedural Audio/Classes/SquareWave.cs[m
[1mdiff --git a/Assets/Scripts/Classes/SquareWave.cs.meta b/Assets/Scripts/Procedural Audio/Classes/SquareWave.cs.meta[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/Classes/SquareWave.cs.meta[m
[1mrename to Assets/Scripts/Procedural Audio/Classes/SquareWave.cs.meta[m
[1mdiff --git a/Assets/Scripts/ProceduralAudioController.cs b/Assets/Scripts/Procedural Audio/ProceduralAudioController.cs[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/ProceduralAudioController.cs[m
[1mrename to Assets/Scripts/Procedural Audio/ProceduralAudioController.cs[m
[1mdiff --git a/Assets/Scripts/ProceduralAudioController.cs.meta b/Assets/Scripts/Procedural Audio/ProceduralAudioController.cs.meta[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/ProceduralAudioController.cs.meta[m
[1mrename to Assets/Scripts/Procedural Audio/ProceduralAudioController.cs.meta[m
[1mdiff --git a/Assets/Scripts/SpectrumVisualizerController.cs b/Assets/Scripts/Procedural Audio/SpectrumVisualizerController.cs[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/SpectrumVisualizerController.cs[m
[1mrename to Assets/Scripts/Procedural Audio/SpectrumVisualizerController.cs[m
[1mdiff --git a/Assets/Scripts/SpectrumVisualizerController.cs.meta b/Assets/Scripts/Procedural Audio/SpectrumVisualizerController.cs.meta[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/SpectrumVisualizerController.cs.meta[m
[1mrename to Assets/Scripts/Procedural Audio/SpectrumVisualizerController.cs.meta[m
[1mdiff --git a/Assets/Scripts/Student.cs b/Assets/Scripts/Student.cs[m
[1mdeleted file mode 100644[m
[1mindex eaab832..0000000[m
[1m--- a/Assets/Scripts/Student.cs[m
[1m+++ /dev/null[m
[36m@@ -1,73 +0,0 @@[m
[31m-﻿using System.Collections;[m
[31m-using System.Collections.Generic;[m
[31m-using UnityEngine;[m
[31m-[m
[31m-public class Student : MonoBehaviour[m
[31m-{[m
[31m-[m
[31m-	public ProceduralAudioController[] audioControllers;[m
[31m-	public float noteLength;[m
[31m-	public float notePause = 0.1f;[m
[31m-	public float chordLength;[m
[31m-	public AnimationCurve speakCurve;[m
[31m-	public Transform[] speechSpheres;[m
[31m-	bool speaking;[m
[31m-[m
[31m-	void SetNotes(int attempt)[m
[31m-	{[m
[31m-		Vector2[] goal = GameManager.instance.levelManager.curGoal;[m
[31m-		for (int i = 0; i < audioControllers.Length; i++)[m
[31m-		{[m
[31m-			audioControllers[i].mainFrequency = goal[i].x + Random.Range(-40f, 40f) / Mathf.Pow(attempt, 2);[m
[31m-			audioControllers[i].frequencyModulationOscillatorIntensity = goal[i].y + Random.Range(-3f, 3f) / Mathf.Pow(attempt, 2);[m
[31m-		}[m
[31m-[m
[31m-	}[m
[31m-[m
[31m-	public IEnumerator LearnChord(int attempt)[m
[31m-	{[m
[31m-		speaking = true;[m
[31m-		SetNotes(attempt);[m
[31m-		float time = 0;[m
[31m-		float perc = 0;[m
[31m-		float lastTime = Time.realtimeSinceStartup;[m
[31m-		Quaternion curLook = transform.rotation;[m
[31m-		for (int i = 0; i < audioControllers.Length; i++)[m
[31m-		{[m
[31m-			time = 0;[m
[31m-			lastTime = Time.realtimeSinceStartup;[m
[31m-			speechSpheres[i].gameObject.SetActive(true);[m
[31m-			do[m
[31m-			{[m
[31m-				time += Time.realtimeSinceStartup - lastTime;[m
[31m-				lastTime = Time.realtimeSinceStartup;[m
[31m-				perc = Mathf.Clamp01(time / noteLength);[m
[31m-				float val = Mathf.Lerp(0, 0.6f, speakCurve.Evaluate(perc));[m
[31m-				audioControllers[i].masterVolume = val;[m
[31m-				speechSpheres[i].localScale = new Vector3(val / 2, val / 2, val / 2);[m
[31m-				yield return null;[m
[31m-			} while (perc < 1);[m
[31m-			speechSpheres[i].gameObject.SetActive(false);[m
[31m-			yield return new WaitForSeconds(notePause);[m
[31m-		}[m
[31m-		time = 0;[m
[31m-		lastTime = Time.realtimeSinceStartup;[m
[31m-		speechSpheres[3].gameObject.SetActive(true);[m
[31m-		do[m
[31m-		{[m
[31m-			time += Time.realtimeSinceStartup - lastTime;[m
[31m-			lastTime = Time.realtimeSinceStartup;[m
[31m-			perc = Mathf.Clamp01(time / chordLength);[m
[31m-			float val = Mathf.Lerp(0, 0.8f, speakCurve.Evaluate(perc));[m
[31m-			foreach (ProceduralAudioController p in audioControllers)[m
[31m-			{[m
[31m-				p.masterVolume = val;[m
[31m-			}[m
[31m-			speechSpheres[3].localScale = new Vector3(val / 1.5F, val / 1.5F, val / 1.5F);[m
[31m-			yield return null;[m
[31m-		} while (perc < 1);[m
[31m-		speechSpheres[3].gameObject.SetActive(false);[m
[31m-		GameManager.instance.levelManager.canIncrement = true;[m
[31m-		speaking = false;[m
[31m-	}[m
[31m-}[m
[1mdiff --git a/Assets/Scripts/Teacher.cs b/Assets/Scripts/Teacher.cs[m
[1mdeleted file mode 100644[m
[1mindex 2d5f54d..0000000[m
[1m--- a/Assets/Scripts/Teacher.cs[m
[1m+++ /dev/null[m
[36m@@ -1,127 +0,0 @@[m
[31m-﻿using System.Collections;[m
[31m-using System.Collections.Generic;[m
[31m-using UnityEngine;[m
[31m-[m
[31m-public class Teacher : MonoBehaviour[m
[31m-{[m
[31m-	public ProceduralAudioController[] audioControllers;[m
[31m-	public float teachRate;[m
[31m-	public float noteLength;[m
[31m-	public float notePause = 0.1f;[m
[31m-	public float chordLength;[m
[31m-	public AnimationCurve speakCurve;[m
[31m-	float teachTimer;[m
[31m-	public float initialDelay = 20;[m
[31m-	bool speaking;[m
[31m-	public Student student;[m
[31m-	public int maxAttempts;[m
[31m-	public int attempt = 1;[m
[31m-	public Transform[] speechSpheres;[m
[31m-	public Vector3 home;[m
[31m-[m
[31m-	Human human;[m
[31m-	IEnumerator coroutine;[m
[31m-[m
[31m-[m
[31m-	private void Start()[m
[31m-	{[m
[31m-		teachTimer = initialDelay;[m
[31m-		human = GetComponent<Human>();[m
[31m-		home = transform.position;[m
[31m-	}[m
[31m-[m
[31m-	void Update()[m
[31m-	{[m
[31m-		if (human.state == HumanState.Attack || human.state == HumanState.Chase)[m
[31m-		{[m
[31m-			StopCoroutine(coroutine);[m
[31m-			Silence();[m
[31m-			GameManager.instance.levelManager.canIncrement = true;[m
[31m-			speaking = false;[m
[31m-		}[m
[31m-		if (!speaking)[m
[31m-		{[m
[31m-			teachTimer -= Time.deltaTime;[m
[31m-			if (teachTimer < 0)[m
[31m-			{[m
[31m-				coroutine = TeachChord();[m
[31m-				StartCoroutine(coroutine);[m
[31m-			}[m
[31m-		}[m
[31m-	}[m
[31m-[m
[31m-	void SetNotes()[m
[31m-	{[m
[31m-		Vector2[] goal = GameManager.instance.levelManager.curGoal;[m
[31m-		for (int i = 0; i < audioControllers.Length; i++)[m
[31m-		{[m
[31m-			audioControllers[i].mainFrequency = goal[i].x;[m
[31m-			audioControllers[i].frequencyModulationOscillatorIntensity = goal[i].y;[m
[31m-		}[m
[31m-	}[m
[31m-[m
[31m-	void Silence()[m
[31m-	{[m
[31m-		for (int i = 0; i < audioControllers.Length; i++)[m
[31m-		{[m
[31m-			audioControllers[i].masterVolume = 0;[m
[31m-		}[m
[31m-	}[m
[31m-[m
[31m-	IEnumerator TeachChord()[m
[31m-	{[m
[31m-		speaking = true;[m
[31m-		human.goTo(home);[m
[31m-		yield return new WaitUntil(() => Vector3.Distance(transform.position, home) < 2);[m
[31m-		teachTimer = teachRate;[m
[31m-		GameManager.instance.levelManager.canIncrement = false;[m
[31m-		SetNotes();[m
[31m-		float time = 0;[m
[31m-		float perc = 0;[m
[31m-		float lastTime = Time.realtimeSinceStartup;[m
[31m-		Quaternion curLook = transform.rotation;[m
[31m-		for (int i = 0; i < audioControllers.Length; i++)[m
[31m-		{[m
[31m-			time = 0;[m
[31m-			lastTime = Time.realtimeSinceStartup;[m
[31m-			speechSpheres[i].gameObject.SetActive(true);[m
[31m-			do[m
[31m-			{[m
[31m-				time += Time.realtimeSinceStartup - lastTime;[m
[31m-				lastTime = Time.realtimeSinceStartup;[m
[31m-				perc = Mathf.Clamp01(time / noteLength);[m
[31m-				float val = Mathf.Lerp(0, 0.6f, speakCurve.Evaluate(perc));[m
[31m-				audioControllers[i].masterVolume = val;[m
[31m-				speechSpheres[i].localScale = new Vector3(val / 2, val / 2, val / 2);[m
[31m-				yield return null;[m
[31m-			} while (perc < 1);[m
[31m-			speechSpheres[i].gameObject.SetActive(false);[m
[31m-			yield return new WaitForSeconds(notePause);[m
[31m-		}[m
[31m-		time = 0;[m
[31m-		lastTime = Time.realtimeSinceStartup;[m
[31m-		speechSpheres[3].gameObject.SetActive(true);[m
[31m-		do[m
[31m-		{[m
[31m-			time += Time.realtimeSinceStartup - lastTime;[m
[31m-			lastTime = Time.realtimeSinceStartup;[m
[31m-			perc = Mathf.Clamp01(time / chordLength);[m
[31m-			float val = Mathf.Lerp(0, 0.8f, speakCurve.Evaluate(perc));[m
[31m-			foreach (ProceduralAudioController p in audioControllers)[m
[31m-			{[m
[31m-				p.masterVolume = val;[m
[31m-			}[m
[31m-			speechSpheres[3].localScale = new Vector3(val / 1.5F, val / 1.5F, val / 1.5F);[m
[31m-			yield return null;[m
[31m-		} while (perc < 1);[m
[31m-		speechSpheres[3].gameObject.SetActive(false);[m
[31m-		GameManager.instance.levelManager.canIncrement = true;[m
[31m-		speaking = false;[m
[31m-		yield return new WaitForSeconds(notePause);[m
[31m-		StartCoroutine(student.LearnChord(attempt++));[m
[31m-		if (attempt > maxAttempts)[m
[31m-		{[m
[31m-			GameManager.instance.levelManager.IncrementGoal();[m
[31m-		}[m
[31m-	}[m
[31m-}[m
[1mdiff --git a/Assets/Scripts/Teacher.cs.meta b/Assets/Scripts/Teacher.cs.meta[m
[1mdeleted file mode 100644[m
[1mindex 41e5d35..0000000[m
[1m--- a/Assets/Scripts/Teacher.cs.meta[m
[1m+++ /dev/null[m
[36m@@ -1,11 +0,0 @@[m
[31m-fileFormatVersion: 2[m
[31m-guid: aedcb01a1d3cfed49a6b90f8c54ef5ca[m
[31m-MonoImporter:[m
[31m-  externalObjects: {}[m
[31m-  serializedVersion: 2[m
[31m-  defaultReferences: [][m
[31m-  executionOrder: 0[m
[31m-  icon: {instanceID: 0}[m
[31m-  userData: [m
[31m-  assetBundleName: [m
[31m-  assetBundleVariant: [m
[1mdiff --git a/Assets/Scripts/Voice.meta b/Assets/Scripts/Voice.meta[m
[1mnew file mode 100644[m
[1mindex 0000000..254acf2[m
[1m--- /dev/null[m
[1m+++ b/Assets/Scripts/Voice.meta[m
[36m@@ -0,0 +1,8 @@[m
[32m+[m[32mfileFormatVersion: 2[m
[32m+[m[32mguid: 31ef0eae7fbc10342b8e493ad3cd262c[m
[32m+[m[32mfolderAsset: yes[m
[32m+[m[32mDefaultImporter:[m
[32m+[m[32m  externalObjects: {}[m
[32m+[m[32m  userData:[m[41m [m
[32m+[m[32m  assetBundleName:[m[41m [m
[32m+[m[32m  assetBundleVariant:[m[41m [m
[1mdiff --git a/Assets/Scripts/Voice.cs b/Assets/Scripts/Voice/Voice.cs[m
[1msimilarity index 88%[m
[1mrename from Assets/Scripts/Voice.cs[m
[1mrename to Assets/Scripts/Voice/Voice.cs[m
[1mindex 68d429e..3124206 100644[m
[1m--- a/Assets/Scripts/Voice.cs[m
[1m+++ b/Assets/Scripts/Voice/Voice.cs[m
[36m@@ -1,246 +1,249 @@[m
[31m-﻿using System.Collections;[m
[31m-using System.Collections.Generic;[m
[31m-using UnityEngine;[m
[31m-using UnityEngine.EventSystems;[m
[31m-using UnityEngine.UI;[m
[31m-[m
[31m-public class Voice : MonoBehaviour, IPointerDownHandler, IPointerUpHandler, IDragHandler[m
[31m-{[m
[31m-	public Player player;[m
[31m-	public ProceduralAudioController[] audioControllers;[m
[31m-	public GameObject voiceNotePrefab;[m
[31m-	public float voiceSpeed = 0.3f;[m
[31m-	public float noteMaxVol = 0.5f;[m
[31m-	public float chordMaxVol = 0.8f;[m
[31m-	public float chordLength = 1f;[m
[31m-	public Image successRing;[m
[31m-	public float noteError = 40f;[m
[31m-	float chordTime;[m
[31m-[m
[31m-[m
[31m-	RectTransform rectTransform;[m
[31m-[m
[31m-	VoiceState voiceState;[m
[31m-	bool canSpeak = true;[m
[31m-	int curNote;[m
[31m-	VoiceNote[] voiceNotes;[m
[31m-	float[] voiceVels;[m
[31m-[m
[31m-	private void Start()[m
[31m-	{[m
[31m-		rectTransform = GetComponent<RectTransform>();[m
[31m-		voiceNotes = new VoiceNote[audioControllers.Length];[m
[31m-		voiceVels = new float[audioControllers.Length];[m
[31m-		chordTime = chordLength;[m
[31m-	}[m
[31m-[m
[31m-	float ErrorFunc(float error)[m
[31m-	{[m
[31m-		error /= 12;[m
[31m-		return 1 - (Mathf.Pow(2.71f, error) - Mathf.Pow(2.71f, -error)) / (Mathf.Pow(2.71f, error) + Mathf.Pow(2.71f, -error));[m
[31m-	}[m
[31m-[m
[31m-	private void Update()[m
[31m-	{[m
[31m-[m
[31m-		switch (voiceState)[m
[31m-		{[m
[31m-			case VoiceState.SpeakingNote:[m
[31m-				SetNote(audioControllers[curNote], voiceNotes[curNote].input.x, voiceNotes[curNote].input.y);[m
[31m-				for (int i = 0; i < audioControllers.Length; i++)[m
[31m-				{[m
[31m-					audioControllers[i].masterVolume = Mathf.SmoothDamp(audioControllers[i].masterVolume, i == curNote ? noteMaxVol : 0, ref voiceVels[i], voiceSpeed);[m
[31m-				}[m
[31m-				break;[m
[31m-			case VoiceState.SpeakingChord:[m
[31m-				for (int i = 0; i < audioControllers.Length; i++)[m
[31m-				{[m
[31m-					audioControllers[i].masterVolume = Mathf.SmoothDamp(audioControllers[i].masterVolume, chordMaxVol, ref voiceVels[i], voiceSpeed);[m
[31m-				}[m
[31m-				chordTime -= Time.deltaTime;[m
[31m-				if (chordTime <= 0)[m
[31m-				{[m
[31m-					chordTime = chordLength;[m
[31m-					voiceState = VoiceState.Silent;[m
[31m-					canSpeak = true;[m
[31m-					for (int i = audioControllers.Length - 1; i >= 0; i--)[m
[31m-						RemoveVoiceNote(i);[m
[31m-				}[m
[31m-				break;[m
[31m-			case VoiceState.Silent:[m
[31m-				for (int i = 0; i < audioControllers.Length; i++)[m
[31m-				{[m
[31m-					audioControllers[i].masterVolume = Mathf.SmoothDamp(audioControllers[i].masterVolume, 0, ref voiceVels[i], voiceSpeed);[m
[31m-				}[m
[31m-				break;[m
[31m-		}[m
[31m-[m
[31m-		if (Input.GetButtonDown("Undo") && canSpeak)[m
[31m-		{[m
[31m-			curNote = (int)Mathf.Clamp(curNote - 1, 0, voiceNotes.Length + 5);[m
[31m-			RemoveVoiceNote(curNote);[m
[31m-		}[m
[31m-	}[m
[31m-[m
[31m-	public void OnPointerDown(PointerEventData eventData)[m
[31m-	{[m
[31m-		if (!canSpeak)[m
[31m-			return;[m
[31m-		voiceState = VoiceState.SpeakingNote;[m
[31m-		voiceNotes[curNote] = MakeVoiceNote(eventData.position - (Vector2)rectTransform.position);[m
[31m-		UpdateNote(curNote, eventData.position);[m
[31m-	}[m
[31m-[m
[31m-	public void OnDrag(PointerEventData eventData)[m
[31m-	{[m
[31m-		if (voiceNotes[curNote] == null || !canSpeak)[m
[31m-			return;[m
[31m-		Vector2 localPos = eventData.position - (Vector2)rectTransform.position;[m
[31m-		if (localPos.magnitude > rectTransform.sizeDelta.x / 2)[m
[31m-		{[m
[31m-			voiceState = VoiceState.Silent;[m
[31m-			RemoveVoiceNote(curNote);[m
[31m-			return;[m
[31m-		}[m
[31m-		UpdateNote(curNote, eventData.position);[m
[31m-	}[m
[31m-[m
[31m-	public void OnPointerUp(PointerEventData eventData)[m
[31m-	{[m
[31m-		if (voiceState == VoiceState.SpeakingNote)[m
[31m-		{[m
[31m-			voiceState = VoiceState.Silent;[m
[31m-			curNote++;[m
[31m-			if (curNote == voiceNotes.Length)[m
[31m-			{[m
[31m-				curNote = 0;[m
[31m-				canSpeak = false;[m
[31m-				StartCoroutine(SpeakChord());[m
[31m-			}[m
[31m-		}[m
[31m-	}[m
[31m-[m
[31m-	void UpdateNote(int note, Vector2 pos)[m
[31m-	{[m
[31m-		voiceNotes[note].transform.position = pos;[m
[31m-		voiceNotes[note].input = GetVoiceVect(pos - (Vector2)rectTransform.position, rectTransform.sizeDelta);[m
[31m-		voiceNotes[note].UpdateLine(GetActualDir(voiceNotes[note].input, GameManager.instance.levelManager.curGoal[note]));[m
[31m-	}[m
[31m-[m
[31m-	void SetNote(ProceduralAudioController pac, float freq, float osc)[m
[31m-	{[m
[31m-		pac.mainFrequency = freq;[m
[31m-		pac.frequencyModulationOscillatorIntensity = osc;[m
[31m-	}[m
[31m-[m
[31m-	void RemoveVoiceNote(int index)[m
[31m-	{[m
[31m-		if (voiceNotes[index] == null)[m
[31m-			return;[m
[31m-		Destroy(voiceNotes[index].gameObject);[m
[31m-		// if (index < voiceNotes.Length - 1)[m
[31m-		// 	voiceNotes[index] = voiceNotes[index + 1];[m
[31m-		// else[m
[31m-		voiceNotes[index] = null;[m
[31m-	}[m
[31m-[m
[31m-	VoiceNote MakeVoiceNote(Vector2 pos)[m
[31m-	{[m
[31m-		GameObject noteObject = Instantiate(voiceNotePrefab, transform);[m
[31m-		VoiceNote vn = noteObject.GetComponent<VoiceNote>();[m
[31m-		Vector2 input = GetVoiceVect(pos, rectTransform.sizeDelta);[m
[31m-		vn.Instantiate(input, curNote);[m
[31m-		vn.transform.localPosition = pos;[m
[31m-		return vn;[m
[31m-	}[m
[31m-[m
[31m-	Vector2 GetVoiceVect(Vector2 pos, Vector2 sizeDelta)[m
[31m-	{[m
[31m-		Vector2 polar = FromCartesian(pos);[m
[31m-		return new Vector2(Map(-Mathf.PI / 2, 3 * Mathf.PI / 2, 400, 900, polar.x), Map(0, sizeDelta.x / 2, 10, 1, polar.y));[m
[31m-	}[m
[31m-[m
[31m-	Vector2 GetActualDir(Vector2 input, Vector2 actual)[m
[31m-	{[m
[31m-		Vector2 mInput = new Vector2(Map(400, 900, -Mathf.PI / 2, 3 * Mathf.PI / 2, input.x), Map(10, 1, 0, rectTransform.sizeDelta.x / 2, input.y));[m
[31m-		Vector2 mActual = new Vector2(Map(400, 900, -Mathf.PI / 2, 3 * Mathf.PI / 2, actual.x), Map(10, 1, 0, rectTransform.sizeDelta.x / 2, actual.y));[m
[31m-		return ToCartesian(mActual) - ToCartesian(mInput);[m
[31m-	}[m
[31m-[m
[31m-	float Map(float from, float to, float from2, float to2, float value)[m
[31m-	{[m
[31m-		return Mathf.Lerp(from2, to2, Mathf.InverseLerp(from, to, value));[m
[31m-	}[m
[31m-[m
[31m-	public Vector2 FromCartesian(Vector3 cart)[m
[31m-	{[m
[31m-		if (cart.x == 0f)[m
[31m-			cart.x = Mathf.Epsilon;[m
[31m-		float radius = cart.magnitude;[m
[31m-		float theta = Mathf.Atan(cart.y / cart.x);[m
[31m-		if (cart.x < 0f)[m
[31m-			theta += Mathf.PI;[m
[31m-		return new Vector2(theta, radius);[m
[31m-	}[m
[31m-[m
[31m-	public Vector3 ToCartesian(Vector2 v)[m
[31m-	{[m
[31m-		return v.y * new Vector2(Mathf.Cos(v.x), Mathf.Sin(v.x));[m
[31m-	}[m
[31m-[m
[31m-	public bool CheckSuccess()[m
[31m-	{[m
[31m-		bool val = true;[m
[31m-		foreach (VoiceNote v in voiceNotes)[m
[31m-		{[m
[31m-			val &= v.error.magnitude < noteError;[m
[31m-		}[m
[31m-		return val;[m
[31m-	}[m
[31m-[m
[31m-	void AlertNearestHuman()[m
[31m-	{[m
[31m-		Human nearest = GameManager.instance.humans[0];[m
[31m-		float nearDist = Vector3.Distance(nearest.transform.position, player.transform.position);[m
[31m-		foreach (Human h in GameManager.instance.humans)[m
[31m-		{[m
[31m-			float newDist = Vector3.Distance(h.transform.position, player.transform.position);[m
[31m-			if (newDist < nearDist)[m
[31m-			{[m
[31m-				nearDist = newDist;[m
[31m-				nearest = h;[m
[31m-			}[m
[31m-		}[m
[31m-		nearest.Alert(player.transform.position);[m
[31m-	}[m
[31m-[m
[31m-	IEnumerator SpeakChord()[m
[31m-	{[m
[31m-		yield return new WaitForSeconds(0.4f);[m
[31m-		AlertNearestHuman();[m
[31m-		bool success = CheckSuccess();[m
[31m-		if (success)[m
[31m-			GameManager.instance.levelManager.IncrementGoal();[m
[31m-		for (int i = 0; i < voiceNotes.Length; i++)[m
[31m-		{[m
[31m-			if (success)[m
[31m-			{[m
[31m-				if (i == 0)[m
[31m-					voiceNotes[i].drawError(0, chordLength, successRing);[m
[31m-				else[m
[31m-					voiceNotes[i].drawError(0, chordLength);[m
[31m-			}[m
[31m-			else[m
[31m-			{[m
[31m-				float error = ErrorFunc(Vector3.Distance(GameManager.instance.teacher.transform.position, player.transform.position));[m
[31m-				voiceNotes[i].drawError(error, chordLength);[m
[31m-			}[m
[31m-		}[m
[31m-		voiceState = VoiceState.SpeakingChord;[m
[31m-	}[m
[31m-}[m
[31m-[m
[31m-public enum VoiceState[m
[31m-{[m
[31m-	Silent, SpeakingNote, SpeakingChord[m
[32m+[m[32m﻿using System.Collections;[m
[32m+[m[32musing System.Collections.Generic;[m
[32m+[m[32musing UnityEngine;[m
[32m+[m[32musing UnityEngine.EventSystems;[m
[32m+[m[32musing UnityEngine.UI;[m
[32m+[m
[32m+[m[32mpublic class Voice : MonoBehaviour, IPointerDownHandler, IPointerUpHandler, IDragHandler[m
[32m+[m[32m{[m
[32m+[m	[32mpublic Player player;[m
[32m+[m	[32mpublic ProceduralAudioController[] audioControllers;[m
[32m+[m	[32mpublic GameObject voiceNotePrefab;[m
[32m+[m	[32mpublic float voiceSpeed = 0.3f;[m
[32m+[m	[32mpublic float noteMaxVol = 0.5f;[m
[32m+[m	[32mpublic float chordMaxVol = 0.8f;[m
[32m+[m	[32mpublic float chordLength = 1f;[m
[32m+[m	[32mpublic Image successRing;[m
[32m+[m	[32mpublic float noteError = 40f;[m
[32m+[m	[32mfloat chordTime;[m
[32m+[m
[32m+[m
[32m+[m	[32mRectTransform rectTransform;[m
[32m+[m
[32m+[m	[32mVoiceState voiceState;[m
[32m+[m	[32mbool canSpeak = true;[m
[32m+[m	[32mint curNote;[m
[32m+[m	[32mVoiceNote[] voiceNotes;[m
[32m+[m	[32mfloat[] voiceVels;[m
[32m+[m
[32m+[m	[32mprivate void Start()[m
[32m+[m	[32m{[m
[32m+[m		[32mrectTransform = GetComponent<RectTransform>();[m
[32m+[m		[32mvoiceNotes = new VoiceNote[audioControllers.Length];[m
[32m+[m		[32mvoiceVels = new float[audioControllers.Length];[m
[32m+[m		[32mchordTime = chordLength;[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mfloat ErrorFunc(float error)[m
[32m+[m	[32m{[m
[32m+[m		[32merror /= 12;[m
[32m+[m		[32mreturn 1 - (Mathf.Pow(2.71f, error) - Mathf.Pow(2.71f, -error)) / (Mathf.Pow(2.71f, error) + Mathf.Pow(2.71f, -error));[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mprivate void Update()[m
[32m+[m	[32m{[m
[32m+[m
[32m+[m		[32mswitch (voiceState)[m
[32m+[m		[32m{[m
[32m+[m			[32mcase VoiceState.SpeakingNote:[m
[32m+[m				[32mSetNote(audioControllers[curNote], voiceNotes[curNote].input.x, voiceNotes[curNote].input.y);[m
[32m+[m				[32mfor (int i = 0; i < audioControllers.Length; i++)[m
[32m+[m				[32m{[m
[32m+[m					[32maudioControllers[i].masterVolume = Mathf.SmoothDamp(audioControllers[i].masterVolume, i == curNote ? noteMaxVol : 0, ref voiceVels[i], voiceSpeed);[m
[32m+[m				[32m}[m
[32m+[m				[32mbreak;[m
[32m+[m			[32mcase VoiceState.SpeakingChord:[m
[32m+[m				[32mfor (int i = 0; i < audioControllers.Length; i++)[m
[32m+[m				[32m{[m
[32m+[m					[32maudioControllers[i].masterVolume = Mathf.SmoothDamp(audioControllers[i].masterVolume, chordMaxVol, ref voiceVels[i], voiceSpeed);[m
[32m+[m				[32m}[m
[32m+[m				[32mchordTime -= Time.deltaTime;[m
[32m+[m				[32mif (chordTime <= 0)[m
[32m+[m				[32m{[m
[32m+[m					[32mchordTime = chordLength;[m
[32m+[m					[32mvoiceState = VoiceState.Silent;[m
[32m+[m					[32mcanSpeak = true;[m
[32m+[m					[32mfor (int i = audioControllers.Length - 1; i >= 0; i--)[m
[32m+[m						[32mRemoveVoiceNote(i);[m
[32m+[m				[32m}[m
[32m+[m				[32mbreak;[m
[32m+[m			[32mcase VoiceState.Silent:[m
[32m+[m				[32mfor (int i = 0; i < audioControllers.Length; i++)[m
[32m+[m				[32m{[m
[32m+[m					[32maudioControllers[i].masterVolume = Mathf.SmoothDamp(audioControllers[i].masterVolume, 0, ref voiceVels[i], voiceSpeed);[m
[32m+[m				[32m}[m
[32m+[m				[32mbreak;[m
[32m+[m		[32m}[m
[32m+[m
[32m+[m		[32mif (Input.GetButtonDown("Undo") && canSpeak)[m
[32m+[m		[32m{[m
[32m+[m			[32mcurNote = (int)Mathf.Clamp(curNote - 1, 0, voiceNotes.Length + 5);[m
[32m+[m			[32mRemoveVoiceNote(curNote);[m
[32m+[m		[32m}[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mpublic void OnPointerDown(PointerEventData eventData)[m
[32m+[m	[32m{[m
[32m+[m		[32mif (!canSpeak)[m
[32m+[m			[32mreturn;[m
[32m+[m		[32mvoiceState = VoiceState.SpeakingNote;[m
[32m+[m		[32mvoiceNotes[curNote] = MakeVoiceNote(eventData.position - (Vector2)rectTransform.position);[m
[32m+[m		[32mUpdateNote(curNote, eventData.position);[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mpublic void OnDrag(PointerEventData eventData)[m
[32m+[m	[32m{[m
[32m+[m		[32mif (voiceNotes[curNote] == null || !canSpeak)[m
[32m+[m			[32mreturn;[m
[32m+[m		[32mVector2 localPos = eventData.position - (Vector2)rectTransform.position;[m
[32m+[m		[32mif (localPos.magnitude > rectTransform.sizeDelta.x / 2)[m
[32m+[m		[32m{[m
[32m+[m			[32mvoiceState = VoiceState.Silent;[m
[32m+[m			[32mRemoveVoiceNote(curNote);[m
[32m+[m			[32mreturn;[m
[32m+[m		[32m}[m
[32m+[m		[32mUpdateNote(curNote, eventData.position);[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mpublic void OnPointerUp(PointerEventData eventData)[m
[32m+[m	[32m{[m
[32m+[m		[32mif (voiceState == VoiceState.SpeakingNote)[m
[32m+[m		[32m{[m
[32m+[m			[32mvoiceState = VoiceState.Silent;[m
[32m+[m			[32mcurNote++;[m
[32m+[m			[32mif (curNote == voiceNotes.Length)[m
[32m+[m			[32m{[m
[32m+[m				[32mcurNote = 0;[m
[32m+[m				[32mcanSpeak = false;[m
[32m+[m				[32mStartCoroutine(SpeakChord());[m
[32m+[m			[32m}[m
[32m+[m		[32m}[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mvoid UpdateNote(int note, Vector2 pos)[m
[32m+[m	[32m{[m
[32m+[m		[32mvoiceNotes[note].transform.position = pos;[m
[32m+[m		[32mvoiceNotes[note].input = GetVoiceVect(pos - (Vector2)rectTransform.position, rectTransform.sizeDelta);[m
[32m+[m		[32m// TODO Fix Voice to work locally[m
[32m+[m		[32m// voiceNotes[note].UpdateLine(GetActualDir(voiceNotes[note].input, GameManager.instance.Level.curGoal[note]));[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mvoid SetNote(ProceduralAudioController pac, float freq, float osc)[m
[32m+[m	[32m{[m
[32m+[m		[32mpac.mainFrequency = freq;[m
[32m+[m		[32mpac.frequencyModulationOscillatorIntensity = osc;[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mvoid RemoveVoiceNote(int index)[m
[32m+[m	[32m{[m
[32m+[m		[32mif (voiceNotes[index] == null)[m
[32m+[m			[32mreturn;[m
[32m+[m		[32mDestroy(voiceNotes[index].gameObject);[m
[32m+[m		[32m// if (index < voiceNotes.Length - 1)[m
[32m+[m		[32m// 	voiceNotes[index] = voiceNotes[index + 1];[m
[32m+[m		[32m// else[m
[32m+[m		[32mvoiceNotes[index] = null;[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mVoiceNote MakeVoiceNote(Vector2 pos)[m
[32m+[m	[32m{[m
[32m+[m		[32mGameObject noteObject = Instantiate(voiceNotePrefab, transform);[m
[32m+[m		[32mVoiceNote vn = noteObject.GetComponent<VoiceNote>();[m
[32m+[m		[32mVector2 input = GetVoiceVect(pos, rectTransform.sizeDelta);[m
[32m+[m		[32mvn.Instantiate(input, curNote);[m
[32m+[m		[32mvn.transform.localPosition = pos;[m
[32m+[m		[32mreturn vn;[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mVector2 GetVoiceVect(Vector2 pos, Vector2 sizeDelta)[m
[32m+[m	[32m{[m
[32m+[m		[32mVector2 polar = FromCartesian(pos);[m
[32m+[m		[32mreturn new Vector2(Map(-Mathf.PI / 2, 3 * Mathf.PI / 2, 400, 900, polar.x), Map(0, sizeDelta.x / 2, 10, 1, polar.y));[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mVector2 GetActualDir(Vector2 input, Vector2 actual)[m
[32m+[m	[32m{[m
[32m+[m		[32mVector2 mInput = new Vector2(Map(400, 900, -Mathf.PI / 2, 3 * Mathf.PI / 2, input.x), Map(10, 1, 0, rectTransform.sizeDelta.x / 2, input.y));[m
[32m+[m		[32mVector2 mActual = new Vector2(Map(400, 900, -Mathf.PI / 2, 3 * Mathf.PI / 2, actual.x), Map(10, 1, 0, rectTransform.sizeDelta.x / 2, actual.y));[m
[32m+[m		[32mreturn ToCartesian(mActual) - ToCartesian(mInput);[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mfloat Map(float from, float to, float from2, float to2, float value)[m
[32m+[m	[32m{[m
[32m+[m		[32mreturn Mathf.Lerp(from2, to2, Mathf.InverseLerp(from, to, value));[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mpublic Vector2 FromCartesian(Vector3 cart)[m
[32m+[m	[32m{[m
[32m+[m		[32mif (cart.x == 0f)[m
[32m+[m			[32mcart.x = Mathf.Epsilon;[m
[32m+[m		[32mfloat radius = cart.magnitude;[m
[32m+[m		[32mfloat theta = Mathf.Atan(cart.y / cart.x);[m
[32m+[m		[32mif (cart.x < 0f)[m
[32m+[m			[32mtheta += Mathf.PI;[m
[32m+[m		[32mreturn new Vector2(theta, radius);[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mpublic Vector3 ToCartesian(Vector2 v)[m
[32m+[m	[32m{[m
[32m+[m		[32mreturn v.y * new Vector2(Mathf.Cos(v.x), Mathf.Sin(v.x));[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mpublic bool CheckSuccess()[m
[32m+[m	[32m{[m
[32m+[m		[32mbool val = true;[m
[32m+[m		[32mforeach (VoiceNote v in voiceNotes)[m
[32m+[m		[32m{[m
[32m+[m			[32mval &= v.error.magnitude < noteError;[m
[32m+[m		[32m}[m
[32m+[m		[32mreturn val;[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mvoid AlertNearestHuman()[m
[32m+[m	[32m{[m
[32m+[m		[32mGuard nearest = GameManager.instance.Level.guards[0];[m
[32m+[m		[32mfloat nearDist = Vector3.Distance(nearest.transform.position, player.transform.position);[m
[32m+[m		[32mforeach (Guard g in GameManager.instance.Level.guards)[m
[32m+[m		[32m{[m
[32m+[m			[32mfloat newDist = Vector3.Distance(g.transform.position, player.transform.position);[m
[32m+[m			[32mif (newDist < nearDist)[m
[32m+[m			[32m{[m
[32m+[m				[32mnearDist = newDist;[m
[32m+[m				[32mnearest = g;[m
[32m+[m			[32m}[m
[32m+[m		[32m}[m
[32m+[m		[32mnearest.Alert(player.transform.position);[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mIEnumerator SpeakChord()[m
[32m+[m	[32m{[m
[32m+[m		[32myield return new WaitForSeconds(0.4f);[m
[32m+[m		[32mAlertNearestHuman();[m
[32m+[m		[32mbool success = CheckSuccess();[m
[32m+[m		[32m// TODO Decouple voice from Level[m
[32m+[m		[32m// if (success)[m
[32m+[m		[32m// 	GameManager.instance.Level.IncrementGoal();[m
[32m+[m		[32mfor (int i = 0; i < voiceNotes.Length; i++)[m
[32m+[m		[32m{[m
[32m+[m			[32mif (success)[m
[32m+[m			[32m{[m
[32m+[m				[32mif (i == 0)[m
[32m+[m					[32mvoiceNotes[i].drawError(0, chordLength, successRing);[m
[32m+[m				[32melse[m
[32m+[m					[32mvoiceNotes[i].drawError(0, chordLength);[m
[32m+[m			[32m}[m
[32m+[m			[32melse[m
[32m+[m			[32m{[m
[32m+[m				[32m// TODO decouple from game manager[m
[32m+[m				[32m// float error = ErrorFunc(Vector3.Distance(GameManager.instance.teacher.transform.position, player.transform.position));[m
[32m+[m				[32m// voiceNotes[i].drawError(error, chordLength);[m
[32m+[m			[32m}[m
[32m+[m		[32m}[m
[32m+[m		[32mvoiceState = VoiceState.SpeakingChord;[m
[32m+[m	[32m}[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mpublic enum VoiceState[m
[32m+[m[32m{[m
[32m+[m	[32mSilent, SpeakingNote, SpeakingChord[m
 }[m
\ No newline at end of file[m
[1mdiff --git a/Assets/Scripts/Voice.cs.meta b/Assets/Scripts/Voice/Voice.cs.meta[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/Voice.cs.meta[m
[1mrename to Assets/Scripts/Voice/Voice.cs.meta[m
[1mdiff --git a/Assets/Scripts/VoiceNote.cs b/Assets/Scripts/Voice/VoiceNote.cs[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/VoiceNote.cs[m
[1mrename to Assets/Scripts/Voice/VoiceNote.cs[m
[1mdiff --git a/Assets/Scripts/VoiceNote.cs.meta b/Assets/Scripts/Voice/VoiceNote.cs.meta[m
[1msimilarity index 100%[m
[1mrename from Assets/Scripts/VoiceNote.cs.meta[m
[1mrename to Assets/Scripts/Voice/VoiceNote.cs.meta[m
[1mdiff --git a/ProjectSettings/EditorBuildSettings.asset b/ProjectSettings/EditorBuildSettings.asset[m
[1mindex abdd917..4aa5e9e 100644[m
[1m--- a/ProjectSettings/EditorBuildSettings.asset[m
[1m+++ b/ProjectSettings/EditorBuildSettings.asset[m
[36m@@ -17,4 +17,10 @@[m [mEditorBuildSettings:[m
   - enabled: 1[m
     path: Assets/Scenes/End.unity[m
     guid: d5d6f9ca891f6e84382dab7693fdcf8e[m
[32m+[m[32m  - enabled: 1[m
[32m+[m[32m    path: Assets/Scenes/MechanicsTesting/MechanicsTesting1.unity[m
[32m+[m[32m    guid: 7332de914921c364487ec84875bdaf3e[m
[32m+[m[32m  - enabled: 1[m
[32m+[m[32m    path: Assets/Scenes/MechanicsTesting/MechanicsTesting0.unity[m
[32m+[m[32m    guid: e23281db68bf41d4486c81842718c8f4[m
   m_configObjects: {}[m
