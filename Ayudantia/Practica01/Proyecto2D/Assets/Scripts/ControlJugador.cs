using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ControlJugador : MonoBehaviour
{
    void Update()
    {
        float h = Input.GetAxis("Horizontal");

        if (Input.GetKeyDown(KeyCode.Space)){
            Debug.Log("Salto detectado");
        }

        if (h != 0) {
            Debug.Log("Movimeinto horizontal " + h);
        }
        
    }
}
