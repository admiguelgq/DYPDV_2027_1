using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraSwitcher : MonoBehaviour{
    public GameObject fpsCam;
    public GameObject tpsCam;
    bool usingFPS = false;
    void Update(){
        if (Input.GetKeyDown(KeyCode.Tab)){
            usingFPS = !usingFPS;
            fpsCam.SetActive(usingFPS);
            tpsCam.SetActive(!usingFPS);
        }
    }
}
