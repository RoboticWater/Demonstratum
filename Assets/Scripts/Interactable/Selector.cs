using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Selector : MonoBehaviour
{
    public abstract void Select();
    public abstract void SetHighlight(bool on);
}
