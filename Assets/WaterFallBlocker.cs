using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;

public class WaterFallBlocker : PushButton
{
    [SerializeField]
    Transform particles;
    [SerializeField]
    WaterFallBlocker[] parents;

    [HideInInspector] public bool active;

    public override void Select()
    {
        throw new System.NotImplementedException();
    }

    // IEnumerator ToggleActive() {
    //     if (parents.Any(p => p.active)) {
            
    //     }
    // }
}
