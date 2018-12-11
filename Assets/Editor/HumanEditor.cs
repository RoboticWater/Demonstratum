using UnityEngine;
using UnityEditor;

[CustomEditor(typeof(Human))]
[CanEditMultipleObjects]
public class HumanEditor : Editor
{
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
	SerializedProperty attackDist;
	SerializedProperty fireRate;
	SerializedProperty damage;
	SerializedProperty projectilePrefab;
	SerializedProperty chaseViewDistance;
	SerializedProperty idleCol;
	SerializedProperty chaseCol;

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

		attackDist = serializedObject.FindProperty("attackDist");
		fireRate = serializedObject.FindProperty("fireRate");
		damage = serializedObject.FindProperty("damage");
		projectilePrefab = serializedObject.FindProperty("projectilePrefab");
		chaseViewDistance = serializedObject.FindProperty("chaseViewDistance");
		idleCol = serializedObject.FindProperty("idleCol");
		chaseCol = serializedObject.FindProperty("chaseCol");
		SceneView.onSceneGUIDelegate += OnSceneViewGUI;
	}

	void OnDisable()
	{
		SceneView.onSceneGUIDelegate -= OnSceneViewGUI;
	}

	public override void OnInspectorGUI()
	{
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
		EditorGUILayout.PropertyField(attackDist);
		EditorGUILayout.PropertyField(fireRate);
		EditorGUILayout.PropertyField(damage);
		EditorGUILayout.PropertyField(projectilePrefab);
		EditorGUILayout.PropertyField(chaseViewDistance);
		EditorGUILayout.PropertyField(idleCol);
		EditorGUILayout.PropertyField(chaseCol);
		serializedObject.ApplyModifiedProperties();
	}

	private void OnSceneViewGUI(SceneView sv)
	{
		Handles.color = new Color(1, 0, 0, 1);
		Human hu = target as Human;
		Handles.DrawWireDisc(hu.transform.position, hu.transform.up, searchRadius.floatValue);
		Handles.color = new Color(0, 1, 0, 0.2f);
		Handles.DrawSolidArc(hu.transform.position, hu.transform.up, hu.transform.forward, viewAngle.floatValue, viewDistance.floatValue);
		Handles.DrawSolidArc(hu.transform.position, hu.transform.up, hu.transform.forward, -viewAngle.floatValue, viewDistance.floatValue);
	}

	private void MinMax(string label, SerializedProperty min, SerializedProperty max)
	{
		EditorGUILayout.BeginHorizontal();
		EditorGUILayout.LabelField(label);
		GUILayout.Label("Min");
		min.floatValue = EditorGUILayout.FloatField(min.floatValue);
		GUILayout.Label("Max");
		max.floatValue = EditorGUILayout.FloatField(max.floatValue);
		EditorGUILayout.EndHorizontal();
	}
}