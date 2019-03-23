using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Elevator : MonoBehaviour
{
    public float maxSpeed = 0.5f;
    public float speedSmooth = 0.3f;
    public float elevatorError = 0.001f;

    public int CurFloor = 1;
    ElevatorDoor[] doors;
    Transform[] floorTransforms;
    bool moving;

    Vector3 moveTarget;
    Vector3 velocity;

    private void Update() {
        if (moving)
            transform.position = Vector3.SmoothDamp(transform.position, moveTarget, ref velocity, speedSmooth, maxSpeed);
    }

    public void MoveToFloor(int floor) {
        if (!moving)
            StartCoroutine(MoveToFloorRoutine(floor));
    }

    IEnumerator MoveToFloorRoutine(int floor) {
        moving = true;
        if (CurFloor == floor) {
            doors[floor].Open();
        } else {
            moveTarget = floorTransforms[floor].position;
            yield return new WaitUntil(() => Vector3.Distance(transform.position, moveTarget) < elevatorError);
            doors[floor].Open();
        }

        moving = false;
    }
}