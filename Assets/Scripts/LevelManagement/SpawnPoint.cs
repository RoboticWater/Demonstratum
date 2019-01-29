using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnPoint : MonoBehaviour
{
    public void OrientActor(Transform actor) {
        actor.position = transform.position + 0.9f * Vector3.up;
        actor.rotation = transform.rotation;
    }

    void OnDrawGizmos() {
        Gizmos.color = new Color(0, 1, 0, 0.3f);
        Gizmos.DrawCube(transform.position + new Vector3(0,1,0), new Vector3(1, 2, 1));
    }
}
