using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemigoIA : Personaje
{
    public float direccion = -1f;

    protected override void Awake()
    {
        base.Awake();
    }
    void Update()
    {
        rb.velocity = new Vector2(direccion * velocidad, rb.velocity.y);
    }
}
