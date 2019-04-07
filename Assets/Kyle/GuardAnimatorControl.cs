using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GuardAnimatorControl : MonoBehaviour
{
    Animator anim;
    Transform parentTrans;
    public Transform head;
    public Transform sphere;
    Vector3 priorPos;

    // Start is called before the first frame update
    void Start()
    {
        anim = GetComponent<Animator>();
        parentTrans = GetComponentInParent<Transform>();
        priorPos = parentTrans.position;
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 velocity = parentTrans.position - priorPos;
        priorPos = parentTrans.position;
        float movementMag = velocity.magnitude;
        sphere.transform.position = head.transform.position;

        if (movementMag > .05f)
        {
            anim.SetBool("walking", true);
            anim.SetBool("idle", false);
            //Vector3 v = transform.InverseTransformDirection(velocity.normalized);
            //transform.forward = Vector3.Lerp(transform.forward, v, .2f * Time.deltaTime);
        }
        else
        {
            anim.SetBool("walking", false);
            anim.SetBool("idle", true);
            //transform.forward = Vector3.Lerp(transform.forward, parentTrans.forward, .2f * Time.deltaTime);
        }

        if (anim.GetBool("walking"))
        {
            anim.SetFloat("speed", 1);
        }
    }
}
