using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public interface SoundReactor
{
    void OnSound(Note n);
    void OnSoundFinish(Note n);
}
