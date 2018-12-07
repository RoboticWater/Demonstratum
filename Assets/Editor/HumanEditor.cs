using UnityEngine;
using UnityEditor;

[CustomEditor(typeof(Human))]
[CanEditMultipleObjects]
public class HumanEditor : Editor {
    SerializedProperty minWaitTime;
    SerializedProperty maxWaitTime;
    SerializedProperty searchRadius;
    SerializedProperty viewAngle;
    SerializedProperty viewDistance;
    SerializedProperty sightLengthError;
    SerializedProperty minLookTime;
    SerializedProperty maxLookTime;
    SerializedProperty minLookDir;
    SerializedProperty maxLookDir;
    SerializedProperty lookSpeed;
    SerializedProperty lookCurve;
    SerializedProperty state;

    void OnEnable()
    {
        searchRadius = serializedObject.FindProperty("searchRadius");
        minWaitTime = serializedObject.FindProperty("minWaitTime");
        maxWaitTime = serializedObject.FindProperty("maxWaitTime");

        viewAngle = serializedObject.FindProperty("viewAngle");
        viewDistance = serializedObject.FindProperty("viewDistance");

        minLookTime = serializedObject.FindProperty("minLookTime");
        maxLookTime = serializedObject.FindProperty("maxLookTime");
        minLookDir = serializedObject.FindProperty("minLookDir");
        maxLookDir = serializedObject.FindProperty("maxLookDir");
        lookSpeed = serializedObject.FindProperty("lookSpeed");
        lookCurve = serializedObject.FindProperty("lookCurve");
        state = serializedObject.FindProperty("state");
        SceneView.onSceneGUIDelegate += OnSceneViewGUI;
    }

    void OnDisable()
    {
        SceneView.onSceneGUIDelegate -= OnSceneViewGUI;
    }
    
    public override void OnInspectorGUI() {
        serializedObject.Update();
        EditorGUILayout.LabelField("Searching", EditorStyles.boldLabel);
        EditorGUILayout.PropertyField(state);
        EditorGUILayout.PropertyField(searchRadius);
        MinMax("Wait Time:", minWaitTime, maxWaitTime);
        EditorGUILayout.LabelField("Random Looking", EditorStyles.boldLabel);
        MinMax("Look Time:", minLookTime, maxLookTime);
        MinMax("Look Dir:", minLookDir, maxLookDir);
        EditorGUILayout.PropertyField(lookSpeed);
        EditorGUILayout.PropertyField(lookCurve);
        EditorGUILayout.LabelField("Detection", EditorStyles.boldLabel);
        EditorGUILayout.PropertyField(viewAngle);
        EditorGUILayout.PropertyField(viewDistance);
        serializedObject.ApplyModifiedProperties();
    }

    private void OnSceneViewGUI(SceneView sv)
    {
        Handles.color = new Color(1,0,0,1);
        Human hu = target as Human;
        Handles.DrawWireDisc(hu.transform.position, hu.transform.up, searchRadius.floatValue);
        Handles.color = new Color(0,1,0,0.2f);
        Handles.DrawSolidArc(hu.transform.position, hu.transform.up, hu.transform.forward, viewAngle.floatValue, viewDistance.floatValue);
        Handles.DrawSolidArc(hu.transform.position, hu.transform.up, hu.transform.forward, -viewAngle.floatValue, viewDistance.floatValue);
    }

    private void MinMax(string label, SerializedProperty min, SerializedProperty max) {
        EditorGUILayout.BeginHorizontal();
        EditorGUILayout.LabelField(label);
        GUILayout.Label("Min");
        min.floatValue = EditorGUILayout.FloatField(min.floatValue);
        GUILayout.Label("Max");
        max.floatValue = EditorGUILayout.FloatField(max.floatValue);
        EditorGUILayout.EndHorizontal();
    }
}