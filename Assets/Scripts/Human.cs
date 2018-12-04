using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using UnityEditor;

public class Human : MonoBehaviour
{

    public float minWaitTime;
    public float maxWaitTime;
    public float minLookTime;
    public float maxLookTime;
    public float minlookDir;
    public float maxLookDir;
    [Range(0.0f, 50.0f)] public float searchRadius;
    [Range(0.0f, 2.0f)] public float moveError;
    public float lookSpeed;
    public AnimationCurve lookCurve;
    public float viewDistance;
    [Range(0.0f, 360.0f)]
    public float viewAngle;
    public float sightLengthError;
    private float sightTimer;

    private NavMeshAgent agent;
    public HumanState state;
    private Vector3 searchPosition;
    private float waitTimer;
    private float lookTimer;
    private bool moving;
    private float lookTarget;
    public Light sight;

    private IEnumerator lookRoutine;

    // void OnInspectorGUI()
    // {
    //     EditorGUILayout.LabelField("Wait Time");
    //     EditorGUILayout.MinMaxSlider(ref minWaitTime, ref maxWaitTime, 0, 30);
    //     EditorGUILayout.LabelField("Look Time");
    //     EditorGUILayout.MinMaxSlider(ref minLookTime, ref maxLookTime, 0, 5);
    //     EditorGUILayout.LabelField("Look Time");
    //     EditorGUILayout.MinMaxSlider(ref minLookTime, ref maxLookTime, -360, 360);
    // }
    
    void Start()
    {
        agent = GetComponent<NavMeshAgent>();
        sight = GetComponentInChildren<Light>();
        searchPosition = transform.position;
        lookRoutine = look();
        sightTimer = sightLengthError;
    }

    void Update()
    {
        switch(state) {
            case HumanState.Idle:
                break;
            case HumanState.Patrole:
                patrole();
                break;
            case HumanState.Chase:
                chase();
                break;
        }
    }

    void patrole() {
        if (playerInSight()) {
            sightTimer += Time.deltaTime;
            if (sightTimer > sightLengthError) {
                state = HumanState.Chase;
                sightTimer = 0;
            }
            // Debug.DrawLine(sight.transform.position,
            //     GameManager.instance.player.transform.position, Color.green);
        } else {
            sightTimer = 0;
            Debug.DrawLine(sight.transform.position,
                GameManager.instance.player.transform.position, Color.red);
            sight.color = new Color(1, 0.8628919f, 0, 1);
        }

        if (moving && Vector3.Distance(transform.position, agent.destination) < moveError) {
            moving = false;
        } else {
            waitTimer -= Time.deltaTime;
            lookTimer -= Time.deltaTime;
            if (waitTimer <= 0) {
                StopCoroutine(lookRoutine);
                setRandomTarget();
                moving = true;
                waitTimer = Random.Range(minWaitTime, maxWaitTime);
            }
            if (lookTimer <= 0) {
                StopCoroutine(lookRoutine);
                lookRoutine = look();
                lookTarget += Random.Range(minlookDir, maxLookDir);
                lookTimer = Random.Range(minLookTime, maxLookTime);
                StartCoroutine(lookRoutine);
            }
        }
    }

    void chase() {
        state = HumanState.Patrole;
        sight.color = Color.red;
    }

    private bool playerInSight() {
        Vector3 toPlayer = GameManager.instance.player.transform.position - sight.transform.position;
        float angle = Vector2.Angle(new Vector2(toPlayer.x, toPlayer.z), 
            new Vector2(transform.forward.x, transform.forward.z));
        bool inSight = false;
        if (angle < viewAngle && toPlayer.magnitude < viewDistance) {
            RaycastHit hit;
            if (Physics.Raycast(sight.transform.position, toPlayer, out hit, viewDistance)) {
                inSight = hit.collider.gameObject.GetComponent<Player>() != null;
            }
        }
        return inSight;
    }

    IEnumerator look() {
        float time = 0;
        float perc = 0;
        float lastTime = Time.realtimeSinceStartup;
        Quaternion curLook = transform.rotation;
        do
        {
          time += Time.realtimeSinceStartup - lastTime;
          lastTime = Time.realtimeSinceStartup;
          perc = Mathf.Clamp01(time / lookSpeed);
          
          transform.rotation = Quaternion.Lerp(curLook, Quaternion.Euler(curLook.eulerAngles.x, lookTarget, curLook.eulerAngles.z), lookCurve.Evaluate(perc));
          yield return null;
        } while (perc < 1);
    }

    void setRandomTarget() {
        Vector3 finalPosition = Vector3.zero;
        for (int i = 0; i < 1000 && finalPosition == Vector3.zero; i++) {
            Vector3 randomDirection = searchPosition + Random.insideUnitSphere * searchRadius;
            NavMeshHit hit;
            if (NavMesh.SamplePosition(randomDirection, out hit, searchRadius, 1)) {
                finalPosition = hit.position;            
            }
        }
        agent.SetDestination(finalPosition);
    }
}

public enum HumanState
{
    Idle, Patrole, Chase
}
