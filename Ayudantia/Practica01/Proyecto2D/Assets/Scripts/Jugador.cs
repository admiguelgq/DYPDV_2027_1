using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Jugador : MonoBehaviour
{
    void Update()
    {
        
    }
    private void FixedUpdate()
    {
        
    }

    private void LateUpdate()
    {
        
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        Debug.Log("Chocando con " + collision.gameObject.name);
    }

    private void OnCollisionStay2D(Collision2D collision)
    {
        Debug.Log("Sigue chocando con " + collision.gameObject.name);
    }

    private void OnDestroy()
    {
        
    }

}
