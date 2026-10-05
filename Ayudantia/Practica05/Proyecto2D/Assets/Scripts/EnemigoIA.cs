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
    private void OnCollisionEnter2D(Collision2D col)
    {
        if (col.gameObject.CompareTag("Pared") ||
            col.gameObject.CompareTag("Obstaculo"))
        {
            direccion *= -1;
            sr.flipX = !sr.flipX;
        }

        if (col.gameObject.CompareTag("Player"))
        {
            if (col.contacts[0].normal.y < 0)
            {
                RecibirDano(1);
            }
            else
            {
                col.gameObject.GetComponent<Jugador>().RecibirDano(1);
            }

        }

    }
}
