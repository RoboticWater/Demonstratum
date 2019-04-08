using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public interface SoundReactor
{
    void OnSound(Note n, NoteLine l);
    void OnSoundFinish(Note n, NoteLine l);
}
