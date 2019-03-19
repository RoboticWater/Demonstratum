using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WoodSelector : Selector
{
    public List<Wood> wood;
    public float outlineWidth = 0.1f;
    public float highlightTime = 0.1f;
    public AnimationCurve highlightCurve;

    bool highlightOn;
    bool highlighting;

    bool pickedUp;
    bool pickingUp;
    public float pickUpTime = 0.3f;
    public AnimationCurve pickUpCurve;

    public float verticalOffset = 0.5f;
    public float depthOffset = 1;
    public float depthWoodOffset = 0.1f;

    public float dropForce = 2;

    public override void SetHighlight(bool on) {
        highlightOn = on;
        if (!highlighting) {
            StartCoroutine(Highlight());
        }
        
    }

    public override void Select() {
        if (pickedUp) {
            Drop();
        } else {
            pickedUp = true;
            StartCoroutine(PickUp());
        }
    }

    private void Update() {
        if (pickedUp && !pickingUp) {
            Transform playerTransform = GameManager.instance.Player.cam.transform;
            
            for (int i = 0; i < wood.Count; i++) {
                if (wood[i].dead) {
                    wood.Remove(wood[i]);
                    i--;
                    continue;
                }
                wood[i].transform.position = playerTransform.position + playerTransform.forward * depthOffset - playerTransform.up * verticalOffset + playerTransform.forward * i * depthWoodOffset;
                wood[i].transform.rotation = Quaternion.LookRotation(playerTransform.right);
            }
        }
    }

    IEnumerator Highlight() {
        highlighting = true;
        float lastTime = Time.timeSinceLevelLoad;
        float perc = highlightOn ? 0 : 1;
        do {
            perc += (highlightOn ? 1 : -1) * (Time.timeSinceLevelLoad - lastTime) / highlightTime;
            lastTime = Time.timeSinceLevelLoad;
            foreach (Wood w in wood) {
                w.material.SetFloat("_OutlineWidth", Mathf.Lerp(0, outlineWidth, highlightCurve.Evaluate(perc)));
            }
            yield return null;
        } while(perc <= 1 && perc >= 0);
        foreach (Wood w in wood) {
            w.material.SetFloat("_OutlineWidth", highlightOn ? outlineWidth : 0);
        }
        highlighting = false;
    }

    IEnumerator PickUp() {
        for (int i = 0; i < wood.Count; i++) {
            if (wood[i].dead) {
                wood.Remove(wood[i]);
                i--;
                continue;
            }
        }
        GameManager.instance.Player.holding = this;
        pickingUp = true;
        float startTime = Time.timeSinceLevelLoad;
        float perc = 0;
        Vector3[] startPositions = new Vector3[wood.Count];
        Quaternion[] startRotations = new Quaternion[wood.Count];
        Vector3 endPosition;
        Quaternion endRotation;
        Transform playerTransform = GameManager.instance.Player.cam.transform;
        for (int i = 0; i < wood.Count; i++) {
            wood[i].DoPhysics = false;
            startPositions[i] = wood[i].transform.position;
            startRotations[i] = wood[i].transform.rotation;
        }
        do {
            endPosition = playerTransform.position + playerTransform.forward * depthOffset - playerTransform.up * verticalOffset;
            endRotation = Quaternion.LookRotation(playerTransform.right);
            perc = (Time.timeSinceLevelLoad - startTime) / pickUpTime;
            for (int i = 0; i < wood.Count; i++) {
                float val = pickUpCurve.Evaluate(perc);
                wood[i].transform.position = Vector3.Lerp(startPositions[i], endPosition + playerTransform.forward * i * depthWoodOffset, val);
                wood[i].transform.rotation = Quaternion.Lerp(startRotations[i], endRotation, val);
            }
            yield return null;
        } while(perc <= 1 && perc >= 0);
        endPosition = playerTransform.position + playerTransform.forward * depthOffset - playerTransform.up * verticalOffset;
        endRotation = Quaternion.LookRotation(playerTransform.right);
        for (int i = 0; i < wood.Count; i++) {
            wood[i].transform.position = endPosition + playerTransform.forward * i * depthWoodOffset;
            wood[i].transform.rotation = endRotation;
        }
        pickingUp = false;
    }

    void Drop() {
        pickedUp = false;
        GameManager.instance.Player.holding = null;
        for (int i = 0; i < wood.Count; i++) {
            wood[i].deathOffset = i * Random.Range(0.4f, 0.6f);
            wood[i].DoPhysics = true;
            wood[i].GetComponent<Rigidbody>().AddForce(GameManager.instance.Player.cam.transform.forward * dropForce, ForceMode.Impulse);
        }
    }
}
