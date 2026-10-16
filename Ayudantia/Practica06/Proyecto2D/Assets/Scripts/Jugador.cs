using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Jugador : Personaje
{
    public bool enSuelo = false;

    protected override void Awake()
    {
        base.Awake();
    }

    private void OnCollisionEnter2D(Collision2D col)
    {
        if (col.gameObject.CompareTag("Suelo"))
        {
            enSuelo = true;
        }
    }

    private void OnCollisionExit2D(Collision2D col)
    {
        if (col.gameObject.CompareTag("Suelo"))
        {
            enSuelo = false;
        }
    }
}
