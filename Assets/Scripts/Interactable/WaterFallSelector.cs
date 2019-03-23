using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaterFallSelector : PushButton
{
    public WaterFallBlocker blocker;
    public override void Select()
    {
        blocker.Select();
    }
}
